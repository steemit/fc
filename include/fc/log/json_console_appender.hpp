#pragma once
#include <fc/log/console_appender.hpp>

namespace fc {

class json_console_appender : public fc::console_appender
{
public:
	// json_console_appender();
	json_console_appender( const variant& args );
    json_console_appender( const config& cfg );
	json_console_appender();
	virtual ~json_console_appender();
private:
        class impl;
        std::unique_ptr<impl> my;
};
}
