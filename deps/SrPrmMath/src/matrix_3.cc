///@Author Pere Prim Carol
#include <matrix_3.h>
#include <matrix_4.h>
#include <vector_3.h>
#include <vector_4.h>

Matrix3x3::Matrix3x3() {
	m[0] = 0.0f;		m[1] = 0.0f;		m[2] = 0.0f;
	m[3] = 0.0f;		m[4] = 0.0f;		m[5] = 0.0f;
	m[6] = 0.0f;		m[7] = 0.0f;		m[8] = 0.0f;
}

Matrix3x3::Matrix3x3(float value) {
	m[0] = value;		m[1] = value;		m[2] = value;
	m[3] = value;		m[4] = value;		m[5] = value;
	m[6] = value;		m[7] = value;		m[8] = value;
}

Matrix3x3::Matrix3x3(float *values_array) {
	m[0] = values_array[0];		m[1] = values_array[1];		m[2] = values_array[2];
	m[3] = values_array[3];		m[4] = values_array[4];		m[5] = values_array[5];
	m[6] = values_array[6];		m[7] = values_array[7];		m[8] = values_array[8];
}

Matrix3x3::Matrix3x3(Vector3 a, Vector3 b, Vector3 c) {
	m[0] = a.x;	m[1] = b.x;	m[2] = c.x;
	m[3] = a.y;	m[4] = b.y;	m[5] = c.y;
	m[6] = a.z;	m[7] = b.z;	m[8] = c.z;
}

Matrix3x3::Matrix3x3(const Matrix3x3& copy) {
	m[0] = copy.m[0];	m[1] = copy.m[1]; m[2] = copy.m[2];
	m[3] = copy.m[3];	m[4] = copy.m[4]; m[5] = copy.m[5];
	m[6] = copy.m[6];	m[7] = copy.m[7]; m[8] = copy.m[8];
}

void Matrix3x3::reset(){
	m[0] = 0.0f;		m[1] = 0.0f;		m[2] = 0.0f;
	m[3] = 0.0f;		m[4] = 0.0f;		m[5] = 0.0f;
	m[6] = 0.0f;		m[7] = 0.0f;		m[8] = 0.0f;
}
Matrix3x3::~Matrix3x3() { }
/*
Vector3 Matrix3x3::Mat4TransformVec3(const Matrix4x4 &a, const Vector3 &r){
	/*
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
  
return ;
}*/
