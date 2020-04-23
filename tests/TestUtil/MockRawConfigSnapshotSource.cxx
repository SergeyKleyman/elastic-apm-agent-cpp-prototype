#include "TestUtil/MockRawConfigSnapshotSource.hxx"
#include "TestUtil/unit_test_macros.hxx"

namespace ElasticApmTests { namespace TestUtil
{

using OptionsMap = MockRawConfigSnapshotSource::OptionsMap;

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class MockRawConfigSnapshot
        : public Config::IRawSnapshot
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( MockRawConfigSnapshot );

    explicit MockRawConfigSnapshot( OptionsMap optionsMap, const PmrByteAllocator& allocator )
            : _allocator{ allocator }
              , _optionsMap{ std::move( optionsMap ) }
    {}

    Optional< ValueData > operator []( const char* key ) const override
    {
        auto it = _optionsMap.find( String::assumeSufficientLifetime( StringView{ key } ) );
        if ( it == _optionsMap.end() ) return {};

        Optional< ValueData > retVal{ ValueData{} };
        retVal->value = String::copyOf( it->second, _allocator );
        retVal->dbgValueSourceDesc = String::fromLiteral( "MockRawConfigSnapshotSource" );
        return retVal;
    }

private:

    const PmrByteAllocator _allocator;
    OptionsMap _optionsMap;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

void MockRawConfigSnapshotSource::setCurrentSnapshot( OptionsMap optionsMap )
{
    _currentSnapshot = std::allocate_shared< MockRawConfigSnapshot >(
            _allocator
            , std::move( optionsMap )
            , _allocator );
}

void MockRawConfigSnapshotSource::setCurrentSnapshot( std::initializer_list< std::pair< StringView, StringView > > keyValuePairs )
{
    OptionsMap optsMap{ _allocator };

    for ( const auto& keyValuePair : keyValuePairs )
    {
        auto emplaceRetVal = optsMap.emplace(
                String::copyOf( keyValuePair.first, _allocator )
                , String::copyOf( keyValuePair.second, _allocator ) );

        UT_ASSERT( emplaceRetVal.second );
    }

    setCurrentSnapshot( std::move( optsMap ) );
}

} } // namespace ElasticApmTests::TestUtil
