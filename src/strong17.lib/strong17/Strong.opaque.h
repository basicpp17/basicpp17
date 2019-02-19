#pragma once
#include "Strong.h"

#include "Strong.make.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>
#include <meta17/TypePack.recurse.h>

#define STRONG_OPAQUE(name, type, ...)                                                                                 \
    struct name;                                                                                                       \
    constexpr auto makeOpaqueType(meta17::Type<strong17::Strong<type, ##__VA_ARGS__>>)->meta17::Type<name> {           \
        return {};                                                                                                     \
    }                                                                                                                  \
    struct name : strong17::Strong<type, ##__VA_ARGS__> {                                                              \
        using Strong::Strong;                                                                                          \
    }
