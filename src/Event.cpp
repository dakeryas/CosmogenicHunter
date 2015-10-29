#include "Event.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Event& event){
  
  output<<std::setw(15)<<std::left<<"Trigger time"<<": "<<std::setw(6)<<std::left<<event.getTriggerTime()
    <<std::setw(16)<<std::left<<"\nVisible energy"<<": "<<std::setw(3)<<std::left<<event.getVisibleEnergy()
    <<std::setw(16)<<std::left<<"\nIdentifier"<<": "<<std::setw(8)<<std::left<<event.getIdentifier();
  return output;
  
}

namespace CosmogenicHunter{

  Event::Event(double triggerTime, float visibleEnergy, unsigned identifier):triggerTime(triggerTime),visibleEnergy(visibleEnergy),identifier(identifier){
    
  }

  double Event::getTriggerTime() const{
    
    return triggerTime;

  }

  float Event::getVisibleEnergy() const{
    
    return visibleEnergy;

  }

  unsigned Event::getIdentifier() const{
    
    return identifier;

  }

}