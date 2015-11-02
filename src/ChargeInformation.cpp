#include "ChargeInformation.hpp"

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::ChargeInformation& chargeInformation){
  
  chargeInformation.print(output, 0);
  return output;
  
}

namespace CosmogenicHunter{

  ChargeInformation::ChargeInformation(float RMS, float difference, float ratio, float startTimeRMS):RMS(RMS),difference(difference),ratio(ratio),startTimeRMS(startTimeRMS){
    
  }

  float ChargeInformation::getRMS() const{
    
    return RMS;

  }

  float ChargeInformation::getDifference() const{
    
    return difference;

  }

  float ChargeInformation::getRatio() const{
    
    return ratio;

  }
  
  float ChargeInformation::getStartTimeRMS() const{
    
    return startTimeRMS;

  }

  void ChargeInformation::setRMS(float RMS){
    
    this->RMS = RMS;

  }

  void ChargeInformation::setDifference(float difference){

    this->difference = difference;

  }
  
  void ChargeInformation::setRatio(float ratio){

    this->ratio = ratio;

  }
  
  void ChargeInformation::setStartTimeRMS(float startTimeRMS){

    this->startTimeRMS = startTimeRMS;

  }
  
  void ChargeInformation::print(std::ostream& output, unsigned outputOffset) const{
    
    output<<std::setw(outputOffset)<<std::left<<" "<<std::setw(13)<<std::left<<"RMS"<<": "<<std::setw(5)<<std::left<<RMS<<"\n"
      <<std::setw(outputOffset)<<std::left<<" "<<std::setw(13)<<std::left<<"Difference"<<": "<<std::setw(5)<<std::left<<difference<<"\n"
      <<std::setw(outputOffset)<<std::left<<" "<<std::setw(13)<<std::left<<"Ratio"<<": "<<std::setw(5)<<std::left<<ratio<<"\n"
      <<std::setw(outputOffset)<<std::left<<" "<<std::setw(13)<<std::left<<"StartTime RMS"<<": "<<std::setw(5)<<std::left<<startTimeRMS;

  }

}