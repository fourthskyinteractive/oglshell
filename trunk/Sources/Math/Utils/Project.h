/*
This file is a part of Z-Trek 3D engine math library. 
You can use it freely in your proprietary applications.

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
*/

// Τΰιλ: /Math/Utils/Project.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __MATH_UTILS_PROJECT_H__
#define __MATH_UTILS_PROJECT_H__

namespace Math
{
    //
    // ProjectVec
    //
    inline bool ProjectVec( 
                           const Vec3<float>& In, 
                           const Mat4& World, 
                           const Mat4& View, 
                           const Mat4& Projection, 
                           const int Viewport[ 4 ], 
                           Vec3<float> *Out 
                           )
    {
        Vec4<float> Proj( In, 1.0f );

        Proj = (Projection * View * World) * Proj;
        if (Proj.w == 0.0f)
            return false;

        Out->x = Proj.x / Proj.w;
        Out->y = Proj.y / Proj.w;
        Out->z = Proj.z / Proj.w;

        // Map x, y and z to range 0.0-1.0.
        Out->x = Out->x * 0.5f + 0.5f;
        Out->y = Out->y * 0.5f + 0.5f;
        Out->z = Out->z * 0.5f + 0.5f;

        // Map x,y to viewport.
        Out->x = Out->x * Viewport[ 2 ] + Viewport[ 0 ];
        Out->y = Out->y * Viewport[ 3 ] + Viewport[ 1 ];

        return true;
    }

    //
    // ProjectVecArray
    //
    inline bool ProjectVecArray(
                                const Vec3<float> *In, 
                                unsigned Count,
                                const Mat4& World, 
                                const Mat4& View, 
                                const Mat4& Projection, 
                                const int Viewport[ 4 ], 
                                Vec3<float> *Out
                                )
    {
        Mat4 WorldViewProj = Projection * View * World;

        for (int i = 0; i < Count; ++i)
        {
            Vec4<float> Proj( In[ i ], 1.0f );

            Proj = WorldViewProj * Proj;
            if (Proj.w == 0.0f)
                return false;

            Out[ i ].x = Proj.x / Proj.w;
            Out[ i ].y = Proj.y / Proj.w;
            Out[ i ].z = Proj.z / Proj.w;

            // Map x, y and z to range 0.0-1.0.
            Out[ i ].x = Out[ i ].x * 0.5f + 0.5f;
            Out[ i ].y = Out[ i ].y * 0.5f + 0.5f;
            Out[ i ].z = Out[ i ].z * 0.5f + 0.5f;

            // Map x, y to viewport.
            Out[ i ].x = Out[ i ].x * Viewport[ 2 ] + Viewport[ 0 ];
            Out[ i ].y = Out[ i ].y * Viewport[ 3 ] + Viewport[ 1 ];
        }

        return true;
    }

    //
    // UnProjectVec
    //
    inline bool UnProjectVec(
                             const Vec3<float>& In, 
                             const Mat4& World, 
                             const Mat4& View, 
                             const Mat4& Projection, 
                             const int Viewport[ 4 ], 
                             Vec3<float> *Out 
                             )
    {
        // TODO: Implement.
        return false;
    }

    //
    // UnProjectVecArray
    //
    inline bool UnProjectVecArray(
                                  const Vec3<float> *In, 
                                  unsigned Count,
                                  const Mat4& World, 
                                  const Mat4& View, 
                                  const Mat4& Projection, 
                                  const int Viewport[ 4 ], 
                                  Vec3<float> *Out
                                  )
    {
        // TODO: Implement.
        return false;
    }
}

#endif // __MATH_UTILS_PROJECT_H__