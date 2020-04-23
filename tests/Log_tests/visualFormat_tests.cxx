// TODO: Sergey Kleyman: Uncomment visualFormat_tests.cxx

//    #include "TestUtil/unit_test_util.hxx"
//    #include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::forward
//    #include "Elastic/Apm/Impl/Log/Backend/visualFormat.hxx"
//    #include "TestUtil/unit_test_util_allocator.hxx"
//    #include "Elastic/Apm/Impl/Util/pmrAllocateUnique.hxx"
//    #include "TestUtil/abortOnCallToGlobalOperatorNewDelete.hxx"
//    #include "Elastic/Apm/Impl/Util/repeat_n_times.hxx"
//
//    TEST_SUITE_BEGIN( Log_tests ) // NOLINT(cert-err58-cpp)
//    TEST_SUITE_BEGIN( visualFormat_tests ) // NOLINT(cert-err58-cpp)
//
//    using namespace Elastic::Apm::Impl::Util;
//    using namespace Elastic::Apm::Impl::Log;
//    using namespace ElasticApmTests::TestUtil;
//
//    std::ostringstream makeTestOStringStream()
//    {
//        std::ostringstream retVal;
//        retVal.imbue( std::locale::classic() );
//        return retVal;
//    }
//
//    void write( std::ostringstream& outStringStream, StringView strView )
//    {
//        outStringStream.write( strView.begin(), static_cast< std::streamsize >( strView.length() ) );
//    }
//
//    std::string toStdString( StringView strView )
//    {
//        return std::string{  strView.begin(), strView.length() };
//    }
//
//    TEST_SUITE_BEGIN( format_RecordContext_tests ) // NOLINT(cert-err58-cpp)
//
//    template< typename FillRecCtx, typename TestFormatResult >
//    void visualFormatContextAndTest( FillRecCtx&& fillRecCtx, TestFormatResult&& testFormatResult, StringView linePrefix = "" )
//    {
//        MockMemoryResource testMemResource;
//        String formatResult;
//
//        {
//            VisualStreamToString txtOutStream{ &testMemResource };
//
//            {
//                AbortOnCallToGlobalOperatorNewDeleteGuard abortOnCallToGlobalOperatorNewDeleteGuard;
//
//                v1_RecordContext recCtx{ &testMemResource };
//                std::forward< FillRecCtx >( fillRecCtx )( recCtx );
//
//                visualFormat( recCtx, txtOutStream, linePrefix );
//            }
//
//            formatResult = String::copyOf( txtOutStream.view(), allocatorUsingGlobalNewDelete() );
//        }
//
//        UT_ASSERT_EQ( testMemResource.balance(), 0 );
//
//        std::forward< TestFormatResult >( testFormatResult )( formatResult.view() );
//    }
//
//    template< typename ValueContent >
//    v1_RecordContextValue makeRecordContextValue( const ValueContent& valContent )
//    {
//        v1_RecordContextValue retVal;
//        retVal.content = valContent;
//        return retVal;
//    }
//
//    using ValueExpectedFormattedDataSet = std::vector< std::pair< v1_RecordContextValue, String > >;
//
//    ValueExpectedFormattedDataSet buildValueExpectedFormattedDataSet()
//    {
//        std::vector< std::pair< v1_RecordContextValue, String > > retVal;
//
//        retVal.emplace_back( makeRecordContextValue< std::nullptr_t >( nullptr )
//                             , String::assumeSufficientLifetime( VisualFormat::null() ) );
//
//        retVal.emplace_back( makeRecordContextValue( false ), String::fromLiteral( "false" ) );
//        retVal.emplace_back( makeRecordContextValue( true ), String::fromLiteral( "true" ) );
//
//        retVal.emplace_back( makeRecordContextValue< uintmax_t >( 0 ), String::fromLiteral( "0" ) );
//        retVal.emplace_back( makeRecordContextValue< intmax_t >( 0 ), String::fromLiteral( "0" ) );
//        retVal.emplace_back( makeRecordContextValue< uintmax_t >( 1 ), String::fromLiteral( "1" ) );
//        retVal.emplace_back( makeRecordContextValue< intmax_t >( 1 ), String::fromLiteral( "1" ) );
//        retVal.emplace_back( makeRecordContextValue< intmax_t >( -22 ), String::fromLiteral( "-22" ) );
//        retVal.emplace_back( makeRecordContextValue< uintmax_t >( 1234567890 ), String::fromLiteral( "1234567890" ) );
//        retVal.emplace_back( makeRecordContextValue< intmax_t >( 1234567890 ), String::fromLiteral( "1234567890" ) );
//        retVal.emplace_back( makeRecordContextValue< intmax_t >( -9876543210 ), String::fromLiteral( "-9876543210" ) );
//
//        retVal.emplace_back( makeRecordContextValue( String::fromLiteral( "ctx element value" ) )
//                             , String::fromLiteral( "`ctx element value'" ) );
//
//        return retVal;
//    }
//
//    std::string buildExpectedResult( const ValueExpectedFormattedDataSet& valueExpectedFormattedDataSet
//                                    , unsigned int numberOfCtxElements
//                                    , bool isHorizontalFormat )
//    {
//        auto expectedResultStream{ makeTestOStringStream() };
//
//        expectedResultStream << "<size: " << numberOfCtxElements << ">";
//
//        if ( isHorizontalFormat )
//        {
//            expectedResultStream << "{ ";
//        }
//
//        ELASTIC_APM_REPEAT_N_TIMES_VAR( elementIndex, numberOfCtxElements )
//        {
//            if ( isHorizontalFormat )
//            {
//                if ( elementIndex != 0 )
//                {
//                    expectedResultStream << ", ";
//                }
//            }
//            else
//            {
//                expectedResultStream << "\n" << VisualFormat::indent();
//            }
//            expectedResultStream << "ctxElement_" << ( elementIndex + 1 ) << ": ";
//            write( expectedResultStream, valueExpectedFormattedDataSet[ elementIndex ].second );
//        }
//
//        if ( isHorizontalFormat )
//        {
//            expectedResultStream << " }";
//        }
//
//        return expectedResultStream.str();
//    }
//
//    std::string buildExpectedResult( const ValueExpectedFormattedDataSet& valueExpectedFormattedDataSet
//                                    , unsigned int numberOfCtxElements )
//    {
//        if ( numberOfCtxElements == 0 )
//        {
//            return std::string{ VisualFormat::emptyMap() };
//        }
//
//        auto expectedResult = buildExpectedResult( valueExpectedFormattedDataSet
//                                                   , numberOfCtxElements
//                                                   , /* isHorizontalFormat: */ true );
//
//        if ( expectedResult.length() <= VisualFormat::maxHorizontalFormatLength() )
//        {
//            return expectedResult;
//        }
//
//        return buildExpectedResult( valueExpectedFormattedDataSet
//                                    , numberOfCtxElements
//                                    , /* isHorizontalFormat: */ false );
//    }
//
//    TEST_CASE( one_element_empty_linePrefix ) // NOLINT(cert-err58-cpp)
//    {
//        const auto valueExpectedFormattedDataSet = buildValueExpectedFormattedDataSet();
//        ELASTIC_APM_REPEAT_N_TIMES_VAR( numberOfCtxElements, valueExpectedFormattedDataSet.size() )
//        {
//            visualFormatContextAndTest(
//                    [&]( v1_RecordContext& recCtx )
//                    {
//                        ELASTIC_APM_REPEAT_N_TIMES_VAR( elementIndex, numberOfCtxElements )
//                        {
//                            auto key = ( VisualStreamToString{ recCtx.elements.get_allocator() }
//                                << literalToView( "ctxElement_" ) << ( elementIndex + 1 ) ).release();
//                            recCtx.elements.emplace_back( std::move( key )
//                                    , valueExpectedFormattedDataSet[ elementIndex ].first );
//                        }
//                    }
//                    , [&]( StringView formatResult )
//                    {
//                        UT_ASSERT_EQ( toStdString( formatResult )
//                                    , buildExpectedResult( valueExpectedFormattedDataSet, numberOfCtxElements ) );
//                    } );
//        }
//    }
//
//    TEST_SUITE_END() // format_RecordContext_tests // NOLINT(cert-err58-cpp)
//
//    // TODO: Sergey Kleyman: Uncomment
//    //TEST_SUITE_BEGIN( format_RecordContextValue_tests ) // NOLINT(cert-err58-cpp)
//    //
//    //TEST_CASE( just_build_Tracer )
//    //// NOLINT(cert-err58-cpp)
//    //{
//    ////    visualFormat
//    //}
//    //
//    //TEST_SUITE_END() // format_RecordContextValue_tests // NOLINT(cert-err58-cpp)
//
//    TEST_SUITE_END() // visualFormat_tests // NOLINT(cert-err58-cpp)
//    TEST_SUITE_END() // Log_tests // NOLINT(cert-err58-cpp)
