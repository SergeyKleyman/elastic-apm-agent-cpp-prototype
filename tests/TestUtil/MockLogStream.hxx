#pragma once

#include "Elastic/Apm/Log/IStream.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Impl/Util/TypeTraits.hxx"
#include "Elastic/Apm/Util/PmrUniquePtr.hxx"
#include "TestUtil/MockLogRecord.hxx"

namespace ElasticApmTests { namespace TestUtil
{

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class MockLogStream
        : public Elastic::Apm::Log::IStream
{
private:

    using Value = MockLogRecord::ContextValue;
    using MapContent = Value::MapContent;
    using ListContent = Value::ListContent;

public:

    ELASTIC_APM_MOVE_CONSTRUCTIBLE_BUT_NOT_MOVE_ASSIGNABLE( MockLogStream );

    explicit MockLogStream( const PmrByteAllocator& allocator, Value& value )
            : _allocator{ allocator }
              , _value{ value }
    {}

    IVisualStream* asVisual() override
    {
        return nullptr;
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueType( StringView type ) override;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( std::nullptr_t /* val */ ) override;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( bool val ) override;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( uintmax_t val ) override;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( intmax_t val ) override;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( double val ) override;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool writeCurrentValueContent( StringView val ) override;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    IStream::IMapBuilder* beginMap() override;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    IStream::IListBuilder* beginList() override;

private:

//    class ListBuilder
//        Stream add()
//        {
//            return Stream{ _allocator, _listContent.emplace_back() };
//        }
//
//    ListBuilder writeList()
//    {
//        _value.content = ListContent{ MapContent::allocator_type{ _allocator } };
//        return ListBuilder{ _allocator, boost::get< ListContent >( _value.content ) };
//    }

    class MapBuilder;
    class ListBuilder;

    using CompositeBuildersVariant = boost::variant< boost::blank, MapBuilder, ListBuilder >;

    class MapBuilder
            : public IStream::IMapBuilder
    {
    public:

        MapBuilder( const PmrByteAllocator& allocator, MapContent& mapContent )
                : _allocator{ allocator }
                  , _mapContent{ &mapContent }
        {}

        ELASTIC_APM_COPY_CTOR_DELETE( MapBuilder );
        ELASTIC_APM_COPY_ASSIGN_DELETE( MapBuilder );

        // TODO: Sergey Kleyman: Investigate why ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( MapBuilder, noexcept ) doesn't compile
        MapBuilder( MapBuilder&& rhs ) noexcept
            : _allocator{ rhs._allocator }
            , _mapContent{ rhs._mapContent }
            , _currentValueStream{ std::move( rhs._currentValueStream ) }
        {}

        MapBuilder& operator =( MapBuilder&& rhs ) noexcept
        {
            _allocator = rhs._allocator;
            _mapContent = rhs._mapContent;
            _currentValueStream = std::move( rhs._currentValueStream );
            return *this;
        }

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        IStream* add( StringView key ) override;

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        bool end() override;

    private:

        PmrByteAllocator _allocator;
        MapContent* _mapContent;
        PmrUniquePtr< MockLogStream > _currentValueStream;
    };

    class ListBuilder
            : public IStream::IListBuilder
    {
    public:

        ListBuilder( const PmrByteAllocator& allocator, ListContent& listContent )
                : _allocator{ allocator }
                  , _listContent{ &listContent }
        {}

        ELASTIC_APM_COPY_CTOR_DELETE( ListBuilder );
        ELASTIC_APM_COPY_ASSIGN_DELETE( ListBuilder );

        // TODO: Sergey Kleyman: Investigate why ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( ListBuilder, noexcept ) doesn't compile
        ListBuilder( ListBuilder&& rhs ) noexcept
                : _allocator{ rhs._allocator }
                  , _listContent{ rhs._listContent }
                  , _currentValueStream{ std::move( rhs._currentValueStream ) }
        {}

        ListBuilder& operator =( ListBuilder&& rhs ) noexcept
        {
            _allocator = rhs._allocator;
            _listContent = rhs._listContent;
            _currentValueStream = std::move( rhs._currentValueStream );
            return *this;
        }

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        IStream* add() override;

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        bool end() override;

    private:

        PmrByteAllocator _allocator;
        ListContent* _listContent;
        PmrUniquePtr< MockLogStream > _currentValueStream;
    };

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _hasCompositeBuilder() const
    {
        return _compositeBuilder.which() != 0;
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _hasValueWritten() const
    {
        return _value.content.which() != 0;
    }

private:

    PmrByteAllocator _allocator;
    Value& _value;
    CompositeBuildersVariant _compositeBuilder;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } // namespace ElasticApmTests::TestUtil
