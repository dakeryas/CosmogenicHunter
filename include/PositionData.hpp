#ifndef COSMOGENIC_POSITION_DATA_H
#define COSMOGENIC_POSITION_DATA_H

#include <iomanip>

namespace CosmogenicHunter{
  
  template <class T>
  struct PositionData{
    
    T position[3];//RecoBAMA Vertex
    T inconsistency;//RecoBAMA functional value
    PositionData() = default;
    
  };
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const PositionData<T>& positionData){
      
    auto formerPrecision = output.precision();
    output<<std::fixed;
    
    output<<std::setprecision(0)<<"("<<std::setw(4)<<std::right<<positionData.position[0]<<", "<<std::setw(5)<<std::right<<positionData.position[1]<<", "<<std::setw(5)<<std::right<<positionData.position[2]<<")"
      <<" | "
      <<std::setprecision(2)<<std::setw(3)<<std::right<<positionData.inconsistency;
    
    output<<std::setprecision(formerPrecision);
    return output;
    
  };
  
}

#endif