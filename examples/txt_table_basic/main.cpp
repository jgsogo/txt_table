
#include "stdafx.h"

#include "../../txt_table/txttable_parser.h"

int main() {
    core::service::txttable_parser parser;
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