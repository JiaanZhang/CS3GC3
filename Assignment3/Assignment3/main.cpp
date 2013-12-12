/*
 3GC3 Assignment 3
 Due: December 2, 2013
 
 File: main.cpp
 
 Wenqiang Chen - 1155437
 Brandon Da Silva - 1057434
 
 */
#include <stdlib.h>
#include <stdio.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "ObjectsList.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>

#include <time.h>

#define ESCAPE 27
#define SPACEBAR 32

using namespace std;

//ray structure which consist of an origin point and a direction
struct Ray{
	point3D origin;
	vec3D direction;
};

//define the mouse ray
Ray ray;

//object list to hold all the drawn object
ObjectsList object;

//vector to hold all the distance of object to origin
vector<float> distances;

//define the math library
_3DMath math;

// Global variables for screen size
int screenSizeX = 900;
int screenSizeY = 900;
bool lightSource0 =true;
bool lightSource1 =false;

//selection of the current drawing material
int currentMaterial = 1;

// Boolean values determining whether the program is paused
static bool paused = false;

// CAMERA PROPERTIES
// Camera position
// More camera properties for moving it
float xPos = 0;
float yPos = 0;
float zPos = 0;
float xRot = 0;
float yRot = 0;
float zRot = 0;
float lastX, lastY;

//initial position of camera
float camPos[] = {150, 150, 150};

//initial position of two light source
float light0_pos[] = {50, 50, 50,1};
float light1_pos[] = {-40, 40, -40,1};


// Fuctions used in this class
void reset();
void camera(void);

// The tabletop
void tableTop();

//boolean to toggle on and off the camera mode
static bool cameraToggle = false;

// DIFFERENT MATERIAL TYPES STRUCTURES
struct materialStruct {
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float emission[4];
    float shininess;
} materialStruct;

// Red plastic material for table top
struct materialStruct redPlastic = {
    {0.3, 0.0, 0.0, 1.0},
    {0.6, 0.0, 0.0, 1.0},
    {0.8, 0.6, 0.6, 1.0},
    {0.0, 0.0, 0.0, 0.0},
    32.0
};
// Green plastic -- DEFAULT (1)
struct materialStruct greenPlastic = {
    {0.0, 0.3, 0.0, 1.0},
    {0.0, 0.6, 0.0, 1.0},
    {0.6, 0.8, 0.6, 1.0},
    {0.0, 0.0, 0.0, 0.0},
    32.0
};
// Yellow plastic (2)
struct materialStruct yellowPlastic = {
    {0.3, 0.3, 0.0, 1.0},
    {0.6, 0.6, 0.0, 1.0},
    {0.8, 0.8, 0.6, 1.0},
    {0.0, 0.0, 0.0, 0.0},
    32.0
};
// Purple plastice material (3)
struct materialStruct purplePlastic = {
    {0.3, 0.0, 0.3, 1.0},
    {0.6, 0.0, 0.6, 1.0},
    {0.8, 0.6, 0.8, 1.0},
    {0.0, 0.0, 0.0, 0.0},
    32.0
};
// Gold material (4)
struct materialStruct goldMat = {
    {0.33, 0.22, 0.03, 1.0},
    {0.78, 0.57, 0.11, 1.0},
    {0.99, 0.91, 0.81, 1.0},
    {0.0, 0.0, 0.0, 0.0},
    27.8
};
// Silver material (5)
struct materialStruct silverMat = {
    {0.5, 0.5, 0.5, 1.0},
    {0.6, 0.6, 0.6, 1.0},
    {0.6, 0.6, 0.6, 1.0},
    {0.2, 0.2, 0.2, 0.0},
    35.0
};

//initialize the lighting and etc
void init(void) {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//light source 0
	float light0_amb[4] = { 0.0, 0.0, 0.0, 1.0};
	float light0_diff[4] = {1.0, 1.0, 1.0, 1.0};
	float light0_spec[4] = {1.0, 1.0, 1.0, 1.0};
    
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    
	//light source 1
	float light1_amb[4] = {0.0, 0.0, 0.0, 1.0};
	float light1_diff[4] = {1.0, 1.0, 1.0, 1.0};
	float light1_spec[4] = {1.0, 1.0, 1.0, 1.0};
    
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_spec);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    
	glMatrixMode(GL_PROJECTION);
    
}

//draw and update light source 1
void light1() {
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silverMat.ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, silverMat.diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, silverMat.specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, silverMat.emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, silverMat.shininess);
    glTranslated(light1_pos[0], light1_pos[1], light1_pos[2]);
    glutSolidSphere(5, 10, 5);
    glPopMatrix();
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
}

