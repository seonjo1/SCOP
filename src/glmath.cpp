#include "../include/glmath.h"

// class vec2

glmath::vec2::vec2()
	: x(0.0f), y(0.0f) {};

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

glmath::vec2 glmath::vec2::operator+(const vec2& rhs) const {
	return glmath::vec2(this->x + rhs.x, this->y + rhs.y);
}

glmath::vec2 glmath::vec2::operator-(const vec2& rhs) const{
	return glmath::vec2(this->x - rhs.x, this->y - rhs.y);
}

glmath::vec2 glmath::vec2::operator*(const vec2& rhs) const{
	return glmath::vec2(this->x * rhs.x, this->y * rhs.y);
}

float& glmath::vec2::operator[](int idx){
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		default:
			throw std::out_of_range("Index out of range");
	}
}

float glmath::vec2::operator[](int idx) const{
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		default:
			throw std::out_of_range("Index out of range");
	}
}

// class vec3

glmath::vec3::vec3()
	: x(0.0f), y(0.0f), z(0.0f) {};

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

glmath::vec3 glmath::vec3::operator+(const vec3& rhs) const {
	return glmath::vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

glmath::vec3 glmath::vec3::operator-(const vec3& rhs) const{
	return glmath::vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

glmath::vec3 glmath::vec3::operator*(const vec3& rhs) const{
	return glmath::vec3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
}

float& glmath::vec3::operator[](int idx){
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		default:
			throw std::out_of_range("Index out of range");
	}
}

float glmath::vec3::operator[](int idx) const{
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		default:
			throw std::out_of_range("Index out of range");
	}
}

// class vec4

glmath::vec4::vec4()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}; 

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

glmath::vec4 glmath::vec4::operator+(const vec4& rhs) const {
	return glmath::vec4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
}

glmath::vec4 glmath::vec4::operator-(const vec4& rhs) const {
	return glmath::vec4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
}

glmath::vec4 glmath::vec4::operator*(const vec4& rhs) const {
	return glmath::vec4(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z, this->w * rhs.w);
}

float& glmath::vec4::operator[](int idx){
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		case 3:
			return this->w;
		default:
			throw std::out_of_range("Index out of range");
	}
}

float glmath::vec4::operator[](int idx) const{
	switch (idx) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		case 3:
			return this->w;
		default:
			throw std::out_of_range("Index out of range");
	}
}


// class mat4

glmath::mat4::mat4()
	: data{} {};

glmath::mat4::mat4(float x)
	: data{glmath::vec4(x, 0.0f, 0.0f, 0.0f), glmath::vec4(0.0f, x, 0.0f, 0.0f),
		glmath::vec4(0.0f, 0.0f, x, 0.0f), glmath::vec4(0.0f, 0.0f, 0.0f, x)} {};

glmath::mat4::mat4(const vec4& c1, const vec4& c2, const vec4& c3, const vec4& c4)
	: data{c1, c2, c3, c4} {};

glmath::mat4::mat4(const glmath::mat4& copy) {
	for (int i = 0; i < 4; i++) {
		(*this)[i] = copy[i];
	}
}

glmath::mat4& glmath::mat4::operator=(const mat4& copy) {
	for (int i = 0; i < 4; i++) {
		(*this)[i] = copy[i];
	}
	return *this;
}

glmath::mat4 glmath::mat4::operator+(const mat4& rhs) const {
	return glmath::mat4(glmath::vec4((*this)[0] + rhs[0]),
						glmath::vec4((*this)[1] + rhs[1]),
						glmath::vec4((*this)[2] + rhs[2]),
						glmath::vec4((*this)[3] + rhs[3]));
}

glmath::mat4 glmath::mat4::operator-(const mat4& rhs) const {
	return glmath::mat4(glmath::vec4((*this)[0] - rhs[0]),
						glmath::vec4((*this)[1] - rhs[1]),
						glmath::vec4((*this)[2] - rhs[2]),
						glmath::vec4((*this)[3] - rhs[3]));
}

glmath::mat4 glmath::mat4::operator*(const mat4& rhs) const {
	glmath::mat4 ret(0.0f);
	for (int i = 0; i < 4; i++) {
		ret[i] = (*this) * rhs[i];
	}
	return ret;
}

glmath::vec4& glmath::mat4::operator[](int idx) {
	if (0 <= idx && idx < 4) return this->data[idx];
	throw std::out_of_range("Index out of range");
}

glmath::vec4 glmath::mat4::operator[](int idx) const {
	if (0 <= idx && idx < 4) return this->data[idx];
	throw std::out_of_range("Index out of range");
}

// non-member operator function

glmath::vec2 glmath::operator*(float scalar, const glmath::vec2& vector) {
	return glmath::vec2(scalar * vector.x, scalar * vector.y);
}

