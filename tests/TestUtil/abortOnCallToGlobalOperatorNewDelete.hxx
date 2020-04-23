#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstdint.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/functional.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"

namespace ElasticApmTests { namespace TestUtil
{

using AbortFunc = std::function<void ()>;

namespace Internals
{
std::pair< bool, AbortFunc > abortOnCallToGlobalOperatorNewDelete( bool shouldAbort, AbortFunc abortFunc = AbortFunc{} );
} // namespace Internals

class AbortOnCallToGlobalOperatorNewDeleteGuard
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( AbortOnCallToGlobalOperatorNewDeleteGuard );

    explicit AbortOnCallToGlobalOperatorNewDeleteGuard( bool shouldAbort = true, AbortFunc abortFunc = AbortFunc{} )
        : _saved_state{ Internals::abortOnCallToGlobalOperatorNewDelete( shouldAbort, std::move( abortFunc ) ) }
    {
    }

    ~AbortOnCallToGlobalOperatorNewDeleteGuard()
    {
        Internals::abortOnCallToGlobalOperatorNewDelete( _saved_state.first, _saved_state.second );
    }

private:

    const std::pair< bool, AbortFunc > _saved_state;
};

template < typename Proc >
void execAbortingOnCallToGlobalOperatorNewDelete( Proc&& proc )
{
    AbortOnCallToGlobalOperatorNewDeleteGuard abortOnCallToGlobalOperatorNewDeleteGuard{ /* shouldAbort: */ true };
    std::forward< Proc >( proc )();
}

} } // namespace ElasticApmTests::TestUtil