//draw and update light source 0
void light0() {
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, goldMat.ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, goldMat.diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, goldMat.specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, goldMat.emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, goldMat.shininess);
    glTranslated(light0_pos[0], light0_pos[1], light0_pos[2]);
    glutSolidSphere(5, 10, 5);
    glPopMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
}

//function that write the current state of the program and all drawn shapes to a text file
void writeFile(){
	ofstream myfile;
	myfile.open ("preference.txt");
    
	//write preference
    myfile <<xPos;
	myfile <<" "<<yPos;
	myfile <<" "<<zPos;
	myfile <<" "<<xRot;
	myfile <<" "<<yRot;
	myfile <<" "<<zRot;
	myfile <<" "<<lastX;
	myfile <<" "<<lastY;
	myfile <<" "<<cameraToggle;
	myfile <<" "<<light0_pos[0];
	myfile <<" "<<light0_pos[1];
	myfile <<" "<<light0_pos[2];
	myfile <<" "<<light1_pos[0];
	myfile <<" "<<light1_pos[1];
	myfile <<" "<<light1_pos[2]<<"\n";
    
	//write each shape
	for (unsigned int i=0; i<object.listObject.size();i++){
		Objects temp = object.listObject.at(i);
		myfile <<temp.position.x<< " " << temp.position.y << " " << temp.position.z;
		myfile << " "<<temp.objType;
		myfile << " "<<temp.matType;
		myfile << " "<<temp.size;
		myfile << " "<<temp.wireSize;
		myfile << " "<<temp.rotationAngle.x<< " " << temp.rotationAngle.y << " " << temp.rotationAngle.z;
		myfile << " "<<temp.boundI.x<< " " << temp.boundI.y << " " << temp.boundI.z;
	    myfile << " "<<temp.boundF.x<< " " << temp.boundF.y << " " << temp.boundF.z;
		myfile << " "<<temp.isSelected << "\n";
	}
	myfile.close();
}

//function that read from the file and load the state as well as all the drawn shapes back to the list
//tokenizer code is from google
void readFile(){
	reset(); //reset the corrent scene and data
	string s;
	ifstream myReadFile ("preference.txt");
	bool readPref=true;
	if (myReadFile.is_open()) {
		//read file line by line
		while (!myReadFile.eof()) {
			getline(myReadFile,s);
			string str = "This is a string";
			istringstream buf(s);
			istream_iterator<std::string> beg(buf), end;
			//tokenize the line by space and store in "tokens" list
			vector<string> tokens(beg, end);
			//int array to store preference line
			int pref[15];
			//int array to store properties of each shape
			int shape[17];
			//populate pref array and shape array
			for(unsigned int i=0; i<tokens.size();i++){
				int value;
				istringstream buffer(tokens.at(i));
				buffer >> value;
				if (tokens.size()==15){
					pref[i]=value;
				}else{
					shape[i]=value;
				}
			}
			//load the preference
			if (readPref){
				xPos=pref[0];
				yPos=pref[1];
				zPos=pref[2];
				xRot=pref[3];
				yRot=pref[4];
				zRot=pref[5];
				lastX=pref[6];
				lastY=pref[7];
				cameraToggle=pref[8];
				light0_pos[0] = pref[9];
				light0_pos[1] = pref[10];
				light0_pos[2] = pref[11];
				light1_pos[0] = pref[12];
				light1_pos[1] = pref[13];
				light1_pos[2] = pref[14];
			}else{
				//load shapes
				Objects temp;
				temp.position.x=shape[0];
				temp.position.y=shape[1];
				temp.position.z=shape[2];
				temp.objType = shape[3];
				temp.matType = shape[4];
				temp.size = shape[5];
				temp.wireSize = shape[6];
				temp.rotationAngle.x=shape[7];
				temp.rotationAngle.y=shape[8];
				temp.rotationAngle.z=shape[9];
				temp.boundI.x=shape[10];
				temp.boundI.y=shape[11];
				temp.boundI.z=shape[12];
				temp.boundF.x=shape[13];
				temp.boundF.y=shape[14];
				temp.boundF.z=shape[15];
				temp.isSelected = shape[16];
				object.listObject.push_back(temp);
			}
			readPref=false;
		}
	}
	myReadFile.close();
	//pop one element back because the last line is empty and one extra element will be added
	object.listObject.pop_back();
}

