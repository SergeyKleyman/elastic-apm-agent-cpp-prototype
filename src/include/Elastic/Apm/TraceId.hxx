#pragma once

#include "Elastic/Apm/Util/BinaryId.hxx"

namespace Elastic { namespace Apm
{

//
// 128 random bits ID
//
// https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L14
// https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L19
//

class TraceId : public Util::BinaryId< 16 >
{
};

} } // namespace Elastic::Apm
