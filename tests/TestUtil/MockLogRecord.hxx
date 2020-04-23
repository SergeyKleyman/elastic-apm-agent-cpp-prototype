#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/variant.hxx"
#include "Elastic/Apm/Util/Optional.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Log/RecordDataRefs.hxx"
#include "Elastic/Apm/Util/String.hxx"
#include "Elastic/Apm/Impl/Util/PmrBoostVector.hxx"

namespace ElasticApmTests { namespace TestUtil
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Log;
using namespace Elastic::Apm::Impl::Util;

class MockLogRecord
{
public:

    ELASTIC_APM_MOVE_CONSTRUCTIBLE_BUT_NOT_MOVE_ASSIGNABLE( MockLogRecord );

    explicit MockLogRecord( const RecordDataRefs& recDataRefs, const PmrByteAllocator& allocator );

    struct SourceCodeLocation
    {
        String filePath;
        uint32_t lineNumber = 0;
        String ppFqFunction;
        String ppFunction;
        String cppFunc;
        String fqClassName;
    };

    struct ContextValue
    {
        ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( ContextValue );

        /// We intentionally use boost::vector because it allows incomplete types
        /// while std::vector doesn't.
        /// See https://www.boost.org/doc/libs/1_72_0/doc/html/container/main_features.html#container.main_features.containers_of_incomplete_types
        using ListContent = PmrBoostVector< ContextValue >;

        using MapContent = PmrBoostVector< std::pair< String, ContextValue > >;

        using Content = boost::variant<
                // the default is boost::blank is not just for exception safety
                // (see https://www.boost.org/doc/libs/1_72_0/doc/html/variant/design.html#variant.design.never-empty)
                // but also because value can indeed be optional
                boost::blank
                , std::nullptr_t
                , bool
                , intmax_t
                , uintmax_t
                , double
                , String
                , ListContent
                , MapContent >;

        Optional< String > type;
        Content content;
    };

    SystemClockTimePoint timestamp;
    Level level = Level::off;
    SourceCodeLocation sourceCodeLocation;
    String message;
    ContextValue::MapContent contextExprs;
};

} } // namespace ElasticApmTests::TestUtil
