#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
#include "Elastic/Apm/Config/IRawSnapshotSource.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Util/pmrAllocateUniqueTypeErasedDeleter.hxx"
#include "Elastic/Apm/Util/PmrString.hxx"
#include "Elastic/Apm/Impl/Util/platform.hxx" // getEnvVar
#include "Elastic/Apm/Impl/Util/text_util.hxx"

namespace Elastic { namespace Apm { namespace Config
{

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

template< typename OptNameToEnvVarName >
class EnvVarsRawSnapshotSource
        : public IRawSnapshotSource
{
private:

    using PmrString = Util::PmrString;
    using PmrByteAllocator = Util::PmrByteAllocator;

public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( EnvVarsRawSnapshotSource );

    static PRawSnapshotSource create( OptNameToEnvVarName&& optNameToEnvVarName, const Util::PmrByteAllocator& allocator )
    {
        return Util::pmrAllocateUniqueTypeErasedDeleter< EnvVarsRawSnapshotSource< OptNameToEnvVarName > >(
                allocator
                , std::forward< OptNameToEnvVarName >( optNameToEnvVarName )
                , allocator );
    }

    explicit EnvVarsRawSnapshotSource( OptNameToEnvVarName optNameToEnvVarName, const PmrByteAllocator& allocator )
            : _allocator{ allocator }
              , _optNameToEnvVarName{ optNameToEnvVarName }
    {}

    PRawSnapshot currentSnapshot() override
    {
        return Util::pmrAllocateUniqueTypeErasedDeleter< RawSnapshot >( _allocator, *this );
    }

private:

    class RawSnapshot
            : public IRawSnapshot
    {
    public:

        ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( RawSnapshot );

        explicit RawSnapshot( const EnvVarsRawSnapshotSource& parent )
                : _parent{ parent }
        {}

        Optional< ValueData > operator []( const char* optName ) const override
        {
            PmrString envVarName = _parent._optNameToEnvVarName( optName, _parent._allocator );
            auto envVarValue = Impl::Util::getEnvVar( envVarName.c_str(), _parent._allocator );
            if ( ! envVarValue ) return {};
            Optional< ValueData > retVal{ ValueData{} };
            retVal->value = std::move( *envVarValue );
            retVal->dbgValueSourceDesc = String::fromLiteral( "Environment variables" );
            return retVal;
        }

        const EnvVarsRawSnapshotSource& _parent;
    };

private:

    const PmrByteAllocator _allocator;
    const OptNameToEnvVarName _optNameToEnvVarName;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

template< typename OptNameToEnvVarName >
PRawSnapshotSource createEnvVarsRawSnapshotSource(
        OptNameToEnvVarName&& optNameToEnvVarName
        , const Util::PmrByteAllocator& allocator )
{
    return EnvVarsRawSnapshotSource< OptNameToEnvVarName >::create(
            std::forward< OptNameToEnvVarName >( optNameToEnvVarName )
            , allocator );
}

inline
Util::String envVarNameDefaultPrefix()
{
    return Util::String::fromLiteral( "ELASTIC_APM_" );
}

inline
PRawSnapshotSource createPrefixEnvVarsRawSnapshotSource( Util::String prefix, const Util::PmrByteAllocator& allocator )
{
    return Config::createEnvVarsRawSnapshotSource(
            [ prefix ]( const char* optName, const PmrByteAllocator& allocator ) -> Util::PmrString
            {
                Util::PmrString envVarName{ prefix.view().begin(), prefix.view().length(), allocator };
                envVarName.append( optName );
                Impl::Util::toUpperCaseInplace( &( envVarName[ prefix.view().length() ] )
                                                , envVarName.length() - prefix.view().length() );
                return envVarName;
            }
            , allocator );
}

inline
PRawSnapshotSource createDefaultPrefixEnvVarsRawSnapshotSource( const Util::PmrByteAllocator& allocator )
{
    return createPrefixEnvVarsRawSnapshotSource( Config::envVarNameDefaultPrefix(), allocator );
}

} } } // namespace Elastic::Apm::Config
