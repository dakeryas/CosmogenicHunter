#ifndef CHARGE_DISTRIBUTION_H
#define CHARGE_DISTRIBUTION_H

#include <iomanip>
#include "cereal/archives/binary.hpp"

namespace CosmogenicHunter{

  class ChargeInformation{
    
    float RMS, difference, ratio, startTimeRMS;
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);
    
  public:
    ChargeInformation() = default;
    ChargeInformation(float RMS, float difference, float ratio, float startTimeRMS);
    ChargeInformation(const ChargeInformation& other) = default;
    ChargeInformation(ChargeInformation&& other) = default;
    ChargeInformation& operator = (const ChargeInformation& other) = default;
    ChargeInformation& operator = (ChargeInformation&& other) = default;
    ~ChargeInformation() = default;
    float getRMS() const;
    float getDifference() const;
    float getRatio() const;
    float getStartTimeRMS() const;
    void setRMS(float RMS);
    void setDifference(float difference);
    void setRatio(float ratio);
    void setStartTimeRMS(float startTimeRMS);
    void print(std::ostream& output, unsigned outputOffset) const;
    
  };
  
  template <class Archive>
  void ChargeInformation::serialize(Archive& archive){
    
    archive(RMS, difference, ratio, startTimeRMS);

  }

}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::ChargeInformation& chargeInformation);

#endif