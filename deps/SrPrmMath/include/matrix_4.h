///@author Adrian Rivera Luna

#ifndef __MATRIX4_H__
#define __MATRIX4_H__ 1

#include "math_utils.h"
#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"


class Matrix4x4{
 public:
 	///@brief this method constructs the variable when its created
  Matrix4x4();

  ///@brief this method constructs the variable when its created with the values that we pass to it
  ///@param float values_array We pass an array of floats with values to introduce into the matrix
  Matrix4x4(float a[16]);

  ///@brief this method constructs the variable when its created with the values that we pass to it
  ///@param float value We pass a float value to introduce in all the fields of the matrix
  Matrix4x4(float value);

  ///@brief this method copies an entire Matrix3x3 on the new Matrix that we are creating
	///@param Matrix3x3 copy We pass a Matrix3x3 variable to copy it
  Matrix4x4(const Matrix4x4& copy);

  ///@brief this method destroys the variable
  ~Matrix4x4();

  ///@brief this method creates a Matrix 4x4 Identity to return it
	///@return Matrix4x4 It returns the Matrix4x4 identity created.
  Matrix4x4 Identity() const;

  ///@brief this method Multiplies our Matrix with one that we pass as parameter
	///@param Matrix4x4 other The Matrix4x4 that we want to multiply
	///@return Matrix4x4 It returns the result of the multiplication.
  Matrix4x4 Multiply(const Matrix4x4& other) const;

  ///@brief this method gets the Determinant of our Matrix
	///@return float It returns the result of the Determinant function.
  float Determinant() const;

  ///@brief this method returns the result of the adjoint of our Matrix
	///@return Matrix4x4 It returns the result of the adjoint.
  Matrix4x4 Adjoint() const;

  ///@brief this method checks if it can get the inverse of the Matrix that we pass as parameter and if it cans returns the inverse
	///@param Matrix4x4 out The Matrix4x4 that we want to know the inverse
	///@return Matrix4x4 It returns the inverse.
  bool GetInverse(Matrix4x4* out) const;

  ///@brief this method obtains the inverse of our matrix and returns it
	///@return Matrix4x4 It returns the inverse.
  Matrix4x4 Inverse() const;

  ///@brief print the values inside of Matrix4x4
	void print();

	///@brief this method obtains the transpose of our matrix and returns it
	///@return Matrix4x4 It returns the transpose.
  Matrix4x4 Transpose() const;

  ///@brief This function translate the matrix
	///@param Vector3 position The position that we want to insert in the matrix
	///@return Matrix4x4 The matrix with the new position
  static Matrix4x4 Translate(const Vector3& distance);

  ///@brief This function translate the matrix
	///@param float x The position x that we want to insert in the matrix
	///@param float y The position y that we want to insert in the matrix
	///@param float z The position z that we want to insert in the matrix
	///@return Matrix4x4 The matrix with the new position
  static Matrix4x4 Translate(float x, float y, float z);

  ///@brief This function Scale the matrix
	///@param Vector3 scale The scale that we want to insert in the matrix
	///@return Matrix4x4 The matrix with the new scale
  static Matrix4x4 Scale(const Vector3& scale);

  ///@brief This function Scale the matrix
	///@param float x The Scale x that we want to insert in the matrix
	///@param float y The Scale y that we want to insert in the matrix
	///@param float z The Scale z that we want to insert in the matrix
	///@return Matrix4x4 The matrix with the new scale
  static Matrix4x4 Scale(float x, float y, float z);

  ///@brief This function Rotate the matrix in X axis 
	///@param float radiants to rotate
	///@return Matrix4x4 The matrix with the new rotation
  static Matrix4x4 RotateX(float radians);

  ///@brief This function Rotate the matrix in Y axis 
	///@param float radiants to rotate
	///@return Matrix4x4 The matrix with the new rotation
  static Matrix4x4 RotateY(float radians);

  ///@brief This function Rotate the matrix in Z axis 
	///@param float radiants to rotate
	///@return Matrix4x4 The matrix with the new rotation
  static Matrix4x4 RotateZ(float radians);

  ///@brief This function Convert the Matrix transform to Vector4 
	///@param Matrix4x4 where take the transformed matrix
	///@param Vector4 the vector with which to do the calculation 
	///@return Vector4 with transformation in vector format.
  Vector4 Mat4TransformVec4(const Matrix4x4 &a, const Vector4 &v);

  ///@brief This function Convert the Matrix transform to Vector3 
	///@param Matrix4x4 where take the transformed matrix
	///@param Vector3 the vector with which to do the calculation 
	///@return Vector3 with transformation in vector format.
	Vector3 Mat4TransformVec3(const Matrix4x4 &a, const Vector3& r);

	///@brief This function make all the Translate, Scale and Rotate in the perfect order to transform the matrix.
	///@param Vector3 the vector with the translate position.
	///@param Vector3 the vector with the scale.
	///@param float with rotation on X axis
	///@param float with rotation on Y axis
	///@param float with rotation on Z axis
	///@return Matrix4X4 with transformation.
  static Matrix4x4 GetTransform(const Vector3& translate, const Vector3& scale,
                      float rotateX, float rotateY, float rotateZ);

