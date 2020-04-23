#include "unit_test_util_allocator.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"
#include <boost/container/pmr/global_resource.hpp>
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"

namespace ElasticApmTests { namespace TestUtil
{

PmrByteAllocator allocatorUsingGlobalNewDelete()
{
    return { boost::container::pmr::new_delete_resource() };
}

} } // namespace ElasticApmTests::TestUtil
