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
    double getTriggerTime() const;
    float getVisibleEnergy() const;
    unsigned getIdentifier() const;//identifier of the event within the corresponding run
    
  };

}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Event& event);

#endif