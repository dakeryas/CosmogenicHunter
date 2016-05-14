#ifndef COSMOGENIC_HUNTER_LIGHT_NOISE_CUTS_H
#define COSMOGENIC_HUNTER_LIGHT_NOISE_CUTS_H

#include "Cuts.hpp"
#include "Cosmogenic/LightNoiseVeto.hpp"

namespace CosmogenicHunter{

  template <class T>
  class LightNoiseCuts: public Cuts<T>{
    
    LightNoiseVeto<T> lightNoiseVeto;

  public:
    LightNoiseCuts() = default;
    LightNoiseCuts(Flavour flavour, LightNoiseVeto<T> lightNoiseVeto);
    const LightNoiseVeto<T>& getLightNoiseVeto() const;
    void setLightNoiseVeto(LightNoiseVeto<T> lightNoiseVeto);
    bool tag(const Entry<T>& entry) const;
    std::unique_ptr<Cuts<T>> clone() const;
    void print(std::ostream& output) const;
    
  };
  
  template <class T>
  LightNoiseCuts<T>::LightNoiseCuts(Flavour flavour, LightNoiseVeto<T> lightNoiseVeto)
  :Cuts<T>(flavour),lightNoiseVeto(std::move(lightNoiseVeto)){
    
  }

  template <class T>
  const LightNoiseVeto<T>& LightNoiseCuts<T>::getLightNoiseVeto() const{
    
    return lightNoiseVeto;

  }
  
  template <class T>
  void LightNoiseCuts<T>::setLightNoiseVeto(LightNoiseVeto<T> lightNoiseVeto){
    
    this->lightNoiseVeto = std::move(lightNoiseVeto);

  }
  
  template <class T>
  bool LightNoiseCuts<T>::tag(const Entry<T>& entry) const{

    return lightNoiseVeto.tag(entry.chargeData);

  }
  
  template <class T>
  std::unique_ptr<Cuts<T>> LightNoiseCuts<T>::clone() const{

    return std::make_unique<LightNoiseCuts<T>>(*this);

  }
  
  template <class T>
  void LightNoiseCuts<T>::print(std::ostream& output) const{

    Cuts<T>::print(output);
    output<<"\n"<<lightNoiseVeto;

  }
  
  template <class T>
  std::ostream& operator<<(std::ostream& output, const LightNoiseCuts<T>& lightNoiseCuts){
    
    lightNoiseCuts.print(output);
    return output;
    
  }
  
}

#endif