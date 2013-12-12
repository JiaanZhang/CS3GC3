#include "_3DMathLib.h"
#include <vector>
#include <iostream>
using namespace std;

class Objects
{
public:
    // Position
    point3D position;
    int size;
    
    bool isSelected;
    
    int objType;
    int matType;
    vec3D rotationAngle;
    int wireSize;
    point3D boundI;
    point3D boundF;
    
    // Constructor
    Objects(point3D p, int o,int m, bool isSelect);
    Objects();
    float generateFloat(float first, float second);
    static int randObjectSize();
    void updateBound();
};
