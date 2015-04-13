// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "stdafx.h"
#include "txt_table_export.h"
#include "txt_table/config.h"

#ifdef _WIN32

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	    case DLL_PROCESS_ATTACH:
            LOG_INFO("DLL_PROCESS_ATTACH " << app_namespace << "::" << app_name << ": " << TXT_TABLE_VERSION_STRING);
            break;
	    case DLL_THREAD_ATTACH:
            LOG_INFO("DLL_THREAD_ATTACH " << app_namespace << "::" << app_name << ": " << TXT_TABLE_VERSION_STRING);
            break;
	    case DLL_THREAD_DETACH:
            LOG_INFO("DLL_THREAD_DETACH " << app_namespace << "::" << app_name << ": " << TXT_TABLE_VERSION_STRING);
            break;
	    case DLL_PROCESS_DETACH:
            LOG_INFO("DLL_PROCESS_DETACH " << app_namespace << "::" << app_name << ": " << TXT_TABLE_VERSION_STRING);
            break;
	    }
	return TRUE;
    }

#endif