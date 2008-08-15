// Τΰιλ: /Sys/Macros.h
//

#ifdef _MSC_VER
#pragma once
#endif

#ifndef __SYS_MACROS_H__
#define __SYS_MACROS_H__

//
//
//

#define BIT( N )                (1 << (N))

#define CH_WHITE_SPACE          ' '
#define END_OF_STRING           std::string::npos

#define TEMPLATE_Y              template <typename Y>

#ifdef _MSC_VER
#pragma warning (disable: 4003)
#endif

#define MAP_ITERATION(Key, Type, Obj, Iter)\
    map<Key, Type>::iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter
#define MAP_CONST_ITERATION(Key, Type, Obj, Iter)\
    map<Key, Type>::const_iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter

#define SET_ITERATION(Type, Obj, Iter)\
    set<Type>::iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter
#define SET_CONST_ITERATION(Type, Obj, Iter)\
    set<Type>::const_iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter

#define VECTOR_ITERATION(Type, Obj, Iter)\
    vector<Type>::iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter
#define VECTOR_CONST_ITERATION(Type, Obj, Iter)\
    vector<Type>::const_iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter

#define __M( M0, T0, M1, T1, M2, T2, M3, T3, M4, T4, M5, T5, M6, T6, M7, T7, M8, T8, M9, T9 )\
    T0 M0;\
    T1 M1;\
    T2 M2;\
    T3 M3;\
    T4 M4;\
    T5 M5;\
    T6 M6;\
    T7 M7;\
    T8 M8;\
    T9 M9;
    
#define SYS_VSPRINTF() \
    va_start( ArgList, FormatStr ); \
    vsprintf( Str, FormatStr, ArgList ); \
    va_end( ArgList );

#define ALIGNED_ALLOCATOR( Alignment )\
    void* operator new ( size_t Size )\
    {\
        return _aligned_malloc( Size, Alignment );\
    }\
    \
    void *operator new[] ( size_t Size )\
    {\
        return _aligned_malloc( Size, Alignment );\
    }\
    \
    void operator delete ( void *Memory, size_t Size )\
    {\
        _aligned_free( Memory );\
    }\
    \
    void operator delete[] ( void *Memory, size_t Size )\
    {\
        _aligned_free( Memory );\
    }
    
#endif // __SYS_MACROS_H__