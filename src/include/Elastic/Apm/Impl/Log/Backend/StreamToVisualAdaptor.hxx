#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/variant.hxx"
#include "Elastic/Apm/Log/IVisualStream.hxx"
#include "Elastic/Apm/Log/IStream.hxx"
#include "Elastic/Apm/Impl/Util/assert.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

using namespace Elastic::Apm::Log;

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

template< typename T >
class StreamToVisualAdaptor
        : public IStream
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( StreamToVisualAdaptor );

    explicit StreamToVisualAdaptor( IVisualStream& wrappedVisualStream )
            : _wrappedVisualStream{ wrappedVisualStream }
    {}

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    IVisualStream* asVisual() override
    {
        return &_wrappedVisualStream;
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueType( StringView type ) override
    {
        if ( ! _wrappedVisualStream.write( '<' ) ) return false;
        if ( ! _wrappedVisualStream.write( type ) ) return false;
        return _wrappedVisualStream.write( literalToView( "> " ) );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( std::nullptr_t /* val */ ) override
    {
        return _wrappedVisualStream.write( nullptr );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( bool val ) override
    {
        return _wrappedVisualStream.write( val );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( uintmax_t val ) override
    {
        return _wrappedVisualStream.write( val );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( intmax_t val ) override
    {
        return _wrappedVisualStream.write( val );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( double val ) override
    {
        return _wrappedVisualStream.write( val );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( StringView val ) override
    {
        if ( ! _wrappedVisualStream.write( '`' ) ) return false;
        if ( ! _wrappedVisualStream.write( val ) ) return false;
        return _wrappedVisualStream.write( '\'' );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    IStream::IMapBuilder* beginMap() override
    {
        ELASTIC_APM_RAW_ASSERT( ! _hasCompositeBuilder(), "This stream's root value already has composite builder" );

        if ( ! _wrappedVisualStream.write( '{' ) ) return nullptr;

        _compositeBuilder = MapBuilder{ *this };
        return &( boost::get< MapBuilder >( _compositeBuilder ) );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    IStream::IListBuilder* beginList() override
    {
        ELASTIC_APM_RAW_ASSERT( ! _hasCompositeBuilder(), "This stream's root value already has composite builder" );

        if ( ! _wrappedVisualStream.write( '[' ) ) return nullptr;

        _compositeBuilder = ListBuilder{ *this };
        return &( boost::get< ListBuilder >( _compositeBuilder ) );
    }

private:

    class MapBuilder;
    class ListBuilder;
    
    using CompositeBuildersVariant = boost::variant< boost::blank, MapBuilder, ListBuilder >;

    class MapBuilder
        : public IStream::IMapBuilder
    {
    public:

        ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( MapBuilder, noexcept );

        explicit MapBuilder( StreamToVisualAdaptor& parent )
                : _parent{ &parent }
        {}

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        IStream* add( StringView key ) override
        {
            if ( _isBeforeFirstElement )
            {
                if ( ! wrappedVisualStream().write( ' ' ) ) return nullptr;
            }
            else
            {
                if ( ! wrappedVisualStream().write( literalToView( ", " ) ) ) return nullptr;
            }
            _isBeforeFirstElement = false;

            if ( ! wrappedVisualStream().write( key ) ) return nullptr;
            if ( ! wrappedVisualStream().write( literalToView( ": " ) ) ) return nullptr;

            return _parent;
        }

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        bool end() override
        {
            if ( _isBeforeFirstElement )
            {
                _isBeforeFirstElement = false;
            }
            else
            {
                if ( ! wrappedVisualStream().write( ' ' ) ) return false;
            }
            return wrappedVisualStream().write( '}' );
        }

    private:

        IVisualStream& wrappedVisualStream()
        {
            return _parent->_wrappedVisualStream;
        }

    private:

        StreamToVisualAdaptor* _parent;
        bool _isBeforeFirstElement = true;
    };

    class ListBuilder
            : public IStream::IListBuilder
    {
    public:

        ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( ListBuilder, noexcept );

        explicit ListBuilder( StreamToVisualAdaptor& parent )
                : _parent{ &parent }
        {}

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        IStream* add() override
        {
            if ( _isBeforeFirstElement )
            {
                if ( ! wrappedVisualStream().write( ' ' ) ) return nullptr;
            }
            else
            {
                if ( ! wrappedVisualStream().write( literalToView( ", " ) ) ) return nullptr;
            }
            _isBeforeFirstElement = false;

            return _parent;
        }

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        bool end() override
        {
            if ( _isBeforeFirstElement )
            {
                _isBeforeFirstElement = false;
            }
            else
            {
                if ( ! wrappedVisualStream().write( ' ' ) ) return false;
            }
            return wrappedVisualStream().write( ']' );
        }

    private:

        IVisualStream& wrappedVisualStream()
        {
            return _parent->_wrappedVisualStream;
        }

    private:

        StreamToVisualAdaptor* _parent;
        bool _isBeforeFirstElement = true;
    };

    bool _hasCompositeBuilder() const
    {
        return _compositeBuilder.which() != 0;
    }

private:

    IVisualStream& _wrappedVisualStream;
    CompositeBuildersVariant _compositeBuilder;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } } } } // namespace Elastic::Apm::Impl::Log::Backend
