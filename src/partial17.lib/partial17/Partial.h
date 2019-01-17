#pragma once
#include <meta17/Index.h>
#include <meta17/Type.h>

#include <meta17/Index.wrap.h> // ToTypePack
#include <meta17/IndexPack.for.h> // IndexPackFor
#include <meta17/Type.wrap.h> // ToTypePack
#include <meta17/TypePack.access.h> // TypeAt
#include <meta17/TypePack.wrap.h> // ToTypePack
#include <meta17/align.h>

#include <algorithm> // std::max
#include <bitset>
#include <memory> // std::unique_ptr
#include <utility> // std::launder

namespace some_of17 {

using meta17::alignOffset;
using meta17::Const;
using meta17::index;
using meta17::Index;
using meta17::index_pack;
using meta17::IndexPack;
using meta17::IndexPackFor;
using meta17::ToTypePack;
using meta17::type;
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
    using Pack = ToTypePack<Ts...>;
    using Indices = IndexPackFor<Pack>;
    enum {
        max_count = sizeof...(Ts),
        max_align = std::max({alignof(Ts)...}),
    };

private:
    std::bitset<max_count> m_bits{};
    std::unique_ptr<uint8_t[]> m_data{};

public:
    constexpr Partial() = default;
    ~Partial() { destructAll(); }

    // copy - TODO
    Partial(const Partial& o) {
        auto hasValue = [&](auto i) { return o.has(i); };
        auto factory = [&](auto i) { return o.get(i); };
        *this = fromFactory(hasValue, factory);
    }
    auto operator=(const Partial& o) -> Partial& {
        destructAll();
        m_bits.reset();
        auto hasValue = [&](auto i) { return o.has(i); };
        auto factory = [&](auto i) { return o.get(i); };
        *this = fromFactory(hasValue, factory);
        return *this;
    }

    // move
    Partial(Partial&& o) noexcept
        : m_bits(o.m_bits)
        , m_data(std::move(o.m_data)) {
        o.m_bits.reset();
    }
    auto operator=(Partial&& o) noexcept -> Partial& {
        destructAll();
        m_bits = o.m_bits;
        m_data = std::move(o.m_data);
        o.m_bits.reset();
        return *this;
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
            Indices{});
        auto ptr = new uint8_t[size + max_align - 1];
        r.m_data.reset(ptr);
        ptr = alignPointer<max_align>(ptr);
        visitIndexTypes(
            [&](auto i, auto t) {
                constexpr auto iv = toValue(i);
                using T = UnwrapType<decltype(t)>;
                if (hasValue(iv)) {
                    ptr = alignPointer<alignof(T)>(ptr);
                    new (ptr) T(factory(index<iv>));
                    r.m_bits.set(iv);
                    ptr += sizeof(T);
                }
            },
            Indices{});

        return r;
    }

    auto data() const { return alignPointer<max_align>(m_data.get()); }

    auto count() const {
        auto acc = size_t{};
        visitAll([&](auto&) { acc++; });
        return acc;
    }

    auto size() const {
        auto acc = size_t{};
        visitAll([&](auto& v) {
            using T = decltype(v);
            acc = alignOffset<alignof(T)>(acc) + sizeof(v);
        });
        return acc;
    }

    template<size_t I>
    auto has(Index<I> = {}) const {
        return m_bits[I];
    }
    auto has(size_t i) const { return m_bits[i]; }

    template<size_t I>
    auto get(Index<I> = {}) -> UnwrapType<TypeAt<Index<I>, Pack>>& {
        using T = UnwrapType<TypeAt<Index<I>, Pack>>;
        return *std::launder(reinterpret_cast<T*>(alignPointer<max_align>(m_data.get()) + offsetAt<I>()));
    }
    template<size_t I>
    auto get(Index<I> = {}) const -> const UnwrapType<TypeAt<Index<I>, Pack>>& {
        using T = UnwrapType<TypeAt<Index<I>, Pack>>;
        return *std::launder(reinterpret_cast<const T*>(alignPointer<max_align>(m_data.get()) + offsetAt<I>()));
    }

    template<class F>
    auto visitAll(F&& f) {
        visitInitialized(std::forward<F>(f), m_data.get());
    }
    template<class F>
    auto visitAll(F&& f) const {
        visitInitialized(std::forward<F>(f), m_data.get());
    }

    [[nodiscard]] auto merge(const Partial& o) const -> Partial {
        auto hasValue = [&](auto i) { return has(i) || o.has(i); };
        auto factory = [&](auto i) { return o.has(i) ? o.get(i) : get(i); };
        return fromFactory(hasValue, factory);
    }

private:
    void destructAll() {
        visitAll([](auto& v) {
            using T = std::remove_reference_t<decltype(v)>;
            v.~T();
        });
    }

    template<size_t I>
    auto offsetAt(Index<I> = {}) const {
        auto offset = size_t{};
        visitIndexTypes(
            [&](auto index, auto type) {
                if (has(index)) {
                    using T = UnwrapType<decltype(type)>;
                    if (index <= I) offset = alignOffset<alignof(T)>(offset);
                    if (index < I) offset += sizeof(T);
                }
            },
            Indices{});
        return offset;
    }

    template<class F, class Ptr>
    auto visitInitialized(F&& f, Ptr* ptr) const {
        ptr = alignPointer<max_align>(ptr);
        visitIndexTypes(
            [&](auto index, auto type) {
                if (has(index)) {
                    using T = UnwrapType<decltype(type)>;
                    ptr = alignPointer<alignof(T)>(ptr);
                    f(*std::launder(reinterpret_cast<T*>(ptr)));
                    ptr += sizeof(T);
                }
            },
            Indices{});
    }

    template<class F, size_t... Is>
    constexpr static auto visitIndexTypes(F&& f, IndexPack<Is...>) {
        (f(index<Is>, type<Ts>), ...);
    }
};

} // namespace some_of17
