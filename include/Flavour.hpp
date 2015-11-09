#ifndef FLAVOUR_H
#define FLAVOUR_H

#include <map>
#include <iostream>

namespace CosmogenicHunter{

  enum class Flavour{Muon, Neutron, Candidate, Other};
  
}

std::ostream& operator<<(std::ostream& output, CosmogenicHunter::Flavour flavour);

#endif