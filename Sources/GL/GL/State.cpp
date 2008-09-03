/*
OpenGL Shell - open source C++ wrapper for use in OOP programs.
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

// Файл: /GL/GL/State.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "State.h"

namespace GL
{
    //
    // Constructor
    //
    CState::CState():
        m_DList( 0 )
    {
        if (m_Extensions->OpenGL_3_0)
        {
            throw CDeprecatedException( this, "::CState()", 3, 0 );
        }

        glClearErrors();
        m_DList = glGenLists( 1 );
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR)
            throw CException( this, Error, "::CState() : Failed to generate display list." );
    }

    //
    // Destructor
    //
    CState::~CState()
    {
        glClearErrors();
        glDeleteLists( m_DList, 1 );
        if (glGetError() != GL_NO_ERROR)
            Print( Sys::CLog::PT_ERROR, "::~CState() : Failed to delete display list." );
    }

    //
    // ApplyState
    //
    void CState::ApplyState() const
    {
    #ifdef _DEBUG
        glClearErrors();
    #endif
        glCallList( m_DList );
    #ifdef _DEBUG
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::ApplyState() : An OpenGL error has occured." );
    #endif
    } 

    //
    // Constructor
    //
    CRasterizerState::TDesc::TDesc():
        FrontFillMode( GL_FILL ),
        BackFillMode( GL_FILL ),
        CullEnable( GL_FALSE ),
        CullMode( GL_BACK )
    {
    }

    //
    // Constructor
    //
    CRasterizerState::CRasterizerState( 
                                       const TDesc& Desc 
                                       ):
        m_Desc( Desc )
    {
    #ifdef _DEBUG
        if (!IsFillMode( Desc.FrontFillMode ))
            throw Sys::CDeveloperException( this, "::CRasterizerState() : Invalid <Desc.FrontFillMode> parameter." );
        if (!IsFillMode( Desc.BackFillMode ))
            throw Sys::CDeveloperException( this, "::CRasterizerState() : Invalid <Desc.BackFillMode> parameter." );
        if (!IsCullMode( Desc.CullMode ))
            throw Sys::CDeveloperException( this, "::CRasterizerState() : Invalid <Desc.CullMode> parameter." );
    #endif // _DEBUG

        glNewList( m_DList, GL_COMPILE );

        if (Desc.FrontFillMode == Desc.BackFillMode)
            glPolygonMode( GL_FRONT_AND_BACK, Desc.FrontFillMode );
        else
        {
            glPolygonMode( GL_FRONT, Desc.FrontFillMode );
            glPolygonMode( GL_BACK, Desc.BackFillMode );
        }

        if (!Desc.CullEnable)
            glDisable( GL_CULL_FACE );
        else
        {
            glCullFace( Desc.CullMode );
            glEnable( GL_CULL_FACE );
        }

        glEndList();
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::CRasterizerState() : An OpenGL error has occured." );
    }

    //
    // GetDesc
    //
    void CRasterizerState::GetDesc( TDesc* Desc ) const
    {
        *Desc = m_Desc;
    }

    //
    // IsFillMode
    //
    bool CRasterizerState::IsFillMode( GLenum Mode ) const
    {
        switch (Mode)
        {
        case GL_POINT:
        case GL_LINE:
        case GL_FILL:
            return true;
        }

        return false;
    }

    //
    // IsCullMode
    //
    bool CRasterizerState::IsCullMode( GLenum Mode ) const
    {
        switch (Mode)
        {
        case GL_FRONT:
        case GL_BACK:
        case GL_FRONT_AND_BACK:
            return true;
        }

        return false;
    }

    //
    // Constructor
    //
    CDepthStencilState::TFace::TFace():
        FailOp( GL_KEEP ),
        DepthFailOp( GL_KEEP ),
        DepthPassOp( GL_KEEP ),
        StencilWriteMask( 0xFFFFFFFF ),
        StencilFunc( GL_ALWAYS )
    {
    }

    //
    // Constructor
    //
    CDepthStencilState::TDesc::TDesc():
        DepthEnable( GL_FALSE ), // Initially, depth test is disabled.
        DepthWriteMask( GL_TRUE ),
        DepthFunc( GL_ALWAYS ), 
        StencilEnable( GL_FALSE ), // Initially the stencil test is disabled.
        StencilReadMask( 0xFFFFFFFF ),
        StencilRef( 0x0 )
    {
    }

    //
    // Constructor
    //
    CDepthStencilState::CDepthStencilState( 
                                           const TDesc& Desc, UINT Flags 
                                           ):
        m_Desc( Desc )
    {
        if (!m_Extensions->OpenGL_2_0)
        {
            throw CExtensionException( this, "::CDepthStencilState()", 2, 0 );
        }

    #ifdef _DEBUG
        if (!IsComparisonFunc( Desc.DepthFunc ))
            throw Sys::CDeveloperException( this, "::CDepthStencilState() : Invalid <Desc.DepthFunc> parameter." );
        
        if (!IsStencilOp( Desc.FrontFace.FailOp ))
            throw Sys::CDeveloperException( this, "::CDepthStencilState() : Invalid <Desc.FrontFace.FailOp> parameter." );
        if (!IsStencilOp( Desc.FrontFace.DepthFailOp ))
            throw Sys::CDeveloperException( this, "::CDepthStencilState() : Invalid <Desc.FrontFace.DepthFailOp> parameter." );
        if (!IsStencilOp( Desc.FrontFace.DepthPassOp ))
            throw Sys::CDeveloperException( this, "::CDepthStencilState() : Invalid <Desc.FrontFace.DepthPassOp> parameter." );
        if (!IsComparisonFunc( Desc.FrontFace.StencilFunc ))
            throw Sys::CDeveloperException( this, "::CDepthStencilState() : Invalid <Desc.FrontFace.StencilFunc> parameter." );

        if (!IsStencilOp( Desc.BackFace.FailOp ))
            throw Sys::CDeveloperException( this, "::CDepthStencilState() : Invalid <Desc.BackFace.FailOp> parameter." );
        if (!IsStencilOp( Desc.BackFace.DepthFailOp ))
            throw Sys::CDeveloperException( this, "::CDepthStencilState() : Invalid <Desc.BackFace.DepthFailOp> parameter." );
        if (!IsStencilOp( Desc.BackFace.DepthPassOp ))
            throw Sys::CDeveloperException( this, "::CDepthStencilState() : Invalid <Desc.BackFace.DepthPassOp> parameter." );
        if (!IsComparisonFunc( Desc.BackFace.StencilFunc ))
            throw Sys::CDeveloperException( this, "::CDepthStencilState() : Invalid <Desc.BackFace.StencilFunc> parameter." );
    #endif // _DEBUG

        glNewList( m_DList, GL_COMPILE );

        if (!Desc.DepthEnable)
            glDisable( GL_DEPTH_TEST );
        else
        {
            if (Flags & APPLY_WRITEMASK)
                glDepthMask( Desc.DepthWriteMask ); // TODO: Зависит ли DepthMask от DepthEnable?
            glDepthFunc( Desc.DepthFunc );
            if (Flags & APPLY_ENABLE)
                glEnable( GL_DEPTH_TEST );
        }

        if (!Desc.StencilEnable)
            glDisable( GL_STENCIL_TEST );
        else
        {
            glStencilOpSeparate( GL_FRONT, Desc.FrontFace.FailOp, Desc.FrontFace.DepthFailOp, Desc.FrontFace.DepthPassOp );
            glStencilOpSeparate( GL_BACK, Desc.BackFace.FailOp, Desc.BackFace.DepthFailOp, Desc.BackFace.DepthPassOp );
            if (Flags & APPLY_WRITEMASK)
            {
                glStencilMaskSeparate( GL_FRONT, Desc.FrontFace.StencilWriteMask );
                glStencilMaskSeparate( GL_BACK, Desc.BackFace.StencilWriteMask );
            }
            glStencilFuncSeparate( Desc.FrontFace.StencilFunc, Desc.BackFace.StencilFunc, Desc.StencilRef, Desc.StencilReadMask );
            if (Flags & APPLY_ENABLE)
                glEnable( GL_STENCIL_TEST );
        }

        glEndList();
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::CDepthStencilState() : An OpenGL error has occured." );
    }

    //
    // GetDesc
    //
    void CDepthStencilState::GetDesc( TDesc* Desc ) const
    {
        *Desc = m_Desc;
    }

    //
    // IsComparisonFunc
    //
    bool CDepthStencilState::IsComparisonFunc( GLenum Func ) const
    {
        switch (Func)
        {
        case GL_NEVER:
        case GL_LESS:
        case GL_LEQUAL:
        case GL_EQUAL:
        case GL_GREATER:
        case GL_NOTEQUAL:
        case GL_GEQUAL: 
        case GL_ALWAYS:
            return true;
        }

        return false;
    }

    //
    // IsStencilOp
    //
    bool CDepthStencilState::IsStencilOp( GLenum Op ) const
    {
        switch (Op)
        {
        case GL_ZERO:
        case GL_KEEP:
        case GL_REPLACE:
        case GL_INCR: 
        case GL_DECR:
        case GL_INVERT:
        // OpenGL 1.4
        case GL_INCR_WRAP:
        case GL_DECR_WRAP:
            return true;
        }

        return false;
    }

    //
    // Constructor
    //
    CBlendState::TDesc::TDesc():
        BlendEnable( FALSE ),
        SrcFactorRGB( GL_ONE ),
        DestFactorRGB( GL_ZERO ),
        BlendOpRGB( GL_FUNC_ADD ),
        SrcFactorAlpha( GL_ONE ),
        DestFactorAlpha( GL_ZERO ),
        BlendOpAlpha( GL_FUNC_ADD )
    {
        ColorWriteMask[ 0 ] = GL_TRUE;
        ColorWriteMask[ 1 ] = GL_TRUE;
        ColorWriteMask[ 2 ] = GL_TRUE;
        ColorWriteMask[ 3 ] = GL_TRUE;
    }

    //
    // Constructor
    //
    CBlendState::CBlendState( 
                             const TDesc& Desc, UINT Flags 
                             ):
        m_Desc( Desc )
    {
        if (!m_Extensions->OpenGL_2_0)
        {
            throw CExtensionException( this, "::CBlendState()", 2, 0 );
        }

    #ifdef _DEBUG
        if (!IsBlendFactor( Desc.SrcFactorRGB ))
            throw Sys::CDeveloperException( this, "::CBlendState() : Invalid <Desc.SrcFactorRGB> parameter." );
        if (!IsBlendFactor( Desc.DestFactorRGB ))
            throw Sys::CDeveloperException( this, "::CBlendState() : Invalid <Desc.DestFactorRGB> parameter." );
        if (!IsBlendFunc( Desc.BlendOpRGB ))
            throw Sys::CDeveloperException( this, "::CBlendState() : Invalid <Desc.BlendOpRGB> parameter." );

        if (!IsBlendFactor( Desc.SrcFactorAlpha ))
            throw Sys::CDeveloperException( this, "::CBlendState() : Invalid <Desc.SrcFactorAlpha> parameter." );
        if (!IsBlendFactor( Desc.DestFactorAlpha ))
            throw Sys::CDeveloperException( this, "::CBlendState() : Invalid <Desc.DestFactorAlpha> parameter." );
        if (!IsBlendFunc( Desc.BlendOpAlpha ))
            throw Sys::CDeveloperException( this, "::CBlendState() : Invalid <Desc.BlendOpAlpha> parameter." );
    #endif // _DEBUG

        glNewList( m_DList, GL_COMPILE );

        if (!Desc.BlendEnable)
            glDisable( GL_BLEND );
        else
        {
            glBlendFuncSeparate( Desc.SrcFactorRGB, Desc.DestFactorRGB, Desc.SrcFactorAlpha, Desc.DestFactorAlpha );
            glBlendEquationSeparate( Desc.BlendOpRGB, Desc.BlendOpAlpha );
            if (Flags & APPLY_ENABLE)
                glEnable( GL_BLEND );
        }

        if (Flags & APPLY_WRITEMASK)
            glColorMask( Desc.ColorWriteMask[ 0 ], Desc.ColorWriteMask[ 1 ], Desc.ColorWriteMask[ 2 ], Desc.ColorWriteMask[ 3 ] );

        glEndList();
        GLenum Error = glGetError();
        if (Error != GL_NO_ERROR) 
            throw CException( this, Error, "::CBlendState() : An OpenGL error has occured." );
        
    }

    //
    // GetDesc
    //
    void CBlendState::GetDesc( TDesc* Desc ) const
    {
        *Desc = m_Desc;
    }

    //
    // IsBlendFactor
    //
    bool CBlendState::IsBlendFactor( GLenum Factor ) const
    {
        switch (Factor)
        {
        case GL_ZERO:
        case GL_ONE:
        case GL_SRC_COLOR:
        case GL_ONE_MINUS_SRC_COLOR:
        case GL_SRC_ALPHA:
        case GL_ONE_MINUS_SRC_ALPHA:
        case GL_DST_ALPHA:
        case GL_ONE_MINUS_DST_ALPHA:
        case GL_DST_COLOR:
        case GL_ONE_MINUS_DST_COLOR:
        case GL_SRC_ALPHA_SATURATE:
            return true;
        }

        return false;
    }

    //
    // IsBlendFunc
    //
    bool CBlendState::IsBlendFunc( GLenum Mode ) const
    {
        switch (Mode)
        {
        case GL_FUNC_ADD:
        case GL_FUNC_SUBTRACT:
        case GL_FUNC_REVERSE_SUBTRACT:
        case GL_MIN:
        case GL_MAX:
            return true;
        }

        return false;
    }
}