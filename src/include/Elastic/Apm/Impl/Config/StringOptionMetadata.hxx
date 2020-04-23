#pragma once

#include "Elastic/Apm/Impl/Config/OptionMetadataBase.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

template< class SnapshotType >
class StringOptionMetadata
        : public OptionMetadataBase< SnapshotType, String, StringOptionMetadata< SnapshotType > >
{
private:

    using Base = OptionMetadataBase< SnapshotType, String, StringOptionMetadata< SnapshotType > >;

public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( StringOptionMetadata );

    explicit StringOptionMetadata( PmrString name
                                   , String SnapshotType::* snapshotFieldPtr
                                   , String defaultValue
                                   , const AmbientContext& ambientContext
    )
            : Base{ std::move( name ), snapshotFieldPtr, std::move( defaultValue ), ambientContext }
              , _ambientContext{ ambientContext, ELASTIC_APM_CLASS_NAME_FROM_MEMBER_FUNCTION }
    {}

private:

    friend Base;

    String _parseValue( StringView rawValue ) const
    {
        return String::copyOf( rawValue, _ambientContext.allocator() );
    }

private:

    AmbientContext _ambientContext;
};

} } } } // namespace Elastic::Apm::Impl::Config
