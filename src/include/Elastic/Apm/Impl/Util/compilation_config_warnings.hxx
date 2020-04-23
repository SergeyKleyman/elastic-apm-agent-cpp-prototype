#pragma once

#ifdef _MSC_VER // Visual C++
#   ifdef ELASTIC_APM_UNDER_IDE
#       pragma warning( disable : 4068 ) // unknown pragma
#   endif
#   pragma warning( disable : 4371 ) // Compiler Warning (level 3) C4371: 'classname': layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
#   pragma warning( disable : 4514 ) // unreferenced inline function has been removed
#   pragma warning( disable : 4710 ) // function not inlined
#   pragma warning( disable : 4711 ) // Compiler Warning (level 1) C4711: function 'function' selected for inline expansion
#   pragma warning( disable : 4820 ) // '?' bytes padding added after data member
#   pragma warning( disable : 4868 ) // Compiler Warning (level 4) C4868: 'file(line_number)' compiler may not enforce left-to-right evaluation order in braced initializer list
#   pragma warning( disable : 5045 ) // Compiler Warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#endif

