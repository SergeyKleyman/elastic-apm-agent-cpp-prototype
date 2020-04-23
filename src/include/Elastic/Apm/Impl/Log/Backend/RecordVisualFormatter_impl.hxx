#pragma once

#include "Elastic/Apm/Impl/Log/Backend/RecordVisualFormatter.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
#include "Elastic/Apm/Impl/Log/Backend/StreamToVisualAdaptor.hxx"
#include "Elastic/Apm/Impl/Log/Backend/VisualStreamToString.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_Level.hxx"
#include "Elastic/Apm/Impl/Util/SystemClockTimePoint_toLog.hxx"
#include "Elastic/Apm/Impl/Util/assert.hxx"
#include "Elastic/Apm/Impl/Util/basic_macros.hxx" // ELASTIC_APM_UNUSED_VAR
#include "Elastic/Apm/Impl/Util/basic_util.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Util/repeat_n_times.hxx"
#include "Elastic/Apm/Impl/Util/text_util.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

namespace Internals
{

using namespace Elastic::Apm::Impl::Util;
using namespace Elastic::Apm::Impl::Log;

class OneRecordFormatter
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( OneRecordFormatter );

    OneRecordFormatter( const RecordVisualFormatter::CachedSrcFilePathPrefixesToCut& cachedSrcFilePathPrefixesToCut
                        , const RecordDataRefs& recDataRefs
                        , StringView linePrefix
                        , const PmrByteAllocator& allocator
    )
            : _cachedSrcFilePathPrefixesToCut{ cachedSrcFilePathPrefixesToCut }
              , _recDataRefs{ recDataRefs }
              , _linePrefix{ linePrefix }
              , _allocator{ allocator }
              , _outStream{ VisualStreamToString::forHorizontalFormat( allocator ) }
    {}

