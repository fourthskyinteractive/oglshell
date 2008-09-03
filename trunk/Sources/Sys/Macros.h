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

//
//
//

#ifdef _MSC_VER
    #if (_MSC_VER >= 1200)
        #define FORCEINLINE __forceinline
    #else
        #define FORCEINLINE __inline
    #endif
#else
    #define FORCEINLINE inline 
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4003)
#endif

#define MAP_ITERATION(Key, Type, Obj, Iter)\
    map<Key, Type>::iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter
#define CONST_MAP_ITERATION(Key, Type, Obj, Iter)\
    map<Key, Type>::const_iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter

#define SET_ITERATION(Type, Obj, Iter)\
    set<Type>::iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter
#define CONST_SET_ITERATION(Type, Obj, Iter)\
    set<Type>::const_iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter

#define VECTOR_ITERATION(Type, Obj, Iter) \
    vector<Type>::iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter
#define VECTOR_ITERATION_COUNT(Type, Obj, Iter, Count) \
    vector<Type>::iterator Iter = Obj.begin(), End = Obj.begin() + Count; Iter != End; ++Iter
#define VECTOR_ITERATION_PTR(Type, Obj, Iter) \
    vector<Type>::iterator Iter = Obj->begin(), End = Obj->end(); Iter != End; ++Iter
#define VECTOR_ITERATION_PTR_COUNT(Type, Obj, Iter, Count) \
    vector<Type>::iterator Iter = Obj->begin(), End = Obj->begin() + Count; Iter != End; ++Iter

#define CONST_VECTOR_ITERATION(Type, Obj, Iter) \
    vector<Type>::const_iterator Iter = Obj.begin(), End = Obj.end(); Iter != End; ++Iter
#define CONST_VECTOR_ITERATION_COUNT(Type, Obj, Iter, Count) \
    vector<Type>::const_iterator Iter = Obj.begin(), End = Obj.begin() + Count; Iter != End; ++Iter
#define CONST_VECTOR_ITERATION_PTR(Type, Obj, Iter) \
    vector<Type>::const_iterator Iter = Obj->begin(), End = Obj->end(); Iter != End; ++Iter
#define CONST_VECTOR_ITERATION_PTR_COUNT(Type, Obj, Iter, Count) \
    vector<Type>::const_iterator Iter = Obj->begin(), End = Obj->begin() + Count; Iter != End; ++Iter

#define __M( M0, T0, M1, T1, M2, T2, M3, T3, M4, T4, M5, T5, M6, T6, M7, T7, M8, T8, M9, T9, M10, T10, M11, T11, M12, T12, M13, T13, M14, T14, M15, T15, M16, T16, M17, T17, M18, T18, M19, T19 )\
    T0 M0;\
    T1 M1;\
    T2 M2;\
    T3 M3;\
    T4 M4;\
    T5 M5;\
    T6 M6;\
    T7 M7;\
    T8 M8;\
    T9 M9;\
    T10 M10;\
    T11 M11;\
    T12 M12;\
    T13 M13;\
    T14 M14;\
    T15 M15;\
    T16 M16;\
    T17 M17;\
    T18 M18;\
    T19 M19;
    
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

#define FOURCC2DWORD(ch0, ch1, ch2, ch3) \
    ((UINT)(BYTE)(ch0) | ((UINT)(BYTE)(ch1) << 8) | \
    ((UINT)(BYTE)(ch2) << 16) | ((UINT)(BYTE)(ch3) << 24))
    
#endif // __SYS_MACROS_H__