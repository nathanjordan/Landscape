//
//  object.h
//  
//
//  Created by Nick Niemann on 12/13/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _object_h
#define _object_h

//handles all openGL includes
#include "../includes/Angel.h"
#include <fstream>
#include <math.h>
#include <string.h>
#include <iostream>
#include "../kixor/objLoader.h"

using namespace std;

typedef vec4 point4;
typedef vec4 color4;
typedef vec4 normal4;

typedef vec3 point3;

typedef vec2 point2;

const int TextureSize = 2048;

struct shaderloc {
	GLuint program;
	GLuint modelLocation;
	GLuint viewLocation;
	GLuint projectionLocation;
	GLuint normalLocation;
	GLuint vertexLocation;
	GLuint ambientLocation;
	GLuint diffuseLocation;
	GLuint specularLocation;
	GLuint lightLocation;
	GLuint shininessLocation;
    
	//lighting variables
	point4 light_position;
	color4 light_ambient;
	color4 light_diffuse;
	color4 light_specular;
    
	//texture locations
	GLuint vTextCoordLocation;
	GLuint textureLocation;
    GLuint texLocation;
    
	//matrixes
	mat4 viewMatrix;
	mat4 projMatrix;
};

struct material {
    material() {
        data = NULL;
        texturized = false;
        texSize = 0;
    }
    
    ~material() {
        if (data !=NULL) {
            delete [] data;
        }
    }
    
	color4 material_ambient;
	color4 material_diffuse;
	color4 material_specular;
	float material_shininess;
    
	unsigned char *data;
    
	bool texturized;
    
    int texSize;
    
	material &operator=(const material &rhs) {
		if (this != &rhs){
			material_ambient = rhs.material_ambient;
			material_diffuse = rhs.material_diffuse;
			material_shininess = rhs.material_shininess;
			material_specular = rhs.material_specular;
            texSize = rhs.texSize;
            
            if (data != NULL) {
                delete [] data;
                data = NULL;
            }
			
            
            if (rhs.texturized) {
                data = new unsigned char [texSize*texSize*3];
                
                for(int i=0; i< texSize*texSize*3; i++)
                    data[i] = rhs.data[i];
            }
			
			texturized = rhs.texturized;
		}
		return *this;
	}
};



//global shader program
extern shaderloc program1;



struct face {
    int vertIndices[3];
    int normalIndices[3];
    face &operator=(const face& rhs) {
        if (this!= &rhs) {
            for (int i=0; i<3; i++) {
                vertIndices[i] = rhs.vertIndices[i];
                normalIndices[i] = rhs.normalIndices[i];
            }
        }
        return *this;
    }
};



class Object {
    
public:
    
	Object(bool stuff=false, int t=0, int i=-1);
	Object(const Object&);
	virtual ~Object();
	Object& operator=(const Object& right );
	void draw( shaderloc&);
	void setFaces( objLoader* loader );
	void rotate( float , float , float );
	void setColor( material&, int m );
	void updatePosition();
    void init(shaderloc &prog);
    void scale(GLfloat);
    void setScale(GLfloat);
    void rotateY(GLfloat);
    
	mat4 matTranslation;
	mat4 matRotation;
	mat4 matScale;
	mat4 matModel;
    
	point4* vertexDrawList;
	color4* colorDrawList;
	normal4* normalDrawList;
    
	vec3 vecVelocity;
	vec3 vecAcceleration;
    
	point4* vertices;
	color4* colors;
	normal4* normals;
    
	material colorAttributes;
    
	bool isConstrained;
	GLfloat constraints[4];
    
	face* faces;
	int numFaces;
    
    GLfloat angle;
    
	int numVertices;
	GLfloat height, width, depth;
    
    int type, treeIndex, materialColor;
    
protected:
    
	GLuint vao, vbo[3];
	GLuint textures[1];
    
};




#endif
