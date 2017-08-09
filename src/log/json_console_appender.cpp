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

class json_console_appender::impl {
public:
  config                      cfg;
  color::type                 lc[log_level::off+1];
#ifdef WIN32
  HANDLE                      json_console_handle;
#endif
};

json_console_appender::json_console_appender( const variant& args ) 
:my(new impl)
{
   configure( args.as<config>() );
}

json_console_appender::json_console_appender( const config& cfg )
:my(new impl)
{
   configure( cfg );
}
json_console_appender::json_console_appender()
:my(new impl){}

void json_console_appender::log( const log_message& m ) {
   
   fc::variant v;
   fc::to_variant(m, v);
   // std::string json_log_message = fc::json::to_pretty_string(v);
   std::string json_log_message = fc::json::to_string(v);

   print(json_log_message, my->lc[m.get_context().get_log_level()] );

   fprintf( out, "\n" );

   if( my->cfg.flush ) fflush( out );
}
}
