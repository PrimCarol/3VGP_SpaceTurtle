///@author Adrián Rivera Luna

#ifndef __MATRIX2_H__
#define __MATRIX2_H__ 1

#include <stdio.h>
#include "math_utils.h"
#include "vector_2.h"

class Matrix2x2 {
public:
	///@brief this method constructs the variable when its created
	Matrix2x2();

	///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float a[4] We pass an array of 4 floats with values to introduce into the matrix
	Matrix2x2(float a[4]);

	///@brief this method constructs the variable when its created with the value that we pass to it
	///@param float value We pass a float value to introduce in all the fields of the matrix
	Matrix2x2(float value);

	///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float a We pass a float to insert on the first field of our matrix
	///@param float b We pass a float to insert on the second field of our matrix					
	///@param float c We pass a float to insert on the third field of our matrix					
	///@param float d We pass a float to insert on the fourth field of our matrix					
	Matrix2x2(float a, float b, float c, float d);

	///@brief this method constructs the variable when its created with 2 Vector2 that we pass to it
	///@param a We pass a Vector2 variable to put it into the first and second field of the matrix
	///@param b We pass a Vector2 variable to put it into the third and fourth field of the matrix			
	Matrix2x2(const Vector2& a, const Vector2& b); 

	///@brief this method copies an entire Matrix2x2 on the new Matrix that we are creating
	///@param Matrix3x3 copy We pass a Matrix2x2 variable to copy it
	Matrix2x2(const Matrix2x2& copy);

	///@brief this method destroys the variable
	~Matrix2x2();

	///@brief this method prints whatever it is inside the matrix
	void print();

	///@brief this method creates a Matrix 2x2 Identity to return it
	///@return Matrix2x2 It returns the Matrix2x2 identity created.
	Matrix2x2 Identity() const;

	///@brief this method Multiplies our Matrix with one that we pass as parameter
	///@param Matrix2x2 other The Matrix2x2 that we want to multiply
	///@return Matrix2x2 It returns the result of the multiplication.
	Matrix2x2 Multiply(const Matrix2x2& other) const;

	///@brief this method gets the Determinant of our Matrix
	///@return float It returns the result of the Determinant function.
	float Determinant() const;

	///@brief this method returns the result of the adjoint of our Matrix
	///@return Matrix2x2 It returns the result of the adjoint.
	Matrix2x2 Adjoint() const;

	///@brief this method returns the line of our Matrix that we want
	///@param int line The line that we want
	///@return Vector2 It returns the line.
	Vector2 GetLine(int line) const;

	///@brief this method returns the column of our Matrix that we want
	///@param int line The column that we want
	///@return Vector2 It returns the column.
	Vector2 GetColum(int line) const;

	///@brief this method obtains the inverse of our matrix and returns it
	///@return Matrix2x2 It returns the inverse.
	inline Matrix2x2 Inverse() const;

	///@brief this method obtains the transpose of our matrix and returns it
	///@return Matrix2x2 It returns the transpose.
	inline Matrix2x2 Transpose() const;

	///@brief this method adds our matrix with another and returns the result
	///@param Matrix2x2 other The Matrix 2x2 that we want to add with ours
	///@return Matrix2x2 It returns the result of the sum
	inline Matrix2x2 operator+(const Matrix2x2& other) const;

	///@brief this method adds our matrix with another
	///@param Matrix2x2 other The Matrix 2x2 that we want to add with ours
	inline void operator+=(const Matrix2x2& other);

	///@brief this method adds a value to our matrix and returns the result
	///@param float value The value that we want to add to the fields of our matrix
	///@return Matrix2x2 It returns the result of the sum
	inline Matrix2x2 operator+(float value) const;

	///@brief this method adds a value to our matrix
	///@param float value The value that we want to add to the fields of our matrix
	inline void operator+=(float value);

	///@brief this method substracts our matrix with another and returns the result
	///@param Matrix2x2 other The Matrix2x2 that we want to subtract with ours
	///@return Matrix2x2 It returns the result of the substraction
	inline Matrix2x2 operator-(const Matrix2x2& other) const;

