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
    
  public:
    Candidate() = default;
    Candidate(Event event, Point<float> position, float reconstructionGoodness, ChargeInformation<float> chargeInformation);
    const Point<float>& getPosition() const;
    float getReconstructionGoodness() const;
    const ChargeInformation<float>& getChargeInformation() const;
    void print(std::ostream& output, unsigned outputOffset) const;
    
  };

}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Candidate& candidate);

#endif