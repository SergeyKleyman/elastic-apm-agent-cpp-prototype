#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstddef.hxx" // std::nullptr_t
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdint.hxx" // uint64_t, int64_t
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/limits.hxx" // std::numeric_limits< T >::max()
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Impl/Util/TypeTraits.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

using namespace Elastic::Apm::Util;

class IJsonWriter
{
public:

    class IObjectWriter
    {
    public:

        virtual IJsonWriter& add( StringView key ) = 0;
        virtual void end() = 0;

    protected:

        ~IObjectWriter() = default;
    };

    class IArrayWriter
    {
    public:

        virtual IJsonWriter& add() = 0;
        virtual void end() = 0;

    protected:

        ~IArrayWriter() = default;
    };

    virtual IObjectWriter& beginObject() = 0;

    virtual IArrayWriter& beginArray() = 0;

    virtual void write( std::nullptr_t /* val */ ) = 0;
    virtual void write( bool val ) = 0;
    virtual void write( int64_t val ) = 0;
    virtual void write( uint64_t val ) = 0;
    virtual void write( double val ) = 0;
    virtual void write( StringView val, std::size_t maxLength ) = 0;

protected:

    ~IJsonWriter() = default;
};

} } } } // namespace Elastic::Apm::Impl::Util
