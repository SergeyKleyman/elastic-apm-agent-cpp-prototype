#pragma once

#ifndef ELASTIC_APM_IS_OS_WINDOWS
#   ifdef _WIN32
#       define ELASTIC_APM_IS_OS_WINDOWS 1
#   else
#       define ELASTIC_APM_IS_OS_WINDOWS 0
#   endif
#endif
