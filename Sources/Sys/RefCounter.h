// Файл: /Sys/RefCounter.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SYS_REF_COUNTER_H__
#define __SYS_REF_COUNTER_H__

namespace Sys
{
    //  Базовый класс счётчика ссылок на разделяемый указатель.

    template <typename T>
    class IRefCounter : public CObject
    {
    public:
                            IRefCounter         ();
                            IRefCounter         ( T *Object );

        //
        // Interface
        //

        virtual void        AddRef              ( const IRefCounter<T>& Counter ) = 0;
        virtual void        Release             () = 0;

        void                Lock                () const;
        void                Unlock              () const;

        virtual T*          GetPointer          () const;
        UINT                GetRefCount         () const;
        bool                IsValid             () const;

        bool                Compare             ( const IRefCounter<T>& Counter ) const;
        TEMPLATE_Y bool     Compare             ( const IRefCounter<Y>& Counter ) const;

    //protected:

        //                                       
        // Class members
        //

        static T*           m_Right;

        T*                  m_Object;
        UINT*               m_RefCount;
    };

    //  Счётчик ссылок на стандартный разделяемый указатель С++.

    template <typename T>
    class CRefCounter : public IRefCounter<T>
    {
    public:
                            CRefCounter         ();
                            CRefCounter         ( T *Object );
        //
        // Interface
        //

        virtual void        AddRef              ( const IRefCounter<T>& Counter );
        TEMPLATE_Y void     AddRef              ( const IRefCounter<Y>& Counter );
        virtual void        Release             (); // См. RefCounterPost.h
    };

    //  Счётчик ссылок на указатель на COM-объект.
    //  TODO: IMPLEMENT

    template <typename T>
    class CRefCounterCOM : public IRefCounter<T>
    {
    public:

        //
        // Interface
        //
    };

    //
    // Constructor
    //
    template <typename T>
    inline IRefCounter<T>::IRefCounter():
        m_Object( NULL ),
        m_RefCount( NULL )
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline IRefCounter<T>::IRefCounter( T *Object ):
        m_Object( Object ),
        m_RefCount( NULL )
    {
        if (m_Object)
            m_RefCount = new UINT( 1 );
    }

    //
    // Lock
    //
    template <typename T>
    inline void IRefCounter<T>::Lock() const
    {
        m_Right = m_Object;
    }
      
    //
    // Unlock
    //
    template <typename T>
    inline void IRefCounter<T>::Unlock() const
    {
        m_Right = NULL;
    }
      
    //
    // GetPointer
    //
    template <typename T>
    FORCEINLINE T *IRefCounter<T>::GetPointer() const
    {
    #ifdef _DEBUG
	    if (!m_Object)
            throw CException( 0, "Sys::IRefCounter", "::GetPointer() : Dereference NULL pointer." );
    #endif
	    return m_Object;
    }
      
    //
    // GetRefCount
    //
    template <typename T>
    inline UINT IRefCounter<T>::GetRefCount() const
    {
        return m_RefCount ? *m_RefCount : 0;
    }

    //
    // IsValid
    //
    template <typename T>
    inline bool IRefCounter<T>::IsValid() const
    {
        return m_Object != NULL;
    }

    //
    // Compare
    //
    template <typename T>
    inline bool IRefCounter<T>::Compare( const IRefCounter<T>& Counter ) const
    {
        return m_Object == Counter.m_Object;
    }
      
    //
    // Compare
    //
    template <typename T> template <typename Y>
    inline bool IRefCounter<T>::Compare( const IRefCounter<Y>& Counter ) const
    {
        return m_Object == dynamic_cast<T *>( Counter.m_Object );
    }

    template <typename T> 
    T* IRefCounter<T>::m_Right = NULL;

    //
    // Constructor
    //
    template <typename T>
    inline CRefCounter<T>::CRefCounter()
    {
    }

    //
    // Constructor
    //
    template <typename T>
    inline CRefCounter<T>::CRefCounter( T *Object ):
        IRefCounter<T>( Object )
    {
    }

    //
    // AddRef
    //
    template <typename T>
    inline void CRefCounter<T>::AddRef( const IRefCounter<T>& Counter )
    {
        m_Object = Counter.m_Object;
        m_RefCount = Counter.m_RefCount;
        if (m_RefCount)
            ++*m_RefCount;
    }

    //
    // AddRef
    //
    template <typename T> template <typename Y> 
    inline void CRefCounter<T>::AddRef( const IRefCounter<Y>& Counter )
    {
        m_Object = dynamic_cast<T *>( Counter.m_Object );
    #ifdef _DEBUG
        // In Visual C++ 2005, there are two breaking changes in the behavior of dynamic_cast in managed code:
        // * dynamic_cast to a pointer to the underlying type of a boxed enum will fail at runtime, returning 0 instead of the converted pointer.
        // * dynamic_cast will no longer throw an exception when type-id is an interior pointer to a value type, with the cast failing at runtime. 
        //   The cast will now return the 0 pointer value instead of throwing.
	    if (!m_Object)
            throw CException( 0, "Sys::CRefCounter", "::AddRef() : dynamic_cast() return NULL." );
    #endif
        m_RefCount = Counter.m_RefCount;
        if (m_RefCount)
            ++*m_RefCount;
    }
}

#endif // __SYS_REF_COUNTER_H__