	///@brief this method subtract a value with our matrix 
	///@param Matrix2x2 other The Matrix 2x2 that we want to substract with ours
	inline void operator-=(const Matrix2x2& other);

	///@brief this method subtract a value with our matrix and returns the result
	///@param float value The value that we want to substract with the fields of our matrix
	///@return Matrix2x2 It returns the result of the substraction
	inline Matrix2x2 operator-(float value) const;

	///@brief this method substracts a value with our matrix
	///@param float value The value that we want to substract with the fields of our matrix
	inline void operator-=(float value);

	///@brief this method multiplies our matrix with a value
	///@param float value The value that we want to multiply with our Matrix
	///@return Matrix2x2 It returns the result of the mutiplication
	inline Matrix2x2 operator*(float value) const;

	///@brief this method multiplies our matrix with a value
	///@param float value The value that we want to multiply with our Matrix
	inline void operator*=(float value);

	///@brief this method divides our matrix with a value
	///@param float value The value that we want to divide with our Matrix
	///@return Matrix2x2 It returns the result of the division
	inline Matrix2x2 operator/(float value) const;

	///@brief this method divides our matrix with a value
	///@param float value The value that we want to divide with our Matrix
	inline void operator/=(float value);

	///@brief this method compares our Matrix2x2 with other
	///@param Matrix2x2 other The Matrix that we want to compare with ours
	///@return bool Returns true if its equal and false if its not
	bool operator==(const Matrix2x2& other) const;

	///@brief this method compares our Matrix2x2 with other
	///@param Matrix2x2 other The Matrix that we want to compare with ours
	///@return bool Returns true if its not equal and false if it is
	bool operator!=(const Matrix2x2& other) const;

	///@brief this method equals our matrix with other
	///@param Matrix2x2 other The Matrix that we want to match ours
	inline void operator=(const Matrix2x2& other);

	///@brief this method resets the values of our Matrix2x2
	void reset();

	float m[4];
};

inline void Matrix2x2::print(){
	for (int i = 0; i < 4; ++i){
		printf("%f \n", m[i]);
		if(i == 1){
			printf("\n");
		}
	}
}

inline Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const {
	float aux[4];

	aux[0] = m[0] + other.m[0];
	aux[1] = m[1] + other.m[1];
	aux[2] = m[2] + other.m[2];
	aux[3] = m[3] + other.m[3];

	return Matrix2x2(aux);	
}

inline void Matrix2x2::operator+=(const Matrix2x2& other) {
	m[0] += other.m[0];
	m[1] += other.m[1];
	m[2] += other.m[2];
	m[3] += other.m[3];
}

inline Matrix2x2 Matrix2x2::operator+(float value) const {
	float aux[4];

	aux[0] = m[0] + value;
	aux[1] = m[1] + value;
	aux[2] = m[2] + value;
	aux[3] = m[3] + value;

	return Matrix2x2(aux);	
}

inline void Matrix2x2::operator+=(float value) {
	m[0] += value;
	m[1] += value;
	m[2] += value;
	m[3] += value;	
}

inline Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other) const {
	float aux[4];

	aux[0] = m[0] - other.m[0];
	aux[1] = m[1] - other.m[1];
	aux[2] = m[2] - other.m[2];
	aux[3] = m[3] - other.m[3];

	return Matrix2x2(aux);	
}

inline void Matrix2x2::operator-=(const Matrix2x2& other) {
	m[0] -= other.m[0];
	m[1] -= other.m[1];
	m[2] -= other.m[2];
	m[3] -= other.m[3];	
}

inline Matrix2x2 Matrix2x2::operator-(float value) const {	
	float aux[4];

	aux[0] = m[0] - value;
	aux[1] = m[1] - value;
	aux[2] = m[2] - value;
	aux[3] = m[3] - value;

	return Matrix2x2(aux);	
}

