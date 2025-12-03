#include "transformComponent.h"

prism::scene::Position& prism::scene::Position::operator+=(const Position& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

prism::scene::Position& prism::scene::Position::operator-=(const Position& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

prism::scene::Position prism::scene::Position::operator-()
{
    return Position{ -x, -y, -z };
}

prism::scene::Position prism::scene::Position::operator+(const Position& other) const
{
    return Position{ x + other.x, y + other.y, z + other.z };
}

prism::scene::Position prism::scene::Position::operator-(const Position& other) const
{
    return Position{ x - other.x, y - other.y, z - other.z };
}

prism::scene::Position& prism::scene::Position::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

prism::scene::Position& prism::scene::Position::operator/=(float scalar)
{
    if (scalar != 0.0f) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
    return *this;
}

prism::scene::Position prism::scene::Position::operator*(float scalar) const
{
    return Position{ x * scalar, y * scalar, z * scalar };
}

prism::scene::Position prism::scene::Position::operator/(float scalar) const
{
    if (scalar != 0.0f) {
        return Position{ x / scalar, y / scalar, z / scalar };
    }
    return *this; // Возвращаем неизменённую позицию при делении на 0
}

bool prism::scene::Position::operator==(const Position& other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool prism::scene::Position::operator!=(const Position& other) const
{
    return !(*this == other);
}

prism::scene::Scale& prism::scene::Scale::operator*=(const Scale& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

prism::scene::Scale& prism::scene::Scale::operator/=(const Scale& other)
{
    if (other.x != 0.0f) x /= other.x;
    if (other.y != 0.0f) y /= other.y;
    if (other.z != 0.0f) z /= other.z;
    return *this;
}

prism::scene::Scale& prism::scene::Scale::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

prism::scene::Scale& prism::scene::Scale::operator/=(float scalar)
{
    if (scalar != 0.0f) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
    return *this;
}

prism::scene::Scale prism::scene::Scale::operator*(const Scale& other) const
{
    return Scale{ x * other.x, y * other.y, z * other.z };
}

prism::scene::Scale prism::scene::Scale::operator/(const Scale& other) const
{
    return Scale{
        other.x != 0.0f ? x / other.x : x,
        other.y != 0.0f ? y / other.y : y,
        other.z != 0.0f ? z / other.z : z
    };
}

prism::scene::Scale prism::scene::Scale::operator*(float scalar) const
{
    return Scale{ x * scalar, y * scalar, z * scalar };
}

prism::scene::Scale prism::scene::Scale::operator/(float scalar) const
{
    if (scalar != 0.0f) {
        return Scale{ x / scalar, y / scalar, z / scalar };
    }
    return *this;
}

bool prism::scene::Scale::operator==(const Scale& other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool prism::scene::Scale::operator!=(const Scale& other) const
{
    return !(*this == other);
}
