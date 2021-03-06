#ifndef COSMOGENIC_PULSE_SHAPE_DATA_H
#define COSMOGENIC_PULSE_SHAPE_DATA_H

#include <iomanip>

namespace CosmogenicHunter{
  
  template <class T>
  struct PulseShapeData{
    
    T inconsistency;//minus log (pulse shape likelihood at reconstruction position)
    T inconsistencyInChimney;//minus log (pulse shape likelihood in the chimney)
    PulseShapeData();
    
  };
  
  template <class T>
  PulseShapeData<T>::PulseShapeData():inconsistency(1), inconsistencyInChimney(std::numeric_limits<T>::max()){
    
  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const PulseShapeData<T>& pulseShapeData){
      
    auto formerPrecision = output.precision();
    output<<std::fixed;
    
    output<<std::setprecision(2)<<std::setw(3)<<std::right<<pulseShapeData.inconsistency<<" | "
      <<std::setw(3)<<std::right<<pulseShapeData.inconsistencyInChimney;
    
    output<<std::setprecision(formerPrecision);
    return output;
    
  };
  
}

#endif