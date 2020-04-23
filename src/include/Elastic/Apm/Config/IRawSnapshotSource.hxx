#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx"
#include "Elastic/Apm/Config/IRawSnapshot.hxx"
#include "Elastic/Apm/Util/UniquePtrTypeErasedDeleter.hxx"

namespace Elastic { namespace Apm { namespace Config
{

using namespace Elastic::Apm;

class IRawSnapshotSource
{
protected:

    using PRawSnapshot = Util::UniquePtrTypeErasedDeleter< IRawSnapshot >;

public:

    virtual PRawSnapshot currentSnapshot() = 0;

protected:

    ~IRawSnapshotSource() = default;
};

using PRawSnapshotSource = Util::UniquePtrTypeErasedDeleter< IRawSnapshotSource >;

} } } // namespace Elastic::Apm::Config
