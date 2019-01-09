# A C++17 base library

[![Build Status](https://travis-ci.org/basicpp17/basicpp17.svg?branch=develop)](https://travis-ci.org/basicpp17/basicpp17)
[![Build Status](https://dev.azure.com/BasiCpp17/BasiCpp17/_apis/build/status/basicpp17.basicpp17?branchName=develop)](https://dev.azure.com/BasiCpp17/BasiCpp17/_build/latest?definitionId=1&branchName=develop)

A collection of useful meta helpers and value types.

## Target Compilers

The goal is to write ISO Standard conforming C++17.
Everything that does not conform to the standard is a bug.

Additionally the code has to compile at least at the latest stable releases of:
* Clang
* Visual Studio C++ 2017 / 2019

GCC has long standing compiler bugs that allow no workarounds,
therefore it is not a goal.

Workarounds for specific compiler bugs should be marked as such!
It is a bug if a workaround is no longer required and not removed.

## Naming Schema

C++ uses a unified namespace between types, functions and constants.
Therefore we use the following patterns.

* `UpperCamelCasing` for types
* `lowerCamelCasing` for functions
* `UPPER_CASING` for precompiler
* `lower_casing` for constexpr constants & namespaces

For formatting `clang-format` is used with the `.clang-format`

## Modules

* `cpp17` - configures the compilers
* `meta17` - everything without runtime code or data
* `tuple17` - simple & fast replacement for `std::tuple`
* `string17` - constexpr enabled string store and view
* `strong17` - simple strong and opaque typedefs
* `variant17` - simple & fast relacement for `std::variant`
* `partial17` - a heap allocated & packed `tuple<optional<T>...>`

## Meta Design

The main goal is to allow simple and efficient compile time introspections.

The library itself should stay simple and readable.
All functions and constants are constexpr.
All functions arguments have enforced zero size.

To (wrap)
- build the type wrapper from the elements
- ensure no double encoding

Unwrap
- get the wrapped value
- also works if value was never wrapped

Extract
- get elements of a wrapper and wrap them differently
- will never work with unwrapped values

Recurse
- helper to build recursive functions
- keeps the same type of wrapper

Make
- produces the wrapped value
- involves some compile time computations

Operators (ops)
- appropriate compare & arithmetic operations

Trait
- checks if a given type is that kind of wrapper

Access
- random access to wrapped elemets of a pack wrapper

Fold & indexOf
- folding / search algorithms for pack wrappers

## Meta Parts

`Type<T>`
- empty constexpr wrapper for any type
- support for compile time comparison

`TemplateOfTypes<…>`
- operations on any template of types

`TemplateOfValues<…>`
- operations on any template of values

`TypePack<…>`
- Any amount of types
- Support for concatentation, indexOf & recursion

`Const<V>`
- std::integral_constant but with C++17 auto
- empty struct (use functons)

`Bool<>`
- required special const, because Const<false> == Const<0>
- convinient implicit cast to bool allows usage in if constexpr conditions

`Value<F>`
- user defined structs as constexpr values (eg. strings)
- values are taken by function or reference

`Index<I>`
- specialisation of Const for size_t
- implements arithmetic operators

`ConstPack<…>`
- Any amount of values
- Support for concatentation, folding & recursion

`IndexPack<…>`
- specialisation of ConstPack for size_t
- conversions for std::index_sequence

`IndexType<I, T>`
- wrapper that associates an index to a type

`IndexTypePack<…>`
- TypePack of IndexTypes
- allows for enum like index generation

`TypeList<…>`
- constexpr wrapper struct for IndexTypePacks
- ensures all indices are unique
- a lot of member functions

## License

This project uses the MIT License - see LICENSE file.

## Contributions

Please report your ideas and bugs as issues!
Pull requests are also welcome.

## Development

Checkout the repository, then run the `git_clone_googletest.sh` from within the folder *thirdparty* to checkout the required google test framework.

The BasiC idea behind the libary part is, that each component can be used standalone. Optional functionality can be introduced by including the dedicated header file.
