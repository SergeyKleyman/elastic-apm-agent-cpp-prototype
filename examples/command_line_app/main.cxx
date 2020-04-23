#include "Elastic/Apm.hxx"
#include <iostream>

// TODO: Sergey Kleyman: Remove after testing
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Impl/ServerComm/SerializedEventsSender.hxx"

int main( int argc, char* argv[] )
{
    std::clog << "\n\n" << CMAKE_PROJECT_DESCRIPTION << " starting...\n\n";

    auto tracer = Elastic::Apm::TracerBuilder{}.build();

    auto textToSend = Elastic::Apm::Util::literalToView( R"-=#=-({"metadata":{"process":{"pid":5612},"service":{"name":"My C++ service","language":{"name":"C++"},"agent":{"version":"0.1-preview","name":"cpp"}}}}\n
{"transaction":{"name":"GET /my_page","id":"0a337a993fe75d4e","trace_id":"121bc9c25356ba222cb4934f1e806da3","type":"script","duration": 0.550, "timestamp":1587364551346016, "result": "0", "context": null, "spans": null, "sampled": null, "span_count": {"started": 0}}}\n
)-=#=-" );

    Elastic::Apm::Impl::ServerComm::SerializedEventsSender::send( textToSend );

    std::clog << "\n\n" << CMAKE_PROJECT_DESCRIPTION << " finished.\n\n";
}
