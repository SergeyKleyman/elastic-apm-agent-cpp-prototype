#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/limits.hxx" // std::numeric_limits< T >::max()
#include "Elastic/Apm/Impl/Log/streamToLogImpl_base.hxx"
#include "Elastic/Apm/Impl/Log/BareTypeToLog.hxx"
#include "Elastic/Apm/Impl/Log/write_obj_fields_as_map.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Log;

template<>
struct StreamToLogImpl< char* >
{
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl( const char* zeroTermString, IStream& logStream )
    {
        return logStream.writeCurrentValueContent( StringView{ zeroTermString } );
    }
};

using VoidPtrRecordContextValueContent = uintmax_t;
static_assert( std::numeric_limits< uintptr_t >::max() <= std::numeric_limits< VoidPtrRecordContextValueContent >::max(), "" );

constexpr uint8_t calcNumberOfHexDigitsInPointer()
{
    return ( sizeof( void* ) / 8 ) * 2;
}

constexpr uint8_t numberOfHexDigitsInPointer = calcNumberOfHexDigitsInPointer();

constexpr StringView pointerTypeName()
{
    return literalToView( "pointer" );
}

template<>
struct StreamToLogImpl< void* >
{
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToVisualLogImpl( const void* ptr, IVisualStream& logVisualStream )
    {
        if ( ptr == nullptr ) return logVisualStream.write( nullptr );

        return logVisualStream.writeHex(
                static_cast< VoidPtrRecordContextValueContent >( reinterpret_cast< uintptr_t >( ptr ) )
                , /* padToLength: */ numberOfHexDigitsInPointer );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl( const void* ptr, IStream& logStream )
    {
        if ( auto logVisualStream = logStream.asVisual() ) return streamToVisualLogImpl( ptr, *logVisualStream );

        if ( ! logStream.writeCurrentValueType( pointerTypeName() ) ) return false;

        if ( ptr == nullptr ) return logStream.writeCurrentValueContent( nullptr );

        return logStream.writeCurrentValueContent(
                static_cast< VoidPtrRecordContextValueContent >( reinterpret_cast< uintptr_t >( ptr ) ) );
    }
};

template< typename T >
struct StreamToLogImpl< T*, boost::enable_if_t< HasStreamToLogImpl< T >::value > >
{
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToVisualLogImpl( const T* ptr, IVisualStream& logVisualStream )
    {
        if ( ! StreamToLogImpl< void* >::streamToVisualLogImpl( ptr, logVisualStream ) ) return false;

        if ( ptr == nullptr ) return true;

        return logVisualStream.writeNested( [ & ]()
                                            { return streamToLog( *ptr, logVisualStream ); } );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    static bool streamToLogImpl( const T* ptr, IStream& logStream )
    {
        if ( auto logVisualStream = logStream.asVisual() ) return streamToVisualLogImpl( ptr, *logVisualStream );

        if ( ptr == nullptr ) return logStream.writeCurrentValueContent( nullptr );

        if ( ! logStream.writeCurrentValueType( pointerTypeName() ) ) return false;

        ELASTIC_APM_WRITE_OBJ_FIELDS_AS_MAP(
                logStream
                , ( literalToView( "address" ), static_cast< const void* >( ptr ) )
                , ( literalToView( "pointee" ), *ptr )
        );

        return true;
    }
};

} } } } // namespace Elastic::Apm::Impl::Log
