#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::pair
#include "Elastic/Apm/ExecutionSegmentId.hxx"
#include "Elastic/Apm/TraceId.hxx"
#include "Elastic/Apm/Util/SystemClockTimePoint.hxx"
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/LabelValue.hxx"

namespace Elastic { namespace Apm
{

class IExecutionSegmentDto
{
protected:

    using SystemClockTimePoint = Util::SystemClockTimePoint;
    using StringView = Util::StringView;

public:

    /**
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L9
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L9
     *
     * @return ID of this execution segment
     */
    virtual const ExecutionSegmentId& getId() const = 0;

    /**
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L14
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L19
     *
     * @return Trace-ID of this execution segment
     */
    virtual const TraceId& getTraceId() const = 0;

    /**
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/timestamp_epoch.json
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L6
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L6
     *
     * @return Start time of this execution segment (UTC based and formatted as microseconds since Unix epoch)
     */
    virtual SystemClockTimePoint getTimestamp() const = 0;

    /**
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L43
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L132
     *
     * @return Duration in milliseconds with 3 decimal points
     */
    virtual double getDuration() const = 0;

    /**
     * - For transaction:
     *      Keyword of specific relevance in the service's domain (eg: 'request', 'backgroundjob', etc)
     *          https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L57
     *
     *  - For span:
     *      Keyword of specific relevance in the service's domain (eg: 'db.postgresql.query', 'template.erb', etc)
     *          https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L149
     *
     * @return Type of this execution segment
     */
    virtual StringView getType() const = 0;

    using ForEachLabelCallback = bool (*)( void* callbackCtx, StringView key, LabelValue value );

    /**
     * labels is a flat mapping of user-defined tags with string, boolean or number values.
     * For string max length is 1024.
     *
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/tags.json
     *
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/transactions/transaction.json#L40
     *      https://github.com/elastic/apm-server/blob/7.0/docs/spec/context.json#L46
     *
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/spans/span.json#L88
     */
    virtual void forEachLabel( ForEachLabelCallback callback, void* callbackCtx ) const = 0;

protected:

    ~IExecutionSegmentDto() = default;
};

} } // namespace Elastic::Apm
