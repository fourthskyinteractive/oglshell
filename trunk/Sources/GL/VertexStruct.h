/*
OpenGL Shell - convenient OpenGL wrapper for use in OOP programs.
Copyright (C) 2005-2008 Victor Coda.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library. If not, see http://www.gnu.org/licenses

e-mail: victor.coda@gmail.com
*/

// Файл: /GL/VertexStruct.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_VERTEX_STRUCTURE_H__
#define __GL_VERTEX_STRUCTURE_H__

namespace GL
{
    //  Описание формата вершины.

    class DLLAPI CVertexStructure : public CObject
    {
    public:
        enum 
        {
            MAX_VERTEX_STREAMS = 4 // Произвольная константа, 4 вполне достаточно.
        };

        enum EVertexAttribute
        {
            VA_ATTRIB0 = 0,
            VA_ATTRIB1,
            VA_ATTRIB2,
            VA_ATTRIB3,
            VA_ATTRIB4,
            VA_ATTRIB5,
            VA_ATTRIB6,
            VA_ATTRIB7,
            VA_ATTRIB8,
            VA_ATTRIB9,
            VA_ATTRIB10,
            VA_ATTRIB11,
            VA_ATTRIB12,
            VA_ATTRIB13,
            VA_ATTRIB14,
            VA_ATTRIB15,
            // Следуя особенностям NVIDIA OpenGL Implementation:
            VA_POSITION = VA_ATTRIB0,
            VA_WEIGHT,
            VA_NORMAL,
            VA_COLOR,
            VA_SECONDARY_COLOR,
            VA_FOG_COORD,
            VA_TEX_COORD0 = VA_ATTRIB8,
            VA_TEX_COORD1,
            VA_TEX_COORD2,
            VA_TEX_COORD3,
            VA_TEX_COORD4,
            VA_TEX_COORD5,
            VA_TEX_COORD6,
            VA_TEX_COORD7
        };
        
        struct DLLAPI TDesc
        {
            GLuint              StreamIndex;
            EVertexAttribute    Attribute;
            GLint               ComponentsCount;
            GLenum              Type;
            GLboolean           Normalized;
        };

    private:
        struct TAttrib
        {                         
            GLint               Size;
            GLenum              Type;
            GLboolean           Normalized;
            GLubyte*            Offset;
        };

        friend              CRenderDeviceDebug;
        friend              CRenderDeviceRelease;

    public:
                            CVertexStructure    ( const TDesc *Attributes, int Count );
                            CVertexStructure    ( const vector<TDesc>& Attributes );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CVertexStructure"; }
        
        //
        // Interface
        //
        
        GLsizei             GetVertexSize       () const;
        
    private:
        void                AddAttribute        ( GLuint StreamIndex, EVertexAttribute Attribute, GLint ComponentsCount, GLenum Type, GLboolean Normalized );
        void                Compile             ();
        
		//
		// Class members
		//
		
        map<GLuint, TAttrib> m_Attributes[ MAX_VERTEX_STREAMS ];
        GLsizei             m_Strides[ MAX_VERTEX_STREAMS ];

        vector<bool>        m_Involved;

        GLsizei             m_VertexSize;     
    };
}

#endif // __GL_VERTEX_STRUCTURE_H__