    PmrString format()
    {
        auto writeRetVal = _writeLogRecordParts();
        ELASTIC_APM_UNUSED_VAR( writeRetVal );

        return _outStream.release();
    }

private:

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _writePartsSeparator()
    {
        return _outStream.write( literalToView( " | " ) );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _writeTimestamp()
    {
        return Impl::Util::streamToVisualLogImpl( _recDataRefs.timestamp, _outStream );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _writeLevel()
    {
        constexpr uint8_t padTo = 8; // level (padded with spaces on the right to 8 chars)
        auto posBeforeWrite = _outStream.currentPosition();
        if ( ! streamToVisualLogImpl( _recDataRefs.level, _outStream ) ) return false;
        auto posAfterWrite = _outStream.currentPosition();
        return _writePadding( posBeforeWrite, posAfterWrite, padTo );
    }

    StringView _findFilePathInterestingPart( StringView filePath )
    {
        for ( const auto& filePathPrefixToCut : _cachedSrcFilePathPrefixesToCut )
        {
            if ( filePath.starts_with( filePathPrefixToCut ) )
            {
                return filePath.substr( filePathPrefixToCut.length() );
            }
        }

        return filePath;
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _writeFileLine()
    {
        constexpr uint8_t padTo = 40; // file name:line number (padded with spaces on the right to 20 chars)
        auto posBeforeWrite = _outStream.currentPosition();

        if ( ! _outStream.write( _findFilePathInterestingPart( _recDataRefs.sourceCodeLocation.filePath ) ) ) return false;
        if ( ! _outStream.write( ':' ) ) return false;
        if ( ! _outStream.write( _recDataRefs.sourceCodeLocation.lineNumber ) ) return false;

        auto posAfterWrite = _outStream.currentPosition();
        return _writePadding( posBeforeWrite, posAfterWrite, padTo );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _writeFunction()
    {
        constexpr uint8_t padTo = 40; // function name (padded with spaces on the right to 30 chars)
        auto posBeforeWrite = _outStream.currentPosition();

        if ( ! _outStream.write( _recDataRefs.sourceCodeLocation.cppFunc ) ) return false;
        if ( ! _outStream.write( literalToView( "()" ) ) ) return false;

        auto posAfterWrite = _outStream.currentPosition();
        return _writePadding( posBeforeWrite, posAfterWrite, padTo );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _writeMessage()
    {
        return _outStream.write( StringView{ _recDataRefs.message } );
    }

    bool hasContext() const
    {
        return _recDataRefs.contextExprs.size() > 0;
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _writeContext()
    {
        bool isFirst = true;
        for ( const auto& ctxExpr : _recDataRefs.contextExprs )
        {
            if ( isFirst )
            {
                isFirst = false;
            }
            else
            {
                if ( ! _outStream.write( literalToView( "; " ) ) ) return false;
            }

            if ( ! _outStream.write( ctxExpr.exprValue->preprocessExprToLogNameImpl( ctxExpr.stringizedExpr ) ) ) return false;
            if ( ! _outStream.write( literalToView( ": " ) ) ) return false;
            StreamToVisualAdaptor< VisualStreamToString > logStream{ _outStream };
            if ( ! ctxExpr.exprValue->streamToLogImpl( logStream ) ) return false;
        }

        return true;
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _writePadding( std::size_t posBeforeWrite, std::size_t posAfterWrite, std::size_t padTo )
    {
        ELASTIC_APM_RAW_ASSERT( posBeforeWrite <= posAfterWrite );

        if ( padTo < static_cast< std::size_t >( posAfterWrite - posBeforeWrite ) ) return true;

        ELASTIC_APM_REPEAT_N_TIMES( static_cast< std::size_t >( padTo - ( posAfterWrite - posBeforeWrite ) ) )
        {
            if ( ! _outStream.write( ' ' ) ) return false;
        }

        return true;
    }

    ELASTIC_APM_INLINE_FOR_IMPL
    bool _writeLogRecordParts()
    {
        if ( ! _outStream.write( _linePrefix ) ) return false;

        if ( ! _writeTimestamp() ) return false;

        if ( ! _writePartsSeparator() ) return false;
        if ( ! _writeLevel() ) return false;

        if ( ! _writePartsSeparator() ) return false;
        if ( ! _writeFileLine() ) return false;

        if ( ! _writePartsSeparator() ) return false;
        if ( ! _writeFunction() ) return false;

        if ( ! _writePartsSeparator() ) return false;
        if ( ! _writeMessage() ) return false;

        if ( hasContext() )
        {
            if ( ! _writePartsSeparator() ) return false;
            if ( ! _writeContext() ) return false;
        }

        return _outStream.write( '\n' );
    }

private:

    const RecordVisualFormatter::CachedSrcFilePathPrefixesToCut& _cachedSrcFilePathPrefixesToCut;
    const RecordDataRefs& _recDataRefs;
    const StringView _linePrefix;
    const PmrByteAllocator _allocator;
    VisualStreamToString _outStream;
};

template< typename PathSegmentConsumer >
void reverseIterateOverPathSegments( StringView filePath, PathSegmentConsumer&& pathSegmentConsumer )
{
    const char* const pathSeparators = "/\\";
    auto filePathRemainder = filePath;
    for ( ;; )
    {
        auto pathSeparator = filePathRemainder.find_last_of( pathSeparators );
        auto currentSegmentBegin = ( pathSeparator == filePathRemainder.npos ) ? 0 : pathSeparator + 1;
        auto currentSegment = filePathRemainder.substr( currentSegmentBegin );

        if ( ! std::forward< PathSegmentConsumer >( pathSegmentConsumer )( currentSegment ) ) return;

        if ( pathSeparator == filePathRemainder.npos || pathSeparator == 0 ) return;

        filePathRemainder = filePathRemainder.substr( 0, pathSeparator );
    }
}

inline
bool isFilePathSeparator( char c )
{
    return c == '/' || c == '\\';
}

inline
RecordVisualFormatter::CachedSrcFilePathPrefixesToCut buildCachedSrcFilePathPrefixesToCut()
{
    auto thisSrcFilePath = literalToView( __FILE__ );
    StringView rootSegments[] = { literalToView( "Elastic" ), literalToView( "Apm" ), literalToView( "Impl" ) };
    std::size_t foundRootSegmentEndPositions[ arraySize( rootSegments ) ];
    std::size_t currentRootSegmentIndex = arraySize( rootSegments ) - 1;
    RecordVisualFormatter::CachedSrcFilePathPrefixesToCut filePathPrefixesToCut;
    bool didFindRootSegmentsSeq = false;

    reverseIterateOverPathSegments( thisSrcFilePath, [ & ]( StringView pathSegment ) -> bool
    {
        if ( areEqualIgnoringCase( pathSegment, rootSegments[ currentRootSegmentIndex ] ) )
        {
            foundRootSegmentEndPositions[ currentRootSegmentIndex ] =
                    ( pathSegment.begin() - thisSrcFilePath.begin() ) + pathSegment.length();
            if ( currentRootSegmentIndex == 0 )
            {
                didFindRootSegmentsSeq = true;
                return false;
            }
            --currentRootSegmentIndex;
        }
        else
        {
            // We need to root segments to appear one after another
            // so we reset the index if we encounter a segment in the middle that doesn't match
            currentRootSegmentIndex = arraySize( rootSegments ) - 1;
        }
        return true;
    } );

    if ( ! didFindRootSegmentsSeq ) return filePathPrefixesToCut;

    filePathPrefixesToCut.reserve( arraySize( rootSegments ) );

    // Start with the longest prefix
    currentRootSegmentIndex = arraySize( rootSegments ) - 1;
    for ( ;; )
    {
        auto segEndPos = foundRootSegmentEndPositions[ currentRootSegmentIndex ];
        ELASTIC_APM_RAW_ASSERT( thisSrcFilePath.length() > segEndPos
                , "End of path segment should be followed by path separator so it should not be the last position" );
        ELASTIC_APM_RAW_ASSERT( isFilePathSeparator( thisSrcFilePath[ segEndPos ] )
                , "End of path segment should be followed by path separator" );

        // +1 because prefix to cut off should include path separator
        filePathPrefixesToCut.push_back( thisSrcFilePath.substr( 0, segEndPos + 1 ) );

        if ( currentRootSegmentIndex == 0 ) break;
        --currentRootSegmentIndex;
    }

    return filePathPrefixesToCut;
}

} // namespace Internals

ELASTIC_APM_INLINE_FOR_IMPL

RecordVisualFormatter::RecordVisualFormatter( const PmrByteAllocator& allocator, String linePrefix )
        : _allocator{ allocator }
          , _linePrefix{ linePrefix }
          , _cachedSrcFilePathPrefixesToCut{ Internals::buildCachedSrcFilePathPrefixesToCut() }
{}

ELASTIC_APM_INLINE_FOR_IMPL
PmrString RecordVisualFormatter::format( const RecordDataRefs& recDataRefs ) const
{
    return Internals::OneRecordFormatter{ _cachedSrcFilePathPrefixesToCut
                                          , recDataRefs
                                          , _linePrefix
                                          , _allocator }.format();
}

} } } } } // namespace Elastic::Apm::Impl::Log::Backend
