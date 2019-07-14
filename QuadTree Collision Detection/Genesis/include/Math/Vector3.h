#pragma once

#include "..\Defines.h"
#include "Vector2.h"

namespace Genesis
{
	namespace math
	{
		class Vector3
		{
			public:
				TFloat32 x;
				TFloat32 y;
				TFloat32 z;

				//Standard vectors//
				//....................
				static const Vector3 kZero;
				static const Vector3 kOne;
				static const Vector3 kHalf;
				static const Vector3 kOrigin;
				static const Vector3 kXAxis;
				static const Vector3 kYAxis;
				static const Vector3 kZAxis;
				//....................

				//Colour Vectors
				//------------------------
				static const Vector3 kWhite;
				static const Vector3 kBlack;
				static const Vector3 kGrey;
				static const Vector3 kRed;
				static const Vector3 kGreen;
				static const Vector3 kBlue;
				static const Vector3 kYellow;
				//------------------------

			public:
				//Constructor: Intialise the values
				Vector3();
				Vector3(const TFloat32& fX, const TFloat32& fY, const TFloat32& fZ);
				Vector3(const Vector2& xy, const TFloat32& fZ = 0.0f);

				//OPERATOR OVERLOADERS//
				//---------------------------------------
				Vector3& operator=(const Vector3& v)
				{
					if (this != &v)
					{
						x = v.x;
						y = v.y;
						z = v.z;
					}
					return *this;
				}

				friend inline Vector3 operator-(const Vector3& v)
				{
					return Vector3(-v.x, -v.y, -v.z);
				}

				friend inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
				{
					return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
				}

				friend inline Vector3 operator+(const Vector3& v1, const Vector3& v2)
				{
					return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
				}

				friend inline Vector3 operator+(const Vector3& v1, const TFloat32& value)
				{
					return Vector3(v1.x + value, v1.y + value, v1.z + value);
				}
				friend inline Vector3 operator+(const TFloat32& value, const Vector3& v1)
				{
					return Vector3(v1.x + value, v1.y + value, v1.z + value);
				}

				friend inline Vector3 operator*(const Vector3& v1, const Vector3& v2)
				{
					return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
				}
				friend inline Vector3 operator*(const Vector3& v1, const TFloat32& value)
				{
					return Vector3(v1.x * value, v1.y * value, v1.z * value);
				}
				friend inline Vector3 operator*(const TFloat32& value, const Vector3& v1)
				{
					return Vector3(v1.x * value, v1.y * value, v1.z * value);
				}

				friend inline Vector3 operator/(const Vector3& v, const TFloat32& s)
				{
					return Vector3(v.x / s, v.y / s, v.z / s);
				}
				friend inline Vector3 operator/(const TFloat32& s, const Vector3& v)
				{
					return Vector3(v.x / s, v.y / s, v.z / s);
				}

				friend inline bool operator>=(const Vector3& v1, const Vector3& v2)
				{
					return (v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z);
				}
				friend inline bool operator<=(const Vector3& v1, const Vector3& v2)
				{
					return (v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z);
				}

				friend inline bool operator>(const Vector3& v1, const Vector3& v2)
				{
					return (v1.x > v2.x && v1.y > v2.y && v1.z > v2.z);
				}
				friend inline bool operator<(const Vector3& v1, const Vector3& v2)
				{
					return (v1.x < v2.x && v1.y < v2.y && v1.z < v2.z);
				}

				//Add another vector to this vector
				Vector3& operator+=(const Vector3& v)
				{
					x += v.x;
					y += v.y;
					z += v.z;
					return *this;
				}

				//Subtract another vector from this vector
				Vector3& operator-=(const Vector3& v)
				{
					x -= v.x;
					y -= v.y;
					z -= v.z;
					return *this;
				}
				//---------------------------------------

				//ACCESSORS//
				//--------------------------

				//Retrieve the length of the vector
				TFloat32 GetLength() const;

				//Returns a Vector2 version of this Vector (x and y values only)
				Vector2 GetVector2() const;

				//--------------------------

				//MUTATORS//
				//-----------------------------

				//Set all at once
				//........................
				void SetAll(TFloat32 fX, TFloat32 fY, TFloat32 fZ);
				//........................

				//Set all the same value
				//.........................
				void SetAll(TFloat32 value);
				//.........................

				//-----------------------------

				//Normalise the vector
				//........................
				void Normalise();
				//........................

				//Calculate Dot Product of this and given vector
				//..............................
				TFloat32 Dot(Vector3& v) const;
				//..............................

				//Calculate Cross Product of this and given vector
				//..............................
				Vector3 Cross(Vector3& v) const;
				//..............................
		};
	}
}