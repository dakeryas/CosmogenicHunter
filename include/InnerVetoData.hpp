#ifndef COSMOGENIC_INNER_VETO_DATA_H
#define COSMOGENIC_INNER_VETO_DATA_H

#include <iomanip>

namespace CosmogenicHunter{
  
  template <class T>
  struct InnerVetoData{
    
    T charge;
    unsigned short numberOfHitPMTs;
    InnerVetoData() = default;
    
  };
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const InnerVetoData<T>& innerVetoData){
      
    auto formerPrecision = output.precision();
    output<<std::fixed;
    
    output<<std::setprecision(0)<<std::setw(9)<<std::right<<innerVetoData.charge<<" | "
      <<std::setw(3)<<std::right<<innerVetoData.numberOfHitPMTs;
    
    output<<std::setprecision(formerPrecision);
    return output;
    
  };
  
}

#endif