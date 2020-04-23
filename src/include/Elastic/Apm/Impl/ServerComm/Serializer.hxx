#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstddef.hxx" // std::size_t
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/variadic/to_seq.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/seq/for_each_i.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/stringize.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/tuple/elem.hxx"
#include "Elastic/Apm/Impl/Util/IJsonWriter.hxx"
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Util/String.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace ServerComm
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Impl::Util;

struct KeywordString
{
    KeywordString( String value )
        : value{ std::move( value ) }
    {}

    String value;
};

struct NonKeywordString
{
    String value;
};

class Serializer
{
public:

    explicit Serializer( IJsonWriter& jsonWriter )
        : _jsonWriter{ jsonWriter }
    {}

    IJsonWriter& jsonWriter()
    {
        return _jsonWriter;
    }

    friend void operator >>( std::nullptr_t val, Serializer& serializer )
    {
        serializer._jsonWriter.write( val );
    }

    friend void operator >>( bool val, Serializer& serializer )
    {
        serializer._jsonWriter.write( val );
    }

    friend void operator >>( double val, Serializer& serializer )
    {
        serializer._jsonWriter.write( val );
    }

    friend void operator >>( const KeywordString& val, Serializer& serializer )
    {
        serializer._jsonWriter.write( val.value, Serializer::_maxKeywordStringLength() );
    }

    friend void operator >>( const NonKeywordString& val, Serializer& serializer )
    {
        serializer._jsonWriter.write( val.value, serializer._maxNonKeywordStringLength );
    }

    template< typename T >
    friend
    boost::enable_if_t< Impl::Util::IsSignedNumericInteger< T >::value, void >
    operator >>( T val, Serializer& serializer )
    {
        static_assert( std::numeric_limits< T >::max() <= std::numeric_limits< int64_t >::max(), "" );
        return serializer._jsonWriter.write( static_cast< int64_t >( val ) );
    }

    template< typename T >
    friend
    boost::enable_if_t< Impl::Util::IsUnsignedNumericInteger< T >::value, void >
    operator >>( T val, Serializer& serializer )
    {
        static_assert( std::numeric_limits< T >::max() <= std::numeric_limits< uint64_t >::max(), "" );
        return serializer._jsonWriter.write( static_cast< uint64_t >( val ) );
    }

//    template< typename WriteObjectFields >
//    void serializeObject( WriteObjectFields&& writeObjectFields )
//    {
//        auto& objWriter = _jsonWriter.beginObject();
//        std::forward< WriteObjectFields >( writeObjectFields )( objWriter );
//        objWriter.end();
//    }
//
//    template< typename WriteArrayElements >
//    void serializeArray( WriteArrayElements&& writeArrayElements )
//    {
//        auto& arrWriter = _jsonWriter.beginArray();
//        std::forward< WriteArrayElements >( writeArrayElements )( arrWriter );
//        arrWriter.end();
//    }

private:

    static constexpr std::size_t _maxKeywordStringLength()
    {
        return 1024;
    }

private:

    const std::size_t _maxNonKeywordStringLength = 40 * 1024;
    IJsonWriter& _jsonWriter;
};

} } } } // namespace Elastic::Apm::Impl::ServerComm

#define ELASTIC_APM_SERIALIZE_JSON_OBJECT_FIELDS_FOR_EACH_CALLBACK( reservedByBoostPp, objWriter, unused_fieldIndex, field ) \
    { \
        Serializer fieldValueSerializer{ objWriter.add( BOOST_PP_STRINGIZE( field ) ) }; \
        (field) >> fieldValueSerializer; \
    } \
/**/

#define ELASTIC_APM_SERIALIZE_JSON_OBJECT_FIELDS( serializer, field1, /* field2, ... */ ... ) \
    do { \
        auto& objWriter = (serializer).jsonWriter().beginObject(); \
        \
        BOOST_PP_SEQ_FOR_EACH_I( \
            ELASTIC_APM_SERIALIZE_JSON_OBJECT_FIELDS_FOR_EACH_CALLBACK \
            , objWriter \
            , BOOST_PP_VARIADIC_TO_SEQ( field1 /* field2, ... */ , ##__VA_ARGS__ ) ) \
        \
    } while( 0 ) \
    /**/