  ///@brief This function make all the Translate, Scale and Rotate in the perfect order to transform the matrix.
	///@param float with X position
	///@param float with Y position
	///@param float with Z position
	///@param float with X Scale
	///@param float with Y Scale
	///@param float with Z Scale
	///@param float with rotation on X axis
	///@param float with rotation on Y axis
	///@param float with rotation on Z axis
	///@return Matrix4X4 with transformation.
  static Matrix4x4 GetTransform(float trans_x, float trans_y, float trans_z,
                      float scale_x, float scale_y, float scale_Z,
                      float rotateX, float rotateY, float rotateZ);

  Matrix4x4 PerspectiveMatrix(float fov, float aspect,
	  float near, float far) const;

  Matrix4x4 OrthoMatrix(float right, float left, float top, float valueottom,
	  float near, float far) const;

  ///@brief this method returns the column of our Matrix that we want
	///@param int column The column that we want
	///@return Vector4 It returns the column.
  Vector4 GetColum(int colum) const;

  ///@brief this method returns the line of our Matrix that we want
	///@param int line The line that we want
	///@return Vector4 It returns the line.
  Vector4 GetLine(int line) const;

  ///@brief this method adds our matrix with another and returns the result
	///@param Matrix4x4 other The Matrix 4x4 that we want to add with ours
	///@return Matrix4x4 It returns the result of the sum
  Matrix4x4 operator+(const Matrix4x4& other) const;

  ///@brief this method adds our matrix with another
	///@param Matrix4x4 other The Matrix 4x4 that we want to add with ours
	///@return Matrix4x4 It returns the pointer this with the sum done
  Matrix4x4& operator+=(const Matrix4x4& other);

  ///@brief this method adds a value to our matrix and returns the result
	///@param float value The value that we want to add to the fields of our matrix
	///@return Matrix4x4 It returns the result of the sum
  Matrix4x4 operator+(float value) const;

  ///@brief this method adds a value to our matrix
	///@param float value The value that we want to add to the fields of our matrix
	///@return Matrix4x4 It returns the pointer this with the sum done
  Matrix4x4& operator+=(float value);

  ///@brief this method substracts our matrix with another and returns the result
	///@param Matrix4x4 other The Matrix4x4 that we want to subtract with ours
	///@return Matrix4x4 It returns the result of the substraction
  Matrix4x4 operator-(const Matrix4x4& other) const;

  ///@brief this method subtract a value with our matrix 
	///@param Matrix4x4 other The Matrix 4x4 that we want to substract with ours
	///@return Matrix4x4 It returns the pointer this with the substraction done
  Matrix4x4& operator-=(const Matrix4x4& other);

  ///@brief this method subtract a value with our matrix and returns the result
	///@param float value The value that we want to substract with the fields of our matrix
	///@return Matrix4x4 It returns the result of the substraction
  Matrix4x4 operator-(float value) const;

  ///@brief this method substracts a value with our matrix
	///@param float value The value that we want to substract with the fields of our matrix
	///@return Matrix4x4 It returns the pointer this with the substraction done
  Matrix4x4& operator-=(float value);

  ///@brief this method multiplies our matrix with a value
	///@param float value The value that we want to multiply with our Matrix
	///@return Matrix4x4 It returns the result of the mutiplication
  Matrix4x4 operator*(float value) const;

  ///@brief this method multiplies our matrix with a value
	///@param float value The value that we want to multiply with our Matrix
	///@return Matrix4x4 It returns the pointer this with the multiplication done
  Matrix4x4& operator*=(float value);

  ///@brief this method divides our matrix with a value
	///@param float value The value that we want to divide with our Matrix
	///@return Matrix4x4 It returns the result of the division
  Matrix4x4 operator/(float value) const;

  ///@brief this method divides our matrix with a value
	///@param float value The value that we want to divide with our Matrix
	///@return Matrix4x4 It returns the pointer this with the division done
  Matrix4x4& operator/=(float value);

  ///@brief this method compares our Matrix4x4 with other
	///@param Matrix4x4 other The Matrix that we want to compare with ours
	///@return bool Returns true if its equal and false if its not
  bool operator==(const Matrix4x4& other);

  ///@brief this method compares our Matrix4x4 with other
	///@param Matrix4x4 other The Matrix that we want to compare with ours
	///@return bool Returns true if its not equal and false if it is
  bool operator!=(const Matrix4x4& other);

  ///@brief this method equals our matrix with other
	///@param Matrix3x3 other The Matrix that we want to match ours
  void operator=(const Matrix4x4& other);

  ///@brief this method resets the values of our Matrix4x4
  void reset();
  float m[16];
};

inline Matrix4x4 Matrix4x4::Identity() const {
	Matrix4x4 aux;
	aux.m[0] = 1;aux.m[4] = 0;aux.m[8] = 0; aux.m[12] = 0;
	aux.m[1] = 0;aux.m[5] = 1;aux.m[9] = 0; aux.m[13] = 0;
	aux.m[2] = 0;aux.m[6] = 0;aux.m[10] = 1;aux.m[14] = 0;
	aux.m[3] = 0;aux.m[7] = 0;aux.m[11] = 0;aux.m[15] = 1;

	return aux;
}

