#include "Variant.trait.h"

#include <gtest/gtest.h>
#include <utility>

using namespace variant17;

TEST(Variant, trait) {
    using T = Variant<int, double, char, short, bool>;
    static_assert(is_variant<T>);
    static_assert(!is_variant_which<T>);

    static_assert(!is_variant<T::Which>);
    static_assert(is_variant_which<T::Which>);

    struct S {
        int i;
    };
    static_assert(!is_variant<S>);
    static_assert(!is_variant_which<S>);

    using P = std::pair<int, double>;
    static_assert(!is_variant<P>);
    static_assert(!is_variant_which<P>);

    static_assert(!is_variant<int>);
    static_assert(!is_variant_which<int>);
}
