#ifndef NEUTRON_CUTS_H
#define NEUTRON_CUTS_H

#include <iomanip>

namespace CosmogenicHunter{

  template <class T>
  class NeutronCuts{
    
    T energyLowCut;//visible ID energy threshold
    T energyUpCut;//maximum value for the visible energy

  public:
    NeutronCuts() = default;
    NeutronCuts(T energyLowCut, T energyUpCut);
    T getEnergyLowCut() const;
    T getEnergyUpCut() const;
    void setEnergyLowCut(T energyLowCut);
    void setEnergyUpCut(T energyUpCut);
    bool accept(T energy) const;
    
  };
  
  template <class T>
  NeutronCuts<T>::NeutronCuts(T energyLowCut, T energyUpCut)
  :energyLowCut(energyLowCut),energyUpCut(energyUpCut){
    
  }

  template <class T>
  T NeutronCuts<T>::getEnergyLowCut() const{
    
    return energyLowCut;

  }

  template <class T>
  T NeutronCuts<T>::getEnergyUpCut() const{
    
    return energyUpCut;

  }
  
  template <class T>
  void NeutronCuts<T>::setEnergyLowCut(T energyLowCut){
    
    this->energyLowCut = energyLowCut;

  }
  
  template <class T>
  void NeutronCuts<T>::setEnergyUpCut(T energyUpCut){

    this->energyUpCut = energyUpCut;

  }
  
  template <class T>
  bool NeutronCuts<T>::accept(T energy) const{

    return energy > energyLowCut && energy < energyUpCut;

  }
  
}

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::NeutronCuts<T>& neutronCuts){
  
  output<<std::setw(16)<<std::left<<"Energy lower cut"<<": "<<std::setw(6)<<std::left<<neutronCuts.getEnergyLowCut()<<"\n"
      <<std::setw(16)<<std::left<<"Energy upper cut"<<": "<<std::setw(6)<<std::left<<neutronCuts.getEnergyUpCut()<<"\n";
  return output;
  
}

#endif