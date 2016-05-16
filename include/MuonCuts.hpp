#ifndef COSMOGENIC_HUNTER_MUON_CUTS_H
#define COSMOGENIC_HUNTER_MUON_CUTS_H

#include "Cuts.hpp"
#include "Cosmogenic/MuonDefinition.hpp"

namespace CosmogenicHunter{

  template <class T>
  class MuonCuts: public Cuts<T>{
    
    MuonDefinition<T> muonDefinition;

  public:
    MuonCuts() = default;
    MuonCuts(MuonDefinition<T> muonDefinition);
    const MuonDefinition<T>& getMuonDefinition() const;
    void setMuonDefinition(MuonDefinition<T> muonDefinition);
    bool tag(const Entry<T>& entry) const;
    std::unique_ptr<Cuts<T>> clone() const;
    void print(std::ostream& output) const;
    
  };
  
  template <class T>
  MuonCuts<T>::MuonCuts(MuonDefinition<T> muonDefinition)
  :Cuts<T>(Flavour::Muon),muonDefinition(std::move(muonDefinition)){
    
  }

   template <class T>
  const MuonDefinition<T>& MuonCuts<T>::getMuonDefinition() const{
    
    return muonDefinition;

  }
  
  template <class T>
  void MuonCuts<T>::setMuonDefinition(MuonDefinition<T> muonDefinition){
    
    this->muonDefinition = std::move(muonDefinition);

  }
  
  template <class T>
  bool MuonCuts<T>::tag(const Entry<T>& entry) const{

    return muonDefinition.tag(entry);

  }
  
  template <class T>
  std::unique_ptr<Cuts<T>> MuonCuts<T>::clone() const{

    return std::make_unique<MuonCuts<T>>(*this);

  }
  
  template <class T>
  void MuonCuts<T>::print(std::ostream& output) const{

    Cuts<T>::print(output);
    output<<"\n"<<muonDefinition;

  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const MuonCuts<T>& muonCuts){
    
    muonCuts.print(output);
    return output;
    
  }
  
}



#endif