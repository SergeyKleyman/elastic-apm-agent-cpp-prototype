#pragma once

#include "Elastic/Apm/IExecutionSegmentDto.hxx"
#include "Elastic/Apm/Util/StringView.hxx"

namespace Elastic { namespace Apm
{

class ISpanDto
        : public IExecutionSegmentDto
{
protected:

    using StringView = Util::StringView;

public:

    //
    // ID of the parent transaction or span
    //
    // https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L24
    //
    virtual const ExecutionSegmentId& getParentId() const = 0;

    //
    // Generic designation of a span in the scope of a transaction
    //
    // https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L136
    //
    virtual StringView getName() const = 0;

protected:

    ~ISpanDto() = default;
};

} } // namespace Elastic::Apm
