#include "MathUtils.h"

#include <cmath>
#include <algorithm>

void MathUtils::ClampMagnitude(sf::Vector2f& r_vec, float min, float max)
{
	float sqrMagnitude = SqrMagnitude(r_vec);
	bool tooShort = sqrMagnitude < min * min;
	bool tooLong = sqrMagnitude > max * max;
	if (!tooShort && !tooLong)
	{
		return;
	}
	float wantedMagnitude = tooShort ? min : max;
	r_vec = Normalize(r_vec) * wantedMagnitude;
}

float MathUtils::SqrMagnitude(const sf::Vector2f& vec)
{
	return SqrMagnitude(vec.x, vec.y);
}

float MathUtils::SqrMagnitude(float x, float y)
{
	return x * x + y * y;
}

float MathUtils::Magnitude(const sf::Vector2f& vec)
{
	return Magnitude(vec.x, vec.y);
}

float MathUtils::Magnitude(float x, float y)
{
	return std::sqrt(SqrMagnitude(x, y));
}

float MathUtils::SqrDistance(const sf::Vector2f& from, const sf::Vector2f& to)
{
	return SqrDistance(from.x, from.y, to.x, to.y);
}

float MathUtils::SqrDistance(float xFrom, float yFrom, float xTo, float yTo)
{
	return SqrMagnitude(xTo - xFrom, yTo - yFrom);
}

float MathUtils::Distance(const sf::Vector2f& from, const sf::Vector2f& to)
{
	return Distance(from.x, from.y, to.x, to.y);
}

float MathUtils::Distance(float xFrom, float yFrom, float xTo, float yTo)
{
	return std::sqrt(SqrDistance(xFrom, yFrom, xTo, yTo));
}

sf::Vector2f MathUtils::Normalize(const sf::Vector2f& vec)
{
	float magnitude = Magnitude(vec);
	return	sf::Vector2f{ vec.x / magnitude, vec.y / magnitude };
}

float MathUtils::Dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

float MathUtils::Angle(const sf::Vector2f& from, const sf::Vector2f& to)
{
	float num = std::sqrt(SqrMagnitude(from) * SqrMagnitude(to));
	if (num < 1E-15f)
	{
		return 0.0f;
	}

	float num2 = std::clamp(Dot(from, to) / num, -1.0f, 1.0f);
	return std::acos(num2);// *57.29578f;
}

float MathUtils::SignedAngle(const sf::Vector2f& from, const sf::Vector2f& to)
{
	float angle = Angle(from, to);
	float sign = Sign(from.x * to.y - from.y * to.x);
	return angle * sign;
}

float MathUtils::Sign(float val)
{
	return val < 0.0f ? -1.0f : 1.0f;
}

int MathUtils::Sign(int val)
{
	return val < 0 ? -1 : 1;
}

float MathUtils::SmoothLerp(float a, float b, float deltaTime, float halfLife)
{
	return b + (a - b) * exp2f(-deltaTime / halfLife);
}

sf::Vector2f MathUtils::SmoothLerp(const sf::Vector2f& a, const sf::Vector2f& b, float deltaTime, float halfLife)
{
	return
	{
		SmoothLerp(a.x, b.x, deltaTime, halfLife),
		SmoothLerp(a.y, b.y, deltaTime, halfLife)
	};
}

float MathUtils::RemapFrom01(float val, float targetMin, float targetMax)
{
	return targetMin + val * (targetMax - targetMin);
}

float MathUtils::RemapTo01(float val, float initialMin, float initialMax)
{
	return (val - initialMin) / (initialMax - initialMin);
}

float MathUtils::Remap(float val, float initialMin, float initialMax, float targetMin, float targetMax)
{
	return RemapFrom01(RemapTo01(val, initialMin, initialMax), targetMin, targetMax);
}