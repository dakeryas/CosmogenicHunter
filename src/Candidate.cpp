#include "Candidate.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Candidate& candidate){
  
  candidate.print(output);//print the base class
  output<<std::setw(15)<<std::left<<"\nPosition"<<": "<<candidate.getPosition()
    <<std::setw(15)<<std::left<<"\nGoodness"<<": "<<candidate.getReconstructionGoodness();
  return output;
  
}

namespace CosmogenicHunter{

  Candidate::Candidate(Event event, Point<float> position, float reconstructionGoodness):Event(event), position(position),reconstructionGoodness(reconstructionGoodness){
    
  }
  
  Candidate::Candidate(double triggerTime, float visibleEnergy, unsigned identifier, Point<float> position, float reconstructionGoodness)
  :Candidate(Event(triggerTime, visibleEnergy, identifier), position, reconstructionGoodness){
    
  }

  const Point<float>& Candidate::getPosition() const{
    
    return position;

  }
  
  float Candidate::getReconstructionGoodness() const{
    
    return reconstructionGoodness;
    
  }

}