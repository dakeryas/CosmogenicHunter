#ifndef ENTRY_H
#define ENTRY_H

#include <iomanip>

namespace CosmogenicHunter{
  
  template <class T>
  struct Entry{
    
    T IVCharge;
    T IDCharge;
    T energy;
    unsigned identifier;
    Entry(T IVCharge, T IDCharge, T energy, unsigned identifier):IVCharge(IVCharge),IDCharge(IDCharge),energy(energy),identifier(identifier){}
    
  };
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const Entry<T>& entry){
      
    output<<std::setw(12)<<std::right<<entry.IVCharge<<" | "<<std::setw(12)<<std::right<<entry.IDCharge<<" | "<<std::setw(8)<<std::right<<entry.energy<<" | "<<std::setw(8)<<std::right<<entry.identifier;
    return output;
      
  };
  
}


#endif