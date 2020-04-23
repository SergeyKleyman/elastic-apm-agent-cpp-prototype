#pragma once

#include "Elastic/Apm/Util/basic_types.hxx" // Byte
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdint.hxx" // uint8_t

namespace Elastic { namespace Apm { namespace Util
{

template< uint8_t sizeInBytesArg >
class BinaryId
{
public:

    static constexpr uint8_t sizeInBytes = sizeInBytesArg;

private:

    using Byte = Util::Byte;

private:

    Byte _bytes[sizeInBytes];
};

} } } // namespace Elastic::Apm::Util
