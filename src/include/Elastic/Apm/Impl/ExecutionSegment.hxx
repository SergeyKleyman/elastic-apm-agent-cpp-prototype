#pragma once

#include "Elastic/Apm/IExecutionSegment.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Tracer.hxx"

namespace Elastic { namespace Apm { namespace Impl
{

using namespace Elastic::Apm::Util;

template< class IExecutionSegmentDerived >
class ExecutionSegment
        : public IExecutionSegmentDerived
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( ExecutionSegment );

    ExecutionSegment( Tracer& tracer, String type )
            : _tracer{ tracer }
              , _type{ std::move( type ) }
    {}

    const ExecutionSegmentId& getId() const override
    {
        return _id;
    }

    void setType( String type ) override
    {

    }

    void setLabel( String key, LabelValue value ) override
    {

    }

private:

    Tracer& _tracer;
    ExecutionSegmentId _id;
    String _type;
};

} } } // namespace Elastic::Apm::Impl
