#pragma once
#include <fc/log/console_appender.hpp>

namespace fc {

class json_console_appender : public fc::console_appender
{
public:
    using fc::console_appender::console_appender;
    void log(const fc::log_message&);

    virtual ~json_console_appender();
};
}