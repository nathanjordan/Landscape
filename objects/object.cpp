//
//  object.cpp
//  
//
//  Created by Nick Niemann on 12/13/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "object.h"
#include <limits>

//global shader program
shaderloc program1;



Object::Object( bool stuff, int t, int i ) {
    
    #ifdef __APPLE__  // include Mac OS X verions of headers
        glGenVertexArraysAPPLE( 1, &vao );
    #else // non-Mac OS X operating systems
        glGenVertexArrays( 1, &vao );
    #endif  // __APPLE__
	
    glGenBuffers( 3, vbo );
	glGenTextures(1, textures);
    
	type = t;
    
    treeIndex = i;
    
    
    
    colorAttributes.texturized = stuff;
     
	
    
    
    vertexDrawList = colorDrawList = normalDrawList = NULL;
    vertices = colors = normals = NULL;
    faces = NULL;
     
	numVertices = 0;
    
	numFaces = 0;
    
	width = 0;
    
	height = 0;
    
	depth = 0;
    
    angle =0;
    
	vecVelocity = vec3( 0.0 , 0.0 , 0.0 );
    
	vecAcceleration = vec3( 0.0 , 0.0 , 0.0 );
    
    
	matModel = matTranslation * matScale * matRotation;
    
}

Object::Object( const Object& right ) {
    /*
    //create new vao's and vbo's that are seperate
    
    #ifdef __APPLE__  // include Mac OS X verions of headers
        glGenVertexArraysAPPLE( 1, &vao );
    #else // non-Mac OS X operating systems
        glGenVertexArrays( 1, &vao );
    #endif  // __APPLE__
	
    
    glGenBuffers( 3, vbo );
	glGenTextures(1, textures);
    */
    
    for (int i=0; i<3; i++) {
        vbo[i] = right.vbo[i];
    }
    
    textures[0] = right.textures[0];
    
    vao = right.vao;
    
    
    type = right.type;
    treeIndex = right.treeIndex;
    materialColor = right.materialColor;
    
    
    numVertices = right.numVertices;
    
    numFaces = right.numFaces;
    
    angle = right.angle;
    
    //copy over the matrices
    this->matTranslation = right.matTranslation;
    
    this->matRotation = right.matRotation;
    
    this->matScale = right.matScale;
    
    this->matModel = right.matModel;
    
    
    faces = new face[numFaces];
    
    for( int i = 0 ; i < numFaces ; i++ ) {
        
        faces[i] = right.faces[i];
        
    }
    
    vertexDrawList = new point4[numFaces*3];
    
    colorDrawList = new point4[numFaces*3];
    
    normalDrawList = new point4[numFaces*3];
    
    
    for( int i = 0 ; i < numFaces * 3 ; i++ ) {
        
        vertexDrawList[i] = right.vertexDrawList[i];
        
        colorDrawList[i] = right.colorDrawList[i];
        
        normalDrawList[i] = right.normalDrawList[i];
        
    }
    
    vertices = new point4[numVertices];
    
    colors = new point4[numVertices];
    
    normals = new point4[numVertices];
    
    for( int i = 0 ; i < numVertices ; i++ ) {
        
        vertices[i] = right.vertices[i];
        
        colors[i] = right.colors[i];
        
        normals[i] = right.normals[i];
        
    }
    
    this->height = right.height;
    
    this->width = right.width;
    
    this->depth = right.depth;
    
    
    //copy over the material attributes, takes care of the texture
    colorAttributes = right.colorAttributes;
    
    isConstrained = right.isConstrained;
    
    for (int i=0; i<4; i++) {
        constraints[i] = right.constraints[i];
    }
    
    //ititialize the object after its been created
    init(program1);
}

