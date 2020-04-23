#pragma once

#include "Elastic/Apm/Util/BinaryId.hxx"

namespace Elastic { namespace Apm
{

//
// 64 random bits ID
//
// https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L9
// https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L9
//

class ExecutionSegmentId : public Util::BinaryId< 8 >
{
};

} } // namespace Elastic::Apm
