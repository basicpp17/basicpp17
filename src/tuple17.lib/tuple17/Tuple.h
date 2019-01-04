#pragma once

#include <meta17/ConstPack.access.h> // constLast
#include <meta17/IndexPack.for.h> //
#include <meta17/Type.ops.h> // type == type
#include <meta17/TypePack.access.h> // typeAt
#include <meta17/TypePack.indexOf.h> // checkedIndexOf
#include <meta17/TypePack.ops.h> // type_pack + type_pack
#include <meta17/TypePack.wrap.h>
#include <meta17/align.h> // AlignedOffsetsFor

#include <algorithm> // std::max
#include <cinttypes> // uint8_t
#include <new> // aligned_storage
#include <utility> // std::conditional

namespace tuple17 {

using meta17::alignTypePack;
using meta17::Const;
using meta17::ConstPack;
using meta17::index;
using meta17::IndexPack;
using meta17::IndexPackFor;
using meta17::to_type_pack;
using meta17::ToTypePack;
using meta17::Type;
using meta17::type;
using meta17::UnwrapType;

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
    static constexpr auto pack = to_type_pack<Ts...>;
    static constexpr auto indices = indexPackFor(pack);
    static constexpr auto offsets = alignTypePack<0>(pack);
    using Sizes = ConstPack<sizeof(Ts)...>;
    enum : size_t {
        size = toValue(constLast(offsets, indices) + constLast(Sizes{}, indices)),
        max_align = std::max({sizeof(Ts)...}),
    };

private:
    std::aligned_storage_t<size, max_align> m;

public:
    constexpr Tuple() {
        visitIndexTypes(indices, [this](auto i, auto t) {
            using T = UnwrapType<decltype(t)>;
            new (ptrAt(i)) T();
        });
    }
    ~Tuple() {
        visitIndexTypes(indices, [this](auto i, auto t) {
            using T = UnwrapType<decltype(t)>;
            at(i).~T();
        });
    }

    constexpr Tuple(const Tuple& o) {
        visitIndexTypes(indices, [this, &o](auto i, auto t) {
            using T = UnwrapType<decltype(t)>;
            new (ptrAt(i)) T(o.at(i));
        });
    }
    constexpr auto operator=(const Tuple& o) -> Tuple& {
        visitIndexTypes(indices, [this, &o](auto i, auto) { at(i) = o.at(i); });
        return *this;
    }

    constexpr Tuple(Tuple&& o) {
        visitIndexTypes(indices, [this, &o](auto i, auto t) {
            using T = UnwrapType<decltype(t)>;
            new (ptrAt(i)) T(std::move(o).at(i));
        });
    }
    constexpr auto operator=(Tuple&& o) -> Tuple& {
        visitIndexTypes(indices, [this, &o](auto i, auto) { at(i) = std::move(o).at(i); });
        return *this;
    }

    template<
        class... Args,
        class = std::enable_if_t< //
            sizeof...(Args) == sizeof...(Ts) //
            && typeHead(to_type_pack<Args...>) != type<Tuple>>>
    constexpr Tuple(Args&&... args) {
        (new (ptrOf<Ts>()) Ts(std::forward<Args>(args)), ...);
    }

    template<class... Os>
    constexpr Tuple(const Tuple<Os...>& o) {
        static_assert((hasType<Os>() && ...), "not all types are stored here!");
        visitIndexTypes(indices, [&](auto i, auto t) {
            using T = UnwrapType<decltype(t)>;
            auto p = ptrAt(i);
            if constexpr (o.template hasType<T>()) {
                new (p) T(o.template of<T>());
            }
            else {
                new (p) T();
            }
        });
    }

    template<class T>
    static constexpr auto hasType(Type<T> = {}) -> bool {
        return ((type<Ts> == type<T>) || ...);
    }

    template<size_t I>
    static constexpr auto offsetAt(Const<I> = {}) -> size_t {
        return toValue(meta17::constAt<I>(offsets, indices));
    }
    template<size_t I>
    static constexpr auto offset_at = offsetAt<I>();

    template<class T>
    static constexpr auto offsetOf(Type<T> = {}) -> size_t {
        constexpr auto I = meta17::checkedIndexOf<T>(pack, indices);
        return offsetAt<I>();
    }
    template<class T>
    static constexpr auto offset_of = offsetOf<T>();

    template<size_t I>
    static constexpr auto typeAt(Const<I> = {}) {
        return meta17::indexedTypeAt<I>(pack, indices);
    }
    template<size_t I>
    using TypeAt = decltype(typeAt<I>());
    template<size_t I>
    static constexpr auto type_at = TypeAt<I>{};

    template<size_t I>
    using UnwrapTypeAt = UnwrapType<TypeAt<I>>;

    template<size_t I>
    constexpr auto at(Const<I> = {}) & -> UnwrapTypeAt<I>& {
        using T = UnwrapTypeAt<I>;
        return *std::launder(reinterpret_cast<T*>(ptrAt<I>()));
    }

    template<size_t I>
    constexpr auto at(Const<I> = {}) && -> UnwrapTypeAt<I> {
        using T = UnwrapTypeAt<I>;
        return std::move(*std::launder(reinterpret_cast<T*>(ptrAt<I>())));
    }

    template<size_t I>
    constexpr auto at(Const<I> = {}) const& -> const UnwrapTypeAt<I>& {
        using T = const UnwrapTypeAt<I>;
        return *std::launder(reinterpret_cast<T*>(ptrAt<I>()));
    }

    template<class T>
    constexpr auto of(Type<T> = {}) & -> T& {
        return *std::launder(reinterpret_cast<T*>(ptrOf<T>()));
    }

    template<class T>
    constexpr auto of(Type<T> = {}) && -> T {
        return std::move(*std::launder(reinterpret_cast<T*>(ptrOf<T>())));
    }

    template<class T>
    constexpr auto of(Type<T> = {}) const& -> const T& {
        return *std::launder(reinterpret_cast<const T*>(ptrOf<T>()));
    }

    template<class F>
    auto visitAll(F&& f) & {
        visitIndexTypes(indices, [this, &f](auto i, auto) { f(at(i)); });
    }
    template<class F>
    auto visitAll(F&& f) const& {
        visitIndexTypes(indices, [this, &f](auto i, auto) { f(at(i)); });
    }

private:
    template<class F, size_t... Is>
    constexpr auto visitIndexTypes(IndexPack<Is...>, F&& f) {
        (f(Const<Is>{}, typeAt<Is>()), ...);
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

} // namespace tuple17
