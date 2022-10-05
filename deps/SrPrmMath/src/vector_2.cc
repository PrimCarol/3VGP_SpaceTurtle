//@author Joel Salas Martos salasmar@esat-alumni.com
#include <vector_2.h>

const Vector2 Vector2::down = Vector2(0.0f, -1.0f);
const Vector2 Vector2::left = Vector2(-1.0f, 0.0f);
const Vector2 Vector2::one = Vector2(1.0f, 1.0f);
const Vector2 Vector2::right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::up = Vector2(0.0f, 1.0f);
const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& other) {
    x = other.x;
    y = other.y;
}

Vector2::~Vector2() {

}

