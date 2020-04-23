#pragma once

#include "Elastic/Apm/ITransaction.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/ExecutionSegment.hxx"

namespace Elastic { namespace Apm { namespace Impl
{

class Transaction
        : public ExecutionSegment< ITransaction >
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( Transaction );

    Transaction( Optional< String > name,  )
    {}

private:

    Optional< String > _name;
};

} } } // namespace Elastic::Apm::Impl
