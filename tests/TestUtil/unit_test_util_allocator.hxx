#pragma once

#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "TestUtil/MockMemoryResource.hxx"

namespace ElasticApmTests { namespace TestUtil
{

using Elastic::Apm::Util::PmrByteAllocator;

PmrByteAllocator allocatorUsingGlobalNewDelete();

} } // namespace ElasticApmTests::TestUtil
