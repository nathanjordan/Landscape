#version 120

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

attribute vec4 vertex;
attribute vec4 normal;
attribute vec2 vTexCoord;

// lighting stuff
varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL;
uniform vec4 LightPosition;

varying vec2 texCoord;

void main() {

	vec3 normal2;
	normal2.xyz = normal.xyz;
    
    vec4 temp;
    temp = model * vertex;
    
    vec4 temp2;
    temp2 = model * normal;

	//lighting stuff
	fN = temp2.xyz;
    fE = temp.xyz;
    fL = LightPosition.xyz;

	if( LightPosition.w != 0.0 ) {
		fL = LightPosition.xyz - temp.xyz;
    }

	
	//gl_Position =  projection * view * model * vertex;
	
	gl_Position = gl_ModelViewProjectionMatrix * model * vertex;
	
	texCoord    = vTexCoord;
	
	}