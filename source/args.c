/* $Id$ */

/*!
 * @file        args.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    CLI arguments functions
 */

/* Local includes */
#include "lzwm.h"

/*!
 * 
 */
void lzwm_get_cli_args( int argc, char ** argv, lzwm_cli_args * args )
{
    int i = 0;
    
    while( ++i < argc && ( ( char * )*( ++argv ) )[ 0 ] == '-' )
    {
        switch( ( ( char * )*( argv ) )[ 1 ] )
        {
            case 'c': args->compress = true; break;
            case 'x': args->expand   = true; break;
            case 'h': args->help     = true; break;
            case 'd': args->debug    = true; break;
        }
    }
    
    if( i++ < argc )
    {
        args->source = *( argv );
    }
    
    if( i++ < argc )
    {
        args->destination = *( ++argv );
    }
}
