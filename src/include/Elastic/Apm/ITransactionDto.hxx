#pragma once

#include "Elastic/Apm/IExecutionSegmentDto.hxx"
#include "Elastic/Apm/Util/Optional.hxx"
#include "Elastic/Apm/Util/StringView.hxx"

namespace Elastic { namespace Apm
{

class ITransactionDto
        : public IExecutionSegmentDto
{
protected:

    using StringView = Util::StringView;

    template< typename T >
    using Optional = Util::Optional< T >;

public:

    //
    // Generic designation of a transaction in the scope of a single service (eg: 'GET /users/:id')
    //
    // https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L47
    //
    virtual Optional< StringView > getName() const = 0;

    //
    // ID of the parent transaction or span.
    // Only root transactions of a trace do not have a parent_id,
    // otherwise it needs to be set.
    //
    // https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L19
    //
    virtual const Optional< ExecutionSegmentId >& getParentId() const = 0;

protected:

    ~ITransactionDto() = default;
};

} } // namespace Elastic::Apm
