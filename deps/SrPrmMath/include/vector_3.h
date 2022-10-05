///@author Joel Salas Martos

#ifndef __VECTOR3_H__
#define __VECTOR3_H__ 1

#include "math_utils.h"

class Vector3 {

public:


  ///@brief this method constructs the variable when its created
	Vector3();

	///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float value The value that fills the vector
	Vector3(float value);

	///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float x We pass a float for the x coordinate
  ///@param float y We pass a float for the y coordinate
  ///@param float z We pass a float for the z coordinate	
	Vector3(float x, float y, float z);

	///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float* values_array The array will fill the vector in order
	Vector3(float* values_array);

	///@brief this method copies an entire Vector3 on the Vector that we are creating
	///@param Vector3 other We pass a Vector3 variable to copy it  	
	Vector3(const Vector3& other);

	///@brief this method destroys the variable  	
	~Vector3();


	///@brief this method adds our vector with another and returns the result
	///@param Vector3 other The Vector that we want to add with ours
	///@return Vector3 It returns the result of the sum
	Vector3 operator+(const Vector3& other) const;

 	///@brief this method adds our vector with a number in both coordinates
	///@param float value The value that we want to add to aur vector
	///@return Vector3 It returns the result of the sum 	
	Vector3 operator+(float value) const;

  ///@brief this method adds our vector with another vector and rewrites it
	///@param Vector3 other The Vector that we want to add with ours	
	Vector3& operator+=(const Vector3& other);

  ///@brief this method adds our vector with a number in both coordinates and rewrites it
	///@param float value The value that we want to add to aur vector	
	Vector3& operator+=(float value);

  ///@brief this method subtracts our vector with another and returns the result
	///@param Vector3 other The Vector that we want to subtract with ours
	///@return Vector3 It returns the result of the subtract	
	Vector3 operator-(const Vector3& other) const;

 	///@brief this method subtracts our vector with a number in both coordinates
	///@param float value The value that we want to subtract to aur vector
	///@return Vector3 It returns the result of the subtract 
	Vector3 operator-(float value) const;

  ///@brief this method subtracts our vector with another and returns the result
	///@param Vector3 other The Vector that we want to subtract with ours
	///@return Vector3 It returns the result of the subtract
	Vector3& operator-=(const Vector3& other);


  ///@brief this method subtracts our vector with a number in both coordinates and rewrites it
	///@param float value The value that we want to subtract to our vector
	Vector3& operator-=(float value);

  ///@brief this method compares our vector with another and returns the result if equal
	///@param Vector3 other The Vector that we want to compare with ours
	///@return bool It returns the result of the comparison
	bool operator==(const Vector3& other) const;

  ///@brief this method compares our vector with another and returns the result if different
	///@param Vector3 other The Vector that we want to compare with ours
	///@return bool It returns the result of the comparison
	bool operator!=(const Vector3& other) const;

  ///@brief this method equals our vector with a vector and rewrites it
	///@param Vector3 other The vector that we want to equal to our vector
	void operator=(const Vector3& other);

  ///@brief this method equals our vector with a value in both coordinates and rewrites it
	///@param float value The value that we want to equal to our vector
	void operator=(float value);

  ///@brief this method multiplies our vector with a value and returns the result
	///@param float value The value that we want to multiply with our vector
	///@return Vector3 It returns the result of the multiply 
	Vector3 operator*(float value) const;

  ///@brief this method multiplies our vector with a value and returns the result
	///@param Vector3 other The vector that we want to multiply with our vector
	///@return Vector3 It returns the result of the multiply 
	Vector3 operator*(const Vector3& other) const; 

  ///@brief this method multiplies our vector with a value and rewrites the result
	///@param float value The value that we want to multiply with our vector
	///@return Vector3 It returns the result of the multiply 
	Vector3& operator*=(float value);

  ///@brief this method divides our vector with a value and returns the result
	///@param float value The value that we want to divide with our vector
	///@return Vector3 It returns the result of the divide  
	Vector3 operator/(float value) const;

