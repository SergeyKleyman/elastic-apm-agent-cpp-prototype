#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstddef.hxx" // std::nullptr_t
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/variant.hxx"
#include "Elastic/Apm/Util/String.hxx"

namespace Elastic { namespace Apm
{

using LabelValue = boost::variant< std::nullptr_t
                                   , bool
                                   , double
                                   , Util::String >;

} } // namespace Elastic::Apm
