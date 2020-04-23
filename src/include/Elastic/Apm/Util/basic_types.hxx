#pragma once

#ifdef __cpp_lib_byte
#   include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstddef.hxx" // std::byte
#endif

namespace Elastic { namespace Apm { namespace Util
{

#ifdef __cpp_lib_byte
using Byte = std::byte;
#else
enum class Byte : unsigned char
{
};
#endif

} } } // namespace Elastic::Apm::Util
