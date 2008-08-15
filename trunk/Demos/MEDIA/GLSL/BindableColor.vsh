//
// File: /Demos/MEDIA/GLSL/BindableColor.vsh
//

#version 110

#extension GL_EXT_bindable_uniform  : enable

//
// Attributes
//

attribute vec4      In_Vertex;

//
// Varyings
//

varying vec3        Out_Color;

//
// Uniforms
//

bindable uniform float  Buffer[ 3 ];

//
// main
//
void main()
{
    Out_Color = vec3( Buffer[ 0 ], Buffer[ 1 ], Buffer[ 2 ] );   
    gl_Position = gl_ModelViewProjectionMatrix * In_Vertex;
}