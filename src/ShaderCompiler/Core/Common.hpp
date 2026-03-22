#pragma once

//Basic Includes
#include <stdint.h>
#include <utility>
#include <cassert>
#include <iostream>
#include <stdexcept>

//Required Includes (will not be replaced)
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <fstream>
#include <filesystem>
#include <functional>
#include <chrono>
#include <charconv>
#include <variant>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

//Includes for STL library that will be replaced with custom implementations in the future
#include <string>
#include <vector>
#include <array>
#include <list>
#include <queue>
#include <deque>
#include <set>
#include <span>
#include <optional>
#include <map>
#include <unordered_map>
#include <limits>

//Aliasing for types that will be replaced with custom implementation.
typedef std::string String;
template<typename T> using Array = std::vector<T>;
template<typename T, size_t S> using FixedArray = std::array<T, S>;
template<typename T> using List = std::list<T>;
template<typename T> using Queue = std::queue<T>;
template<typename T> using DoubleEndedQueue = std::deque<T>;
template<typename T, typename C = std::less<T>> using Set = std::set<T, C>;
template<typename T> using Optional = std::optional<T>;
template<typename T> using Span = std::span<T>;
template<typename K, typename V> using Map = std::map<K, V>;
template<typename K, typename V> using UnorderedMap = std::unordered_map<K, V>;

//Aliasing for types that will not be replaced, or may be replaced in the far future.
typedef std::thread Thread;
typedef std::mutex Mutex;
typedef std::condition_variable ConditionVariable;
typedef std::filesystem::path FilePath;
typedef std::fstream FileStream;
template<typename T> using Function = std::function<T>;
template<typename T, class D = std::default_delete<T>> using Unique = std::unique_ptr<T, D>;
template<typename T> using Shared = std::shared_ptr<T>;
template<typename T> using Weak = std::weak_ptr<T>;

#define HC_CREATE_32BIT_TAG(char1, char2, char3, char4) (static_cast<uint32>(char4) << 24) | (static_cast<uint32>(char3) << 16) | (static_cast<uint32>(char2) << 8) | static_cast<uint32>(char1)
#define HC_SFINAE_REQUIRE_NUMERIC(_typename) typename = typename std::enable_if<std::disjunction<std::is_integral<_typename>, std::is_floating_point<_typename>>::value>::type
#define HC_SFINAE_REQUIRE_INTEGER(_typename) typename = typename std::enable_if<std::is_integral<_typename>::value>::type
#define HC_SFINAE_REQUIRE_FLOATING_POINT(_typename) typename = typename std::enable_if<std::is_floating_point<_typename>::value>::type
#define HC_INLINE inline