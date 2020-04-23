#pragma once

/**
 * Examples:
 *
 *      String:
 *              `abc'
 *              `a\tbc\n\r'
 *
 *      List:
 *              list [size: 3]
 *                  `a'
 *                  `b'
 *                  `c'
 *
 *      Map:
 *              map [size: 2]
 *                  a: list [size: 3]
 *                      - 1
 *                      - 2
 *                      - 3
 *                  b: list [size: 2]
 *                      - [TransactionId] `0123456789ABCDEF'
 *                      - [TransactionId] `ABCDEF0123456789'
 */

#include "Elastic/Apm/Impl/Log/Backend/visualFormatContextValue.hxx"
#include "Elastic/Apm/Impl/Log/Backend/VisualStreamToString.hxx"
#include "Elastic/Apm/Impl/Log/Backend/StreamToVisualAdaptor.hxx"
#include "Elastic/Apm/Impl/Util/basic_macros.hxx" // ELASTIC_APM_UNUSED_VAR
//#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/range/adaptor/transformed.hxx"
//#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
//#include "Elastic/Apm/Impl/Log/BareTypeToLog.hxx"
//#include "Elastic/Apm/Impl/Util/OnScopeExit.hxx"
//#include "Elastic/Apm/Impl/Util/repeat_n_times.hxx"
//#include "Elastic/Apm/Impl/Util/text_util.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

// TODO: Sergey Kleyman: Uncomment

