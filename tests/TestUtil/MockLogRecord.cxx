#include "TestUtil/MockLogRecord.hxx"
#include "TestUtil/MockLogStream.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/type_traits.hxx"
#include "TestUtil/unit_test_macros.hxx"
#include "TestUtil/unit_test_util.hxx"

namespace ElasticApmTests { namespace TestUtil
{

namespace Internals
{

#define ELASTIC_APM_TESTS_DEEP_COPY_FIELD( fieldName ) deepCopyRecordDataRefs( src.fieldName, /* out */ dst.fieldName, allocator )

void deepCopyRecordDataRefs( SystemClockTimePoint src, SystemClockTimePoint& dst, const PmrByteAllocator& /* allocator */ )
{
    dst = src;
}

template< typename T >
boost::enable_if_t< std::is_enum< T >::value || std::is_integral< T >::value, void > // NOLINT(misc-redundant-expression)
deepCopyRecordDataRefs( T src, T& dst, const PmrByteAllocator& /* allocator */ )
{
    dst = src;
}

void deepCopyRecordDataRefs( StringView src, String& dst, const PmrByteAllocator& allocator )
{
    dst = String::copyOf( src, allocator );
}

void deepCopyRecordDataRefs( const RecordDataRefs::SourceCodeLocation& src
                             , MockLogRecord::SourceCodeLocation& dst
                             , const PmrByteAllocator& allocator
)
{
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( filePath );
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( lineNumber );
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( ppFqFunction );
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( ppFunction );
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( cppFunc );
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( fqClassName );
}

void deepCopyRecordDataRefs( const decltype( RecordDataRefs::contextExprs )& src
                             , decltype( MockLogRecord::contextExprs )& dst
                             , const PmrByteAllocator& allocator
)
{
    for ( const auto& srcNameValue : src )
    {
        dst.emplace_back( String::copyOf( srcNameValue.stringizedExpr, allocator ), MockLogRecord::ContextValue{} );
        MockLogStream logStream{ allocator, dst.back().second };
        if ( srcNameValue.exprValue )
        {
            UT_ASSERT( srcNameValue.exprValue->streamToLogImpl( logStream ) );
        }
    }
}

void deepCopyRecordDataRefs( const RecordDataRefs& src
                             , MockLogRecord& dst
                             , const PmrByteAllocator& allocator
)
{
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( timestamp );
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( level );
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( sourceCodeLocation );
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( message );
    ELASTIC_APM_TESTS_DEEP_COPY_FIELD( contextExprs );
}

#undef ELASTIC_APM_TESTS_DEEP_COPY_FIELD

} // namespace Internals

MockLogRecord::MockLogRecord( const RecordDataRefs& recDataRefs, const PmrByteAllocator& allocator )
{
    Internals::deepCopyRecordDataRefs( recDataRefs, *this, allocator );
}

} } // namespace ElasticApmTests::TestUtil
