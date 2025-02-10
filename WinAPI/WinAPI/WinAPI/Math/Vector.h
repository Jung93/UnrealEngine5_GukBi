
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

	bool operator==(const Vector& other)
	{
		if (x == other.x && y == other.y)
			return true;
		return false;
	}

	bool operator!=(const Vector& other)
	{
		return !this->operator==(other);
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

	void Rotate(float theta)
	{
		x = x * cosf(theta) - y * sinf(theta);
		y = x * sinf(theta) + y * cosf(theta);
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

	float ManhattanDistance(Vector pos) 
	{ 
		Vector temp = pos - *this;

		return abs(temp.x) + abs(temp.y);
	}


	float x;
	float y;
};