/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina - www.xs-labs.com
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
 * @header      compress.c
 * @copyright   (c) 2011 - Jean-David Gadina - www.xs-labs.com
 * @abstract    ...
 */

#include "lzwm.h"

/*!
 * 
 */
lzwm_status lzwm_compress( FILE * source, FILE * destination )
{
    unsigned int        i;
    unsigned int        j;
    unsigned int        n;
    unsigned int        p;
    unsigned long       read_ops;
    unsigned long       read_op;
    float               tmp;
    size_t              size;
    size_t              length;
    size_t              bytes;
    uint8_t             c;
    uint8_t             s[ LZWM_DATA_MAX_LENGTH ];
    uint8_t             read_buffer[ LZWM_READ_BUFFER_LENGTH ];
    uint16_t            write_buffer[ LZWM_WRITE_BUFFER_LENGTH ];
    lzwm_dict         * dict;
    lzwm_code         * code;
    lzwm_code         * prev_code;
    libprogressbar_args args;
    
    c         = 0;
    i         = 0;
    j         = 0;
    n         = 1;
    p         = 0;
    read_op   = 0;
    length    = 0;
    bytes     = 0;
    dict      = NULL;
    code      = NULL;
    prev_code = NULL;
    size      = fsize( source );
    tmp       = ceil( ( double )size / ( double )LZWM_READ_BUFFER_LENGTH );
    read_ops  = ( unsigned long )tmp;
    
    memset( s,           0, LZWM_DATA_MAX_LENGTH );
    memset( read_buffer, 0, LZWM_READ_BUFFER_LENGTH );
     
    if( fread( &s, sizeof( uint8_t ), 1, source ) == 0 )
    {
        return LZWM_ERROR_INVALID_FILE;
    }
    
    DEBUG( "Initializing the LZWM dictionary" );
    
    if( NULL == ( dict = lzwm_create_dict() ) )
    {
        return LZWM_ERROR_MALLOC;
    }
    
    DEBUG( "Writing the file signature" );
    fwrite( LZWM_FILE_ID, 1, 4, destination );
    
    if( libdebug_is_enabled() == false )
    {
        args.percent = &p;
        args.length  = 50;
        args.label   = "Compressing file:";
        args.done    = "[OK]";
        
        libprogressbar_create_progressbar( ( void * )( &args ) );
    }
    
    DEBUG( "First character: 0x%02X - %03u (%c)", s[ 0 ], s[ 0 ], ( isprint( s[ 0 ] ) ) ? s[ 0 ] : '.' );
    
    prev_code = &( dict->codes[ s[ 0 ] ] );
    
    while( ( length = fread( read_buffer, sizeof( uint8_t ), LZWM_READ_BUFFER_LENGTH, source ) ) )
    {
        DEBUG( "Reading data from source file" );
        
        read_op++;
        
        for( i = 0; i < length; i++ )
        {
            c      = read_buffer[ i ];
            s[ n ] = c;
            
            bytes++;
            
            if( NULL == ( code = lzwm_find_dict_entry( dict, s, n + 1 ) ) )
            {
                
                DEBUG( "    - Symbol not found: adding new entry: 0x%03X - %03u (%s)", dict->count, dict->count, s );
                DEBUG( "    - Writing previous symbol code to the buffer: 0x%03X - %03u", prev_code->code, prev_code->code );
                
                if( j == LZWM_WRITE_BUFFER_LENGTH )
                {
                    lzwm_compress_write( dict, write_buffer, j, bytes, destination );
                    memset( write_buffer, 0, LZWM_WRITE_BUFFER_LENGTH );
                    
                    j     = 0;
                    bytes = 0;
                }
                
                write_buffer[ j++ ] = prev_code->code;
                
                if( lzwm_add_dict_entry( dict, s, n + 1 ) == NULL )
                {
                    if( j == LZWM_WRITE_BUFFER_LENGTH )
                    {
                        lzwm_compress_write( dict, write_buffer, j, bytes, destination );
                        memset( write_buffer, 0, LZWM_WRITE_BUFFER_LENGTH );
                        
                        j     = 0;
                        bytes = 0;
                    }
                    
                    DEBUG( "Maximum number of codes reached. Creating a new LZWM dictionary" );
                    lzwm_delete_dict( dict );
                    
                    if( NULL == ( dict = lzwm_create_dict() ) )
                    {
                        return LZWM_ERROR_MALLOC;
                    }
                    
                    lzwm_add_dict_entry( dict, s, n + 1 );
                    
                    DEBUG( "Writing dictionary end marker" );
                    
                    write_buffer[ j++ ] = LZWM_DICT_MARKER_END;
                }
                
                memset( s, 0, LZWM_DATA_MAX_LENGTH );
                
                s[ 0 ]    = c;
                n         = 1;
                prev_code = &( dict->codes[ c ] );
            }
            else
            {
                DEBUG( "    - Symbol found:     0x%03X - %03u (%s)", code->code, code->code, code->data );
                
                prev_code = code;
                
                n++;
            }
        }
        
        p = ( unsigned int )( ( ( double )read_op / ( double )read_ops ) * 100 );
    }
    
    if( j == LZWM_WRITE_BUFFER_LENGTH )
    {
        lzwm_compress_write( dict, write_buffer, j, bytes, destination );
        memset( write_buffer, 0, LZWM_WRITE_BUFFER_LENGTH );
        
        j     = 0;
        bytes = 0;
    }
    
    write_buffer[ j++ ] = prev_code->code;
    lzwm_compress_write( dict, write_buffer, j, bytes, destination );
    
    p = 100;
    
    libprogressbar_end();
    
    DEBUG( "Deleting the LZWM dictionary" );
    lzwm_delete_dict( dict );
    
    return LZWM_OK;
}
  
