#pragma once

#include "Elastic/Apm/IExecutionSegment.hxx"
#include "Elastic/Apm/ITransactionDto.hxx"
#include "Elastic/Apm/Util/String.hxx"

namespace Elastic { namespace Apm
{

class ITransaction
        : public IExecutionSegment< ITransactionDto >
{
protected:

    using String = Util::String;

public:

    virtual void setName( Optional< String > name ) const = 0;
    virtual void setParentId( const Optional< ExecutionSegmentId >& parentId ) const = 0;

protected:

    ~ITransaction() = default;
};

} } // namespace Elastic::Apm
