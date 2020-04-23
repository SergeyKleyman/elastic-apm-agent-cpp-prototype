#pragma once

#include "Elastic/Apm/ITransactionDto.hxx"
#include "Elastic/Apm/ISpanDto.hxx"

namespace Elastic { namespace Apm
{

class IEventSink
{
public:

    virtual void send( const ISpanDto& spanDto ) = 0;
    virtual void send( const ITransactionDto& transactionDto ) = 0;

protected:

    ~IEventSink() = default;
};

} } // namespace Elastic::Apm
