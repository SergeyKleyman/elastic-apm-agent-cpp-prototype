#pragma once

#include "Elastic/Apm/Log/IStream.hxx"

namespace Elastic { namespace Apm { namespace Log
{

using namespace Elastic::Apm::Util;

class IStreamable
{
public:

    virtual StringView preprocessExprToLogNameImpl( StringView outerName ) const = 0;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool streamToLogImpl( IStream& logStream ) const = 0;

protected:

    ~IStreamable() = default;
};

} } } // namespace Elastic::Apm::Log