//function to draw the ground plane
void tableTop() {
    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, redPlastic.ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redPlastic.diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, redPlastic.specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, redPlastic.emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, redPlastic.shininess);
    // Front
    glVertex3f(-80, -1, 80);
    glVertex3f(80, -1, 80);
    glVertex3f(80, 1, 80);
    glVertex3f(-80, 1, 80);
    
    // Top
    glVertex3f(-80,1,80);
    glVertex3f(80,1,80);
    glVertex3f(80,1,-80);
    glVertex3f(-80,1,-80);
    
    // Bottom
    glVertex3f(-80,-1,80);
    glVertex3f(80,-1,80);
    glVertex3f(80,-1,-80);
    glVertex3f(-80,-1,-80);
    
    // Left side
    glVertex3f(-80,1,80);
    glVertex3f(-80,-1,80);
    glVertex3f(-80,-1,-80);
    glVertex3f(-80,1,-80);
    
    // Right side
    glVertex3f(80,1,80);
    glVertex3f(80,-1,80);
    glVertex3f(80,-1,-80);
    glVertex3f(80,1,-80);
    
    // Back side
    glVertex3f(-80,1,-80);
    glVertex3f(-80,-1,-80);
    glVertex3f(80,-1,-80);
    glVertex3f(80,1,-80);
    glEnd();
}

//function that takes a ray and a plane and returns the point that the ray intercepts the plane
point3D getIntercept(Ray ray, Plane plane){
	//formula to find t
	float t = (math.dotProduct(math.vectorMultiply(plane.normal,-1),ray.origin) + plane.d) / math.dotProduct(plane.normal,ray.direction);
	//find intercept by r0+t*rd
	point3D intercept = math.movePoint(ray.origin, math.vectorMultiply(ray.direction,t));
	return intercept;
}

//function that loops through the list and makes every shape unselected
void unSelect(){
	for (unsigned int i=0; i<object.listObject.size();i++){
		object.listObject.at(i).isSelected=false;
	}
}

//function that takes three point and return a plane
Plane getPlane(point3D p1, point3D p2, point3D p3){
	Plane plane;
	//generate two vector
	vec3D v1 = math.createVector(p1,p2);
	vec3D v2 = math.createVector(p1,p3);
	//generate normal of the two vector
	vec3D normal = math.normalize(math.crossProduct(v1,v2));
	plane.normal=math.vectorMultiply(normal,-1);
	plane.d= -normal.x*p1.x - normal.y*p1.y-normal.z*p1.z;
	return plane;
}

// Displays everything
void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
    glColor3f(1,1,1);
    
    //rotate the scene
    camera();
    
    //update light
    light0();
    light1();
    
    //redraw ground plane
    tableTop();
    
    //draw each shape
    if (object.listObject.size()!= 0) {
        for (unsigned int i=0; i <object.listObject.size();i++){
        	Objects temp=object.listObject.at(i);
        	glPushMatrix();
            //translate each shape
            glTranslatef(temp.position.x, temp.position.y + temp.size/2, temp.position.z);
            
            //sets the drawing material
            if (temp.matType == 1) {
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, greenPlastic.ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greenPlastic.diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, greenPlastic.specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenPlastic.emission);
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, greenPlastic.shininess);
            } else if (temp.matType == 2) {
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellowPlastic.ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellowPlastic.diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, yellowPlastic.specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellowPlastic.emission);
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, yellowPlastic.shininess);
            } else if (temp.matType == 3) {
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, purplePlastic.ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, purplePlastic.diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, purplePlastic.specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, purplePlastic.emission);
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, purplePlastic.shininess);
            } else if (temp.matType == 4) {
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, goldMat.ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, goldMat.diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, goldMat.specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, goldMat.emission);
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, goldMat.shininess);
            } else if (temp.matType == 5) {
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silverMat.ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, silverMat.diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, silverMat.specular);
                glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, silverMat.emission);
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, silverMat.shininess);
            }
            //draw current shape and rotate
            glPushMatrix();
            glRotatef(temp.rotationAngle.x, 1.0, 0.0, 0.0);
            glRotatef(temp.rotationAngle.y, 0.0, 1.0, 0.0);
            glRotatef(temp.rotationAngle.z, 0.0, 0.0, 1.0);
            if (temp.objType == 1) {
                glutSolidCube(temp.size);
            } else if (temp.objType == 2) {
                glutSolidSphere(temp.size / 2, temp.size, temp.size);
            } else if (temp.objType == 3) {
                glutSolidTeapot(temp.size);
            } else if (temp.objType == 4) {
                glutSolidCone(temp.size / 2, temp.size, temp.size, temp.size);
            } else if (temp.objType == 5) {
                glutSolidTorus(temp.size / 3, temp.size, 10, temp.size);
            }
            glPopMatrix();
            //draw wireframe cube
            if (temp.isSelected) {
                glColor3f(0,1,0);
                glutWireCube(temp.wireSize);
            }
        	glPopMatrix();
        }
    }
    //swap buffer
    glutSwapBuffers();
    glutPostRedisplay();
}

