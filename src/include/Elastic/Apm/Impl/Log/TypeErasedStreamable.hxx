#pragma once

#include "Elastic/Apm/Log/IStreamable.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Log/streamToLogImpl_base.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log
{

using namespace Elastic::Apm::Log;

template< typename T >
class TypeErasedStreamable
        : public IStreamable
{
public:

    ELASTIC_APM_MOVE_CONSTRUCTIBLE_BUT_NOT_MOVE_ASSIGNABLE( TypeErasedStreamable );

    explicit TypeErasedStreamable( const T& wrappedObj )
            : _wrappedObj{ wrappedObj }
    {}

    StringView preprocessExprToLogNameImpl( StringView outerName ) const override
    {
        return preprocessExprToLogName( _wrappedObj, outerName );
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    bool streamToLogImpl( IStream& logStream ) const override
    {
        return streamToLog( _wrappedObj, logStream );
    }

private:

    const T& _wrappedObj;
};

template< typename T >
TypeErasedStreamable< T > makeTypeErasedStreamable( const T& wrappedObj )
{
    return TypeErasedStreamable< T >{ wrappedObj };
}

} } } } // namespace Elastic::Apm::Impl::Log
