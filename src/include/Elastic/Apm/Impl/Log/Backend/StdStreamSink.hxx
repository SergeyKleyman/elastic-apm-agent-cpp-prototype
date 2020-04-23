#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/iostream.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/mutex.hxx"
#include "Elastic/Apm/Impl/Log/Backend/TextSinkBase.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class StdStreamSink
        : public TextSinkBase< StdStreamSink >
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( StdStreamSink );

    explicit StdStreamSink( const PmrByteAllocator& allocator, String linePrefix = String{} )
            : Base{ allocator, std::move( linePrefix ) }
    {}

private:

    using Base = TextSinkBase< StdStreamSink >;
    friend Base;

    void consume( const RecordDataRefs& recDataRefs, const char* formattedRecord )
    {
        const std::lock_guard< std::mutex > lockGuard( _mutex );

        ( isMoreImportantThan( recDataRefs.level, Level::info ) ? std::cerr : std::clog ) << formattedRecord;
    }

private:

    std::mutex _mutex;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } } } } // namespace Elastic::Apm::Impl::Log::Backend
