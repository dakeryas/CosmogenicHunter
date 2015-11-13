#include "Flavour.hpp"

namespace CosmogenicHunter{

  std::map <Flavour, std::string> flavourMap = {{Flavour::Muon, "Muon"}, {Flavour::Neutron, "Neutron"}, {Flavour::Candidate, "Candidate"}, {Flavour::Other, "Other"}};
  
  const std::string& toString(Flavour flavour){
    
    return flavourMap[flavour];

  }

  std::ostream& operator<<(std::ostream& output, Flavour flavour){
    
    output<<toString(flavour);
    return output;

  }

}


