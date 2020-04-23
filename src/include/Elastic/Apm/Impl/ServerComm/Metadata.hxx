#pragma once

#include "Elastic/Apm/Impl/Util/platform.hxx"
#include "Elastic/Apm/Util/String.hxx"
#include "Elastic/Apm/Impl/ServerComm/Serializer.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace ServerComm
{

using namespace Elastic::Apm::Impl::Util;

/**
 * https://github.com/elastic/apm-server/blob/7.0/docs/spec/metadata.json
 */
struct Metadata
{
    /**
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/service.json
     */
    struct Service
    {
        /**
         * https://github.com/elastic/apm-server/blob/7.0/docs/spec/service.json#L6
         */
        struct Agent
        {
            void operator >>( Serializer& serializer ) const
            {
                ELASTIC_APM_SERIALIZE_JSON_OBJECT_FIELDS(
                        serializer
                        , name
                        , version
                );
            }

            KeywordString name = String::fromLiteral( "Cpp" ); // "maxLength": 1024
            KeywordString version = String::fromLiteral( "0.1-preview" ); // "maxLength": 1024
        };

        /**
         * https://github.com/elastic/apm-server/blob/7.0/docs/spec/service.json#L36
         */
        struct Language
        {
            void operator >>( Serializer& serializer ) const
            {
                ELASTIC_APM_SERIALIZE_JSON_OBJECT_FIELDS(
                        serializer
                        , name
                );
            }

            KeywordString name = String::fromLiteral( "C++" );
        };

        void operator >>( Serializer& serializer ) const
        {
            ELASTIC_APM_SERIALIZE_JSON_OBJECT_FIELDS(
                    serializer
                    , agent
                    , language
            );
        }

        Agent agent;
        Language language;
    };

    /**
     * https://github.com/elastic/apm-server/blob/7.0/docs/spec/process.json
     */
    struct Process
    {
        void operator >>( Serializer& serializer ) const
        {
            ELASTIC_APM_SERIALIZE_JSON_OBJECT_FIELDS(
                    serializer
                    , pid
            );
        }

        ProcessId pid;
    };

    void operator >>( Serializer& serializer ) const
    {
        ELASTIC_APM_SERIALIZE_JSON_OBJECT_FIELDS(
                serializer
                , process
                , service
        );
    }

    Process process;
    Service service;
};

} } } } // namespace Elastic::Apm::Impl::ServerComm
