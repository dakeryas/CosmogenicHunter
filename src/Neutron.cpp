#include "Neutron.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Neutron& neutron){
  
  neutron.print(output);//print the base class
  output<<std::setw(15)<<std::setw(15)<<std::left<<"\nPosition"<<": "<<neutron.getPosition();
  return output;
  
}

namespace CosmogenicHunter{

  Neutron::Neutron(Event event, Point<float> position):Event(event), position(position){
    
  }
  
  Neutron::Neutron(double triggerTime, float visibleEnergy, unsigned identifier, Point<float> position):Neutron(Event(triggerTime, visibleEnergy, identifier), position){
    
  }

  const Point<float>& Neutron::getPosition() const{
    
    return position;

  }

}