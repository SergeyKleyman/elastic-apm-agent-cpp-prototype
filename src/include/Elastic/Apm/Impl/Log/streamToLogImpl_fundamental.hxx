#pragma once

#include "Elastic/Apm/Impl/Log/streamToLogImpl_pointers.hxx"
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Util/String.hxx"

namespace Elastic { namespace Apm { namespace Impl
{
namespace Log
{

namespace Internals
{

using String = Elastic::Apm::Util::String;
using StringView = Elastic::Apm::Util::StringView;

template< typename T >
struct HasStreamDirectWrite
{
    static constexpr bool value = std::is_same< T, std::nullptr_t >::value
                                  || std::is_same< T, bool >::value
                                  || Util::IsNumericInteger< T >::value
                                  || std::is_floating_point< T >::value
                                  || std::is_same< T, String >::value
                                  || std::is_same< T, StringView >::value
                                  || std::is_same< T, char* >::value;
};

} // namespace Internals

template< typename T >
struct StreamToLogImpl< T, boost::enable_if_t< Internals::HasStreamDirectWrite< BareTypeToLog< T > >::value > >
{
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl( const T& t, IStream& logStream )
    {
        return logStream.writeCurrentValueContent( t );
    }
};

}
} } } // namespace Elastic::Apm::Impl::Log
