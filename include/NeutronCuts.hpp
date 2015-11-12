#ifndef NEUTRON_CUTS_H
#define NEUTRON_CUTS_H

#include "Cuts.hpp"

namespace CosmogenicHunter{

  template <class T>
  class NeutronCuts: public Cuts<T>{
    
    T energyLowCut;//visible ID energy threshold
    T energyUpCut;//maximum value for the visible energy

  public:
    NeutronCuts() = default;
    NeutronCuts(Flavour flavour, T energyLowCut, T energyUpCut);
    T getEnergyLowCut() const;
    T getEnergyUpCut() const;
    void setEnergyLowCut(T energyLowCut);
    void setEnergyUpCut(T energyUpCut);
    bool accept(const Entry<T>& entry) const;
    void print(std::ostream& output) const;
    
  };
  
  template <class T>
  NeutronCuts<T>::NeutronCuts(Flavour flavour, T energyLowCut, T energyUpCut)
  :Cuts<T>(flavour),energyLowCut(energyLowCut),energyUpCut(energyUpCut){
    
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
  bool NeutronCuts<T>::accept(const Entry<T>& entry) const{

    return entry.energy > energyLowCut && entry.energy < energyUpCut;

  }
  
  template <class T>
  void NeutronCuts<T>::print(std::ostream& output) const{

    Cuts<T>::print(output);
    output<<"\n"<<std::setw(16)<<std::left<<"Energy lower cut"<<": "<<std::setw(6)<<std::left<<energyLowCut<<"\n"
      <<std::setw(16)<<std::left<<"Energy upper cut"<<": "<<std::setw(6)<<std::left<<energyUpCut;

  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const NeutronCuts<T>& neutronCuts){
    
    neutronCuts.print(output);
    return output;
    
  }
  
}

#endif