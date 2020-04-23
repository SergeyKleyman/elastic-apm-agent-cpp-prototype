#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/type_traits.hxx"

#define ELASTIC_APM_REMOVE_CONST_FROM_THIS() \
            ( \
                const_cast \
                < \
                    boost::remove_const_t \
                    < \
                        boost::remove_reference_t< decltype( *this ) > \
                    > \
                    & \
                > \
                ( *this ) \
            ) \
    /**/

