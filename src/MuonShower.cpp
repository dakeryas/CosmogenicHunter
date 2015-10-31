#include "MuonShower.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::MuonShower& muonShower){
  
  output<<std::setw(14)<<std::left<<"Start muon"<<":\n"<<muonShower.getInitiatingMuon()
    <<std::setw(15)<<std::left<<"\nNeutrons"<<":\n"<<muonShower.getNeutronWindow();
  return output;
  
}

namespace CosmogenicHunter{

  MuonShower::MuonShower(Muon initiatingMuon, double maximumDuration):initiatingMuon(initiatingMuon), neutronWindow(initiatingMuon.getTriggerTime(), maximumDuration){
    
  }

  const Muon& MuonShower::getInitiatingMuon() const{
    
    return initiatingMuon;

  }
  
  double MuonShower::getTriggerTime() const{

    return initiatingMuon.getTriggerTime();
    
  }

  const Window<Neutron>& MuonShower::getNeutronWindow() const{
    
    return neutronWindow;

  }
  
  unsigned MuonShower::getNumberOfNeutrons() const{
    
    return neutronWindow.getNumberOfEvents();

  }
  
  void MuonShower::pushBackNeutron(const Neutron& neutron){

    neutronWindow.pushBackEvent(neutron);
    
  }
  
  void MuonShower::pushBackNeutron(Neutron&& neutron){

    neutronWindow.pushBackEvent(neutron);
    
  }

}