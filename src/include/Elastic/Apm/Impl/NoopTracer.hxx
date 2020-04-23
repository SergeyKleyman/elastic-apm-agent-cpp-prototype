#pragma once

#include "Elastic/Apm/ITracer.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Util/pmrAllocateUnique.hxx"

namespace Elastic { namespace Apm { namespace Impl
{

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class NoopTracer
        : public ITracer
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( NoopTracer );

    static PTracer create( const PmrByteAllocator& allocator )
    {
        return pmrAllocateUnique< NoopTracer >( allocator );
    }

    NoopTracer() = default;

    bool isNoop() const override
    {
        return true;
    }
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } } // namespace Elastic::Apm::Impl
