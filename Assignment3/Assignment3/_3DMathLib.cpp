#include "_3DMathLib.h"
#include <math.h>

point3D::point3D(){
	x = 0;
	y = 0;
    z = 0;
}
point3D::point3D(float newX, float newY, float newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}

Plane::Plane(){
}

vec3D::vec3D(){
	x = 0;
	y = 0;
    z = 0;
    magnitude = 0;
}

vec3D::vec3D(float newX, float newY, float newZ){
	x = newX;
	y = newY;
    z = newZ;
    magnitude = 0;
}

color::color()
{
    r = 0;
    g = 0;
    b = 0;
}

color::color(float newR, float newG, float newB)
{
    r = newR;
    g = newG;
    b = newB;
}

float _3DMath::distance (point3D p1, point3D p2)
{
    float d;
    d = sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) + (p2.z - p1.z)*(p2.z - p1.z));
    return d;
};

float _3DMath::fastDistance (point3D p1, point3D p2)
{
    return (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) + (p2.z - p1.z)*(p2.z - p1.z);
};

float _3DMath::length (vec3D vector)
{
    double vectorLength;
    vectorLength = sqrt((vector.x)*(vector.x) + (vector.y)*(vector.y) + (vector.z)*(vector.z));
    vector.magnitude = vectorLength;
    return vectorLength;
};

vec3D _3DMath::normalize (vec3D newVector)
{
    vec3D normalize;
    normalize.x = newVector.x/length(newVector);
    normalize.y = newVector.y/length(newVector);
    normalize.z = newVector.z/length(newVector);
    return normalize;
};

vec3D _3DMath::crossProduct(vec3D v1, vec3D v2){
	return vec3D(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);
}
float _3DMath::dotProduct(vec3D v1, vec3D v2){
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}
float _3DMath::dotProduct(vec3D v1, point3D v2){
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

vec3D _3DMath::vectorMultiply (vec3D vector, float s)
{
    vec3D scalar;
    scalar.x = s * vector.x;
    scalar.y = s * vector.y;
    scalar.z = s * vector.z;
    return scalar;
};

vec3D _3DMath::createVector (point3D p1, point3D p2)
{
    vec3D createVector;
    createVector.x = p2.x - p1.x;
    createVector.y = p2.y - p1.y;
    createVector.z = p2.z - p1.z;
    return createVector;
};

point3D _3DMath::movePoint (point3D p, vec3D vector)
{
    point3D otherVec;
    otherVec.x = vector.x + p.x;
    otherVec.y = vector.y + p.y;
    otherVec.z = vector.z + p.z;
    return otherVec;
};
