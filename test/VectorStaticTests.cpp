#include "App/Types.hpp"

static_assert(vec3(5.0f).x == 5.0f && vec3(5.0f).y == 5.0f && vec3(5.0f).z == 5.0f);
static_assert(ivec3(5).x == 5 && ivec3(5).y == 5 && ivec3(5).z == 5);

static_assert(vec2(5.0f).x == 5.0f && vec2(5.0f).y == 5.0f);
static_assert(ivec2(5).x == 5 && ivec2(5).y == 5);

// Test Addition + Overload
// - operator(+) uses operator(+=) assignment
constexpr auto vec3_v1 = ivec3{1, 2, 3};
constexpr auto vec3_v2 = ivec3{4, 5, 6};
constexpr auto vec3_sum = static_cast<ivec3>(vec3_v1 + vec3_v2);
static_assert(vec3_sum.x == 5 && vec3_sum.y == 7 && vec3_sum.z == 9);

constexpr auto vec2_v1 = ivec2{1, 2};
constexpr auto vec2_v2 = ivec2{4, 5};
constexpr auto vec2_sum = static_cast<ivec2>(vec2_v1 + vec2_v2);
static_assert(vec2_sum.x == 5 && vec2_sum.y == 7);

// Test Empty Vector Addition
constexpr auto vec3_v3 = ivec3{};
constexpr auto vec3_v4 = ivec3{};
constexpr auto vec3_sum_empty = static_cast<ivec3>(vec3_v3 + vec3_v4);
static_assert(vec3_sum_empty.x == 0 && vec3_sum_empty.y == 0 && vec3_sum_empty.z == 0);

constexpr auto vec2_v3 = ivec2{};
constexpr auto vec2_v4 = ivec2{};
constexpr auto v_sum_empty = static_cast<ivec2>(vec2_v3 + vec2_v4);
static_assert(v_sum_empty.x == 0 && v_sum_empty.y == 0);

// Test Scalar Multiplication
constexpr auto vec3_v5 = ivec3{2, 1, 6};
constexpr auto vec3_v5_scaled = static_cast<ivec3>(vec3_v5 * 2);
static_assert(vec3_v5_scaled.x == 4 && vec3_v5_scaled.y == 2 && vec3_v5_scaled.z == 12);

constexpr auto vec2_v5 = ivec2{2, 1};
constexpr auto vec2_v5_scaled = static_cast<ivec2>(vec2_v5 * 2);
static_assert(vec2_v5_scaled.x == 4 && vec2_v5_scaled.y == 2);

constexpr auto bad_vector  = ivec3{2, 4, 6};
constexpr auto bad_vector2 = ivec2{2, 4};
constexpr bad_vector2 *= bad_vector;
