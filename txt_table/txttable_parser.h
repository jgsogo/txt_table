
#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "txt_table_export.h"
#include "field.h"

namespace core {
    namespace service {

        class TXT_TABLE_EXPORT txttable_parser {
            public:
                typedef std::vector<field*> _t_fields;
                typedef std::map<std::string, field*> _t_row;
                typedef std::map<std::string, std::pair<std::string, field*> > _t_field_descriptors;
                typedef std::vector<_t_row> _t_rows;
                
                typedef std::function<int (_t_row&)> _t_on_row;
                typedef std::function<int (std::vector<std::string>&)> _t_on_header_row;
            public:
                txttable_parser();
                virtual ~txttable_parser();

                void reset();

                template <class T, template <class> class field_class>
                void add_field(const std::string& keyname, const std::string& column_header = "") {
                    typedef field_class<T> concrete_field_type;
                    field* aux_field_pointer = new concrete_field_type(keyname);
                    _fields.push_back(aux_field_pointer);
                    _field_descriptors.insert( std::make_pair(keyname, std::make_pair(column_header, aux_field_pointer)) );
                    };
                
                template <class T>
                void add_field(const std::string& keyname, const std::string& column_header = "") {
                    this->add_field<T, field_concrete>(keyname, column_header);
                    };
                
                const _t_field_descriptors& get_fields() const { return _field_descriptors;};
                int delete_field(const std::string& keyname);
                
                void set_on_row_callback(_t_on_row fn_on_row, _t_on_header_row fn_on_header_row = 0);

                int parse_headers(const std::string& headers, const std::string& sep);
                int parse_file(const std::string& file, const std::string& sep, const bool& first_row_are_headers=true, std::function<void (const std::string&)> f =0);
                virtual int parse(std::ifstream& file, const std::string& sep, const bool& first_row_are_headers=true, std::function<void (const std::string&)> f =0);

                const _t_rows& get_rows() const;
                const _t_row& get_row(unsigned int row_id) const;
                int get_row(unsigned int row_id, const _t_row* row) const;

                // Dumping
                void dump(std::ostream& os, const std::string& sep, const bool& headers) const;
                void dump_headers(std::ostream& os, const std::string& sep) const;

            protected:
                static int split(const std::string& line, const std::string& sep, std::vector<std::string> &vstrings);

            protected:
                _t_fields _fields;
                _t_field_descriptors _field_descriptors;
                _t_on_row _fn_on_row;
                _t_on_header_row _fn_on_header_row;
                _t_rows _rows;
            };

        }
    }
