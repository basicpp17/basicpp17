#include "Strong.inspect.h"

#include "Strong.base.h"
#include "Strong.opaque.h"

#include <gtest/gtest.h>

using namespace strong17;

using Type124Explicit = Strong<int, struct FirstTag, struct SecondTag, struct ForthTag>;

STRONG_OPAQUE(Type134Opaque, int, struct FirstTag, struct ThirdTag, struct ForthTag);

TEST(Strong, hasTag) {
    static_assert(hasTag(type<Type124Explicit>, type<struct FirstTag>));
    static_assert(!hasTag(type<Type124Explicit>, type<struct ThirdTag>));
}

TEST(StrongOpaque, hasTag) {
    static_assert(hasTag(type<Base<Type134Opaque>>, type<struct ThirdTag>));
    static_assert(!hasTag(type<Base<Type134Opaque>>, type<struct SecondTag>));
}

TEST(Strong, contains) {
    static_assert(contains(type<Type124Explicit>, type<struct FirstTag>));
    static_assert(!contains(type<Type124Explicit>, type<struct ThirdTag>));
}

TEST(StrongOpaque, contains) {
    static_assert(contains(type<Base<Type134Opaque>>, type<struct ThirdTag>));
    static_assert(!contains(type<Base<Type134Opaque>>, type<struct SecondTag>));
}
