#ifndef COSMOGENIC_HUNTER_MUON_CUTS_H
#define COSMOGENIC_HUNTER_MUON_CUTS_H

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
    MuonCuts(Flavour flavour, T IVChargeThreshold, T energyThreshold, T energyToIDChargeFactor);
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
    std::unique_ptr<Cuts<T>> clone() const;
    void print(std::ostream& output) const;
    
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
  MuonCuts<T>::MuonCuts(Flavour flavour, T IVChargeThreshold, T energyThreshold,  T energyToIDChargeFactor)
  :Cuts<T>(flavour),IVChargeThreshold(IVChargeThreshold),energyThreshold(energyThreshold),energyToIDChargeFactor(energyToIDChargeFactor),IDChargeThreshold(energyThreshold * energyToIDChargeFactor), IDChargeToEnergyFactor(1/energyToIDChargeFactor){
    
    if(IVChargeThreshold < 0 || energyThreshold < 0 || energyToIDChargeFactor  < 0) throw std::invalid_argument("Invalid muon cuts parameters.");
    
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
    
    if(IVChargeThreshold > 0) this->IVChargeThreshold = IVChargeThreshold;

  }
  
  template <class T>
  void MuonCuts<T>::setEnergyThreshold(T energyThreshold){

    if(energyThreshold > 0){
      
      this->energyThreshold = energyThreshold;
      updateIDChargeThreshold();
      
    }

  }
  
  template <class T>
  void MuonCuts<T>::setEnergyToIDChargeFactor(T energyToIDChargeFactor){

    if(energyToIDChargeFactor > 0){
      
      this->energyToIDChargeFactor = energyToIDChargeFactor;
      updateIDChargeThreshold();
      
    }

  }
  
  template <class T>
  void MuonCuts<T>::setIDChargeThreshold(T IDChargeThreshold){

    if(IDChargeThreshold > 0){
      
      this->IDChargeThreshold = IDChargeThreshold;
      updateEnergyThreshold();
      
    }
    
  }
  
  template <class T>
  void MuonCuts<T>::setIDChargeToEnergyFactor(T IDChargeToEnergyFactor){

    if(IDChargeToEnergyFactor > 0){
      
      this->IDChargeToEnergyFactor = IDChargeToEnergyFactor;
      updateEnergyThreshold();
      
    }

  }
  
  template <class T>
  bool MuonCuts<T>::accept(const Entry<T>& entry) const{

    return entry.innerVetoData.charge > IVChargeThreshold && ( entry.energy > energyThreshold || entry.IDCharge > IDChargeThreshold);

  }
  
  template <class T>
  T MuonCuts<T>::getEnergy(T IDCharge) const{

    return IDCharge * IDChargeToEnergyFactor;

  }
  
  template <class T>
  T MuonCuts<T>::getIDCharge(T energy) const{

    return energy * energyToIDChargeFactor;

  }
  
  template <class T>
  std::unique_ptr<Cuts<T>> MuonCuts<T>::clone() const{

    return std::make_unique<MuonCuts<T>>(*this);

  }
  
  template <class T>
  void MuonCuts<T>::print(std::ostream& output) const{

    Cuts<T>::print(output);
    
    auto formerPrecision = output.precision();
    output<<std::fixed;
    
    output<<"\n"<<std::setw(26)<<std::left<<"IV Charge threshold"<<": "<<std::setw(8)<<std::right<<std::setprecision(0)<<IVChargeThreshold<<"\n"
      <<std::setw(26)<<std::left<<"Energy threshold"<<": "<<std::setw(8)<<std::right<<energyThreshold<<"\n"
      <<std::setw(26)<<std::left<<"Energy to ID charge factor"<<": "<<std::setw(8)<<std::right<<energyToIDChargeFactor<<"\n"
      <<std::setw(26)<<std::left<<"ID charge threshold"<<": "<<std::setw(8)<<std::right<<IDChargeThreshold<<"\n"
      <<std::setw(26)<<std::left<<"ID charge to energy factor"<<": "<<std::setw(8)<<std::right<<std::setprecision(6)<<IDChargeToEnergyFactor;
      
    output.unsetf(std::ios_base::floatfield);
    output<<std::setprecision(formerPrecision);

  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const MuonCuts<T>& muonCuts){
    
    muonCuts.print(output);
    return output;
    
  }
  
}



#endif