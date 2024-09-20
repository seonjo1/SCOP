#ifndef GLMATH_H
# define GLMATH_H

# include <stdexcept>
# include <cmath>

namespace glmath{

constexpr float pi = 3.14159f;

class vec2 {
private:

public:
	float x;
	float y;

	vec2();
	vec2(float x);
	vec2(float x, float y);
	vec2(const vec2& copy);
	vec2& operator=(const vec2& copy);
	vec2 operator+(const vec2& rhs) const;
	vec2 operator-(const vec2& rhs) const;
	vec2 operator*(const vec2& rhs) const;
	float& operator[](int idx);
	float operator[](int idx) const;
};

class vec3 {
private:

public:
	float x;
	float y;
	float z;

	vec3();
	vec3(float x);
	vec3(float x, float y, float z);
	vec3(const vec3& copy);
	vec3& operator=(const vec3& copy);
	vec3 operator+(const vec3& rhs) const;
	vec3 operator-(const vec3& rhs) const;
	vec3 operator*(const vec3& rhs) const;
	float& operator[](int idx);
	float operator[](int idx) const;
};

class vec4 {
private:

public:
	float x;
	float y;
	float z;
	float w;

	vec4();
	vec4(float x);
	vec4(float x, float y, float z, float w);
	vec4(const vec4& copy);
	vec4& operator=(const vec4& copy);
	vec4 operator+(const vec4& rhs) const;
	vec4 operator-(const vec4& rhs) const;
	vec4 operator*(const vec4& rhs) const;
	float& operator[](int idx);
	float operator[](int idx) const;
};

class mat4 {
private:

public:
	vec4 data[4];

	mat4();
	mat4(float x);
	mat4(const vec4& c1, const vec4& c2, const vec4& c3, const vec4& c4);
	mat4(const mat4& copy);
	mat4& operator=(const mat4& copy);
	mat4 operator+(const mat4& rhs) const;
	mat4 operator-(const mat4& rhs) const;
	mat4 operator*(const mat4& rhs) const;
	vec4& operator[](int idx);
	vec4 operator[](int idx) const;
};

vec2 operator*(float scalar, const vec2& vector);
vec2 operator*(const vec2& vector, float scalar);

vec3 operator*(float scalar, const vec3& vector);
vec3 operator*(const vec3& vector, float scalar);

vec4 operator*(float scalar, const vec4& vector);
vec4 operator*(const vec4& vector, float scalar);
vec4 operator*(const mat4& matrix, const vec4& vector);

mat4 operator*(float scalar, const mat4& matrix);
mat4 operator*(const mat4& matrix, float scalar);

float* value_ptr(vec2& vector);
float* value_ptr(vec3& vector);
float* value_ptr(vec4& vector);
float* value_ptr(mat4& matrix);

float dot(const vec2& vector1, const vec2& vector2);
float dot(const vec3& vector1, const vec3& vector2);
float dot(const vec4& vector1, const vec4& vector2);

vec3 cross(const vec3& vector1, const vec3& vector2);

vec2 normalize(const vec2& vector);
vec3 normalize(const vec3& vector);
vec4 normalize(const vec4& vector);

float radians(float degree);

}


#endif