#pragma once

#include "Elastic/Apm/IExecutionSegmentDto.hxx"

namespace Elastic { namespace Apm
{

template< class IExecutionSegmentDtoDerived >
class IExecutionSegment
        : public IExecutionSegmentDtoDerived
{
protected:

    using String = Util::String;

public:

    /**
     * @return Whether this execution segment is no-op
     */
    virtual bool isNoop() const = 0;

    /**
     * @see IExecutionSegmentDto::getType
     */
    virtual void setType( String type ) = 0;

    /**
     * @see IExecutionSegmentDto::forEachLabel
     */
    virtual void setLabel( String key, LabelValue value ) = 0;

protected:

    ~IExecutionSegment() = default;
};

} } // namespace Elastic::Apm
