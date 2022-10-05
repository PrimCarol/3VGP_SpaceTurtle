///@author Pere Prim Carol

#ifndef __MATRIX3_H__
#define __MATRIX3_H__ 1

#include "math_utils.h"
#include "vector_3.h"
#include "vector_2.h"
#include "matrix_2.h"

class Matrix3x3 {
public:
	///@brief this method constructs the variable when its created
	Matrix3x3();

	///@brief this method constructs the variable when its created with the values that we pass to it
	///@param float values_array We pass an array of floats with values to introduce into the matrix
	Matrix3x3(float *values_array);

	///@brief this method constructs the variable when its created with the value that we pass to it
	///@param float value We pass a float value to introduce in all the fields of the matrix
	Matrix3x3(float value);

	///@brief this method constructs the variable when its created with the values that we pass to it
	///@param Vector3 a We pass a Vector3 to insert on the Matrix
	///@param Vector3 b We pass a Vector3 to insert on the Matrix			
	///@param Vector3 c We pass a Vector3 to insert on the Matrix							
	Matrix3x3(Vector3 a, Vector3 b, Vector3 c);

	///@brief this method copies an entire Matrix3x3 on the new Matrix that we are creating
	///@param Matrix3x3 copy We pass a Matrix3x3 variable to copy it
	Matrix3x3(const Matrix3x3& copy);

	///@brief this method destroys the variable
	~Matrix3x3();

	///@brief this method creates a Matrix 3x3 Identity to return it
	///@return Matrix3x3 It returns the Matrix3x3 identity created.
	static Matrix3x3 Identity();

	///@brief this method Multiplies our Matrix with one that we pass as parameter
	///@param Matrix3x3 other The Matrix3x3 that we want to multiply
	///@return Matrix3x3 It returns the result of the multiplication.
	Matrix3x3 Multiply(const Matrix3x3& other) const;

	///@brief this method gets the Determinant of our Matrix
	///@return float It returns the result of the Determinant function.
	float Determinant() const;	

	///@brief this method returns the result of the adjoint of our Matrix
	///@return Matrix3x3 It returns the result of the adjoint.
	Matrix3x3 Adjoint() const;

	///@brief this method checks if it can get the inverse of the Matrix that we pass as parameter and if it cans returns the inverse
	///@param Matrix3x3 out The Matrix3x3 that we want to know the inverse
	///@return Matrix3x3 It returns the inverse.
	bool GetInverse(Matrix3x3& out) const;

	///@brief this method obtains the inverse of our matrix and returns it
	///@return Matrix3x3 It returns the inverse.
	bool Inverse();

	///@brief this method obtains the transpose of our matrix and returns it
	///@return Matrix3x3 It returns the transpose.
	Matrix3x3 Transpose() const;

	///@brief This function inserts the vector 2 that we pass as parameter into the fields 6 and 7 of the matrix
	///@param Vector2 position The position that we want to insert in the matrix
	///@return Matrix3x3 The matrix with the new position
	static Matrix3x3 Translate(const Vector2& position);

	///@brief This function inserts a couple of floats that we pass as parameter into the fields 6 and 7 of the matrix
	///@param float x The position x that we want to insert in the matrix
	///@param float y The position y that we want to insert in the matrix
	///@return Matrix3x3 The matrix with the new position
	static Matrix3x3 Translate(float x, float y);

	///@brief this method returns the column of our Matrix that we want
	///@param int column The column that we want
	///@return Vector3 It returns the column.
	Vector3 GetColum(int colum) const;

	///@brief this method returns the line of our Matrix that we want
	///@param int line The line that we want
	///@return Vector3 It returns the line.
	Vector3 GetLine(int line) const;

	///@brief this method adds our matrix with another and returns the result
	///@param Matrix3x3 other The Matrix 3x3 that we want to add with ours
	///@return Matrix3x3 It returns the result of the sum
	inline Matrix3x3 operator+(const Matrix3x3& other) const;

	///@brief this method adds our matrix with another
	///@param Matrix3x3 other The Matrix 3x3 that we want to add with ours
	///@return Matrix3x3 It returns the pointer this with the sum done
	inline Matrix3x3& operator+=(const Matrix3x3& other);

	///@brief this method adds a value to our matrix and returns the result
	///@param float value The value that we want to add to the fields of our matrix
	///@return Matrix3x3 It returns the result of the sum
	inline Matrix3x3 operator+(float value) const;

	///@brief this method adds a value to our matrix
	///@param float value The value that we want to add to the fields of our matrix
	///@return Matrix3x3 It returns the pointer this with the sum done
	inline Matrix3x3& operator+=(float value);

