#ifndef INFO_ACCESSOR_H
#define INFO_ACCESSOR_H

#include "TTree.h"
#include "Entry.hpp"
#include "Segment.hpp"
#include "ChargeInformation.hpp"

namespace CosmogenicHunter{

  class InfoAccessor {
    
    TTree* tree;//not owned by InfoAccessor
    unsigned currentIndex;
    double IVCharge[3];
    double IDCharge[3];
    Entry<double> entry;//the actual TTree is written with double's only
    double recoBAMAVertex[3];
    double trackMuHam[2][3];
    double chargeRMS, chargeDifference, chargeRatio, startTimeRMS;
    double reconstructionGoodness;
    void updateEntry();//set entry members to the C-array values
    
  public:
    explicit InfoAccessor(TTree* tree);//unfortunately the ROOT reading methods modify the state of TTree
    InfoAccessor(const InfoAccessor& other) = delete;
    InfoAccessor(InfoAccessor&& other) = default;
    InfoAccessor& operator = (const InfoAccessor& other) = delete;
    InfoAccessor& operator = (InfoAccessor&& other) = default;
    virtual ~InfoAccessor() = default;
    unsigned getCurrentIndex() const;
    const Entry<double>& getEntry() const;
    template <class T>
    Segment<T> getMuonTrack() const;
    template <class T>
    Point<T> getPosition() const;
    template <class T>
    T getReconstructionGoodness() const;
    template <class T>
    ChargeInformation<T> getChargeInformation() const;
    bool loadInfo();//write all infos from the tree into the data members, return false at the tree's end
    
  };
  
  std::ostream& operator<<(std::ostream& output, const InfoAccessor& infoAccessor);


  template <class T>
  Segment<T> InfoAccessor::getMuonTrack() const{
    
    Point<T> entryPoint(trackMuHam[0][0], trackMuHam[0][1], trackMuHam[0][2]);
    Point<T> exitPoint(trackMuHam[1][0], trackMuHam[1][1], trackMuHam[1][2]);
	
    return Segment<T> (entryPoint, exitPoint);

  }
  
  template <class T>
  Point<T> InfoAccessor::getPosition() const{
    
    return Point<T> (recoBAMAVertex[0], recoBAMAVertex[1], recoBAMAVertex[2]);

  }
  
  template <class T>
  T InfoAccessor::getReconstructionGoodness() const{
    
    return reconstructionGoodness;
    
  }
  
  template <class T>
  ChargeInformation<T> InfoAccessor::getChargeInformation() const{
    
    
    return ChargeInformation<T> (chargeRMS, chargeDifference, chargeRatio, startTimeRMS);
    
  }
  
}


#endif