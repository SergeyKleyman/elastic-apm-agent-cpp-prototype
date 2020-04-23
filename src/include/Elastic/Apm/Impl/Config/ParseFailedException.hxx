#pragma once

#include "Elastic/Apm/Impl/Util/Exception.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

using namespace Elastic::Apm::Impl::Util;

class ParseFailedException
        : public Exception
{
public:

    explicit ParseFailedException( String message )
            : Exception{ std::move( message ) }
    {}
};

} } } } // namespace Elastic::Apm::Impl::Config
