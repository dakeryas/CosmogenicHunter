#ifndef NEUTRON_H
#define NEUTRON_H

#include "Event.hpp"
#include "Point.hpp"

namespace CosmogenicHunter{

  class Neutron : public Event{
    
    Point<float> position;//RecoBAMA reconstructed positon
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);
    
  public:
    Neutron() = default;
    Neutron(double triggerTime, float vetoCharge, float visibleEnergy, unsigned identifier, Point<float> position);
    const Point<float>& getPosition() const;
    void print(std::ostream& output, unsigned outputOffset) const;
    
  };
  
  template <class Archive>
  void Neutron::serialize(Archive& archive){
    
    archive(cereal::base_class<Event>(this), position);

  }
  
  std::ostream& operator<<(std::ostream& output, const Neutron& neutron);

}

#endif