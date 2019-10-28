#pragma once

#include "meta17/Const.wrap.h"
#include "meta17/ConstPack.access.h" // constLast
#include "meta17/IndexPack.for.h" // IndexPackFor
#include "meta17/Type.ops.h" // type == type
#include "meta17/TypePack.access.h" // typeAt
#include "meta17/TypePack.indexOf.h" // checkedIndexOf
#include "meta17/TypePack.ops.h" // type_pack + type_pack
#include "meta17/TypePack.wrap.h"
#include "meta17/align.h" // AlignedOffsetsFor

#if defined(_MSC_VER) && !defined(NDEBUG)
#    include "meta17/ConstPack.recurse.h" // const_head, const_tail
#    include "meta17/TypePack.recurse.h" // TypeHead, type_tail
#endif

#include <cinttypes> // uint8_t
#include <new> // aligned_storage
#include <type_traits> // std::is_reference_v / std::is_const_v
#include <utility> // std::conditional

namespace tuple17 {

using meta17::_const;
using meta17::alignTypePack;
using meta17::Const;
using meta17::const_count;
using meta17::const_head;
using meta17::const_pack;
using meta17::const_tail;
using meta17::constAt;
using meta17::index_pack;
using meta17::indexedTypeAt;
using meta17::indexedTypePackIndexOf;
using meta17::IndexPack;
using meta17::IndexPackFor;
using meta17::maxAlignOf;
using meta17::sizeofTypePack;
using meta17::to_type_pack;
using meta17::toValue;
using meta17::Type;
using meta17::type;
using meta17::type_count;
using meta17::type_pack;
using meta17::type_tail;
using meta17::TypeHead;
using meta17::UnwrapType;

template<class... Ts>
constexpr auto noReference() {
    return (!std::is_reference_v<Ts> && ... && true);
}

template<class... Ts>
constexpr auto noConst() {
    return (!std::is_const_v<Ts> && ... && true);
}

#if defined(_MSC_VER) && !defined(NDEBUG) /// Helper Types to formulate Debug Helpers / Visualizers for MSVC
template<class Hd, size_t O, class Tl>
struct DebugType {
    using Head = Hd;
    using Tail = Tl;
    constexpr static auto Offset = O;
};

template<class Types, class Offsets>
constexpr auto makeDebugTypes(Types, Offsets) {
    if constexpr (0 == type_count<Types> || 0 == const_count<Offsets>) {
        return DebugType<void, 0, void>{};
    }
    else {
        return DebugType<
            TypeHead<Types>,
            const_head<Offsets>,
            decltype(makeDebugTypes(type_tail<Types>, const_tail<Offsets>))>{};
    }
}
#endif

/** \brief storage type for all given types
 *
 * features:
 * + fast compilation (no type recursion)
 * + order is preserved
 * + compile time offsets
 * + indexed by type and compile time indices
 *
 */
template<class... Ts>
struct Tuple {
    static_assert(noReference<Ts...>());
    static_assert(noConst<Ts...>());

    static constexpr auto pack = to_type_pack<Ts...>;
    static constexpr auto indices = indexPackFor(pack);
    static constexpr auto offsets = alignTypePack(pack);
    enum : size_t {
        size = sizeofTypePack(pack),
        max_align = maxAlignOf<Ts...>(),
        npos = sizeof...(Ts),
    };

#if defined(_MSC_VER) && !defined(NDEBUG)
    using DebugTypes = decltype(makeDebugTypes(pack, offsets));
#endif

private:
    std::aligned_storage_t<(size == 0 ? 1 : size), max_align> m;

public:
    constexpr Tuple() {
        visitIndexTypes(indices, [&](auto i, auto t) {
            using T = UnwrapType<decltype(t)>;
            new (ptrAt(i)) T();
        });
    }
    ~Tuple() {
        visitIndexTypes(indices, [&](auto i, auto t) {
            using T = UnwrapType<decltype(t)>;
            at(i).~T();
        });
    }

