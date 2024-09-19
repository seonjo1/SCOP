#include "../include/glmath.h"

// class vec2

glmath::vec2::vec2(float x)
	: x(x), y(x) {};

glmath::vec2::vec2(float x, float y)
	: x(x), y(y) {};

glmath::vec2::vec2(const vec2& copy)
	: x(copy.x), y(copy.y) {};

glmath::vec2& glmath::vec2::operator=(const glmath::vec2& copy) {
	this->x = copy.x;
	this->y = copy.y;
	return *this;
}

glmath::vec2 glmath::vec2::operator+(const vec2& copy) const {
	return glmath::vec2(this->x + copy.x, this->y + copy.y);
}

glmath::vec2 glmath::vec2::operator-(const vec2& copy) const{
	return glmath::vec2(this->x - copy.x, this->y - copy.y);
}

glmath::vec2 glmath::vec2::operator*(const vec2& copy) const{
	return glmath::vec2(this->x * copy.x, this->y * copy.y);
}