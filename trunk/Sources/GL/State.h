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

e-mail: bob.vilson@gmail.com
*/

// Файл: /GL/State.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __GL_STATE_H__
#define __GL_STATE_H__

namespace GL
{
    //  Базовый класса состояния заданного этапа конвейера.
    //  Представляет собой набор OpenGL-команд, скомпилированных в дисплейный список в надежде, что
    //  драйвер OpenGL сможет соптимизировать выполнение команд в такой форме. 

    class CState : public CObject
    {
    public:
        enum
        {
            APPLY_ENABLE = BIT( 1 ),
            APPLY_WRITEMASK = BIT( 2 )
        };

    protected:
                            CState              ();

    public:
                            ~CState             ();

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CState"; }

        //
        // Interface
        //

        void                ApplyState          () const;

    protected:

        //
        // Class members
        //

        GLuint              m_List;
    };

    //  Состояние растеризатора.

    class CRasterizerState : public CState
    {
    public:
        struct TDesc
        {
                                TDesc           ();

            GLenum              FrontFillMode;
            GLenum              BackFillMode;
            GLboolean           CullEnable;
            GLenum              CullMode;
        };

    public:
                            CRasterizerState    ( const TDesc& Desc );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CRasterizerState"; }

        //
        // Interface
        //

        void                GetDesc             ( TDesc* Desc ) const;

    private:
        bool                IsFillMode          ( GLenum Mode ) const;
        bool                IsCullMode          ( GLenum Mode ) const;

        //
        // Class members
        //

        TDesc               m_Desc;
    };

    //  Состояния теста глубины и двустороннего теста трафарета.

    class CDepthStencilState : public CState
    {
    public:
        struct TFace
        {
                                TFace           ();

            GLenum              FailOp;
            GLenum              DepthFailOp;
            GLenum              DepthPassOp;
            GLuint              StencilWriteMask;
            GLenum              StencilFunc;
        };

        struct TDesc
        {
                                TDesc           ();

            GLboolean           DepthEnable;
            GLboolean           DepthWriteMask;
            GLenum              DepthFunc;
            GLboolean           StencilEnable;
            GLuint              StencilReadMask;
            GLuint              StencilRef;
            TFace               FrontFace;
            TFace               BackFace;
        };

    public:
                            CDepthStencilState  ( const TDesc& Desc, UINT Flags = APPLY_ENABLE | APPLY_WRITEMASK );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CDepthStencilState"; }

        //
        // Interface
        //

        void                GetDesc             ( TDesc* Desc ) const;

    private:
        bool                IsComparisonFunc    ( GLenum Func ) const;
        bool                IsStencilOp         ( GLenum Op ) const;

        //
        // Class members
        //

        TDesc               m_Desc;
    };

    //  Состояние смешивания в буфере кадра. 

    class CBlendState : public CState
    {
    public:
        struct TDesc
        {
                                TDesc           ();

            GLboolean           BlendEnable;
            GLenum              SrcFactorRGB;
            GLenum              DestFactorRGB;
            GLenum              BlendOpRGB;
            GLenum              SrcFactorAlpha;
            GLenum              DestFactorAlpha;
            GLenum              BlendOpAlpha;
            GLboolean           ColorWriteMask[ 4 ];
        };

    public:
                            CBlendState         ( const TDesc& Desc, UINT Flags = APPLY_ENABLE | APPLY_WRITEMASK );

        //
        // RTTI
        //

        virtual string      GetClassName        () const { return "GL::CBlendState"; }

        //
        // Interface
        //

        void                GetDesc             ( TDesc* Desc ) const;

    private:
        bool                IsBlendFactor       ( GLenum Factor ) const;
        bool                IsBlendFunc         ( GLenum Mode ) const;

        //
        // Class members
        //

        TDesc               m_Desc;
    };
}

#endif // __GL_STATE_H__