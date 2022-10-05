///@author Joel Salas Martos

#ifndef __VECTOR2_H__
#define __VECTOR2_H__ 1

#include "math_utils.h"

class Vector2 {
 public:

  ///@brief this method constructs the variable when its created
  Vector2();

  ///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float x We pass a float for the x coordinate
  ///@param float y We pass a float for the y coordinate
  Vector2(float x, float y);

	///@brief this method copies an entire Vector2 on the Vector that we are creating
	///@param Vector2 copy We pass a Vector2 variable to copy it  
  Vector2(const Vector2& copy);

	///@brief this method destroys the variable  
  ~Vector2();


	///@brief this method adds our vector with another and returns the result
	///@param Vector2 other The Vector that we want to add with ours
	///@return Vector2 It returns the result of the sum
  Vector2 operator+(const Vector2& other) const;

 	///@brief this method adds our vector with a number in both coordinates
	///@param float value The value that we want to add to aur vector
	///@return Vector2 It returns the result of the sum 
  Vector2 operator+(float value);

  ///@brief this method adds our vector with another vector and rewrites it
	///@param Vector2 other The Vector that we want to add with ours
  Vector2& operator+=(const Vector2& other);

  ///@brief this method adds our vector with a number in both coordinates and rewrites it
	///@param float value The value that we want to add to aur vector
  Vector2& operator+=(float value);

  ///@brief this method subtracts our vector with another and returns the result
	///@param Vector2 other The Vector that we want to subtract with ours
	///@return Vector2 It returns the result of the subtract
  Vector2 operator-(const Vector2& other) const;

 	///@brief this method subtracts our vector with a number in both coordinates
	///@param float value The value that we want to subtract to aur vector
	///@return Vector2 It returns the result of the subtract 
  Vector2 operator-(float value) const;

	///@brief this method negates a vector
	///@return Vector2 It returns the result of the negation
  Vector2& operator-();

  ///@brief this method subtracts our vector with another vector and rewrites it
	///@param Vector2 other The Vector that we want to add with subtract
  Vector2& operator-=(const Vector2& other);

  ///@brief this method subtracts our vector with a number in both coordinates and rewrites it
	///@param float value The value that we want to subtract to our vector
  Vector2& operator-=(float value);

  ///@brief this method compares our vector with another and returns the result if equal
	///@param Vector2 other The Vector that we want to compare with ours
	///@return bool It returns the result of the comparison
  bool operator==(const Vector2& other) const;

  ///@brief this method compares our vector with another and returns the result if different
	///@param Vector2 other The Vector that we want to compare with ours
	///@return bool It returns the result of the comparison
  bool operator!=(const Vector2& other) const;

  ///@brief this method equals our vector with a vector and rewrites it
	///@param Vector2 other The vector that we want to equal to our vector
  void operator=(const Vector2& other);

  ///@brief this method equals our vector with a value in both coordinates and rewrites it
	///@param Vector2 other The value that we want to equal to our vector
  void operator=(float value);

  ///@brief this method multiplies our vector with a value and returns the result
	///@param float value The value that we want to multiply with our vector
	///@return Vector2 It returns the result of the multiply  
  Vector2 operator*(float value) const;

  ///@brief this method multiplies our vector with a value and rewrites the result
	///@param float value The value that we want to multiply with our vector
	///@return Vector2 It returns the result of the multiply    
  Vector2& operator*=(float value);

  ///@brief this method divides our vector with a value and returns the result
	///@param float value The value that we want to divide with our vector
	///@return Vector2 It returns the result of the divide    
  Vector2 operator/(float value) const;

  ///@brief this method divides our vector with a value and rewrites the result
	///@param float value The value that we want to divide with our vector
	///@return Vector2 It returns the result of the divide      
  Vector2& operator/=(float value);

  ///@brief this method calculates the magnitude of the vector
	///@return float It returns the magnitude.
  float Magnitude() const;

  ///@brief this method calculates the normalization of the vector and rewrites it
  void Normalize();

  ///@brief this method calculates the normalization of the vector
	///@return Vector2 It returns the normalized vector
  Vector2 Normalized() const;

  ///@brief this method scales the vector
	///@param Vector2 scale The value that we want to scale with our vector
  void Scale(const Vector2 scale);

  ///@brief this method calculates the magnitude without sqroot of the vector
	///@return float It returns the magnitude without sqroot 
  float SqrMagnitude() const;

  ///@brief this method calculates the distance between two vectors
	///@param Vector2 a First Point of distance
  ///@param Vector2 b Second Point of distance
	///@return float Returns the distance between these vectors        
  static float Distance(const Vector2 a, const Vector2 b);

  ///@brief This method calculates the dot product
	///@param Vector2 a First Vector
  ///@param Vector2 b Second Vector
	///@return float Returns dot product of both vectors
  static float DotProduct(Vector2 a, Vector2 b);

