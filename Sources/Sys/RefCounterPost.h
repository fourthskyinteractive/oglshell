// ����: /Sys/RefCounterPost.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SYS_REF_COUNTER_POST_H__
#define __SYS_REF_COUNTER_POST_H__

//  �. �. ��� ������������� Forward Declaration ���������� T �� ����� ������ � �� ������� ������ ������, 
//  ��� ������ �������� � ��������� ����, ������� ������ ���������� ��������� � ������������������ ���������.

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