///@author Joel Salas Martos

#ifndef __Vector4_H__
#define __Vector4_H__ 1

#include "math_utils.h"
#include "vector_3.h"

class Vector4 {
public:

  ///@brief this method constructs the variable when its created
	Vector4();

  ///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float x We pass a float for the x coordinate
  ///@param float y We pass a float for the y coordinate
	///@param float z We pass a float for the z coordinate
  ///@param float w We pass a float for the w coordinate
	Vector4(float x, float y, float z, float w);

  ///@brief this method constructs the variable when its created with the values that we pass to it
	///@param Vector3 a We pass a Vector with three coordinates
  ///@param float w We pass a float for the w coordinate
	Vector4(Vector3 a, float w);

	///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float a The value that fills the vector
	Vector4(float a);

	///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float* values_array The array will fill the vector in order
	Vector4(float* values_array);

	///@brief this method copies an entire Vector4 on the Vector that we are creating
	///@param Vector4 other We pass a Vector4 variable to copy it  	
	Vector4(const Vector4& other);

	///@brief this method destroys the variable  	
	~Vector4();

	///@brief this method adds our vector with another and returns the result
	///@param Vector4 other The Vector that we want to add with ours
	///@return Vector4 It returns the result of the sum	
	Vector4 operator+(const Vector4& other) const;

 	///@brief this method adds our vector with a number in both coordinates
	///@param float value The value that we want to add to aur vector
	///@return Vector4 It returns the result of the sum 
	Vector4 operator+(float value) const;

  ///@brief this method adds our vector with another vector and rewrites it
	///@param Vector4 other The Vector that we want to add with ours	
	void operator+=(const Vector4& other);

  ///@brief this method adds our vector with a number in both coordinates and rewrites it
	///@param float value The value that we want to add to aur vector	
	void operator+=(float value);

  ///@brief this method subtracts our vector with another and returns the result
	///@param Vector4 other The Vector that we want to subtract with ours
	///@return Vector4 It returns the result of the subtract
	Vector4 operator-(const Vector4& other) const;

 	///@brief this method subtracts our vector with a number in both coordinates
	///@param float value The value that we want to subtract to aur vector
	///@return Vector4 It returns the result of the subtract
	Vector4 operator-(float value) const;

  ///@brief this method subtracts our vector with another and returns the result
	///@param Vector4 other The Vector that we want to subtract with ours
	///@return Vector4 It returns the result of the subtract
	void operator -=(const Vector4& other);

  ///@brief this method subtracts our vector with a number in both coordinates and rewrites it
	///@param float value The value that we want to subtract to our vector
	void operator -=(float value);

  ///@brief this method multiplies our vector with a value and returns the result
	///@param float value The value that we want to multiply with our vector
	///@return Vector4 It returns the result of the multiply 
	Vector4 operator*(float value) const;

  ///@brief this method multiplies our vector with a value and rewrites the result
	///@param float value The value that we want to multiply with our vector
	void operator*=(float value);

  ///@brief this method divides our vector with a value and returns the result
	///@param float value The value that we want to divide with our vector
	///@return Vector4 It returns the result of the divide
	Vector4 operator/(float value) const;

  ///@brief this method divides our vector with a value and rewrites the result
	///@param float value The value that we want to divide with our vector
	void operator/=(float value);

  ///@brief this method compares our vector with another and returns the result if equal
	///@param Vector4 other The Vector that we want to compare with ours
	///@return bool It returns the result of the comparison
	bool operator==(const Vector4& other);

  ///@brief this method compares our vector with another and returns the result if different
	///@param Vector4 other The Vector that we want to compare with ours
	///@return bool It returns the result of the comparison
	bool operator!=(const Vector4& other);

  ///@brief this method equals our vector with a vector and rewrites it
	///@param Vector4 other The vector that we want to equal to our vector
	void operator=(const Vector4& other);

  ///@brief this method calculates the magnitude of the vector
	///@return float It returns the magnitude.
	float Magnitude() const;

 ///@brief this method calculates the normalization of the vector and rewrites it
	void Normalize();

  ///@brief this method calculates the normalization of the vector
	///@return Vector4 It returns the normalized vector
	Vector4 Normalized() const;

  ///@brief this method scales the vector
	///@param Vector4 scale The value that we want to scale with our vector
	void Scale(Vector4 scale);

  ///@brief this method calculates the magnitude without sqroot of the vector
	///@return float It returns the magnitude without sqroot 
	float SqrMagnitude() const;

  ///@brief this method calculates the distance between two vectors
	///@param Vector4 a First Point of distance
  ///@param Vector4 b Second Point of distance
	///@return float Returns the distance between these vectors
	static float Distance(const Vector4& a, const Vector4& b);

  ///@brief This method calculates the dot product
	///@param Vector4 a First Vector
  ///@param Vector4 b Second Vector
	///@return float Returns dot product of both vectors
	static float DotProduct(Vector4 a, Vector4 b);