inline Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& other)const  {
	Matrix4x4 aux;

	aux.m[0] = (m[0] * other.m[0] + m[1] * other.m[4] + m[2] * other.m[8] + m[3] * other.m[12]);
	aux.m[1] = (m[0] * other.m[1] + m[1] * other.m[5] + m[2] * other.m[9] + m[3] * other.m[13]);
	aux.m[2] = (m[0] * other.m[2] + m[1] * other.m[6] + m[2] * other.m[10] + m[3] * other.m[14]);
	aux.m[3] = (m[0] * other.m[3] + m[1] * other.m[7] + m[2] * other.m[11] + m[3] * other.m[15]);

	aux.m[4] = (m[4] * other.m[0] + m[5] * other.m[4] + m[6] * other.m[8] + m[7] * other.m[12]);
	aux.m[5] = (m[4] * other.m[1] + m[5] * other.m[5] + m[6] * other.m[9] + m[7] * other.m[13]);
	aux.m[6] = (m[4] * other.m[2] + m[5] * other.m[6] + m[6] * other.m[10] + m[7] * other.m[14]);
	aux.m[7] = (m[4] * other.m[3] + m[5] * other.m[7] + m[6] * other.m[11] + m[7] * other.m[15]);

	aux.m[8] = (m[8] * other.m[0] + m[9] * other.m[4] + m[10] * other.m[8] + m[11] * other.m[12]);
	aux.m[9] = (m[8] * other.m[1] + m[9] * other.m[5] + m[10] * other.m[9] + m[11] * other.m[13]);
	aux.m[10] = (m[8] * other.m[2] + m[9] * other.m[6] + m[10] * other.m[10] + m[11] * other.m[14]);
	aux.m[11] = (m[8] * other.m[3] + m[9] * other.m[7] + m[10] * other.m[11] + m[11] * other.m[15]);

	aux.m[12] = (m[12] * other.m[0] + m[13] * other.m[4] + m[14] * other.m[8] + m[15] * other.m[12]);
	aux.m[13] = (m[12] * other.m[1] + m[13] * other.m[5] + m[14] * other.m[9] + m[15] * other.m[13]);
	aux.m[14] = (m[12] * other.m[2] + m[13] * other.m[6] + m[14] * other.m[10] + m[15] * other.m[14]);
	aux.m[15] = (m[12] * other.m[3] + m[13] * other.m[7] + m[14] * other.m[11] + m[15] * other.m[15]);

	return Matrix4x4(aux);
}


inline float Matrix4x4::Determinant() const {
	Matrix3x3 aux;
	float aux_floats[4];

	aux.m[0] = this->m[5];aux.m[3] = this->m[9]; aux.m[6] = this->m[13];
	aux.m[1] = this->m[6];aux.m[4] = this->m[10];aux.m[7] = this->m[14];
	aux.m[2] = this->m[7];aux.m[5] = this->m[11];aux.m[8] = this->m[15];
	aux_floats[0] = this->m[0]*aux.Determinant();

	aux.m[0] = this->m[4];aux.m[3] = this->m[8]; aux.m[6] = this->m[12];
	aux.m[1] = this->m[6];aux.m[4] = this->m[10];aux.m[7] = this->m[14];
	aux.m[2] = this->m[7];aux.m[5] = this->m[11];aux.m[8] = this->m[15];
	aux_floats[1] = this->m[1]*aux.Determinant();

	aux.m[0] = this->m[4];aux.m[3] = this->m[8]; aux.m[6] = this->m[12];
	aux.m[1] = this->m[5];aux.m[4] = this->m[9]; aux.m[7] = this->m[13];
	aux.m[2] = this->m[7];aux.m[5] = this->m[11];aux.m[8] = this->m[15];
	aux_floats[2] = this->m[2]*aux.Determinant();

	aux.m[0] = this->m[4];aux.m[3] = this->m[8]; aux.m[6] = this->m[12];
	aux.m[1] = this->m[5];aux.m[4] = this->m[9]; aux.m[7] = this->m[13];
	aux.m[2] = this->m[6];aux.m[5] = this->m[10];aux.m[8] = this->m[14];
	aux_floats[3] = this->m[3]*aux.Determinant();

	return (aux_floats[0] - aux_floats[1] + aux_floats[2] - aux_floats[3]);
}


