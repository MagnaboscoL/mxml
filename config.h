/*
 * Abstraction layer for Mini-XML, a small XML file parsing
 * library.
 *
 * Copyright 2003-2018 by Michael R Sweet.
 *
 * These coded instructions, statements, and computer programs are the
 * property of Michael R Sweet and are protected by Federal copyright
 * law.  Distribution and use rights are outlined in the file "COPYING"
 * which should have been included with this file.  If this file is
 * missing or damaged, see the license at:
 *
 *     https://michaelrsweet.github.io/mxml
 */


/*
 * Include necessary headers...
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <io.h>


#ifdef _MSC_VER  
/*
* Microsoft also renames the POSIX functions to _name, and introduces
* a broken compatibility layer using the original names.  As a result,
* random crashes can occur when, for example, strdup() allocates memory
* from a different heap than used by malloc() and free().
*
* To avoid moronic problems like this, we #define the POSIX function
* names to the corresponding non-standard Microsoft names.
*/

#define close		_close
#define open		_open
#define read	    _read
#define snprintf 	_snprintf
#define strdup		_strdup
#define vsnprintf 	_vsnprintf
#define write		_write

#endif

#ifndef MXML_OPEN
#define MXML_OPEN open
#endif

#ifndef MXML_CLOSE
#define MXML_CLOSE close
#endif

#ifndef MXML_READ
#define MXML_READ read
#endif

#ifndef MXML_WRITE
#define MXML_WRITE write
#endif

#ifndef MXML_MALLOC
#define MXML_MALLOC malloc
#endif

#ifndef MXML_CALLOC
#define MXML_CALLOC calloc
#endif

#ifndef MXML_REALLOC
#define MXML_REALLOC realloc
#endif

/** To handle the calls that were originally fprintf().
* By default no logging function is registered.
* The MXML_ENABLE_LOGGING has been kept because the DEBUG define was present, but we could actually avoid id and simply define or not MXML_LOG.
*/
#ifndef MXML_LOG
#define MXML_LOG 
#ifdef MXML_ENABLE_LOGGING
#error "To log you have to set a logging function!"
#endif
#endif

#ifndef MXML_LOG_ARG
#define MXML_LOG_ARG stderr
#endif

#ifndef MXML_GET_C
#define MXML_GET_C getc
#endif

/*
 * Version number...
 */

#define MXML_VERSION "Mini-XML v2.12"


/*
 * Inline function support...
 */

#ifdef __GNUC__ 
//#define inline inline
#elif _MSC_VER
#define inline _inline
#else
#define inline
#endif


/*
 * Long long support...
 */

/* #define HAVE_LONG_LONG 1 */


/*
 * Do we have the *printf() functions?
 */

/* #define HAVE_SNPRINTF 1 */
/* #undef HAVE_VASPRINTF */
/* #define HAVE_VSNPRINTF 1 */


/*
 * Do we have the strXXX() functions?
 */

/* #define HAVE_STRDUP 1 */
/* #undef HAVE_STRLCPY */


/*
 * Do we have threading support?
 */

/* #undef HAVE_PTHREAD_H */

/*
 * C++ support...
 */

#ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

/*
 * Define prototypes for string functions as needed...
 */

#  ifndef HAVE_STRDUP
extern char	*_mxml_strdup(const char *);
#    define strdup _mxml_strdup
#  endif /* !HAVE_STRDUP */

#  ifndef HAVE_STRLCPY
extern size_t	_mxml_strlcpy(char *, const char *, size_t);
#    define strlcpy _mxml_strlcpy
#  endif /* !HAVE_STRLCPY */

extern char	*_mxml_strdupf(const char *, ...);
extern char	*_mxml_vstrdupf(const char *, va_list);

#  ifndef HAVE_SNPRINTF
extern int	_mxml_snprintf(char *, size_t, const char *, ...);
#    define snprintf _mxml_snprintf
#  endif /* !HAVE_SNPRINTF */

#  ifndef HAVE_VSNPRINTF
extern int	_mxml_vsnprintf(char *, size_t, const char *, va_list);
#    define vsnprintf _mxml_vsnprintf
#  endif /* !HAVE_VSNPRINTF */

#ifdef __cplusplus
}
#  endif /* __cplusplus */
