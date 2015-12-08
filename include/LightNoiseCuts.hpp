#ifndef COSMOGENIC_HUNTER_LIGHT_NOISE_CUTS_H
#define COSMOGENIC_HUNTER_LIGHT_NOISE_CUTS_H

#include "Cuts.hpp"

namespace CosmogenicHunter{

  template <class T>
  class LightNoiseCuts: public Cuts<T>{
    
    T maxRMS, slopeRMS, maxDifference, maxRatio;
    double maxStartTimeRMS;

  public:
    LightNoiseCuts() = default;
    LightNoiseCuts(Flavour flavour, T maxRMS, T slopeRMS, T maxDifference, T maxRatio, double maxStartTimeRMS);
    T getMaxRMS() const;
    T getSlopeRMS() const;
    T getMaxDifference() const;
    T getMaxRatio() const;
    double getMaxStartTimeRMS() const;
    void setMaxRMS(T maxRMS);
    void setSlopeRMS(T slopeRMS);
    void setMaxDifference(T maxDifference);
    void setMaxRatio(T maxRatio);
    void setMaxStartTimeRMS(double maxStartTimeRMS);
    bool accept(const Entry<T>& entry) const;
    std::unique_ptr<Cuts<T>> clone() const;
    void print(std::ostream& output) const;
    
  };
  
  template <class T>
  LightNoiseCuts<T>::LightNoiseCuts(Flavour flavour, T maxRMS, T slopeRMS, T maxDifference, T maxRatio, double maxStartTimeRMS)
  :Cuts<T>(flavour),maxRMS(maxRMS),slopeRMS(slopeRMS),maxDifference(maxDifference),maxRatio(maxRatio),maxStartTimeRMS(maxStartTimeRMS){
    
  }

  template <class T>
  T LightNoiseCuts<T>::getMaxRMS() const{
    
    return maxRMS;

  }

  template <class T>
  T LightNoiseCuts<T>::getSlopeRMS() const{
    
    return slopeRMS;

  }
  
  template <class T>
  T LightNoiseCuts<T>::getMaxDifference() const{
    
    return maxDifference;

  }

  template <class T>
  T LightNoiseCuts<T>::getMaxRatio() const{
    
    return maxRatio;

  }
  
  template <class T>
  double LightNoiseCuts<T>::getMaxStartTimeRMS() const{
    
    return maxStartTimeRMS;

  }
  
  template <class T>
  void LightNoiseCuts<T>::setMaxRMS(T maxRMS){
    
    if(maxRMS > 0) this->maxRMS = maxRMS;

  }
  
  template <class T>
  void LightNoiseCuts<T>::setSlopeRMS(T slopeRMS){

    if(slopeRMS > 0) this->slopeRMS = slopeRMS;

  }
  
  template <class T>
  void LightNoiseCuts<T>::setMaxDifference(T maxDifference){
    
    if(maxDifference > 0) this->maxDifference = maxDifference;

  }
  
  template <class T>
  void LightNoiseCuts<T>::setMaxRatio(T maxRatio){

    if(maxRatio > 0) this->maxRatio = maxRatio;

  }
  
  template <class T>
  void LightNoiseCuts<T>::setMaxStartTimeRMS(double maxStartTimeRMS){

    if(maxStartTimeRMS > 0) this->maxStartTimeRMS = maxStartTimeRMS;

  }
  
  template <class T>
  bool LightNoiseCuts<T>::accept(const Entry<T>& entry) const{

    return entry.chargeData.difference > maxDifference || entry.chargeData.ratio > maxRatio || (entry.chargeData.startTimeRMS > maxStartTimeRMS && (entry.chargeData.RMS > (maxRMS - slopeRMS * entry.chargeData.startTimeRMS)));

  }
  
  template <class T>
  std::unique_ptr<Cuts<T>> LightNoiseCuts<T>::clone() const{

    return std::make_unique<LightNoiseCuts<T>>(*this);

  }
  
  template <class T>
  void LightNoiseCuts<T>::print(std::ostream& output) const{

    Cuts<T>::print(output);
    output<<"\n"<<std::setw(14)<<std::left<<"Max RMS"<<": "<<std::setw(6)<<std::right<<maxRMS<<"\n"
      <<std::setw(14)<<std::left<<"Slope RMS"<<": "<<std::setw(6)<<std::right<<slopeRMS<<"\n"
      <<std::setw(14)<<std::left<<"Max Diff"<<": "<<std::setw(6)<<std::right<<maxDifference<<"\n"
      <<std::setw(14)<<std::left<<"Max Ratio"<<": "<<std::setw(6)<<std::right<<maxRatio<<"\n"
      <<std::setw(14)<<std::left<<"Max RMSTstart"<<": "<<std::setw(6)<<std::right<<maxStartTimeRMS;

  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const LightNoiseCuts<T>& lightNoiseCuts){
    
    lightNoiseCuts.print(output);
    return output;
    
  }
  
}

#endif