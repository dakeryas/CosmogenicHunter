#ifndef MUON_H
#define MUON_H

#include "Event.hpp"
#include "Segment.hpp"

namespace CosmogenicHunter{

  class Muon : public Event{
    
    float vetoCharge;
    float detectorCharge;
    Segment<float> track;
    
  public:
    Muon() = default;
    Muon(Event event, float vetoCharge, float detectorCharge, Segment<float> track);
    Muon(double triggerTime, float visibleEnergy, unsigned identifier, float vetoCharge, float detectorCharge, Segment<float> track);
    float getVetoCharge() const;
    float getDetectorCharge() const;
    const Segment<float>& getTrack() const;
    
  };

}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Muon& muon);

#endif