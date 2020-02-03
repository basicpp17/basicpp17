#pragma once
#include "meta17/IndexPack.h"
#include "meta17/Type.h"

#include "meta17/ConstPack.fold.h" // max(Pack)
#include "meta17/IndexPack.for.h" // indexPackFor
#include "meta17/Type.ops.h" // type == type
#include "meta17/Type.wrap.h" // UnwrapType
#include "meta17/TypePack.access.h" // indexedTypeAt
#include "meta17/TypePack.indexOf.h" // indexOf
#include "meta17/TypePack.recurse.h" // ExtractHead
#include "meta17/TypePack.wrap.h" // to_type_pack
#include "meta17/Unreachable.h" // unreachable

#include <cstdint> // uint8_t, …
#include <limits> // std::numeric_limits
#include <type_traits> // std::aligned_storage_t

namespace variant17 {

using meta17::_const;
using meta17::containsOf;
using meta17::Index;
using meta17::index_pack;
using meta17::indexedTypeAt;
using meta17::indexedTypePackIndexOf;
using meta17::IndexPack;
using meta17::indexPackFor;
using meta17::to_type_pack;
using meta17::type;
using meta17::Type;
using meta17::type_pack;
using meta17::TypeHead;
using meta17::TypePack;
using meta17::UnwrapType;

template<class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};
template<class... Ts>
Overloaded(Ts...)->Overloaded<Ts...>;

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

template<class... Ts>
struct VariantWhich {
    static constexpr auto pack = to_type_pack<Ts...>;
    static constexpr auto indices = indexPackFor(pack);
    using WhichValue = UnwrapType<SelectType<sizeof...(Ts)>>; // enough for npos!

    constexpr VariantWhich()
        : value(0) {}
    explicit constexpr VariantWhich(WhichValue v)
        : value(v) {}

    constexpr operator WhichValue() const { return value; }

    constexpr bool operator==(VariantWhich w) const { return w.value == value; }
    constexpr bool operator!=(VariantWhich w) const { return w.value != value; }

    template<class T>
    constexpr bool operator==(Type<T>) const {
        return whichOf<T>() == *this;
    }
    template<class T>
    constexpr bool operator!=(Type<T>) const {
        return whichOf<T>() != *this;
    }

    template<class T>
    constexpr static auto whichOf(Type<T> = {}) -> VariantWhich {
        return VariantWhich{static_cast<WhichValue>(indexedTypePackIndexOf<T>(pack, indices))};
    }

private:
    WhichValue value;
};

/// Variant != std::variant
/// * unchecked invalid state (only destruction is valid!)
/// * simple recursive vistor
/// * allows uncheck casts (you have to check before!)
/// * sizeof(index) limits
template<class... Ts>
struct Variant {
    using Which = VariantWhich<Ts...>;
    static constexpr auto pack = Which::pack;
    static constexpr auto indices = Which::indices;
    using First = TypeHead<decltype(pack)>;
    using WhichValue = typename Which::WhichValue;
    enum { npos = sizeof...(Ts) }; // invalid state after exception - only destruction checks!

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
        class = std::enable_if_t<(!std::is_base_of_v<Variant, BT>)>>
    Variant(T&& t) {
        static_assert(containsOf<BT>(pack), "type not part of variant");
        constructOf(type<BT>, std::forward<T>(t));
        whichValue = Which::whichOf(type<BT>);
    }

    /// inplace construct of type
    template<class T, class... Args>
    Variant(Type<T>, Args&&... args) {
        static_assert(containsOf<T>(pack), "type not part of variant");
        constructOf(type<T>, std::forward<Args>(args)...);
        whichValue = Which::whichOf(type<T>);
    }

    template<size_t I, class... Args>
    Variant(Index<I>, Args&&... args) {
        static_assert(I < npos, "index not part of variant");
        constexpr auto t = type_at<I>;
        constructOf(t, std::forward<Args>(args)...);
        whichValue = I;
    }

    /// inplace change of type
    template<size_t I, class... Args>
    void emplace(Index<I>, Args&&... args) {
        static_assert(I < npos, "index not part of variant");
        if (whichValue != npos) destruct();
        whichValue = npos;
        constexpr auto t = type_at<I>;
        constructOf(t, std::forward<Args>(args)...);
        whichValue = I;
    }

    template<class T, class... Args>
    void emplace(Type<T>, Args&&... args) {
        static_assert(containsOf<T>(pack), "type not part of variant");
        if (whichValue != npos) destruct();
        whichValue = npos;
        constructOf(type<T>, std::forward<Args>(args)...);
        whichValue = Which::whichOf(type<T>);
    }

    template<size_t I>
    using TypeAt = decltype(indexedTypeAt<I>(pack, indices));
    template<size_t I>
    constexpr static auto type_at = type<TypeAt<I>>;

    constexpr auto which() const -> Which { return Which{whichValue}; }

    template<class T>
    constexpr auto asPtr(Type<T> = {}) -> T* { // TODO(mstaff): Maybe an assert to verify that this is the current type?
        static_assert(containsOf<T>(pack), "type not part of variant");
        return std::launder(reinterpret_cast<T*>(&m));
    }
    template<class T>
    constexpr auto asPtr(Type<T> = {}) const -> const T* {
        static_assert(containsOf<T>(pack), "type not part of variant");
        return std::launder(reinterpret_cast<const T*>(&m));
    }
    template<class F>
    constexpr auto visit(F&& f) -> decltype(auto) {
        return visitImpl(*this, std::forward<F>(f));
    }
    template<class F>
    constexpr auto visit(F&& f) const -> decltype(auto) {
        return visitImpl(*this, std::forward<F>(f));
    }

    /// overloaded visitor
    template<class F, class F2, class... Fs>
    constexpr auto visit(F&& f, F2&& f2, Fs&&... fs) -> decltype(auto) {
        return visit(Overloaded{std::forward<F>(f), std::forward<F2>(f2), std::forward<Fs>(fs)...});
    }
    template<class F, class F2, class... Fs>
    constexpr auto visit(F&& f, F2&& f2, Fs&&... fs) const -> decltype(auto) {
        return visit(Overloaded{std::forward<F>(f), std::forward<F2>(f2), std::forward<Fs>(fs)...});
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
    static constexpr auto visitImpl(V&& v, F&& f) -> decltype(auto) {
        using R = std::remove_cv_t<decltype(f(v.first()))>;
        if constexpr (type<R> == type<void>)
            visitVoidImpl(std::forward<V>(v), std::forward<F>(f), indices);
        else
            return visitRecursiveImpl(std::forward<V>(v), std::forward<F>(f), pack, indices);
    }

    template<class V, class F, size_t... Is>
    static constexpr auto visitVoidImpl(V&& v, F&& f, IndexPack<Is...>) {
        return (void)((Is == v.whichValue ? (f(*v.asPtr(type<Ts>)), true) : false) || ...);
    }
    template<class V, class F, class T, class... TTs, size_t I, size_t... Is>
    static constexpr auto visitRecursiveImpl(V&& v, F&& f, TypePack<T, TTs...>, IndexPack<I, Is...>) -> decltype(auto) {
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
