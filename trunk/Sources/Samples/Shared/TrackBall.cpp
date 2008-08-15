// Τΰιλ: /Samples/Shared/TrackBall.cpp
//

#include "precompiled.h"
#pragma hdrstop

#include "TrackBall.h"

namespace UI
{
    //
    // Constructor
    //
    CTrackBall::CTrackBall( 
                           const Vec2<float>& Center, float Radius, EType Type 
                           ):
        m_Center( Center ),
        m_Radius( Radius ),
        m_Type( Type ),

        m_RotMat( 1.0f ),
        m_From( 0.0f ),
        m_ProjFrom( 0.0f, 0.0f, 0.0f ),
        m_ProjTo( 0.0f, 0.0f, 0.0f ),
        m_Touched( false ),       
        m_Dragged( false )
    {
        m_CurrQuat.Identity();
        m_LastQuat.Identity();
    }

    //
    // SetCenter
    //
    void CTrackBall::SetCenter( 
                               const Vec2<float>& Center 
                               )
    {
        m_Center = Center;
    }

    //
    // GetCenter
    //
    const Vec2<float>& CTrackBall::GetCenter() const
    {
        return m_Center;
    }

    //
    // GetRadius
    //
    float CTrackBall::GetRadius() const
    {
        return m_Radius;
    }

    //
    // GetType
    //
    CTrackBall::EType CTrackBall::GetType() const
    {
        return m_Type;
    }

    //
    // Touch
    //
    void CTrackBall::Touch( 
                           const Vec2<float>& Pos
                           )
    {
        if ((Pos - m_Center).GetLength() < m_Radius)
            m_Touched = true;
    }

    //
    // Release
    //
    void CTrackBall::Release()
    {
        m_Touched = false;
    }

    //
    // Rotate
    //
    void CTrackBall::Rotate( 
                            const Vec2<float>& Pos 
                            )
    {
        if (!m_Dragged) 
        {
            if (m_Touched) 
            {
                m_From = Pos;
                m_LastQuat = m_CurrQuat;
                m_LastQuat.Normalize();
                m_Dragged = true;
            }
        }
        else 
        {
            if (!m_Touched) 
            {
                m_Dragged = false;
                m_ProjFrom = m_ProjTo = Vec3<float>( 0.0f, 0.0f, 0.0f );
            }
            else 
            {
                Vec2<float> From = (m_From - m_Center) / m_Radius;
                Vec2<float> To = (Pos - m_Center) / m_Radius;

                m_ProjFrom = Math::OrthoProjectOnSphere( From.x, From.y );
                m_ProjTo = Math::OrthoProjectOnSphere( To.x, To.y );

                if (m_Type == RT_ARCBALL) 
                {
                    // Calculate rotation of arcball user input, used to perform object rotation by mouse. 
                    // "from" and "to" the mouse on screen coordinates (with - x, y on screen) in range of -1 to +1. 
                    // The arcball radius is 1.0 and it stand in a center (x = 0, y = 0).
                    
                    Vec3<float> c = Math::CrossProduct( m_ProjFrom, m_ProjTo );
                    if (c.GetLength() <= Math::EPSILON)
                        m_CurrQuat.Identity();
                    else 
                    {
                        float d = Math::DotProduct( m_ProjFrom, m_ProjTo );
                        m_CurrQuat = Quat4<float>( c.x, c.y, c.z, d );
                    }
                }
                else 
                {
                    // Rotate as a half arcball, more realistic manner (like 3dsmax).
                    m_CurrQuat = Math::ShortestArc( m_ProjFrom, m_ProjTo );
                }

                m_CurrQuat *= m_LastQuat;
                m_RotMat = m_CurrQuat.ToMat3();
            }
        }   
    }

    //
    // GetRotMat
    //
    const Mat3& CTrackBall::GetRotMat() const
    {
        return m_RotMat;
    }

    //
    // Reset
    //
    void CTrackBall::Reset()
    {
        m_RotMat.Identity();
        m_CurrQuat.Identity();
        m_LastQuat.Identity();
    }

    //
    // DrawCircle
    //
    void DrawCircle( 
                    const Vec2<float>& Center, float Radius, UINT NumSteps 
                    )
    {
        const float PI2 = Math::PI * 2.0f;

	    glPushMatrix();
	    glTranslatef( Center.x, Center.y, 0.0f );
	    glScalef( Radius, Radius, 0.0f );

	    glBegin( GL_LINE_STRIP );

		for (int i = 0; i <= NumSteps; ++i) 
        {
            float Angle = PI2 * (float)i / NumSteps;
            glVertex2f( Math::Sin( Angle ), Math::Cos( Angle ) );
		}

	    glEnd();

	    glPopMatrix();
    }

    //
    // DrawArc
    //
    void DrawArc( 
                 const Vec2<float>& Center, float Radius, const Vec3<float>& From, const Vec3<float>& To 
                 )
    {
        const int LG_NUM_SEGS = 5;
	    const int NUM_SEGS = 1 << LG_NUM_SEGS;

	    static Vec3<float> Points[ NUM_SEGS + 1 ];

	    Points[ 0 ] = From;
	    Points[ 1 ] = Points[ NUM_SEGS ] = To;

	    for (int i = 0; i < LG_NUM_SEGS; ++i) 
        {
		    Points[ 1 ] += Points[ 0 ];
		    if (Points[ 1 ].GetLength() < Math::EPSILON)
			    Points[ 1 ].Zero();
		    else
			    Points[ 1 ].Normalize();
	    }

        float Dp = 2.0f * Math::DotProduct( Points[ 0 ], Points[ 1 ] );

	    for (int i = 2; i < NUM_SEGS; ++i)
		    Points[ i ] = Points[ i - 1 ] * Dp - Points[ i - 2 ];

	    glPushMatrix();
	    glTranslatef( Center.x, Center.y, 0.0f );
	    glScalef( Radius, Radius, 0.0f );
	    glBegin( GL_LINE_STRIP );
            
        for (int i = 0; i <= NUM_SEGS; ++i)
            GL::glVertex2fv( Points[ i ].ToVec2<float>() );
	    
        glEnd();
	    glPopMatrix();
    }

    //
    // DrawSchematic
    //
    void CTrackBall::DrawSchematic( 
                                   bool DrawArcLine
                                   )
    {
        DrawCircle( m_Center, m_Radius, 128 );

        if (DrawArcLine)
        {
            if (m_Touched && m_Dragged)
                DrawArc( m_Center, m_Radius, m_ProjFrom, m_ProjTo );
        }
    }
}