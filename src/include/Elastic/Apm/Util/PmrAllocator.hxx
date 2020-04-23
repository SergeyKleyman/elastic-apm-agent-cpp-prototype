#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/container/pmr/polymorphic_allocator.hxx"

#include "Elastic/Apm/Util/basic_types.hxx" // Byte

namespace Elastic { namespace Apm { namespace Util
{

using MemoryResource = boost::container::pmr::memory_resource;

template< typename T >
using PmrAllocator = boost::container::pmr::polymorphic_allocator< T >;

using PmrByteAllocator = PmrAllocator< Byte >;

} } } // namespace Elastic::Apm::Util
