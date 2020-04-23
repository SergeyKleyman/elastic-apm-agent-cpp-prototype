#pragma once

#include "Elastic/Apm/Config/IRawSnapshot.hxx"
#include "Elastic/Apm/Impl/streamToLogImpl.hxx"

//
// NOTE: streamToLogImpl for IRawSnapshot::ValueData has to be in the same namespace as IRawSnapshot::ValueData
// so that streamToLogImpl can be found via ADL
//
namespace Elastic { namespace Apm { namespace Config
{

ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
inline
bool streamToLogImpl( const IRawSnapshot::ValueData& val, Log::IStream& logStream )
{
    using namespace Util;

    if ( ! logStream.writeCurrentValueType( literalToView( "IRawSnapshot::ValueData" ) ) ) return false;

    ELASTIC_APM_WRITE_OBJ_FIELDS_AS_MAP(
            logStream
            , ( literalToView( "value" ), val.value )
            , ( literalToView( "dbgValueSourceDesc" ), val.dbgValueSourceDesc )
    );

    return true;
}

} } } // namespace Elastic::Apm::Config
