#pragma once

#include "Vector.hpp"

#include <array>
#include <format>
#include <span>

namespace Math {

// NOTE: this matrix implementation is column-major
struct Matrix4D {
public:
    constexpr Matrix4D()
        : data_{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f} {}

    constexpr Matrix4D(const std::array<float, 16zu> &array) : data_{array} {}

    /* matrix *= matrix */
    constexpr Matrix4D &operator*=(const Matrix4D &right) {
        std::array<float, 16zu> result_data{};
        for (auto column{0zu}; column < 4; ++column) {
            for (auto k{0zu}; k < 4; ++k) {
                float right_value = right.data_[k + column * 4];
                for (auto row{0zu}; row < 4; ++row) {
                    result_data[row + column * 4] += data_[row + k * 4] * right_value;
                }
            }
        }
        data_ = result_data;
        return *this;
    }

    /* matrix * matrix */
    friend constexpr Matrix4D operator*(const Matrix4D &left_matrix, const Matrix4D &right_matrix) {
        Matrix4D product = left_matrix;
        product *= right_matrix;
        return product;
    }

    constexpr Matrix4D(Vector3 translation)
        : data_{1.0f, 0.0f, 0.0f, 0.0f, 0.0f,          1.0f,          0.0f,          0.0f,
                0.0f, 0.0f, 1.0f, 0.0f, translation.x, translation.y, translation.z, 1.0f} {}

    // TODO: optimize this
    static constexpr Matrix4D LookAt(const Vector3 &eye, const Vector3 &look_at, const Vector3 &up) {
        const auto forward = Vector3::Normalize(look_at - eye);
        const auto right = Vector3::CrossProduct(up, forward).Normalize();
        const auto true_up = Vector3::CrossProduct(forward, right).Normalize();
        auto matrix = Matrix4D{}.data_ = {right.x,   right.y, right.z,   0.0f,      true_up.x, true_up.y,
                                   true_up.z, 0.0f,    forward.x, forward.y, forward.z, 0.0f,
                                   0.0f,      0.0f,    0.0f,      1.0f};

        return matrix * Matrix4D{-eye};
    }

    constexpr std::span<const float> GetView() const { return data_; }

private:
    std::array<float, 16zu> data_;
};

} // namespace Math

using Matrix4 = Math::Matrix4D;

template <>
struct std::formatter<Matrix4> {
    constexpr auto parse(std::format_parse_context &context) const { return std::begin(context); }
    constexpr auto format(const Matrix4 &object, std::format_context &context) const {
        const auto *data = object.GetView().data();
        return std::format_to(context.out(), "[\n{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n]", data[0],
                              data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9],
                              data[10], data[11], data[12], data[13], data[14], data[15]);
    }
};