  ///@brief This method calculates media of the vector, between the lerp quantity
	///@param Vector2 a First Vector
  ///@param Vector2 b Second Vector
  ///@param float t Lerp quantity
	///@return Vector2 Returns the Vector lerped
  static Vector2 Lerp(const Vector2 a, const Vector2 b, float t);

  ///@brief This method calculates media of the vector, between the lerp quantity
	///@param Vector2 a First Vector
  ///@param Vector2 b Second Vector
  ///@param float t Lerp quantity
	///@return Vector2 Returns the Vector lerped without having limit in lerp  
  static Vector2 LerpUnclamped(const Vector2 a, const Vector2 b, float t);

  static const Vector2 up;
  static const Vector2 down;
  static const Vector2 right;
  static const Vector2 left;
  static const Vector2 zero;
  static const Vector2 one;

  float x;
  float y;
};

inline Vector2 Vector2::operator+(const Vector2& other) const {
  float x,y;
  x = this->x + other.x;
  y = this->y + other.y;
  return Vector2(x,y);
}

inline Vector2 Vector2::operator+(float value) {
  float x,y;
  x = this->x + value;
  y = this->y + value;
  return Vector2(x,y);
}

inline Vector2& Vector2::operator+=(const Vector2& other){
  this->x = this->x + other.x;
  this->y = this->y + other.y;
  return *this;
}

inline Vector2& Vector2::operator+=(float value){
  this->x = this->x + value;
  this->y = this->y + value;
  return *this;
}

inline Vector2 Vector2::operator-(const Vector2& other) const {
  float x,y;
  x = this->x - other.x;
  y = this->y - other.y;
  return Vector2(x,y);
}

inline Vector2 Vector2::operator-(float value) const {
  float x,y;
  x = this->x - value;
  y = this->y - value;
  return Vector2(x,y);
}

inline Vector2& Vector2::operator-() {
  this->x = -this->x;
  this->y = -this->y;
  return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& other) {
  this->x = this->x - other.x;
  this->y = this->y - other.y;
  return *this;
}

inline Vector2& Vector2::operator-=(float value){
  this->x = this->x - value;
  this->y = this->y - value;
  return *this;
}

inline bool Vector2::operator==(const Vector2& value) const {
  if(this->x == value.x && this->y == value.y)return true;
  return false;
}

inline bool Vector2::operator!=(const Vector2& value) const {
  if(this->x != value.x || this->y != value.y)return true;
  return false;
}

inline void Vector2::operator=(const Vector2& other) {
  this->x = other.x;
  this->y = other.y;
}

inline void Vector2::operator=(float value) {
  this->x = value;
  this->y = value;
}

inline Vector2 Vector2::operator*(float value) const {
  float x,y;
  x = this->x * value;
  y = this->y * value;
	return Vector2(x,y);
}

inline Vector2& Vector2::operator*=(float value) {  
  this->x = this->x * value;
  this->y = this->y * value;
  return *this;
}

inline Vector2 Vector2::operator/(float value) const {
  float x,y,inversevalue;
  inversevalue = 1/value;

  x = this->x *inversevalue;
  y = this->y *inversevalue;
	return Vector2(x,y);
}

inline Vector2& Vector2::operator/=(float value) {
  float inversevalue;
  inversevalue = 1/value;
  
  this->x = this->x / value;
  this->y = this->y / value;
  return *this;
}

inline float Vector2::Magnitude() const {
  return MathUtils::Sqroot(SqrMagnitude());
}

inline void Vector2::Normalize() { 
  float inverseMagnitude = 1.0f / Magnitude();
	*this *= inverseMagnitude;
}

inline Vector2 Vector2::Normalized() const {
  float inverseMagnitude = 1.0f / Magnitude();
	return Vector2(this->x * inverseMagnitude,this->y * inverseMagnitude);
}

inline void Vector2::Scale(const Vector2 scale){
  this->x *= scale.x;
  this->y *= scale.y;
}

inline float Vector2::SqrMagnitude() const {
  return (MathUtils::Power(this->x,2)+MathUtils::Power(this->y,2));
}

inline float Vector2::Distance(const Vector2 a, const Vector2 b) {
  Vector2 aux;

  aux.x = b.x - a.x;
  aux.y = b.y - a.y;
  return (aux.Magnitude());
}

inline Vector2 Vector2::Lerp(const Vector2 a, const Vector2 b, float t) {
  float x,y;
  x = a.x + (b.x - a.x) * MathUtils::Clamp(t,0,1);
  y = a.y + (b.y - a.y) * MathUtils::Clamp(t,0,1);
	return Vector2(x,y);
}

inline Vector2 Vector2::LerpUnclamped(const Vector2 a, const Vector2 b, float t) {
  float x,y;
  x = a.x + (b.x - a.x) * t;
  y = a.y + (b.y - a.y) * t;
	return Vector2(x,y);
}

inline float Vector2::DotProduct(Vector2 a, Vector2 b) {
	return (a.x*b.x)+(a.y*b.y);
}

#endif 