  ///@brief this method divides our vector with a value and rewrites the result
	///@param float value The value that we want to divide with our vector
	///@return Vector3 It returns the result of the divide      
	Vector3& operator/=(float value);

  ///@brief this method calculates the magnitude of the vector
	///@return float It returns the magnitude.
	float Magnitude() const;

  ///@brief this method calculates the normalization of the vector
	///@return Vector3 It returns the normalized vector
	Vector3 Normalized() const;

  ///@brief this method calculates the normalization of the vector and rewrites it
	void Normalize();

  ///@brief this method calculates the magnitude without sqroot of the vector
	///@return float It returns the magnitude without sqroot 
	float SqrMagnitude() const;

  ///@brief this method scales the vector
	///@param Vector3 scale The value that we want to scale with our vector
	void Scale(const Vector3& other);

  ///@brief This method calculates media of the vector, between the lerp quantity
	///@param Vector3 a First Vector
  ///@param Vector3 b Second Vector
  ///@param float t Lerp quantity
	///@return Vector3 Returns the Vector lerped
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

  ///@brief This method calculates media of the vector, between the lerp quantity
	///@param Vector3 a First Vector
  ///@param Vector3 b Second Vector
  ///@param float t Lerp quantity
	///@return Vector3 Returns the Vector lerped without having limit in lerp  
	static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);

  ///@brief This method calculates the dot product
	///@param Vector3 a First Vector
  ///@param Vector3 b Second Vector
	///@return float Returns dot product of both vectors
	static float DotProduct(const Vector3& a, const Vector3& b);

  ///@brief This method calculates the angle between both vectors
	///@param Vector3 a First Vector
  ///@param Vector3 b Second Vector
	///@return float Returns angle of both vectors
	static float Angle(const Vector3& a, const Vector3& b);

  ///@brief This method calculates the Cross Product
	///@param Vector3 a First Vector
  ///@param Vector3 b Second Vector
	///@return float Returns Cross Product of both vectors
	static Vector3 CrossProduct(const Vector3& a,const Vector3& b);	

  ///@brief this method calculates the distance between two vectors
	///@param Vector2 a First Point of distance
  ///@param Vector2 b Second Point of distance
	///@return float Returns the distance between these vectors  
	static float Distance(const Vector3& a, const Vector3& b);

  ///@brief this method calculates the reflection with normal and direction
	///@param Vector2 a direction
  ///@param Vector2 b normal
	///@return float Returns the reflected vector 
	static Vector3 Reflect(const Vector3& direction, const Vector3& normal);

	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 right;
	static const Vector3 left;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 zero;
	static const Vector3 unit;

	float x;
	float y;
	float z;
};


inline float Vector3::Magnitude() const {
  return MathUtils::Sqroot(SqrMagnitude());
}

inline void Vector3::Normalize() {	
	float inverseMagnitude = 1.0f / Magnitude();
	*this *= inverseMagnitude;
}

inline Vector3 Vector3::Normalized() const {
  float inverseMagnitude = 1.0f / Magnitude();
	return Vector3(x * inverseMagnitude,
                   y * inverseMagnitude,
                   z * inverseMagnitude);
}

inline float Vector3::DotProduct(const Vector3& a, const Vector3& other)  {
	return (a.x*other.x)+(a.y*other.y)+(a.z*other.z);
}

inline float Vector3::Angle(const Vector3& a, const Vector3& other)  {

	//auxf = DotProduct(a,other);
	//auxf/= (a.Magnitude()*other.Magnitude());

	float auxf = MathUtils::Sqroot(a.SqrMagnitude() * other.SqrMagnitude());
	if (auxf < 0.01f) {
		return 0;
	}

	return MathUtils::Arcosine( DotProduct(a,other) / auxf);
}

