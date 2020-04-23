#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"
#include <boost/container/pmr/memory_resource.hpp>
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"

namespace ElasticApmTests { namespace TestUtil
{

class MockMemoryResource
        : public boost::container::pmr::memory_resource
{
public:

    std::size_t balance();

protected:

    void* do_allocate( std::size_t blockSize, std::size_t /* alignment */ ) override;
    void do_deallocate( void* ptr, std::size_t /* blockSize */, std::size_t /* alignment */ ) override;
    bool do_is_equal( const memory_resource& other ) const noexcept override;

private:

    std::size_t _balance = 0;
};

} } // namespace ElasticApmTests::TestUtil
