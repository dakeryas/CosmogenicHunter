#ifndef WINDOW_H
#define WINDOW_H

#include <iomanip>
#include <queue>
#include <algorithm>

namespace CosmogenicHunter{

  template <class T>
  class Window{
    
    double startTime;
    double lenght;
    std::deque<T> events;
    
  public:
    Window() = default;
    Window(double startTime, double lenght);
    double getStartTime() const;
    double getLenght() const;
    unsigned getNumberOfEvents() const;
    typename std::deque<T>::const_iterator begin() const;
    typename std::deque<T>::const_iterator end() const;
    void setStartTime(double startTime);
    void setLenght(double lenght);
    bool covers(double triggerTime) const;//check if the trigger is within the time window
    bool covers(const T& event) const;//check if the event is within the time window
    bool isEmpty() const;
    template <class... Args>
    void emplaceEvent(double triggerTime, Args&&... args);//emplace back the event if it is within the window
    void pushBackEvent(const T& event);//push back the event if it is within the window (slower than emplace)
    void clear();//clear all events
    
  };

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
    
      if(lenght < this->lenght) events.erase(std::find_if(events.begin(), events.end(), [&](const auto& event){return event.getTriggerTime() >= startTime + lenght;}), events.end());;
      this->lenght = lenght;
      
    }

  }

  template <class T>
  bool Window<T>::covers(double triggerTime) const{
    
    return triggerTime >= startTime && triggerTime < startTime + lenght;

  }

  template <class T>
  bool Window<T>::covers(const T& event) const{
    
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
  void Window<T>::pushBackEvent(const T& event){
    
    if(covers(event)) events.push_back(event);

  }

  template <class T>
  void Window<T>::clear(){
    
    events.clear();

  }

}

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Window<T>& window){
  
  output<<std::setw(12)<<std::left<<"Start time: "<<std::setw(8)<<std::left<<window.getStartTime()<<std::setw(8)<<std::left<<" Lenght: "<<std::setw(8)<<std::left<<window.getLenght()
    <<std::setw(14)<<std::left<<"Number of events: "<<std::setw(8)<<std::left<<window.getNumberOfEvents();
    
  if(!window.isEmpty()) for(const auto& event : window) output<<"\n"<<event;
    
  return output;
  
}

#endif