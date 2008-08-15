// Файл: /Samples/Shared/TrackBall.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SHARED_TRACKBALL_H__
#define __SHARED_TRACKBALL_H__

namespace UI
{
    //  Манипулятор типа "Track Ball".

    class CTrackBall //: public IControl
    {
    public:
        enum EType
        {
            RT_ARCBALL = 0,
            RT_TRACKBALL
        };

    public:
                            CTrackBall          ( const Vec2<float>& Center, float Radius, EType Type );

        //
        // Interface
        //

        void                SetCenter           ( const Vec2<float>& Center );
        const Vec2<float>&  GetCenter           () const;
        float               GetRadius           () const;
        EType               GetType             () const;

        void                Touch               ( const Vec2<float>& Pos );
        void                Release             ();
        void                Rotate              ( const Vec2<float>& Pos );
        const Mat3&         GetRotMat           () const;

        void                Reset               ();

        void                DrawSchematic       ( bool DrawArcLine = false );

    private:

        //
        // Class members
        //

        Vec2<float>         m_Center;
        float               m_Radius;
        EType               m_Type;

        Mat3                m_RotMat;
        Quat4<float>        m_CurrQuat, m_LastQuat;
        Vec2<float>         m_From;
        Vec3<float>         m_ProjFrom, m_ProjTo;
        bool                m_Touched;
        bool                m_Dragged;
    };
}

#endif // __SHARED_TRACKBALL_H__