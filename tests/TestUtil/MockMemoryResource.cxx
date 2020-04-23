#include "TestUtil/MockMemoryResource.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"
#include <new> // std::bad_alloc
#include <iostream> // std::clog
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdlib.hxx" // std::abort

namespace ElasticApmTests { namespace TestUtil
{

std::size_t MockMemoryResource::balance()
{
    return _balance;
}

void* MockMemoryResource::do_allocate( std::size_t blockSize, std::size_t /* alignment */ )
{
    void* ptr = std::malloc( blockSize );
    if ( ptr == nullptr ) throw std::bad_alloc{};

    _balance += blockSize;

    return ptr;
}

void MockMemoryResource::do_deallocate( void* ptr, std::size_t blockSize, std::size_t /* alignment */ )
{
    if ( _balance < blockSize )
    {
        std::clog << "Aborting because global operator new/delete has been called while it shouldn't..." << std::endl;
        std::abort();
    }

    _balance -= blockSize;

    std::free( ptr );
}

bool MockMemoryResource::do_is_equal( const memory_resource& other ) const noexcept
{
    return this == &other;
}

} } // namespace ElasticApmTests::TestUtil
