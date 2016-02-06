#include "InfoAccessor.hpp"

namespace CosmogenicHunter{

  InfoAccessor::InfoAccessor(TTree* tree):tree(tree),currentIndex(0){
    
    tree->SetBranchStatus("*", false);
    tree->SetBranchStatus("TrigTime", true);
    tree->SetBranchStatus("EvisID", true);
    tree->SetBranchStatus("TriggerID", true);
    tree->SetBranchStatus("ChargeIV", true);
    tree->SetBranchStatus("NhitIV", true);
    tree->SetBranchStatus("StartTIV", true);
    tree->SetBranchStatus("Vtx_IV", true);
    tree->SetBranchStatus("ChargeID", true);
    tree->SetBranchStatus("StartTID", true);
    tree->SetBranchStatus("Vtx_BAMA", true);
    tree->SetBranchStatus("Vtx_BAMAfuncV", true);
    tree->SetBranchStatus("QRMS", true);
    tree->SetBranchStatus("Qdiff", true);
    tree->SetBranchStatus("Qratio", true);
    tree->SetBranchStatus("RMSTstart", true);
    tree->SetBranchStatus("Trk_MuHamID", true);
    tree->SetBranchStatus("SMLikelihoodVTX", true);
    tree->SetBranchStatus("SMLikelihoodChimney", true);
    tree->SetBranchStatus("LiHeLike", true);
    
    tree->SetBranchAddress("TrigTime", &entry.triggerTime);
    tree->SetBranchAddress("EvisID", &entry.energy);
    tree->SetBranchAddress("TriggerID", &entry.identifier);
    tree->SetBranchAddress("ChargeIV", entry.innerVetoData.charge);
    tree->SetBranchAddress("NhitIV", entry.innerVetoData.numberOfHitPMTs);
    tree->SetBranchAddress("StartTIV", entry.innerVetoData.startTime);
    tree->SetBranchAddress("Vtx_IV", entry.innerVetoData.position);
    tree->SetBranchAddress("ChargeID", entry.innerDetectorData.charge);
    tree->SetBranchAddress("StartTID", entry.innerDetectorData.startTime);
    tree->SetBranchAddress("Vtx_BAMA", entry.innerDetectorData.positionData.position);
    tree->SetBranchAddress("Vtx_BAMAfuncV", &entry.innerDetectorData.positionData.inconsistency);
    tree->SetBranchAddress("QRMS", &entry.chargeData.RMS);
    tree->SetBranchAddress("Qdiff", &entry.chargeData.difference);
    tree->SetBranchAddress("Qratio", &entry.chargeData.ratio);
    tree->SetBranchAddress("RMSTstart", &entry.chargeData.startTimeRMS);
    tree->SetBranchAddress("Trk_MuHamID", trackMuHam);
    tree->SetBranchAddress("SMLikelihoodVTX", &pulseShapeData.inconsistency);
    tree->SetBranchAddress("SMLikelihoodChimney", &pulseShapeData.inconsistencyInChimney);
    tree->SetBranchAddress("LiHeLike", cosmogenicLikelihood);
    
  }
  
  unsigned InfoAccessor::getCurrentIndex() const{
    
    return currentIndex;

  }

  const Entry<double>& InfoAccessor::getEntry() const{
    
    return entry;

  }
  
  bool InfoAccessor::loadInfo(){
    
    auto readSize = tree->GetEntry(currentIndex);
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