    constexpr Tuple(const Tuple& o) {
        visitIndexTypes(indices, [&](auto i, auto t) {
            using T = UnwrapType<decltype(t)>;
            new (ptrAt(i)) T(o.at(i));
        });
    }
    constexpr auto operator=(const Tuple& o) -> Tuple& {
        visitIndexTypes(indices, [&](auto i, auto) { at(i) = o.at(i); });
        return *this;
    }

    constexpr Tuple(Tuple&& o) {
        visitIndexTypes(indices, [&](auto i, auto t) {
            using T = UnwrapType<decltype(t)>;
            new (ptrAt(i)) T(std::move(o).at(i));
        });
    }
    constexpr auto operator=(Tuple&& o) -> Tuple& {
        visitIndexTypes(indices, [&](auto i, auto) { at(i) = std::move(o).at(i); });
        return *this;
    }

    template<class... Os>
    static auto from(Os&&... os) -> Tuple {
        auto res = Tuple{};
        ((res.of(type<std::remove_const_t<std::remove_reference_t<Os>>>) = std::forward<Os>(os)), ...);
        return res;
    }

    template<class... Os>
    static auto fromTuple(const Tuple<Os...>& os) -> Tuple {
        auto res = Tuple{};
        ((res.of(type<Os>) = os.of(type<Os>)), ...);
        return res;
    }
    template<class... Os>
    static auto fromTuple(Tuple<Os...>&& os) -> Tuple {
        auto res = Tuple{};
        ((res.of(type<Os>) = std::move(os.of(type<Os>))), ...);
        return res;
    }

    constexpr Tuple(const Ts&... ts) { indexedInitialize(indices, ts...); }
    constexpr Tuple(Ts&&... ts) { indexedInitialize(indices, std::move(ts)...); }

    template<class T>
    static constexpr auto hasType(Type<T> = {}) -> bool {
        return ((type<Ts> == type<T>) || ...);
    }

    template<size_t I>
    static constexpr auto offsetAt(Const<I> = {}) -> size_t {
        return toValue(constAt<I>(offsets, indices));
    }
    template<size_t I>
    static constexpr auto offset_at = offsetAt<I>();

    template<class T>
    static constexpr auto offsetOf(Type<T> = {}) -> size_t {
        constexpr auto I = indexedTypePackIndexOf<T>(pack, indices);
        return offsetAt<I>();
    }
    template<class T>
    static constexpr auto offset_of = offsetOf<T>();

    template<size_t I>
    using TypeAt = decltype(indexedTypeAt<I>(pack, indices));
    template<size_t I>
    static constexpr auto type_at = type<TypeAt<I>>;

    template<size_t I>
    constexpr auto at(Const<I> = {}) & -> TypeAt<I>& {
        using T = TypeAt<I>;
        return *std::launder(reinterpret_cast<T*>(ptrAt<I>()));
    }

    template<size_t I>
    constexpr auto at(Const<I> = {}) && -> TypeAt<I> {
        using T = TypeAt<I>;
        return std::move(*std::launder(reinterpret_cast<T*>(ptrAt<I>())));
    }

    template<size_t I>
    constexpr auto at(Const<I> = {}) const& -> const TypeAt<I>& {
        using T = const TypeAt<I>;
        return *std::launder(reinterpret_cast<T*>(ptrAt<I>()));
    }

    template<class T>
    constexpr auto of(Type<T> = {}) & -> T& {
        static_assert(hasType(type<T>));
        return *std::launder(reinterpret_cast<T*>(ptrOf<T>()));
    }

    template<class T>
    constexpr auto of(Type<T> = {}) && -> T {
        static_assert(hasType(type<T>));
        return std::move(*std::launder(reinterpret_cast<T*>(ptrOf<T>())));
    }

    template<class T>
    constexpr auto of(Type<T> = {}) const& -> const T& {
        static_assert(hasType(type<T>));
        return *std::launder(reinterpret_cast<const T*>(ptrOf<T>()));
    }

