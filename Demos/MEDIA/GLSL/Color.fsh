//
// File: /Demos/MEDIA/GLSL/Color.fsh
//

#version 110

//
// Varyings
//

varying vec3        Out_Color;

//
// main
//
void main()
{
    gl_FragColor = vec4( Out_Color, 1.0 );
}