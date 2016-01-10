#ifndef COSMOGENIC_HUNTER_CANDIDATE_CUTS_H
#define COSMOGENIC_HUNTER_CANDIDATE_CUTS_H

#include "Cuts.hpp"
#include "Cosmogenic/InnerVetoThreshold.hpp"

namespace CosmogenicHunter{

  template <class T>
  class CandidateCuts: public Cuts<T>{
    
    InnerVetoThreshold<T> innerVetoThreshold;
    double minimumTriggerTime;//do not consider events too close to the begining of the run
    std::vector<unsigned> candidateIdentifiers;//ID's of the IBD candidates to decide whether the entry is a candidate
    
  public:
    CandidateCuts() = default;
    CandidateCuts(Flavour flavour, const InnerVetoThreshold<T>& innerVetoThreshold, double minimumTriggerTime,std::vector<unsigned> candidateIdentifiers);
    const InnerVetoThreshold<T>& getInnerVetoThreshold() const;
    double getMinimumTriggerTime() const;
    const std::vector<unsigned>& getCandidateIdentifiers() const;
    void setInnerVetoThreshold(const InnerVetoThreshold<T>& innerVetoThreshold);
    void setMinimumTriggerTime(double minimumTriggerTime);
    void setCandidateIdentifiers(std::vector<unsigned> candidateIdentifiers);
    bool tag(const Entry<T>& entry) const;
    std::unique_ptr<Cuts<T>> clone() const;
    void print(std::ostream& output) const;
    
  };
  
  template <class T>
  CandidateCuts<T>::CandidateCuts(Flavour flavour, const InnerVetoThreshold<T>& innerVetoThreshold, double minimumTriggerTime, std::vector<unsigned> candidateIdentifiers)
  :Cuts<T>(flavour),innerVetoThreshold(innerVetoThreshold),minimumTriggerTime(minimumTriggerTime),candidateIdentifiers(candidateIdentifiers){
    
    if(minimumTriggerTime < 0) throw std::invalid_argument(std::to_string(minimumTriggerTime)+"ns are not valid candidate cuts");
    
  }
    
  template <class T>
  const InnerVetoThreshold<T>& CandidateCuts<T>::getInnerVetoThreshold() const{
    
    return innerVetoThreshold;

  }
  
  template <class T>
  double CandidateCuts<T>::getMinimumTriggerTime() const{
    
    return minimumTriggerTime;

  }
  
  template <class T>
  const std::vector<unsigned>& CandidateCuts<T>::getCandidateIdentifiers() const{
    
    return candidateIdentifiers;

  }

  template <class T>
  void CandidateCuts<T>::setMinimumTriggerTime(double minimumTriggerTime){
    
    if(minimumTriggerTime > 0) this->minimumTriggerTime = minimumTriggerTime;

  }
  
  template <class T>
  void CandidateCuts<T>::setInnerVetoThreshold(const InnerVetoThreshold<T>& innerVetoThreshold){
    
    if(innerVetoThreshold > 0) this->innerVetoThreshold = innerVetoThreshold;

  }
  
  template <class T>
  void CandidateCuts<T>::setCandidateIdentifiers(std::vector<unsigned> candidateIdentifiers){
    
    this->candidateIdentifiers = std::move(candidateIdentifiers);

  }
  
  template <class T>
  bool CandidateCuts<T>::tag(const Entry<T>& entry) const{

    return !innerVetoThreshold.tag(entry.innerVetoData) && entry.triggerTime > minimumTriggerTime && (std::find(candidateIdentifiers.begin(), candidateIdentifiers.end(), entry.identifier) !=  candidateIdentifiers.end());

  }
  
  template <class T>
  std::unique_ptr<Cuts<T>> CandidateCuts<T>::clone() const{

    return std::make_unique<CandidateCuts<T>>(*this);

  }
  
  template <class T>
  void CandidateCuts<T>::print(std::ostream& output) const{

    Cuts<T>::print(output);
    output<<"\n"<<std::setw(16)<<std::left<<"IV threshold"<<":\n"<<innerVetoThreshold
      <<"\n"<<std::setw(16)<<std::left<<"Min trigger time"<<": "<<std::setw(6)<<std::right<<minimumTriggerTime
      <<"\n"<<std::setw(16)<<std::left<<"Candidate ID's"<<": ";
    for(auto identifier : candidateIdentifiers) output<<"\n"<<identifier;

  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const CandidateCuts<T>& candidateCuts){
    
    candidateCuts.print(output);
    return output;
    
  }
  
}

#endif