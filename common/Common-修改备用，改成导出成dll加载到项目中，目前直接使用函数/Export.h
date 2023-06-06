#ifndef COMMON_EXPORT_H
#define COMMON_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( COMMON_LIBRARY_STATIC )
    #    define COMMON_EXPORT
    #  elif defined( COMMON_LIBRARY )
    #    define COMMON_EXPORT   __declspec(dllexport)
    #  else
    #    define COMMON_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define COMMON_EXPORT
#endif  

#endif
