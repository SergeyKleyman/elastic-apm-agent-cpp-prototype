#pragma once

#include "Elastic/Apm/IEventSink.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"
#include "Elastic/Apm/Impl/Config/SnapshotSource.hxx"
#include "Elastic/Apm/Impl/AmbientContext.hxx"

// TODO: Sergey Kleyman: Wrap headers
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"
#include <boost/beast/core.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace ServerComm
{

using namespace Elastic::Apm;
using namespace Elastic::Apm::Impl;

class SerializedEventsSender
{
public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( SerializedEventsSender );

    explicit SerializedEventsSender( Config::SnapshotSource& cfgSnapshotSource, const AmbientContext& ambientContext )
            : _ambientContext{ ambientContext, ELASTIC_APM_CLASS_NAME_FROM_MEMBER_FUNCTION }
              , _cfgSnapshotSource{ cfgSnapshotSource }
    {}

    static void send( StringView serializedEventAsLine )
    {
        _send( serializedEventAsLine );
    }

private:

    static void _send( StringView text )
    {
        namespace beast = boost::beast;     // from <boost/beast.hpp>
        namespace http = beast::http;       // from <boost/beast/http.hpp>
        namespace net = boost::asio;        // from <boost/asio.hpp>
        using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

        try
        {
            auto const host = "localhost";
            auto const port = "8200";
            auto const target = "/intake/v2/events";
            int version = 11;

            // The io_context is required for all I/O
            net::io_context ioc;

            // These objects perform our I/O
            tcp::resolver resolver( ioc );
            beast::tcp_stream stream( ioc );

            // Look up the domain name
            auto const results = resolver.resolve( host, port );

            // Make the connection on the IP address we get from a lookup
            stream.connect( results );

            // Set up an HTTP POST request message
            http::request< http::string_body > req{ http::verb::post, target, version };
            req.set( http::field::host, host );
            req.set( http::field::content_type, "application/x-ndjson" );
            req.set( http::field::user_agent, BOOST_BEAST_VERSION_STRING );

            std::clog << "text: [ " << text.length() << " ]: " << text << "\n";
            req.body() = std::string{ text.begin(), text.length() };
            req.set( http::field::content_length, text.length() );

            // Send the HTTP request to the remote host
            http::write( stream, req );

            // This buffer is used for reading and must be persisted
            beast::flat_buffer buffer;

            // Declare a container to hold the response
            http::response< http::dynamic_body > res;

            // Receive the HTTP response
            http::read( stream, buffer, res );

            // Write the message to standard out
            std::cout << res << std::endl;

            // Gracefully close the socket
            beast::error_code ec;
            stream.socket().shutdown( tcp::socket::shutdown_both, ec );

            // not_connected happens sometimes
            // so don't bother reporting it.
            //
            if ( ec && ec != beast::errc::not_connected )
            {
                throw beast::system_error{ ec };
            }

            // If we get here then the connection is closed gracefully
        }
        catch ( std::exception const& e )
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

private:

    AmbientContext _ambientContext;
    Config::SnapshotSource& _cfgSnapshotSource;
};

} } } } // namespace Elastic::Apm::Impl::ServerComm
