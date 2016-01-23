#include "InfoAccessor.hpp"

namespace CosmogenicHunter{

  void InfoAccessor::updateEntry(){
    
    entry.innerVetoData.charge = IVCharge[2];//point to mini data value
    entry.innerVetoData.numberOfHitPMTs = numberOfHitIVPMTs[0];//RecoPulse value
    entry.IDCharge = IDCharge[2];

  }
  
  InfoAccessor::InfoAccessor(TTree* tree):tree(tree),currentIndex(0){
    
    tree->SetBranchStatus("*", false);
    tree->SetBranchStatus("TrigTime", true);
    tree->SetBranchStatus("TriggerID", true);
    tree->SetBranchStatus("ChargeIV", true);
    tree->SetBranchStatus("NhitIV", true);
    tree->SetBranchStatus("ChargeID", true);
    tree->SetBranchStatus("Vtx_BAMA", true);
    tree->SetBranchStatus("EvisID", true);
    tree->SetBranchStatus("QRMS", true);
    tree->SetBranchStatus("Qdiff", true);
    tree->SetBranchStatus("Qratio", true);
    tree->SetBranchStatus("RMSTstart", true);
    tree->SetBranchStatus("Trk_MuHamID", true);
    tree->SetBranchStatus("Vtx_BAMAfuncV", true);
    tree->SetBranchStatus("SMLikelihoodVTX", true);
    tree->SetBranchStatus("SMLikelihoodChimney", true);
    
    tree->SetBranchAddress("TrigTime", &entry.triggerTime);
    tree->SetBranchAddress("TriggerID", &entry.identifier);
    tree->SetBranchAddress("ChargeIV", IVCharge);
    tree->SetBranchAddress("NhitIV", numberOfHitIVPMTs);
    tree->SetBranchAddress("ChargeID", IDCharge);
    tree->SetBranchAddress("Vtx_BAMA", positionData.position);
    tree->SetBranchAddress("EvisID", &entry.energy);
    tree->SetBranchAddress("QRMS", &entry.chargeData.RMS);
    tree->SetBranchAddress("Qdiff", &entry.chargeData.difference);
    tree->SetBranchAddress("Qratio", &entry.chargeData.ratio);
    tree->SetBranchAddress("RMSTstart", &entry.chargeData.startTimeRMS);
    tree->SetBranchAddress("Trk_MuHamID", trackMuHam);
    tree->SetBranchAddress("Vtx_BAMAfuncV", &positionData.inconsistency);
    tree->SetBranchAddress("SMLikelihoodVTX", &pulseShapeData.inconsistency);
    tree->SetBranchAddress("SMLikelihoodChimney", &pulseShapeData.inconsistencyInChimney);
    
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
  
  void InfoAccessor::reset(){
    
    currentIndex = 0;
    
  }
  
  std::ostream& operator<<(std::ostream& output, const InfoAccessor& infoAccessor){
    
    output<<std::setw(6)<<std::left<<"Index"<<": "<<std::setw(10)<<std::left<<infoAccessor.getCurrentIndex()<<"\n"
      <<std::setw(6)<<std::left<<"Entry"<<": "<<infoAccessor.getEntry();
    return output;
    
  }

}
