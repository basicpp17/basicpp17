#pragma once
#include "Bool.h"

namespace meta17 {

template<class F>
struct DeferStaticError : F, False {
    using F::operator();
};
template<class F>
DeferStaticError(F &&)->DeferStaticError<F>;

struct DeferSuccess : True {
    constexpr auto operator()() const { return true; }
};

#define META17_DEFER_STATIC_ERROR(error)                                                                               \
    meta17::DeferStaticError {                                                                                         \
        [](auto... args) {                                                                                             \
            constexpr auto check = (false && ... && args);                                                             \
            static_assert(check, error);                                                                               \
            return false;                                                                                              \
        }                                                                                                              \
    }

} // namespace meta17
