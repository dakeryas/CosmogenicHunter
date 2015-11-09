#ifndef CUTS_H
#define CUTS_H

#include <iomanip>

namespace CosmogenicHunter{

  template <class T>//to accept entries saved with the accuracy of type T
  class Cuts{
    
  public:
    Cuts() = default;
    Cuts(const Cuts& other) = default;
    Cuts(Cuts&& other) = default;
    Cuts& operator = (const Cuts& other) = default;
    Cuts& operator = (Cuts&& other) = default;
    virtual ~Cuts() = default;//custom destructor implies to define (even if default-ed) all copy / move / assignement operations
    virtual bool accept(const Entry<T>& entry) const = 0;//accept or reject the entry based on the chosen cuts
    
  };
  
}

#endif