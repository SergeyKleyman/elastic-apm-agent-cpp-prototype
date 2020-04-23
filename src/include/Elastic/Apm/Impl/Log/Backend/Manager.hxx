#pragma once

#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/vector.hxx"
#include "Elastic/Apm/Log/ISink.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Impl/Log/Backend/Facade.hxx"
#include "Elastic/Apm/Impl/Log/LoggerFactory.hxx"
#include "Elastic/Apm/Util/ISystemClock.hxx"
#include "Elastic/Apm/Impl/Config/Snapshot.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

using namespace Elastic::Apm::Log;
using namespace Elastic::Apm::Util;

class Manager
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( Manager );

    #ifdef _MSC_VER // Visual C++
    #   pragma warning( push, 0 )
    #   pragma warning( disable : 4355 ) // Compiler Warning C4355: 'this' : used in base member initializer list
    #endif

    explicit Manager( const PmrByteAllocator& allocator
                      , ISystemClock& systemClock
                      , ISink& sink
                      , const Config::Snapshot* /*cfgSnapWithInitSeqOptsOnly*/ = nullptr
    )
            : _allocator{ allocator }
              , _systemClock{ systemClock }
              , _sink{ sink }
              , _level{ Level::trace }
              , _facade{ *this }
              , _loggerFactory{ _facade }
    {}

    #ifdef _MSC_VER // Visual C++
    #   pragma warning( pop )
    #endif

    void consume( RecordDataRefs&& recDataRefs )
    {
        _sink.consume( recDataRefs );
    }

    bool isEnabled( Level statementLevel ) const
    {
        return isAtLeastAsImportantAs( statementLevel, _level );
    }

    const LoggerFactory& loggerFactory() const
    {
        return _loggerFactory;
    }

    SystemClockTimePoint genTimestamp() const
    {
        return _systemClock.now();
    }

private:

    const PmrByteAllocator _allocator;
    ISystemClock& _systemClock;
    ISink& _sink;
    Level _level;
    Facade _facade;
    LoggerFactory _loggerFactory;
};

} } } } } // namespace Elastic::Apm::Impl::Log::Backend

#ifndef ELASTIC_APM_SEPARATE_COMPILATION
#   include "Elastic/Apm/Impl/Log/Backend/Manager_impl.hxx"
#endif
