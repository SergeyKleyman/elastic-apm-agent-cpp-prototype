#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/type_traits.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/sstream.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/container/pmr/monotonic_buffer_resource.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Util/PmrString.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

using namespace Elastic::Apm::Util;

template< std::size_t onStackBufferSize = 100 >
class PmrOutputStringStream
{
private:

    using MonotonicBufferResource = boost::container::pmr::monotonic_buffer_resource;

public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( PmrOutputStringStream );

    explicit PmrOutputStringStream( const PmrByteAllocator& allocator )
            : _monotonicBufferResource{ &( _onStackBuffer[ 0 ] ), onStackBufferSize, allocator.resource() }
            , _oStringStream{ PmrString{ PmrByteAllocator{ &_monotonicBufferResource } } }
    {
        _oStringStream.imbue( std::locale::classic() );
    }

    using WrappedType = std::basic_ostringstream< char, std::char_traits< char >, PmrAllocator< char > >;

    WrappedType& get()
    {
        return _oStringStream;
    }

private:

    Byte _onStackBuffer[onStackBufferSize];
    MonotonicBufferResource _monotonicBufferResource;
    WrappedType _oStringStream;
};

} } } } } // namespace Elastic::Apm::Impl::Log::Backend
