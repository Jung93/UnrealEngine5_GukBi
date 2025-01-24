
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

	Vector& operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector& operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	float Length() const
	{
		return sqrtf(this->x * this->x + this->y * this->y);
	}

	void Noramlize()
	{
		float length = Length();
		x /= length;
		y /= length;

	}

	Vector NormalVector() const
	{
		Vector result = *this;
		result.Noramlize();
		return result;
	
	}


	float Dot(const Vector& other) const
	{
		float result;

		result = (this->x * other.x) + (this->y * other.y);

		return result;
	}

	//z값의 크기
	float Cross(const Vector& other) const
	{
		float result;

		result = (this->x * other.y) - (this->y * other.x);

		return result;
	}


	float x;
	float y;
};