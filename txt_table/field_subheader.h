
#pragma once

#include "field.h"

namespace core {
    namespace service {

        template <class T>
        class field_subheader : public field_concrete<T> {
            public:
                field_subheader(const std::string& name, const field_subheader<T>* subhead_field = 0) : field_concrete<T>(name), _subhead_field(subhead_field) {};
                field_subheader(const std::string& name, const std::string& value, const field_subheader<T>* subhead_field = 0) : field_concrete<T>(name, value), _subhead_field(subhead_field) {};
                virtual ~field_subheader() {};

                virtual field* _build_from_value(const std::string& value) {
                    if (_rows.empty()) {
                        // First row, headers!
                        boost::split(_headers, value, boost::is_any_of("\t "));
                        std::for_each(_headers.begin(), _headers.end(), boost::bind(&boost::trim<std::string>, _1, std::locale()));
                        return new field_subheader<T>(_name, this);
                        }
                    return new field_subheader<T>(_name, value, this);
                    };

                const std::vector<std::string>& get_headers() const { 
                    if (_subhead_field) {
                        return _subhead_field->get_headers();
                        }
                    else {
                        return _headers;
                        }
                    };
            protected:
                std::vector<std::string> _headers;
                const field_subheader<T>* _subhead_field;
            };

        }
    }