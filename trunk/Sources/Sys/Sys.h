// Τΰιλ: /Sys/Sys.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SYS_SYS_H__
#define __SYS_SYS_H__

#include "Types.h"
#include "Macros.h"

namespace Sys
{
    //

    class DLLAPI CObject
    {
    public:
    
        //
        // Constructor/Destructor
        //

                            CObject();
        virtual             ~CObject();
    };
    
    //
    
    class DLLAPI CNonCopyable : public CObject
    {
    public:
    
        //
        // Constructor/Destructor
        //
        
                            CNonCopyable();
                            ~CNonCopyable();
                            
    private:
                            CNonCopyable( const CNonCopyable& Arg );
                   
        //
        // Operators
        //

        const CNonCopyable& operator = (const CNonCopyable& Arg) { return *this; }
    };
    
    //
    
    class DLLAPI IRTTIObject : public CObject
    {
    public:
                                
        //
        // RTTI
        //

        virtual string      GetClassName() const = 0;
    };
}

#endif // __SYS_SYS_H__