#ifndef GLMATH_H
# define GLMATH_H

namespace glmath{

class vec2 {
private:

public:
    float x;
    float y;

	vec2(float x);
	vec2(float x, float y);
	vec2(const vec2& copy);
	vec2& operator=(const vec2& copy);
	vec2 operator+(const vec2& copy) const;
	vec2 operator-(const vec2& copy) const;
	vec2 operator*(const vec2& copy) const;
};

}

#endif