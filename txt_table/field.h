
#pragma once

#include <string>
#include <vector>
#include "txt_table/txt_table_export.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace core {
    namespace service {

        template <class T> class field_concrete;

        class TXT_TABLE_EXPORT field {
            protected:
                typedef std::vector<field*> _t_rows;
            public:
                field(const std::string& name);
                virtual ~field();

                const std::string& get_name() const;
                virtual const std::string get_str_value() const = 0;
                field* build_from_value(const std::string& value) {
                    field* hret = this->_build_from_value(value);
                    _rows.push_back(hret);
                    return hret;
                    };
                virtual field* _build_from_value(const std::string& value) = 0;

                template <typename T>
                const T& get() const {
                    typedef field_concrete<T> concrete_field_type;
                    return (dynamic_cast<const concrete_field_type*>(this))->get();
                    };
            protected:
                _t_rows _rows;
                std::string _name;
            };

        template <class T>
        inline T field_concrete_value_cast(const std::string& value) {
            return boost::lexical_cast<T>(value);
            }

        template <class T>
        class field_concrete : public field {
            public:
                field_concrete(const std::string& name) : field(name) {};
                field_concrete(const std::string& name, const std::string& value) : field(name), _value( field_concrete_value_cast<T>(value) ) {};
                virtual ~field_concrete() {};

                virtual field* _build_from_value(const std::string& value) {
                    return new field_concrete<T>(_name, boost::trim_copy(value));
                    };
                virtual const T& get() const { return _value;};
                virtual const std::string get_str_value() const {
                    /* \todo TODO: Lexical cast it's actually a very slow function due to use of streamstrings.
                        Override default behaviour for specific types to gain speed.
                    */
                    return boost::lexical_cast<std::string>(_value);
                    };

            protected:
                T _value;
            };


        // Non accesible field
        struct ignored {};

        template <>
        class TXT_TABLE_EXPORT field_concrete<ignored> : public field {
            public:
                field_concrete(const std::string& name) : field("[ignored]") {};
                field_concrete(const std::string& name, const std::string& value) : field(name) {};
                virtual ~field_concrete() {
                    _rows.clear();
                    };

                virtual field* _build_from_value(const std::string& value) {
                    return &dummy;
                    };
                virtual const ignored& get() const {
                    throw std::runtime_error("Field ignored.");
                    return _ignored;
                    };
                virtual const std::string get_str_value() const { return "[ignored]";};
            protected:
                static field_concrete<ignored> dummy;
				ignored _ignored;
            };

        typedef field_concrete<ignored> field_ignored;

        }
    }
