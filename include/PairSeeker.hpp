#ifndef COSMOGENIC_HUNTER_PAIR_SEEKER_H
#define COSMOGENIC_HUNTER_PAIR_SEEKER_H

#include "Cosmogenic/CandidatePair.hpp"
#include "Bounds.hpp"

namespace CosmogenicHunter{

  template <class T>//to accept entries saved with the accuracy of type T
  class PairSeeker{
    
    Bounds<double> timeBounds;
    T maxDistance;
    bool hasRecentPrompt;
    bool hasRecentDelayed;
    Single<T> prompt;
    Single<T> delayed;
    bool isAdmissibleDelayed(const Single<T>& delayed) const;
    
  public:
    PairSeeker(Bounds<double> timeBounds, T maxDistance);
    void catchPrompt(Single<T> prompt);
    void catchDelayed(const Single<T>& delayed);
    bool caughtDelayed() const;
    CandidatePair<T> getCandidatePair() const;
    void reset();
    
  };
  
  template <class T>
  bool PairSeeker<T>::isAdmissibleDelayed(const Single<T>& delayed) const{
    
    return areTimeCorrelated(prompt, delayed, timeBounds.getLowEdge(), timeBounds.getUpEdge()) && areSpaceCorrelated(prompt, delayed, maxDistance);
    
  }
  
  template <class T>
  PairSeeker<T>::PairSeeker(Bounds<double> timeBounds, T maxDistance):timeBounds(std::move(timeBounds)),maxDistance(maxDistance),hasRecentPrompt(false),hasRecentDelayed(false){
    
  }
  
  template <class T>
  void PairSeeker<T>::catchPrompt(Single<T> prompt){
    
    this->prompt = std::move(prompt);
    hasRecentPrompt = true;
    
  }
  
  template <class T>
  void PairSeeker<T>::catchDelayed(const Single<T>& delayed){
    
    if(hasRecentPrompt && isAdmissibleDelayed(delayed)){
      
      this->delayed = delayed;
      hasRecentDelayed = true;
      
    }
    
  }
  
  template <class T>
  bool PairSeeker<T>::caughtDelayed() const{
    
    return hasRecentDelayed;
    
  }
  
  template <class T>
  CandidatePair<T> PairSeeker<T>::getCandidatePair() const{
    
    return CandidatePair<T>(prompt, delayed);
    
  }
  
  template <class T>
  void PairSeeker<T>::reset(){
    
    hasRecentPrompt = false;
    hasRecentDelayed = false;
    
  }
  
}

#endif