#include "Tuple.trait.h"

#include <gtest/gtest.h>
#include <utility>

using namespace tuple17;

TEST(Tuple, trait) {
    using T = Tuple<int, double, char, short, bool>;
    static_assert(is_tuple<T>);

    struct S {
        int i;
        double d;
        char c;
        short s;
        bool b;
    };
    static_assert(!is_tuple<S>);

    using P = std::pair<int, double>;
    static_assert(!is_tuple<P>);

    static_assert(!is_tuple<int>);
}
