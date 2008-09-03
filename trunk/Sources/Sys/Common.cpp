// Τΰιλ: /Sys/Common.cpp
//

#include "Precompiled.h"
#pragma hdrstop

#include "Common.h"

namespace Sys
{
    FILE *CLog::m_File = NULL;

    //
    // Open
    //
    void CLog::Open( 
                    const char *FileName 
                    )
    {
    }

    //
    // Close
    //
	void CLog::Close()
    {
    }

    //
    // Put
    //
    void CLog::Put( 
                   const char *Str 
                   )
    {
    }
    
    //
    // Print
    //
    void CLog::Print( 
                     const char *FormatStr, ... 
                     )
    {
    }

    //
    // Print
    //
    void CLog::Print( 
                     EPrintType Type, const char *FormatStr, ... 
                     )
    {
    }

    //
    // Constructor
    //
    CException::CException()
    {
    }

    //
    // Constructor
    //
    CException::CException( 
                           const char *FormatStr, ... 
                           )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = string( Str );

        if (m_Str.length() > 0)
            Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CException::CException( 
                           const IRTTIObject *Obj, const char *FormatStr, ... 
                           )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = Obj->GetClassName() + "\n\n" + string( Str );

        Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CException::CException( 
                           int Dummy, const char *ClsName, const char *FormatStr, ... 
                           )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = string( ClsName ) + "\n\n" + string( Str );

        Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    CException::~CException()
    {
    }

    //
    // GetErrorString
    //
    const string& CException::GetErrorString() const
    {
        return m_Str;
    }

    //
    // Constructor
    //
    CBadAllocException::CBadAllocException( 
                                           const IRTTIObject *Obj, const char *FormatStr, ... 
                                           )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = Obj->GetClassName() + "\n\n" + string( Str );

        Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CBadAllocException::CBadAllocException( 
                                           const char *ClsName, const char *FormatStr, ... 
                                           )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = string( ClsName ) + "\n\n" + string( Str );

        Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CBadAllocException::CBadAllocException()
    {
    }

    //
    // Constructor
    //
    CCriticalException::CCriticalException( 
                                           const IRTTIObject *Obj, const char *FormatStr, ... 
                                           )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = Obj->GetClassName() + "\n\n" + string( Str );

        Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CCriticalException::CCriticalException( 
                                           const char *ClsName, const char *FormatStr, ... 
                                           )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = string( ClsName ) + "\n\n" + string( Str );

        Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CCriticalException::CCriticalException()
    {
    }

    CFatalException::CFatalException( 
                                     int Dummy, const char *FormatStr, ... 
                                     )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = string( Str );

        if (m_Str.length() > 0)
            Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CFatalException::CFatalException( 
                                     const IRTTIObject *Obj, const char *FormatStr, ... 
                                     )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = Obj->GetClassName() + "\n\n" + string( Str );

        Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CFatalException::CFatalException( 
                                     const char *ClsName, const char *FormatStr, ... 
                                     )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = string( ClsName ) + "\n\n" + string( Str );

        Print( CLog::PT_ERROR, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CDeveloperException::CDeveloperException( 
                                             EError Code, const char *FormatStr, ... 
                                             ):
        m_Code( Code )
    {
        char Str[MAX_STRING];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = ToString( Code ) + "\n" + string( Str );

        Print( CLog::PT_DEVELOPER, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CDeveloperException::CDeveloperException( 
                                             const IRTTIObject *Obj, const char *FormatStr, ... 
                                             ):
        m_Code( ERROR_OK )
    {
        char Str[MAX_STRING];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = Obj->GetClassName() + "\n\n" + string( Str );

        Print( CLog::PT_DEVELOPER, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CDeveloperException::CDeveloperException( 
                                             const IRTTIObject *Obj, EError Code, const char *FormatStr, ... 
                                             ):
        m_Code( Code )
    {
        char Str[MAX_STRING];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = Obj->GetClassName() + "\n\n" + ToString( Code ) + "\n" + string( Str );

        Print( CLog::PT_DEVELOPER, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CDeveloperException::CDeveloperException( 
                                             const char *ClsName, const char *FormatStr, ... 
                                             ):
        m_Code( ERROR_OK )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = string( ClsName ) + "\n\n" + string( Str );

        Print( CLog::PT_DEVELOPER, m_Str.c_str() );
    }

    //
    // Constructor
    //
    CDeveloperException::CDeveloperException( 
                                             const char *ClsName, EError Code, const char *FormatStr, ... 
                                             ):
        m_Code( Code )
    {
        char Str[ MAX_STRING ];
        va_list ArgList;

        SYS_VSPRINTF();
        m_Str = string( ClsName ) + "\n\n" + ToString( Code ) + "\n" + string( Str );

        Print( CLog::PT_DEVELOPER, m_Str.c_str() );
    }

    //
    // GetErrorCode
    //
    CDeveloperException::EError CDeveloperException::GetErrorCode() const
    {
        return m_Code;
    }

    //
    // CodeToString
    //
    string CDeveloperException::ToString( 
                                         EError Code 
                                         ) const
    {
        switch (Code) 
        {
        case ERROR_OK:
            return "ERROR_OK";
        case ERROR_INVALID_ENUM:
            return "ERROR_INVALID_ENUM";
        case ERROR_INVALID_PARAM:
            return "ERROR_INVALID_PARAM";
        case ERROR_INVALID_RAW_POINTER:
            return "ERROR_INVALID_RAW_POINTER";
        case ERROR_INVALID_CALL:
            return "ERROR_INVALID_CALL";
        case ERROR_INVALID_THROW:
            return "ERROR_INVALID_THROW";
        case ERROR_METHOD_NOT_IMPLEMENTED:
            return "ERROR_METHOD_NOT_IMPLEMENTED";
        }

        return "";
    }
}