	///@brief this method substracts our matrix with another and returns the result
	///@param Matrix3x3 other The Matrix3x3 that we want to subtract with ours
	///@return Matrix3x3 It returns the result of the substraction
	inline Matrix3x3 operator-(const Matrix3x3& other) const;

	///@brief this method subtract a value with our matrix 
	///@param Matrix3x3 other The Matrix 3x3 that we want to substract with ours
	///@return Matrix3x3 It returns the pointer this with the substraction done
	inline Matrix3x3& operator-=(const Matrix3x3& other);

	///@brief this method subtract a value with our matrix and returns the result
	///@param float value The value that we want to substract with the fields of our matrix
	///@return Matrix3x3 It returns the result of the substraction
	inline Matrix3x3 operator-(float value) const;

	///@brief this method substracts a value with our matrix
	///@param float value The value that we want to substract with the fields of our matrix
	///@return Matrix3x3 It returns the pointer this with the substraction done
	inline Matrix3x3& operator-=(float value);

	///@brief this method multiplies our matrix with a value
	///@param float value The value that we want to multiply with our Matrix
	///@return Matrix3x3 It returns the result of the mutiplication
	inline Matrix3x3 operator*(float value) const;

	///@brief this method multiplies our matrix with a value
	///@param float value The value that we want to multiply with our Matrix
	///@return Matrix3x3 It returns the pointer this with the multiplication done
	inline Matrix3x3& operator*=(float value);

	///@brief this method divides our matrix with a value
	///@param float value The value that we want to divide with our Matrix
	///@return Matrix3x3 It returns the result of the division
	inline Matrix3x3 operator/(float value) const;

	///@brief this method divides our matrix with a value
	///@param float value The value that we want to divide with our Matrix
	///@return Matrix3x3 It returns the pointer this with the division done
	inline Matrix3x3& operator/=(float value);

	///@brief this method compares our Matrix3x3 with other
	///@param Matrix3x3 other The Matrix that we want to compare with ours
	///@return bool Returns true if its equal and false if its not
	bool operator==(const Matrix3x3& other) const;

	///@brief this method compares our Matrix3x3 with other
	///@param Matrix3x3 other The Matrix that we want to compare with ours
	///@return bool Returns true if its not equal and false if it is
	bool operator!=(const Matrix3x3& other) const;

	///@brief this method equals our matrix with other
	///@param Matrix3x3 other The Matrix that we want to match ours
	inline void operator=(const Matrix3x3& other);

	///@brief this method resets the values of our Matrix3x3
	void reset();
	float m[9];
};

inline Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
	float aux[9];

	aux[0] = m[0] + other.m[0];
	aux[1] = m[1] + other.m[1];
	aux[2] = m[2] + other.m[2];
	aux[3] = m[3] + other.m[3];
	aux[4] = m[4] + other.m[4];
	aux[5] = m[5] + other.m[5];
	aux[6] = m[6] + other.m[6];
	aux[7] = m[7] + other.m[7];
	aux[8] = m[8] + other.m[8];

	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) {
	m[0] += other.m[0];
	m[1] += other.m[1];
	m[2] += other.m[2];
	m[3] += other.m[3];
	m[4] += other.m[4];
	m[5] += other.m[5];
	m[6] += other.m[6];
	m[7] += other.m[7];
	m[8] += other.m[8];

	return *this;
}

inline Matrix3x3 Matrix3x3::operator+(float value) const {
	float aux[9];

	aux[0] = m[0] + value;
	aux[1] = m[1] + value;
	aux[2] = m[2] + value;
	aux[3] = m[3] + value;
	aux[4] = m[4] + value;
	aux[5] = m[5] + value;
	aux[6] = m[6] + value;
	aux[7] = m[7] + value;
	aux[8] = m[8] + value;

	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator+=(float value) {
	m[0] += value;
	m[1] += value;
	m[2] += value;
	m[3] += value;
	m[4] += value;
	m[5] += value;
	m[6] += value;
	m[7] += value;
	m[8] += value;

	return *this;
}

inline Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
	float aux[9];

	aux[0] = m[0] - other.m[0];
	aux[1] = m[1] - other.m[1];
	aux[2] = m[2] - other.m[2];
	aux[3] = m[3] - other.m[3];
	aux[4] = m[4] - other.m[4];
	aux[5] = m[5] - other.m[5];
	aux[6] = m[6] - other.m[6];
	aux[7] = m[7] - other.m[7];
	aux[8] = m[8] - other.m[8];

	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) {
	m[0] -= other.m[0];
	m[1] -= other.m[1];
	m[2] -= other.m[2];
	m[3] -= other.m[3];
	m[4] -= other.m[4];
	m[5] -= other.m[5];
	m[6] -= other.m[6];
	m[7] -= other.m[7];
	m[8] -= other.m[8];

	return *this;
}

