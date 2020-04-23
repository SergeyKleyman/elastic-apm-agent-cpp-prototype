#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/algorithm.hxx" // std::min()
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/rapidjson/writer.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/rapidjson/stringbuffer.hxx"
#include "Elastic/Apm/Impl/Util/IJsonWriter.hxx"
#include "Elastic/Apm/Impl/Util/assert.hxx"
#include "Elastic/Apm/Impl/AmbientContext.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

using namespace Elastic::Apm::Util;

class JsonWriter
        : public IJsonWriter
{
public:

    explicit JsonWriter( const AmbientContext& ambientContext )
            : _ambientContext{ ambientContext, ELASTIC_APM_CLASS_NAME_FROM_MEMBER_FUNCTION }
              , _rapidjsonWriter{ _rapidjsonStringBuffer }
    {}

    IObjectWriter& beginObject() override
    {
        ELASTIC_APM_ASSERT( ! _hasValueWritten(), "Root value already has been written" );
        _writerVariant = ObjectWriter{ *this };
        return boost::get< ObjectWriter >( _writerVariant );
    }

    IArrayWriter& beginArray() override
    {
        ELASTIC_APM_ASSERT( ! _hasValueWritten(), "Root value already has been written" );
        _writerVariant = ArrayWriter{ *this };
        return boost::get< ArrayWriter >( _writerVariant );
    }

    void write( std::nullptr_t /* val */ ) override
    {
        ELASTIC_APM_ASSERT( ! _hasValueWritten(), "Root value already has been written" );
        _writerVariant = ScalarWriter{};
        _rapidjsonWriter.Null();
    }

    void write( bool val ) override
    {
        ELASTIC_APM_ASSERT( ! _hasValueWritten(), "Root value already has been written" );
        _writerVariant = ScalarWriter{};
        _rapidjsonWriter.Bool( val );
    }

    void write( int64_t val ) override
    {
        ELASTIC_APM_ASSERT( ! _hasValueWritten(), "Root value already has been written" );
        _writerVariant = ScalarWriter{};
        _rapidjsonWriter.Int64( val );
    }

    void write( uint64_t val ) override
    {
        ELASTIC_APM_ASSERT( ! _hasValueWritten(), "Root value already has been written" );
        _writerVariant = ScalarWriter{};
        _rapidjsonWriter.Uint64( val );
    }

    void write( double val ) override
    {
        ELASTIC_APM_ASSERT( ! _hasValueWritten(), "Root value already has been written" );
        _writerVariant = ScalarWriter{};
        _rapidjsonWriter.Double( val );
    }

    void write( StringView val, std::size_t maxLength ) override
    {
        ELASTIC_APM_ASSERT( ! _hasValueWritten(), "Root value already has been written" );
        _writerVariant = ScalarWriter{};
        _rapidjsonWriter.String( val.begin(), std::min( val.length(), maxLength ) );
    }

private:

    bool _hasValueWritten() const
    {
        return _writerVariant.which() != 0;
    }

    class ObjectWriter
            : public IObjectWriter
    {
    public:

        explicit ObjectWriter( JsonWriter& jsonWriter )
                : _jsonWriter{ jsonWriter }
        {
            _jsonWriter._rapidjsonWriter.StartObject();
        }

        IJsonWriter& add( StringView key ) override
        {
            return _jsonWriter;
        }

        void end() override
        {
            _jsonWriter._rapidjsonWriter.EndObject();
        }

    private:

        JsonWriter& _jsonWriter;
    };

    class ArrayWriter
            : public IArrayWriter
    {
    public:

        explicit ArrayWriter( JsonWriter& jsonWriter )
                : _jsonWriter{ jsonWriter }
        {
            _jsonWriter._rapidjsonWriter.StartObject();
        }

        IJsonWriter& add() override
        {
            return _jsonWriter;
        }

        void end() override
        {
            _jsonWriter._rapidjsonWriter.EndArray();
        }

    private:

        JsonWriter& _jsonWriter;
    };

    struct ScalarWriter
    {
    };

    using WritersVariant = boost::variant< boost::blank, ScalarWriter, ObjectWriter, ArrayWriter >;

private:

    AmbientContext _ambientContext;
    rapidjson::StringBuffer _rapidjsonStringBuffer;
    rapidjson::Writer< rapidjson::StringBuffer > _rapidjsonWriter;
    WritersVariant _writerVariant;
};

} } } } // namespace Elastic::Apm::Impl::Util
