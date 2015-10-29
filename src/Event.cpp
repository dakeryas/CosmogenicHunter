#include "Event.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Event& event){
  
  event.print(output);//print to output
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
  
  void Event::print(std::ostream& output) const{

    output<<std::setw(14)<<std::left<<"Trigger time"<<": "<<std::setw(6)<<std::left<<triggerTime
    <<std::setw(15)<<std::left<<"\nVisible energy"<<": "<<std::setw(3)<<std::left<<visibleEnergy
    <<std::setw(15)<<std::left<<"\nIdentifier"<<": "<<std::setw(8)<<std::left<<identifier;
    
  }

}