//function that checks if a point is within two other point
bool checkBound(point3D p, point3D bound1, point3D bound2, float size){
	return (p.x<=bound2.x && p.x >= bound1.x && p.y<=bound2.y && p.y>=bound1.y-size && p.z <=bound2.z && p.z>=bound1.z);
}

//function that return the minimum distance of a ray to a shape
//compares all 6 plane and return the minimum distance
//if ray does not intercept the box then -1 is returned
float getDistance(Ray ray, Objects shape){
	Plane planes[6];
	//top
	planes[0] = getPlane(shape.boundI, point3D(shape.boundF.x,shape.boundI.y,shape.boundI.z), point3D(shape.boundI.x,shape.boundI.y,shape.boundF.z));
	//bottom
	planes[1] = getPlane(point3D(shape.boundI.x,shape.boundI.y-shape.wireSize,shape.boundI.z), point3D(shape.boundF.x,shape.boundF.y-shape.wireSize,shape.boundF.z), point3D(shape.boundI.x+shape.wireSize,shape.boundI.y-shape.wireSize,shape.boundI.z));
	//left
	planes[2] = getPlane(shape.boundI, point3D(shape.boundI.x,shape.boundF.y,shape.boundF.z), point3D(shape.boundI.x,shape.boundI.y-shape.wireSize,shape.boundI.z));
	//right
	planes[3] = getPlane(point3D(shape.boundF.x,shape.boundI.y,shape.boundI.z), point3D(shape.boundF.x,shape.boundI.y,shape.boundF.z), point3D(shape.boundF.x,shape.boundI.y-shape.wireSize,shape.boundI.z));
	//front
	planes[4] = getPlane(shape.boundI, point3D(shape.boundF.x,shape.boundI.y,shape.boundI.z), point3D(shape.boundI.x,shape.boundI.y-shape.wireSize,shape.boundI.z));
	//back
	planes[5] = getPlane(shape.boundF, point3D(shape.boundF.x,shape.boundI.y-shape.wireSize,shape.boundF.z), point3D(shape.boundI.x,shape.boundI.y-shape.wireSize,shape.boundF.z));
	float min = -1;
	//check all 6 plane
	for (int i=0; i<6;i++){
		if (checkBound(getIntercept(ray,planes[i]),shape.boundI,shape.boundF,shape.wireSize)){
			if (min>math.distance(ray.origin,getIntercept(ray,planes[i])) || min<0){
				min=math.distance(ray.origin,getIntercept(ray,planes[i]));
			}
		}
	}
	return min;
}

//function that checks if ray hits a sphere and return the distance
int raySphere(point3D center, Ray ray){
	int t0=0;
	int t1=0;
	float a = math.dotProduct(ray.direction,ray.direction);
	float b = 2 * math.dotProduct(math.createVector(center,ray.origin),ray.direction);
	float c = math.dotProduct(math.createVector(ray.origin,center),math.createVector(ray.origin,center))-25;
	//check if ray hits
	if ((b*b-4*a*c) < 0){
		return -1; //ray missed
	}else{// compute both t
		t0=(-b+sqrt(b*b-4*a*c))/(2*a);
		t1=(-b-sqrt(b*b-4*a*c))/(2*a);
	}
	//finds both intercept
	point3D intercept1 = math.movePoint(ray.origin, math.vectorMultiply(ray.direction,t0));
	point3D intercept2 = math.movePoint(ray.origin, math.vectorMultiply(ray.direction,t1));
	//finds both distance
	int d1=math.distance(ray.origin,intercept1);
	int d2=math.distance(ray.origin,intercept2);
	//return the shorter distance
	if (d1<d2){
		return d1;
	}else{
		return d2;
	}
}

//function that allows mouse to rotate the scene
//code found online
void mouseMotion(int x, int y) {
    if (cameraToggle) {
        int diffX = x - lastX;
        int diffY = y - lastY;
        
        lastX = x;
        lastY = y;
        
        xRot += ((float) diffY) / 2;
        yRot += ((float) diffX) / 2;
    }
}

// Camera function to rotate
void camera(void) {
	glRotatef(xRot, 1.0, 0.0, 0.0);  // Rotate about the x-axis
	glRotatef(yRot, 0.0, 1.0, 0.0);  // Rotate about the y-axis
	glRotatef(zRot, 0.0, 0.0, 1.0);  // Rotate about the z-axis
	glTranslated(-xPos, -yPos, -zPos);
    
}

