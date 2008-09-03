// ����: /Sys/Common.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SYS_COMMON_H__
#define __SYS_COMMON_H__

namespace Sys
{
    //  ����� ������� ���������.   

    class DLLAPI CLog
    {
    public:
        enum
        {
            MAX_STRING = 4096
        };

        enum EPrintType
        {
            PT_WARNING = 0,
            PT_ERROR,
            PT_DEVELOPER,
        };

    public:

        //
        // Interface
        //

        static void         Open                ( const char *FileName );
		static void         Close               ();

        static void         Put                 ( const char *Str );
        static void         Print               ( const char *FormatStr, ... );
        static void         Print               ( EPrintType Type, const char *FormatStr, ... );

    private:

        //
        // Class members
        //

        static FILE*        m_File;
    };
    
    //  ������� ����� ����������.

    class DLLAPI CException : public CLog
    {
    public:
                            CException          ( const char *FormatStr, ... ); // <- int Dummy ?
                            CException          ( const IRTTIObject *Obj, const char *FormatStr, ... );
                            CException          ( int Dummy, const char *ClsName, const char *FormatStr, ... );
                            ~CException         ();

        //
	    // Interface
	    //

        const string&       GetErrorString      () const;

    protected:
                            CException          ();

        //
        // Class members
        //

        string              m_Str;
    };

    //  ���������� ��� ����� ���-�� ������.
    //  ��������� � ������, ���� ���������� �������� ���������� ��������� ��� �����������. 

    class CBadAllocException : public CException
    {
    public:
                            CBadAllocException  ( const IRTTIObject *Obj, const char *FormatStr, ... );
                            CBadAllocException  ( const char *ClsName, const char *FormatStr, ... );

    protected:
                            CBadAllocException  ();
    };

    //  ����������� ����������.
    //  ��������� � ������, ��������, ���� ��������� ����������� ��� ��������� codepath � ��� �� ��� ������� ������.

    class CCriticalException : public CException
    {
    public:
                            CCriticalException  ( const IRTTIObject *Obj, const char *FormatStr, ... );
                            CCriticalException  ( const char *ClsName, const char *FormatStr, ... );

    protected:
                            CCriticalException  ();
    };

    //  ��������� ����������.
    //  ��������� � ������, ���� ������ ��������� ���������� ����������. ����� ��������� ��������� � ��������� ������.

    class CFatalException : public CCriticalException
    {                            
    public:
                            CFatalException     ( int Dummy, const char *FormatStr, ... );

                            CFatalException     ( const IRTTIObject *Obj, const char *FormatStr, ... );
                            CFatalException     ( const char *ClsName, const char *FormatStr, ... );
    };

    //  ���������� ��� ������������.
    //  ��������� � ������ ����������� �������� ���������� ��� �������� �������. 
    //  � ������ ��� ���������� �� ������ ��������� � release-������ ���������.

    class CDeveloperException : public CException
    {
    public:
        enum EError
        {
            ERROR_OK = 0,
            ERROR_INVALID_ENUM,
            ERROR_INVALID_PARAM,
            ERROR_INVALID_RAW_POINTER,
            ERROR_INVALID_CALL,
            ERROR_INVALID_THROW, 
            ERROR_METHOD_NOT_IMPLEMENTED,
        };

    public:
                            CDeveloperException ( EError Code, const char *FormatStr, ... );
                            CDeveloperException ( const IRTTIObject *Obj, const char *FormatStr, ... );
                            CDeveloperException ( const IRTTIObject *Obj, EError Code, const char *FormatStr, ... );
                            CDeveloperException ( const char *ClsName, const char *FormatStr, ... );
                            CDeveloperException ( const char *ClsName, EError Code, const char *FormatStr, ... );

        //
	    // Interface
	    //

        EError              GetErrorCode        () const;

    private:
        string              ToString            ( EError Code ) const;

        //
        // Class members
        //

        EError              m_Code;
    };
}

#endif // __SYS_COMMON_H__ 