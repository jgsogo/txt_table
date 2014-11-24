
#pragma once

#include "txttable_parser.h"
#include "field.h"

//! Build a parser using specified technology
extern "C" TXT_TABLE_EXPORT void get_version(std::string& txttable_parser_version);
extern "C" TXT_TABLE_EXPORT int build_txttable_parser(core::service::txttable_parser* &parser);
extern "C" TXT_TABLE_EXPORT int delete_txttable_parser(core::service::txttable_parser* parser);