inline Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& other)  {
	return Vector3(a.y * other.z - a.z * other.y,
								 a.z * other.x - a.x * other.z,
								 a.x * other.y - a.y * other.x);
}

inline float Vector3::SqrMagnitude() const {
	/*return (MathUtils::Power(this->x, 2) +
          MathUtils::Power(this->y,2)+
          MathUtils::Power(this->z,2));*/
	return (x * x) + (y * y) + (z * z);
}

inline void Vector3::Scale(const Vector3& other) {	
	x = x * other.x;
	y = y * other.y;
	z = z * other.z;
}

inline Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {
	t = MathUtils::Clamp(t,0,1);
	return LerpUnclamped(a,b,t);
}

inline Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t) {
	float x,y,z;
  	x = a.x + (b.x - a.x) * t;
 	 y = a.y + (b.y - a.y) * t;
  	z = a.z + (b.z - a.z) * t;
	return Vector3(x,y,z);
}

inline float Vector3::Distance(const Vector3& a, const Vector3& b) {
	//Vector3 aux;
	float aux_x = a.x - b.x;
	float aux_y = a.y - b.y;
	float aux_z = a.z - b.z;

	return MathUtils::Sqroot(aux_x*aux_x + aux_y*aux_y + aux_z*aux_z);
	/*return (aux.Magnitude()); */
}

inline Vector3 Vector3::Reflect(const Vector3& direction, const Vector3& normal) {
	(direction - ((normal * DotProduct(direction, normal) * 2.f)));
	return (direction - ((normal * DotProduct(direction, normal) * 2.f)));
	//return Vector3();
}

inline Vector3 Vector3::operator+(const Vector3& other) const {
	return Vector3(x+other.x, y+other.y, z+other.z);
}

inline Vector3 Vector3::operator+(float value) const {
	return Vector3(x+value, y+value, z+value);
}

inline Vector3& Vector3::operator+=(const Vector3& other) {
	x = x + other.x;
	y = y + other.y;
	z = z + other.z;
	return *this;
}

inline Vector3& Vector3::operator+=(float value) {
	x = x + value;
	y = y + value;
	z = z + value;
	return *this;
}

inline Vector3 Vector3::operator-(const Vector3& other) const {
	return Vector3(x-other.x, y-other.y, z-other.z);
}

inline Vector3 Vector3::operator-(float value) const {
	return Vector3(x-value, y-value, z-value);
}

inline Vector3& Vector3::operator-=(const Vector3& other) {
	x = x - other.x;
	y = y - other.y;
	z = z - other.z;
	return *this;
}

inline Vector3& Vector3::operator-=(float value) {
	x = x - value;
	y = y - value;
	z = z - value;
	return *this;
}

inline bool Vector3::operator==(const Vector3& other) const {
	if((x==other.x)&&(y==other.y)&&(z==other.z))return true;
	return false;
}

inline bool Vector3::operator!=(const Vector3& other) const {
	if((x==other.x)||(y==other.y)||(z==other.z))return true;
	return false;
}

inline void Vector3::operator=(const Vector3& other) {	
	x = other.x;
	y = other.y;
	z = other.z;
}

inline void Vector3::operator=(float value) {	
	x = value;
	y = value;
	z = value;
}

inline Vector3 Vector3::operator*(float value) const {
	return Vector3(x*value, y*value, z*value);
}

inline Vector3 Vector3::operator*(const Vector3& other) const {
	
	return Vector3();
}

inline Vector3& Vector3::operator*=(float value) {	
	x = x*value;
	y = y*value;
	z = z*value;
	return *this;
}

inline Vector3 Vector3::operator/(float value) const {
	float inversevalue;
	inversevalue = 1/value;
	return Vector3(x*inversevalue, y*inversevalue, z*inversevalue);
}

inline Vector3& Vector3::operator/=(float value) {	
	float inversevalue;
	inversevalue = 1/value;

	x = x * inversevalue;
	y = y * inversevalue;
	z = z * inversevalue;
	return *this;
}

#endif 