inline Matrix4x4 Matrix4x4::Adjoint() const {
    Matrix3x3 aux_m;
    Matrix4x4 result;
    //Adjoint matrix is the matrix formed by cofactors´s determinant
    //First Line
    aux_m.m[0] = m[5];
    aux_m.m[1] = m[6];
    aux_m.m[2] = m[7];

    aux_m.m[3] = m[9];
    aux_m.m[4] = m[10];
    aux_m.m[5] = m[11];

    aux_m.m[6] = m[13];
    aux_m.m[7] = m[14];
    aux_m.m[8] = m[15];

    result.m[0] = aux_m.Determinant();

    aux_m.m[0] = m[4];
    aux_m.m[3] = m[8];
    aux_m.m[6] = m[12];

    result.m[1] = aux_m.Determinant();

    aux_m.m[1] = m[5];
    aux_m.m[4] = m[9];
    aux_m.m[7] = m[13];

    result.m[2] = aux_m.Determinant();

    aux_m.m[2] = m[6];
    aux_m.m[5] = m[10];
    aux_m.m[8] = m[14];

    result.m[3] = aux_m.Determinant();
    //Second Line
    aux_m.m[0] = m[1];
    aux_m.m[1] = m[2];
    aux_m.m[2] = m[3];

    aux_m.m[3] = m[9];
    aux_m.m[4] = m[10];
    aux_m.m[5] = m[11];

    aux_m.m[6] = m[13];
    aux_m.m[7] = m[14];
    aux_m.m[8] = m[15];

    result.m[4] = aux_m.Determinant();

    aux_m.m[0] = m[0];
    aux_m.m[3] = m[8];
    aux_m.m[6] = m[12];

    result.m[5] = aux_m.Determinant();

    aux_m.m[1] = m[1];
    aux_m.m[4] = m[9];
    aux_m.m[7] = m[13];

    result.m[6] = aux_m.Determinant();

    aux_m.m[2] = m[2];
    aux_m.m[5] = m[10];
    aux_m.m[8] = m[14];

    result.m[7] = aux_m.Determinant();
    //Third Line
    aux_m.m[0] = m[1];
    aux_m.m[1] = m[2];
    aux_m.m[2] = m[3];

    aux_m.m[3] = m[5];
    aux_m.m[4] = m[6];
    aux_m.m[5] = m[7];

    aux_m.m[6] = m[13];
    aux_m.m[7] = m[14];
    aux_m.m[8] = m[15];

    result.m[8] = aux_m.Determinant();

    aux_m.m[0] = m[0];
    aux_m.m[3] = m[4];
    aux_m.m[6] = m[12];

    result.m[9] = aux_m.Determinant();

    aux_m.m[1] = m[1];
    aux_m.m[4] = m[5];
    aux_m.m[7] = m[13];

    result.m[10] = aux_m.Determinant();

    aux_m.m[2] = m[2];
    aux_m.m[5] = m[6];
    aux_m.m[8] = m[14];

    result.m[11] = aux_m.Determinant();
//Fourth Line
    aux_m.m[0] = m[1];
    aux_m.m[1] = m[2];
    aux_m.m[2] = m[3];

    aux_m.m[3] = m[5];
    aux_m.m[4] = m[6];
    aux_m.m[5] = m[7];

    aux_m.m[6] = m[9];
    aux_m.m[7] = m[10];
    aux_m.m[8] = m[11];

    result.m[12] = aux_m.Determinant();

    aux_m.m[0] = m[0];
    aux_m.m[3] = m[4];
    aux_m.m[6] = m[8];

    result.m[13] = aux_m.Determinant();

    aux_m.m[1] = m[1];
    aux_m.m[4] = m[5];
    aux_m.m[7] = m[9];

    result.m[14] = aux_m.Determinant();

    aux_m.m[2] = m[2];
    aux_m.m[5] = m[6];
    aux_m.m[8] = m[10];

    result.m[15] = aux_m.Determinant();


    result.m[1] = -result.m[1];
    result.m[3] = -result.m[3];
    result.m[4] = -result.m[4];
    result.m[6] = -result.m[6];
    result.m[9] = -result.m[9];
    result.m[11] = -result.m[11];
    result.m[12] = -result.m[12];
    result.m[14] = -result.m[14];


    return result;
}

inline Matrix4x4 Matrix4x4::Inverse() const {
	
	/*float inverse_determinant;
  	Matrix4x4 aux;
  
  	if(Determinant()==0){
		return false;
	}

  	inverse_determinant = 1 / this->Determinant();
  	aux = this->Adjoint().Transpose();

	for(int i=0;i<16;i++){
		this->m[i] = aux.m[i]*inverse_determinant;
	}
	return true;*/
	float inverse_determinant = 1 / this->Determinant();
	Matrix4x4 aux;
	for (unsigned char i = 0; i < 16; i++) {
		aux.m[i] = Adjoint().Transpose().m[i] / inverse_determinant;
	}

	return aux;

}

inline bool Matrix4x4::GetInverse(Matrix4x4* out) const {
	float inverse_determinant;
  
  	if(Determinant()==0){
		return false;
	}

  	inverse_determinant = 1 / this->Determinant();

	for(int i=0;i<16;i++){
		out->m[i] = Adjoint().Transpose().m[i] / inverse_determinant;
	}
	return true;
}

inline void Matrix4x4::print(){

	printf(" \n============Mat 4============");
	printf(" \n%02.2f %02.2f %02.2f %02.2f ", m[0], m[1], m[2], m[3] );
	printf(" \n%02.2f %02.2f %02.2f %02.2f ", m[4], m[5], m[6], m[7] );
	printf(" \n%02.2f %02.2f %02.2f %02.2f ", m[8], m[9], m[10], m[11] );
	printf(" \n%02.2f %02.2f %02.2f %02.2f ", m[12], m[13], m[14], m[15] );
	printf(" \n============Mat 4============\n");

}

inline Matrix4x4 Matrix4x4::Transpose() const {
	Matrix4x4 aux;
	aux.m[0] = this->m[0];
	aux.m[1] = this->m[4];
	aux.m[2] = this->m[8];
	aux.m[3] = this->m[12];

	aux.m[4] = this->m[1];
	aux.m[5] = this->m[5];
	aux.m[6] = this->m[9];
	aux.m[7] = this->m[13];

	aux.m[8] = this->m[2];
	aux.m[9] = this->m[6];
	aux.m[10] = this->m[10];
	aux.m[11] = this->m[14];

	aux.m[12] = this->m[3];
	aux.m[13] = this->m[7];
	aux.m[14] = this->m[11];
	aux.m[15] = this->m[15];

	return Matrix4x4(aux);
}

