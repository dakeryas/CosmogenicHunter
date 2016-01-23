#ifndef COSMOGENIC_HUNTER_INFO_ACCESSOR_H
#define COSMOGENIC_HUNTER_INFO_ACCESSOR_H

#include "TTree.h"
#include "EntrySorter.hpp"

#include "PulseShapeData.hpp"
#include "Cosmogenic/Muon.hpp"
#include "Cosmogenic/Single.hpp"
#include "Cosmogenic/PulseShapeInformation.hpp"

namespace CosmogenicHunter{

  class InfoAccessor {
    
    TTree* tree;//not owned by InfoAccessor
    unsigned currentIndex;
    
    double IVCharge[3];
    unsigned short numberOfHitIVPMTs[2];
    double IDCharge[3];
    Entry<double> entry;//the actual TTree is written with double's mostly
    double trackMuHam[2][3];
    PulseShapeData<float> pulseShapeData;//CPS variables
    void updateEntry();//set entry members to the C-array values
    
  public:
    explicit InfoAccessor(TTree* tree);//unfortunately the ROOT reading methods modify the state of TTree
    InfoAccessor(const InfoAccessor& other) = default;
    InfoAccessor(InfoAccessor&& other) = default;
    InfoAccessor& operator = (const InfoAccessor& other) = default;
    InfoAccessor& operator = (InfoAccessor&& other) = default;
    virtual ~InfoAccessor() = default;
    unsigned getCurrentIndex() const;
    const Entry<double>& getEntry() const;
    template <class T>
    Flavour getFlavour(const EntrySorter<T>& entrySorter) const;//find current entry flavour using EntrySorter (visitor)
    template <class T>
    Segment<T> getMuonTrack() const;
    template <class T>
    InnerVetoInformation<T> getInnerVetoInformation() const;
    template <class T>
    PositionInformation<T> getPositionInformation() const;
    template <class T>
    ChargeInformation<T> getChargeInformation() const;
    template <class T>
    T getChimneyInconsistencyRatio() const;
    template <class T>
    Muon<T> getAsMuon() const;
    template <class T>
    Single<T> getAsSingle() const;
    
    bool loadInfo();//write all infos from the tree into the data members, return false at the tree's end
    void reset();//return to start index
    
  };
  
  std::ostream& operator<<(std::ostream& output, const InfoAccessor& infoAccessor);

  template <class T>
  Flavour InfoAccessor::getFlavour(const EntrySorter<T>& entrySorter) const{
    
    return entrySorter.getFlavour(entry);

  }

  template <class T>
  Segment<T> InfoAccessor::getMuonTrack() const{
    
    Point<T> entryPoint(trackMuHam[0][0], trackMuHam[0][1], trackMuHam[0][2]);
    Point<T> exitPoint(trackMuHam[1][0], trackMuHam[1][1], trackMuHam[1][2]);
    
    return Segment<T>(std::move(entryPoint), std::move(exitPoint));

  }
  
  template <class T>
  InnerVetoInformation<T> InfoAccessor::getInnerVetoInformation() const{
    
    return InnerVetoInformation<T>(entry.innerVetoData.charge, entry.innerVetoData.numberOfHitPMTs);

  }
  
  template <class T>
  PositionInformation<T> InfoAccessor::getPositionInformation() const{
    
    return PositionInformation<T>(Point<T>(entry.positionData.position[0], entry.positionData.position[1], entry.positionData.position[2]),  entry.positionData.inconsistency);

  }
  
  template <class T>
  ChargeInformation<T> InfoAccessor::getChargeInformation() const{
    
    try{
      
      return ChargeInformation<T>(entry.chargeData.RMS, entry.chargeData.difference, entry.chargeData.ratio, entry.chargeData.startTimeRMS);
      
    }
    catch(std::invalid_argument& error){
     
      std::cerr<<"Error: for event "<<entry.identifier<<": "<<error.what()<<std::endl;
      return ChargeInformation<T>{};
      
    }
    
  }
  
  template <class T>
  T InfoAccessor::getChimneyInconsistencyRatio() const{
    
    try{
      
      return PulseShapeInformation<T>(pulseShapeData.inconsistency, pulseShapeData.inconsistencyInChimney).getChimneyInconsistencyRatio();
      
    }
    catch(std::invalid_argument& error){
     
      std::cerr<<"Error: for event "<<entry.identifier<<": "<<error.what()<<std::endl;
      return std::numeric_limits<T>::lowest();
      
    }

  }
  
  template <class T>
  Muon<T> InfoAccessor::getAsMuon() const{
    
    return Muon<T>(entry.triggerTime, entry.energy, entry.identifier, getMuonTrack<T>(), entry.innerVetoData.charge, entry.IDCharge);

  }
  
  template <class T>
  Single<T> InfoAccessor::getAsSingle() const{
    
    return Single<T>(entry.triggerTime, entry.energy, entry.identifier, getPositionInformation<T>(), getInnerVetoInformation<T>(), getChargeInformation<T>(), getChimneyInconsistencyRatio<T>());

  }
  
}


#endif