/*!
 * 
 */
lzwm_status lzwm_compress_write( lzwm_dict * dict, uint16_t * buffer, size_t length, size_t bytes, FILE * destination )
{
    unsigned int i;
    unsigned int j;
    unsigned int n;
    uint8_t    * char_buffer;
    lzwm_code  * code;
    uint16_t     shrt;
    uint16_t     marker_8bits;
    uint16_t     marker_16bits;
    
    marker_8bits  = LZWM_DICT_MARKER_8BITS;
    marker_16bits = LZWM_DICT_MARKER_16BITS;
    i             = 0;
    j             = 0;
    n             = 0;
    
    DEBUG( "Writing data to the destination file" )
    DEBUG( "Checking compression ratio" );
    
    if( bytes > length * 2 )
    {
        DEBUG( "%u bytes saved: writing 16 bits codes", bytes - ( length * 2 ) );
        fwrite( &marker_16bits, sizeof( uint16_t ), 1, destination );
        fwrite( buffer, sizeof( uint16_t ), length, destination );
    }
    else
    {
        DEBUG( "No byte saved: writing 8 bits data" );
        
        if( NULL == ( char_buffer = ( ( uint8_t * )malloc( sizeof( uint8_t ) * bytes ) ) ) )
        {
            ERROR( "Out of memory" );
        }
        
        for( i = 0; i < length; i++ )
        {
            shrt = buffer[ i ];
            
            if( shrt == LZWM_DICT_MARKER_END )
            {
                continue;
            }
            
            code = &( dict->codes[ shrt ] );
            
            for( j = 0; j < code->length; j++ )
            {
                char_buffer[ n++ ] = code->data[ j ];
            }
        }
        
        fwrite( &marker_8bits, sizeof( uint16_t ), 1, destination );
        fwrite( &bytes, sizeof( size_t ), 1, destination );
        fwrite( char_buffer, sizeof( uint8_t ), bytes, destination );
        free( char_buffer );
    }
    
    return LZWM_OK;
}
