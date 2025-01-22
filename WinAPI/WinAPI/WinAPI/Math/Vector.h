
#pragma once

class Vector
{
public:
	Vector() : x(0.0f), y(0.0f) {}
	Vector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	~Vector() {}

	Vector operator+(const Vector& other) const
	{
		Vector result;
		result.x = this->x + other.x;
		result.y = this->y + other.y;

		return result;
	}

	Vector operator-(const Vector& other) const
	{
		Vector result;
		result.x = this->x - other.x;
		result.y = this->y - other.y;

		return result;
	}


	Vector operator*(float value) const
	{
		Vector result;
		result.x = this->x * value;
		result.y = this->y * value;

		return result;
	}

	Vector& operator=(const Vector& other)
	{
		this->x = other.x;
		this->y = other.y;

		return *this;
	}

	Vector& operator++()
	{
		this->x += 1.0f;
		this->y += 1.0f;

		return *this;
	}

	Vector operator++(int)
	{
		Vector result(*this);
		this->x += 1.0f;
		this->y += 1.0f;

		return result;
	}

	float Length() const
	{
		return sqrtf(this->x * this->x + this->y * this->y);
	}

	void Noramlize()
	{
		// ����
	}

	float Dot(const Vector& other) const
	{
		float result;

		result = (this->x * other.x) + (this->y * other.y);

		return result;
	}

	float Cross(const Vector& other) const
	{
		float result;

		result = (this->x * other.y) - (this->y * other.x);

		return result;
	}


	float x;
	float y;
};