inline Matrix4x4 Matrix4x4::Translate(const Vector3& distance){
	Matrix4x4 aux;

	aux.m[0]=1.0f;
	aux.m[1]=0.0f;
	aux.m[2]=0.0f;
	aux.m[3]=0.0f;

	aux.m[4]=0.0f;
	aux.m[5]=1.0f;
	aux.m[6]=0.0f;
	aux.m[7]=0.0f;

	aux.m[8]=0.0f;
	aux.m[9]=0.0f;
	aux.m[10]=1.0f;
	aux.m[11]=0.0f;

	aux.m[12]=distance.x;
	aux.m[13]=distance.y;
	aux.m[14]=distance.z;
	aux.m[15]=1.0f;
	return Matrix4x4(aux);
}

inline Matrix4x4 Matrix4x4::Translate(float x, float y, float z){
	Matrix4x4 aux;

	aux.m[0]=1.0f;
	aux.m[1]=0.0f;
	aux.m[2]=0.0f;
	aux.m[3]=0.0f;

	aux.m[4]=0.0f;
	aux.m[5]=1.0f;
	aux.m[6]=0.0f;
	aux.m[7]=0.0f;

	aux.m[8]=0.0f;
	aux.m[9]=0.0f;
	aux.m[10]=1.0f;
	aux.m[11]=0.0f;

	aux.m[12]=x;
	aux.m[13]=y;
	aux.m[14]=z;
	aux.m[15]=1.0f;

	return Matrix4x4(aux);
}

inline Matrix4x4 Matrix4x4::Scale(const Vector3& scale){
	Matrix4x4 aux;

	aux.m[0] = scale.x;    aux.m[4] = 0.0f;			aux.m[8] = 0.0f;				aux.m[12] = 0.0f;
	aux.m[1] = 0.0f;	     aux.m[5] = scale.y;	aux.m[9] = 0.0f;				aux.m[13] = 0.0f;
	aux.m[2] = 0.0f;			 aux.m[6] = 0.0f;			aux.m[10] = scale.z;		aux.m[14] = 0.0f;
	aux.m[3] = 0.0f;			 aux.m[7] = 0.0f;			aux.m[11] = 0.0f;				aux.m[15] = 1.0f;

	return Matrix4x4(aux);
}

inline Matrix4x4 Matrix4x4::Scale(float x, float y, float z){
	Matrix4x4 aux;

	aux.m[0] = x;    	aux.m[4] = 0.0f;	aux.m[8] = 0.0f;	aux.m[12] = 0.0f;
	aux.m[1] = 0.0f;	aux.m[5] = y;			aux.m[9] = 0.0f;	aux.m[13] = 0.0f;
	aux.m[2] = 0.0f;	aux.m[6] = 0.0f;	aux.m[10] = z;		aux.m[14] = 0.0f;
	aux.m[3] = 0.0f;	aux.m[7] = 0.0f;	aux.m[11] = 0.0f;	aux.m[15] = 1.0f;

	return Matrix4x4(aux);
}

inline Matrix4x4 Matrix4x4::RotateX(float radians){
	Matrix4x4 aux;

	aux.m[0] = 1.0f;  aux.m[4] = 0.0f;						           aux.m[8] = 0.0f;							            aux.m[12] = 0.0f;
	aux.m[1] = 0.0f;  aux.m[5] = MathUtils::Cosine(radians); aux.m[9] = MathUtils::Sine(radians);		  aux.m[13] = 0.0f;
	aux.m[2] = 0.0f;  aux.m[6] =-MathUtils::Sine(radians);   aux.m[10] = MathUtils::Cosine(radians);	aux.m[14] = 0.0f;
	aux.m[3] = 0.0f;  aux.m[7] = 0.0f;						           aux.m[11] = 0.0f;							          aux.m[15] = 1.0f;

	return Matrix4x4(aux);
}

inline Matrix4x4 Matrix4x4::RotateY(float radians){
	Matrix4x4 aux;

	aux.m[0] = MathUtils::Cosine(radians);  		aux.m[4] = 0.0f;					aux.m[8] = -MathUtils::Sine(radians);				aux.m[12] = 0.0f;
	aux.m[1] = 0.0f;														aux.m[5] = 1.0f;					aux.m[9] = 0.0f;														aux.m[13] = 0.0f;
	aux.m[2] = MathUtils::Sine(radians);				aux.m[6] = 0.0f;					aux.m[10] = MathUtils::Cosine(radians);			aux.m[14] = 0.0f;
	aux.m[3] = 0.0f;														aux.m[7] = 0.0f;					aux.m[11] = 0.0f;														aux.m[15] = 1.0f;

	return Matrix4x4(aux);
}

