#pragma once

#include "Vector3.h"
#include <iostream>

namespace Genesis
{
	namespace math
	{
		class Vector4
		{
			public:
				TFloat32 x;
				TFloat32 y;
				TFloat32 z;
				TFloat32 w;

				//Standard vectors//
				//....................
				static const Vector4 kZero;
				static const Vector4 kOne;
				static const Vector4 kOrigin;
				static const Vector4 kXAxis;
				static const Vector4 kYAxis;
				static const Vector4 kZAxis;
				//....................

				//Colour Vectors
				//------------------------
				static const Vector4 kWhite;
				static const Vector4 kBlack;
				static const Vector4 kRed;
				static const Vector4 kGreen;
				static const Vector4 kBlue;
				//------------------------

			public:
				//Constructor: Intialise the values
				Vector4();
				Vector4(const TFloat32& fX, const TFloat32& fY, const TFloat32& fZ, const TFloat32& fW);
				Vector4(const Vector3& xyz, TFloat32 fW);

				//OPERATOR OVERLOADERS//
				//---------------------------------------
				Vector4& operator=(const Vector4& v)
				{
					try
					{
						if (this != &v)
						{
							x = v.x;
							y = v.y;
							z = v.z;
							w = v.w;
						}
						return *this;
					}
					catch (const std::exception& ex)
					{
						std::cout << "ERROR!! " << ex.what() << std::endl;
					}
				}

				friend inline Vector4 operator-(const Vector4& v1, const Vector4& v2)
				{
					return Vector4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
				}

				friend inline Vector4 operator+(const Vector4& v1, const Vector4& v2)
				{
					return Vector4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
				}

				friend inline Vector4 operator+(const Vector4& v1, const TFloat32& value)
				{
					return Vector4(v1.x + value, v1.y + value, v1.z + value, v1.w + value);
				}

				friend inline Vector4 operator*(const Vector4& v1, const Vector4& v2)
				{
					return Vector4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
				}
				friend inline Vector4 operator*(const Vector4& v1, const TFloat32& value)
				{
					return Vector4(v1.x * value, v1.y * value, v1.z * value, v1.w * value);
				}

				friend inline Vector4 operator/(const Vector4& v, const TFloat32 s)
				{
					return Vector4(v.x / s, v.y / s, v.z / s, v.w / s);
				}

				friend inline Vector4 operator-(const Vector4& v)
				{
					return Vector4(-v.x, -v.y, -v.z, -v.w);
				}

				//Add another vector to this vector
				Vector4& operator+=(const Vector4& v)
				{
					x += v.x;
					y += v.y;
					z += v.z;
					w += v.w;
					return *this;
				}

				//Subtract another vector from this vector
				Vector4& operator-=(const Vector4& v)
				{
					x -= v.x;
					y -= v.y;
					z -= v.z;
					w -= v.w;
					return *this;
				}
				//---------------------------------------

				//ACCESSORS//
				//--------------------------

				//Retrieve the length of the vector
				TFloat32 GetLength() const;

				//--------------------------

				//MUTATORS//
				//-----------------------------

				//Set all at once
				//........................
				void SetAll(TFloat32 fX, TFloat32 fY, TFloat32 fZ, TFloat32 fW);
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
				TFloat32 Dot(Vector4& v) const;
				//..............................

				//Calculate Cross Product of this and given vector
				//..............................
				Vector4 Cross(Vector4& v) const;
				//..............................
			};
	}
}