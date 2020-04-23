#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/exception.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/typeinfo.hxx"
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
#include "Elastic/Apm/Util/String.hxx"
#include "Elastic/Apm/Impl/streamToLogImpl.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

using namespace Elastic::Apm::Util;

class Exception
    : public std::exception
{
public:

    explicit Exception( String message )
        : _message{ std::move( message ) }
    {}

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    const char* what() const noexcept override
    {
        return _message.view().cbegin();
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    virtual bool streamToLogImpl( ILogStream& logStream ) const
    {
        if ( ! logStream.writeCurrentValueType( literalToView( "Exception" ) ) ) return false;

        ELASTIC_APM_WRITE_OBJ_FIELDS_AS_MAP(
                logStream
                , ( literalToView( "dynamic type" ), typeid( *this ).name() )
                , ( literalToView( "what" ), what() )
        );

        return true;
    }

private:

    String _message;
};

} } } } // namespace Elastic::Apm::Impl::Util
