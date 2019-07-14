#pragma once

#include "Vector3.h"
#include "Matrix4x4.h"


namespace Genesis
{
	namespace math
	{
		class Quaternion
		{
			//DATA
			//----------------------

			public:
				TFloat32 w;
				TFloat32 x, y, z;

			//----------------------

			//Static Functions
			public:

				//Returns an Identity Quaternion (1, 0, 0 ,0)
				static const Quaternion kIdentity;

				//Returns a Quaternion using the given Euler Angles in Degrees
				static Quaternion Euler(const Vector3& v);

				//Returns a Quaternion using the given Euler Angles in Degrees
				static Quaternion Euler(const TFloat32& x, const TFloat32& y, const TFloat32& z);

				//Constructs a Quaternion using the given 4x4 Matrix (Assumes it is a normal Rotation Matrix)
				static Quaternion Matrix(const Matrix4x4& m);

			public:
				//OPERATOR OVERLOAD
				//----------------------------------
				Quaternion& operator=(const Quaternion& q)
				{
					if (this != &q)
					{
						w = q.w;
						x = q.x;
						y = q.y;
						z = q.z;
					}
					return *this;
				}

				Quaternion& operator+=(const Quaternion& q)
				{
					w += q.w;
					x += q.x;
					y += q.y;
					z += q.z;
					return *this;
				}

				Quaternion& operator-=(const Quaternion& q)
				{
					w -= q.w;
					x -= q.x;
					y -= q.y;
					z -= q.z;
					return *this;
				}

				Quaternion& operator*=(const TFloat32& scalar)
				{
					w *= scalar;
					x *= scalar;
					y *= scalar;
					z *= scalar;
					return *this;
				}

				Quaternion& operator/=(const TFloat32& scalar)
				{
					w /= scalar;
					x /= scalar;
					y /= scalar;
					z /= scalar;
					return *this;
				}
				//----------------------------------


				//CONSTRUCTORS
				//-------------------------------

				//Construct with default values (x,y,z = 0. w = 1)
				Quaternion();

				//Construct with given values
				Quaternion(TFloat32 iW, TFloat32 iX, TFloat32 iY, TFloat32 iZ);

				//-------------------------------


				//GETTERS
				//--------------------------------

				//Converts the Quaternion into Euler Angles
				//Returns the Euler Angles
				Vector3 ToEulerAngles() const;

				//Convert the Quaternion into a 4x4 Matrix
				Matrix4x4 ToMatrix() const;
				
				//--------------------------------


				//SETTERS
				//-------------------------------

				//Sets the Quaternion using the given Euler Angles
				void SetEuler(const Vector3& v);
				void SetEuler(const TFloat32& fX, const TFloat32& fY, const TFloat32& fZ);

				//Normalises the Quaternion (Unit Length as a Vector4)
				void Normalise();

				//Inverts the Quaternion
				void Invert();

				//-------------------------------


				//Returns the Norm/Length of the Quaternion
				TFloat32 Length() const;

				//Returns the Inverse of this Quaternion
				Quaternion Inverse() const;
		};

		//NON-MEMBER OPERATOR OVERLOAD
		//-------------------------------
		
		//Quaternion Addition
		inline Quaternion operator+
		(
			const Quaternion& quat1,
			const Quaternion& quat2
		)
		{
			return Quaternion(quat1.w + quat2.w, quat1.x + quat2.x, quat1.y + quat2.y, quat1.z + quat2.z);
		}

		//Quaternion Subtraction
		inline Quaternion operator-
		(
			const Quaternion& quat1,
			const Quaternion& quat2
		)
		{
			return Quaternion(quat1.w - quat2.w, quat1.x - quat2.x, quat1.y - quat2.y, quat1.z - quat2.z);
		}

		//Quaternion multiplied by scalar
		inline Quaternion operator*
		(
			const Quaternion& quat,
			const TFloat32 scalar
		)
		{
			return Quaternion(quat.w*scalar, quat.x*scalar, quat.y*scalar, quat.z*scalar);
		}

		//Scalar multiplied by quaternion
		inline Quaternion operator*
		(
			const TFloat32 scalar,
			const Quaternion& quat
		)
		{
			return Quaternion(quat.w*scalar, quat.x*scalar, quat.y*scalar, quat.z*scalar);
		}
		//-------------------------------


		//Interpolation Functions
		//-----------------------------------

		//Perform Linear Interpolation between the 2 Quaternions
		Quaternion Lerp
		(
			const Quaternion& q1,
			const Quaternion& q2,
			const TFloat32 t
		);

		//Perform Spherical Linear Interpolation between the 2 Quaternions
		//More Accurate than Lerp
		Quaternion SLerp
		(
			const Quaternion& q1,
			const Quaternion& q2,
			const TFloat32 t
		);

		//Perform Linear Interpolation between the 2 Quaternions.
		//Result is Normalised
		Quaternion NLerp
		(
			const Quaternion& q1,
			const Quaternion& q2,
			const TFloat32 t
		);

		//-----------------------------------
	}
}