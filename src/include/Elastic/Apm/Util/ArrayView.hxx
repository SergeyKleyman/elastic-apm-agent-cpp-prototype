#pragma once

#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/cstddef.hxx" // std::size_t

namespace Elastic { namespace Apm { namespace Util
{

template< typename T >
class ArrayView
{
public:

    ArrayView()
            : _begin{ nullptr }
              , _size{ 0 }
    {}

    ArrayView( T* begin, std::size_t size )
            : _begin{ begin }
              , _size{ size }
    {}

    template < std::size_t N >
    ArrayView( T (& staticArray )[ N ] ) // NOLINT(google-explicit-constructor,hicpp-explicit-conversions)
            : ArrayView{ &(staticArray[ 0 ]), N }
    {}

    T* begin() const
    {
        return _begin;
    }

    T* end() const
    {
        return _begin + _size;
    }

    std::size_t size() const
    {
        return _size;
    }

private:

    T* _begin;
    std::size_t _size;
};

} } } // namespace Elastic::Apm::Util