glmath::vec2 glmath::operator*(const glmath::vec2& vector, float scalar) {
	return glmath::vec2(scalar * vector.x, scalar * vector.y);
}


glmath::vec3 glmath::operator*(float scalar, const glmath::vec3& vector) {
	return glmath::vec3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

glmath::vec3 glmath::operator*(const glmath::vec3& vector, float scalar) {
	return glmath::vec3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}


glmath::vec4 glmath::operator*(float scalar, const glmath::vec4& vector) {
	return glmath::vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
}

glmath::vec4 glmath::operator*(const glmath::vec4& vector, float scalar) {
	return glmath::vec4(scalar * vector.x, scalar * vector.y, scalar * vector.z, scalar * vector.w);
}

glmath::vec4 glmath::operator*(const glmath::mat4& matrix, const glmath::vec4& vector) {
	glmath::vec4 ret(0.0f);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret[i] += matrix[j][i] * vector[j];
		}
	}
	return ret;
}

glmath::mat4 glmath::operator*(float scalar, const glmath::mat4& matrix) {
	return glmath::mat4({scalar * matrix[0], scalar * matrix[1], scalar * matrix[2], scalar * matrix[3]});
}

glmath::mat4 glmath::operator*(const glmath::mat4& matrix, float scalar) {
	return glmath::mat4({scalar * matrix[0], scalar * matrix[1], scalar * matrix[2], scalar * matrix[3]});
}

// non-member function

float* glmath::value_ptr(vec2& vector) {
	return &vector[0];
}

float* glmath::value_ptr(vec3& vector) {
	return &vector[0];
}

float* glmath::value_ptr(vec4& vector) {
	return &vector[0];
}

float* glmath::value_ptr(mat4& matrix) {
	return &matrix[0][0];
}

float glmath::dot(const glmath::vec2& vector1, const glmath::vec2& vector2) {
	float ret = 0.0f;
	for (int i = 0; i < 2; i++) {
		ret += vector1[i] * vector2[i];
	}
	return ret;
}

float glmath::dot(const glmath::vec3& vector1, const glmath::vec3& vector2) {
	float ret = 0.0f;
	for (int i = 0; i < 3; i++) {
		ret += vector1[i] * vector2[i];
	}
	return ret;
}

float glmath::dot(const glmath::vec4& vector1, const glmath::vec4& vector2) {
	float ret = 0.0f;
	for (int i = 0; i < 4; i++) {
		ret += vector1[i] * vector2[i];
	}
	return ret;
}

glmath::vec3 glmath::cross(const glmath::vec3& vector1, const glmath::vec3& vector2) {
	return glmath::vec3(vector1.y * vector2.z - vector1.z * vector2.y,
						vector1.z * vector2.x - vector1.x * vector2.z,
						vector1.x * vector2.y - vector1.y * vector2.x);
}

glmath::vec2 glmath::normalize(const glmath::vec2& vector) {
	float magnitude = 0;
	for (int i = 0; i < 2; i++) {
		magnitude += pow(vector[i], 2); 
	}
	magnitude = sqrt(magnitude);
	return glmath::vec2(vector.x / magnitude, vector.y / magnitude);
}

glmath::vec3 glmath::normalize(const glmath::vec3& vector) {
	float magnitude = 0;
	for (int i = 0; i < 3; i++) {
		magnitude += pow(vector[i], 2); 
	}
	magnitude = sqrt(magnitude);
	return glmath::vec3(vector.x / magnitude, vector.y / magnitude, vector.z / magnitude);
}

glmath::vec4 glmath::normalize(const glmath::vec4& vector) {
	float magnitude = 0;
	for (int i = 0; i < 4; i++) {
		magnitude += pow(vector[i], 2); 
	}
	magnitude = sqrt(magnitude);
	return glmath::vec4(vector.x / magnitude, vector.y / magnitude, vector.z / magnitude, vector.w / magnitude);
}

float glmath::radians(float degree) {
    return degree * (3.14159f / 180.0f);
}

glmath::mat4 glmath::scale(const glmath::mat4& matrix, const glmath::vec3& vector) {
	glmath::mat4 scaleMatrix(glmath::vec4(vector.x, 0.0f, 0.0f, 0.0f),
							glmath::vec4(0.0f, vector.y, 0.0f, 0.0f),
							glmath::vec4(0.0f, 0.0f, vector.z, 0.0f),
							glmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	return matrix * scaleMatrix;
}

glmath::mat4 glmath::translate(const glmath::mat4& matrix, const glmath::vec3& vector) {
	glmath::mat4 translateMatrix(glmath::vec4(1.0f, 0.0f, 0.0f, 0.0f),
								glmath::vec4(0.0f, 1.0f, 0.0f, 0.0f),	
								glmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
								glmath::vec4(vector.x, vector.y, vector.z, 1.0f));
	return matrix * translateMatrix;
}
