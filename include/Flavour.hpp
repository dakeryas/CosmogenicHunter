#ifndef FLAVOUR_H
#define FLAVOUR_H

#include <map>
#include <iostream>

enum class Flavour{Muon, Neutron, Candidate, Other};

std::ostream& operator<<(std::ostream& output, Flavour flavour);

#endif