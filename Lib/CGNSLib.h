/*****************************************************************************/
/**
 *  @file   CGNSLib.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#pragma once

#include <cgnslib.h>
#include <iostream>
#include <string>
#include <kvs/Macro>
#include <kvs/Breakpoint>
#include <kvs/Message>


#if defined( KVS_ENABLE_DEBUG )
namespace
{
bool IsError( const int error, const char* file, const int line, const char* func, const char* command )
{
    if ( error == CG_OK ) { return false; }

    // Output message tag.
    std::string message_tag( "CGNS ERROR" );
    std::cerr << KVS_MESSAGE_SET_COLOR( KVS_MESSAGE_RED );
    std::cerr << message_tag;
    std::cerr << KVS_MESSAGE_RESET_COLOR;

    // Output message with an error string.
    std::string error_string;
    const char* c = cg_get_error();
    while ( *c ) error_string += *c++;
    std::cerr << ": " << error_string << std::endl;
    std::cerr << "\t" << "FILE: " << file << " (" << line << ")" << std::endl;
    std::cerr << "\t" << "FUNC: " << func << std::endl;
    std::cerr << "\t" << "CGNS COMMAND: " << command << std::endl;

    return true;
}
}
#define CGNS_CALL( command )                                            \
    KVS_MACRO_MULTI_STATEMENT_BEGIN                                     \
    int status = command;                                               \
    if ( ::IsError( KVS_MACRO_FILE, KVS_MACRO_LINE, KVS_MACRO_FUNC, #command ) ) { KVS_BREAKPOINT; } \
    KVS_MACRO_MULTI_STATEMENT_END
#else
#define CGNS_CALL( command ) ( command )
#endif // KVS_ENABLE_DEBUG
