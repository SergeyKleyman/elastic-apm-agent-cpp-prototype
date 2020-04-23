#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/utility.hxx" // std::move
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx" // std::is_nothrow_move_constructible
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/boost/type_traits.hxx" // boost::enable_if_t
#include "Elastic/Apm/Impl/Util/Cpp_features_detection.hxx" // ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"

namespace Elastic { namespace Apm { namespace Impl { namespace Util
{

template< typename T, template< typename > class WrappedSmartPtr >
class UniquePtrWrapper
{
public:

    static_assert( std::is_nothrow_move_constructible< WrappedSmartPtr< T > >::value, "" );
    ELASTIC_APM_MOVABLE_BUT_NOT_COPYABLE( UniquePtrWrapper, noexcept );

    explicit UniquePtrWrapper( WrappedSmartPtr< T >&& ptr ) noexcept
            : _ptr{ std::move( ptr ) }
    {}

    UniquePtrWrapper() = default;

    template< typename U, template< typename > class SomeWrappedSmartPtr >
    friend
    class UniquePtrWrapper;

    #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
    #   pragma clang diagnostic push
    #   pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
    #endif

    template< typename U, boost::enable_if_t< std::is_convertible< WrappedSmartPtr< U >, WrappedSmartPtr< T > >::value, int > = 0 >
    UniquePtrWrapper( UniquePtrWrapper< U, WrappedSmartPtr >&& rhs ) noexcept // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
            : _ptr{ std::move( rhs._ptr ) }
    {}

    #if ELASTIC_APM_HAS_PRAGMA_CLANG == 1
    #   pragma clang diagnostic pop
    #endif

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    T* get() const noexcept
    {
        return _ptr.get();
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    T* operator ->() const noexcept
    {
        return get();
    }

    ELASTIC_APM_CPP_NODISCARD_ATTRIBUTE
    typename std::add_lvalue_reference< T >::type operator *() const noexcept
    {
        return *_ptr;
    }

    void reset() noexcept
    {
        _ptr.reset();
    }

    T* release() noexcept
    {
        return _ptr.release();
    }

    explicit operator bool() const noexcept
    {
        return static_cast< bool >( _ptr );
    }

private:

    WrappedSmartPtr< T > _ptr;
};

} } } } // namespace
