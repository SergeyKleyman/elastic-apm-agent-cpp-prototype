#pragma once

#include "Elastic/Apm/Impl/streamToLogImpl.hxx"
#include "Elastic/Apm/Impl/Log/Backend/visualFormatContextValue.hxx"
#include "Elastic/Apm/Impl/Log/TypeErasedStreamable.hxx"
#include "Has_to_std_ostream_operator.hxx"
#include "TestUtil/unit_test_util_log.hxx"
#include "TestUtil/unit_test_util_allocator.hxx"

namespace ElasticApmTests { namespace TestUtil { namespace Internals
{

using namespace Elastic::Apm::Log;
using namespace Elastic::Apm::Impl::Log;
using namespace Elastic::Apm::Impl::Log::Backend;

template< typename T >
void to_std_ostream_via_streamToLog( const T& t, std::ostream& outStream )
{
    outStream << visualFormatContextValue( TypeErasedStreamable< T >{ t }, allocatorUsingGlobalNewDelete() );
}

} } } // namespace ElasticApmTests::TestUtil::Internals

namespace std // NOLINT(cert-dcl58-cpp)
{

template< typename T >
boost::enable_if_t<
        ! ElasticApmTests::TestUtil::Has_to_std_ostream_operator< T >::value
        && Elastic::Apm::Impl::Log::HasStreamToLogImpl< T >::value
        , ostream& >
operator << ( ostream& outStream, const T& t )
{
    ElasticApmTests::TestUtil::Internals::to_std_ostream_via_streamToLog( t, outStream );
    return outStream;
}

} // namespace std
