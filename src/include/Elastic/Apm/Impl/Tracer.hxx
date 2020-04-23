#pragma once

#include "Elastic/Apm/ITracer.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/TracerDependencies.hxx"
#include "Elastic/Apm/Impl/Log/Backend/Manager.hxx"
#include "Elastic/Apm/Impl/log.hxx"
#include "Elastic/Apm/Impl/Util/pmrAllocateUnique.hxx"
#include "Elastic/Apm/Impl/ServerComm/EventSender.hxx"
#include "Elastic/Apm/Impl/AmbientContext.hxx"
#include "Elastic/Apm/Impl/Config/Manager.hxx"

namespace Elastic { namespace Apm { namespace Impl
{

using namespace Elastic::Apm::Impl::Util;

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class Tracer
        : public ITracer
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( Tracer );

    static PTracer create( TracerDependencies tracerDependencies, Config::PSnapshot cfgSnapWithInitSeqOptsOnly )
    {
        return pmrAllocateUnique< Tracer >( tracerDependencies.allocator.get()
                                            , std::move( tracerDependencies )
                                            , std::move( cfgSnapWithInitSeqOptsOnly ) );
    }

    explicit Tracer( TracerDependencies dependencies, const Config::PSnapshot& cfgSnapWithInitSeqOptsOnly )
            : _dependencies{ std::move( dependencies ) }
              , _logBackendManager{ _dependencies.allocator.get()
                                    , _dependencies.timeSource.get()->systemClock()
                                    , *_dependencies.logSink.get()
                                    , cfgSnapWithInitSeqOptsOnly.get() }
              , _ambientContextRoot{ _dependencies.allocator.get(), _logBackendManager.loggerFactory() }
              , _ambientContext{ _ambientContextRoot, ELASTIC_APM_CLASS_NAME_FROM_MEMBER_FUNCTION }
              , _configManager{ *_dependencies.configSource.get(), _ambientContext }
    {
        ELASTIC_APM_LOG_INFO(
                "Created"
                , ELASTIC_APM_WRAP_STREAM_TO_LOG_DIRECT_RETURN( "Provided dependencies"
                                                                , _dependencies.listProvidedDependencies( logStream ) )
        );

        setToDefaultIfNotProvidedByUser(
                _dependencies.eventSink
                , [ & ]()
                {
                    return pmrAllocateUniqueTypeErasedDeleter< ServerComm::EventSender >(
                            _dependencies.allocator.get()
                            , _configManager.snapshotSource()
                            , _ambientContext );
                } );
    }

    bool isNoop() const override
    {
        return false;
    }

private:

    TracerDependencies _dependencies;
    const Log::Backend::Manager _logBackendManager;
    AmbientContextRoot _ambientContextRoot;
    AmbientContext _ambientContext;
    Config::Manager _configManager;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } } // namespace Elastic::Apm::Impl
