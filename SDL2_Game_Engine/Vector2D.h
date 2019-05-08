#pragma once
#include <iostream>
using namespace std;
class Vector2D
{
public:
	float x;
	float y;

	//setup the initial Vector2D
	Vector2D(float x=0.0, float y=0.0);
	//Add constant vector force
	Vector2D& Add(const Vector2D& vec);
	//Subtract constant vector force
	Vector2D& Subtract(const Vector2D& vec);
	//Multiply constant vector force
	Vector2D& Multiply(const Vector2D& vec);
	//Divide constant vector force
	Vector2D& Divide(const Vector2D& vec);

	//to create operator overload, returns reference to Vector2D we will add vector force to the current vector force if i understand this plus operator overload
	//we can access x and y directly because this is a friend even if it isn't/wasn't a member function
	//see https://www.learncpp.com/cpp-tutorial/92-overloading-the-arithmetic-operators-using-friend-functions/ for more info
	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	//overrides vector2D, returns reference to it and subtracts current v1 by v2 values
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	//overrides vector2D, returns reference to it and multiplies current v1 by v2 values
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	//overrides vector2D, returns reference to it and divides current v1 by v2 values
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	//directly operates on the referenced Vector2D to add the value of vec to it
	Vector2D& operator+=(const Vector2D& vec);
	//directly operates on the referenced Vector2D to subtract the value of vec to it
	Vector2D& operator-=(const Vector2D& vec);
	//directly operates on the referenced Vector2D to multiply it by the value of vec
	Vector2D& operator*=(const Vector2D& vec);
	//directly operates on the referenced Vector2D to divideit by the value of vec
	Vector2D& operator/=(const Vector2D& vec);
	
	// multiplying our vectors by a scaler number
	Vector2D& operator*(const int& i);
	//zero out our vectors
	Vector2D& Zero();
	
	friend ostream& operator << (ostream& stream, const Vector2D& vec);
};