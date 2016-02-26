#ifndef COSMOGENIC_INNER_DETECTOR_DATA_H
#define COSMOGENIC_INNER_DETECTOR_DATA_H

#include "PositionData.hpp"

namespace CosmogenicHunter{
  
  template <class T>
  struct InnerDetectorData{
    
    T charge[2];
    T startTime[3];//first is average
    PositionData<T> positionData;
    InnerDetectorData() = default;
    
  };
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const InnerDetectorData<T>& innerDetectorData){
      
    auto formerPrecision = output.precision();
    output<<std::fixed;
    
    output<<std::setprecision(0)<<std::setw(9)<<std::right<<innerDetectorData.charge[2]<<" | "
      <<std::setw(3)<<std::right<<innerDetectorData.startTime[0]<<" | "
      <<innerDetectorData.positionData;
    
    output<<std::setprecision(formerPrecision);
    return output;
    
  };
  
}

#endif
