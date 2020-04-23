#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/mutex.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Log/RecordDataRefs.hxx"
#include "Elastic/Apm/Util/PmrVector.hxx"
#include "Elastic/Apm/Util/PmrUniquePtr.hxx"
#include "Elastic/Apm/Impl/Util/pmrAllocateUnique.hxx"
#include "TestUtil/MockLogRecord.hxx"
#include "remove_const_from_this.hxx"

namespace ElasticApmTests { namespace TestUtil
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Log;
using namespace Elastic::Apm::Impl::Log;

class MockLogger
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( MockLogger );

    explicit MockLogger( const PmrByteAllocator& allocator, Level level = Level::all )
            : _allocator{ allocator }
              , _records{ allocator }
              , _level{ level }
    {
    }

    bool isEnabled( Level statementLevel ) const
    {
        return _level >= statementLevel;
    }

    void consume( const RecordDataRefs& recDataRefs ) const
    {
        const std::lock_guard< std::mutex > lockGuard( _recordsMutex );
        _records.push_back( pmrAllocateUnique< MockLogRecord >( _allocator, recDataRefs, _allocator ) );
    }

    using PRecord = PmrUniquePtr< MockLogRecord >;
    using Records = PmrVector< PRecord >;

    Records takeRecords()
    {
        Records result;
        result = std::move( _records );
        _records.clear();
        return result;
    }

private:

    PmrByteAllocator _allocator;
    mutable Records _records;
    mutable std::mutex _recordsMutex;
    Level _level;
};

} } // namespace ElasticApmTests::TestUtil
