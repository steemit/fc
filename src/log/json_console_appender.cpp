#include <fc/log/json_console_appender.hpp>
#include <fc/log/log_message.hpp>
#include <fc/thread/unique_lock.hpp>
#include <fc/string.hpp>
#include <fc/variant.hpp>
#include <fc/reflect/variant.hpp>
#ifndef WIN32
#include <unistd.h>
#endif
#include <boost/thread/mutex.hpp>
#define COLOR_CONSOLE 1
#include "console_defines.h"
#include <fc/io/stdio.hpp>
#include <fc/io/json.hpp>
#include <fc/exception/exception.hpp>
#include <iomanip>
#include <sstream>

namespace fc {

boost::mutex& json_log_mutex() {
    static boost::mutex m; return m;
}

void json_console_appender::log( const log_message& m ) {
    fc::variant v;
    mutable_variant_object log_map;

    FILE* out = stream::std_error ? stderr : stdout;

    log_map( "level", m.get_context().get_log_level() );
    log_map( "file", m.get_context().get_file() );
    log_map( "line", m.get_context().get_line_number() );

    auto me = m.get_context().get_method();
    // strip all leading scopes...
    if ( me.size() )
    {
        uint32_t p = 0;
        for( uint32_t i = 0; i < me.size(); ++i )
        {
            if( me[i] == ':' ) p = i;
        }

        if( me[p] == ':' ) ++p;
        log_map( "method", m.get_context().get_method().substr(p, 20) );
    }

    log_map( "hostname", m.get_context().get_host_name() );
    log_map( "thread_name", m.get_context().get_thread_name().substr(0, 9) );
    log_map( "timestamp", m.get_context().get_timestamp() );
    log_map( "context", m.get_context().get_context() );
    log_map( "format", m.get_format() );
    log_map( "data", m.get_data() );

    fc::to_variant(log_map, v);
    // std::string json_log_message = fc::json::to_pretty_string(v);
    std::string json_log_message = fc::json::to_string(v);

    fc::unique_lock<boost::mutex> lock(json_log_mutex());

    print( json_log_message, this->get_text_color(m) );

    fprintf( out, "\n" );
    if ( can_flush() ) {
        fflush( out );
    }
        
}
}