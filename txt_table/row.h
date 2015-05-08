
#pragma once

#include "field.h"

namespace core {
	namespace service {

		struct row {
			std::vector<field*> fields;
			std::vector<field*>::iterator it;

			
			row& reset(const std::size_t& offset=0) { it = fields.begin()+offset; return *this;};

			template <typename T>
			row& operator<<(const T& dato) {
				if (it == fields.end()) {
					throw std::runtime_error("Out of range");
					}
				(*it)->set<T>(dato);
				++it;
				return *this;
				};

			void print(std::ostream& os, const std::string& sep) const {
				auto it_end = --fields.end();
				for(auto it = fields.begin(); it!=fields.end(); ++it) {
					os << (*it)->get_str_value();
					if (it!=it_end) {
						os << sep;
						}
					}
				};
			};

		std::ostream& operator<<(std::ostream& os, const row& r) {
			r.print(os, ", ");
			return os;
			}

		}
	}

