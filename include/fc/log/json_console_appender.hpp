#pragma once
#include <fc/log/console_appender.hpp>

namespace fc {

class json_console_appender : public fc::console_appender
{
public:
	json_console_appender( const variant& args );
	json_console_appender( const config& cfg );
	json_console_appender();
	virtual ~json_console_appender();
// protected:
//         class impl:fc::console_appender::impl;
//         std::unique_ptr<impl> my;
};
}
// #include <fc/reflect/reflect.hpp>
// FC_REFLECT_ENUM( fc::json_console_appender::stream::type, (std_out)(std_error) )
// FC_REFLECT_ENUM( fc::json_console_appender::color::type, (red)(green)(brown)(blue)(magenta)(cyan)(white)(console_default) )
// FC_REFLECT( fc::json_console_appender::level_color, (level)(color) )
// FC_REFLECT( fc::json_console_appender::config, (format)(stream)(level_colors)(flush) )
