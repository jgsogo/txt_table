// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include <fstream>
#include <iterator>
#include <algorithm>
#include <boost/iterator/zip_iterator.hpp>

#include "../depends/logger/logging.h"
#undef LOGGER
#include "../depends/logger/log_console_colored.h"
#define LOGGER core::logging::logger<core::logging::log_console_colored>