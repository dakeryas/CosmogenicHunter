#ifndef COSMOGENIC_HUNTER_ENTRY_SORTER_H
#define COSMOGENIC_HUNTER_ENTRY_SORTER_H

#include <vector>
#include "Entry.hpp"
#include "Cuts.hpp"

namespace CosmogenicHunter{

  template <class T>
  class EntrySorter{
    
    std::vector<std::unique_ptr<Cuts<T>>> cuts;
    
  public:
    EntrySorter() = default;
    EntrySorter(std::vector<std::unique_ptr<Cuts<T>>> cuts);//ordering is important since the cuts are applied as they are stored
    EntrySorter(const EntrySorter<T>& other);
    EntrySorter(EntrySorter&& other) = default;
    EntrySorter<T>& operator = (EntrySorter<T> other);
    EntrySorter<T>& operator = (EntrySorter<T>&& other) = default;
    virtual ~EntrySorter() = default;//custom destructor implies to define (even if default-ed) all copy / move / assignement operations
    const std::vector<std::unique_ptr<Cuts<T>>>& getCuts() const;
    void addCut(std::unique_ptr<Cuts<T>> cut);
    void clearCuts();
    Flavour getFlavour(const Entry<T>& entry) const;
    
  };
  
  template <class T>
  EntrySorter<T>::EntrySorter(std::vector<std::unique_ptr<Cuts<T>>> cuts)
  :cuts(std::move(cuts)){

  }
  
  template <class T>
  EntrySorter<T>::EntrySorter(const EntrySorter<T>& other){
    
    for(const auto& cutPtr : other.cuts) cuts.emplace_back(cutPtr->clone());
    
  }

  template <class T>
  EntrySorter<T>& EntrySorter<T>::operator = (EntrySorter<T> other){
    
    std::swap(cuts , other.cuts);
    return *this;
    
  }
  
  template <class T>
  const std::vector<std::unique_ptr<Cuts<T>>>& EntrySorter<T>::getCuts() const{
    
    return cuts;

  }
  
  template <class T>
  void EntrySorter<T>::addCut(std::unique_ptr<Cuts<T>> cut){
    
    cuts.emplace_back(std::move(cut));

  }
  
  template <class T>
  void EntrySorter<T>::clearCuts(){
    
    cuts.clear();

  }
  
  template <class T>
  Flavour EntrySorter<T>::getFlavour(const Entry<T>& entry) const{

    for(const auto& cutPtr : cuts) if(cutPtr->tag(entry)) return cutPtr->getFlavour();
    
    return Flavour::Other;

  }

  template <class T>
  std::ostream& operator<<(std::ostream& output, const EntrySorter<T>& entrySorter){
    
    for(auto it = entrySorter.getCuts().begin(); it != entrySorter.getCuts().end() - 1; ++it) output<<**it<<"\n====================================\n";
    output<<(**(entrySorter.getCuts().end() - 1));
    
    return output;
    
  }
  
}

#endif