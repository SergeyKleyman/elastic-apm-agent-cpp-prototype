#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
#include "Elastic/Apm/Util/UniquePtrTypeErasedDeleter.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"

namespace Elastic { namespace Apm { namespace Util
{

template< class T, typename ... TCtorArgs >
UniquePtrTypeErasedDeleter< T > pmrAllocateUniqueTypeErasedDeleter(
        const PmrByteAllocator& allocator
        , TCtorArgs&& ... tCtorArgs
)
{
    return UniquePtrTypeErasedDeleter< T >{
            std::allocate_shared< T >(
                    PmrAllocator< T >{ allocator }
                    , std::forward< TCtorArgs >( tCtorArgs )... ) };
}

} } } // namespace Elastic::Apm::Util