inline Matrix3x3 Matrix3x3::operator-(float value) const {
	float aux[9];

	aux[0] = m[0] - value;
	aux[1] = m[1] - value;
	aux[2] = m[2] - value;
	aux[3] = m[3] - value;
	aux[4] = m[4] - value;
	aux[5] = m[5] - value;
	aux[6] = m[6] - value;
	aux[7] = m[7] - value;
	aux[8] = m[8] - value;

	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator-=(float value) {
	m[0] -= value;
	m[1] -= value;
	m[2] -= value;
	m[3] -= value;
	m[4] -= value;
	m[5] -= value;
	m[6] -= value;
	m[7] -= value;
	m[8] -= value;

	return *this;
}

inline Matrix3x3 Matrix3x3::operator*(float value) const {
	float aux[9];

	aux[0] = m[0] * value;
	aux[1] = m[1] * value;
	aux[2] = m[2] * value;
	aux[3] = m[3] * value;
	aux[4] = m[4] * value;
	aux[5] = m[5] * value;
	aux[6] = m[6] * value;
	aux[7] = m[7] * value;
	aux[8] = m[8] * value;

	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator*=(float value) { 
	m[0] *= value;
	m[1] *= value;
	m[2] *= value;
	m[3] *= value;
	m[4] *= value;
	m[5] *= value;
	m[6] *= value;
	m[7] *= value;
	m[8] *= value;

	return *this;
}

inline Matrix3x3 Matrix3x3::operator/(float value) const {
	float aux[9];

	aux[0] = m[0] / value;
	aux[1] = m[1] / value;
	aux[2] = m[2] / value;
	aux[3] = m[3] / value;
	aux[4] = m[4] / value;
	aux[5] = m[5] / value;
	aux[6] = m[6] / value;
	aux[7] = m[7] / value;
	aux[8] = m[8] / value;

	return Matrix3x3(aux);
}

inline Matrix3x3& Matrix3x3::operator/=(float value) {
	m[0] /= value;
	m[1] /= value;
	m[2] /= value;
	m[3] /= value;
	m[4] /= value;
	m[5] /= value;
	m[6] /= value;
	m[7] /= value;
	m[8] /= value;

	return *this;
}

inline bool Matrix3x3::operator==(const Matrix3x3& other) const {
	return (m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2]
			&& m[3] == other.m[3] && m[4] == other.m[4] && m[5] == other.m[5]
			&& m[6] == other.m[6] && m[7] == other.m[7] && m[8] == other.m[8]);
}

inline bool Matrix3x3::operator!=(const Matrix3x3& other) const {
	return (m[0] != other.m[0] && m[1] != other.m[1] && m[2] != other.m[2]
			&& m[3] != other.m[3] && m[4] != other.m[4] && m[5] != other.m[5]
			&& m[6] != other.m[6] && m[7] != other.m[7] && m[8] != other.m[8]);
}

inline void Matrix3x3::operator=(const Matrix3x3& other) {
	m[0] = other.m[0];	m[1] = other.m[1]; m[2] = other.m[2];
	m[3] = other.m[3];	m[4] = other.m[4]; m[5] = other.m[5];
	m[6] = other.m[6];	m[7] = other.m[7]; m[8] = other.m[8];
}

inline Matrix3x3 Matrix3x3::Identity(){
	float aux[9]= { 1.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f,
									0.0f, 0.0f ,1.0f};
	
	return Matrix3x3(aux);
}

inline float Matrix3x3::Determinant() const {
	return ((m[0]*m[4]*m[8])+(m[3]*m[7]*m[2])+(m[1]*m[6]*m[5])) - ((m[6]*m[4]*m[2]) + (m[1]*m[3]*m[8]) + (m[5]*m[7]*m[0]));
}

inline bool Matrix3x3::GetInverse(Matrix3x3& out) const {
	if(Determinant()==0){
		return false;
	}
  
  float inverse_determinant;
  Matrix3x3 aux;

  inverse_determinant = 1 / this->Determinant();
  aux = this->Adjoint().Transpose();

	for(int i=0;i<9;i++){
		out.m[i] = aux.m[i]*inverse_determinant;
	}
	return true;
}

inline bool Matrix3x3::Inverse() {
  
  float inverse_determinant;
  Matrix3x3 aux;
  
  if(Determinant()==0){
		return false;
	}

  inverse_determinant = 1 / this->Determinant();
  aux = this->Adjoint().Transpose();

	for(int i=0;i<9;i++){
		this->m[i] = aux.m[i]*inverse_determinant;
	}
	return true;
}

inline Matrix3x3 Matrix3x3::Translate(const Vector2& mov_vector) {	
	Matrix3x3 aux;
	aux.m[0]=1.0f;aux.m[3]=0.0f;aux.m[6]=mov_vector.x;
	aux.m[1]=0.0f;aux.m[4]=1.0f;aux.m[7]=mov_vector.y;
	aux.m[2]=0.0f;aux.m[5]=0.0f;aux.m[8]=1.0f;

	return aux;
}

inline Matrix3x3 Matrix3x3::Translate(float x, float y) {
	Matrix3x3 aux;
	aux.m[0]=1.0f;aux.m[3]=0.0f;aux.m[6]=x;
	aux.m[1]=0.0f;aux.m[4]=1.0f;aux.m[7]=y;
	aux.m[2]=0.0f;aux.m[5]=0.0f;aux.m[8]=1.0f;
	return aux;
}

inline Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& other) const {
	Matrix3x3 aux;
	aux.m[0] = (m[0]*other.m[0]+m[1]*other.m[3]+m[2]*other.m[6]);
	aux.m[1] = (m[0]*other.m[1]+m[1]*other.m[4]+m[2]*other.m[7]);
	aux.m[2] = (m[0]*other.m[2]+m[1]*other.m[5]+m[2]*other.m[8]);

	aux.m[3] = (m[3]*other.m[0]+m[4]*other.m[3]+m[5]*other.m[6]);
	aux.m[4] = (m[3]*other.m[1]+m[4]*other.m[4]+m[5]*other.m[7]);
	aux.m[5] = (m[3]*other.m[2]+m[4]*other.m[5]+m[5]*other.m[8]);

	aux.m[6] = (m[6]*other.m[0]+m[7]*other.m[3]+m[8]*other.m[6]);
	aux.m[7] = (m[6]*other.m[1]+m[7]*other.m[4]+m[8]*other.m[7]);
	aux.m[8] = (m[6]*other.m[2]+m[7]*other.m[5]+m[8]*other.m[8]);

	return Matrix3x3(aux);
}

