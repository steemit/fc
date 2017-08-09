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
#include <fc/exception/exception.hpp>
#include <iomanip>
#include <sstream>
// 
#include <fc/io/json.hpp>
// 
namespace fc {
json_console_appender::~json_console_appender() {

}
void json_console_appender::log( const log_message& m ) {

   FILE* out = stream::std_error ? stderr : stdout;

   fc::variant v;
   fc::to_variant(m, v);
   // std::string json_log_message = fc::json::to_pretty_string(v);
   std::string json_log_message = fc::json::to_string(v);

   print(json_log_message, this->get_text_color(m) );

   fprintf( out, "\n" );
   // if(my->cfg.flush )
    fflush( out );
}
}