// Keyboard function
void keyboard(unsigned char key, int x, int y) {
    
    // Quits the program
    if (key == ESCAPE || key == 'q' || key == 'Q') {
        exit(0);
    }
    
    // Toggles whether the program is paused or not
    if (key == SPACEBAR) {
        paused = !paused;
        if (paused) {
            printf("PAUSED\n");
        } else {
            printf("RESUME\n");
        }
    }
    
    // Resets the array and screen (camera)
    if (key == 'r' || key == 'R') {
        reset();
    }
    
    if (!paused) {
    	//select the other light source
    	if (key == 'y' || key == 'Y') {
    	    lightSource0 = !lightSource0;
    	    lightSource1 = !lightSource1;
    	}
    	//move light to front
    	if (key == 't' || key == 'T') {
    	    if (lightSource0) {
    	        light0_pos[2] -= 2;
    	    } else {
    	        light1_pos[2] -= 2;
    	    }
    	}
    	//move light to back
    	if (key == 'g' || key == 'G') {
            if (lightSource0) {
                light0_pos[2] += 2;
            } else {
                light1_pos[2] += 2;
            }
    	}
    	//move light to right
    	if (key == 'h' || key == 'H') {
    	    if (lightSource0) {
    	        light0_pos[0] += 2;
    	    } else {
                light1_pos[0] += 2;
    	    }
    	}
    	//move light to left
    	if (key == 'f' || key == 'F') {
    	    if (lightSource0) {
    	        light0_pos[0] -= 2;
    	    } else {
                light1_pos[0] -= 2;
    	    }
    	}
    	//decrease light height
    	if (key == '6') {
    	    if (lightSource0) {
    	        light0_pos[1] -= 2;
    	    } else {
    	        light1_pos[1] -= 2;
    	    }
    	}
    	//increase light height
    	if (key == '7') {
    	    if (lightSource0) {
    	        light0_pos[1] += 2;
    	    } else {
    	        light1_pos[1] += 2;
    	    }
    	}
        
        // Adding a new object
    	//cube
        if (key == '!') {
        	object.newObject(1,currentMaterial, true);
        	unSelect();
        	object.listObject.at(object.listObject.size()-1).isSelected=true;
        }
        //sphere
        if (key =='@'){
        	object.newObject(2,currentMaterial, true);
        	unSelect();
            object.listObject.at(object.listObject.size()-1).isSelected=true;
        }
        //teapot
        if (key == '#'){
        	object.newObject(3,currentMaterial, true);
        	object.listObject.at(object.listObject.size()-1).wireSize*=2;
        	unSelect();
            object.listObject.at(object.listObject.size()-1).isSelected=true;
        }
        //cone
        if (key == '$'){
        	object.newObject(4,currentMaterial, true);
        	unSelect();
            object.listObject.at(object.listObject.size()-1).isSelected=true;
        }
        //ring
        if (key == '%'){
        	object.newObject(5,currentMaterial, true);
        	object.listObject.at(object.listObject.size()-1).wireSize*=2;
        	unSelect();
            object.listObject.at(object.listObject.size()-1).isSelected=true;
        }
        
        // change current material
        if (key == '1') {
            currentMaterial = 1;
        }
        if (key == '2') {
            currentMaterial = 2;
        }
        if (key == '3') {
            currentMaterial = 3;
        }
        if (key == '4') {
            currentMaterial = 4;
        }
        if (key == '5') {
            currentMaterial = 5;
        }
        
        // Save the current scene to a text file
        if (key == 'x' || key == 'X') {
            writeFile();
        }
        
        // Load a saved scene from a text file
        if (key == 'c' || key == 'C') {
            readFile();
        }
        
        // Increase and decrease selected object size
        // Increase
        if (key == '+') {
            // RAY CAST TO DETERMINE WHICH OBJECT TO MANIPULATE
            // THEN APPLY SIZE CHANGE i.e. object->i->size++ or something like that
        	for (unsigned int i=0; i< object.listObject.size();i++){
        		if (object.listObject.at(i).isSelected){
        			object.listObject.at(i).size+=1;
        			object.listObject.at(i).wireSize+=1;
        			object.listObject.at(i).updateBound();
        		}
        	}
            
        }
        // Decrease
        if (key == '-') {
        	for (unsigned int i=0; i< object.listObject.size();i++){
                if (object.listObject.at(i).isSelected){
                    object.listObject.at(i).size-=1;
                    object.listObject.at(i).wireSize-=1;
                    object.listObject.at(i).updateBound();
        	    }
        	}
            
        }
        
        // APPLYING MATERIAL
        if (key == 'm' || key == 'M') {
        	for (unsigned int i=0; i< object.listObject.size();i++){
        	    if (object.listObject.at(i).isSelected){
        	        object.listObject.at(i).matType=currentMaterial;
        	    }
        	}
        }
    }
    
    //rotate scene or hold shift to rotate object
    //rotate about y axis
    if (key == 'd' || key == 'D') {
    	if (glutGetModifiers()==GLUT_ACTIVE_SHIFT){
    		for (unsigned int i=0; i< object.listObject.size();i++){
    		    if (object.listObject.at(i).isSelected){
    		        object.listObject.at(i).rotationAngle.x+=1.2;
    		    }
    		}
    	}else{
    		yRot += 1.2;
    		if (yRot > 360) {
    			yRot -= 360;
    		}
    	}
    }
    // Rotate about the y-axis
    if (key == 'a' || key == 'A') {
    	if (glutGetModifiers()==GLUT_ACTIVE_SHIFT){
    	    for (unsigned int i=0; i< object.listObject.size();i++){
    	    	if (object.listObject.at(i).isSelected){
    	    		object.listObject.at(i).rotationAngle.x-=1.2;
    	    	}
    	    }
    	}else{
    	    yRot -= 1.2;
    	    if (yRot < -360) {
    	    	yRot += 360;
    	    }
    	}
    }
    
    // Rotate about the z-axis
    if (key == 'w' || key == 'W') {
    	if (glutGetModifiers()==GLUT_ACTIVE_SHIFT){
    	    for (unsigned int i=0; i< object.listObject.size();i++){
                if (object.listObject.at(i).isSelected){
                    object.listObject.at(i).rotationAngle.z+=1.2;
                }
    	    }
    	}else{
    		zRot += 1.2;
    		if (zRot > 360) {
    			zRot -= 360;
    		}
    	}
    }
    // Rotate about the z-axis
    if (key == 's' || key == 'S') {
    	if (glutGetModifiers()==GLUT_ACTIVE_SHIFT){
    	    for (unsigned int i=0; i< object.listObject.size();i++){
    	    	if (object.listObject.at(i).isSelected){
    	    	    object.listObject.at(i).rotationAngle.z-=1.2;
    	    	}
    	    }
    	}else{
    		zRot -= 1.2;
    		if (zRot < -360) {
    			zRot += 360;
    		}
    	}
    }
    
    // TOGGLES CAMERA CONTROLS
    if (key == 'z' || key == 'Z') {
        cameraToggle = !cameraToggle;
        if (cameraToggle) {
            printf("CAMERA ON\n");
        } else {
            printf("CAMERA OFF\n");
        }
    }
    
    //move camera around
    if (cameraToggle) {
        if (key == 'i' || key == 'I') {
            float xRotRad = (xRot / 180 * M_PI);
            float yRotRad = (yRot / 180 * M_PI);
            xPos += (float(sin(yRotRad))) * 2;
            yPos -= (float(sin(xRotRad))) * 2;
            zPos -= (float(cos(yRotRad))) * 2;
        }
        if (key == 'k' || key == 'K') {
            float xRotRad = (xRot / 180 * M_PI);
            float yRotRad = (yRot / 180 * M_PI);
            xPos -= (float(sin(yRotRad))) * 2;
            yPos += (float(sin(xRotRad))) * 2;
            zPos += (float(cos(yRotRad))) * 2;
        }
        if (key == 'j' || key == 'J') {
            float yRotRad = (yRot / 180 * M_PI);
            xPos -= float(cos(yRotRad)) * 2;
            zPos -= float(sin(yRotRad)) * 2;
        }
        if (key == 'l' || key == 'L') {
            float yRotRad = (yRot / 180 * M_PI);
            xPos += float(cos(yRotRad)) * 2;
            zPos += float(sin(yRotRad)) * 2;
        }
    }
}


