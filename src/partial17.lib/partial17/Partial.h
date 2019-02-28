#pragma once
#include <meta17/Index.h>
#include <meta17/Type.h>

#include <meta17/Index.wrap.h> // ToTypePack
#include <meta17/IndexPack.for.h> // IndexPackFor
#include <meta17/Type.wrap.h> // ToTypePack
#include <meta17/TypePack.access.h> // TypeAt
#include <meta17/TypePack.indexOf.h> // index_of, contains_of
#include <meta17/TypePack.wrap.h> // ToTypePack
#include <meta17/align.h> // sizeOfTypePack, alignOffset

#include <algorithm> // std::max
#include <bitset>
#include <memory> // std::unique_ptr
#include <type_traits> // std::remove_reference_t, std::remove_const_t
#include <utility> // std::launder

namespace partial17 {

using meta17::alignOffset;
using meta17::checkedIndexOf;
using meta17::Const;
using meta17::contains_of;
using meta17::index;
using meta17::Index;
using meta17::index_of;
using meta17::index_pack;
using meta17::IndexPack;
using meta17::IndexPackFor;
using meta17::maxAlignOf;
using meta17::sizeOfTypePack;
using meta17::to_type_pack;
using meta17::ToTypePack;
using meta17::type;
using meta17::Type;
using meta17::type_pack;
using meta17::TypeAt;
using meta17::TypePack;
using meta17::UnwrapType;

template<size_t Align, class Ptr>
constexpr auto alignPointer(Ptr* ptr, Const<Align> = {}) -> Ptr* {
    auto offset = reinterpret_cast<intptr_t>(ptr);
    return reinterpret_cast<Ptr*>(alignOffset<Align>(offset));
}

template<class... Ts>
struct Partial {
    static constexpr auto pack = to_type_pack<Ts...>;
    static constexpr auto indices = indexPackFor(pack);
    using Pack = ToTypePack<Ts...>;
    enum {
        max_count = sizeof...(Ts),
        max_align = maxAlignOf<Ts...>(),
    };
    using WhichBits = std::bitset<max_count>;

    struct Which {
        constexpr explicit Which(WhichBits b)
            : bits(b) {}

        constexpr operator WhichBits() const { return bits; }

        constexpr bool operator==(const Which& o) const { return bits == o.bits; }
        constexpr bool operator!=(const Which& o) const { return bits != o.bits; }

        constexpr auto count() const { return bits.count(); }

        template<size_t I>
        constexpr auto at(Index<I> = {}) const {
            return bits[I];
        }
        constexpr auto at(size_t i) const { return bits[i]; }

        template<class T>
        constexpr auto of(Type<T> = {}) const {
            constexpr size_t index = checkedIndexOf<T>(pack, indices);
            return at<index>();
        }

    private:
        WhichBits bits;
    };

private:
    WhichBits whichBits{};
    std::unique_ptr<uint8_t[]> pointer{};

public:
    // Debugging helpers
    static constexpr size_t alignments[max_count] = {alignof(Ts)...};
    static constexpr size_t sizes[max_count] = {sizeof(Ts)...};

public:
    constexpr Partial() = default;
    ~Partial() {
        destructAll();

        // force compiler to include these arrays in debug build
        auto foo = alignments[0];
        auto bar = sizes[0];
    }

    // copy
    Partial(const Partial& o) {
        auto hasValue = [&](auto i) { return o.which().at(i); };
        auto factory = [&](auto i) { return o.at(i); };
        *this = fromFactory(hasValue, factory);
    }
    auto operator=(const Partial& o) -> Partial& {
        destructAll();
        whichBits.reset();
        auto hasValue = [&](auto i) { return o.which().at(i); };
        auto factory = [&](auto i) { return o.at(i); };
        *this = fromFactory(hasValue, factory);
        return *this;
    }

    // move
    Partial(Partial&& o) noexcept
        : whichBits(o.whichBits)
        , pointer(std::move(o.pointer)) {
        o.whichBits.reset();
    }
    auto operator=(Partial&& o) noexcept -> Partial& {
        destructAll();
        whichBits = o.whichBits;
        pointer = std::move(o.pointer);
        o.whichBits.reset();
        return *this;
    }

    // construct
    template<
        class... Vs,
        class = std::enable_if_t<
            (sizeof...(Vs) > 0) && (contains_of<std::remove_cv_t<std::remove_reference_t<Vs>>, Pack> && ...)>>
    Partial(Vs&&... vs) {
        auto size = sizeOfTypePack<0>(type_pack<std::remove_cv_t<std::remove_reference_t<Vs>>...>);
        auto ptr = new uint8_t[size + max_align - 1];
        pointer.reset(ptr);
        ptr = alignPointer<max_align>(ptr);

        auto make = [&](auto t, auto&& v) {
            using V = decltype(v);
            using T = std::remove_cv_t<std::remove_reference_t<V>>;
            if constexpr (t == type<T>) {
                auto iv = index_of<T, Pack>;
                ptr = alignPointer<alignof(T)>(ptr);
                new (ptr) T(std::forward<V>(v));
                whichBits.set(iv);
                ptr += sizeof(T);
            }
        };
        auto invoke = [&](auto t) { (make(t, std::forward<Vs>(vs)), ...); };
        (invoke(type<Ts>), ...);
    }

