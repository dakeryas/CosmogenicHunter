#include "Neutron.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Neutron& neutron){
  
  neutron.print(output, 0);//print the base class
  return output;
  
}

namespace CosmogenicHunter{
  
  Neutron::Neutron(double triggerTime, float vetoCharge, float visibleEnergy, unsigned identifier, Point<float> position)
  :Event(triggerTime, vetoCharge, visibleEnergy, identifier), position(std::move(position)){
    
  }

  const Point<float>& Neutron::getPosition() const{
    
    return position;

  }
  
  void Neutron::print(std::ostream& output, unsigned outputOffset) const{
    
    Event::print(output, outputOffset);//print the base class
    output<<"\n"<<std::setw(outputOffset)<<std::left<<""<<std::setw(12)<<std::left<<"Position"<<": "<<position;

  }

}