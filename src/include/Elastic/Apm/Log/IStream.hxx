#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstddef.hxx" // std::nullptr_t
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdint.hxx" // uintmax_t, intmax_t
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/limits.hxx" // std::numeric_limits< T >::max()
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
#include "Elastic/Apm/Impl/Util/TypeTraits.hxx"
#include "Elastic/Apm/Impl/Log/BareTypeToLog.hxx"
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Log/IVisualStream.hxx"

namespace Elastic { namespace Apm { namespace Log
{

class IStream
{
protected:

    using StringView = Util::StringView;

public:

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual IVisualStream* asVisual() = 0;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool writeCurrentValueType( StringView type ) = 0;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool writeCurrentValueContent( std::nullptr_t /* val */ ) = 0;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool writeCurrentValueContent( bool val ) = 0;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool writeCurrentValueContent( uintmax_t val ) = 0;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool writeCurrentValueContent( intmax_t val ) = 0;

    template< typename T >
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    boost::enable_if_t< Impl::Util::IsSignedNumericInteger< T >::value && ! std::is_same< Impl::Log::BareTypeToLog< T >, intmax_t >::value, bool >
    writeCurrentValueContent( T val )
    {
        static_assert( std::numeric_limits< T >::max() <= std::numeric_limits< intmax_t >::max(), "" );
        return writeCurrentValueContent( static_cast< intmax_t >( val ) );
    }

    template< typename T >
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    boost::enable_if_t< Impl::Util::IsUnsignedNumericInteger< T >::value && ! std::is_same< Impl::Log::BareTypeToLog< T >, uintmax_t >::value, bool >
    writeCurrentValueContent( T val )
    {
        static_assert( std::numeric_limits< T >::max() <= std::numeric_limits< uintmax_t >::max(), "" );
        return writeCurrentValueContent( static_cast< uintmax_t >( val ) );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool writeCurrentValueContent( double val ) = 0;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool writeCurrentValueContent( StringView val ) = 0;

    class IMapBuilder
    {
    public:

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        virtual IStream* add( StringView key ) = 0;

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        virtual bool end() = 0;

    protected:

        ~IMapBuilder() = default;
    };

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual IMapBuilder* beginMap() = 0;

    class IListBuilder
    {
    public:

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        virtual IStream* add() = 0;

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        virtual bool end() = 0;

        template< typename WriteElement >
        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        bool addAndWriteElement( WriteElement&& writeElement )
        {
            auto elementStream = add();
            if ( ! elementStream ) return false;

            return std::forward< WriteElement >( writeElement )( *elementStream );
        }

    protected:

        ~IListBuilder() = default;
    };

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual IListBuilder* beginList() = 0;

//    template< typename WriteMapKeyValuePairsCall >
//    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
//    bool writeCurrentValueContentAsMap( WriteMapKeyValuePairsCall&& writeMapKeyValuePairsCall )
//    {
//        if ( auto mapStream = beginMap() )
//        {
//            if ( !std::forward< WriteMapKeyValuePairsCall >( writeMapKeyValuePairsCall )( *mapStream ) ) return false;
//            return mapStream->end();
//        }
//
//        return false;
//    }

    template< typename WriteListElements >
    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContentAsList( WriteListElements&& writeListElements )
    {
        if ( auto listStream = beginList() )
        {
            if ( !std::forward< WriteListElements >( writeListElements )( *listStream ) ) return false;
            return listStream->end();
        }

        return false;
    }

protected:

    ~IStream() = default;
};

} } } // namespace Elastic::Apm::Log
