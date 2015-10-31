#ifndef MUON_SHOWER_H
#define MUON_SHOWER_H

#include "Muon.hpp"
#include "Neutron.hpp"
#include "Window.hpp"

namespace CosmogenicHunter{

  class MuonShower{
    
    Muon initiatingMuon;//initiatingMuon creating the neutron flux
    Window<Neutron> neutronWindow;
    
  public:
    MuonShower() = default;
    MuonShower(Muon initiatingMuon, double maximumDuration);//opens a window starting at initiatingMuon.getTriggerTime() and lasting 'maximumDuration' to push neutrons
    const Muon& getInitiatingMuon() const;
    double getTriggerTime() const;//returns initiatingMuon.getTriggerTime() 
    const Window<Neutron>& getNeutronWindow() const;
    unsigned getNumberOfNeutrons() const;
    template <class... Args>
    void emplaceNeutron(Args&&... args);
    void pushBackNeutron(const Neutron& neutron);
    void pushBackNeutron(Neutron&& neutron);
    
  };

  template <class... Args>
  void MuonShower::emplaceNeutron(Args&&... args){
    
    neutronWindow.emplaceEvent(std::forward<Args>(args)...);

  }
  
}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::MuonShower& muonShower);

#endif