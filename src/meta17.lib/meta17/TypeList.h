#pragma once
#include "IndexTypePack.h"

#include "Arguments.fold.h"
#include "Const.h"
#include "Type.h"
#include "TypePack.wrap.h"

namespace meta17 {

// API wrapper for IndexTypePack
template<class T>
struct TypeList;

template<class... Ts, size_t... Is>
struct TypeList<TypePack<IndexType<Is, Ts>...>> {
    enum : size_t { count = sizeof...(Ts), npos = count };

    template<class C>
    static constexpr auto countOf(Type<C> c = {}) -> size_t {
        return ((c == Type<Ts>{} ? 1u : 0u) + ...);
    }

    template<class C>
    static constexpr bool contains(Type<C> c = {}) {
        return 0 < countOf(c);
    }

    template<class C>
    static constexpr auto indexOf(Type<C> c = {}) -> size_t {
        return 1 == countOf(c) ? ((c == Type<Ts>{} ? Is : 0u) + ...) : npos;
    }

    template<size_t I>
    static constexpr auto countIndex(Const<I> = {}) -> size_t {
        return ((Is == I ? 1u : 0u) + ...);
    }
    template<size_t I>
    static constexpr bool hasIndex(Const<I> i = {}) {
        return 0 < countIndex(i);
    }

    template<size_t I>
    static constexpr auto at(Const<I> = {})
        -> Type<UnwrapTypePack<AccumulateInstances<std::conditional_t<(Is == I), TypePack<Ts>, TypePack<>>...>>> {
        return {};
    }

    template<size_t I>
    using At = decltype(at<I>());

    template<size_t I>
    constexpr auto operator[](Const<I>) const -> decltype(at<I>()) {
        return {};
    }

    template<class F>
    static constexpr auto countIfType(F f) -> size_t {
        return ((f(Type<Ts>{}) ? 1u : 0u) + ... + 0u);
    }

    template<class F>
    static constexpr auto filterIfType(F f) //
        -> TypeList<
            AccumulateInstances<std::conditional_t<f(Type<Ts>{}), TypePack<IndexType<Is, Ts>>, TypePack<>>...>> {
        return {};
    }

    static_assert(allArguments((1 == countIndex(_const<Is>))...), "all indices have to be unique!");
};

template<>
struct TypeList<TypePack<>> {
    enum : size_t { count = 0, npos = count };

    template<class C>
    static constexpr auto countOf(Type<C> = {}) -> size_t {
        return 0;
    }

    template<class C>
    static constexpr bool contains(Type<C> = {}) {
        return false;
    }

    template<class C>
    static constexpr auto indexOf(Type<C> = {}) -> size_t {
        return npos;
    }

    template<size_t I>
    static constexpr auto countIndex(Const<I> = {}) -> size_t {
        return 0;
    }
    template<size_t I>
    static constexpr bool hasIndex(Const<I> = {}) {
        return false;
    }

    template<class F>
    static constexpr auto countIfType(F) -> size_t {
        return 0;
    }

    template<class F>
    static constexpr auto filterIfType(F) -> TypeList<TypePack<>> {
        return {};
    }
};

} // namespace meta17
