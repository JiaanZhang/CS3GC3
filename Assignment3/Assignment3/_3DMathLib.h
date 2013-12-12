#include <math.h>

// Defining my own pi
//#define M_PI 3.1415926535897932384626433832795

class point3D
{
public:
    float x;
    float y;
    float z;
    point3D();
    point3D(float inX, float inY, float inZ);
};

class vec3D
{
public:
    float x;
    float y;
    float z;
    float magnitude;
    vec3D();
    vec3D(float x, float y, float z);
};

class color
{
public:
    float r;
    float g;
    float b;
    color();
    color(float r, float g, float b);
};

class Plane{
public:
	vec3D normal;
	float d;
	Plane();
};


class _3DMath
{
public:
    static float distance (point3D p1, point3D p2);
    static float fastDistance (point3D p1, point3D p2);
    static float length (vec3D vector);
    static vec3D normalize (vec3D vector);
    static vec3D vectorMultiply (vec3D vector, float s);
    static vec3D createVector (point3D p1, point3D p2);
    static point3D movePoint (point3D p, vec3D vector);
    static vec3D crossProduct (vec3D v1, vec3D v2);
    static float dotProduct (vec3D v1, vec3D v2);
    static float dotProduct (vec3D v1, point3D p1);
};
