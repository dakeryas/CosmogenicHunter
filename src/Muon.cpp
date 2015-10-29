#include "Muon.hpp"


std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Muon& muon){
  
  muon.print(output);//print the base class
  output<<std::setw(15)<<std::left<<"\nIV Charge"<<": "<<std::setw(6)<<std::left<<muon.getVetoCharge()
    <<std::setw(15)<<std::left<<"\nID Charge"<<": "<<std::setw(3)<<std::left<<muon.getDetectorCharge()
    <<std::setw(15)<<std::left<<"\nTrack"<<": "<<muon.getTrack();
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

}