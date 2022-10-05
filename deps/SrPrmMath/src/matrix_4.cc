///@Author Adrian Rivera Luna
#include <matrix_4.h>

Matrix4x4::Matrix4x4() {
    m[0] = 1.0f;   m[1] = 0.0f;  m[2] = 0.0f;  m[3] = 0.0f;
    m[4] = 0.0f;   m[5] = 1.0f;  m[6] = 0.0f;  m[7] = 0.0f;
    m[8] = 0.0f;   m[9] = 0.0f;  m[10] = 1.0f; m[11] = 0.0f;
    m[12] = 0.0f;  m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
}

Matrix4x4::Matrix4x4(float array[16]) {
    m[0] = array[0];    m[1] = array[1];   m[2] = array[2];   m[3] = array[3];
    m[4] = array[4];    m[5] = array[5];   m[6] = array[6];   m[7] = array[7];
    m[8] = array[8];    m[9] = array[9];   m[10] = array[10]; m[11] = array[11];
    m[12] = array[12];  m[13] = array[13]; m[14] = array[14]; m[15] = array[15];
}

Matrix4x4::Matrix4x4(float value) {
	m[0] = value;   m[1] = value;  m[2] = value;  m[3] = value;
  m[4] = value;   m[5] = value;  m[6] = value;  m[7] = value;
  m[8] = value;   m[9] = value;  m[10] = value; m[11] = value;
  m[12] = value;  m[13] = value; m[14] = value; m[15] = value;
}

Matrix4x4::Matrix4x4(const Matrix4x4& copy) {
	m[0] = copy.m[0];    m[1] = copy.m[1];     m[2] = copy.m[2];     m[3] = copy.m[3];
  m[4] = copy.m[4];    m[5] = copy.m[5];     m[6] = copy.m[6];     m[7] = copy.m[7];
  m[8] = copy.m[8];    m[9] = copy.m[9];     m[10] = copy.m[10];   m[11] = copy.m[11];
  m[12] = copy.m[12];  m[13] = copy.m[13];   m[14] = copy.m[14];   m[15] = copy.m[15];
}

void Matrix4x4::reset(){
    m[0] = 0.0f;   m[1] = 0.0f;  m[2] = 0.0f;  m[3] = 0.0f;
    m[4] = 0.0f;   m[5] = 0.0f;  m[6] = 0.0f;  m[7] = 0.0f;
    m[8] = 0.0f;   m[9] = 0.0f;  m[10] = 0.0f; m[11] = 0.0f;
    m[12] = 0.0f;  m[13] = 0.0f; m[14] = 0.0f; m[15] = 0.0f;
}

Matrix4x4::~Matrix4x4() {

}