//special key function to transform the object
void special(int key, int x, int y)
{
	//change the position of the selected object
	for (unsigned int i=0; i<object.listObject.size();i++){
		if (object.listObject.at(i).isSelected){
			switch(key){
				case GLUT_KEY_LEFT:
					object.listObject.at(i).position.x--;
					break;
				case GLUT_KEY_RIGHT:
					object.listObject.at(i).position.x++;
					break;
				case GLUT_KEY_UP:
					object.listObject.at(i).position.z--;
					break;
				case GLUT_KEY_DOWN:
					object.listObject.at(i).position.z++;
					break;
			}
			object.listObject.at(i).updateBound();
		}
	}
    
}

// Resets the scene
void reset() {
    xPos = 0;
    yPos = 0;
    zPos = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    object.listObject.clear();
    distances.clear();
    light0_pos[0] = 50;
    light0_pos[1] = 50;
    light0_pos[2] = 50;
    light1_pos[0] = -40;
    light1_pos[1] = 40;
    light1_pos[2] = -40;
    lightSource0 = true;
    lightSource1 = false;
}

// Reshape function
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
}

// Idle function
void idle() {
    glutPostRedisplay();
}

// Timer function
void timer(int msec) {
    if (paused == false) {
        
    }
    glutPostRedisplay();
    glutTimerFunc(50, timer, 0);
}

