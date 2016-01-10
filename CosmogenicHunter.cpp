#include "TFile.h"
#include "FixedTokensTypedValue.hpp"
#include "Utility.hpp"
#include "CandidateMapReader.hpp"
#include "Hunter.hpp"
#include "MuonCuts.hpp"
#include "LightNoiseCuts.hpp"
#include "NeutronCuts.hpp"
#include "CandidateCuts.hpp"

namespace CsHt = CosmogenicHunter;
namespace bpo = boost::program_options;

namespace CosmogenicHunter{

  template <class MuonAccuracy, class SingleAccuracy, class EntryAccuracy>
  void hunt(TFile* targetFile, const boost::filesystem::path& outputPath, const EntrySorter<EntryAccuracy>& entrySorter, const PairSeeker<SingleAccuracy>& pairSeeker, double muonWindowLenght, double neutronWindowLenght){

    TTree* globalInfo = dynamic_cast<TTree*>(targetFile->Get("GI"));
    std::ofstream outputStream(outputPath.string(), std::ios::binary);
    
    Hunter<MuonAccuracy, SingleAccuracy, EntryAccuracy> hunter(entrySorter, pairSeeker, muonWindowLenght, neutronWindowLenght);
    hunter.chaseAndSave(globalInfo, outputStream);

  }
  
}

int main(int argc, char* argv[]){
 
  boost::filesystem::path targetPath, mapPath, outputPath;
  double muonWindowLenght;
  double IVChargeThreshold, visibleEnergyThreshold, energyToIDChargeFactor;
  double neutronWindowLenght;
  std::vector<CsHt::Bounds<double>> neutronEnergyBounds;
  CsHt::InnerVetoThreshold<double> candidateInnerVetoThreshold;
  CsHt::Bounds<double> pairTimeCorrelationBounds;
  double pairSpaceCorrelationUpCut;
  CsHt::LightNoiseCutParameters<double> lightNoiseParameters;
  
  bpo::options_description optionDescription("CosmogenicHunter usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("target,t", bpo::value<boost::filesystem::path>(&targetPath)->required(), "Path of the file to process")
  ("map,m", bpo::value<boost::filesystem::path>(&mapPath)->required(), "Path of the binary map of candidates")
  ("output,o", bpo::value<boost::filesystem::path>(&outputPath)->required(), "Output file where to save the candidate trees")
  ("muon-window-lenght", bpo::value<double>(&muonWindowLenght)->required(), "Muon window lenght (ns)")
  ("muon-IV-cut", bpo::value<double>(&IVChargeThreshold)->required(), "Inner Veto charge threshold for muons (DUQ)")
  ("muon-energy-cut", bpo::value<double>(&visibleEnergyThreshold)->required(), "Visible energy threshold for muons (MeV)")
  ("factor-muon-energy-to-ID-charge,f", bpo::value<double>(&energyToIDChargeFactor)->required(), "Conversion factor from muon visible energy to Inner Detector charge to (DUQ/MeV)")
  ("light-noise-cuts", bpo::value<CsHt::LightNoiseCutParameters<double>>(&lightNoiseParameters)->required(), "Light noise rejection parameters (max RMS charge : RMS slope : max charge difference : max charge ratio : max RMS start time)")
  ("candidate-IV-cuts", bpo::value<CsHt::InnerVetoThreshold<double>>(&candidateInnerVetoThreshold)->required(), "Inner Veto rejection parameters (max charge : max number of hit PMTs)")
  ("neutron-window-lenght", bpo::value<double>(&neutronWindowLenght)->required(), "Neutron window lenght (ns)")
  ("neutron-energy-bounds", bpo::fixed_tokens_value<CsHt::Bounds<double>>(&neutronEnergyBounds, 1, 2)->required(), "Variable number of bounds (':' separator) on the neutron's energy (MeV)")
  ("pair-time-bounds", bpo::value<CsHt::Bounds<double>>(&pairTimeCorrelationBounds)->required(), "Bounds(':' separator) on the prompt-delayed time correlation (ns)")
  ("pair-space-up-cut", bpo::value<double>(&pairSpaceCorrelationUpCut)->required(), "Upper cut on the prompt-delayed space correlation (mm)");
  
  bpo::positional_options_description positionalOptions;//to use arguments without "--"
  positionalOptions.add("target", 1);
  
  bpo::variables_map arguments;
  try{
    
    bpo::store(bpo::command_line_parser(argc, argv).options(optionDescription).positional(positionalOptions).run(), arguments);
    
    if(arguments.count("help") || argc == 1){
      
      std::cout<<optionDescription<<std::endl;
      return 0;
      
    }
      
    bpo::notify(arguments);//the arguments are ready to be used
    
  }
  catch(bpo::error& error){
    
    std::cout<<error.what()<<std::endl;
    return 1;
    
  }
  catch(std::invalid_argument& error){
    
    std::cout<<"Error: "<<error.what()<<std::endl;
    return 1;
    
  }
  
  if(!boost::filesystem::is_regular_file(mapPath)){
    
    std::cout<<"Error: "<<mapPath<<" is not a regular file"<<std::endl;
    return 1;
    
  }
  else{
    
    TFile* targetFile = TFile::Open(targetPath.c_str());
    unsigned runNumber = CsHt::Utility::getRunNumber(targetPath.stem().string());
    
    if(targetFile == nullptr){
      
      std::cout<<"Error: "<<targetPath<<" cannot be opened"<<std::endl;
      return 1;
      
    }
    else if(runNumber == 0){
      
      std::cout<<"Error: cannot deduce the run number from "<<targetPath<<std::endl;
      return 1;
      
    }
    else{
    
      CsHt::CandidateMapReader mapReader;
      mapReader.Read(mapPath);
      std::vector<unsigned> candidateIdentifiers;

      try{
	
	candidateIdentifiers =  mapReader.getCandidateIdentifiers(runNumber);
	
      }
      catch(std::out_of_range& error){
	
	std::cout<<"Error: Run "<<runNumber<< " is not in the map of candidates"<<std::endl;
	return 1;
	
      }

      CsHt::EntrySorter<double> entrySorter;//the cuts are tested in the order in which they are passed
      
      try{
	
	entrySorter.emplaceCut(std::make_unique<CsHt::MuonCuts<double>> (CsHt::Flavour::Muon, IVChargeThreshold, visibleEnergyThreshold,  energyToIDChargeFactor));
	entrySorter.emplaceCut(std::make_unique<CsHt::LightNoiseCuts<double>>(CsHt::Flavour::LightNoise, lightNoiseParameters));
	entrySorter.emplaceCut(std::make_unique<CsHt::CandidateCuts<double>>(CsHt::Flavour::Candidate, candidateInnerVetoThreshold, muonWindowLenght, candidateIdentifiers));
	entrySorter.emplaceCut(std::make_unique<CsHt::NeutronCuts<double>>(CsHt::Flavour::Neutron, neutronEnergyBounds));
	
      }
      catch(std::invalid_argument& error){
	
	std::cout<<"Error: "<<error.what()<<std::endl;
	return 1;
	
      }

      CsHt::PairSeeker<float> pairSeeker(pairTimeCorrelationBounds, pairSpaceCorrelationUpCut);
      CsHt::hunt<float, float>(targetFile, outputPath, entrySorter, pairSeeker, muonWindowLenght, neutronWindowLenght);
      
    }
    
  }
  
}