    template<class HasValue, class Factory>
    static auto fromFactory(HasValue&& hasValue, Factory&& factory) {
        auto r = Partial{};
        auto size = size_t{};
        visitIndexTypes(
            [&](auto i, auto t) {
                constexpr auto iv = toValue(i);
                using T = UnwrapType<decltype(t)>;
                if (hasValue(iv)) {
                    size = alignOffset<alignof(T)>(size) + sizeof(T);
                }
            },
            indices);
        auto ptr = new uint8_t[size + max_align - 1];
        r.pointer.reset(ptr);
        ptr = alignPointer<max_align>(ptr);
        visitIndexTypes(
            [&](auto i, auto t) {
                constexpr auto iv = toValue(i);
                using T = UnwrapType<decltype(t)>;
                if (hasValue(iv)) {
                    ptr = alignPointer<alignof(T)>(ptr);
                    new (ptr) T(factory(index<iv>));
                    r.whichBits.set(iv);
                    ptr += sizeof(T);
                }
            },
            indices);

        return r;
    }

    template<class... Ws>
    constexpr static auto whichOf(TypePack<Ws...> = {}) -> Which {
        auto bits = WhichBits{};
        (bits.set(meta17::checkedIndexOf<Ws>(pack, indices)), ...);
        return Which{bits};
    }

    constexpr auto which() const -> Which { return Which{whichBits}; }

    auto countAll() const { return whichBits.size(); }

    auto size() const {
        auto acc = size_t{};
        visitInitialized([&](auto& v) {
            using T = decltype(v);
            acc = alignOffset<alignof(T)>(acc) + sizeof(v);
        });
        return acc;
    }

    template<size_t I>
    auto at(Index<I> = {}) -> UnwrapType<TypeAt<Index<I>, Pack>>& {
        using T = UnwrapType<TypeAt<Index<I>, Pack>>;
        return *std::launder(reinterpret_cast<T*>(alignPointer<max_align>(pointer.get()) + offsetAt<I>()));
    }
    template<size_t I>
    auto at(Index<I> = {}) const -> const UnwrapType<TypeAt<Index<I>, Pack>>& {
        using T = UnwrapType<TypeAt<Index<I>, Pack>>;
        return *std::launder(reinterpret_cast<const T*>(alignPointer<max_align>(pointer.get()) + offsetAt<I>()));
    }

    template<class T>
    auto of(Type<T> = {}) const -> decltype(auto) {
        constexpr size_t index = checkedIndexOf<T>(pack, indices);
        return at<index>();
    }

    template<class F>
    auto visitInitialized(F&& f) {
        visitInitializedInternal(std::forward<F>(f), pointer.get());
    }
    template<class F>
    auto visitInitialized(F&& f) const {
        visitInitializedInternal(std::forward<F>(f), pointer.get());
    }

    template<class F>
    auto visitAll(F&& f) {
        visitIndexTypes(std::forward<F>(f), indices);
    }
    template<class F>
    auto visitAll(F&& f) const {
        visitIndexTypes(std::forward<F>(f), indices);
    }

    template<class F, class Ptr>
    auto visitInitializedIndexTypes(F&& f) const {
        visitIndexTypes(
            [&](auto index, auto type) {
                if (which().at(index)) {
                    f(index, type);
                }
            },
            indices);
    }

    [[nodiscard]] auto merge(const Partial& o) const -> Partial {
        auto hasValue = [&](auto i) { return which().at(i) || o.which().at(i); };
        auto factory = [&](auto i) { return o.which().at(i) ? o.at(i) : at(i); };
        return fromFactory(hasValue, factory);
    }

private:
    void destructAll() {
        visitInitialized([](auto& v) {
            using T = std::remove_reference_t<decltype(v)>;
            v.~T();
        });
    }

    template<size_t I>
    auto offsetAt(Index<I> = {}) const {
        auto offset = size_t{};
        visitIndexTypes(
            [&](auto index, auto type) {
                if (which().at(index)) {
                    using T = UnwrapType<decltype(type)>;
                    if (index <= I) offset = alignOffset<alignof(T)>(offset);
                    if (index < I) offset += sizeof(T);
                }
            },
            indices);
        return offset;
    }

    template<class F, class Ptr>
    auto visitInitializedInternal(F&& f, Ptr* ptr) const {
        ptr = alignPointer<max_align>(ptr);
        visitIndexTypes(
            [&](auto index, auto type) {
                if (which().at(index)) {
                    using T = UnwrapType<decltype(type)>;
                    ptr = alignPointer<alignof(T)>(ptr);
                    f(*std::launder(reinterpret_cast<T*>(ptr)));
                    ptr += sizeof(T);
                }
            },
            indices);
    }

    template<class F, size_t... Is>
    constexpr static auto visitIndexTypes(F&& f, IndexPack<Is...>) {
        (f(index<Is>, type<Ts>), ...);
    }
};

} // namespace partial17
