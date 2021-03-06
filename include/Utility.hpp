#ifndef COSMOGENIC_HUNTER_UTILITY_H
#define COSMOGENIC_HUNTER_UTILITY_H

#include <regex>

namespace CosmogenicHunter{

  namespace Utility{
    
    unsigned getRunNumber(const std::string& targetStem);
    
    template <class T>
    std::string to_string(const T& object) {
      
      std::ostringstream output;
      output<<object;
      return output.str();
      
    }
    
  }

}


#endif