Object::~Object() {
    
	if (vertices != NULL) {
        delete [] vertices;
    }
    
    if (colors != NULL) {
        delete [] colors;
    }
    
    if (normals != NULL) {
        delete [] normals;
    }
    
    if (vertexDrawList != NULL) {
        delete [] vertexDrawList;
    }
    
    if (colorDrawList != NULL) {
        delete [] colorDrawList;
    }
    
    if (normalDrawList != NULL) {
        delete [] normalDrawList;
    }
    
    if (faces != NULL) {
        delete [] faces;
    }
    
}
Object& Object::operator=( const Object& right ) {
    
    if (this != &right) {
        /*
        //create new vao's and vbo's that are seperate
        
        #ifdef __APPLE__  // include Mac OS X verions of headers
                glGenVertexArraysAPPLE( 1, &vao );
        #else // non-Mac OS X operating systems
                glGenVertexArrays( 1, &vao );
        #endif  // __APPLE__
        
        glGenBuffers( 3, vbo );
        glGenTextures(1, textures);
        
         */
         
        for (int i=0; i<3; i++) {
            vbo[i] = right.vbo[i];
        }
        
        textures[0] = right.textures[0];
        
        vao = right.vao;
        
        type = right.type;
        treeIndex = right.treeIndex;
        materialColor = right.materialColor;
        
    	numVertices = right.numVertices;
        
        numFaces = right.numFaces;
        
        angle = right.angle;
        
        this->matTranslation = right.matTranslation;
        
        this->matRotation = right.matRotation;
        
        this->matScale = right.matScale;
        
        this->matModel = right.matModel;
        
        if (faces != NULL) {
            delete [] faces;
        }
        
        faces = new face[numFaces];
        
        for( int i = 0 ; i < numFaces ; i++ ) {
            
            faces[i] = right.faces[i];
            
        }
        
        if (vertexDrawList != NULL) {
            delete [] vertexDrawList;
        }
        vertexDrawList = new point4[numFaces*3];
        
        if (colorDrawList != NULL) {
            delete [] colorDrawList;
        }
        colorDrawList = new point4[numFaces*3];
        
        if (normalDrawList != NULL) {
            delete [] normalDrawList;
        }
        normalDrawList = new point4[numFaces*3];
        
        
        for( int i = 0 ; i < numFaces * 3 ; i++ ) {
            
            vertexDrawList[i] = right.vertexDrawList[i];
            
            colorDrawList[i] = right.colorDrawList[i];
            
            normalDrawList[i] = right.normalDrawList[i];
            
        }
        
        if (vertices != NULL) {
            delete [] vertices;
        }
        vertices = new point4[numVertices];
        
        if (colors != NULL) {
            delete [] colors;
        }
        colors = new point4[numVertices];
        
        if (normals != NULL) {
            delete [] normals;
        }
        normals = new point4[numVertices];
        
        for( int i = 0 ; i < numVertices ; i++ ) {
            
            vertices[i] = right.vertices[i];
            
            colors[i] = right.colors[i];
            
            normals[i] = right.normals[i];
            
        }
        
        this->height = right.height;
        
        this->width = right.width;
        
        this->depth = right.depth;
        
        colorAttributes = right.colorAttributes;
        
        isConstrained = right.isConstrained;
        
        for (int i=0; i<4; i++) {
            constraints[i] = right.constraints[i];
        }

        //initialize the object
        init(program1);
    }
    
	return *this;
    
}

