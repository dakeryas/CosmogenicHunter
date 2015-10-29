#ifndef EVENT_H
#define EVENT_H

#include <iomanip>

namespace CosmogenicHunter{

  class Event{
    
    double triggerTime;
    float visibleEnergy;
    unsigned identifier;

  public:
    Event() = default;
    Event(double triggerTime, float visibleEnergy, unsigned identifier);
    Event(const Event& other) = default;
    Event(Event&& other) = default;
    Event& operator = (const Event& other) = default;
    Event& operator = (Event&& other) = default;
    virtual ~Event() = default;//custom destructor implies to define (even if default-ed) all copy / move / assignement operations
    double getTriggerTime() const;
    float getVisibleEnergy() const;
    unsigned getIdentifier() const;//identifier of the event within the corresponding run
    virtual void print(std::ostream& output) const;//needed to act as if 'operator<<' was virtual
    
  };

}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Event& event);

#endif