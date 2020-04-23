#pragma once

#include "Elastic/Apm/Impl/Log/Logger.hxx"
#include "Elastic/Apm/Impl/Log/Backend/Facade.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Util/class_name_from_member_function.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

class LoggerFactory
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( LoggerFactory );

    explicit LoggerFactory( Backend::Facade& backend )
            : _backend{ backend }
    {
    }

    Logger createLoggerForClass( String fqClassName ) const
    {
        return Logger{ _backend, std::move( fqClassName ) };
    }

private:

    Backend::Facade& _backend;
};

} } } } // namespace Elastic::Apm::Impl::Log
