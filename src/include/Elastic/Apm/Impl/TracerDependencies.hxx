#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::move
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Util/UniquePtrTypeErasedDeleter.hxx"
#include "Elastic/Apm/Log/ISink.hxx"
#include "Elastic/Apm/Config/IRawSnapshotSource.hxx"
#include "Elastic/Apm/Util/ITimeSource.hxx"
#include "Elastic/Apm/IEventSink.hxx"
#include "Elastic/Apm/Util/PmrUniquePtr.hxx"
#include "Elastic/Apm/Log/IStream.hxx"

namespace Elastic { namespace Apm { namespace Impl
{

using namespace Elastic::Apm::Util;
using ILogStream = Elastic::Apm::Log::IStream;

using PLogSink = Elastic::Apm::Log::PSink;
using PTimeSource = UniquePtrTypeErasedDeleter< ITimeSource >;
using PEventSink = UniquePtrTypeErasedDeleter< IEventSink >;
using PRawConfigSnapshotSource = Config::PRawSnapshotSource;

struct TracerDependencies
{
    ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( TracerDependencies );

    template< typename T >
    class Dep
    {
    public:

        ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( Dep );

        explicit Dep( String name )
                : _name{ std::move( name ) }
        {}

        void set( T value, bool isProvided )
        {
            _value = std::move( value );
            _isProvided = isProvided;
        }

        const T& get() const
        {
            return _value;
        }

        ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
        bool logIfProvided( ILogStream::IListBuilder& listStream )
        {
            if ( ! _isProvided ) return true;

            return listStream.addAndWriteElement(
                    [ this ]( ILogStream& logStream )
                    {
                        return logStream.writeCurrentValueContent( _name );
                    } );
        }

    private:

        String _name;
        T _value;
        bool _isProvided = false;
    };

    TracerDependencies() = default;

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool listProvidedDependencies( ILogStream& logStream )
    {
        return logStream.writeCurrentValueContentAsList(
                [ this ]( ILogStream::IListBuilder& listStream )
                {
                    if ( ! allocator.logIfProvided( listStream ) ) return false;
                    if ( ! logSink.logIfProvided( listStream ) ) return false;
                    if ( ! configSource.logIfProvided( listStream ) ) return false;
                    if ( ! timeSource.logIfProvided( listStream ) ) return false;
                    return eventSink.logIfProvided( listStream );
                } );
    }

    Dep< PmrByteAllocator > allocator{ String::fromLiteral( "Allocator" ) };
    Dep< PLogSink > logSink{ String::fromLiteral( "LogSink" ) };
    Dep< PRawConfigSnapshotSource > configSource{ String::fromLiteral( "RawConfigSnapshotSource" ) };
    Dep< PTimeSource > timeSource{ String::fromLiteral( "TimeSource" ) };
    Dep< PEventSink > eventSink{ String::fromLiteral( "EventSink" ) };
};

template< typename DepPtr, typename CreateDefaultValue >
void setToDefaultIfNotProvidedByUser( TracerDependencies::Dep< DepPtr >& dep, CreateDefaultValue&& createDefaultValue )
{
    if ( dep.get() ) return;
    dep.set( std::forward< CreateDefaultValue >( createDefaultValue )(), /* isProvided: */ false );
}

} } } // namespace Elastic::Apm::Impl
