/*******************************************************************************
 * Copyright (c) 2010, Jean-David Gadina <macmade@eosgarden.com>
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/* $Id$ */

/*!
 * @file        lzwm.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Program's main functions
 */

#include "eos-skl/eos-skl.h"
#include "lzwm.h"

/*!
 * 
 */
int main( int argc, char * argv[] )
{
    FILE        * f1;
    FILE        * f2;
    lzwm_cli_args args;
    
    lzwm_get_cli_args( argc, argv, &args );
    
    f1          = NULL;
    f2          = NULL;
    
    if( args.source == NULL || args.destination == NULL || ( args.compress == true && args.expand == true ) || ( args.compress == false && args.expand == false ) )
    {
        lzwm_help( argv[ 0 ] );
        
        return EXIT_SUCCESS;
    }
    
    if( args.debug == true )
    {
        libdebug_enable();
        DEBUG( "Debug mode is now enabled" );
    }
    
    DEBUG( "Checking access to the source and destination file" );
    
    if( access( args.source, R_OK ) != 0 )
    {
        printf( "Error: unable to open source file for reading: %s\n", args.source );
        
        return EXIT_FAILURE;
    }
    
    if( access( args.destination, F_OK ) == 0 && access( args.destination, W_OK ) != 0 )
    {
        printf( "Error: unable to destination file for writing: %s\n", args.destination );
        
        return EXIT_FAILURE;
    }
    
    DEBUG( "Opening the file handles" );
    
    if( NULL == ( f1 = fopen( args.source, "rb" ) ) )
    {
        printf( "Error: unable to open source file: %s\n", args.source );
        
        return EXIT_FAILURE;
    }
    else if( NULL == ( f2 = fopen( args.destination, "wb" ) ) )
    {
        printf( "Error: unable to open destination file: %s\n", args.destination );
        
        return EXIT_FAILURE;
    }
    
    if( args.compress == true )
    {
        DEBUG( "Compressing file" );
        /* lzwm_compress( f1, f2 ); */
    }
    else if( args.expand == true )
    {
        DEBUG( "Expanding file" );
        /* lzwm_expand( f1, f2 ); */
    }
    else
    {
        lzwm_help( argv[ 0 ] );
    }
    
    DEBUG( "Closing the file handles" );
    fclose( f1 );
    fclose( f2 );
    
    return EXIT_SUCCESS;
}
