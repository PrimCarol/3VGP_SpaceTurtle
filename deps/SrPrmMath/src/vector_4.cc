//@author Joel Salas Martos salasmar@esat-alumni.com
#include <vector_4.h>

Vector4::Vector4() { 
    x = 0; 
    y = 0; 
    z = 0; 
    w = 0; 
}

Vector4::Vector4(float x, float y, float z, float w) {
    this->x = x; 
    this->y = y; 
    this->z = z; 
    this->w = w; 
}

Vector4::Vector4(Vector3 a, float w) {
    this->x = a.x;     
    this->y = a.y; 
    this->z = a.z; 
    this->w = w; 
}

Vector4::Vector4(float a) {
    this->x = a; 
    this->y = a; 
    this->z = a; 
    this->w = a; 
}

Vector4::Vector4(float* values_array) {
    this->x = values_array[0];
    this->y = values_array[1];
    this->z = values_array[2];
    this->w = values_array[3];  
}

Vector4::Vector4(const Vector4& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;  
}

Vector4::~Vector4() { 
    //Nothing now
}


const Vector4 Vector4::one = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4 Vector4::zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);