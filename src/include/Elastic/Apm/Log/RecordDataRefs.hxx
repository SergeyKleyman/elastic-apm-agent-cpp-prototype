#pragma once

#include "Elastic/Apm/Log/Level.hxx"
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Util/ArrayView.hxx"
#include "Elastic/Apm/Log/IStreamable.hxx"
#include "Elastic/Apm/Util/SystemClockTimePoint.hxx"

namespace Elastic { namespace Apm { namespace Log
{

class RecordDataRefs
{
private:

    using StringView = Util::StringView;

    // TODO: Sergey Kleyman: Remove if not necessary
    // using SystemClockTimePoint = Util::SystemClockTimePoint;

public:

    ELASTIC_APM_NOT_MOVABLE_AND_NOT_COPYABLE( RecordDataRefs );

    struct ContextExpr
    {
        ContextExpr() = default;

        ContextExpr( StringView stringizedExpr, const IStreamable& exprValue )
                : stringizedExpr{ stringizedExpr }
                  , exprValue{ &exprValue }
        {}

        StringView stringizedExpr;
        const IStreamable* exprValue = nullptr;
    };

    explicit RecordDataRefs( ArrayView< ContextExpr > contextExprs )
        : contextExprs{ contextExprs }
    {}

    struct SourceCodeLocation
    {
        StringView filePath;
        uint32_t lineNumber = 0;
        StringView ppFqFunction;
        StringView ppFunction;
        StringView cppFunc;
        StringView fqClassName;
    };

    SystemClockTimePoint timestamp;
    Level level = Level::off;
    SourceCodeLocation sourceCodeLocation;
    const char* message = nullptr;
    ArrayView< ContextExpr > contextExprs;
};

} } } // namespace Elastic::Apm::Log
