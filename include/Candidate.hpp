#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "Event.hpp"
#include "Point.hpp"

namespace CosmogenicHunter{

  class Candidate : public Event{
    
    Point<float> position;//RecoBAMA reconstructed positon
    float reconstructionGoodness;//RecoBAMA global fitting functional value
    
  public:
    Candidate() = default;
    Candidate(Event event, Point<float> position, float reconstructionGoodness);
    Candidate(double triggerTime, float visibleEnergy, unsigned identifier, Point<float> position, float reconstructionGoodness);
    const Point<float>& getPosition() const;
    float getReconstructionGoodness() const;
    
  };

}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Candidate& candidate);

#endif