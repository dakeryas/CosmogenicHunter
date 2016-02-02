#ifndef COSMOGENIC_INNER_VETO_DATA_H
#define COSMOGENIC_INNER_VETO_DATA_H

#include <iomanip>

namespace CosmogenicHunter{
  
  template <class T>
  struct InnerVetoData{
    
    T charge[3];//mini data comes last
    unsigned short numberOfHitPMTs[2];//RecoPulse comes first
    T startTime[3];//first is average
    T position[3];//reconstructed position inside the inner veto
    InnerVetoData() = default;
    
  };
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const InnerVetoData<T>& innerVetoData){
      
    auto formerPrecision = output.precision();
    output<<std::fixed;
    
    output<<std::setprecision(0)<<std::setw(9)<<std::right<<innerVetoData.charge[2]<<" | "
      <<std::setw(3)<<std::right<<innerVetoData.numberOfHitPMTs[0]<<" | "
      <<std::setw(3)<<std::right<<innerVetoData.startTime[0]<<" | "
      <<"("<<std::setw(5)<<std::right<<innerVetoData.position[0]<<", "<<std::setw(5)<<std::right<<innerVetoData.position[1]<<", "<<std::setw(5)<<std::right<<innerVetoData.position[2]<<")";
    
    output<<std::setprecision(formerPrecision);
    return output;
    
  };
  
}

#endif