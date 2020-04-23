#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdint.hxx" // uint8_t
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/array.hxx" // uint8_t
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Util/Optional.hxx"
#include "Elastic/Apm/Impl/Util/basic_util.hxx"

namespace Elastic { namespace Apm { namespace Log
{

/**
 * The order is important because lower numeric values are considered contained in higher ones
 * for example `error` means that both `error` and `critical` is enabled.
 */
enum class Level: uint8_t
{
    off = 0,

    critical,
    error,
    warning,
    notice,
    info,
    debug,
    trace,

    all
};

enum
{
    numberOfLevels = static_cast< unsigned int >( Level::all ) + 1
};

inline
bool isMoreImportantThan( Level lhs, Level rhs )
{
    return lhs < rhs;
}

inline
bool isAtLeastAsImportantAs( Level lhs, Level rhs )
{
    return lhs <= rhs;
}

inline
constexpr std::array< Util::StringView, numberOfLevels > levelNames()
{
    return
            {
                    "OFF",
                    "CRITICAL",
                    "ERROR",
                    "WARNING",
                    "NOTICE",
                    "INFO",
                    "DEBUG",
                    "TRACE",
                    "ALL"
            };
}

inline
Util::Optional< Util::StringView > levelName( Level level )
{
    auto levelNamesArray = levelNames();
    if ( static_cast< uint8_t >( level ) < levelNamesArray.size() )
    {
        return levelNamesArray[ static_cast< uint8_t >( level ) ];
    }

    return {};
}

} } } // namespace Elastic::Apm::Log
