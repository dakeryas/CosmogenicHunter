#ifndef ENTRY_SORTER_H
#define ENTRY_SORTER_H

#include "Entry.hpp"
#include "Flavour.hpp"
#include "MuonCuts.hpp"
#include "NeutronCuts.hpp"
#include "CandidateCuts.hpp"

namespace CosmogenicHunter{

  template <class T>
  class EntrySorter{
    
    MuonCuts<T> muonCuts;//cuts to decide whether the entry corresponds to a muon
    NeutronCuts<T> neutronCuts;//cuts to decide whether the entry corresponds to a neutron
    CandidateCuts<T> candidateCuts;
    
  public:
    EntrySorter() = default;
    EntrySorter(MuonCuts<T> muonCuts, NeutronCuts<T> neutronCuts, CandidateCuts<T> candidateCuts);
    const MuonCuts<T>& getMuonCuts() const;
    const NeutronCuts<T>& getNeutronCuts() const;
    const CandidateCuts<T>& getCandidateCuts() const;
    void setMuonCuts(MuonCuts<T> muonCuts);
    void setNeutronCuts(NeutronCuts<T> neutronCuts);
    void setCandidateIdentifiers(CandidateCuts<T> candidateCuts);
    Flavour getFlavour(const Entry<T>& entry) const;
    
  };
  
  template <class T>
  EntrySorter<T>::EntrySorter(MuonCuts<T> muonCuts, NeutronCuts<T> neutronCuts, CandidateCuts<T> candidateCuts)
  :muonCuts(std::move(muonCuts)),neutronCuts(std::move(neutronCuts)),candidateCuts(std::move(candidateCuts)){
    
  }

  template <class T>
  const MuonCuts<T>& EntrySorter<T>::getMuonCuts() const{
    
    return muonCuts;

  }

  template <class T>
  const NeutronCuts<T>& EntrySorter<T>::getNeutronCuts() const{
    
    return neutronCuts;

  }
  
  template <class T>
  const CandidateCuts<T>& EntrySorter<T>::getCandidateCuts() const{
    
    return candidateCuts;
    
  }
  
  template <class T>
  void EntrySorter<T>::setMuonCuts(MuonCuts<T> muonCuts){
    
    this->muonCuts = std::move(muonCuts);

  }
  
  template <class T>
  void EntrySorter<T>::setNeutronCuts(NeutronCuts<T> neutronCuts){

    this->neutronCuts = std::move(neutronCuts);

  }
  
  template <class T>
  void EntrySorter<T>::setCandidateIdentifiers(CandidateCuts<T> candidateCuts){
    
    this->candidateCuts = std::move(candidateCuts);
    
  }
  
  template <class T>
  Flavour EntrySorter<T>::getFlavour(const Entry<T>& entry) const{

    if(muonCuts.accept(entry)) return Flavour::Muon;
    else if(candidateCuts.accept(entry)) return Flavour::Candidate;
    else if(neutronCuts.accept(entry)) return Flavour::Neutron;
    else return Flavour::Other;

  }
  
}

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::EntrySorter<T>& entrySorter){
  
  output<<std::setw(14)<<std::left<<"Muon cuts"<<":\n"<<entrySorter.getMuonCuts()<<"\n"
      <<std::setw(14)<<std::left<<"Neutron cuts"<<":\n"<<entrySorter.getNeutronCuts()<<"\n"
      <<std::setw(14)<<std::left<<"Candidate cuts"<<":\n"<<entrySorter.getCandidateCuts();
  
  
  return output;
  
}

#endif