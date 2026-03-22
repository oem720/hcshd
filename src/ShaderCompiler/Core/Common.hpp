#pragma once

#include <stdint.h>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <fstream>
#include <filesystem>
#include <charconv>
#include <string>
#include <vector>
#include <array>
#include <map>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef std::string String;
template<typename T> using Array = std::vector<T>;
template<typename T, size_t S> using FixedArray = std::array<T, S>;
template<typename K, typename V> using Map = std::map<K, V>;

typedef std::filesystem::path FilePath;
typedef std::fstream FileStream;

template<typename T, class D = std::default_delete<T>> using Unique = std::unique_ptr<T, D>;

#define HC_CREATE_32BIT_TAG(char1, char2, char3, char4) (static_cast<uint32>(char4) << 24) | (static_cast<uint32>(char3) << 16) | (static_cast<uint32>(char2) << 8) | static_cast<uint32>(char1)
#define HC_SFINAE_REQUIRE_NUMERIC(_typename) typename = typename std::enable_if<std::disjunction<std::is_integral<_typename>, std::is_floating_point<_typename>>::value>::type
#define HC_SFINAE_REQUIRE_INTEGER(_typename) typename = typename std::enable_if<std::is_integral<_typename>::value>::type
#define HC_SFINAE_REQUIRE_FLOATING_POINT(_typename) typename = typename std::enable_if<std::is_floating_point<_typename>::value>::type
#define HC_INLINE inline