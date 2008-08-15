// Файл: /Sys/RefCounterPost.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SYS_REF_COUNTER_POST_H__
#define __SYS_REF_COUNTER_POST_H__

//  Т. к. при использовании Forward Declaration деструктор T не будет вызван и мы получим утечку памяти, 
//  эти методы вынесены в отдельный файл, который должен включаться последним в прекомпилированном заголовке.

namespace Sys
{
    //
    // Release
    //
    template <typename T>
    inline void CRefCounter<T>::Release()
    {
        if (!m_Object)
            return;

        if (--*m_RefCount == 0 && m_Object != m_Right) 
        {
            delete m_Object; 
            m_Object = NULL;
            delete m_RefCount; 
            m_RefCount = NULL;
        }
    }
}

#endif // __SYS_REF_COUNTER_POST_H__