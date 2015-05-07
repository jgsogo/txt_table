
#include "stdafx.h"
#include "field.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

namespace core {
    namespace service {

        field::field(const std::string& name) : _name(name) {};
        field::~field() {
            _t_rows::iterator it;
            for (it=_rows.begin(); it!=_rows.end(); ++it) {
                delete (*it);
                }
            _rows.clear();
            }

        const std::string& field::get_name() const { return _name;};


        // Field ignored
        field_concrete<ignored> field_concrete<ignored>::dummy("");

        }
    }