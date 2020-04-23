#pragma once

#include "Elastic/Apm/Impl/Util/SystemClockTimePoint_toLog.hxx"
#include "Elastic/Apm/Impl/Log/Backend/PmrOutputStringStream.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/chrono/io/time_point_io.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
ELASTIC_APM_INLINE_FOR_IMPL
bool streamToVisualLogImpl( SystemClockTimePoint timePoint, IVisualStream& logVisualStream )
{
    // boost::chrono prints nanoseconds:
    //
    //          2020-04-12 14:56:17.933835123 +0300
    //
    // while it's enough to have microseconds:
    //
    //          2020-04-12 14:56:17.933835 +0300

    Elastic::Apm::Impl::Log::Backend::PmrOutputStringStream<> auxOutStringStream{ logVisualStream.allocator() };
    auxOutStringStream.get()
            << boost::chrono::time_fmt( boost::chrono::timezone::local )
            << boost::chrono::time_point_cast< boost::chrono::microseconds >( timePoint );

    auto timePointAsString = auxOutStringStream.get().str();

    // convert "2020-04-12 14:56:17.933835000 +0300" to "2020-04-12 14:56:17.933835 +0300"
    //                                    ^^^ - starts at position 26 (counting from 0)
    constexpr std::string::size_type nanoSecondsPos = 26;
    constexpr auto expectedNanoSeconds = literalToView( "000 " );
    if ( ( nanoSecondsPos + expectedNanoSeconds.length() <= timePointAsString.length() )
         && ( StringView{ &timePointAsString[ nanoSecondsPos ], expectedNanoSeconds.length() } == expectedNanoSeconds ) )
    {
        // -1 to leave space before timezone's UTC offset
        timePointAsString.erase( nanoSecondsPos, expectedNanoSeconds.length() - 1 );
    }

    return logVisualStream.write( timePointAsString );
}

} } } } // namespace Elastic::Apm::Impl::Util