inline Matrix4x4 Matrix4x4::RotateZ(float radians) {
	Matrix4x4 aux;

	aux.m[0] = MathUtils::Cosine(radians);  aux.m[4] = MathUtils::Sine(radians);	  aux.m[8] = 0.0f;				aux.m[12] = 0.0f;
	aux.m[1] = -MathUtils::Sine(radians);	  aux.m[5] = MathUtils::Cosine(radians);	aux.m[9] = 0.0f;				aux.m[13] = 0.0f;
	aux.m[2] = 0.0f;					              aux.m[6] = 0.0f;												aux.m[10] = 1.0f;				aux.m[14] = 0.0f;
	aux.m[3] = 0.0f;												aux.m[7] = 0.0f;										    aux.m[11] = 0.0f;				aux.m[15] = 1.0f;

	return Matrix4x4(aux);
}

inline Matrix4x4 Matrix4x4::GetTransform(const Vector3& translate,
				                                const Vector3& scale,
				                                float rotateX, float rotateY,
				                                float rotateZ){
  Matrix4x4 result;
	Matrix4x4 translation;
	Matrix4x4 scaling;
	Matrix4x4 rotation;

	// R = RX * RY * RZ
	rotation = rotation.RotateX(rotateX).Multiply(rotation.RotateY(rotateY).Multiply(rotation.RotateZ(rotateZ)));

	// MT = T * R * S
	result = translation.Translate(translate.x, translate.y, translate.z).Multiply(rotation.Multiply(scaling.Scale(scale.x, scale.y, scale.z)));	


	return result;
}

inline Matrix4x4 Matrix4x4::GetTransform(float trans_x, float trans_y, float trans_z,
																			  float scale_x, float scale_y, float scale_z,
																			  float rotateX, float rotateY, float rotateZ){
	Matrix4x4 result;
	Matrix4x4 translation;
	Matrix4x4 scaling;
	Matrix4x4 rotation;

	// R = RX * RY * RZ
	rotation = rotation.RotateX(rotateX).Multiply(rotation.RotateY(rotateY).Multiply(rotation.RotateZ(rotateZ)));

	// MT = T * R * S
	result = translation.Translate(trans_x, trans_y, trans_z).Multiply(rotation.Multiply(scaling.Scale(scale_x, scale_y, scale_z)));	

	return result;
}

inline Vector4 Matrix4x4::GetColum(int colum) const {
	Vector4 v;
	if(colum == 0){
		v.x = m[0];
		v.y = m[1];
		v.z = m[2];
		v.w = m[3];
	}else if(colum == 1){
		v.x = m[4];
		v.y = m[5];
		v.z = m[6];
		v.w = m[7];
	}else if(colum == 2){
		v.x = m[8];
		v.y = m[9];
		v.z = m[10];
		v.w = m[11];
	}else if(colum == 3){
		v.x = m[12];
		v.y = m[13];
		v.z = m[14];
		v.w = m[15];
	}
	return Vector4(v);
}

inline Vector4 Matrix4x4::GetLine(int line) const {
	Vector4 v;
	if(line == 0){
		v.x = m[0];
		v.y = m[4];
		v.z = m[8];
		v.w = m[12];
	}else if(line == 1){
		v.x = m[1];
		v.y = m[5];
		v.z = m[9];
		v.w = m[13];
	}else if(line == 2){
		v.x = m[2];
		v.y = m[6];
		v.z = m[10];
		v.w = m[14];
	}else if(line == 3){
		v.x = m[3];
		v.y = m[7];
		v.z = m[11];
		v.w = m[15];
	}
	return Vector4(v);
}

inline Matrix4x4 Matrix4x4::PerspectiveMatrix(float fov, float aspect,
	float near, float far) const {
	printf("No hace falta hacer de momento.\n");
	return Matrix4x4();
}

inline Matrix4x4 Matrix4x4::OrthoMatrix(float right, float left, float top, float valueottom,
	float near, float far) const {
	printf("No hace falta hacer de momento.\n");
	return Matrix4x4();
}

inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const {
	Matrix4x4 aux;
	aux.m[0] = this->m[0] + other.m[0];
	aux.m[1] = this->m[1] + other.m[1];
	aux.m[2] = this->m[2] + other.m[2];
	aux.m[3] = this->m[3] + other.m[3];

	aux.m[4] = this->m[4] + other.m[4];
	aux.m[5] = this->m[5] + other.m[5];
	aux.m[6] = this->m[6] + other.m[6];
	aux.m[7] = this->m[7] + other.m[7];

	aux.m[8] = this->m[8] + other.m[8];
	aux.m[9] = this->m[9] + other.m[9];
	aux.m[10] = this->m[10] + other.m[10];
	aux.m[11] = this->m[11] + other.m[11];

	aux.m[12] = this->m[12] + other.m[12];
	aux.m[13] = this->m[13] + other.m[13];
	aux.m[14] = this->m[14] + other.m[14];
	aux.m[15] = this->m[15] + other.m[15];


	return Matrix4x4(aux);
}

inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) {
	this->m[0] += other.m[0];
	this->m[1] += other.m[1];
	this->m[2] += other.m[2];
	this->m[3] += other.m[3];

	this->m[4] += other.m[4];
	this->m[5] += other.m[5];
	this->m[6] += other.m[6];
	this->m[7] += other.m[7];

	this->m[8] += other.m[8];
	this->m[9] += other.m[9];
	this->m[10] += other.m[10];
	this->m[11] += other.m[11];

	this->m[12] += other.m[12];
	this->m[13] += other.m[13];
	this->m[14] += other.m[14];
	this->m[15] += other.m[15];

	 return *this;
}

