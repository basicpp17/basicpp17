#pragma once

namespace meta17 {

// note: MSVC has issues if we pack this into a funtion
// * this function cannot be inlined - resulting in very bad codegen

#ifdef _MSC_VER
#    define UNREACHABLE() __assume(false)
#else
#    define UNREACHABLE() __builtin_unreachable()
#endif

} // namespace meta17
