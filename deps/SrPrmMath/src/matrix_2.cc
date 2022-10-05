///@Author Adrián Rivera Luna

#include <matrix_2.h>

Matrix2x2::Matrix2x2() {
	m[0] = 0.0f;	m[1] = 0.0f;
	m[2] = 0.0f;    m[3] = 0.0f;
}

void Matrix2x2::reset(){
	m[0] = 0.0f;	m[1] = 0.0f;
	m[2] = 0.0f;    m[3] = 0.0f;
}

Matrix2x2::Matrix2x2(float a[4]) {
	m[0] = a[0];
	m[1] = a[1];
	m[2] = a[2];
	m[3] = a[3];
}

Matrix2x2::Matrix2x2(float a, float b, float c, float d) {
	m[0] = a;
	m[1] = b;
	m[2] = c;
	m[3] = d;
}

Matrix2x2::Matrix2x2(float a) {
	m[0] = a;
	m[1] = a;
	m[2] = a;
	m[3] = a;
}

/*Matrix2x2::Matrix2x2(const Vector2& a, const Vector2& b) {
	m[0] = a.x;		m[1] = b.x;
	m[2] = a.y;		m[3] = b.y;
}*/

Matrix2x2::Matrix2x2(const Matrix2x2& copy) {
	m[0] = copy.m[0];		
	m[1] = copy.m[1];
	m[2] = copy.m[2];
	m[3] = copy.m[3];
}

Matrix2x2::~Matrix2x2() { }