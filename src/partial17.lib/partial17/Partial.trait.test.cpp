#include "Partial.trait.h"

#include <gtest/gtest.h>
#include <utility>

using namespace partial17;

TEST(Partial, trait) {
    using T = Partial<int, double, char, short, bool>;
    static_assert(is_partial<T>);

    struct S {
        int i;
    };
    static_assert(!is_partial<S>);

    using P = std::pair<int, double>;
    static_assert(!is_partial<P>);

    static_assert(!is_partial<int>);
}
