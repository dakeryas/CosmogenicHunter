#ifndef FLAVOUR_H
#define FLAVOUR_H

#include <map>
#include <iostream>

namespace CosmogenicHunter{

  enum class Flavour : char {Muon, Neutron, Candidate, Other};
  std::ostream& operator<<(std::ostream& output, Flavour flavour);
  
}

#endif