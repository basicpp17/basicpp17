#pragma once
#include "Strong.h"

#include "Strong.make.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>
#include <meta17/TypePack.recurse.h>

#define STRONG_OPAQUE(name, type, ...)                                                                                 \
    struct name;                                                                                                       \
    struct name##Tag;                                                                                                  \
    constexpr auto makeStrongType(                                                                                     \
        meta17::TypeTail<meta17::TypePack<void, __VA_ARGS__, name##Tag>> = {}, meta17::Type<type> = {})                \
        ->meta17::Type<name> {                                                                                         \
        return {};                                                                                                     \
    }                                                                                                                  \
    struct name : strong17::Strong<type, ##__VA_ARGS__, name##Tag> {                                                   \
        using Strong::Strong;                                                                                          \
    }
