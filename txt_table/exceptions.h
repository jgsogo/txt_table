
#pragma once

#include <exception>
#include <string>

namespace core {
    namespace service {

        class txttable_parser_exception : public std::runtime_error {
            public:
                txttable_parser_exception(const std::string& what) : std::runtime_error(what) {};
                txttable_parser_exception(const char* what) : std::runtime_error(what) {};
            };
        

        }
    }