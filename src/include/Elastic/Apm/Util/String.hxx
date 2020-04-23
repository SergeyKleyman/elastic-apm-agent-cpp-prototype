#pragma once

#include "Elastic/Apm/Impl/Util/compilation_config.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/memory.hxx" // std::uses_allocator
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/variant.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/operators.hxx"
#include "Elastic/Apm/Util/StringView.hxx"
#include "Elastic/Apm/Util/PmrString.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"

namespace Elastic { namespace Apm { namespace Util
{

class String
        : public boost::equality_comparable< String >
          , public boost::equality_comparable< String, StringView >
          , public boost::less_than_comparable< String >
          , public boost::less_than_comparable< String, StringView >
{
public:

    ELASTIC_APM_MOVABLE_AND_COPYABLE( String );

    String() noexcept
            : _value( literalToView( "" ) )
    {}

    explicit String( PmrString str ) noexcept
            : _value{ std::move( str ) }
    {}

    static String assumeSufficientLifetime( StringView strView ) noexcept
    {
        return String{ strView };
    }

    template< std::size_t N >
    static String fromLiteral( const char (& stringLiteral)[N] )
    {
        return String::assumeSufficientLifetime( literalToView( stringLiteral ) );
    }

    static String copyOf( StringView strView, const PmrByteAllocator& allocator ) noexcept
    {
        return String{ PmrString( strView.begin(), strView.length(), allocator ) };
    }

    StringView view() const
    {
        return boost::apply_visitor( AsStringViewVisitor{}, _value );
    }

    operator StringView() const  // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
    {
        return view();
    }

    bool ownsStorage() const
    {
        return boost::apply_visitor( OwnsStorageVisitor{}, _value );
    }

    friend bool operator ==( const String& lhs, const String& rhs )
    {
        return lhs.view() == rhs.view();
    }

    friend bool operator ==( StringView lhs, const String& rhs )
    {
        return lhs == rhs.view();
    }

    friend bool operator ==( const String& lhs, StringView rhs )
    {
        return lhs.view() == rhs;
    }

    friend bool operator <( const String& lhs, const String& rhs )
    {
        return lhs.view() < rhs.view();
    }

    friend bool operator <( StringView lhs, const String& rhs )
    {
        return lhs < rhs.view();
    }

    friend bool operator <( const String& lhs, StringView rhs )
    {
        return lhs.view() < rhs;
    }

private:

    explicit String( StringView strView ) noexcept
            : _value{ strView }
    {}

    struct AsStringViewVisitor
            : public boost::static_visitor< StringView >
    {
        StringView operator ()( const boost::blank& /* blankVal */ ) const
        {
            return {};
        }

        StringView operator ()( const StringView& strView ) const
        {
            return strView;
        }

        StringView operator ()( const PmrString& str ) const
        {
            return StringView{ str };
        }
    };

    struct OwnsStorageVisitor
            : public boost::static_visitor< bool >
    {
        bool operator ()( const boost::blank& /* blankVal */ ) const
        {
            return false;
        }

        bool operator ()( const StringView& /* strView */ ) const
        {
            return false;
        }

        bool operator ()( const PmrString& /* str */ ) const
        {
            return true;
        }
    };

private:

    boost::variant< boost::blank, StringView, PmrString > _value;
};

} } } // namespace Elastic::Apm::Util

namespace std
{

template<>
struct hash< Elastic::Apm::Util::String >
{
    typedef Elastic::Apm::Util::String argument_type;
    typedef size_t result_type;

    size_t operator ()( const argument_type& str ) const noexcept
    {
        return boost::hash_value( str.view() );
    }
};

} // namespace std