void Object::init(shaderloc &prog) {
    
    GLfloat* tempVertices = new GLfloat[ numFaces * 3 * 4];
    
    
	for( int i = 0 ; i < numFaces * 3 ; i++ ) {
        
		for( int j = 0 ; j < 4 ; j++ ) {
            
			tempVertices[i * 4 + j] = vertexDrawList[i][j];
            
        }
        
    }
    
	point2* tempTexils = new point2[numFaces * 3];
	for( int i = 0; i< numFaces * 3; i+=6) {
		tempTexils[i] = point2(0.0, 0.0);
		tempTexils[i+1] = point2(0.0, 1.0);
		tempTexils[i+2] =point2(1.0, 1.0);
		tempTexils[i+3] = point2(0.0, 0.0);
		tempTexils[i+4] = point2(1.0, 1.0);
		tempTexils[i+5] =point2(1.0, 0.0);
	}
     
    
	GLfloat* tempNormals = new GLfloat[ numFaces * 3 * 4 ];
    
    
	for( int i = 0 ; i < numFaces * 3 ; i++ ) {
        
		for( int j = 0 ; j < 4 ; j++ ) {
            
			tempNormals[i * 4 + j] = normalDrawList[i][j];
            
        }
        
    }
    
    
    
    if( colorAttributes.texturized) {
        
        glActiveTexture( GL_TEXTURE0 );
		//texturing stuff
		glBindTexture(GL_TEXTURE_2D, textures[0]);
        
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, colorAttributes.data );
        
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        
		glActiveTexture( GL_TEXTURE0 );
        
        
	}
    
    #ifdef __APPLE__  // include Mac OS X verions of headers
        glBindVertexArrayAPPLE( vao );
    #else // non-Mac OS X operating systems
        glBindVertexArray( vao );
    #endif  // __APPLE__
    
    
	// Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)
	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
    
	// Copy the vertex data from diamond to our buffer
	// 8 * sizeof(GLfloat) is the size of the diamond array, since it contains 8 GLfloat values
	glBufferData( GL_ARRAY_BUFFER , numFaces * 3 * 4 * sizeof(GLfloat) , tempVertices , GL_STATIC_DRAW );
    
	// Specify that our coordinate data is going into attribute index 0, and contains two floats per vertex
	glVertexAttribPointer( prog.vertexLocation , 4 , GL_FLOAT , GL_FALSE , 0 , 0 );
    
	// Enable attribute index 0 as being used
	glEnableVertexAttribArray( prog.vertexLocation );
    
	//Bind our second VBO as being the active buffer and storing vertex attributes (normals)
	glBindBuffer( GL_ARRAY_BUFFER , vbo[1] );
    
	// Copy the color data from colors to our buffer
	// 12 * sizeof(GLfloat) is the size of the colors array, since it contains 12 GLfloat values
	glBufferData( GL_ARRAY_BUFFER , numFaces * 3 * 4 * sizeof(GLfloat) , tempNormals , GL_STATIC_DRAW );
    
	// Specify that our color data is going into attribute index 1, and contains three floats per vertex
	glVertexAttribPointer( prog.normalLocation , 4 , GL_FLOAT, GL_FALSE, 0, 0);
    
	// Enable attribute index 1 as being used
	glEnableVertexAttribArray( prog.normalLocation );
    
    
    
	if(colorAttributes.texturized) {
        
        
        // Bind our third VBO as being the active buffer and storing vertex attributes (coordinates)
        glBindBuffer( GL_ARRAY_BUFFER, vbo[2] );
        
        // Copy the vertex data from diamond to our buffer
        // 8 * sizeof(GLfloat) is the size of the diamond array, since it contains 8 GLfloat values
        glBufferData( GL_ARRAY_BUFFER , numFaces * 3 * 2 * sizeof(GLfloat) , tempTexils , GL_STATIC_DRAW );
        
        glEnableVertexAttribArray( prog.vTextCoordLocation );
        
        glVertexAttribPointer( prog.vTextCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0 );
        
        
	}
    
	delete [] tempVertices;
	delete [] tempNormals;

}

