#include "Objects.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

float generateFloat(float first, float second) {
	return ((second - first) * ((float)rand() / RAND_MAX)) + first;
}

int Objects::randObjectSize() {
    int lowVal = 4;
    int highVal = 10;
    return rand() % (highVal - lowVal) + lowVal;
}

void Objects::updateBound(){
	boundI.x = position.x-(wireSize)/2;
	boundI.y = position.y+(wireSize)/2;
    boundI.z = position.z-(wireSize)/2;
	boundF.x = boundI.x+(wireSize);
	boundF.y = boundI.y;
	boundF.z = boundI.z+(wireSize+3);
}
// Constructor
// Creates shape properties
Objects::Objects(point3D startingPt, int o, int m, bool isSelect) {
    position = startingPt;
    
    objType = o;
    matType =m;
    size = 10;
    wireSize=size+3;
    
    rotationAngle = vec3D(0, 0, 0);
    boundI.x = position.x-(wireSize)/2;
    boundI.y = position.y+(wireSize)/2;
    boundI.z = position.z-(wireSize)/2;
    boundF.x = boundI.x+(wireSize);
    boundF.y = boundI.y;
    boundF.z = boundI.z+(wireSize+3);
    
    isSelected = isSelect;
}
Objects::Objects(){
    
}
