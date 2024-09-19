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


// class vec3

glmath::vec3::vec3(float x)
	: x(x), y(x), z(x) {};

glmath::vec3::vec3(float x, float y, float z)
	: x(x), y(y), z(z) {};

glmath::vec3::vec3(const vec3& copy)
	: x(copy.x), y(copy.y), z(copy.z) {};

glmath::vec3& glmath::vec3::operator=(const glmath::vec3& copy) {
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	return *this;
}

glmath::vec3 glmath::vec3::operator+(const vec3& copy) const {
	return glmath::vec3(this->x + copy.x, this->y + copy.y, this->z + copy.z);
}

glmath::vec3 glmath::vec3::operator-(const vec3& copy) const{
	return glmath::vec3(this->x - copy.x, this->y - copy.y, this->z - copy.z);
}

glmath::vec3 glmath::vec3::operator*(const vec3& copy) const{
	return glmath::vec3(this->x * copy.x, this->y * copy.y, this->z * copy.z);
}


// class vec4

glmath::vec4::vec4(float x)
	: x(x), y(x), z(x), w(x) {};

glmath::vec4::vec4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w) {};

glmath::vec4::vec4(const vec4& copy)
	: x(copy.x), y(copy.y), z(copy.z), w(copy.w) {};

glmath::vec4& glmath::vec4::operator=(const glmath::vec4& copy) {
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	this->w = copy.w;
	return *this;
}

glmath::vec4 glmath::vec4::operator+(const vec4& copy) const {
	return glmath::vec4(this->x + copy.x, this->y + copy.y, this->z + copy.z, this->w + copy.w);
}

glmath::vec4 glmath::vec4::operator-(const vec4& copy) const{
	return glmath::vec4(this->x - copy.x, this->y - copy.y, this->z - copy.z, this->w - copy.w);
}

glmath::vec4 glmath::vec4::operator*(const vec4& copy) const{
	return glmath::vec4(this->x * copy.x, this->y * copy.y, this->z * copy.z, this->w * copy.w);
}
