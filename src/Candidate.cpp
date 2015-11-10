#include "Candidate.hpp"

std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Candidate& candidate){
  
  candidate.print(output, 0);
  return output;
  
}

namespace CosmogenicHunter{
  
  Candidate::Candidate(double triggerTime, float vetoCharge, float visibleEnergy, unsigned identifier, Point<float> position, float reconstructionGoodness, ChargeInformation<float> chargeInformation)
  :Event(triggerTime, vetoCharge, visibleEnergy, identifier), position(std::move(position)),reconstructionGoodness(reconstructionGoodness),chargeInformation(std::move(chargeInformation)){
    
  }

  const Point<float>& Candidate::getPosition() const{
    
    return position;

  }
  
  float Candidate::getReconstructionGoodness() const{
    
    return reconstructionGoodness;
    
  }
  
  const ChargeInformation<float>& Candidate::getChargeInformation() const{
    
    return chargeInformation;
    
  }
  
  void Candidate::print(std::ostream& output, unsigned outputOffset) const{
    
    Event::print(output, outputOffset);//print the base class
    output<<"\n"<<std::setw(outputOffset)<<std::left<<""<<std::setw(12)<<std::left<<"Position"<<": "<<position
      <<"\n"<<std::setw(outputOffset)<<std::left<<""<<std::setw(12)<<std::left<<"Goodness"<<": "<<reconstructionGoodness
      <<"\n"<<std::setw(outputOffset)<<std::left<<""<<std::setw(12)<<std::left<<"Charge"<<":\n";
    chargeInformation.print(output, outputOffset + 3);  

  }

}