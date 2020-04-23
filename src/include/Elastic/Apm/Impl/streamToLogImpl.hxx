#pragma once

#include "Elastic/Apm/Impl/Log/streamToLogImpl_base.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_method.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_via_ADL.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_fundamental.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_std_string.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_Level.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_Optional.hxx"
#include "Elastic/Apm/Impl/Log/write_obj_fields_as_map.hxx"
#include "Elastic/Apm/Impl/Log/wrap_stream_to_log_func.hxx"

namespace Elastic { namespace Apm { namespace Impl
{

using ILogStream = Log::IStream;

} } } // namespace Elastic::Apm::Impl