void Object::draw( shaderloc &prog) {
    
	color4 ambient_product = prog.light_ambient * colorAttributes.material_ambient;
	color4 diffuse_product = prog.light_diffuse * colorAttributes.material_diffuse;
	color4 specular_product = prog.light_specular * colorAttributes.material_specular;
    
    
    matModel = matTranslation * matScale * matRotation;
    

    
#ifdef __APPLE__  // include Mac OS X verions of headers
    glBindVertexArrayAPPLE( vao );
#else // non-Mac OS X operating systems
    glBindVertexArray( vao );
#endif  // __APPLE__
    
    glUseProgram(prog.program);
    
	glUniformMatrix4fv( prog.modelLocation , 1 , true , matModel );
    
	glUniformMatrix4fv( prog.viewLocation, 1 , true , prog.viewMatrix );
    
	glUniformMatrix4fv( prog.projectionLocation, 1 , true , prog.projMatrix );
    
	glUniform4fv( prog.ambientLocation, 1, ambient_product );
    
	glUniform4fv( prog.diffuseLocation, 1, diffuse_product );
    
	glUniform4fv( prog.specularLocation, 1, specular_product );
    
	glUniform4fv( prog.lightLocation, 1, prog.light_position );
    
	glUniform1f( prog.shininessLocation, colorAttributes.material_shininess );
    
    glUniform1i( prog.texLocation, (int)colorAttributes.texturized);
    
	if (colorAttributes.texturized)
		glUniform1i( prog.textureLocation, 0 );
    
    
	glDrawArrays( GL_TRIANGLES, 0 , numFaces * 3 );
    
    /*
	delete [] tempColors;
	delete [] tempVertices;
	delete [] tempNormals;
    */
    
}

void Object::setFaces( objLoader* loader ) {
    
	//Asumes 3 vertices/normals per face (triangle)
    
	numFaces = loader->faceCount;
    
    if (faces != NULL) {
        delete [] faces;
    }
    
	faces = new face[loader->faceCount];
    
	//vertex and normal indices
	for( int i = 0 ; i < loader->faceCount ; i++ ) {
        
		//vertex indices
		faces[i].vertIndices[0] = (loader->faceList[i])->vertex_index[0];
        
		faces[i].vertIndices[1] = (loader->faceList[i])->vertex_index[1];
        
		faces[i].vertIndices[2] = (loader->faceList[i])->vertex_index[2];
        
		//normal indices
		faces[i].normalIndices[0] = (loader->faceList[i])->normal_index[0];
        
		faces[i].normalIndices[1] = (loader->faceList[i])->normal_index[1];
        
		faces[i].normalIndices[2] = (loader->faceList[i])->normal_index[2];
    }
    
	numVertices = loader->vertexCount;
    
    if (vertices != NULL) {
        delete [] vertices;
    }
    
	vertices = new point4[loader->vertexCount];
    
	for( int i = 0 ; i < loader->vertexCount ; i++ ) {
        
		vertices[i][0] = (loader->vertexList[i])->e[0];
        
		vertices[i][1] = (loader->vertexList[i])->e[1];
        
		vertices[i][2] = (loader->vertexList[i])->e[2];
        
		vertices[i][3] = 1.0;
        
    }
    
    if (colors != NULL) {
        delete [] colors;
    }
    
	colors = new color4[loader->vertexCount];
    
	for( int i = 0 ; i < loader->vertexCount ; i++ ) {
        
		colors[i][0] = 1.0;
        
		colors[i][1] = 0.0;
        
		colors[i][2] = 0.0;
        
		colors[i][3] = 1.0;
        
    }
    
    if (normals != NULL) {
        delete [] normals;
    }
    
	normals = new normal4[loader->normalCount];
    
	for( int i = 0 ; i < loader->normalCount ; i++ ) {
        
		normals[i][0] = (loader->normalList[i])->e[0];
        
		normals[i][1] = (loader->normalList[i])->e[1];
        
		normals[i][2] = (loader->normalList[i])->e[2];
        
		normals[i][3] = 0.0;
        
    }
    
	//construct draw arrays
    
    if (vertexDrawList != NULL) {
        delete [] vertexDrawList;
    }
    
	vertexDrawList = new point4[loader->faceCount * 3];
    
	for( int i = 0 ; i < numFaces ; i++ ) {
        
		vertexDrawList[ i * 3 + 0 ] = vertices[ faces[i].vertIndices[0] ];
        
		vertexDrawList[ i * 3 + 1 ] = vertices[ faces[i].vertIndices[1] ];
        
		vertexDrawList[ i * 3 + 2 ] = vertices[ faces[i].vertIndices[2] ];
        
    }
    
    if (colorDrawList != NULL) {
        delete [] colorDrawList;
    }
    
	colorDrawList = new color4[loader->faceCount * 3];
    
	for( int i = 0 ; i < numFaces ; i++ ) {
        
		colorDrawList[ i * 3 + 0 ] = colors[ faces[i].vertIndices[0] ];
        
		colorDrawList[ i * 3 + 1 ] = colors[ faces[i].vertIndices[1] ];
        
		colorDrawList[ i * 3 + 2 ] = colors[ faces[i].vertIndices[2] ];
        
    }
    
    if (normalDrawList != NULL) {
        delete [] normalDrawList;
    }
    
	normalDrawList = new normal4[loader->faceCount * 3];
    
	for( int i = 0 ; i < numFaces ; i++ ) {
        
		normalDrawList[ i * 3 + 0 ] = normals[ faces[i].normalIndices[0] ];
        
		normalDrawList[ i * 3 + 1 ] = normals[ faces[i].normalIndices[1] ];
        
		normalDrawList[ i * 3 + 2 ] = normals[ faces[i].normalIndices[2] ];
        
    }
	GLfloat minX = vertices[0][0], minY = vertices[0][1] , minZ = vertices[0][2] , maxX = vertices[0][0], maxY = vertices[0][1] , maxZ = vertices[0][2];
    
	for( int i = 0 ; i < numVertices ; i++ ) {
		//x
		if( vertices[i][0] <  minX )
			minX = vertices[i][0];
        
		if( vertices[i][0] >  maxX )
			maxX = vertices[i][0];
		//y
		if( vertices[i][1] <  minY )
			minY = vertices[i][1];
        
		if( vertices[i][1] >  maxY )
			maxY = vertices[i][1];
		//z
		if( vertices[i][2] <  minZ )
			minZ = vertices[i][2];
        
		if( vertices[i][2] >  maxZ )
			maxZ = vertices[i][2];
        
    }
    
	width = maxX - minX;
    
	height = maxY - minY;
    
	depth = maxZ - minZ;
    
}

