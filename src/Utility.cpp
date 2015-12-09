#include "Utility.hpp"

namespace CosmogenicHunter{

  namespace Utility{
    
    unsigned getRunNumber(const std::string& targetStem){

      unsigned runNumber{};
      std::regex regex("\\.([0-9]{5,7})");
      std::smatch regexMatches;
      if(std::regex_search(targetStem, regexMatches, regex)) runNumber = std::stoul(regexMatches.str(1));
      
      return runNumber;
      
    }
    
  }

}
