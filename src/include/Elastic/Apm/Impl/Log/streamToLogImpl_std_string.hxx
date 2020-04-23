#pragma once

#include "Elastic/Apm/Impl/Log/streamToLogImpl_base.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_fundamental.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

template< typename CharType, class CharTraits, class Allocator >
struct StreamToLogImpl< std::basic_string< CharType, CharTraits, Allocator > >
{
    using ValueType = std::basic_string< CharType, CharTraits, Allocator >;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl( const ValueType& val, IStream& logStream )
    {
        return logStream.writeCurrentValueContent( StringView{ val } );
    }
};

static_assert( HasStreamToLogImpl< std::string >::value, "" );

} } } } // namespace Elastic::Apm::Impl::Log
