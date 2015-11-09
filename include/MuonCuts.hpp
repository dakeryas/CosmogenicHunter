#ifndef MUON_CUTS_H
#define MUON_CUTS_H

#include "Cuts.hpp"

namespace CosmogenicHunter{

  template <class T>
  class MuonCuts: public Cuts<T>{
    
    T IVChargeThreshold;//lower cut on the IV charge
    T energyThreshold;//visible ID energy
    T energyToIDChargeFactor;//conversion from (possibly) MeV to DUQ's
    
    T IDChargeThreshold;//computed from the other members
    T IDChargeToEnergyFactor;//computed from the other members
    void updateEnergyThreshold();
    void updateIDChargeThreshold();

  public:
    MuonCuts() = default;
    MuonCuts(T IVChargeThreshold, T energyThreshold, T energyToIDChargeFactor);
    T getIVChargeThreshold() const;
    T getEnergyToIDChargeFactor() const;
    T getEnergyThreshold() const;
    T getIDChargeThreshold() const;
    T getIDChargeToEnergyFactor() const;
    void setIVChargeThreshold(T IVChargeThreshold);
    void setEnergyToIDChargeFactor(T energyToIDChargeFactor);
    void setEnergyThreshold(T energyThreshold);
    void setIDChargeThreshold(T IDChargeThreshold);
    void setIDChargeToEnergyFactor(T IDChargeToEnergyFactor);
    bool accept(const Entry<T>& entry) const;
    T getEnergy(T IDCharge) const;
    T getIDCharge(T energy) const;
    
  };
  
  template <class T>
  void MuonCuts<T>::updateEnergyThreshold(){
    
    energyThreshold = IDChargeThreshold * IDChargeToEnergyFactor;

  }
  
  template <class T>
  void MuonCuts<T>::updateIDChargeThreshold(){
    
    IDChargeThreshold = energyThreshold * energyToIDChargeFactor;

  }
  
  template <class T>
  MuonCuts<T>::MuonCuts(T IVChargeThreshold, T energyThreshold,  T energyToIDChargeFactor)
  :IVChargeThreshold(IVChargeThreshold),energyThreshold(energyThreshold),energyToIDChargeFactor(energyToIDChargeFactor),IDChargeThreshold(energyThreshold * energyToIDChargeFactor), IDChargeToEnergyFactor(1/energyToIDChargeFactor){
    
  }

  template <class T>
  T MuonCuts<T>::getIVChargeThreshold() const{
    
    return IVChargeThreshold;

  }

  template <class T>
  T MuonCuts<T>::getEnergyThreshold() const{
    
    return energyThreshold;

  }
  
  template <class T>
  T MuonCuts<T>::getEnergyToIDChargeFactor() const{
    
    return energyToIDChargeFactor;

  }
  
  template <class T>
  T MuonCuts<T>::getIDChargeThreshold() const{
    
    return IDChargeThreshold;

  }
  
  template <class T>
  T MuonCuts<T>::getIDChargeToEnergyFactor() const{
    
    return IDChargeToEnergyFactor;

  }

  template <class T>
  void MuonCuts<T>::setIVChargeThreshold(T IVChargeThreshold){
    
    this->IVChargeThreshold = IVChargeThreshold;

  }
  
  template <class T>
  void MuonCuts<T>::setEnergyThreshold(T energyThreshold){

    this->energyThreshold = energyThreshold;
    updateIDChargeThreshold();

  }
  
  template <class T>
  void MuonCuts<T>::setEnergyToIDChargeFactor(T energyToIDChargeFactor){

    this->energyToIDChargeFactor = energyToIDChargeFactor;
    updateIDChargeThreshold();

  }
  
  template <class T>
  void MuonCuts<T>::setIDChargeThreshold(T IDChargeThreshold){

    this->IDChargeThreshold = IDChargeThreshold;
    updateEnergyThreshold();
    
  }
  
  template <class T>
  void MuonCuts<T>::setIDChargeToEnergyFactor(T IDChargeToEnergyFactor){

    this->IDChargeToEnergyFactor = IDChargeToEnergyFactor;
    updateEnergyThreshold();

  }
  
  template <class T>
  bool MuonCuts<T>::accept(const Entry<T>& entry) const{

    return entry.IVCharge > IVChargeThreshold && entry.energy > energyThreshold;

  }
  
  template <class T>
  T MuonCuts<T>::getEnergy(T IDCharge) const{

    return IDCharge * IDChargeToEnergyFactor;

  }
  
  template <class T>
  T MuonCuts<T>::getIDCharge(T energy) const{

    return energy * energyToIDChargeFactor;

  }
  
}

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::MuonCuts<T>& muonCuts){
  
  output<<std::setw(26)<<std::left<<"IV Charge threshold"<<": "<<std::setw(6)<<std::left<<muonCuts.getIVChargeThreshold()<<"\n"
      <<std::setw(26)<<std::left<<"Energy threshold"<<": "<<std::setw(6)<<std::left<<muonCuts.getEnergyThreshold()<<"\n"
      <<std::setw(26)<<std::left<<"Energy to ID charge factor"<<": "<<std::setw(6)<<std::left<<muonCuts.getEnergyToIDChargeFactor()<<"\n"
      <<std::setw(26)<<std::left<<"ID charge threshold"<<": "<<std::setw(6)<<std::left<<muonCuts.getIDChargeThreshold()<<"\n"
      <<std::setw(26)<<std::left<<"ID charge to energy factor"<<": "<<std::setw(6)<<std::left<<muonCuts.getIDChargeToEnergyFactor();
  return output;
  
}

#endif