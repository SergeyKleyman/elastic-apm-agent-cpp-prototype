#pragma once

#include "Elastic/Apm/Log/ISink.hxx"
#include "Elastic/Apm/Impl/Log/Backend/RecordVisualFormatter.hxx"
#include "Elastic/Apm/Util/String.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

template< class Derived >
class TextSinkBase
        : public ISink
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( TextSinkBase );

    explicit TextSinkBase( const PmrByteAllocator& allocator, String linePrefix = String{} )
            : _formatter{ allocator, linePrefix }
    {}

    void consume( const RecordDataRefs& recDataRefs ) override
    {
        auto formattedRecord = _formatter.format( recDataRefs );
        static_cast< Derived* >( this )->consume( recDataRefs, formattedRecord.c_str() );
    }

    static constexpr StringView sharedSinkPrefix()
    {
        return literalToView( "Elastic APM C++ Agent | " );
    }

private:

    RecordVisualFormatter _formatter;
};

} } } } } // namespace Elastic::Apm::Impl::Log::Backend
