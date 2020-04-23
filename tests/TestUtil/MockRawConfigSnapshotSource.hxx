#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx" // std::shared_ptr
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"
#include <initializer_list>
#include <boost/container/pmr/map.hpp>
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"
#include "Elastic/Apm/Config/IRawSnapshotSource.hxx"
#include "TestUtil/sharedPtrToUniqueTypeErasedDeleter.hxx"

namespace ElasticApmTests { namespace TestUtil
{

using namespace Elastic::Apm;

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class MockRawConfigSnapshotSource
        : public Config::IRawSnapshotSource
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( MockRawConfigSnapshotSource );

    explicit MockRawConfigSnapshotSource( const PmrByteAllocator& allocator )
            : _allocator{ allocator }
    {
        setCurrentSnapshot( OptionsMap{} );
    }

    PRawSnapshot currentSnapshot() override
    {
        return sharedPtrToUniqueTypeErasedDeleter( _currentSnapshot );
    }

    using OptionsMap = boost::container::pmr::map< String, String >;

    void setCurrentSnapshot( OptionsMap optionsMap );

    void setCurrentSnapshot( std::initializer_list< std::pair< StringView, StringView > > keyValuePairs );

private:

    const PmrByteAllocator _allocator;
    std::shared_ptr< Config::IRawSnapshot > _currentSnapshot;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } // namespace ElasticApmTests::TestUtil
