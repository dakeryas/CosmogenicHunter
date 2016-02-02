#ifndef COSMOGENIC_HUNTER_ENTRY_H
#define COSMOGENIC_HUNTER_ENTRY_H

#include "InnerDetectorData.hpp"
#include "InnerVetoData.hpp"
#include "ChargeData.hpp"

namespace CosmogenicHunter{

  template <class T>
  struct Entry{//public for ROOT TTree's branch addresses
    
    double triggerTime;
    T energy;
    unsigned identifier;
    InnerVetoData<T> innerVetoData;
    InnerDetectorData<T> innerDetectorData;
    ChargeData<T> chargeData;
    Entry() = default;
    
  };
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const Entry<T>& entry){
    
    auto formerPrecision = output.precision();
    output<<std::fixed;
    
    output<<std::setw(13)<<std::right<<std::setprecision(0)<<entry.triggerTime<<" || "
      <<entry.innerVetoData<<" || "
      <<entry.innerDetectorData<<" || "
      <<std::setw(6)<<std::right<<std::setprecision(2)<<entry.energy<<" | "
      <<std::setw(7)<<std::right<<entry.identifier<<" || "
      <<entry.chargeData;
      
    output<<std::setprecision(formerPrecision);
    return output;
      
  };
  
}

#endif