//function that takes a mouse coordinate and sets the ray
void getRay(int x, int y)
{
	//set properties
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY;
    GLdouble posX, posY, posZ;
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    //point in near plane and far plane
    point3D pNear;
    point3D pFar;
    //get window x and y coordinate
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    //unproject the 2d coordinate to 3d
    gluUnProject( winX, winY, 0.0, modelview, projection, viewport, &posX, &posY, &posZ);
    pNear=point3D(posX,posY,posZ);
    gluUnProject( winX, winY, 1.0, modelview, projection, viewport, &posX, &posY, &posZ);
    pFar= point3D(posX, posY, posZ);
    
    //sets origin to be the current camera location
    //code found online
    ray.origin.x=-(modelview[0] * modelview[12] + modelview[1] * modelview[13] + modelview[2] * modelview[14]);
    ray.origin.y=-(modelview[4] * modelview[12] + modelview[5] * modelview[13] + modelview[6] * modelview[14]);
    ray.origin.z=-(modelview[8] * modelview[12] + modelview[9] * modelview[13] + modelview[10] * modelview[14]);
    //sets direction
    ray.direction.x=pFar.x -pNear.x;
    ray.direction.y=pFar.y -pNear.y;
    ray.direction.z=pFar.z -pNear.z;
    ray.direction = math.normalize(ray.direction);
}

//function that loops through the distance list and return a tuple of the index for the
//shortest distance (-1 is not available) and the distance at that location
int* getMin(){
	float min = -1;
	int index=-1;
	//loops through whole list for the min distance
	for (unsigned int i=0; i<distances.size();i++){
		if ((min>distances.at(i) && distances.at(i)!=-1) || min<0){
			min=distances.at(i);
			index=i;
		}
	}
	//declare the tuple
	int ind[2];
	//if there is no interception then return (-1,min)
	if (min<0){
		ind[0]=-1;
		ind[1]=min;
	}else{ // if min exist then return (index,min)
		ind[0]=index;
		ind[1]=min;
	}
	return ind;
    
}

//mouse function to cast the ray
void onMouseButton(int button, int state, int x, int y)
{
	//clear distances list every time a new ray is casted
	distances.clear();
	//set the ray
	getRay(x,y);
	//get the distance from origin to every object
	for (unsigned int i=0; i<object.listObject.size();i++){
		distances.push_back(getDistance(ray,object.listObject.at(i)));
	}
	//unselect all drawn shape
	unSelect();
	//check if ray hits the light source (for selection)
	float light0 = raySphere(point3D(light0_pos[0],light0_pos[1],light0_pos[2]),ray);
	float light1 = raySphere(point3D(light1_pos[0],light1_pos[1],light1_pos[2]),ray);
	//if ray hits a object
	if (getMin()[0]!=-1){
		//check if ray hits light source before the object
		if ((getMin()[1]>light0 &&light0!=-1)|| (getMin()[1]>light1 &&light1!=-1)){
			//select appropriate light source
			if (light0!=-1 && light1!=-1){
				if (light0<light1){
					lightSource0=true;
					lightSource1=false;
				}else{
					lightSource0=false;
					lightSource1=true;
				}
			}else if(light0==-1 && light1!=-1){
				lightSource0=false;
				lightSource1=true;
			}else if (light0!=-1 && light1==-1){
				lightSource0=true;
				lightSource1=false;
			}
		}else{//if ray didn't hit light source before object
			if (button == GLUT_LEFT_BUTTON){ //select object if lift click
				int i=getMin()[0];
				object.listObject.at(i).isSelected=true;
			}else if (button == GLUT_RIGHT_BUTTON && GLUT_DOWN == state){ // delete object if right click
				int i=getMin()[0];
				object.listObject.erase(object.listObject.begin()+i);
			}
		}
	}else{//if ray does not hit object
		//select appropriate light source
		if (light0!=-1 && light1!=-1){
			if (light0<light1){
				lightSource0=true;
				lightSource1=false;
			}else{
				lightSource0=false;
				lightSource1=true;
			}
		}else if(light0==-1 && light1!=-1){
			lightSource0=false;
			lightSource1=true;
		}else if (light0!=-1 && light1==-1){
			lightSource0=true;
			lightSource1=false;
		}
	}
    glutPostRedisplay();
}