inline Matrix4x4 Matrix4x4::operator+(float value) const {
	Matrix4x4 aux;
	aux.m[0] = this->m[0] + value;
	aux.m[1] = this->m[1] + value;
	aux.m[2] = this->m[2] + value;
	aux.m[3] = this->m[3] + value;

	aux.m[4] = this->m[4] + value;
	aux.m[5] = this->m[5] + value;
	aux.m[6] = this->m[6] + value;
	aux.m[7] = this->m[7] + value;

	aux.m[8] = this->m[8] + value;
	aux.m[9] = this->m[9] + value;
	aux.m[10] = this->m[10] + value;
	aux.m[11] = this->m[11] + value;

	aux.m[12] = this->m[12] + value;
	aux.m[13] = this->m[13] + value;
	aux.m[14] = this->m[14] + value;
	aux.m[15] = this->m[15] + value;

	return Matrix4x4(aux);
}

inline Matrix4x4& Matrix4x4::operator+=(float value) {	
	this->m[0] += value;
	this->m[1] += value;
	this->m[2] += value;
	this->m[3] += value;

	this->m[4] += value;
	this->m[5] += value;
	this->m[6] += value;
	this->m[7] += value;

	this->m[8] += value;
	this->m[9] += value;
	this->m[10] += value;
	this->m[11] += value;

	this->m[12] += value;
	this->m[13] += value;
	this->m[14] += value;
	this->m[15] += value;

	 return *this;
}


inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const  {
	Matrix4x4 aux;
	aux.m[0] = this->m[0] - other.m[0];
	aux.m[1] = this->m[1] - other.m[1];
	aux.m[2] = this->m[2] - other.m[2];
	aux.m[3] = this->m[3] - other.m[3];

	aux.m[4] = this->m[4] - other.m[4];
	aux.m[5] = this->m[5] - other.m[5];
	aux.m[6] = this->m[6] - other.m[6];
	aux.m[7] = this->m[7] - other.m[7];

	aux.m[8] = this->m[8] - other.m[8];
	aux.m[9] = this->m[9] - other.m[9];
	aux.m[10] = this->m[10] - other.m[10];
	aux.m[11] = this->m[11] - other.m[11];

	aux.m[12] = this->m[12] - other.m[12];
	aux.m[13] = this->m[13] - other.m[13];
	aux.m[14] = this->m[14] - other.m[14];
	aux.m[15] = this->m[15] - other.m[15];

	return Matrix4x4(aux);
}

inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) {
	this->m[0] -= other.m[0];
	this->m[1] -= other.m[1];
	this->m[2] -= other.m[2];
	this->m[3] -= other.m[3];

	this->m[4] -= other.m[4];
	this->m[5] -= other.m[5];
	this->m[6] -= other.m[6];
	this->m[7] -= other.m[7];

	this->m[8] -= other.m[8];
	this->m[9] -= other.m[9];
	this->m[10] -= other.m[10];
	this->m[11] -= other.m[11];

	this->m[12] -= other.m[12];
	this->m[13] -= other.m[13];
	this->m[14] -= other.m[14];
	this->m[15] -= other.m[15];

	 return *this;
}

inline Matrix4x4 Matrix4x4::operator-(float value) const  {
	Matrix4x4 aux;
	aux.m[0] = this->m[0] - value;
	aux.m[1] = this->m[1] - value;
	aux.m[2] = this->m[2] - value;
	aux.m[3] = this->m[3] - value;

	aux.m[4] = this->m[4] - value;
	aux.m[5] = this->m[5] - value;
	aux.m[6] = this->m[6] - value;
	aux.m[7] = this->m[7] - value;

	aux.m[8] = this->m[8] - value;
	aux.m[9] = this->m[9] - value;
	aux.m[10] = this->m[10] - value;
	aux.m[11] = this->m[11] - value;

	aux.m[12] = this->m[12] - value;
	aux.m[13] = this->m[13] - value;
	aux.m[14] = this->m[14] - value;
	aux.m[15] = this->m[15] - value;

	return Matrix4x4(aux);
}

inline Matrix4x4& Matrix4x4::operator-=(float value) {
	this->m[0] -= value;
	this->m[1] -= value;
	this->m[2] -= value;
	this->m[3] -= value;

	this->m[4] -= value;
	this->m[5] -= value;
	this->m[6] -= value;
	this->m[7] -= value;

	this->m[8] -= value;
	this->m[9] -= value;
	this->m[10] -= value;
	this->m[11] -= value;

	this->m[12] -= value;
	this->m[13] -= value;
	this->m[14] -= value;
	this->m[15] -= value;

	return *this;
}

inline Matrix4x4& Matrix4x4::operator*=(float value) {
	this->m[0] *= value;
	this->m[1] *= value;
	this->m[2] *= value;
	this->m[3] *= value;

	this->m[4] *= value;
	this->m[5] *= value;
	this->m[6] *= value;
	this->m[7] *= value;

	this->m[8] *= value;
	this->m[9] *= value;
	this->m[10] *= value;
	this->m[11] *= value;

	this->m[12] *= value;
	this->m[13] *= value;
	this->m[14] *= value;
	this->m[15] *= value;

	return *this;
}

