#ifndef ENTRY_SORTER_H
#define ENTRY_SORTER_H

#include <vector>
#include <memory>
#include "Entry.hpp"
#include "Cuts.hpp"

namespace CosmogenicHunter{

  template <class T>
  class EntrySorter{
    
    std::vector<std::unique_ptr<Cuts<T>>> cuts;
    
  public:
    EntrySorter() = default;
    EntrySorter(std::vector<std::unique_ptr<Cuts<T>>> cuts);//ordering is important since the cuts are applied as they are stored
    EntrySorter(const EntrySorter<T>& other) = delete;
    EntrySorter(EntrySorter&& other) = default;
    EntrySorter& operator = (const EntrySorter<T>& other) = delete;
    EntrySorter& operator = (EntrySorter&& other) = default;
    virtual ~EntrySorter() = default;//custom destructor implies to define (even if default-ed) all copy / move / assignement operations
    const std::vector<std::unique_ptr<Cuts<T>>>& getCuts() const;
    void emplaceCut(std::unique_ptr<Cuts<T>> cut);
    void clearCuts();
    Flavour getFlavour(const Entry<T>& entry) const;
    
  };
  
  template <class T>
  EntrySorter<T>::EntrySorter(std::vector<std::unique_ptr<Cuts<T>>> cuts)
  :cuts(std::move(cuts)){
    
  }

  template <class T>
  const std::vector<std::unique_ptr<Cuts<T>>>& EntrySorter<T>::getCuts() const{
    
    return cuts;

  }
  
  template <class T>
  void EntrySorter<T>::emplaceCut(std::unique_ptr<Cuts<T>> cut){
    
    cuts.emplace_back(std::move(cut));

  }
  
  template <class T>
  void EntrySorter<T>::clearCuts(){
    
    cuts.clear();

  }
  
  template <class T>
  Flavour EntrySorter<T>::getFlavour(const Entry<T>& entry) const{

    for(const auto& cutPtr : cuts) if(cutPtr->accept(entry)) return cutPtr->getFlavour();
    
    return Flavour::Other;

  }

  template <class T>
  std::ostream& operator<<(std::ostream& output, const EntrySorter<T>& entrySorter){
    
    for(const auto& cutPtr : entrySorter.getCuts()) output<<"\n"<<*cutPtr;
    
    return output;
    
  }
  
}

#endif