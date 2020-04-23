#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx" // std::allocate_shared
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Config/IRawSnapshot_ex.hxx"
#include "Elastic/Apm/Impl/Config/OptionsMetadata.hxx"
#include "Elastic/Apm/Impl/AmbientContext.hxx"
#include "Elastic/Apm/Impl/log.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

using namespace Elastic::Apm::Impl::Log;

template< class SnapshotType >
class Parser
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( Parser );

    explicit Parser( OptionsMetadata< SnapshotType > optsMeta, const AmbientContext& ambientContext )
            : _ambientContext{ ambientContext, ELASTIC_APM_CLASS_NAME_FROM_MEMBER_FUNCTION }
              , _optsMeta{ std::move( optsMeta ) }
    {}

    std::shared_ptr< SnapshotType > parse( const IRawSnapshot& rawSnapshot ) const
    {
        auto resultSnapshot = std::allocate_shared< SnapshotType >( _ambientContext.allocator() );

        for ( const auto& optMeta: _optsMeta )
        {
            optMeta->parse( rawSnapshot, *resultSnapshot );
        }

        return std::move( resultSnapshot );
    }

private:

    AmbientContext _ambientContext;
    const OptionsMetadata< SnapshotType > _optsMeta;
};

} } } } // namespace Elastic::Apm::Impl::Config
