#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx" // std::allocate_shared
#include "Elastic/Apm/Util/PmrUniquePtr.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

using namespace Elastic::Apm::Util;

template< class T, typename ... TCtorArgs >
PmrUniquePtr< T > pmrAllocateUnique( const PmrByteAllocator& allocator, TCtorArgs&& ... tCtorArgs )
{
    return PmrUniquePtr< T >{
            std::allocate_shared< T >(
                    PmrAllocator< T >{ allocator }
                    , std::forward< TCtorArgs >( tCtorArgs )... ) };
}

} } } } // namespace Elastic::Apm::Impl::Util
