#pragma once

#include "Elastic/Apm/Impl/Config/IOptionMetadata.hxx"
#include "Elastic/Apm/Impl/Config/ParseFailedException.hxx"
#include "Elastic/Apm/Impl/AmbientContext.hxx"
#include "Elastic/Apm/Impl/log.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Config
{

using namespace Elastic::Apm::Impl::Log;

template< class SnapshotType, typename ValueType, class OptionMetadataDerived >
class OptionMetadataBase
        : public IOptionMetadata< SnapshotType >
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( OptionMetadataBase );

    explicit OptionMetadataBase( PmrString name
                                 , ValueType SnapshotType::* snapshotFieldPtr
                                 , ValueType defaultValue
                                 , const AmbientContext& ambientContext
    )
            : _ambientContext{ ambientContext, ELASTIC_APM_CLASS_NAME_FROM_MEMBER_FUNCTION }
              , _name{ std::move( name ) }
              , _defaultValue{ std::move( defaultValue ) }
              , _snapshotFieldPtr{ snapshotFieldPtr }
    {}

    void parse( const IRawSnapshot& rawSnapshot, /* out */ SnapshotType& dstSnapshot ) const override
    {
        auto rawValueData = rawSnapshot[ _name.c_str() ];
        if ( ! rawValueData )
        {
            ELASTIC_APM_LOG_DEBUG( "Configuration option is not set - default value will be used"
                                   , _name
                                   , _defaultValue );
            _setValue( dstSnapshot, _defaultValue );
            return;
        }

        try
        {
            auto parsedValue = static_cast< const OptionMetadataDerived* >( this )->_parseValue( rawValueData->value );
            ELASTIC_APM_LOG_DEBUG( "Successfully parsed configuration option"
                                   , _name
                                   , rawValueData
                                   , parsedValue );
            _setValue( dstSnapshot, std::move( parsedValue ) );
        }
        catch ( const ParseFailedException& ex )
        {
            ELASTIC_APM_LOG_WARNING( "Failed to parse configuration option - default value will be used"
                                     , ex
                                     , _name
                                     , rawValueData
                                     , _defaultValue );

            _setValue( dstSnapshot, _defaultValue );
        }
    }

private:

    void _setValue( /* out */ SnapshotType& dstSnapshot, ValueType value ) const
    {
        dstSnapshot.*_snapshotFieldPtr = std::move( value );
    }

private:

    AmbientContext _ambientContext;
    const PmrString _name;
    const ValueType _defaultValue;
    ValueType SnapshotType::* const _snapshotFieldPtr;
};

} } } } // namespace Elastic::Apm::Impl::Config
