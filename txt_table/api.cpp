
#include "stdafx.h"
#include "api.h"

#include "txt_table/config.h"

void get_version(std::string& txttable_parser_version) {
	txttable_parser_version = TXT_TABLE_VERSION_STRING;
	}

int build_txttable_parser(core::service::txttable_parser* &parser) {
	parser = new core::service::txttable_parser();
	return 0;
	
	}

int delete_txttable_parser(core::service::txttable_parser* parser) {
    delete parser;
    return 0;
    }