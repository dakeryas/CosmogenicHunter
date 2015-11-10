#include "Flavour.hpp"

namespace CosmogenicHunter{

  std::map <Flavour, std::string> flavourMap = {{Flavour::Muon, "Muon"}, {Flavour::Neutron, "Neutron"}, {Flavour::Candidate, "Candidate"}, {Flavour::Other, "Other"}};
  std::ostream& operator<<(std::ostream& output, Flavour flavour){
    
    output<<CosmogenicHunter::flavourMap[flavour];
    return output;

  }

}


