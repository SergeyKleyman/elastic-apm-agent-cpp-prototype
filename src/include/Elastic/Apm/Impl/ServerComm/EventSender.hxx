#pragma once

#include "Elastic/Apm/IEventSink.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Config/SnapshotSource.hxx"
#include "Elastic/Apm/Impl/AmbientContext.hxx"
#include "Elastic/Apm/Impl/ServerComm/SerializedEventsSender.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace ServerComm
{

#ifdef _MSC_VER // Visual C++
#   pragma warning( push, 0 )
#   pragma warning( disable : 4265 ) // Compiler Warning (level 3) C4265: class has virtual functions, but destructor is not virtual
#endif

class EventSender
        : public IEventSink
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( EventSender );

    explicit EventSender( Config::SnapshotSource& cfgSnapshotSource, const AmbientContext& ambientContext )
            : _ambientContext{ ambientContext, ELASTIC_APM_CLASS_NAME_FROM_MEMBER_FUNCTION }
              , _cfgSnapshotSource{ cfgSnapshotSource }
              , _serializedEventsSender{ cfgSnapshotSource, ambientContext }
    {}

    void send( const ISpanDto& /*spanDto*/ ) override
    {
        // TODO: Sergey Kleyman: Implement: EventSender::send( const ISpanDto& spanDto )
    }

    void send( const ITransactionDto& /*transactionDto*/ ) override
    {
        // TODO: Sergey Kleyman: Implement: EventSender::( const ITransactionDto& transactionDto )
    }

private:

    AmbientContext _ambientContext;
    Config::SnapshotSource& _cfgSnapshotSource;
    SerializedEventsSender _serializedEventsSender;
};

#ifdef _MSC_VER // Visual C++
#   pragma warning( pop )
#endif

} } } } // namespace Elastic::Apm::Impl::ServerComm
