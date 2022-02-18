#pragma once

#ifndef NDEBUG
#define assert(...) __assume(__VA_ARGS__)
#else
#define assert(...) if (not (__VA_ARGS__)) __debugbreak()
#endif