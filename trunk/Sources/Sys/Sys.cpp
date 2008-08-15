// Τΰιλ: /Sys/Sys.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Ptr.h"

namespace Sys
{
    //
    // Constructor
    //
    CObject::CObject()
    {
    }

    //
    // Destructor
    //
    CObject::~CObject()
    {
    }
    
    //
    // Constructor
    //
    CNonCopyable::CNonCopyable()
    {
    }

    //
    // Destructor
    //
    CNonCopyable::~CNonCopyable()
    {
    }

    //
    // Constructor
    //
    CNonCopyable::CNonCopyable( const CNonCopyable& Arg )
    {
    }
}