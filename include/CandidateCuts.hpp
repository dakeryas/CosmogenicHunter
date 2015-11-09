#ifndef CANDIDATE_CUTS_H
#define CANDIDATE_CUTS_H

#include "Cuts.hpp"

namespace CosmogenicHunter{

  template <class T>
  class CandidateCuts: public Cuts<T>{
    
    T IVChargeUpCut;
    std::vector<unsigned> candidateIdentifiers;//ID's of the IBD candidates to decide whether the entry is a candidate
    
  public:
    CandidateCuts() = default;
    CandidateCuts(T IVChargeUpCut, std::vector<unsigned> candidateIdentifiers);
    T getIVChargeUpCut() const;
    const std::vector<unsigned>& getCandidateIdentifiers() const;
    void setIVChargeUpCut(T IVChargeUpCut);
    void setCandidateIdentifiers(std::vector<unsigned> candidateIdentifiers);
    bool accept(const Entry<T>& entry) const;
    
  };
  
  template <class T>
  CandidateCuts<T>::CandidateCuts(T IVChargeUpCut, std::vector<unsigned> candidateIdentifiers)
  :IVChargeUpCut(IVChargeUpCut),candidateIdentifiers(candidateIdentifiers){
    
  }
    
  template <class T>
  T CandidateCuts<T>::getIVChargeUpCut() const{
    
    return IVChargeUpCut;

  }
  
  template <class T>
  const std::vector<unsigned>& CandidateCuts<T>::getCandidateIdentifiers() const{
    
    return candidateIdentifiers;

  }

  template <class T>
  void CandidateCuts<T>::setIVChargeUpCut(T IVChargeUpCut){
    
    this->IVChargeUpCut = IVChargeUpCut;

  }
  
  template <class T>
  void CandidateCuts<T>::setCandidateIdentifiers(std::vector<unsigned> candidateIdentifiers){
    
    this->candidateIdentifiers = std::move(candidateIdentifiers);

  }
  
  template <class T>
  bool CandidateCuts<T>::accept(const Entry<T>& entry) const{

    return entry.IVCharge < IVChargeUpCut && (std::find(candidateIdentifiers.begin(), candidateIdentifiers.end(), entry.identifier) !=  candidateIdentifiers.end());

  }
  
}

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::CandidateCuts<T>& candidateCuts){
  
  output<<std::setw(14)<<std::left<<"max IV Charge"<<": "<<std::setw(6)<<std::left<<candidateCuts.getIVChargeUpCut()<<"\n"
    <<std::setw(14)<<std::left<<"Candidate ID's"<<": ";
  for(auto identifier : candidateCuts.getCandidateIdentifiers()) output<<"\n"<<identifier;
  return output;
  
}

#endif