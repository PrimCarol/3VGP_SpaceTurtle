//@author Joel Salas Martos salasmar@esat-alumni.com

#include <vector_3.h>

const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::down = Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::left = Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::forward = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::back = Vector3(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::unit = Vector3(1.0f, 1.0f, 1.0f);

Vector3::Vector3() {
  x = 0;
  y = 0; 
  z = 0;
}

Vector3::Vector3(float x, float y, float z) {
  this->x = x;
  this->y = y; 
  this->z = z;
}

Vector3::Vector3(float * values_array) {
  this->x = values_array[0];
  this->y = values_array[1];
  this->z = values_array[2];
}

Vector3::Vector3(float value) {
  this->x = value;
  this->y = value;
  this->z = value;
}

Vector3::Vector3(const Vector3& other) {
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
}

 Vector3::~Vector3() {
  //Empty 
}
