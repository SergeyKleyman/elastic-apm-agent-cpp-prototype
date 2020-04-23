#pragma once

#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Impl/Log/LoggerFactory.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Util/assert_config.hxx"

namespace Elastic { namespace Apm { namespace Impl
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Impl::Util;

class AmbientContextRoot
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( AmbientContextRoot );

    explicit AmbientContextRoot( const PmrByteAllocator& allocator
                                 , const Log::LoggerFactory& loggerFactory
                                 , AssertLevel assertLevel = assertDefaultLevel
    )
            : _allocator{ allocator }
              , _loggerFactory{ loggerFactory }
              , _assertLevel{ assertLevel }
    {}

    PmrByteAllocator allocator() const
    {
        return _allocator;
    }

    const Log::LoggerFactory& loggerFactory() const
    {
        return _loggerFactory;
    }

    AssertLevel assertLevel() const
    {
        return _assertLevel;
    }

private:

    const PmrByteAllocator _allocator;
    const Log::LoggerFactory& _loggerFactory;
    AssertLevel _assertLevel;
};

} } } // namespace Elastic::Apm::Impl
