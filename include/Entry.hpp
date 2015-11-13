#ifndef ENTRY_H
#define ENTRY_H

#include <iomanip>

namespace CosmogenicHunter{
  
  template <class T>
  struct Entry{//public for ROOT TTree's branches address
    
    double triggerTime;
    T IVCharge;
    T IDCharge;
    T energy;
    unsigned identifier;
    Entry() = default;
    Entry(double triggerTime, T IVCharge, T IDCharge, T energy, unsigned identifier);
    
  };
  
  template <class T>
  Entry<T>::Entry(double triggerTime, T IVCharge, T IDCharge, T energy, unsigned identifier)
  :triggerTime(triggerTime),IVCharge(IVCharge),IDCharge(IDCharge),energy(energy),identifier(identifier){
      
  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const Entry<T>& entry){
      
    output<<std::setw(12)<<std::left<<entry.triggerTime<<" | "
      <<std::setw(10)<<std::left<<entry.IVCharge<<" | "
      <<std::setw(10)<<std::left<<entry.IDCharge<<" | "
      <<std::setw(8)<<std::left<<entry.energy<<" | "
      <<std::setw(8)<<std::left<<entry.identifier;
    return output;
      
  };
  
}

#endif