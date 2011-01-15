/* $Id$ */

/*!
 * @header      args.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    CLI arguments functions
 */

#ifndef _LZWM_ARGS_H_
#define _LZWM_ARGS_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

    /*!
     * 
     */
    void lzwm_get_cli_args( int argc, char ** argv, lzwm_cli_args * args );

#ifdef __cplusplus
}
#endif

#endif /* _LZWM_ARGS_H_ */