  ///@brief This method calculates media of the vector, between the lerp quantity
	///@param Vector4 a First Vector
  ///@param Vector4 b Second Vector
  ///@param float t Lerp quantity
	///@return Vector3 Returns the Vector lerped
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float index);

  ///@brief This method calculates media of the vector, between the lerp quantity
	///@param Vector4 a First Vector
  ///@param Vector4 b Second Vector
  ///@param float t Lerp quantity
	///@return Vector3 Returns the Vector lerped without having limit in lerp
  static Vector4 LerpUnclamped(const Vector4& a, const Vector4& b, float t);	


	static const Vector4 one;
	static const Vector4 zero;

	float x;
	float y;
	float z;
	float w;

};

inline float Vector4::Magnitude() const{
	return MathUtils::Sqroot(SqrMagnitude());
}

inline void Vector4::Normalize() {	
	float inversemagnitude = 1 /Magnitude();
	*this *= inversemagnitude;
}

inline Vector4 Vector4::Normalized() const {
  float inverseMagnitude = 1.0f / Magnitude();
	return Vector4(this->x * inverseMagnitude,
                 this->y * inverseMagnitude,
                 this->z * inverseMagnitude,
				         this->w * inverseMagnitude);
}

inline void Vector4::Scale(Vector4 scale) {	
    this->x *= scale.x;
    this->y *= scale.y;
    this->z *= scale.z;
    this->w *= scale.w;
}

inline float Vector4::SqrMagnitude() const {
	return (MathUtils::Power(this->x,2)+MathUtils::Power(this->y,2)+
            MathUtils::Power(this->z,2)+MathUtils::Power(this->w,2));
}

inline float Vector4::Distance(const Vector4& a, const Vector4& b) {
		Vector4 aux;
  aux.x = b.x - a.x;
  aux.y = b.y - a.y;
  aux.z = b.z - a.z;
  aux.w = b.w - a.w;
  return (aux.Magnitude());
}

inline float Vector4::DotProduct(Vector4 a, Vector4 b) {
	return (a.x*b.x)+(a.y*b.y)+(a.z*b.z)+(a.w*b.w);
}

inline Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float index) {	
	index = MathUtils::Clamp(index,0,1);
	return LerpUnclamped(a,b,index);
}

inline Vector4 Vector4::LerpUnclamped(const Vector4& a, const Vector4& b, float t) {
	float x,y,z,w;
  x = a.x + (b.x - a.x) * t;
  y = a.y + (b.y - a.y) * t;
  z = a.z + (b.z - a.z) * t;
  w = a.w + (b.w - a.w) * t;
	return Vector4(x,y,z,w);
}

inline Vector4 Vector4::operator+(const Vector4& other) const{
	return Vector4(x+other.x, y+other.y, z+other.z, w+other.w);
}

inline Vector4 Vector4::operator+(float value) const{
	return Vector4(x+value, y+value, z+value, w+value );
}

inline void Vector4::operator+=(const Vector4& other) {
	this->x = this->x + other.x;
	this->y = this->y + other.y;
	this->z = this->z + other.z;
	this->w = this->w + other.w;
}

inline void Vector4::operator+=(float value) {
	this->x = this->x + value;
	this->y = this->y + value;
	this->z = this->z + value;
	this->w = this->w + value;
}

inline Vector4 Vector4::operator-(const Vector4& other) const{
	return Vector4(x-other.x, y-other.y, z-other.z, w-other.w);
}

inline Vector4 Vector4::operator-(float value) const{
	return Vector4(x-value, y-value, z-value, w-value);
}

inline void Vector4::operator -=(const Vector4& other) {
	this->x = this->x - other.x;
	this->y = this->y - other.y;
	this->z = this->z - other.z;
	this->w = this->w - other.w;	
}

inline void Vector4::operator -=(float value) {
	this->x = this->x - value;
	this->y = this->y - value;
	this->z = this->z - value;
	this->w = this->w - value;
}

inline Vector4 Vector4::operator*(float value) const{
	return Vector4(x*value, y*value, z*value, w*value);
}

inline void Vector4::operator*=(float value) {
	this->x = this->x*value;
	this->y = this->y*value;
	this->z = this->z*value;
	this->w = this->w*value;
}

inline Vector4 Vector4::operator/(float value) const{
	float inversevalue;
	inversevalue = 1/value;
	return Vector4(x*inversevalue, y*inversevalue, z*inversevalue, w*inversevalue);
}

inline void Vector4::operator/=(float value) {
	float inversevalue;
	inversevalue = 1/value;

	this->x = this->x * inversevalue;
	this->y = this->y * inversevalue;
	this->z = this->z * inversevalue;
	this->w = this->w * inversevalue;
}

inline bool Vector4::operator==(const Vector4& other) {
	if((x==other.x)&&(y==other.y)&&(z==other.z)&&(w==other.w))return true;
	return false;
}
inline bool Vector4::operator!=(const Vector4& other) {
	if((x==other.x)||(y==other.y)||(z==other.z)||(w==other.w))return true;
	return false;
}
inline void Vector4::operator=(const Vector4& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}



#endif 
