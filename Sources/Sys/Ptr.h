// Файл: /Sys/Ptr.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SYS_PTR_H__
#define __SYS_PTR_H__

#include "RefCounter.h"

namespace Sys
{
    //  Умный разделяемый указатель.

    template <typename T>
    class Ptr
    {
        template <typename Y> 
        friend class Ptr;

    public:
                            Ptr                 ();
                                            
                            Ptr                 ( T *Object );
                            Ptr                 ( const Ptr<T>& Object );
        TEMPLATE_Y          Ptr                 ( const Ptr<Y>& Object );

                            ~Ptr                ();

        //
        // Interface
        //

        T*                  GetRawPointer       () const; // Указатель не должен быть NULL.
        UINT                GetRefCount         () const;

        TEMPLATE_Y Ptr<Y>   CastTo              () const;

        //
        // Operators
        //

        Ptr<T>&             operator =          (T *Object);
        Ptr<T>&             operator =          (const Ptr<T>& Object);
        TEMPLATE_Y Ptr<T>&  operator =          (const Ptr<Y>& Object);

        T&                  operator *          () const; 
        T*                  operator ->         () const;
        bool                operator !          () const; 
        
        bool                operator ==         (const Ptr<T>& Object) const;
        TEMPLATE_Y bool     operator ==         (const Ptr<Y>& Object) const;
        bool                operator !=         (const Ptr<T>& Object) const;
        TEMPLATE_Y bool     operator !=         (const Ptr<Y>& Object) const;
        
                            operator bool       () const;

    private:

        //
        // Class members
        //

        CRefCounter<T>      m_Counter;
    };

    //
    // Constructor
    //
    template <typename T>
    inline Ptr<T>::Ptr()
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline Ptr<T>::Ptr( T *Object ):
        m_Counter( Object )
    {
    }
                
    //
    // Constructor
    //
    template <typename T>
    inline Ptr<T>::Ptr( const Ptr<T>& Object )
    {
        if (Object)
            m_Counter.AddRef( Object.m_Counter );
    }

    //
    // Constructor
    //
    template <typename T> template <typename Y>
    inline Ptr<T>::Ptr( const Ptr<Y>& Object )
    {
        if (Object)
            m_Counter.AddRef( Object.m_Counter );
    }
     
    //
    // Destructor
    //
    template <typename T>
    inline Ptr<T>::~Ptr()
    {
        m_Counter.Release();
    }

    //
    // GetRawPointer
    //
    template <typename T>
    inline T *Ptr<T>::GetRawPointer() const
    {
        return m_Counter.GetPointer();
    }
        
    //
    // GetRefCount
    //
    template <typename T>
    inline UINT Ptr<T>::GetRefCount() const
    {
        return m_Counter.GetRefCount();
    }

    //
    // CastTo
    //
    template <typename T> template <typename Y>
    inline Ptr<Y> Ptr<T>::CastTo() const
    {
        Ptr<Y> Object;

        Object.m_Counter.AddRef( m_Counter );

        return Object;
    }

    //
    // operator =
    //
    template <typename T>
    inline Ptr<T>& Ptr<T>::operator = (T *Object)
    {
        m_Counter.Release();
        m_Counter = CRefCounter<T>( Object );

        return *this;
    }

    //
    // operator =
    //
    template <typename T>
    inline Ptr<T>& Ptr<T>::operator = (const Ptr<T>& Object)
    {
        if (this != &Object) 
        {
            CRefCounter<T> Temp = Object.m_Counter;

            Temp.Lock();
            m_Counter.Release();
            Temp.Unlock();

            m_Counter.AddRef( Temp );
	    }

	    return *this;
    }

    //
    // operator =
    //
    template <typename T> template <typename Y>
    inline Ptr<T>& Ptr<T>::operator = (const Ptr<Y>& Object)
    {
        if ((const void *)this != (const void *)&Object) 
        {
            CRefCounter<Y> Temp = Object.m_Counter;

            Temp.Lock();
            m_Counter.Release();
            Temp.Unlock();

            m_Counter.AddRef( Temp );   
	    }

	    return *this;
    }

    //
    // operator *
    //
    template <typename T>
    inline T& Ptr<T>::operator * () const
    {
        return m_Counter.GetPointer();
    }
        
    //
    // operator ->
    //
    template <typename T>
    __forceinline T *Ptr<T>::operator -> () const
    {
        return m_Counter.GetPointer();
    }
      
    //
    // operator !
    //
    template <typename T>
    inline bool Ptr<T>::operator ! () const
    {
        return !m_Counter.IsValid();
    }

    //
    // operator ==
    //
    template <typename T>
    inline bool Ptr<T>::operator == (const Ptr<T>& Object) const
    {
        return m_Counter.Compare( Object.m_Counter );
    }

    //
    // operator ==
    //
    template <typename T> template <typename Y>
    inline bool Ptr<T>::operator == (const Ptr<Y>& Object) const
    {
        return m_Counter.Compare( Object.m_Counter );
    }

    //
    // operator !=
    //
    template <typename T>
    inline bool Ptr<T>::operator != (const Ptr<T>& Object) const
    {
        return !m_Counter.Compare( Object.m_Counter );
    }

    //
    // operator !=
    //
    template <typename T> template <typename Y>
    inline bool Ptr<T>::operator != (const Ptr<Y>& Object) const
    {
        return m_Counter.Compare( Object.m_Counter );
    }

    //
    // operator bool
    //
    template <typename T>
    inline Ptr<T>::operator bool () const
    {
        return m_Counter.IsValid();
    }
}

#endif // __SYS_PTR_H__