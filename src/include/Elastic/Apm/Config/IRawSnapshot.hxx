#pragma once

#include "Elastic/Apm/Util/String.hxx"
#include "Elastic/Apm/Util/Optional.hxx"

namespace Elastic { namespace Apm { namespace Config
{

using namespace Elastic::Apm;

class IRawSnapshot
{
protected:

    using String = Util::String;

    template< typename T >
    using Optional = Util::Optional< T >;

public:

    struct ValueData
    {
        String value;
        String dbgValueSourceDesc;
    };

    virtual Optional< ValueData > operator[]( const char* optName ) const = 0;

protected:

    ~IRawSnapshot() = default;
};

} } } // namespace Elastic::Apm::Config
