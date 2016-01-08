#ifndef COSMOGENIC_HUNTER_LIGHT_NOISE_CUTS_H
#define COSMOGENIC_HUNTER_LIGHT_NOISE_CUTS_H

#include "Cuts.hpp"
#include "Cosmogenic/LightNoiseCutParameters.hpp"

namespace CosmogenicHunter{

  template <class T>
  class LightNoiseCuts: public Cuts<T>{
    
    LightNoiseCutParameters<T> lightNoiseCutParameters;

  public:
    LightNoiseCuts() = default;
    LightNoiseCuts(Flavour flavour, LightNoiseCutParameters<T> lightNoiseCutParameters);
    T getMaxRMS() const;
    T getSlopeRMS() const;
    T getMaxDifference() const;
    T getMaxRatio() const;
    const LightNoiseCutParameters<T>& getLightNoiseCutParameters() const;
    void setLightNoiseCutParameters(LightNoiseCutParameters<T> lightNoiseCutParameters);
    bool tag(const Entry<T>& entry) const;
    std::unique_ptr<Cuts<T>> clone() const;
    void print(std::ostream& output) const;
    
  };
  
  template <class T>
  LightNoiseCuts<T>::LightNoiseCuts(Flavour flavour, LightNoiseCutParameters<T> lightNoiseCutParameters)
  :Cuts<T>(flavour),lightNoiseCutParameters(std::move(lightNoiseCutParameters)){
    
  }

  template <class T>
  const LightNoiseCutParameters<T>& LightNoiseCuts<T>::getLightNoiseCutParameters() const{
    
    return lightNoiseCutParameters;

  }
  
  template <class T>
  void LightNoiseCuts<T>::setLightNoiseCutParameters(LightNoiseCutParameters<T> lightNoiseCutParameters){
    
    this->lightNoiseCutParameters = std::move(lightNoiseCutParameters);

  }
  
  template <class T>
  bool LightNoiseCuts<T>::tag(const Entry<T>& entry) const{

    return lightNoiseCutParameters.tag(entry.chargeData);

  }
  
  template <class T>
  std::unique_ptr<Cuts<T>> LightNoiseCuts<T>::clone() const{

    return std::make_unique<LightNoiseCuts<T>>(*this);

  }
  
  template <class T>
  void LightNoiseCuts<T>::print(std::ostream& output) const{

    Cuts<T>::print(output);
    output<<"\n"<<lightNoiseCutParameters;

  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const LightNoiseCuts<T>& lightNoiseCuts){
    
    lightNoiseCuts.print(output);
    return output;
    
  }
  
}

#endif