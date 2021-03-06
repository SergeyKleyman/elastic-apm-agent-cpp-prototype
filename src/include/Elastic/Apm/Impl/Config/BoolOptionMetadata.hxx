#pragma once

#include "Elastic/Apm/Impl/Config/OptionMetadataBase.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

template< class SnapshotType >
class BoolOptionMetadata
        : public OptionMetadataBase< SnapshotType, bool, BoolOptionMetadata< SnapshotType > >
{
private:

    using Base = OptionMetadataBase< SnapshotType, bool, BoolOptionMetadata< SnapshotType > >;

public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( BoolOptionMetadata );

    explicit BoolOptionMetadata( PmrString name
                                 , bool SnapshotType::* snapshotFieldPtr
                                 , bool defaultValue
                                 , const AmbientContext& ambientContext
    )
            : Base{ std::move( name ), snapshotFieldPtr, std::move( defaultValue ), ambientContext }
    {}

private:

    friend Base;

    /**
     * @throws ParseFailedException
     */
    bool _parseValue( StringView rawValue ) const
    {
        if ( areEqualIgnoringCase( rawValue, "true" ) ) return true;
        if ( areEqualIgnoringCase( rawValue, "false" ) ) return false;

        throw ParseFailedException( String::fromLiteral( "Not a valid boolean value" ) );
    }
};

} } } } // namespace Elastic::Apm::Impl::Config
