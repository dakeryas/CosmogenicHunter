#include "Event.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Event& event){
  
  event.print(output, 0);//print to output
  return output;
  
}

bool operator==(const CosmogenicHunter::Event& event1, const CosmogenicHunter::Event& event2){

  return event1.isEqualTo(event2);
  
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
  
  void Event::print(std::ostream& output, unsigned outputOffset) const{

    output<<std::setw(outputOffset)<<std::left<<" "<<std::setw(12)<<std::left<<"Trigger time"<<": "<<std::setw(6)<<std::left<<triggerTime
      <<"\n"<<std::setw(outputOffset)<<std::left<<" "<<std::setw(12)<<std::left<<"Energy"<<": "<<std::setw(3)<<std::left<<visibleEnergy
      <<"\n"<<std::setw(outputOffset)<<std::left<<" "<<std::setw(12)<<std::left<<"Identifier"<<": "<<std::setw(8)<<std::left<<identifier;
    
  }
  
  bool Event::isEqualTo(const Event& other) const{

    return identifier == other.identifier;
    
  }

}