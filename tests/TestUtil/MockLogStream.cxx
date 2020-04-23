#include "TestUtil/MockLogStream.hxx"
#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Impl/Util/pmrAllocateUnique.hxx"

namespace ElasticApmTests { namespace TestUtil
{

bool MockLogStream::writeCurrentValueType( StringView type )
{
    UT_ASSERT( ! _hasValueWritten(), "This stream's root value already has been written" );

    _value.type = String::copyOf( type, _allocator );
    return true;
}

bool MockLogStream::writeCurrentValueContent( std::nullptr_t /* val */ )
{
    UT_ASSERT( ! _hasValueWritten(), "This stream's root value already has been written" );

    _value.content = nullptr;
    return true;
}

bool MockLogStream::writeCurrentValueContent( bool val )
{
    UT_ASSERT( ! _hasValueWritten(), "This stream's root value already has been written" );

    _value.content = val;
    return true;
}

bool MockLogStream::writeCurrentValueContent( uintmax_t val )
{
    UT_ASSERT( ! _hasValueWritten(), "This stream's root value already has been written" );

    _value.content = val;
    return true;
}

bool MockLogStream::writeCurrentValueContent( intmax_t val )
{
    UT_ASSERT( ! _hasValueWritten(), "This stream's root value already has been written" );

    _value.content = val;
    return true;
}

bool MockLogStream::writeCurrentValueContent( double val )
{
    UT_ASSERT( ! _hasValueWritten(), "This stream's root value already has been written" );

    _value.content = val;
    return true;
}

bool MockLogStream::writeCurrentValueContent( StringView val )
{
    UT_ASSERT( ! _hasValueWritten(), "This stream's root value already has been written" );

    _value.content = String::copyOf( val, _allocator );
    return true;
}

IStream::IMapBuilder* MockLogStream::beginMap()
{
    UT_ASSERT( !_hasCompositeBuilder(), "This stream's root value already has composite builder" );
    UT_ASSERT( ! _hasValueWritten(), "This stream's root value already has been written" );

    _value.content = MapContent{ _allocator };
    _compositeBuilder = MapBuilder{ _allocator, boost::get< MapContent >( _value.content ) };
    return &( boost::get< MapBuilder >( _compositeBuilder ) );
}

IStream* MockLogStream::MapBuilder::add( StringView key )
{
    UT_ASSERT( ( !_currentValueStream ) || _currentValueStream->_hasValueWritten()
               , "New key-value pair should not be started before value for the current key-value pair is written" );

    _mapContent->emplace_back( String::copyOf( key, _allocator ), Value{} );
    _currentValueStream = pmrAllocateUnique< MockLogStream >( _allocator, _allocator, _mapContent->back().second );
    return _currentValueStream.get();
}

bool MockLogStream::MapBuilder::end()
{
    UT_ASSERT( ( !_currentValueStream ) || _currentValueStream->_hasValueWritten()
               , "Map should not be ended before value for the current key-value pair is written" );

    return true;
}

IStream::IListBuilder* MockLogStream::beginList()
{
    UT_ASSERT( !_hasCompositeBuilder(), "This stream's root value already has composite builder" );
    UT_ASSERT( ! _hasValueWritten(), "This stream's root value already has been written" );

    _value.content = ListContent{ _allocator };
    _compositeBuilder = ListBuilder{ _allocator, boost::get< ListContent >( _value.content ) };
    return &( boost::get< ListBuilder >( _compositeBuilder ) );
}

IStream* MockLogStream::ListBuilder::add()
{
    UT_ASSERT( ( !_currentValueStream ) || _currentValueStream->_hasValueWritten()
               , "New list value should not be started before the current list value is written" );

    _listContent->emplace_back( Value{} );
    _currentValueStream = pmrAllocateUnique< MockLogStream >( _allocator, _allocator, _listContent->back() );
    return _currentValueStream.get();
}

bool MockLogStream::ListBuilder::end()
{
    UT_ASSERT( ( !_currentValueStream ) || _currentValueStream->_hasValueWritten()
               , "List should not be ended before the current value is written" );

    return true;
}

} } // namespace ElasticApmTests::TestUtil
