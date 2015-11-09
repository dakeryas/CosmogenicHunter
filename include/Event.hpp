#ifndef EVENT_H
#define EVENT_H

#include <iomanip>
#include "cereal/archives/binary.hpp"

namespace CosmogenicHunter{

  class Event{
    
    double triggerTime;
    float vetoCharge;//IV charge
    float visibleEnergy;
    unsigned identifier;
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);

  public:
    Event() = default;
    Event(double triggerTime, float vetoCharge, float visibleEnergy, unsigned identifier);
    Event(const Event& other) = default;
    Event(Event&& other) = default;
    Event& operator = (const Event& other) = default;
    Event& operator = (Event&& other) = default;
    virtual ~Event() = default;//custom destructor implies to define (even if default-ed) all copy / move / assignement operations
    double getTriggerTime() const;
    float getVetoCharge() const;
    float getVisibleEnergy() const;
    unsigned getIdentifier() const;//identifier of the event within the corresponding run
    virtual void print(std::ostream& output, unsigned outputOffset) const;//needed to act as if 'operator<<' was virtual
    bool isEqualTo(const Event& other) const;//checks identifiers only
    
  };
  
  template <class Archive>
  void Event::serialize(Archive& archive){
    
    archive(triggerTime, vetoCharge, visibleEnergy, identifier);

  }

}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Event& event);
bool operator == (const CosmogenicHunter::Event& event1, const CosmogenicHunter::Event& event2);

#endif