inline void Matrix2x2::operator-=(float value) {
	m[0] -= value;
	m[1] -= value;
	m[2] -= value;
	m[3] -= value;
}


inline Matrix2x2 Matrix2x2::operator*(float value) const {
	float aux[4];

	aux[0] = m[0] * value;
	aux[1] = m[1] * value;
	aux[2] = m[2] * value;
	aux[3] = m[3] * value;

	return Matrix2x2(aux);
}

inline void Matrix2x2::operator*=(float value) {
	m[0] *= value;
	m[1] *= value;
	m[2] *= value;
	m[3] *= value;	
}

inline Matrix2x2 Matrix2x2::operator/(float value) const {
	/*if(value == 0.0f){
		///assert
		return *this->m;
	}*/
	///assert(value != 0 && " </> Te mamaste wey ");

	float aux[4];

	aux[0] = m[0] / value;
	aux[1] = m[1] / value;
	aux[2] = m[2] / value;
	aux[3] = m[3] / value;

	return Matrix2x2(aux);
}

inline void Matrix2x2::operator/=(float value) {
	/*if(value == 0){
		///assert
	}*/
	///assert(value != 0 && " </=> Te mamaste wey ");

	m[0] /= value;
	m[1] /= value;
	m[2] /= value;
	m[3] /= value;	
}


inline bool Matrix2x2::operator==(const Matrix2x2& other) const {
	return (m[0] == other.m[0] && m[1] == other.m[1]
		 && m[2] == other.m[2] && m[3] == other.m[3]);
}

inline bool Matrix2x2::operator!=(const Matrix2x2& other) const {
	return (m[0] != other.m[0] && m[1] != other.m[1]
		 && m[2] != other.m[2] && m[3] != other.m[3]);
}

inline void Matrix2x2::operator=(const Matrix2x2& other) {
	m[0] = other.m[0];
	m[1] = other.m[1];
	m[2] = other.m[2];
	m[3] = other.m[3];
}

inline Matrix2x2 Matrix2x2::Identity() const {
	float aux[4]= { 1.0f, 0.0f,
		    				  0.0f, 1.0f};
	
	return Matrix2x2(aux);
}

inline float Matrix2x2::Determinant() const {
	return m[0] * m[3] - m[1] * m[2];
}

inline Matrix2x2 Matrix2x2::Inverse() const {
	Matrix2x2 aux;
	
	float det = this->Determinant();
	aux = this->Adjoint();

	aux /= det;

	return Matrix2x2(aux);
}

inline Matrix2x2 Matrix2x2::Multiply(const Matrix2x2& other) const {
	float aux[4];

	aux[0] = m[0] * other.m[0] + m[2] * other.m[1];
	aux[1] = m[1] * other.m[0] + m[3] * other.m[1];
	aux[2] = m[0] * other.m[2] + m[2] * other.m[3];
	aux[3] = m[1] * other.m[2] + m[3] * other.m[3];

	return Matrix2x2(aux);
}

inline Matrix2x2 Matrix2x2::Adjoint() const {
	float aux[4];

	aux[0] = m[3];
	aux[1] = m[1] * -1;
	aux[2] = m[2] * -1;
	aux[3] = m[0];

	return Matrix2x2(aux);
}

inline Matrix2x2 Matrix2x2::Transpose() const {
	float aux[4];
	
	aux[0] = m[0];
	aux[1] = m[2];
	aux[2] = m[1];
	aux[3] = m[3];

	return Matrix2x2(aux);
}

inline Vector2 Matrix2x2::GetLine(int line) const {
	if(line < 0 || line > 1){
		///Todo assert
	}

	if(line == 0){
		return Vector2(m[0],m[1]);
	}else{
		return Vector2(m[2],m[3]);
	}
}

inline Vector2 Matrix2x2::GetColum(int line) const {
	if(line < 0 || line > 1){
		///Todo assert
	}
	if(line == 0){
		return Vector2(m[0],m[2]);
	}else{
		return Vector2(m[1],m[3]);
	}
}

#endif
