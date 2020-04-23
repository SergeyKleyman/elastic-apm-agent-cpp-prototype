#pragma once

#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Log/IStreamable.hxx"
#include "Elastic/Apm/Util/PmrAllocator.hxx"
#include "Elastic/Apm/Util/PmrString.hxx"
#include "Elastic/Apm/Util/StringView.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Log { namespace Backend
{

using namespace Elastic::Apm::Util;
using namespace Elastic::Apm::Log;
using namespace Elastic::Apm::Impl::Util;
using namespace Elastic::Apm::Impl::Log;

//namespace VisualFormat
//{
//
//constexpr StringView blank()
//{
//    return literalToView( "<blank>" );
//}
//
//constexpr StringView null()
//{
//    return literalToView( "<null>" );
//}
//
//constexpr StringView emptyList()
//{
//    return literalToView( "<empty list>" );
//}
//
//constexpr StringView emptyMap()
//{
//    return literalToView( "<empty map>" );
//}
//
//constexpr std::size_t maxHorizontalFormatLength()
//{
//    return 100;
//}
//
//constexpr StringView indent()
//{
//    return literalToView( "    " );
//}
//
//} // namespace VisualFormat

ELASTIC_APM_INLINE_FOR_IMPL
PmrString visualFormatContextValue( const IStreamable& t, const PmrByteAllocator& allocator, StringView linePrefix = "" );

} } } } } // namespace Elastic::Apm::Impl::Log::Backend

#ifndef ELASTIC_APM_SEPARATE_COMPILATION
#   include "Elastic/Apm/Impl/Log/Backend/visualFormatContextValue_impl.hxx"
#endif