inline Matrix4x4 Matrix4x4::operator*(float value) const  {
	Matrix4x4 aux;

	aux.m[0] = this->m[0] * value;
	aux.m[1] = this->m[1] * value;
	aux.m[2] = this->m[2] * value;
	aux.m[3] = this->m[3] * value;

	aux.m[4] = this->m[4] * value;
	aux.m[5] = this->m[5] * value;
	aux.m[6] = this->m[6] * value;
	aux.m[7] = this->m[7] * value;

	aux.m[8] = this->m[8] * value;
	aux.m[9] = this->m[9] * value;
	aux.m[10] = this->m[10] * value;
	aux.m[11] = this->m[11] * value;

	aux.m[12] = this->m[12] * value;
	aux.m[13] = this->m[13] * value;
	aux.m[14] = this->m[14] * value;
	aux.m[15] = this->m[15] * value;

	return Matrix4x4(aux);
}

inline Matrix4x4& Matrix4x4::operator/=(float value) {
	float inverted_value = 1/value;
	this->m[0] *= inverted_value;
	this->m[1] *= inverted_value;
	this->m[2] *= inverted_value;
	this->m[3] *= inverted_value;

	this->m[4] *= inverted_value;
	this->m[5] *= inverted_value;
	this->m[6] *= inverted_value;
	this->m[7] *= inverted_value;

	this->m[8] *= inverted_value;
	this->m[9] *= inverted_value;
	this->m[10] *= inverted_value;
	this->m[11] *= inverted_value;

	this->m[12] *= inverted_value;
	this->m[13] *= inverted_value;
	this->m[14] *= inverted_value;
	this->m[15] *= inverted_value;

	return *this;
}

inline Matrix4x4 Matrix4x4::operator/(float value) const {
	Matrix4x4 aux;
	float inverted_value = 1/value;

	aux.m[0] = this->m[0] * inverted_value;
	aux.m[1] = this->m[1] * inverted_value;
	aux.m[2] = this->m[2] * inverted_value;
	aux.m[3] = this->m[3] * inverted_value;

	aux.m[4] = this->m[4] * inverted_value;
	aux.m[5] = this->m[5] * inverted_value;
	aux.m[6] = this->m[6] * inverted_value;
	aux.m[7] = this->m[7] * inverted_value;

	aux.m[8] = this->m[8] * inverted_value;
	aux.m[9] = this->m[9] * inverted_value;
	aux.m[10] = this->m[10] * inverted_value;
	aux.m[11] = this->m[11] * inverted_value;

	aux.m[12] = this->m[12] * inverted_value;
	aux.m[13] = this->m[13] * inverted_value;
	aux.m[14] = this->m[14] * inverted_value;
	aux.m[15] = this->m[15] * inverted_value;

	return Matrix4x4(aux);
}

inline bool Matrix4x4::operator==(const Matrix4x4& other) {
	return (this->GetColum(0) == other.GetColum(0) && this->GetColum(1) == other.GetColum(1) && this->GetColum(2) == other.GetColum(2) && this->GetColum(3) == other.GetColum(3));
}

inline bool Matrix4x4::operator!=(const Matrix4x4& other) {
	return (this->GetColum(0) != other.GetColum(0) || this->GetColum(1) != other.GetColum(1) || this->GetColum(2) != other.GetColum(2) || this->GetColum(3) != other.GetColum(3));
}

inline void Matrix4x4::operator=(const Matrix4x4& other) {
	this->m[0] = other.m[0];
	this->m[1] = other.m[1];
	this->m[2] = other.m[2];
	this->m[3] = other.m[3];

	this->m[4] = other.m[4];
	this->m[5] = other.m[5];
	this->m[6] = other.m[6];
	this->m[7] = other.m[7];

	this->m[8] = other.m[8];
	this->m[9] = other.m[9];
	this->m[10] = other.m[10];
	this->m[11] = other.m[11];

	this->m[12] = other.m[12];
	this->m[13] = other.m[13];
	this->m[14] = other.m[14];
	this->m[15] = other.m[15];
}

inline Vector3 Matrix4x4::Mat4TransformVec3(const Matrix4x4& a, const Vector3& r){
	Vector4 tmp;
  tmp.x = r.x;
  tmp.y = r.y;
  tmp.z = r.z;
  tmp.w = 1.0;
  Vector4 result = Mat4TransformVec4(a, tmp);
  result.x = result.x / result.w;
  result.y = result.y / result.w;
  result.z = result.z / result.w;
  Vector3 k;
  k.x = result.x;
  k.y = result.y;
  k.z = result.z;
  return k;
  
}

inline Vector4 Matrix4x4::Mat4TransformVec4(const Matrix4x4 &a, const Vector4 &v){
  Vector4 o;
  o.x = a.m[0] * v.x + a.m[4] * v.y + a.m[8]  * v.z + a.m[12] * v.w;
  o.y = a.m[1] * v.x + a.m[5] * v.y + a.m[9]  * v.z + a.m[13] * v.w;
  o.z = a.m[2] * v.x + a.m[6] * v.y + a.m[10] * v.z + a.m[14] * v.w;
  o.w = a.m[3] * v.x + a.m[7] * v.y + a.m[11] * v.z + a.m[15] * v.w;
  return o;
}
#endif