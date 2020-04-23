#pragma once

#include "Elastic/Apm/Impl/Util/platform_detection.hxx"

#if ELASTIC_APM_IS_OS_WINDOWS != 0

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/Windows/windows.hxx"
#include "Elastic/Apm/Impl/Log/Backend/TextSinkBase.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class WindowsOutputDebugStringSink
        : public TextSinkBase< WindowsOutputDebugStringSink >
{
public:

    explicit WindowsOutputDebugStringSink( const PmrByteAllocator& allocator, String linePrefix = linePrefix_default() )
            : Base{ allocator, std::move( linePrefix ) }
    {}

private:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( WindowsOutputDebugStringSink );

    using Base = TextSinkBase< WindowsOutputDebugStringSink >;
    friend Base;

    void consume( const RecordDataRefs& /* recDataRefs */, const char* formattedRecord )
    {
        OutputDebugStringA( formattedRecord );
    }

    static String linePrefix_default()
    {
        return String::fromLiteral( "Elastic APM C++ Agent | " );
    }
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } } } } // namespace Elastic::Apm::Impl::Log::Backend

#endif // #if ELASTIC_APM_IS_OS_WINDOWS != 0
