#include <iostream>
#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"
#include "DCCalib-TypeDef.hh"
#include "EntrySorter.hpp"
#include "Muon.hpp"
#include "Neutron.hpp"
#include "Candidate.hpp"
#include "Shower.hpp"

namespace CsHt = CosmogenicHunter;
namespace bpo = boost::program_options;
using MuonShower = CsHt::Shower<CsHt::Muon<float>, CsHt::Neutron<float>>;

namespace CosmogenicHunter{

  std::vector<unsigned> getCandidateIdentifiers(const boost::filesystem::path& mapPath, unsigned runNumber){
  
    std::unordered_map<unsigned, std::vector<unsigned>> candidatesMap;
    
    std::ifstream inputStream(mapPath.string(), std::ios::binary);
    cereal::BinaryInputArchive inputArchive(inputStream);
    inputArchive(candidatesMap);
    
    return candidatesMap.at(runNumber);

  }

  template <class T>
  void hunt(unsigned runNumber, const boost::filesystem::path& targetPath, const boost::filesystem::path& outputPath, const EntrySorter<T>& entrySorter, double muonWindowLenght, double neutronWindowLenght){

    Message::SetLevelMSG(DC::kMERROR);
    
    EnDep::SetDirDataINPUT(targetPath.c_str());
    EnDep::SetRunNumber(runNumber);
    
    EnDep energyDeposit;
    energyDeposit.CancelAllInfoCapsule_Tree();
    energyDeposit.UncancelInfoCapsule_Tree(DC::kRunIT);
    energyDeposit.UncancelInfoCapsule_Tree(DC::kGlobalIT);
    energyDeposit.UncancelInfoCapsule_Tree(DC::kRecoBAMAIT);
    energyDeposit.UncancelInfoCapsule_Tree(DC::kRecoMuHamIDIT);
    energyDeposit.RetrieveME();

    const GlobalInfo* globalInfo;
    const RecoBAMAInfo* recoBAMAInfo;
    const RecoMuHamIDInfo* recoMuHamInfo;

    std::ofstream outputStream(outputPath.string(), std::ios::binary);
    cereal::BinaryOutputArchive outputArchive(outputStream);

    Window<MuonShower> muonShowerWindow(0, muonWindowLenght);

    while(energyDeposit.Next()){
      
      globalInfo = energyDeposit.GetGlobalInfo();
      double triggerTime = globalInfo->GetTrigTime();
      double numberOfPhotoElectrons = globalInfo->GetCaloPEID(DC::kCaloPEDefaultDC);
      unsigned identifier = globalInfo->GetTriggerID();
      
      float chargeIV = globalInfo->GetChargeIV(DC::kCharge_AlgoMiniDATA);//we are looking for muons, so compare them with the mini data algorithm
      float chargeID = globalInfo->GetChargeID(DC::kCharge_AlgoMiniDATA);
      
      recoBAMAInfo = energyDeposit.GetRecoBAMAInfo();
      Point<float> position(recoBAMAInfo->GetRecoX()[0], recoBAMAInfo->GetRecoX()[1], recoBAMAInfo->GetRecoX()[2]);
      float energy = Calib::GetME(energyDeposit.GetVldContext())->EvisID(numberOfPhotoElectrons, globalInfo->GetNGoodChID(), position.getR(), position.getZ(), DCSimFlag::kDATA, DC::kESv10);

      Entry<float> entry(chargeIV, chargeID, energy, identifier);
      auto flavour = entrySorter.getFlavour(entry);
      
      muonShowerWindow.setEndTime(triggerTime + 1);

      if(flavour == Flavour::Muon){
	
	recoMuHamInfo = energyDeposit.GetRecoMuHamIDInfo();
	Point<float> entryPoint(recoMuHamInfo->GetEntryID()[0], recoMuHamInfo->GetEntryID()[1], recoMuHamInfo->GetEntryID()[2]);
	Point<float> exitPoint(recoMuHamInfo->GetExitID()[0], recoMuHamInfo->GetExitID()[1], recoMuHamInfo->GetExitID()[2]);
	Segment<float> track(entryPoint, exitPoint);
	
	if(entryPoint != Point<float>(0,0,0)){

	  Muon<float> muon(triggerTime, chargeIV, energy, identifier, track, chargeID);
	  muonShowerWindow.emplaceEvent(muon, neutronWindowLenght);

	}
      
      }
      else if(flavour == Flavour::Candidate && triggerTime > muonWindowLenght) outputArchive(muonShowerWindow);//we cannot save candidate trees too early in the run
      else if(flavour == Flavour::Neutron){
	
	for(auto& muonShower : muonShowerWindow) muonShower.emplaceFollower(triggerTime, chargeIV, energy, identifier, position);
	
      }
      
    }

  }
  
}

