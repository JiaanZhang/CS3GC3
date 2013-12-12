#include "Objects.h"

class ObjectsList
{
public:
    vector<Objects> listObject;
    
    // Origin
    int orgX;
    int orgY;
    int orgZ;
    point3D origin;
    
    // Constructor
    ObjectsList(int x, int y, int z);
    ObjectsList();
    // Methods
    void newObject(int o, int m, bool isSelect);
    void updatePosition();
    void clearObjects();
};
