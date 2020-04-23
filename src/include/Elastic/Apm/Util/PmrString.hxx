#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/string.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"

namespace Elastic { namespace Apm { namespace Util
{

template< class CharT, class Traits = std::char_traits< CharT > >
using PmrBasicString = std::basic_string< CharT, Traits, PmrAllocator< CharT > >;

using PmrString = PmrBasicString< char >;

} } } // namespace Elastic::Apm::Util
