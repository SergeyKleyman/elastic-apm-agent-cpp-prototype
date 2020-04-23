#pragma once

#include "Elastic/Apm/Impl/Util/assertValid_base.hxx"
#include "Elastic/Apm/Impl/Util/assertValid_method.hxx"
#include "Elastic/Apm/Impl/Util/assertValid_via_ADL.hxx"
#include "Elastic/Apm/Impl/Util/assertValid_pointers.hxx"
#include "Elastic/Apm/Impl/Util/assert_macros.hxx"

#define ELASTIC_APM_ASSERT_VALID( obj ) \
    ELASTIC_APM_ASSERT_CALL_IF_O_1_ENABLED( Elastic::Apm::Impl::Util::assertValid( (_ambientContext), obj ) )
