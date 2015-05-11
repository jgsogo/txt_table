
#include "stdafx.h"
#include "txttable_parser.h"

//#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include "exceptions.h"

namespace core {
    namespace service {

        txttable_parser::txttable_parser() {
            _fn_on_row = nullptr;
            }

        txttable_parser::~txttable_parser() {
            this->reset();
            }

        void txttable_parser::reset() {
            _fn_on_row = nullptr;
            _rows.clear();
            _columns.clear();
            // TODO: actually delete fields.
            }

        int txttable_parser::delete_column(const std::string& keyname) {
            _t_columns::iterator it = std::find_if(_columns.begin(), _columns.end(), [&keyname](const std::pair<std::string, field*>& item){
                return (keyname.compare(item.second->get_name())==0);
                });
            if (it != _columns.end()) {
                _columns.erase(it);
                }
            return 0;
            }

        void txttable_parser::set_on_row_callback(_t_on_row fn_on_row, _t_on_header_row fn_on_header_row) {
            _fn_on_row = fn_on_row;
            _fn_on_header_row = fn_on_header_row;
            }

        int txttable_parser::parse_file(const std::string& file, const std::string& sep, const bool& first_row_are_headers, std::function<void (const std::string&)> f) {
            int hRet = -1;
            std::ifstream infile(file.c_str());            
            if (infile!=0) {
                LOG_DEBUG("Parsing file '" << file << "'");
                hRet = this->parse(infile, sep, first_row_are_headers, f);
                }
            else {
                LOG_ERROR("File '" << file << "' does not exists.");
                }
            return hRet;
            }

        const txttable_parser::_t_rows& txttable_parser::get_rows() const {
            return _rows;
            }

        int txttable_parser::get_row(unsigned int row_id, const _t_row* row) const {
            try {
                row = &(this->get_row(row_id));
                return 0;
                }
            catch( std::out_of_range&) {
				LOG_ERROR("Out of range");
                return -1;
                }
            }

        const txttable_parser::_t_row& txttable_parser::get_row(unsigned int row_id) const {
            return _rows.at(row_id);            
            }

        int txttable_parser::split(const std::string& line, const std::string& sep, std::vector<std::string> &vstrings) {
            /*
            tokens* tokens_ = new tokens(sep);
            std::istringstream iss(headers);
            iss.imbue(std::locale(std::locale(), tokens_));
            std::vector<std::string> v_headers;
            std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string>>(v_headers));
            */
            //boost::split(vstrings, line, boost::is_equal(sep), boost::token_compress_off);
            // Better iter_split (¿slower?), can set a complete work as separator
            boost::iter_split(vstrings, line, boost::first_finder(sep, boost::is_equal()));
            // No trim!!! Some fields may be vectors separated by tabs/blanks and some of them could be at the end/beginning
            //std::for_each(vstrings.begin(), vstrings.end(), boost::bind(&boost::trim<std::string>, _1, std::locale()));
            return 0;
            }

        int txttable_parser::parse_headers(const std::string& headers, const std::string& sep) {
            //Check first line against fields in vector
            std::vector<std::string> v_headers;
            txttable_parser::split(headers, sep, v_headers);
            std::for_each(v_headers.begin(), v_headers.end(), boost::bind(&boost::trim<std::string>, _1, std::locale()));

            if (v_headers.size() != _columns.size()) {
                LOG_ERROR("Headers size if different from fields size. Abort!");
                return -1;
                }

            int hret = 0;
            if (_fn_on_header_row) {
                hret = _fn_on_header_row(v_headers);
                }

            return hret;
            }

        int txttable_parser::parse(std::ifstream& file, const std::string& sep, const bool& first_row_are_headers, std::function<void (const std::string&)> f) {
            std::string line;
            
            _t_rows::iterator it_row;

            if (first_row_are_headers) {
                std::getline(file, line);
                this->parse_headers(line, sep);
                }

            int i=0;
            while (std::getline(file, line)) {                
                std::vector<std::string> words;
                txttable_parser::split(line, sep, words);

                if (words.size() == _columns.size()) {
                    try {
                        it_row = _rows.insert(_rows.end(), _t_row());
                        std::for_each( boost::make_zip_iterator(boost::make_tuple(words.begin(), _columns.begin())),
                                        boost::make_zip_iterator(boost::make_tuple(words.end(), _columns.end())),
                                        [&it_row](const boost::tuple<const std::string&, const std::pair<std::string, field*>&>& item ) {
                                            try {
                                                (*it_row).fields.push_back( item.get<1>().second->build_from_value(item.get<0>()));
                                                }
                                            catch(boost::bad_lexical_cast& e) {
                                                std::string msg = e.what();
                                                msg += ". Source value was '" + item.get<0>() + "' for field '" + item.get<1>().second->get_name() + "'";
                                                throw txttable_parser_exception(msg);
                                                }
                                            catch(std::bad_cast& e) {
                                                std::string msg = e.what();
                                                msg += ". Source value was '" + item.get<0>() + "' for field '" + item.get<1>().second->get_name() + "'";
                                                throw txttable_parser_exception(msg);
                                                }
                                            });

                        // Notify on row
                        if (_fn_on_row) {
                            // Based on returned value I can choose not to keep this row.
                            int hret = _fn_on_row( *it_row);
                            if (hret != 0) {
                                _rows.erase(it_row);
                                }
                            }
                        }
                    catch(txttable_parser_exception& e) {                        
                        LOG_ERROR("Exception on line [" << i << "]' " << boost::trim_copy(line) << "' (trimmed): " << e.what());
                        }

                    if (f && ((i%100)==0)) {
                        std::stringstream ss; ss << "Parsing line " << i;
                        f(ss.str());
                        }
                    }
                else {
                    LOG_WARN("Cannot properly parse line [" << i << "] '" << boost::trim_copy(line) << "' (trimmed)");
                    }
                i++;
                }

            LOG_DEBUG("'" << _rows.size() << "' rows read.");
            return 0;
            }
        /*
        void txttable_parser::dump_headers(std::ostream& os, const std::string& sep) const {
            _t_field_descriptors::const_iterator it_last = --_field_descriptors.end();
            for (auto it = _field_descriptors.begin(); it!=_field_descriptors.end(); ++it) {
                os << (it->second.first.length() ? it->second.first : it->first);
                if (it != it_last) {
                    os << sep;
                    }
                }
            }

        void txttable_parser::dump(std::ostream& os, const std::string& sep, const bool& headers) const {
            if (headers) {
                dump_headers(os, sep);
                os << "\n";
                }
            for (auto it = _rows.begin(); it!=_rows.end(); ++it) {
                for (auto it_field = it->begin(); it_field!=it->end(); ++it_field) {
                    auto it_last = --it->end();
                    os << it_field->second->get_str_value();
                    if (it_field != it_last) {
                        os << sep;
                        }
                    }
                os << "\n";
                }
            os << "\n";
            }
        */

        }
    }