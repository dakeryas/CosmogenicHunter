#ifndef NEUTRON_H
#define NEUTRON_H

#include "Event.hpp"
#include "Point.hpp"

namespace CosmogenicHunter{

  class Neutron : public Event{
    
    Point<float> position;//RecoBAMA reconstructed positon
    
  public:
    Neutron() = default;
    Neutron(Event event, Point<float> position);
    Neutron(double triggerTime, float visibleEnergy, unsigned identifier, Point<float> position);
    const Point<float>& getPosition() const;
    
  };

}

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Neutron& neutron);

#endif