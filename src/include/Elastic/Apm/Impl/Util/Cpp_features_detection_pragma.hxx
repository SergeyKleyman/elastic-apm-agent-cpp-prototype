#pragma once

////////////////////////////////////////////////////////////////////////////////
//
// ELASTIC_APM_HAS_PRAGMA_CLANG
//

#ifdef ELASTIC_APM_UNDER_IDE
#   define ELASTIC_APM_HAS_PRAGMA_CLANG 1
#endif

#ifndef ELASTIC_APM_HAS_PRAGMA_CLANG
#   ifdef _MSC_VER // Visual C++
#       define ELASTIC_APM_HAS_PRAGMA_CLANG 0
#   else
#       define ELASTIC_APM_HAS_PRAGMA_CLANG 1
#   endif
#endif

//
// ELASTIC_APM_HAS_PRAGMA_CLANG
//
////////////////////////////////////////////////////////////////////////////////
