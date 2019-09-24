#include "Tuple.h"

#include "Tuple.make.h"
#include "Tuple.ops.h"

#include <meta17/Type.ops.h>

#include <gtest/gtest.h>

using namespace tuple17;
using meta17::Index;

namespace {
template<typename Type>
constexpr std::size_t alignment(std::size_t offset = 0, std::size_t current = 0) {
    return current >= offset ? current : alignment<Type>(offset, current + alignof(Type));
}
} // namespace

TEST(Tuple, basic) {
    using T = Tuple<char, int, double>;

    const auto offset0 = alignment<char>();
    const auto offset1 = alignment<int>(offset0 + sizeof(char));
    const auto offset2 = alignment<double>(offset1 + sizeof(int));
    const auto offsetT = alignment<T>(offset2 + sizeof(double));

    static_assert(T::offset_at<0> == offset0);
    static_assert(T::offset_at<1> == offset1);
    static_assert(T::offset_at<2> == offset2);

    static_assert(T::offset_of<char> == offset0);
    static_assert(T::offset_of<int> == offset1);
    static_assert(T::offset_of<double> == offset2);

    static_assert(T::type_at<0> == type<char>);
    static_assert(T::type_at<1> == type<int>);
    static_assert(T::type_at<2> == type<double>);

    static_assert(T::hasType<char>());
    static_assert(T::hasType<int>());
    static_assert(T::hasType<double>());
    static_assert(!T::hasType<float>());
    static_assert(!T::hasType<bool>());
    static_assert(!T::hasType<unsigned int>());

    static_assert(T::type_at<0> == type<char>);
    static_assert(T::type_at<1> == type<int>);
    static_assert(T::type_at<2> == type<double>);
    static_assert(T::type_at<1> != type<unsigned int>);
    static_assert(T::type_at<2> != type<float>);

    static_assert(sizeof(T) == offsetT);

    static_assert(std::tuple_size<T>::value == 3);
    static_assert(type<std::tuple_element<0, T>::type> == type<char>);
    static_assert(type<std::tuple_element<1, T>::type> == type<int>);
    static_assert(type<std::tuple_element<2, T>::type> == type<double>);
}

TEST(Tuple, bool) {
    using T = Tuple<bool, int>;

    const auto offset0 = alignment<bool>();
    const auto offset1 = alignment<int>(offset0 + sizeof(bool));
    const auto offsetT = alignment<T>(offset1 + sizeof(int));

    static_assert(T::offset_at<0> == offset0);
    static_assert(T::offset_at<1> == offset1);

    // Access by type does not work because bool and int are not distinguishable
    // static_assert(T::offset_of<bool> == offset0);
    // static_assert(T::offset_of<int> == offset1);

    static_assert(T::type_at<0> == type<bool>);
    static_assert(T::type_at<1> == type<int>);

    static_assert(T::hasType<bool>());
    static_assert(T::hasType<int>());

    static_assert(T::type_at<0> == type<bool>);
    static_assert(T::type_at<1> == type<int>);

    static_assert(sizeof(T) == offsetT);

    static_assert(std::tuple_size<T>::value == 2);
    static_assert(type<std::tuple_element<0, T>::type> == type<bool>);
    static_assert(type<std::tuple_element<1, T>::type> == type<int>);
}

