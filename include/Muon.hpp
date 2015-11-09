#ifndef MUON_H
#define MUON_H

#include "Event.hpp"
#include "Segment.hpp"

namespace CosmogenicHunter{

  class Muon : public Event{
    
    Segment<float> track;
    float detectorCharge;
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);
    
  public:
    Muon() = default;
    Muon(double triggerTime, float vetoCharge, float visibleEnergy, unsigned identifier, Segment<float> track, float detectorCharge);
    const Segment<float>& getTrack() const;
    float getDetectorCharge() const;
    void print(std::ostream& output, unsigned outputOffset) const;
    
  };
  
  template <class Archive>
  void Muon::serialize(Archive& archive){
    
    archive(cereal::base_class<Event>(this), track, detectorCharge);

  }

}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Muon& muon);

#endif