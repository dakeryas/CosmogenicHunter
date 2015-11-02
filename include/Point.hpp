#ifndef POINT_H
#define POINT_H

#include <iomanip>
#include <cmath>
#include "cereal/archives/binary.hpp"

namespace CosmogenicHunter{

  template <class T>
  class Point{
    
    T x, y, z;
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& archive);
    
  public:
    Point() = default;
    Point(T x, T y, T z);
    Point(const Point<T>& other) = default;
    Point(Point<T>&& other) = default;
    Point<T>& operator = (const Point<T>& other) = default;
    Point<T>& operator = (Point<T>&& other) = default;
    ~Point() = default;
    const T & getX() const;
    const T & getY() const;
    const T & getZ() const;
    void setX(T x);
    void setY(T y);
    void setZ(T z);
    void setCoordinates(T x, T y, T z);
    T getDistanceTo(const Point& otherPoint) const;
    Point<T> getMidpointTo(const Point& otherPoint) const;
    
  };
  
  template <class T>
  template <class Archive>
  void Point<T>::serialize(Archive& archive){
    
    archive(x, y, z);

  }

  template <class T>
  Point<T>::Point(T x, T y, T z):x(x),y(y),z(z){
    
  }

  template <class T>
  const T & Point<T>::getX() const{
    
    return x;

  }

  template <class T>
  const T & Point<T>::getY() const{
    
    return y;

  }

  template <class T>
  const T & Point<T>::getZ() const{
    
    return z;

  }

  template <class T>
  void Point<T>::setX(T x){
    
    this->x = x;

  }

  template <class T>
  void Point<T>::setY(T y){

    this->y = y;

  }
  
  template <class T>
  void Point<T>::setZ(T z){

    this->z = z;

  }
  
  template <class T>
  void Point<T>::setCoordinates(T x, T y, T z){

    setX(x);
    setY(y);
    setZ(z);

  }
  
  template <class T>
  T Point<T>::getDistanceTo(const Point& otherPoint) const{
    
    return std::sqrt(std::pow(x - otherPoint.x, 2) + std::pow(y - otherPoint.y, 2) + std::pow(z - otherPoint.z, 2));

  }
  
  template <class T>
  Point<T> Point<T>::getMidpointTo(const Point<T>& otherPoint) const{

    return Point(.5*(x + otherPoint.x), .5*(y + otherPoint.y), .5*(z + otherPoint.z));
    
  }
  
  template <class T>
  T getDistanceBetween(const CosmogenicHunter::Point<T>& point1, const CosmogenicHunter::Point<T>& point2){
    
    return point1.getDistanceTo(point2);
    
  }
  
  template <class T>
  Point<T> getMidpointBetween(const CosmogenicHunter::Point<T>& point1, const CosmogenicHunter::Point<T>& point2){
    
    return point1.getMidpointTo(point2);
    
  }

}

template <class T>
std::ostream& operator<<(std::ostream& output, const CosmogenicHunter::Point<T>& point){
  
  output<<"("<<std::setw(5)<<std::internal<<point.getX()<<", "<<std::setw(5)<<std::internal<<point.getY()<<", "<<std::setw(5)<<std::internal<<point.getZ()<<")";
    
  return output;
  
}



#endif