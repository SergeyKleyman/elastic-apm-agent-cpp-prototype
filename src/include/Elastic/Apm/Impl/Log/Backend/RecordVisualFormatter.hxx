#pragma once

// 2020-02-15 21:51:32.123456 +0200 | ERROR    | 12345:0xABCDEF01 | lifecycle.c:482                          | sendEventsToApmServer                    | Couldn't connect to server blah blah blah blah blah blah blah blah
// 2020-02-15 21:51:32.123456 +0200 | WARNING  | 12345:0xABCDEF01 | Config/Manager.c:45                      | constructSnapshotUsingDefaults           | Not found blah blah blah blah blah blah blah blah
// 2020-02-15 21:51:32.123456 +0200 | CRITICAL |   345:0xABCDEF01 | Config/OptionMetadataBase.hxx:56         | constructSnapshotUsingDefaults           | Send failed. Error message: Couldn't connect to server. server_url: `http://localhost:8200'
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   ^^^^^^^^   ^^^^^ ^^^^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// ^                                  ^          ^     ^            ^                                          ^                                          Message text
// ^                                  ^          ^     ^            ^                                          function name (padded with spaces on the right to 40 chars)
// ^                                  ^          ^     ^            file name:line number (padded with spaces on the right to 40 chars)
// ^                                  ^          ^     thread ID (padded with spaces on the left to 5 chars)
// ^                                  ^          process ID (padded with spaces on the left to 5 chars)
// ^                                  level (padded with spaces on the right to 8 chars)
// timestamp (no padding)

#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Log/RecordDataRefs.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Util/PmrString.hxx"
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Util/PmrVector.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Log;
using namespace Elastic::Apm::Impl::Util;
using namespace Elastic::Apm::Impl::Log;

class RecordVisualFormatter
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( RecordVisualFormatter );

    explicit RecordVisualFormatter( const PmrByteAllocator& allocator, String linePrefix );

    PmrString format( const RecordDataRefs& recDataRefs ) const;

    using CachedSrcFilePathPrefixesToCut = PmrVector< StringView >;

private:

    const PmrByteAllocator _allocator;
    const String _linePrefix;
    CachedSrcFilePathPrefixesToCut _cachedSrcFilePathPrefixesToCut;
};

} } } } } // namespace Elastic::Apm::Impl::Log::Backend

#ifndef ELASTIC_APM_SEPARATE_COMPILATION
#   include "Elastic/Apm/Impl/Log/Backend/RecordVisualFormatter_impl.hxx"
#endif
