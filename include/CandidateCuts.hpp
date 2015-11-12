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
    CandidateCuts(Flavour flavour, T IVChargeUpCut, std::vector<unsigned> candidateIdentifiers);
    T getIVChargeUpCut() const;
    const std::vector<unsigned>& getCandidateIdentifiers() const;
    void setIVChargeUpCut(T IVChargeUpCut);
    void setCandidateIdentifiers(std::vector<unsigned> candidateIdentifiers);
    bool accept(const Entry<T>& entry) const;
    void print(std::ostream& output) const;
    
  };
  
  template <class T>
  CandidateCuts<T>::CandidateCuts(Flavour flavour, T IVChargeUpCut, std::vector<unsigned> candidateIdentifiers)
  :Cuts<T>(flavour),IVChargeUpCut(IVChargeUpCut),candidateIdentifiers(candidateIdentifiers){
    
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
  
  template <class T>
  void CandidateCuts<T>::print(std::ostream& output) const{

    Cuts<T>::print(output);
    output<<"\n"<<std::setw(14)<<std::left<<"max IV Charge"<<": "<<std::setw(6)<<std::left<<IVChargeUpCut<<"\n"
      <<std::setw(14)<<std::left<<"Candidate ID's"<<": ";
    for(auto identifier : candidateIdentifiers) output<<"\n"<<identifier;

  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const CandidateCuts<T>& candidateCuts){
    
    candidateCuts.print(output);
    return output;
    
  }
  
}

#endif