#include "Muon.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Muon& muon){
  
  muon.print(output, 0);
  return output;
  
}

namespace CosmogenicHunter{
  
  Muon::Muon(double triggerTime, float vetoCharge, float visibleEnergy, unsigned identifier, Segment<float> track, float detectorCharge)
  :Event(triggerTime, vetoCharge, visibleEnergy, identifier), track(std::move(track)), detectorCharge(detectorCharge){
    
  }
  
  const Segment<float>& Muon::getTrack() const{
    
    return track;

  }
  
  float Muon::getDetectorCharge() const{
    
    return detectorCharge;

  }
  
  void Muon::print(std::ostream& output, unsigned outputOffset) const{
    
    Event::print(output, outputOffset);//print the base class
    output<<"\n"<<std::setw(outputOffset)<<std::left<<" "<<std::setw(12)<<std::left<<"Track"<<": "<<track
      <<"\n"<<std::setw(outputOffset)<<std::left<<" "<<std::setw(12)<<std::left<<"ID Charge"<<": "<<std::setw(6)<<std::left<<detectorCharge;

  }

}