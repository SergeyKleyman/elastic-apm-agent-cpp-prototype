#pragma once

#include "Elastic/Apm/Util/PmrUniquePtr.hxx"

namespace Elastic { namespace Apm
{

class ITracer
{
public:

    /**
     * @return Whether this tracer is no-op
     */
    virtual bool isNoop() const = 0;

protected:

    ~ITracer() = default;
};

using PTracer = Util::PmrUniquePtr< ITracer >;

} } // namespace Elastic::Apm