//namespace Internals
//{
//
//class VisualFormatter
//        : public boost::static_visitor< /* visit methods return value: */ void >
//{
//private:
//
//    using Value = v1_RecordContextValue;
//    using MapContent = Value::MapContent;
//    using ListContent = Value::ListContent;
//
//public:
//
//    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( VisualFormatter );
//
//    explicit VisualFormatter( VisualStreamToString& txtOutStream, StringView linePrefix )
//            : _txtOutStream{ txtOutStream }
//              , _linePrefix{ linePrefix }
//    {
//    }
//
//    void format( const v1_RecordContext& recCtx )
//    {
//        _findBestFitAndFormatValueContent( recCtx.elements );
//    }
//
//    void format( const v1_RecordContextValue& val )
//    {
//        _formatValue( val );
//    }
//
//private:
//
//    class OneLevelContentFormatter
//    {
//    public:
//
//        ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( OneLevelContentFormatter );
//
//        OneLevelContentFormatter( VisualFormatter& formatter, bool isHorizontalFormat )
//                : _formatter{ formatter }
//                  , _txtOutStream{ formatter._txtOutStream }
//                  , _linePrefix{ formatter._linePrefix }
//                  , _nestingDepth{ formatter._nestingDepth }
//                  , _isHorizontalFormat{ isHorizontalFormat }
//        {}
//
//        void format( boost::blank /* valContent */ ) const
//        {
//            _txtOutStream << VisualFormat::blank();
//        }
//
//        void format( std::nullptr_t /* valContent */ ) const
//        {
//            _txtOutStream << VisualFormat::null();
//        }
//
//        template< typename T >
//        boost::enable_if_t< std::is_arithmetic< BareTypeToLog < T > >::value, void >
//        format( T val )
//        {
//            _txtOutStream << val;
//        }
//
//        void format( const String& val ) const
//        {
//            _txtOutStream << '`' << val.view() << '\'';
//        }
//
//        void format( const ListContent& valContent ) const
//        {
//            if ( valContent.empty() )
//            {
//                _txtOutStream << VisualFormat::emptyList();
//                return;
//            }
//
//            _formatCollection(
//                    valContent
//                    , [ & ]( const v1_RecordContextValue& listElementVal )
//                    {
//                        _formatter._formatChildValue( listElementVal );
//                    }
//                    , /* collectionBeginDelimiter */ '['
//                    , /* collectionEndDelimiter */ ']' );
//        }
//
//        void format( const MapContent& valContent ) const
//        {
//            if ( valContent.empty() )
//            {
//                _txtOutStream << VisualFormat::emptyMap();
//                return;
//            }
//
//            _formatCollection(
//                    valContent
//                    , [ & ]( const MapContent::value_type& mapElementKeyValue )
//                    {
//                        _txtOutStream << mapElementKeyValue.first.view() << literalToView( ": " );
//                        _formatter._formatChildValue( mapElementKeyValue.second );
//                    }
//                    , /* collectionBeginDelimiter */ '{'
//                    , /* collectionEndDelimiter */ '}' );
//        }
//
//    private:
//
//        template< class Collection, typename FormatElement >
//        void _formatCollection( const Collection& collection
//                                , FormatElement&& formatElement
//                                , char collectionBeginDelimiter
//                                , char collectionEndDelimiter
//        ) const
//        {
//            _beginCollection( collection.size(), collectionBeginDelimiter );
//
//            bool isFirst = true;
//            for ( const auto& collectionElement : collection )
//            {
//                if ( isFirst )
//                {
//                    isFirst = false;
//                }
//                else
//                {
//                    _insertCollectionElementsSeparator();
//                }
//
//                std::forward< FormatElement >( formatElement )( collectionElement );
//            }
//
//            _endCollection( collectionEndDelimiter );
//        }
//
//        void _beginCollection( std::size_t collectionSize, char collectionBeginDelimiter ) const
//        {
//            _txtOutStream << literalToView( "<size: " ) << collectionSize << literalToView( ">" );
//
//            if ( _isHorizontalFormat )
//            {
//                _txtOutStream << collectionBeginDelimiter << ' ';
//            }
//            else
//            {
//                _startNewLine( _nestingDepth + 1 );
//            }
//        }
//
//        void _insertCollectionElementsSeparator() const
//        {
//            if ( _isHorizontalFormat )
//            {
//                _txtOutStream << literalToView( ", " );
//            }
//            else
//            {
//                _startNewLine( _nestingDepth + 1 );
//            }
//        }
//
//        void _endCollection( char collectionEndDelimiter ) const
//        {
//            if ( _isHorizontalFormat )
//            {
//                _txtOutStream << ' ' << collectionEndDelimiter;
//            }
//        }
//
//        void _startNewLine( unsigned int nestingDepth ) const
//        {
//            _txtOutStream << '\n' << _linePrefix;
//            ELASTIC_APM_REPEAT_N_TIMES( nestingDepth ) _txtOutStream << VisualFormat::indent();
//        }
//
//    private:
//
//        VisualFormatter& _formatter;
//        VisualStreamToString& _txtOutStream;
//        StringView _linePrefix;
//        const unsigned int _nestingDepth;
//        const bool _isHorizontalFormat;
//    };
//
//    enum class BestFitCandidate
//    {
//        horizontalOnly,
//        verticalOnly,
//        shouldTryHorizontal
//    };
//
//    class FindBestFitCandidateVisitor
//            : public boost::static_visitor< BestFitCandidate >
//    {
//    public:
//
//        ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( FindBestFitCandidateVisitor );
//
//        explicit FindBestFitCandidateVisitor( unsigned int nestingDepth = 0 )
//                : _nestingDepth{ nestingDepth }
//        {}
//
//        BestFitCandidate operator ()( boost::blank /* valContent */ ) const
//        {
//            return BestFitCandidate::horizontalOnly;
//        }
//
//        BestFitCandidate operator ()( std::nullptr_t /* valContent */ ) const
//        {
//            return BestFitCandidate::horizontalOnly;
//        }
//
//        template< typename T >
//        boost::enable_if_t< std::is_arithmetic< BareTypeToLog < T > >::value, BestFitCandidate >
//
//        operator ()( T /* val */ ) const
//        {
//            return BestFitCandidate::horizontalOnly;
//        }
//
//        BestFitCandidate operator ()( const String& valContent ) const
//        {
//            return containsNewLine( valContent )
//                   ? BestFitCandidate::verticalOnly
//                   : BestFitCandidate::horizontalOnly;
//        }
//
//        BestFitCandidate operator ()( const ListContent& valContent ) const
//        {
//            return _visitCollection( valContent );
//        }
//
//        BestFitCandidate operator ()( const MapContent& valContent ) const
//        {
//            return _visitCollection( valContent | boost::adaptors::transformed(
//                    []( const MapContent::value_type& keyVal ) -> const v1_RecordContextValue&
//                    {
//                        return keyVal.second;
//                    } ) );
//        }
//
//    private:
//
//        BestFitCandidate _visitChildValue( const v1_RecordContextValue& val ) const
//        {
//            return boost::apply_visitor( FindBestFitCandidateVisitor{ _nestingDepth + 1 }, val.content );
//        }
//
//        template< class ValueRange >
//        BestFitCandidate _visitCollection( const ValueRange& valRange ) const
//        {
//            if ( _nestingDepth > 0 ) return BestFitCandidate::verticalOnly;
//
//            for ( const auto& childVal: valRange )
//            {
//                if ( _visitChildValue( childVal ) == BestFitCandidate::verticalOnly )
//                {
//                    return BestFitCandidate::verticalOnly;
//                }
//            }
//
//            return BestFitCandidate::shouldTryHorizontal;
//        }
//
//    private:
//
//        const unsigned int _nestingDepth;
//    };
//
//    template< typename ValueContent >
//    void _formatValueContent( const ValueContent& valContent, bool isHorizontalFormat )
//    {
//        OneLevelContentFormatter{ *this, isHorizontalFormat }.format( valContent );
//    }
//
//    template< typename ValueContent >
//    bool _tryToFormatHorizontally( const ValueContent& valContent )
//    {
//        auto posBefore = _txtOutStream.currentPosition();
//        _formatValueContent( valContent, /* isHorizontalFormat: */ true );
//        if ( ( _txtOutStream.currentPosition() - posBefore ) > VisualFormat::maxHorizontalFormatLength() )
//        {
//            _txtOutStream.rewind( posBefore );
//            return false;
//        }
//        return true;
//    }
//
//    template< typename ValueContent >
//    void _findBestFitAndFormatValueContent( const ValueContent& valContent )
//    {
//        auto bestFitCandidate = FindBestFitCandidateVisitor{}( valContent );
//        if ( bestFitCandidate != BestFitCandidate::shouldTryHorizontal )
//        {
//            _formatValueContent( valContent
//                                 , /* isHorizontalFormat: */ bestFitCandidate == BestFitCandidate::horizontalOnly );
//            return;
//        }
//
//        if ( _tryToFormatHorizontally( valContent ) ) return;
//
//        _formatValueContent( valContent, /* isHorizontalFormat: */ false );
//    }
//
//    class Call_findBestFitAndFormatValueContent_Visitor
//            : public boost::static_visitor< void >
//    {
//    public:
//
//        ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( Call_findBestFitAndFormatValueContent_Visitor );
//
//        explicit Call_findBestFitAndFormatValueContent_Visitor( VisualFormatter& formatter )
//                : _formatter{ formatter }
//        {
//        }
//
//        template< typename T >
//        void operator ()( const T& valContent ) const
//        {
//            _formatter._findBestFitAndFormatValueContent( valContent );
//        }
//
//    private:
//
//        VisualFormatter& _formatter;
//    };
//
//    void _formatChildValue( const v1_RecordContextValue& val )
//    {
//        ++_nestingDepth;
//        format( val );
//        --_nestingDepth;
//    }
//
//    void _formatValue( const v1_RecordContextValue& val )
//    {
//        if ( val.type && !val.type->name.view().empty() ) _txtOutStream << '<' << val.type->name.view() << literalToView( "> " );
//
//        if ( val.type && val.type->visualFormat )
//        {
//            val.type->visualFormat(
//                    val
//                    , _txtOutStream
//                    , []( const v1_RecordContextValue& childVal, VisualStreamToString& /* txtOutStream */, void* childFormatCtx )
//                    {
//                        reinterpret_cast< VisualFormatter* >( childFormatCtx )->_formatChildValue( childVal );
//                    }
//                    , /* childFormatCtx: */ reinterpret_cast< void* >( this ) );
//        }
//        else
//        {
//            boost::apply_visitor( Call_findBestFitAndFormatValueContent_Visitor{ *this }, val.content );
//        }
//    }
//
//private:
//
//    VisualStreamToString& _txtOutStream;
//    StringView _linePrefix;
//    unsigned int _nestingDepth = 0;
//};
//
//} // namespace Internals

ELASTIC_APM_INLINE_FOR_IMPL
PmrString visualFormatContextValue( const IStreamable& val, const PmrByteAllocator& allocator, StringView /* linePrefix */ )
{
    // TODO: Sergey Kleyman: Implement: Smarter format choosing between horizontal and vertical
    auto visualLogStream = VisualStreamToString::forHorizontalFormat( allocator );
    StreamToVisualAdaptor< VisualStreamToString > logStream{ visualLogStream };

    auto streamToLogRetVal = val.streamToLogImpl( logStream );
    ELASTIC_APM_UNUSED_VAR( streamToLogRetVal );

    return visualLogStream.release();
}

} } } } } // namespace Elastic::Apm::Impl::Log::Backend
