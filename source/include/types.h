/* $Id$ */

/*!
 * @header      types.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Program's type definitions
 */

#ifndef _LZWM_TYPES_H_
#define _LZWM_TYPES_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    
    typedef struct _lzwm_cli_args
    {
        bool   compress;
        bool   expand;
        bool   help;
        bool   debug;
        char * source;
        char * destination;
    }
    lzwm_cli_args;
    
#ifdef __cplusplus
}
#endif

#endif /* _LZWM_TYPES_H_ */

