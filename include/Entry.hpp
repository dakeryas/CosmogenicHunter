#ifndef COSMOGENIC_HUNTER_ENTRY_H
#define COSMOGENIC_HUNTER_ENTRY_H

#include "Cosmogenic/ChargeData.hpp"

namespace CosmogenicHunter{

  template <class T>
  struct Entry{//public for ROOT TTree's branches address
    
    double triggerTime;
    T IVCharge;
    T IDCharge;
    T energy;
    unsigned identifier;
    ChargeData<T> chargeData;
    Entry() = default;
    
  };
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const Entry<T>& entry){
    
    auto formerPrecision = output.precision();
    output<<std::fixed;
    
    output<<std::setw(12)<<std::right<<std::setprecision(0)<<entry.triggerTime<<" | "
      <<std::setw(9)<<std::right<<entry.IVCharge<<" | "
      <<std::setw(9)<<std::right<<entry.IDCharge<<" | "
      <<std::setw(6)<<std::right<<std::setprecision(2)<<entry.energy<<" | "
      <<std::setw(7)<<std::right<<entry.identifier<<" || "
      <<std::setw(4*7)<<std::setprecision(0)<<entry.chargeData;
      
    output<<std::setprecision(formerPrecision);
    return output;
      
  };
  
}

#endif