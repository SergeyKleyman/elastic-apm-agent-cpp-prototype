#pragma once

#include "Elastic/Apm/Impl/Util/Exception.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

class AssertionFailedException
    : public Exception
{
public:

    explicit AssertionFailedException( String message )
        : Exception{ std::move( message ) }
    {}
};

} } } } // namespace Elastic::Apm::Impl::Util
