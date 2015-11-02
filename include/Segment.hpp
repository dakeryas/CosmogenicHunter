#ifndef SEGMENT_H
#define SEGMENT_H

#include "Point.hpp"

namespace CosmogenicHunter{

  template <class T>
  class Segment{

    Point<T> startPoint;
    Point<T> endPoint;
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);
    
  public:
    Segment() = default;
    Segment(const Point<T>& startPoint, const Point<T>& endPoint);
    Segment(const Segment<T>& other) = default;
    Segment(Segment<T>&& other) = default;
    Segment<T>& operator = (const Segment<T>& other) = default;
    Segment<T>& operator = (Segment<T>&& other) = default;
    ~Segment() = default;
    void setStartPoint(const Point<T>& startPoint);
    void setEndPoint(const Point<T>& endPoint);
    void setPoints(const Point<T>& startPoint, const Point<T>& endPoint);
    const Point<T>& getStartPoint() const;
    const Point<T>& getEndPoint() const;
    T getLenght() const;
    Point<T> getCenter() const;
    bool isSmallerThan(T lenght) const;
    bool isSmallerThan(const Segment<T>& other) const;
    T getDistanceTo(const Point<T>& point) const;//get the shortest distance to the line defined by the segment
    
  };
  
  template <class T>
  template <class Archive>
  void Segment<T>::serialize(Archive& archive){
    
    archive(startPoint, endPoint);

  }

  template <class T>
  Segment<T>::Segment(const Point<T>& startPoint, const Point<T>& endPoint):startPoint(startPoint),endPoint(endPoint){
    
  }
  
  template <class T>
  void Segment<T>::setStartPoint(const Point<T>& startPoint){
    
    this->startPoint = startPoint;

  }

  template <class T>
  void Segment<T>::setEndPoint(const Point<T>& endPoint){
    
    this->endPoint = endPoint;

  }
  
  template <class T>
  void Segment<T>::setPoints(const Point<T>& startPoint, const Point<T>& endPoint){
    
    setStartPoint(startPoint);
    setEndPoint(endPoint);

  }

  template <class T>
  const Point<T>& Segment<T>::getStartPoint() const{
    
    return startPoint;

  }

  template <class T>
  const Point<T>& Segment<T>::getEndPoint() const{
    
    return endPoint;

  }

  template <class T>
  T Segment<T>::getLenght() const{
    
    return getDistanceBetween(startPoint, endPoint);

  }
  
  template <class T>
  Point<T> Segment<T>::getCenter() const{
    
    return getMidpointBetween(startPoint, endPoint);

  }
  
  template <class T>
  bool Segment<T>::isSmallerThan(T lenght) const{
    
    return getLenght() < lenght;

  }
  
  template <class T>
  bool Segment<T>::isSmallerThan(const Segment<T>& other) const{
    
    return isSmallerThan(other.getLenght());

  }
  
  template <class T>
  T Segment<T>::getDistanceTo(const Point<T>& point) const{
    
    auto a = getDistanceBetween(startPoint, endPoint);
    auto b = getDistanceBetween(startPoint, point);
    auto c = getDistanceBetween(endPoint, point);
    
    auto halfPerimeter = .5 * (a + b + c);//half-perimeter of the triangle (startPoint  endPoint  point)
    
    return 2 * std::sqrt(halfPerimeter * (halfPerimeter - a) *(halfPerimeter - b) * (halfPerimeter - c)) / a; //'area = Heron's formula' and 'area = distance * track / 2' thus 'distance = 2 Heron / track'

  }
  
}

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Segment<T>& segment){
  
  output<<"["<<segment.getStartPoint()<<", "<<segment.getEndPoint()<<"]";
  return output;
  
}

template <class T>
bool operator<(const CosmogenicHunter::Segment<T>& segment1, const CosmogenicHunter::Segment<T>& segment2){
  
  return segment1.isSmallerThan(segment2);
  
}

template <class T>
bool operator>(const CosmogenicHunter::Segment<T>& segment1, const CosmogenicHunter::Segment<T>& segment2){
  
  return !(segment1 < segment2);
  
}

#endif