#include "Elastic/Apm/Impl/Util/compilation_config.hxx"

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4365 ) // Compiler Warning (level 4) C4365: 'action' : conversion from 'type_1' to 'type_2', signed/unsigned mismatch
#   pragma warning( disable : 4548 ) // Compiler Warning (level 1) C4548: expression before comma has no effect; expected expression with side-effect
#   pragma warning( disable : 4624 ) // 'derived class' : destructor was implicitly defined as deleted because a base class destructor is inaccessible or deleted
#   pragma warning( disable : 4710 ) // function not inlined
#   pragma warning( disable : 4711 ) // function 'function' selected for inline expansion
#endif
