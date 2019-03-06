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

TEST(Strong, hasType) {
    static_assert(!hasType(type<Type124Explicit>, type<struct FirstTag>));
    static_assert(!hasType(type<Type124Explicit>, type<struct ThirdTag>));
    static_assert(hasType(type<Type124Explicit>, type<int>));
    static_assert(!hasType(type<Type124Explicit>, type<float>));
}

TEST(StrongOpaque, hasType) {
    static_assert(!hasType(type<Base<Type134Opaque>>, type<struct ThirdTag>));
    static_assert(!hasType(type<Base<Type134Opaque>>, type<struct SecondTag>));
    static_assert(hasType(type<Base<Type134Opaque>>, type<int>));
    static_assert(!hasType(type<Base<Type134Opaque>>, type<float>));
}
