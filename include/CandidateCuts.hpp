#ifndef CANDIDATE_CUTS_H
#define CANDIDATE_CUTS_H

#include "Cuts.hpp"

namespace CosmogenicHunter{

  template <class T>
  class CandidateCuts: public Cuts<T>{
    
    std::vector<unsigned> candidateIdentifiers;//ID's of the IBD candidates to decide whether the entry is a candidate

  public:
    CandidateCuts() = default;
    CandidateCuts(std::vector<unsigned>);
    const std::vector<unsigned>& getCandidateIdentifiers() const;
    void setCandidateIdentifiers(std::vector<unsigned> candidateIdentifiers);
    bool accept(const Entry<T>& entry) const;
    
  };
  
  template <class T>
  CandidateCuts<T>::CandidateCuts(std::vector<unsigned> candidateIdentifiers)
  :candidateIdentifiers(candidateIdentifiers){
    
  }

  template <class T>
  const std::vector<unsigned>& CandidateCuts<T>::getCandidateIdentifiers() const{
    
    return candidateIdentifiers;

  }
  
  template <class T>
  void CandidateCuts<T>::setCandidateIdentifiers(std::vector<unsigned> candidateIdentifiers){
    
    this->candidateIdentifiers = std::move(candidateIdentifiers);

  }
  
  template <class T>
  bool CandidateCuts<T>::accept(const Entry<T>& entry) const{

    return std::find(candidateIdentifiers.begin(), candidateIdentifiers.end(), entry.identifier) !=  candidateIdentifiers.end();

  }
  
}

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::CandidateCuts<T>& candidateCuts){
  
  for(auto identifier : candidateCuts.getCandidateIdentifiers()) output<<"\n"<<identifier;
  return output;
  
}

#endif