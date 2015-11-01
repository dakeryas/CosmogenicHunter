#ifndef SHOWER_H
#define SHOWER_H

#include "Window.hpp"

namespace CosmogenicHunter{

  template <class Initiator, class Follower>
  class Shower{
    
    Initiator initiator;//Initiator creating the follower flux
    Window<Follower> followerWindow;
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);
    
  public:
    Shower() = default;
    Shower(Initiator initiator, double maximumDuration);//opens a window starting at Initiator.getTriggerTime() and lasting 'maximumDuration' to push followers
    const Initiator& getInitiator() const;
    double getTriggerTime() const;//returns Initiator.getTriggerTime() 
    const Window<Follower>& getFollowerWindow() const;
    unsigned getNumberOfFollowers() const;
    template <class... Args>
    void emplaceFollower(Args&&... args);
    void pushBackFollower(const Follower& follower);
    void pushBackFollower(Follower&& follower);
    
  };
  
  template <class Initiator, class Follower>
  template <class Archive>
  void Shower<Initiator, Follower>::serialize(Archive& archive){
    
    archive(initiator, followerWindow);

  }

  template <class Initiator, class Follower>
  template <class... Args>
  void Shower<Initiator, Follower>::emplaceFollower(Args&&... args){
    
    followerWindow.emplaceEvent(std::forward<Args>(args)...);

  }
  
  template <class Initiator, class Follower>
  Shower<Initiator, Follower>::Shower(Initiator initiator, double maximumDuration):initiator(initiator), followerWindow(initiator.getTriggerTime(), maximumDuration){
    
  }

  template <class Initiator, class Follower>
  const Initiator& Shower<Initiator, Follower>::getInitiator() const{
    
    return initiator;

  }
  
  template <class Initiator, class Follower>
  double Shower<Initiator, Follower>::getTriggerTime() const{

    return initiator.getTriggerTime();
    
  }

  template <class Initiator, class Follower>
  const Window<Follower>& Shower<Initiator, Follower>::getFollowerWindow() const{
    
    return followerWindow;

  }
  
  template <class Initiator, class Follower>
  unsigned Shower<Initiator, Follower>::getNumberOfFollowers() const{
    
    return followerWindow.getNumberOfEvents();

  }
  
  template <class Initiator, class Follower>
  void Shower<Initiator, Follower>::pushBackFollower(const Follower& follower){

    followerWindow.pushBackEvent(follower);
    
  }
  
  template <class Initiator, class Follower>
  void Shower<Initiator, Follower>::pushBackFollower(Follower&& follower){

    followerWindow.pushBackEvent(follower);
    
  }

}

template <class Initiator, class Follower>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Shower<Initiator,Follower>& shower){
  
  output<<std::setw(14)<<std::left<<"Initiator"<<":\n"<<shower.getInitiator()
    <<std::setw(15)<<std::left<<"\nFollowers"<<":\n"<<shower.getFollowerWindow();
  return output;
  
}

#endif