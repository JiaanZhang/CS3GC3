#include "ObjectsList.h"

// Creates each new object in the list
ObjectsList::ObjectsList(int x, int y, int z) {
    orgX = x;
    orgY = y;
    orgZ = z;
    origin = point3D(orgX, orgY, orgZ);
}
ObjectsList::ObjectsList(){
}

// Creates a new object
void ObjectsList::newObject(int o,int m, bool isSelect) {
    Objects objects = Objects(origin, o, m, isSelect);
    
    listObject.push_back(objects);
}

// Clears the shapes in the array
void ObjectsList::clearObjects() {
    listObject.clear();
}
