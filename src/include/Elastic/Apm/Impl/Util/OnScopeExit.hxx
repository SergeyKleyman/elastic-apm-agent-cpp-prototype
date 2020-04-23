#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/compressed_pair.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/preprocessor/cat.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

template< typename OnScopeExitFunc >
class OnScopeExit
{
public:

    ELASTIC_APM_MOVE_CONSTRUCTIBLE_BUT_NOT_MOVE_ASSIGNABLE( OnScopeExit ); // NOLINT(hicpp-noexcept-move,performance-noexcept-move-constructor)

    explicit OnScopeExit( OnScopeExitFunc&& onScopeExitFunc )
            : _isEnabled_onScopeExitFunc{ true, std::forward< OnScopeExitFunc >( onScopeExitFunc ) }
    {
    }

    ~OnScopeExit()
    {
        if ( _isEnabled_onScopeExitFunc.first() )
        {
            _isEnabled_onScopeExitFunc.second()();
        }
    }

    void disable()
    {
        _isEnabled_onScopeExitFunc.first() = false;
    }

private:

    boost::compressed_pair< bool, OnScopeExitFunc > _isEnabled_onScopeExitFunc;
};

template< typename OnScopeExitFunc >
OnScopeExit< OnScopeExitFunc > makeOnScopeExit( OnScopeExitFunc&& onScopeExitFunc )
{
    return OnScopeExit< OnScopeExitFunc >{ std::forward< OnScopeExitFunc >( onScopeExitFunc ) };
}

} } } } // namespace Elastic::Apm::Impl::Util

#define ELASTIC_APM_ON_SCOPE_EXIT( callable ) \
    auto BOOST_PP_CAT( elastic_apm_on_scope_exit_guard_var, __LINE__ ) = Elastic::Apm::Impl::Util::makeOnScopeExit( callable )
/**/