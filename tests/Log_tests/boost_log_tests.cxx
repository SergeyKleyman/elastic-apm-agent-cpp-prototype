// TODO: Sergey Kleyman: Remove boost_log_tests.cxx when not necessary anymore

//    #include "TestUtil/unit_test_util.hxx"
//
//    #include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/iomanip.hxx"
//    #include "Elastic/Apm/Impl/wrapped_3rd_party_headers/prefix.hxx"
//    #include <boost/smart_ptr/make_unique.hpp>
//    #include <boost/log/sinks/text_file_backend.hpp>
//    #include <boost/filesystem.hpp>
//    #include <thread>
//    #include <chrono>
//    #include <boost/chrono.hpp>
//    #include "Elastic/Apm/Impl/wrapped_3rd_party_headers/suffix.hxx"
//    #include "Elastic/Apm/Impl/Util/repeat_n_times.hxx"
//
//    TEST_SUITE_BEGIN( Log_tests ) // NOLINT(cert-err58-cpp)
//    TEST_SUITE_BEGIN( boost_log_tests ) // NOLINT(cert-err58-cpp)
//
//    using namespace Elastic::Apm::Util;
//
//    namespace logging = boost::log;
//    namespace sinks = boost::log::sinks;
//    //    namespace src = boost::log::sources;
//    //    namespace expr = boost::log::expressions;
//    //    namespace attrs = boost::log::attributes;
//    namespace keywords = boost::log::keywords;
//
//    using Sink = boost::log::sinks::text_file_backend;
//
//    inline
//    bool isError( const boost::system::error_code& errorCode )
//    {
//        return static_cast< bool >( errorCode );
//    }
//
//    class RotateOnFirstCall
//    {
//    public:
//
//        explicit RotateOnFirstCall( bool shouldRotateOnFirstCall )
//            : _shouldRotateOnNextCall{ shouldRotateOnFirstCall }
//        {
//        }
//
//        bool operator() () const
//        {
//            if ( _shouldRotateOnNextCall )
//            {
//                _shouldRotateOnNextCall = false;
//                return true;
//            }
//
//            return false;
//        }
//
//    private:
//
//        mutable bool _shouldRotateOnNextCall;
//    };
//
//    std::unique_ptr< Sink > buildSink()
//    {
//        std::string activeFile = "LOGs/Elastic_APM_Cpp_Agent.log";
//
//        bool shouldRotateOnFirstCall = false;
//        boost::system::error_code errorCode;
//        bool fileExists = boost::filesystem::exists( activeFile, /* out */ errorCode );
//        // TODO: Sergey Kleyman: Rotate only when file exists and size > 0
//        if ( ( ! isError( errorCode ) ) && fileExists )
//        {
//            auto fileSize = boost::filesystem::file_size( activeFile, /* out */ errorCode );
//            if ( ( ! isError( errorCode ) ) && ( fileSize > 0 ) )
//            {
//                shouldRotateOnFirstCall = true;
//            }
//        }
//
//        auto sink = boost::make_unique< Sink >(
//                keywords::file_name = activeFile
//                , keywords::target_file_name = "LOGs/Elastic_APM_Cpp_Agent_%Y-%m-%d_%H-%M-%S.%f.log"
//                , keywords::rotation_size = 1 * 1024 * 1024
//                , keywords::enable_final_rotation = false
//                , keywords::auto_flush = false
//                , keywords::open_mode = std::ios_base::out | std::ios_base::app
//                , keywords::time_based_rotation = RotateOnFirstCall{ shouldRotateOnFirstCall }
//        );
//
//        sink->set_file_collector( sinks::file::make_collector(
//                keywords::target = "LOGs"
//                , keywords::max_size = 16 * 1024 * 1024
//                , keywords::min_free_space = 100 * 1024 * 1024
//        ) );
//
//        sink->scan_for_files();
//
//        if ( shouldRotateOnFirstCall ) sink->consume( boost::log::record_view{}, "" );
//
//        return sink;
//    }
//
//    TEST_CASE( file_sink_test ) // NOLINT(cert-err58-cpp)
//    {
//        auto sink = buildSink();
//        ELASTIC_APM_REPEAT_N_TIMES( 100 )
//        {
//            ELASTIC_APM_REPEAT_N_TIMES( 10000 )
//            {
//                std::ostringstream logLineStream;
//                {
//                    std::ostringstream timestampStream;
//                    auto sysClockNow = boost::chrono::system_clock::now();
//                    auto sysClockNowAsDurationSinceEpoch = boost::chrono::duration_cast< boost::chrono::microseconds >( sysClockNow.time_since_epoch() );
//                    auto sysClockNowRoundedToUs = boost::chrono::system_clock::time_point{ sysClockNowAsDurationSinceEpoch };
//                    timestampStream << boost::chrono::time_fmt( boost::chrono::timezone::local ) << sysClockNowRoundedToUs;
//                    auto timestampString = timestampStream.str();
//                    // convert "2020-04-12 14:56:17.933835000 +0300" to "2020-04-12 14:56:17.933835 +0300"
//                    //                                    ^^^ - starts at position 26 (counting from 0)
//                    constexpr std::string::size_type nanoSecondsPos = 26;
//                    constexpr auto expectedNanoSeconds = literalToView( "000 " );
//                    if ( ( nanoSecondsPos + expectedNanoSeconds.length() <= timestampString.length() )
//                         && ( StringView{ &timestampString[ nanoSecondsPos ], expectedNanoSeconds.length() } == expectedNanoSeconds ) )
//                    {
//                        // -1 to leave space before timezone's UTC offset
//                        timestampString.erase( nanoSecondsPos, expectedNanoSeconds.length() - 1 );
//                    }
//
//                    logLineStream << timestampString;
//                }
//
//                logLineStream << " | " << "Some text [" + std::string( 100, 'x' ) + "]";
//
//                sink->consume( boost::log::record_view{}, logLineStream.str() );
//            }
//            std::this_thread::sleep_for( std::chrono::seconds{ 1 } );
//        }
//    }
//
//    TEST_SUITE_END() // boost_log_tests // NOLINT(cert-err58-cpp)
//    TEST_SUITE_END() // Log_tests // NOLINT(cert-err58-cpp)
