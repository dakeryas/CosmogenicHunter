#include "Muon.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Muon& muon){
  
  muon.print(output, 0);
  return output;
  
}

namespace CosmogenicHunter{

  Muon::Muon(Event event, float vetoCharge, float detectorCharge, Segment<float> track)
  :Event(event), vetoCharge{vetoCharge}, detectorCharge(detectorCharge), track(track){
    
  }
  
  Muon::Muon(double triggerTime, float visibleEnergy, unsigned identifier, float vetoCharge, float detectorCharge, Segment<float> track)
  :Muon(Event(triggerTime, visibleEnergy, identifier), vetoCharge, detectorCharge, track){
    
  }

  float Muon::getVetoCharge() const{
    
    return vetoCharge;

  }

  float Muon::getDetectorCharge() const{
    
    return detectorCharge;

  }

  const Segment<float>& Muon::getTrack() const{
    
    return track;

  }
  
  void Muon::print(std::ostream& output, unsigned outputOffset) const{
    
    Event::print(output, outputOffset);//print the base class
    output<<"\n"<<std::setw(outputOffset)<<std::left<<" "<<std::setw(12)<<std::left<<"IV Charge"<<": "<<std::setw(6)<<std::left<<vetoCharge
      <<"\n"<<std::setw(outputOffset)<<std::left<<" "<<std::setw(12)<<std::left<<"ID Charge"<<": "<<std::setw(3)<<std::left<<detectorCharge
      <<"\n"<<std::setw(outputOffset)<<std::left<<" "<<std::setw(12)<<std::left<<"Track"<<": "<<track;

  }

}