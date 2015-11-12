#ifndef CUTS_H
#define CUTS_H

#include <iomanip>
#include "Flavour.hpp"

namespace CosmogenicHunter{

  template <class T>//to accept entries saved with the accuracy of type T
  class Cuts{
    Flavour flavour;
    
  public:
    Cuts() = default;
    Cuts(Flavour flavour);
    Cuts(const Cuts& other) = default;
    Cuts(Cuts&& other) = default;
    Cuts& operator = (const Cuts& other) = default;
    Cuts& operator = (Cuts&& other) = default;
    Flavour getFlavour() const;
    void setFlavour(Flavour flavour);
    virtual ~Cuts() = default;//custom destructor implies to define (even if default-ed) all copy / move / assignement operations
    virtual bool accept(const Entry<T>& entry) const = 0;//accept or reject the entry based on the chosen cuts
    virtual void print(std::ostream& output) const;//needed to act as if 'operator<<' was virtual
    
  };
  
  template <class T>
  Cuts<T>::Cuts(Flavour flavour):flavour(flavour){
    
  }
  
  template <class T>
  Flavour Cuts<T>::getFlavour() const{
    
    return flavour;
    
  }
  
  template <class T>
  void Cuts<T>::setFlavour(Flavour flavour){
    
    this->flavour = flavour;
    
  }
  
  template <class T>
  void Cuts<T>::print(std::ostream& output) const{
    
    output<<"Flavour: "<<flavour;
    
  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const Cuts<T>& cuts){
    
    cuts.print(output);
    return output;
    
  }
  
}

#endif