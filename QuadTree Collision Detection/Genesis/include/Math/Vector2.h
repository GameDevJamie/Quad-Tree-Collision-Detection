#pragma once

#include "..\Defines.h"

namespace Genesis
{
	namespace math
	{
		class Vector2
		{
		public:
			TFloat32 x;
			TFloat32 y;

			//Standard vectors//
			//....................
			static const Vector2 kZero;
			static const Vector2 kOne;
			static const Vector2 kOrigin;
			static const Vector2 kXAxis;
			static const Vector2 kYAxis;
			//....................

		public:
			//Constructor: Intialise the values
			Vector2(float fX = 0.0f, float fY = 0.0f);

			//OPERATOR OVERLOADERS//
			//---------------------------------------
			Vector2& operator=(const Vector2& v)
			{
				if (this != &v)
				{
					x = v.x;
					y = v.y;
				}
				return *this;
			}

			friend inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
			{
				return Vector2(v1.x - v2.x, v1.y - v2.y);
			}

			friend inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
			{
				return Vector2(v1.x + v2.x, v1.y + v2.y);
			}

			friend inline Vector2 operator*(const Vector2& v1, const Vector2& v2)
			{
				return Vector2(v1.x * v2.x, v1.y * v2.y);
			}
			friend inline Vector2 operator*(const Vector2& v1, const TFloat32& value)
			{
				return Vector2(v1.x * value, v1.y * value);
			}

			friend inline Vector2 operator/(const Vector2& v, const TFloat32 s)
			{
				return Vector2(v.x / s, v.y / s);
			}

			friend inline Vector2 operator-(const Vector2& v)
			{
				return Vector2(-v.x, -v.y);
			}

			friend inline bool operator>=(const Vector2& v1, const Vector2& v2)
			{
				return (v1.x >= v2.x && v1.y >= v2.y);
			}
			friend inline bool operator<=(const Vector2& v1, const Vector2& v2)
			{
				return (v1.x <= v2.x && v1.y <= v2.y);
			}

			friend inline bool operator>(const Vector2& v1, const Vector2& v2)
			{
				return (v1.x > v2.x && v1.y > v2.y);
			}
			friend inline bool operator<(const Vector2& v1, const Vector2& v2)
			{
				return (v1.x < v2.x && v1.y < v2.y);
			}

			//Add another vector to this vector
			Vector2& operator+=(const Vector2& v)
			{
				x += v.x;
				y += v.y;
				return *this;
			}

			//Subtract another vector from this vector
			Vector2& operator-=(const Vector2& v)
			{
				x -= v.x;
				y -= v.y;
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
			void SetAll(TFloat32 fX, TFloat32 fY);

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
			TFloat32 Dot(Vector2& v) const;
			//..............................
		};
	}
}