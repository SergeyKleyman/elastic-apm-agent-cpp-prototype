#include "abortOnCallToGlobalOperatorNewDelete.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"
#include <new> // std::bad_alloc
#include <iostream> // std::clog
#include <boost/stacktrace.hpp>
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdlib.hxx" // std::malloc, std::free
#include "Elastic/Apm/Impl/Util/OnScopeExit.hxx"

namespace ElasticApmTests { namespace TestUtil { namespace Internals
{

void defaultAbortOnCallToGlobalOperatorNewDelete()
{
    std::clog << "Aborting because global operator new/delete has been called while it shouldn't..." << std::endl;
    std::clog << "Current stacktrace ..." << std::endl;
    std::cout << boost::stacktrace::stacktrace() << std::endl;
    std::abort();
}

static bool g_shouldAbortOnCallToGlobalOperatorNewDelete;
static AbortFunc g_abortFuncOnCallToGlobalOperatorNewDelete = defaultAbortOnCallToGlobalOperatorNewDelete; // NOLINT(cert-err58-cpp)

void callAbortFunc()
{
    // Temporarily set shouldAbort to false to avoid re-entrance if abortFunc calls new/delete
    ElasticApmTests::TestUtil::Internals::g_shouldAbortOnCallToGlobalOperatorNewDelete = false;
    ELASTIC_APM_ON_SCOPE_EXIT(( [&](){ ElasticApmTests::TestUtil::Internals::g_shouldAbortOnCallToGlobalOperatorNewDelete = true; } ));

    ElasticApmTests::TestUtil::Internals::g_abortFuncOnCallToGlobalOperatorNewDelete();
}

std::pair< bool, AbortFunc > abortOnCallToGlobalOperatorNewDelete( bool shouldAbort, AbortFunc abortFunc )
{
    bool old_shouldAbort = g_shouldAbortOnCallToGlobalOperatorNewDelete;
    AbortFunc old_abortFunc{ std::move( g_abortFuncOnCallToGlobalOperatorNewDelete ) };
    g_shouldAbortOnCallToGlobalOperatorNewDelete = shouldAbort;
    g_abortFuncOnCallToGlobalOperatorNewDelete = abortFunc
            ? std::move( abortFunc )
            : defaultAbortOnCallToGlobalOperatorNewDelete;
    return { old_shouldAbort, std::move( old_abortFunc ) };
}

} } } // namespace ElasticApmTests::TestUtil::Internals

void* operator new( std::size_t blockSize )
{
    if ( ElasticApmTests::TestUtil::Internals::g_shouldAbortOnCallToGlobalOperatorNewDelete )
    {
        ElasticApmTests::TestUtil::Internals::callAbortFunc();
    }

    void* ptr = std::malloc( blockSize );
    if ( ptr == nullptr ) throw std::bad_alloc{};
    return ptr;
}

void operator delete( void* ptr ) noexcept
{
    if ( ElasticApmTests::TestUtil::Internals::g_shouldAbortOnCallToGlobalOperatorNewDelete )
    {
        ElasticApmTests::TestUtil::Internals::callAbortFunc();
    }

    std::free( ptr );
}
