#pragma once
#include <fc/log/console_appender.hpp>

namespace fc {

class json_console_appender : public fc::console_appender {
public:
    using fc::console_appender::console_appender;
        void log(const fc::log_message&);

		struct j_color 
        {
            enum type {
               red,
               green,
               brown,
               blue,
               magenta,
               cyan,
               white,
               console_default,
            };
        };

        struct j_stream { enum type { std_out, std_error }; };

        struct j_level_color 
        {
           j_level_color( log_level l=log_level::all, 
                        j_color::type c=j_color::console_default )
           :level(l), color(c){}

           log_level                		        level;
           json_console_appender::j_color::type     color;
        };

        struct j_config 
        {
           j_config()
           :format( "${timestamp} ${thread_name} ${context} ${file}:${line} ${method} ${level}]  ${message}" ),
            stream(json_console_appender::j_stream::std_error),flush(true){}

           fc::string                         	format;
           json_console_appender::j_stream::type  stream;
           std::vector<j_level_color>           level_colors;
           bool                               	flush;
        };
    
    virtual ~json_console_appender() = default;
};
}

#include <fc/reflect/reflect.hpp>
FC_REFLECT_ENUM( fc::json_console_appender::j_stream::type, (std_out)(std_error) )
FC_REFLECT_ENUM( fc::json_console_appender::j_color::type, (red)(green)(brown)(blue)(magenta)(cyan)(white)(console_default) )
FC_REFLECT( fc::json_console_appender::j_level_color, (level)(color) )
FC_REFLECT( fc::json_console_appender::j_config, (format)(stream)(level_colors)(flush) )
