#include "Flavour.hpp"

std::map <Flavour, std::string> flavourMap = {{Flavour::Muon, "Muon"}, {Flavour::Neutron, "Neutron"}, {Flavour::Candidate, "Candidate"}, {Flavour::Other, "Other"}};

std::ostream& operator<<(std::ostream& output, Flavour flavour){
  
  output<<flavourMap[flavour];
  return output;

}