void Object::setColor( material &colorStuff, int m ) {
    
    materialColor = m;
    
    
    colorAttributes = colorStuff;
    
    /*
	colorAttributes.material_ambient = colorStuff.material_ambient;
	colorAttributes.material_diffuse = colorStuff.material_diffuse;
	colorAttributes.material_specular = colorStuff.material_specular;
	colorAttributes.material_shininess = colorStuff.material_shininess;
     */
    
}


void Object::scale(GLfloat increase) {
    matScale[0].x += increase;
    matScale[1].y += increase;
    matScale[2].z += increase;
}

void Object::setScale(GLfloat increase) {
    matScale[0].x = increase;
    matScale[1].y = increase;
    matScale[2].z = increase;
}

void Object::rotateY(GLfloat a) {
    
    angle += DegreesToRadians * a;
    
    matRotation[0].x = cos(angle);
    matRotation[0].z = sin(angle);
    matRotation[2].x = -sin(angle);
    matRotation[2].z = cos(angle);
}


void Object::updatePosition() {
    
	vecVelocity[0] += vecAcceleration[0];
	vecVelocity[1] += vecAcceleration[1];
	vecVelocity[2] += vecAcceleration[2];
    
	matTranslation[0][3] += vecVelocity[0];
	matTranslation[1][3] += vecVelocity[1];
	matTranslation[2][3] += vecVelocity[2];
    
	if( isConstrained ) {
        
		//x
		if(matTranslation[0][3] > (constraints[0] - width / 2 ) )
			matTranslation[0][3] = constraints[0] - width / 2;
        
		if(matTranslation[0][3] < (constraints[1] + width / 2) )
			matTranslation[0][3] = constraints[1] + width / 2;
        
		//z
		if(matTranslation[2][3] > (constraints[2] - depth / 2) )
			matTranslation[2][3] = constraints[2] - depth / 2;
        
		if(matTranslation[2][3] < (constraints[3] + depth / 2 ) )
			matTranslation[2][3] = constraints[3] + depth / 2;
        
    }
    
}
