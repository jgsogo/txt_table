
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iomanip>

#include "../../txt_table/txttable_parser.h"

using namespace core::service;

void print_stats(const std::vector<field*>& rows) {
    auto compare = [](field* const& lhs, field* const& rhs) {return (lhs->get<float>() < rhs->get<float>());};
    auto min_element = std::min_element(rows.begin(), rows.end(), compare );
    auto max_element = std::max_element(rows.begin(), rows.end(), compare );
    std::cout << "min=" << (*min_element)->get<float>() << "\t max=" << (*max_element)->get<float>();
    }

int main() {
    txttable_parser parser;
    parser.add_field<float>("sepal length");
    parser.add_field<float>("sepal width");
    parser.add_field<float>("petal length");
    parser.add_field<float>("petal width");
    parser.add_field<std::string>("class");

    // Do parse
    parser.parse_file("data/iris.data", ",", false);
    auto rows = parser.get_rows();
    auto fields = parser.get_fields();
    // Print some statistics
    std::cout << "I have read " << rows.size() << " rows, for fields:" << std::endl;
    for (auto it = fields.begin(); it!=fields.end(); ++it) {
        auto field_rows = (*it).second.second->get_rows();
        std::cout << "\t" << (*it).first << ": " << field_rows.size() << " rows";
        if (it->first.compare("class") != 0) {
            print_stats(field_rows);
            std::cout << std::endl;
            };
        }
    // Recreate original file
    std::cout << "=========== DUMP ============" << std::endl;
    parser.dump(std::cout, ",\t", true);
    getchar();
    return 0;
    }