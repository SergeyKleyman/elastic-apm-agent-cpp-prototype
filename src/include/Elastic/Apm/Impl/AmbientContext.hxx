#pragma once

#include "Elastic/Apm/Impl/AmbientContextRoot.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Log/Logger.hxx"

namespace Elastic { namespace Apm { namespace Impl
{

class AmbientContext
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( AmbientContext );

    explicit AmbientContext( const AmbientContext& parentContext, String fqClassName )
            : _root{ parentContext._root }
              , _logger{ _root.loggerFactory().createLoggerForClass( std::move( fqClassName ) ) }
    {}

    explicit AmbientContext( const AmbientContextRoot& root, String fqClassName )
            : _root{ root }
              , _logger{ _root.loggerFactory().createLoggerForClass( std::move( fqClassName ) ) }
    {}

    PmrByteAllocator allocator() const
    {
        return _root.allocator();
    }

    AssertLevel assertLevel() const
    {
        return _root.assertLevel();
    }

    const Log::Logger& logger() const
    {
        return _logger;
    }

private:

    const AmbientContextRoot& _root;
    const Log::Logger _logger;
};

} } } // namespace Elastic::Apm::Impl
