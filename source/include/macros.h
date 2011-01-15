/* $Id$ */

/*!
 * @header      macros.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Program's macros
 */

#ifndef _LZWM_MACROS_H_
#define _LZWM_MACROS_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Local includes */
#include "stdc/c89.h"

/*!
 * @define      __FATAL
 * @abstract    Issues a fatal error message on stderr and aborts the program's execution (exit code: 1)
 * @param       FILE    The file path
 * @param       LINE    The line number
 * @param       ...     Optional arguments
 */
#define __FATAL( FILE, LINE, ... )  \
    fprintf                         \
    (                               \
        stderr,                     \
        "!!! FATAL ERROR !!!\n"     \
        "\n"                        \
        "    - File: %s\n"          \
        "    - Line: %i\n",         \
        strrchr( FILE, '/' ) + 1,   \
        LINE                        \
    );                              \
    fprintf                         \
    (                               \
        stderr,                     \
        __VA_ARGS__                 \
    );                              \
    fprintf( stderr, "\n" );        \
    pthread_exit( EXIT_SUCCESS );   \
    exit( EXIT_FAILURE );

/*!
 * @define      FATAL
 * @abstract    Issues a fatal error message on stderr and aborts the program's execution (exit code: 1)
 * @param       ...     Optional arguments
 */
#define FATAL( ... ) __FATAL( __FILE__, __LINE__, __VA_ARGS__ )

/*!
 * @define      ERROR
 * @abstract    Issues an error message on stderr and aborts the program's execution (exit code: 1)
 * @param       ...     Optional arguments
 */
#define ERROR( ... )                \
    fprintf                         \
    (                               \
        stderr,                     \
        "Error: "                   \
    );                              \
    fprintf                         \
    (                               \
        stderr,                     \
        __VA_ARGS__                 \
    );                              \
    fprintf( stderr, "\n" );        \
    pthread_exit( EXIT_SUCCESS );   \
    exit( EXIT_FAILURE );

#ifdef __cplusplus
}
#endif

#endif /* _LZWM_MACROS_H_ */