    template<class F>
    void visitAll(F&& f) & {
        visitIndexTypes(indices, [&](auto i, auto) { f(at(i)); });
    }
    template<class F>
    void visitAll(F&& f) const& {
        visitIndexTypes(indices, [&](auto i, auto) { f(at(i)); });
    }

private:
    template<size_t... Is>
    void indexedInitialize(IndexPack<Is...>, const Ts&... ts) {
        ((new (this->ptrAt<Is>()) Ts(ts)), ...);
    }
    template<size_t... Is, class = std::enable_if_t<(sizeof...(Is) > 0)>>
    void indexedInitialize(IndexPack<Is...>, Ts&&... ts) {
        ((new (this->ptrAt<Is>()) Ts(std::move(ts))), ...);
    }

    template<class F, size_t... Is>
    constexpr void visitIndexTypes(IndexPack<Is...>, F&& f) {
        (f(_const<Is>, type_at<Is>), ...);
    }

    template<class F, size_t... Is>
    constexpr void visitIndexTypes(IndexPack<Is...>, F&& f) const {
        (f(_const<Is>, type_at<Is>), ...);
    }

    template<size_t I>
    constexpr auto ptrAt(Const<I> = {}) & -> void* {
        return reinterpret_cast<uint8_t*>(&m) + offsetAt<I>();
    }

    template<size_t I>
    constexpr auto ptrAt(Const<I> = {}) const& -> const void* {
        return reinterpret_cast<const uint8_t*>(&m) + offsetAt<I>();
    }

    template<class T>
    constexpr auto ptrOf(Type<T> = {}) & -> void* {
        return reinterpret_cast<uint8_t*>(&m) + offsetOf<T>();
    }

    template<class T>
    constexpr auto ptrOf(Type<T> = {}) const& -> const void* {
        return reinterpret_cast<const uint8_t*>(&m) + offsetOf<T>();
    }
};

template<>
struct Tuple<> {
    static constexpr auto pack = type_pack<>;
    static constexpr auto indices = index_pack<>;
    static constexpr auto offsets = const_pack<>;
    enum : size_t {
        size = 0,
        max_align = 1,
        npos = 1,
    };
    static auto from() -> Tuple { return {}; }
    static auto fromTuple(const Tuple&) -> Tuple { return {}; }

    template<class T>
    static constexpr auto hasType(Type<T> = {}) -> bool {
        return false;
    }

    template<class F>
    void visitAll(F&&) & {}

    template<class F>
    void visitAll(F&&) const& {}
};

template<size_t I, class... Ts>
auto constexpr get(Tuple<Ts...>& tuple) -> decltype(auto) {
    return tuple.at(_const<I>);
}
template<size_t I, class... Ts>
auto constexpr get(Tuple<Ts...>&& tuple) -> decltype(auto) {
    return std::move(tuple).at(_const<I>);
}
template<size_t I, class... Ts>
auto constexpr get(const Tuple<Ts...>& tuple) -> decltype(auto) {
    return tuple.at(_const<I>);
}
template<class T, class... Ts>
auto constexpr get(tuple17::Tuple<Ts...>& tuple, Type<T> = {}) -> decltype(auto) {
    return tuple.template of<T>();
}
template<class T, class... Ts>
auto constexpr get(const tuple17::Tuple<Ts...>& tuple, Type<T> = {}) -> decltype(auto) {
    return tuple.template of<T>();
}

template<class... Ts>
Tuple(Ts...)->Tuple<Ts...>;

} // namespace tuple17

/// for c++17 structured bindings support
namespace std {

template<class... Ts>
class tuple_size<tuple17::Tuple<Ts...>> : public std::integral_constant<size_t, sizeof...(Ts)> {};

template<size_t I, class... Ts>
class tuple_element<I, tuple17::Tuple<Ts...>> {
public:
    using type = typename tuple17::Tuple<Ts...>::template TypeAt<I>;
};

} // namespace std
