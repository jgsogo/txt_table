// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#ifdef _WIN32

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN  // Excluir material rara vez utilizado de encabezados de Windows
#include <windows.h>

#endif

// Archivos de encabezado en tiempo de ejecución de C
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <assert.h>
