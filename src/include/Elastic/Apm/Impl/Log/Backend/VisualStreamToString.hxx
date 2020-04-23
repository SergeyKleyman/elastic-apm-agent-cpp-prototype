#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstddef.hxx" // std::size_t
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/limits.hxx" // std::numeric_limits< T >::max()
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/algorithm.hxx" // std::min()
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/ios.hxx" // std::hex, std::uppercase, std::showbase
#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Log/IVisualStream.hxx"
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Util/String.hxx"
#include "Elastic/Apm/Impl/Util/TypeTraits.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Log/Backend/PmrOutputStringStream.hxx"
#include "Elastic/Apm/Impl/Util/assert.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class VisualStreamToString
        : public IVisualStream
{
public:

    ELASTIC_APM_MOVE_CONSTRUCTIBLE_BUT_NOT_MOVE_ASSIGNABLE( VisualStreamToString );

    static constexpr std::size_t maxNumberOfCharsToWrite_default()
    {
        return std::numeric_limits< std::size_t >::max();
    }

    static String linePrefix_default()
    {
        return String::fromLiteral( "" );
    }

    static VisualStreamToString forHorizontalFormat(
            const PmrByteAllocator& allocator
            , std::size_t maxNumberOfCharsToWrite = maxNumberOfCharsToWrite_default()
    )
    {
        return VisualStreamToString{ allocator
                                     , /* isHorizontalFormat: */ true
                                     , maxNumberOfCharsToWrite };
    }

    static VisualStreamToString forVerticalFormat(
            const PmrByteAllocator& allocator
            , std::size_t maxNumberOfCharsToWrite = maxNumberOfCharsToWrite_default()
            , String linePrefix = linePrefix_default()
    )
    {
        return VisualStreamToString{ allocator
                                     , /* isHorizontalFormat: */ false
                                     , maxNumberOfCharsToWrite
                                     , std::move( linePrefix ) };
    }

    using IVisualStream::write;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool write( StringView val ) override
    {
        return _appendToBuffer( val );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool write( double val ) override
    {
        PmrOutputStringStream<> auxOutStringStream( _buffer.get_allocator() );
        auxOutStringStream.get() << std::uppercase << val;
        return _appendToBuffer( auxOutStringStream.get().str() );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool write( intmax_t val ) override
    {
        PmrOutputStringStream<> auxOutStringStream( _buffer.get_allocator() );
        auxOutStringStream.get() << val;
        return _appendToBuffer( auxOutStringStream.get().str() );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool write( uintmax_t val, bool isHex, int padToLength, char paddingChar, bool showBase ) override
    {
        PmrOutputStringStream<> auxOutStringStream( _buffer.get_allocator() );
        if ( isHex )
        {
            // std::uppercase - Enables the use of uppercase characters
            // in floating-point and hexadecimal integer
            auxOutStringStream.get() << std::hex << std::uppercase;
            if ( showBase )
            {
                auxOutStringStream.get() << std::hex << std::showbase;
            }
        }

        /// padToLength == 0 - no padding
        /// padToLength > 0 - padding on the left:  |    123|
        /// padToLength < 0 - padding on the right  |123    |

        if ( padToLength != 0 )
        {
            if ( padToLength > 0 )
            {
                auxOutStringStream.get().width( padToLength );

                // std::ios::right - the output is padded to the field width
                // by inserting fill characters at the beginning
                //                              ^^^^^^^^^^^^^^^^ - |    123|
                auxOutStringStream.get().setf( std::ios::right );
            }
            else
            {
                auxOutStringStream.get().width( -padToLength );

                // std::ios::left - the output is padded to the field width
                // appending fill characters at the end
                //                           ^^^^^^^^^^ - |123    |
                auxOutStringStream.get().setf( std::ios::left );
            }

            auxOutStringStream.get().fill( paddingChar );
        }

        auxOutStringStream.get() << val;
        return _appendToBuffer( auxOutStringStream.get().str() );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool increaseNesting() override
    {
        ++_nesting;
        return true;
    }

    void decreaseNesting() override
    {
        ELASTIC_APM_RAW_ASSERT( _nesting > 0 );

        --_nesting;
    }

    PmrByteAllocator allocator() const override
    {
        return _buffer.get_allocator();
    }

    std::size_t currentPosition() const
    {
        return _buffer.size();
    }

    void rewind( std::size_t position )
    {
        ELASTIC_APM_RAW_ASSERT( _buffer.size() >= position );

        _buffer.resize( position );
    }

    StringView view() const
    {
        return StringView{ _buffer };
    }

    const char* c_str() const
    {
        return _buffer.c_str();
    }

    PmrString release()
    {
        PmrString retVal{ std::move( _buffer ) };
        _buffer.clear();
        return retVal;
    }

private:

    VisualStreamToString( const PmrByteAllocator& allocator
                          , bool isHorizontalFormat
                          , std::size_t maxNumberOfCharsToWrite = maxNumberOfCharsToWrite_default()
                          , String linePrefix = linePrefix_default()
    )
            : _buffer{ allocator }
              , _isHorizontalFormat{ isHorizontalFormat }
              , _maxNumberOfCharsToWrite{ maxNumberOfCharsToWrite }
              , _linePrefix{ std::move( linePrefix ) }
    {}

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool _appendToBuffer( StringView strView )
    {
        auto leftToMax = static_cast< std::size_t >( _maxNumberOfCharsToWrite - _buffer.size() );
        auto numberOfCharsToAppend = std::min( leftToMax, strView.length() );
        _buffer.append( strView.begin(), numberOfCharsToAppend );
        return numberOfCharsToAppend == strView.length();
    }

private:

    PmrString _buffer;
    const bool _isHorizontalFormat;
    const std::size_t _maxNumberOfCharsToWrite;
    const String _linePrefix;
    unsigned int _nesting = 0;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } } } } // namespace Elastic::Apm::Impl::Log::Backend
