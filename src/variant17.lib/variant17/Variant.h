#pragma once
#include <meta17/IndexPack.h>
#include <meta17/Type.h>

#include <meta17/ConstPack.fold.h> // max(Pack)
#include <meta17/IndexPack.for.h> // IndexPackFor
#include <meta17/Type.ops.h> // type == type
#include <meta17/Type.wrap.h> // UnwrapType
#include <meta17/TypePack.access.h> // TypeAt
#include <meta17/TypePack.indexOf.h> // indexOf
#include <meta17/TypePack.recurse.h> // ExtractHead
#include <meta17/TypePack.wrap.h> // ToTypePack
#include <meta17/Unreachable.h> // unreachable

#include <cstdint> // uint8_t, …
#include <limits> // std::numeric_limits
#include <type_traits> // std::aligned_storage_t

namespace variant17 {

using meta17::checkedIndexOf;
using meta17::ConstPack;
using meta17::Index;
using meta17::index_pack;
using meta17::IndexPack;
using meta17::IndexPackFor;
using meta17::max;
using meta17::ToTypePack;
using meta17::type;
using meta17::Type;
using meta17::type_pack;
using meta17::typeAt;
using meta17::TypeHead;
using meta17::TypePack;
using meta17::UnwrapType;

template<size_t N>
auto selectType() {
    if constexpr (N <= std::numeric_limits<uint8_t>::max()) {
        return type<uint8_t>;
    }
    else if constexpr (N <= std::numeric_limits<uint16_t>::max()) {
        return type<uint16_t>;
    }
    else if constexpr (N <= std::numeric_limits<uint32_t>::max()) {
        return type<uint32_t>;
    }
    else if constexpr (N <= std::numeric_limits<uint64_t>::max()) {
        return type<uint64_t>;
    }
}
template<size_t N>
using SelectType = UnwrapType<decltype(selectType<N>())>;

/// Variant != std::variant
/// * unchecked invalid state (only destruction is valid!)
/// * simple recursive vistor
/// * allows uncheck casts (you have to check before!)
/// * sizeof(index) limits
template<class... Ts>
struct Variant {
    using Pack = ToTypePack<Ts...>;
    using Indices = IndexPackFor<Pack>;
    using First = UnwrapType<TypeHead<Pack>>;
    using WhichValue = UnwrapType<SelectType<sizeof...(Ts)>>; // enough for npos!
    enum { npos = sizeof...(Ts) }; // invalid state after exception - only destruction checks!

    struct Which {
        explicit constexpr Which(WhichValue v)
            : value(v) {}

        operator WhichValue() const { return value; }

        constexpr bool operator==(Which w) const { return w.value == value; }
        constexpr bool operator!=(Which w) const { return w.value != value; }

        template<class T>
        constexpr bool operator==(Type<T>) const {
            return whichOf<T>() == *this;
        }
        template<class T>
        constexpr bool operator!=(Type<T>) const {
            return whichOf<T>() != *this;
        }

    private:
        WhichValue value;
    };

private:
    std::aligned_union_t<0, Ts...> m{};
    WhichValue whichValue{npos};

public:
    constexpr Variant() {
        constructOf(type<First>);
        whichValue = 0;
    }
    ~Variant() {
        if (whichValue != npos) destruct();
    }

    // copy
    constexpr Variant(const Variant& o) {
        o.visit([&](auto& v) {
            using V = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
            constructOf(type<V>, v);
        });
        whichValue = o.whichValue;
    }
    constexpr auto operator=(const Variant& o) -> Variant& {
        if (o.whichValue == whichValue) {
            o.visit([&](auto& v) {
                using V = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
                *asPtr(type<V>) = v;
            });
        }
        else {
            destruct();
            whichValue = npos;
            o.visit([&](auto& v) {
                using V = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
                constructOf(type<V>, v);
            });
            whichValue = o.whichValue;
        }
        return *this;
    }

