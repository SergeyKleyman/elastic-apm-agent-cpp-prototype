#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx" // std::shared_ptr
#include "Elastic/Apm/Impl/Util/UniquePtrWrapper.hxx"

namespace Elastic { namespace Apm { namespace Util
{

template< typename T >
using UniquePtrTypeErasedDeleter = Impl::Util::UniquePtrWrapper< T, std::shared_ptr >;

} } } // namespace Elastic::Apm::Util
