#include "InfoAccessor.hpp"

namespace CosmogenicHunter{

  void InfoAccessor::updateEntry(){
    
    entry.IVCharge = IVCharge[2];//point to mini data value
    entry.IDCharge = IDCharge[2];

  }
  
  InfoAccessor::InfoAccessor(TTree* tree):tree(tree),currentIndex(0){
    
    tree->SetBranchStatus("*", false);
    tree->SetBranchStatus("TrigTime", true);
    tree->SetBranchStatus("TriggerID", true);
    tree->SetBranchStatus("ChargeIV", true);
    tree->SetBranchStatus("ChargeID", true);
    tree->SetBranchStatus("Vtx_BAMA", true);
    tree->SetBranchStatus("EvisID", true);
    tree->SetBranchStatus("Trk_MuHamID", true);
    tree->SetBranchStatus("QRMS", true);
    tree->SetBranchStatus("Qdiff", true);
    tree->SetBranchStatus("Qratio", true);
    tree->SetBranchStatus("RMSTstart", true);
    tree->SetBranchStatus("Vtx_BAMAfuncV", true);
    
    tree->SetBranchAddress("TrigTime", &entry.triggerTime);
    tree->SetBranchAddress("TriggerID", &entry.identifier);
    tree->SetBranchAddress("ChargeIV", IVCharge);
    tree->SetBranchAddress("ChargeID", IDCharge);
    tree->SetBranchAddress("Vtx_BAMA", recoBAMAVertex);
    tree->SetBranchAddress("EvisID", &entry.energy);
    tree->SetBranchAddress("Trk_MuHamID", trackMuHam);
    tree->SetBranchAddress("QRMS", &chargeRMS);
    tree->SetBranchAddress("Qdiff", &chargeDifference);
    tree->SetBranchAddress("Qratio", &chargeRatio);
    tree->SetBranchAddress("RMSTstart", &startTimeRMS);
    tree->SetBranchAddress("Vtx_BAMAfuncV", &reconstructionGoodness);
    
  }
  
  unsigned InfoAccessor::getCurrentIndex() const{
    
    return currentIndex;

  }

  const Entry<double>& InfoAccessor::getEntry() const{
    
    return entry;

  }
  
  bool InfoAccessor::loadInfo(){
    
    auto readSize = tree->GetEntry(currentIndex);
    updateEntry();
    ++currentIndex;
    
    return readSize > 0; //if nothing could be read GetEntry returns 0 or -1 

  }
  
  std::ostream& operator<<(std::ostream& output, const InfoAccessor& infoAccessor){
    
    output<<std::setw(7)<<std::left<<"Index: "<<std::setw(10)<<std::left<<infoAccessor.getCurrentIndex()<<"\n"
      <<std::setw(12)<<std::left<<"TriggerTime"<<" | "
      <<std::setw(10)<<std::left<<"IVCharge"<<" | "
      <<std::setw(10)<<std::left<<"IDCharge"<<" | "
      <<std::setw(8)<<std::left<<"Energy"<<" | "
      <<std::setw(8)<<std::left<<"Identifier\n"
      <<infoAccessor.getEntry();
    return output;
    
  }

}