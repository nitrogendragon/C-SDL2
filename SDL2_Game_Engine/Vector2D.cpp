#include "Vector2D.h"
//constructor class for Vector2D taking in two parameters x and y which if not declared will both be 0.0
Vector2D::Vector2D(float x, float y)
{
	//set up x val for Vector2D
	this->x = x;
	//set up y val for Vector2D
	this->y = y;
}
//adding to our referenced Vector2D
Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

//subtracting from our referenced Vector2D
Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

//Multiplying our referenced Vector2D
Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

//dividing our referenced Vector2D
Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}
//overrides vector2D, returns reference to it and adds current v1 by v2 values
Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}
//overrides vector2D, returns reference to it and subtracts current v1 by v2 values
Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}
//overrides vector2D, returns reference to it and multiplies current v1 by v2 values
Vector2D& operator*(Vector2D& v1, const Vector2D& v2) 
{
	return v1.Multiply(v2);
}
//overrides vector2D, returns reference to it and divides current v1 by v2 values
Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}

//directly operates on the referenced Vector2D to add the value of vec to it
Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}
//directly operates on the referenced Vector2D to subtract the value of vec to it
Vector2D& Vector2D::operator -= (const Vector2D& vec)
{
	return this->Subtract(vec);
}
//directly operates on the referenced Vector2D to multiply it by the value of vec
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}
//directly operates on the referenced Vector2D to divideit by the value of vec
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}


ostream& operator << (ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}