// Text instructions printed to console
void consoleText() {
    printf("This is our Simple Modeler\nBelow are a list of commands to use this program");
    printf("Commands\n\n");
    printf("%-12s %-70s\n", " 'w' 's'  --", "Move camera about z-axis");
    printf("%-12s %-70s\n", " 'a' 'd'  --", "Move camera about y-axis");
    printf("%-12s %-70s\n", " 'SPACE'  --", "Pauses the program");
    printf("%-12s %-70s\n", " 'ESC'/'q'--", "Terminates the program");
    printf("%-12s %-70s\n", " 'r'      --", "Resets the program");
    printf("%-12s %-70s\n", " 'm'      --", "Apply the material to the object the mouse is over");
    printf("%-12s %-70s\n", " 'x'      --", "Saving the current scene to a text file");
    printf("%-12s %-70s\n", " 'c'      --", "Loads a previously saved scene");
    printf("%-12s %-70s\n", " shift + 1--", "Draw a cube");
    printf("%-12s %-70s\n", " shift + 2--", "Draw a sphere");
    printf("%-12s %-70s\n", " shift + 3--", "Draw a teapot");
    printf("%-12s %-70s\n", " shift + 4--", "Draw a cone");
    printf("%-12s %-70s\n", " shift + 5--", "Draw a torus");
    printf("%-12s %-70s\n", " '1'      --", "Change material to greenPlastic");
    printf("%-12s %-70s\n", " '2'      --", "Change material to yellowPlastic");
    printf("%-12s %-70s\n", " '3'      --", "Change material to purplePlastic");
    printf("%-12s %-70s\n", " '4'      --", "Change material to goldMat");
    printf("%-12s %-70s\n", " '5'      --", "Change material to silverMat");
    printf("%-12s %-70s\n", " LMB      --", "Selects an object to manipulate");
    printf("%-12s %-70s\n", " RMB      --", "Deletes an object the ray intersects");
    printf("OBJECT INTERACTION\n");
    printf("%-12s %-70s\n", " '+/-'    --", "Increase/decrease size");
    printf("%-12s %-70s\n", " 'shift + w' 'shift + s'  --", "Move object about z-axis");
    printf("%-12s %-70s\n", " 'shift + a' 'shift + d'  --", "Move object about x-axis");
    printf("%-12s %-70s\n", " 'up' 'down'  --", "Move object about z-axis");
    printf("%-12s %-70s\n", " 'left' 'right'  --", "Move object about x-axis");
    printf("LIGHT SOURCE CONTROLS\n");
    printf("%-12s %-70s\n", " 'y'      --", "Toggle which light to manipulate");
    printf("%-12s %-70s\n", " 't' 'g'  --", "Move selected light along x-axis");
    printf("%-12s %-70s\n", " 'f' 'h'  --", "Move selected light along z-axis");
    printf("%-12s %-70s\n", " '6' '7'  --", "Move selected light along y-axis");
    printf("CAMERA CONTROLS (extra)\n");
    printf("%-12s %-70s\n", " 'z'      --", "Toggle extra camera movement feature");
    printf("%-12s %-70s\n", " 'i' 'k'  --", "Move camera forward and backward");
    printf("%-12s %-70s\n", " 'j' 'l'  --", "Move camera left and right");
    printf("%-12s %-70s\n", " mouse    --", "Mouse movement to control direction of camera through space");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);  // starts up GLUT
    
    glutInitWindowPosition(400, 0);
    glutInitWindowSize(screenSizeX, screenSizeY);
    glutCreateWindow("Simple Modeler");  // creates window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    srand(time(NULL));
    
    // Enable Z buffer test, otherwise things appear in the order drawn
    glEnable(GL_DEPTH_TEST);
    
    // Display program instructions
    consoleText();
    object = ObjectsList(0, 2, 0);
    
    // Set initial view, change to project matrix mode, and set the extents of the viewing volume
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, 1, 1, 500);
    glMatrixMode(GL_MODELVIEW);
    
    glutTimerFunc(50, timer, 0);
    
    // Enable culling
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    
    // GLUT functions
    glutDisplayFunc(display);
	glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutMouseFunc(onMouseButton);
    glutMotionFunc(mouseMotion);
    init();
    
    glutMainLoop();
    
    return(0);  // May not be necessary on all compilers
}
