
#include "stdafx.h"

#include <iostream>
#include <exception>

#include "../../txt_table/row.h"
#include "../../txt_table/field.h"

using namespace core::service;

int main() {
    row r;
    r.fields.push_back(new field_concrete<float>("field#1"));
    r.fields.push_back(new field_concrete<std::string>("field#2"));

    std::cout << "Test row output implementation" << std::endl;
    std::cout << "\t Initial: '" << r << "'" << std::endl;

    // Assignment
    r.reset() << 5.3f << std::string("Hello World!");
    std::cout << "\t Test1: '" << r << "'" << std::endl;

    // Assignment
    r.reset(1) << std::string("Bye bye!");
    std::cout << "\t Test2: '" << r << "'" << std::endl;

    // Accessing
    std::cout << "field#1: " << r.get<float>(0) << std::endl;
    std::cout << "field#2: " << r[1] << std::endl;

    // Accessing
    std::cout << "field#1: " << r.get<float>("field#1") << std::endl;
    std::cout << "field#2: " << r["field#2"] << std::endl;

    return 0;
    }