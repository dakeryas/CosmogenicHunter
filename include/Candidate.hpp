#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "Event.hpp"
#include "Point.hpp"
#include "ChargeInformation.hpp"

namespace CosmogenicHunter{

  class Candidate : public Event{
    
    Point<float> position;//RecoBAMA reconstructed positon
    float reconstructionGoodness;//RecoBAMA global fitting functional value
    ChargeInformation<float> chargeInformation;//QRMS, QDiff, QRatio, startTimeRMS
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);
    
  public:
    Candidate() = default;
    Candidate(double triggerTime, float vetoCharge, float visibleEnergy, unsigned identifier, Point<float> position, float reconstructionGoodness, ChargeInformation<float> chargeInformation);
    const Point<float>& getPosition() const;
    float getReconstructionGoodness() const;
    const ChargeInformation<float>& getChargeInformation() const;
    void print(std::ostream& output, unsigned outputOffset) const;
    
  };
  
  template <class Archive>
  void Candidate::serialize(Archive& archive){
    
    archive(cereal::base_class<Event>(this), position, reconstructionGoodness, chargeInformation);

  }
  std::ostream& operator<<(std::ostream& output, const Candidate& candidate);

}


#endif