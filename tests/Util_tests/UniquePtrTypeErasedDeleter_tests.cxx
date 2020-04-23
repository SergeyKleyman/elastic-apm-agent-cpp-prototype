#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/exception.hxx"
#include "Elastic/Apm/Impl/wrapped_3rd_party_headers/std/type_traits.hxx"
#include "TestUtil/unit_test_util.hxx"
#include "Elastic/Apm/Util/UniquePtrTypeErasedDeleter.hxx"
#include "Elastic/Apm/Impl/Util/movable_copyable.hxx"

TEST_SUITE_BEGIN( UniquePtrTypeErasedDeleter_tests ) // NOLINT(cert-err58-cpp)

using Elastic::Apm::Util::UniquePtrTypeErasedDeleter;

static_assert( std::is_nothrow_move_constructible< UniquePtrTypeErasedDeleter< int > >::value, "" );

class ClassWithThrowMoveCtor
{
public:

    ClassWithThrowMoveCtor( ClassWithThrowMoveCtor&& ) // NOLINT(hicpp-noexcept-move,performance-noexcept-move-constructor)
    {
        throw std::exception();
    }

    ELASTIC_APM_COPY_CTOR_DELETE( ClassWithThrowMoveCtor );
    ELASTIC_APM_COPY_ASSIGN_DELETE( ClassWithThrowMoveCtor );
};

static_assert( std::is_nothrow_move_constructible< UniquePtrTypeErasedDeleter< ClassWithThrowMoveCtor > >::value, "" );

TEST_CASE( reset_test ) // NOLINT(cert-err58-cpp)
{
    int i = 1;
    auto up = UniquePtrTypeErasedDeleter< int >{ std::shared_ptr< int >{ &i, /* noop deleter */ []( void * ){} } };
    UT_ASSERT_EQ( *up, 1 );
    i = 2;
    UT_ASSERT_EQ( *up, 2 );
    up.reset();
    UT_ASSERT( !up );
    UT_ASSERT( up.get() == nullptr );
}

TEST_SUITE_END() // StringView_tests // NOLINT(cert-err58-cpp)
