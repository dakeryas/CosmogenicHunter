#ifndef WINDOW_H
#define WINDOW_H

#include <iomanip>
#include <queue>
#include <algorithm>
#include "cereal/types/deque.hpp"

namespace CosmogenicHunter{

  template <class T>
  class Window{
    
    double startTime;
    double lenght;
    std::deque<T> events;//class T must implement 'getTriggerTime'
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);
    
  public:
    Window() = default;
    Window(double startTime, double lenght);
    Window(const Window<T>& other) = default;
    Window(Window<T>&& other) = default;
    ~Window() = default;
    double getStartTime() const;
    double getLenght() const;
    unsigned getNumberOfEvents() const;
    typename std::deque<T>::const_iterator begin() const;
    typename std::deque<T>::const_iterator end() const;
    void setStartTime(double startTime);
    void setLenght(double lenght);
    void setEndTime(double endTime);
    bool covers(double triggerTime) const;//check if the trigger is within the time window
    template <class K>
    bool covers(const K& event) const;//check if the event is within the time window (event need not be of the same 'event type' as the ones stored in the window)
    bool isEmpty() const;
    template <class... Args>
    void emplaceEvent(double triggerTime, Args&&... args);//emplace back the event if it is within the window
    template <class BaseClass, class... Args>
    void emplaceEvent(BaseClass eventBase, Args&&... args);//meant for Derived::BaseClass built from a BaseClass that implements 'getTriggerTime'
    void pushBackEvent(const T& event);//push back the event if it is within the window
    void pushBackEvent(T&& event);//'T&&' is not a 'universal reference' since T has been deduced already at the instantation of Window<T>, so 'T&&' can only bind to rvalue references and not lvalues
    void clear();//clear all events
    
  };
  
  template <class T>
  template <class Archive>
  void Window<T>::serialize(Archive& archive){
    
    archive(startTime, lenght, events);

  }
  
  template <class T>
  Window<T>::Window(double startTime, double lenght):startTime(startTime),lenght(std::abs(lenght)){
    
  }

  template <class T>
  double Window<T>::getStartTime() const{
    
    return startTime;

  }

  template <class T>
  double Window<T>::getLenght() const{
    
    return lenght;

  }

  template <class T>
  unsigned Window<T>::getNumberOfEvents() const{
    
    return events.size();

  }

  template <class T>
  typename std::deque<T>::const_iterator Window<T>::begin() const{

    return events.begin();
    
  }

  template <class T>
  typename std::deque<T>::const_iterator Window<T>::end() const{

    return events.end();
    
  }

  template <class T>
  void Window<T>::setStartTime(double startTime){
    
    if(startTime - this->startTime >= lenght) events.clear();
    else if(startTime - this->startTime < lenght) events.erase(events.begin(), std::find_if(events.begin(), events.end(), [&](const auto& event){return event.getTriggerTime() >= startTime;}));
    
    this->startTime = startTime;

  }

  template <class T>
  void Window<T>::setLenght(double lenght){
    
    if(lenght > 0){
    
      if(lenght < this->lenght) events.erase(std::find_if(events.begin(), events.end(), [&](const auto& event){return event.getTriggerTime() >= startTime + lenght;}), events.end());
      this->lenght = lenght;
      
    }

  }
  
  template <class T>
  void Window<T>::setEndTime(double endTime){
    
    setStartTime(endTime - lenght);

  }

  template <class T>
  bool Window<T>::covers(double triggerTime) const{
    
    return triggerTime >= startTime && triggerTime < startTime + lenght;

  }

  template <class T>
  template <class K>
  bool Window<T>::covers(const K& event) const{
    
    return covers(event.getTriggerTime());

  }

  template <class T>
  bool Window<T>::isEmpty() const{
    
    return events.empty();

  }

  template <class T>
  template <class... Args>
  void Window<T>::emplaceEvent(double triggerTime, Args&&... args){
    
    if(covers(triggerTime)) events.emplace_back(triggerTime, std::forward<Args>(args)...);

  }
  
  template <class T>
  template <class BaseClass, class... Args>
  void Window<T>::emplaceEvent(BaseClass eventBase, Args&&... args){
    
    if(covers(eventBase)) events.emplace_back(eventBase, std::forward<Args>(args)...);

  }
  
  template <class T>
  void Window<T>::pushBackEvent(const T& event){
    
    if(covers(event)) events.push_back(event);

  }

  template <class T>
  void Window<T>::pushBackEvent(T&& event){
    
    if(covers(event)) events.push_back(event);

  }

  template <class T>
  void Window<T>::clear(){
    
    events.clear();

  }

}

// Foward declaration of operator<< for Shower otherwise Window cannot print Shower's

namespace CosmogenicHunter{
  
  template <class Initiator, class Follower>
  class Shower;
  
}

template <class Initiator, class Follower>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Shower<Initiator,Follower>& shower);

//Declaration end

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Window<T>& window){
  
  output<<std::setw(12)<<std::left<<"Start time: "<<std::setw(8)<<std::left<<window.getStartTime()<<std::setw(8)<<std::left<<" Lenght: "<<std::setw(8)<<std::left<<window.getLenght()
    <<std::setw(14)<<std::left<<"Number of events: "<<std::setw(8)<<std::left<<window.getNumberOfEvents();
    
  if(!window.isEmpty())
    for(const auto& event : window){
      
      output<<"\n";
      event.print(output, 3);//offset all events by 3 spaces
      
    }
      
  return output;
  
}

#endif