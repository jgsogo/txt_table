
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

    parser.parse_file("data/iris/iris.data", ",", false);

    auto rows = parser.get_rows();
    std::cout << "Read " << rows.size() << " rows." << std::endl;
    for (auto i = 0; i<10; ++i) {
        std::cout << rows[i] << std::endl;
        }

    return 0;
    }