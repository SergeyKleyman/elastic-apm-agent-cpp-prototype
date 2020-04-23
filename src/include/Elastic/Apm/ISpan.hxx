#pragma once

#include "Elastic/Apm/ISpanDto.hxx"

namespace Elastic { namespace Apm
{

class ISpan
        : public ISpanDto
{
public:


protected:

    ~ISpan() = default;
};

} } // namespace Elastic::Apm
