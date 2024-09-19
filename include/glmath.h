#ifndef GLMATH_H
# define GLMATH_H

# include <stdexcept>

namespace glmath{

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

}

#endif