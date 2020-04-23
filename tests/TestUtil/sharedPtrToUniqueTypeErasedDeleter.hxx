#pragma once

#include "Elastic/Apm/Util/UniquePtrTypeErasedDeleter.hxx"

namespace ElasticApmTests { namespace TestUtil
{

using namespace Elastic::Apm::Util;

template< typename T >
UniquePtrTypeErasedDeleter< T > sharedPtrToUniqueTypeErasedDeleter( std::shared_ptr< T > ptrCopy )
{
    return UniquePtrTypeErasedDeleter< T >{ std::move( ptrCopy ) };
}

} } // namespace ElasticApmTests::TestUtil
