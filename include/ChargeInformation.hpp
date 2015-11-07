#ifndef CHARGE_DISTRIBUTION_H
#define CHARGE_DISTRIBUTION_H

#include <iomanip>
#include "cereal/archives/binary.hpp"

namespace CosmogenicHunter{

  template <class T>
  class ChargeInformation{
    
    T RMS, difference, ratio, startTimeRMS;
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);
    
  public:
    ChargeInformation() = default;
    ChargeInformation(T RMS, T difference, T ratio, T startTimeRMS);
    T getRMS() const;
    T getDifference() const;
    T getRatio() const;
    T getStartTimeRMS() const;
    void setRMS(T RMS);
    void setDifference(T difference);
    void setRatio(T ratio);
    void setStartTimeRMS(T startTimeRMS);
    void print(std::ostream& output, unsigned outputOffset) const;
    
  };
  
  template <class T>
  template <class Archive>
  void ChargeInformation<T>::serialize(Archive& archive){
    
    archive(RMS, difference, ratio, startTimeRMS);

  }
  
  template <class T>
  ChargeInformation<T>::ChargeInformation(T RMS, T difference, T ratio, T startTimeRMS):RMS(RMS),difference(difference),ratio(ratio),startTimeRMS(startTimeRMS){
    
  }

  template <class T>
  T ChargeInformation<T>::getRMS() const{
    
    return RMS;

  }

  template <class T>
  T ChargeInformation<T>::getDifference() const{
    
    return difference;

  }

  template <class T>
  T ChargeInformation<T>::getRatio() const{
    
    return ratio;

  }
  
  template <class T>
  T ChargeInformation<T>::getStartTimeRMS() const{
    
    return startTimeRMS;

  }

  template <class T>
  void ChargeInformation<T>::setRMS(T RMS){
    
    this->RMS = RMS;

  }

  template <class T>
  void ChargeInformation<T>::setDifference(T difference){

    this->difference = difference;

  }
  
  template <class T>
  void ChargeInformation<T>::setRatio(T ratio){

    this->ratio = ratio;

  }
  
  template <class T>
  void ChargeInformation<T>::setStartTimeRMS(T startTimeRMS){

    this->startTimeRMS = startTimeRMS;

  }
  
  template <class T>
  void ChargeInformation<T>::print(std::ostream& output, unsigned outputOffset) const{
    
    output<<std::setw(outputOffset)<<std::left<<" "<<std::setw(13)<<std::left<<"RMS"<<": "<<std::setw(5)<<std::left<<RMS<<"\n"
      <<std::setw(outputOffset)<<std::left<<" "<<std::setw(13)<<std::left<<"Difference"<<": "<<std::setw(5)<<std::left<<difference<<"\n"
      <<std::setw(outputOffset)<<std::left<<" "<<std::setw(13)<<std::left<<"Ratio"<<": "<<std::setw(5)<<std::left<<ratio<<"\n"
      <<std::setw(outputOffset)<<std::left<<" "<<std::setw(13)<<std::left<<"StartTime RMS"<<": "<<std::setw(5)<<std::left<<startTimeRMS;

  }

}

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::ChargeInformation<T>& chargeInformation){
  
  chargeInformation.print(output, 0);
  return output;
  
}

#endif