inline Matrix3x3 Matrix3x3::Adjoint() const {
	Matrix3x3 aux;
	
	aux.m[0] = Matrix2x2(m[4], m[5], m[7], m[8]).Determinant();

	aux.m[1] = Matrix2x2(m[3], m[5], m[6], m[8]).Determinant() * -1;

	aux.m[2] = Matrix2x2(m[3], m[4], m[6], m[7]).Determinant();

	aux.m[3] = Matrix2x2(m[1], m[2], m[7], m[8]).Determinant() * -1;

	aux.m[4] = Matrix2x2(m[0], m[2], m[6], m[8]).Determinant();

	aux.m[5] = Matrix2x2(m[0], m[1], m[6], m[7]).Determinant() * -1;

	aux.m[6] = Matrix2x2(m[1], m[2], m[4], m[5]).Determinant();

	aux.m[7] = Matrix2x2(m[0], m[2], m[3], m[5]).Determinant() * -1;

	aux.m[8] = Matrix2x2(m[0], m[1], m[3], m[4]).Determinant();

	return aux;
}

inline Matrix3x3 Matrix3x3::Transpose() const {
	Matrix3x3 aux;

	aux.m[0] = m[0];	aux.m[3]=m[1];  aux.m[6]=m[2];
	aux.m[1] = m[3];	aux.m[4]=m[4];  aux.m[7]=m[5];
	aux.m[2] = m[6];	aux.m[5]=m[7];  aux.m[8]=m[8];
	return Matrix3x3(aux);
}

inline Vector3 Matrix3x3::GetColum(int colum) const {
	Vector3 v;
	
	if(colum == 0){
		v.x = m[0];
		v.y = m[1];
		v.z = m[2];
	}else if(colum == 1){
		v.x = m[3];
		v.y = m[4];
		v.z = m[5];
	}else if(colum == 2){
		v.x = m[6];
		v.y = m[7];
		v.z = m[8];
	}

	return Vector3(v);
}

inline Vector3 Matrix3x3::GetLine(int line) const {
	Vector3 v;

	if(line == 0){
		v.x = m[0];
		v.y = m[3];
		v.z = m[6];
	}else if(line == 1){
		v.x = m[1];
		v.y = m[4];
		v.z = m[7];
	}else if(line == 2){
		v.x = m[2];
		v.y = m[5];
		v.z = m[8];
	}
	return Vector3(v);
}
#endif 