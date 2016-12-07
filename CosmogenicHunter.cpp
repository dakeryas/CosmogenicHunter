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
  void hunt(TFile* targetFile, const boost::filesystem::path& outputPath, const EntrySorter<EntryAccuracy>& entrySorter, const PairSeeker<SingleAccuracy>& pairSeeker, double muonWindowLength, double neutronWindowLength){

    TTree* globalInfo = dynamic_cast<TTree*>(targetFile->Get("GI"));
    std::ofstream outputStream(outputPath.string(), std::ios::binary);
    
    Hunter<MuonAccuracy, SingleAccuracy, EntryAccuracy> hunter(entrySorter, pairSeeker, muonWindowLength, neutronWindowLength);
    hunter.chaseAndSave(globalInfo, outputStream);

  }
  
}

int main(int argc, char* argv[]){
 
  boost::filesystem::path targetPath, mapPath, outputPath;
  double muonWindowLength;
  CsHt::MuonDefinition<double> muonDefinition;
  double neutronWindowLength;
  std::vector<CsHt::Bounds<double>> neutronEnergyBounds;
  CsHt::Bounds<double> pairTimeCorrelationBounds;
  double pairSpaceCorrelationUpCut;
  CsHt::LightNoiseVeto<double> lightNoiseVeto;
  
  bpo::options_description optionDescription("CosmogenicHunter usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("target", bpo::value<boost::filesystem::path>(&targetPath)->required(), "Path of the file to process")
  ("map,m", bpo::value<boost::filesystem::path>(&mapPath)->required(), "Path of the binary map of candidates")
  ("output,o", bpo::value<boost::filesystem::path>(&outputPath)->required(), "Output file where to save the candidate trees")
  ("muon-window-length", bpo::value<double>(&muonWindowLength)->required(), "Muon window length [ns]")
  ("muon-definition", bpo::value<CsHt::MuonDefinition<double>>(&muonDefinition)->required(), "Muon definition parameters (Inner Veto charge threshold [DUQ] : visible energy threshold [MeV] : visible energy to Inner Detector charge conversion factor [DUQ/MeV])")
  ("light-noise-cuts", bpo::value<CsHt::LightNoiseVeto<double>>(&lightNoiseVeto)->required(), "Light noise rejection parameters (max RMS charge [DUQ]: RMS slope [DUQ/ns]: max charge difference [DUQ]: max charge ratio : max RMS start time [ns])")
  ("neutron-window-length", bpo::value<double>(&neutronWindowLength)->required(), "Neutron window length [ns]")
  ("neutron-energy-bounds", bpo::fixed_tokens_value<CsHt::Bounds<double>>(&neutronEnergyBounds, 1, 2)->required(), "Variable number of bounds (':' separator) on the neutron's energy [MeV]")
  ("pair-time-bounds", bpo::value<CsHt::Bounds<double>>(&pairTimeCorrelationBounds)->required(), "Bounds(':' separator) on the prompt-delayed time correlation [ns]")
  ("pair-space-up-cut", bpo::value<double>(&pairSpaceCorrelationUpCut)->required(), "Upper cut on the prompt-delayed space correlation [mm]");
  
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
    
    std::cerr<<error.what()<<std::endl;
    return 1;
    
  }
  catch(std::invalid_argument& error){
    
    std::cerr<<"Error: "<<error.what()<<std::endl;
    return 1;
    
  }
  
  if(!boost::filesystem::is_regular_file(mapPath)){
    
    std::cerr<<"Error: "<<mapPath<<" is not a regular file"<<std::endl;
    return 1;
    
  }
  else{
    
    TFile* targetFile = TFile::Open(targetPath.c_str());
    unsigned runNumber = CsHt::Utility::getRunNumber(targetPath.stem().string());
    
    if(targetFile == nullptr){
      
      std::cerr<<"Error: "<<targetPath<<" cannot be opened"<<std::endl;
      return 1;
      
    }
    else if(runNumber == 0){
      
      std::cerr<<"Error: cannot deduce the run number from "<<targetPath<<std::endl;
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
	
	std::cerr<<"Error: Run "<<runNumber<< " is not in the map of candidates"<<std::endl;
	return 1;
	
      }

      CsHt::EntrySorter<double> entrySorter;//the cuts are tested in the order in which they are passed
      
      try{
	
	entrySorter.addCut(std::make_unique<CsHt::MuonCuts<double>> (muonDefinition));
	entrySorter.addCut(std::make_unique<CsHt::LightNoiseCuts<double>>(lightNoiseVeto));
	entrySorter.addCut(std::make_unique<CsHt::CandidateCuts<double>>(muonWindowLength, candidateIdentifiers));
	entrySorter.addCut(std::make_unique<CsHt::NeutronCuts<double>>(neutronEnergyBounds));
	
      }
      catch(std::invalid_argument& error){
	
	std::cerr<<"Error: "<<error.what()<<std::endl;
	return 1;
	
      }

      CsHt::PairSeeker<float> pairSeeker(pairTimeCorrelationBounds, pairSpaceCorrelationUpCut);
      CsHt::hunt<float, float>(targetFile, outputPath, entrySorter, pairSeeker, muonWindowLength, neutronWindowLength);
      
    }
    
  }
  
}
