
#pragma once

#include "field.h"

namespace core {
    namespace service {

        template <class T>
        class field_vector : public field {
            public:
                field_vector(const std::string& name) : field(name) {};
                field_vector(const std::string& name, const std::string& value) : field(name) {
                    if (!value.empty()) {
                        boost::split(_value, value, boost::is_any_of("\t "));
                        }
                    };
                virtual ~field_vector() {
                    _value.clear();
                    };

                virtual field* _build_from_value(const std::string& value) {
                    return new field_vector<T>(_name, boost::trim_copy(value));
                    };
                virtual const std::vector<T>& get() const {return _value;};
                virtual const std::string get_str_value() const { return boost::algorithm::join(_value, "\t");};
            protected:
                std::vector<T> _value;
            };        

        }
    }