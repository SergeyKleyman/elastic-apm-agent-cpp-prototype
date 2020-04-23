#pragma once

#include "Elastic/Apm/Log/ISink.hxx"
#include "Elastic/Apm/Util/PmrVector.hxx"
#include "Elastic/Apm/Util/pmrAllocateUniqueTypeErasedDeleter.hxx"

namespace Elastic { namespace Apm { namespace Log
{

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class CompositeSink
        : public ISink
{
public:

    using Sinks = Util::PmrVector< PSink >;

    static PSink create( Sinks sinks, const Util::PmrByteAllocator& allocator )
    {
        return Util::pmrAllocateUniqueTypeErasedDeleter< CompositeSink >(
                allocator
                , std::move( sinks ) );
    }

    explicit CompositeSink( Sinks sinks )
            : _sinks{ std::move( sinks ) }
    {}

    void consume( const RecordDataRefs& recDataRefs ) override
    {
        for ( auto& sink : _sinks ) sink->consume( recDataRefs );
    }

private:

    Sinks _sinks;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } } // namespace Elastic::Apm::Log
