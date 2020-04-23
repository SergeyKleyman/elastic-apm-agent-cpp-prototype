#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstddef.hxx" // std::nullptr_t
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/limits.hxx" // std::numeric_limits< T >::max()
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Impl/Util/TypeTraits.hxx"
#include "Elastic/Apm/Impl/Log/BareTypeToLog.hxx"
#include "Elastic/Apm/Impl/Util/OnScopeExit.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"

namespace Elastic { namespace Apm { namespace Log
{

class IVisualStream
{
protected:

    using StringView = Util::StringView;
    using PmrByteAllocator = Util::PmrByteAllocator;

public:

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool write( bool val )
    {
        return write( val ? Util::literalToView( "true" ) : Util::literalToView( "false" ) );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool write( std::nullptr_t /* val */ )
    {
        return write( Util::literalToView( "<null>" ) );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool write( StringView val ) = 0;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool write( double val ) = 0;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool write( char val )
    {
        return write( StringView{ &val, 1 } );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool write( intmax_t val ) = 0;

    template< typename T >
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    boost::enable_if_t< Impl::Util::IsSignedNumericInteger< T >::value && ! std::is_same< Impl::Log::BareTypeToLog< T >, intmax_t >::value, bool >
    write( T val )
    {
        static_assert( std::numeric_limits< T >::max() <= std::numeric_limits< intmax_t >::max(), "" );

        return write( static_cast< intmax_t >( val ) );
    }

    /// padToLength == 0 - no padding
    /// padToLength > 0 - padding on the left:  |    123|
    /// padToLength < 0 - padding on the right  |123    |

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool write( uintmax_t val, bool isHex, int padToLength, char paddingChar, bool showBase ) = 0;

    template< typename T >
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    boost::enable_if_t< Impl::Util::IsUnsignedNumericInteger< T >::value, bool >
    write( T val, int padToLength = 0, char paddingChar = ' ' )
    {
        static_assert( std::numeric_limits< T >::max() <= std::numeric_limits< uintmax_t >::max(), "" );

        return write( static_cast< uintmax_t >( val ), /* isHex: */ false, padToLength, paddingChar, /* showBase: */ false );
    }

    template< typename T >
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    boost::enable_if_t< Impl::Util::IsUnsignedNumericInteger< T >::value, bool >
    writeHex( T val, int padToLength = 0, char paddingChar = ' ', bool showBase = true )
    {
        static_assert( std::numeric_limits< T >::max() <= std::numeric_limits< uintmax_t >::max(), "" );

        return write( static_cast< uintmax_t >( val ), /* isHex: */ true, padToLength, paddingChar, showBase );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool increaseNesting() = 0;

    virtual void decreaseNesting() = 0;

    template< typename NestedWriteCall >
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeNested( NestedWriteCall&& nestedWriteCall )
    {
        if ( ! increaseNesting() ) return false;
        ELASTIC_APM_ON_SCOPE_EXIT(( [&](){ decreaseNesting(); } ));

        return std::forward< NestedWriteCall >( nestedWriteCall )();
    }

    virtual PmrByteAllocator allocator() const = 0;

protected:

    ~IVisualStream() = default;
};


} } } // namespace Elastic::Apm::Log