TEST(Tuple, complex) {
    struct Inner {
        double d;
        int i;
        char c;
    };

    using T = Tuple<Inner, char, Inner>;

    const auto offset0 = alignment<Inner>();
    const auto offset1 = alignment<char>(offset0 + sizeof(Inner));
    const auto offset2 = alignment<Inner>(offset1 + sizeof(char));
    const auto offsetT = alignment<T>(offset2 + sizeof(Inner));

    static_assert(T::offset_at<0> == offset0);
    static_assert(T::offset_at<1> == offset1);
    static_assert(T::offset_at<2> == offset2);

    // Access by type does not work for Inner because types used multiple times
    // static_assert(T::offset_of<Inner> == offset0);
    static_assert(T::offset_of<char> == offset1);
    // static_assert(T::offset_of<Inner> == offset2);

    static_assert(T::type_at<0> == type<Inner>);
    static_assert(T::type_at<1> == type<char>);
    static_assert(T::type_at<2> == type<Inner>);

    static_assert(T::hasType<Inner>());
    static_assert(T::hasType<char>());

    static_assert(T::type_at<0> == type<Inner>);
    static_assert(T::type_at<1> == type<char>);
    static_assert(T::type_at<2> == type<Inner>);

    auto t = T{};
    static_assert(sizeof(t) == offsetT);

    static_assert(std::tuple_size<T>::value == 3);
    static_assert(type<std::tuple_element<0, T>::type> == type<Inner>);
    static_assert(type<std::tuple_element<1, T>::type> == type<char>);
    static_assert(type<std::tuple_element<2, T>::type> == type<Inner>);
}

TEST(Tuple, access) {
    using meta17::index;
    using T = Tuple<char, int, double>;
    auto t = T{};

    t.at(index<1>) = 23;
    t.of<double>() = 4.2;
    EXPECT_EQ((t.of(type<int>)), 23);
    EXPECT_EQ((t.at(index<2>)), 4.2);

    EXPECT_EQ(get<char>(t), '\0');
    EXPECT_EQ(get<int>(t), 23);
    EXPECT_EQ(get<double>(t), 4.2);
}

TEST(Tuple, empty) {
    using T = Tuple<>;
    auto t = T{};
}

TEST(Tuple, construction) {
    using MultiArg = Tuple<char, int, double>;
    auto m0 = MultiArg{};
    auto m1 = m0; // copy
    auto m2 = std::move(m1); // move copy

    EXPECT_EQ(m0, m2);

    using SingleArg = Tuple<int>;

    SingleArg s0{23};
    SingleArg s1(s0); // Test that it won't use the argument forward constructor

    EXPECT_EQ(s0, s1);

    using Ambiguous = Tuple<char, int, int>;
    auto a0 = Ambiguous{};
    // TODO CK: Tuple is sorted, should accept only sorted list
    // Cannot assign due to ambiguous type index association int int
    // auto a1 = Ambiguous{'c'};
    // auto a2 = Ambiguous{'c', 23};
    // auto a3 = Ambiguous{'c', 23, 32};
}

TEST(Tuple, fromTuple) {
    using Small = Tuple<char, int, double>;
    using Large = Tuple<int, double, char, float>;
    auto s = Small{'c', 23, 4.2};
    auto l = Large::fromTuple(s);

    EXPECT_EQ((l.of<char>()), 'c');
    EXPECT_EQ((l.of<double>()), 4.2);
    EXPECT_EQ((l.of<int>()), 23);
    EXPECT_EQ((l.of<float>()), 0);
}

TEST(Tuple, shrink) {
    // Shrinking is not allowed since not all parts can be assigned - code should not compile!
    /*
     * using Large = Tuple<char, int, double, float>;
     * auto l = Large{'c', 23, 4.2, 2.4};
     * using Small = MakeTuple<TypePack<int, double, char>>; // other order / bigger
     * auto s = Small(l);
     */
}

TEST(Tuple, structuredBinding) {
    using T = Tuple<char, int>;
    auto v = T{'c', 23};
    auto& [a, b] = v;

    static_assert(type<decltype(a)> == type<char>);
    static_assert(type<decltype(b)> == type<int>);

    EXPECT_EQ(a, 'c');
    EXPECT_EQ(b, 23);
}

TEST(Tuple, constStructuredBinding) {
    using T = Tuple<char, int>;
    const auto v = T{'c', 23};
    auto& [a, b] = v;

    static_assert(type<decltype(a)> == type<const char>);
    static_assert(type<decltype(b)> == type<const int>);

    EXPECT_EQ(a, 'c');
    EXPECT_EQ(b, 23);
}