    // move
    constexpr Variant(Variant&& o) {
        o.visit([&](auto&& v) {
            using V = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
            constructOf(type<V>, std::move(v));
        });
        whichValue = o.whichValue;
        o.whichValue = npos;
    }
    constexpr auto operator=(Variant&& o) -> Variant& {
        if (o.whichValue == whichValue) {
            o.visit([&](auto&& v) {
                using V = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
                *asPtr(type<V>) = std::move(v);
            });
        }
        else {
            destruct();
            whichValue = npos;
            o.visit([&](auto&& v) {
                using V = std::remove_cv_t<std::remove_reference_t<decltype(v)>>;
                constructOf(type<V>, std::move(v));
            });
            whichValue = o.whichValue;
            o.whichValue = npos;
        }
        return *this;
    }

    /// construct from move/copy
    template<
        class T,
        class BT = std::remove_cv_t<std::remove_reference_t<T>>,
        class = std::enable_if_t<type<BT> != type<Variant>>>
    Variant(T&& t) {
        constructOf(type<BT>, std::forward<T>(t));
        whichValue = whichOf<BT>();
    }

    /// inplace construct of type
    template<class T, class... Args>
    Variant(Type<T>, Args&&... args) {
        constructOf(type<T>, std::forward<Args>(args)...);
        whichValue = whichOf<T>();
    }

    template<size_t I, class... Args>
    Variant(Index<I>, Args&&... args) {
        constexpr auto t = typeAt<I>(Pack{}, Indices{});
        constructOf(t, std::forward<Args>(args)...);
        whichValue = I;
    }

    template<class T>
    constexpr static auto whichOf(Type<T> = {}) -> Which {
        return Which{static_cast<WhichValue>(meta17::checkedIndexOf<T>(Pack{}, Indices{}))};
    }

    constexpr auto which() const -> Which { return Which{whichValue}; }

    template<class T>
    constexpr auto asPtr(Type<T> = {}) -> T* { // TODO(mstaff): Maybe an assert to verify that this is the current type?
        return std::launder(reinterpret_cast<T*>(&m));
    }
    template<class T>
    constexpr auto asPtr(Type<T> = {}) const -> const T* {
        return std::launder(reinterpret_cast<const T*>(&m));
    }
    template<class F>
    constexpr auto visit(F&& f) {
        return visitImpl(*this, std::forward<F>(f));
    }
    template<class F>
    constexpr auto visit(F&& f) const {
        return visitImpl(*this, std::forward<F>(f));
    }

private:
    template<class T, class... Args>
    constexpr auto constructOf(Type<T>, Args&&... args) {
        new (&m) T(std::forward<Args>(args)...);
    }
    constexpr auto destruct() {
        visit([](auto& v) {
            using T = std::remove_reference_t<decltype(v)>;
            v.~T();
        });
    }

    template<class V, class F>
    static constexpr auto visitImpl(V&& v, F&& f) {
        using R = std::remove_cv_t<decltype(f(v.first()))>;
        if constexpr (type<R> == type<void>)
            visitVoidImpl(std::forward<V>(v), std::forward<F>(f), Indices{});
        else
            return visitRecursiveImpl(std::forward<V>(v), std::forward<F>(f), Pack{}, Indices{});
    }

    template<class V, class F, size_t... Is>
    static constexpr auto visitVoidImpl(V&& v, F&& f, IndexPack<Is...>) {
        return (void)((Is == v.whichValue ? (f(*v.asPtr(type<Ts>)), true) : false) || ...);
    }
    template<class V, class F, class T, class... TTs, size_t I, size_t... Is>
    static constexpr auto visitRecursiveImpl(V&& v, F&& f, TypePack<T, TTs...>, IndexPack<I, Is...>) {
        if (I == v.whichValue) {
            return f(*v.asPtr(type<T>));
        }
        if constexpr (0 != sizeof...(TTs)) {
            return visitRecursiveImpl(std::forward<V>(v), std::forward<F>(f), type_pack<TTs...>, index_pack<Is...>);
        }
        else {
            UNREACHABLE();
        }
    }

    auto first() -> First&;
    auto first() const -> const First&;
};

} // namespace variant17
