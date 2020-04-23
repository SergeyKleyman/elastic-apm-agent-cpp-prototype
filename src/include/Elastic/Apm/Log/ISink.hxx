#pragma once

#include "Elastic/Apm/Log/RecordDataRefs.hxx"
#include "Elastic/Apm/Util/UniquePtrTypeErasedDeleter.hxx"

namespace Elastic { namespace Apm { namespace Log
{

class ISink
{
public:

    virtual void consume( const RecordDataRefs& recDataRefs ) = 0;

protected:

    ~ISink() = default;
};

using PSink = Util::UniquePtrTypeErasedDeleter< ISink >;

} } } // namespace Elastic::Apm::Log
