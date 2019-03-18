#pragma once
#include "Strong.h"

#include "Strong.make.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>
#include <meta17/TypePack.recurse.h>

#define STRONG_OPAQUE(NAME, TYPE, ...)                                                                                 \
    struct NAME;                                                                                                       \
    constexpr auto makeOpaqueType(meta17::Type<strong17::Strong<TYPE, ##__VA_ARGS__>>)->meta17::Type<NAME> {           \
        return {};                                                                                                     \
    }                                                                                                                  \
    struct NAME : strong17::Strong<TYPE, ##__VA_ARGS__> {                                                              \
        using Strong::Strong;                                                                                          \
    }

#define STRONG_OPAQUE_TYPE(NAME, STRONG_TYPE)                                                                          \
    struct NAME;                                                                                                       \
    constexpr auto makeOpaqueType(meta17::Type<STRONG_TYPE>)->meta17::Type<NAME> { return {}; }                        \
    struct NAME : STRONG_TYPE {                                                                                        \
        using Strong::Strong;                                                                                          \
    }