int main(int argc, char* argv[]){
 
  unsigned runNumber;
  boost::filesystem::path targetPath, mapPath, outputPath;
  double muonWindowLenght;
  float IVChargeThreshold, visibleEnergyThreshold, energyToIDChargeFactor;
  double neutronWindowLenght;
  std::vector<float> neutronEnergyBounds(2);
  float candidateIVChargeUpCut;
  
  bpo::options_description optionDescription("CosmogenicHunter usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("run,r", bpo::value<unsigned>(&runNumber)->required(), "Run number of the file to process")
  ("target,t", bpo::value<boost::filesystem::path>(&targetPath)->required(), "Directory of the file")
  ("map,m", bpo::value<boost::filesystem::path>(&mapPath)->required(), "Path of the binary map of candidates")
  ("output,o", bpo::value<boost::filesystem::path>(&outputPath)->required(), "Output file where to save the candidate trees")
  ("muon-window-lenght", bpo::value<double>(&muonWindowLenght)->required(), "Muon window lenght (ns)")
  ("muon-IV-cut", bpo::value<float>(&IVChargeThreshold)->required(), "Inner Veto charge threshold for muons (DUQ)")
  ("muon-energy-cut", bpo::value<float>(&visibleEnergyThreshold)->required(), "Visible energy threshold for muons (MeV)")
  ("factor-muon-energy-to-ID-charge,f", bpo::value<float>(&energyToIDChargeFactor)->required(), "Conversion factor from muon visible energy to Inner Detector charge to (DUQ/MeV)")
  ("neutron-window-lenght", bpo::value<double>(&neutronWindowLenght)->required(), "Neutron window lenght (ns)")
  ("neutron-energy-bounds", bpo::value<std::vector<float>>(&neutronEnergyBounds)->multitoken()->required(), "Bounds on the neutron's energy (MeV)")
  ("candidate-IV-up-cut", bpo::value<float>(&candidateIVChargeUpCut)->required(), "Upper cut on the candidate's Inner Veto charge (DUQ)");

  bpo::positional_options_description positionalOptions;//to use arguments without "--"
  positionalOptions.add("run", 1);
  
  bpo::variables_map arguments;
  try{
    
    bpo::store(bpo::command_line_parser(argc, argv).options(optionDescription).positional(positionalOptions).run(), arguments);
    
    if(arguments.count("help")){
      
      std::cout<<optionDescription<<std::endl;
      return 0;
      
    }
      
    bpo::notify(arguments);//the arguments are ready to be used
    
  }
  catch(bpo::error& e){
    
    std::cout<<e.what()<<std::endl;
    return 1;
    
  }
  
  if(!boost::filesystem::is_directory(targetPath)){
      
      std::cout<<"Error: '"<<targetPath<<"' is not a directory"<<std::endl;
      return 1;
      
  }
  else if(!boost::filesystem::is_regular_file(mapPath)){
    
    std::cout<<"Error: '"<<mapPath<<"' is not a regular file"<<std::endl;
    return 1;
    
  }
  else{
    
    std::vector<unsigned> candidateIdentifiers;

    try{
      
      candidateIdentifiers =  CsHt::getCandidateIdentifiers(mapPath, runNumber);
      
    }
    catch(std::out_of_range& e){
      
      std::cout<<"Error: Run "<<runNumber<< " is not in the map of candidates"<<std::endl;
      return 1;
      
    }
    CsHt::MuonCuts<float> muonCuts(CsHt::Flavour::Muon, IVChargeThreshold, visibleEnergyThreshold,  energyToIDChargeFactor);
    CsHt::NeutronCuts<float> neutronCuts(CsHt::Flavour::Neutron,neutronEnergyBounds[0], neutronEnergyBounds[1]);
    CsHt::CandidateCuts<float> candidateCuts(CsHt::Flavour::Candidate, candidateIVChargeUpCut, candidateIdentifiers);
    CsHt::EntrySorter<float> entrySorter(muonCuts, neutronCuts, candidateCuts);
    CsHt::hunt(runNumber, targetPath, outputPath, entrySorter, muonWindowLenght, neutronWindowLenght);
    
  }
  
}
