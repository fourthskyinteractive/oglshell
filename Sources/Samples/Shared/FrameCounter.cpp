// Τΰιλ: FrameCounter.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "FrameCounter.h"

namespace Demo
{
    //
    // Constructor
    //
    CFrameCounter::CFrameCounter()
    {
        Reset();
    }

    //
    // AddFrame
    //
    void CFrameCounter::AddFrame()
    {
        ++m_NumFrames;

        if (m_PrevClock == -1L)
        {
            m_PrevClock = clock();
            return;
        }

        clock_t CurrClock = clock();
	    clock_t ElapsedClocks = CurrClock - m_PrevClock;

        if (ElapsedClocks > CLOCKS_PER_SEC) 
        {
            m_FramesPerSecond = m_NumFrames * CLOCKS_PER_SEC / ElapsedClocks;
            m_NumFrames = 0;
            m_PrevClock = CurrClock;
        }
    }
    
    //
    // GetFramesPerSecond
    //
    UINT CFrameCounter::GetFramesPerSecond() const
    {
        return m_FramesPerSecond;
    }

    //
    // Reset
    //
    void CFrameCounter::Reset()
    {
        m_NumFrames = 0;
        m_FramesPerSecond = 0;
        m_PrevTime = 0;

        m_PrevClock = -1L;
    }

    //
    // Constructor
    //
    CTimer::CTimer():
        m_PrevClock( -1L ),
        m_ElapsedTime( 0.0f )
    {
    }

    //
    // GetElapsedTime
    //
    float CTimer::GetElapsedTime() const
    {
        if (m_PrevClock == -1L)
        {
            m_PrevClock = clock();
            return 0.0f;
        }

        clock_t CurrClock = clock();
	    clock_t ElapsedClocks = CurrClock - m_PrevClock;

        if (ElapsedClocks > 1)
        {
            m_PrevClock = CurrClock;
            m_ElapsedTime = (float)ElapsedClocks / (float)CLOCKS_PER_SEC;
        }

        return m_ElapsedTime;
    }
}