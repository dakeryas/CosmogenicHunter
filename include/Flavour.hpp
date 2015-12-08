#ifndef COSMOGENIC_HUNTER_FLAVOUR_H
#define COSMOGENIC_HUNTER_FLAVOUR_H

#include <map>
#include <iostream>

namespace CosmogenicHunter{

  enum class Flavour : char {Muon, LightNoise, Neutron, Candidate, Other};
  const std::string& toString(Flavour flavour);
  std::ostream& operator<<(std::ostream& output, Flavour flavour);
  
}

#endif