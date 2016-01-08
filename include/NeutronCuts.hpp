#ifndef COSMOGENIC_HUNTER_NEUTRON_CUTS_H
#define COSMOGENIC_HUNTER_NEUTRON_CUTS_H

#include "boost/optional.hpp"
#include "Cuts.hpp"
#include "Cosmogenic/Bounds.hpp"

namespace CosmogenicHunter{

  template <class T>
  class NeutronCuts: public Cuts<T>{
    
    std::vector<Bounds<T>> energyBounds;

  public:
    NeutronCuts() = default;
    NeutronCuts(Flavour flavour, std::vector<Bounds<T>> energyBounds);
    const std::vector<Bounds<T>>& getEnergyBounds() const;
    void setEnergyBounds(std::vector<Bounds<T>> energyBounds);
    bool tag(const Entry<T>& entry) const;
    std::unique_ptr<Cuts<T>> clone() const;
    void print(std::ostream& output) const;
    
  };
  
  template <class T>
  NeutronCuts<T>::NeutronCuts(Flavour flavour, std::vector<Bounds<T>> energyBounds)
  :Cuts<T>(flavour),energyBounds(std::move(energyBounds)){
    
  }

  template <class T>
  const std::vector<Bounds<T>>& NeutronCuts<T>::getEnergyBounds() const{
    
    return energyBounds;

  }
  
  template <class T>
  void NeutronCuts<T>::setEnergyBounds(std::vector<Bounds<T>> energyBounds){
    
    this->energyBounds = std::move(energyBounds);

  }
  
  template <class T>
  bool NeutronCuts<T>::tag(const Entry<T>& entry) const{

    for(const auto& energyBound : energyBounds) if(energyBound.contains(entry.energy)) return true;
    return false;

  }
  
  template <class T>
  std::unique_ptr<Cuts<T>> NeutronCuts<T>::clone() const{

    return std::make_unique<NeutronCuts<T>>(*this);

  }
  
  template <class T>
  void NeutronCuts<T>::print(std::ostream& output) const{

    Cuts<T>::print(output);
    output<<"\n"<<std::setw(12)<<std::left<<"Energy bounds"<<":\n";
    for(auto it = energyBounds.begin(); it != energyBounds.end() - 1; ++it) output<<*it<<"\n";
    output<<(*(energyBounds.end() - 1));

  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const NeutronCuts<T>& neutronCuts){
    
    neutronCuts.print(output);
    return output;
    
  }
  
}

#endif