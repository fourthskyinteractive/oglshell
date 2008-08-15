// װאיכ: FrameCounter.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SHARED_FRAME_COUNTER_H__
#define __SHARED_FRAME_COUNTER_H__

#include <time.h>

namespace Demo
{
    //  ׁק¸עקטך FPS.

    class CFrameCounter
    {
    public:
                            CFrameCounter();

        //
        // Interface
        //

        void                AddFrame();
        UINT                GetFramesPerSecond() const;

        void                Reset();

    private:

        //
        // Class members
        //

        UINT                m_NumFrames;
        UINT                m_FramesPerSecond;
        int                 m_PrevTime;

        mutable clock_t     m_PrevClock;
    };

    //  ֿנמסעוירטי עאילונ.

    class CTimer
    {
    public:
                            CTimer();

        //
        // Interface
        //

        float               GetElapsedTime() const;

    private:

        //
        // Class members
        //

        mutable clock_t     m_PrevClock;
        mutable float       m_ElapsedTime;
    };
}

#endif // __SHARED_FRAME_COUNTER_H__