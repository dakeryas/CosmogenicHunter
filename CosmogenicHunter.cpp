#include <iostream>
#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"
#include "DCCalib-TypeDef.hh"
#include "Muon.hpp"
#include "Neutron.hpp"
#include "Candidate.hpp"
#include "Shower.hpp"

namespace CsHt = CosmogenicHunter;
namespace bpo = boost::program_options;
using MuonShower = CsHt::Shower<CsHt::Muon, CsHt::Neutron>;

namespace CosmogenicHunter {

  struct MuonDefinition{
    
    float IVChargeThreshold, energyToIDChargeFactor, visibleEnergyThreshold;
    float getIDChargeThreshold() const{ //to be used for mini data only
      
      return visibleEnergyThreshold * energyToIDChargeFactor;
      
    }
    
  };

}

void hunt(unsigned runNumber, const boost::filesystem::path& targetPath, const boost::filesystem::path& outputPath, const CsHt::MuonDefinition& muonDefinition){
  
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

{  
  std::ofstream outputStream(outputPath.string(), std::ios::binary);
  cereal::BinaryOutputArchive outputArchive(outputStream);

  while(energyDeposit.Next()){
    
    globalInfo = energyDeposit.GetGlobalInfo();
    double triggerTime = globalInfo->GetTrigTime();
    double numberOfPhotoElectrons = globalInfo->GetCaloPEID(DC::kCaloPEDefaultDC);
    unsigned identifier = globalInfo->GetTriggerID();
    
    if(numberOfPhotoElectrons > 0){
    
      recoBAMAInfo = energyDeposit.GetRecoBAMAInfo();
      CsHt::Point<float> position(recoBAMAInfo->GetRecoX()[0], recoBAMAInfo->GetRecoX()[1], recoBAMAInfo->GetRecoX()[2]);
      float energy = Calib::GetME(energyDeposit.GetVldContext())->EvisID(numberOfPhotoElectrons, globalInfo->GetNGoodChID(), position.getR(), position.getZ(), DCSimFlag::kDATA, DC::kESv10);
      float chargeIV = globalInfo->GetChargeIV(DC::kCharge_AlgoMiniDATA);//we are looking for muons, so compare them with the mini data algorithm
      
      if(energy > muonDefinition.visibleEnergyThreshold && chargeIV > muonDefinition.IVChargeThreshold){
	
	float chargeID = globalInfo->GetChargeID(DC::kCharge_AlgoMiniDATA);
	
	recoMuHamInfo = energyDeposit.GetRecoMuHamIDInfo();
	CsHt::Point<float> entryPoint(recoMuHamInfo->GetEntryID()[0], recoMuHamInfo->GetEntryID()[1], recoMuHamInfo->GetEntryID()[2]);
	CsHt::Point<float> exitPoint(recoMuHamInfo->GetExitID()[0], recoMuHamInfo->GetExitID()[1], recoMuHamInfo->GetExitID()[2]);
	CsHt::Segment<float> track(entryPoint, exitPoint);
	
	CsHt::Muon muon(triggerTime, energy, identifier, chargeID, chargeIV, track);
	outputArchive(muon);
      
      }
      
    }
    else if(globalInfo->HitIV(DC::kIVMuon)){
      
      float chargeID = globalInfo->GetChargeID(DC::kCharge_AlgoMiniDATA);
      float chargeIV = globalInfo->GetChargeIV(DC::kCharge_AlgoMiniDATA);
      
      recoMuHamInfo = energyDeposit.GetRecoMuHamIDInfo();
      CsHt::Point<float> entryPoint(recoMuHamInfo->GetEntryID()[0], recoMuHamInfo->GetEntryID()[1], recoMuHamInfo->GetEntryID()[2]);
      CsHt::Point<float> exitPoint(recoMuHamInfo->GetExitID()[0], recoMuHamInfo->GetExitID()[1], recoMuHamInfo->GetExitID()[2]);
      CsHt::Segment<float> track(entryPoint, exitPoint);

      CsHt::Muon muon(triggerTime, chargeID / muonDefinition.energyToIDChargeFactor, identifier, chargeIV, chargeID, track);
      if(entryPoint != CsHt::Point<float>(0,0,0) && chargeID > muonDefinition.getIDChargeThreshold()) outputArchive(muon);
      
    }
    
  }

}
  
  CsHt::Muon candidateInput;
  std::ifstream inputStream(outputPath.string(), std::ios::binary);
  cereal::BinaryInputArchive inputArchive(inputStream);
  
  unsigned inputCounter{};
  while(true){
    
    try{
      
      inputArchive(candidateInput);
      ++inputCounter;
      
    }
    catch(cereal::Exception& e){
      
      break;
      
    }
    
  }
  std::cout<<"Read "<<inputCounter<<" events"<<std::endl;
  
}

int main(int argc, char* argv[]){
  
  unsigned runNumber;
  boost::filesystem::path targetPath, outputPath;
  CsHt::MuonDefinition muonDefinition;
  
  bpo::options_description optionDescription("CosmogenicHunter usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("run,r", bpo::value<unsigned>(&runNumber)->required(), "Run number of the CT file to process")
  ("target,t", bpo::value<boost::filesystem::path>(&targetPath)->required(), "Directory of the data file")
  ("output,o", bpo::value<boost::filesystem::path>(&outputPath)->required(), "Output file where to save the candidate trees")
  ("muon-IV-cut", bpo::value<float>(&muonDefinition.IVChargeThreshold)->required(), "Inner Veto charge threshold for muons (DUQ)")
  ("factor-muon-energy-to-ID-charge,f", bpo::value<float>(&muonDefinition.energyToIDChargeFactor)->required(), "Conversion factor from muon visible energy to Inner Detector charge to (DUQ/MeV)")
  ("muon-energy-cut", bpo::value<float>(&muonDefinition.visibleEnergyThreshold)->required(), "Visible energy threshold for muons (MeV)");

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
  else hunt(runNumber, targetPath, outputPath, muonDefinition);
  
}
