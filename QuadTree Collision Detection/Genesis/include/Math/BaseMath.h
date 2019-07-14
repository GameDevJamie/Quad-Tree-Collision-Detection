#pragma once

#include "..\Defines.h"
#include "Vector2.h"
#include "Matrix4x4.h"
#include "AABB.h"

#include <string>
#include <vector>

namespace Genesis
{
	namespace math
	{
		TFloat32 Sin(const TFloat32& x);
		TFloat32 Cos(const TFloat32& x);
		TFloat32 Tan(const TFloat32 x);
		TFloat32 ATan(const TFloat32 x);
		void SinCos(const TFloat32& x, TFloat32& pSin, TFloat32& pCos);

		TFloat32 Sqrt(const TFloat32 x);
		TFloat32 InvSqrt(const TFloat32 x);

		TFloat32 ToRadians(const TFloat32& degrees);
		TFloat32 ToDegrees(const TFloat32& radians);

		TInt32 RoundDown(const TFloat32& x, const TInt32& rounding);
		TInt32 RoundUp(const TFloat32& x, const TInt32& rounding);
		TInt32 Round(const TFloat32& x);

		//FUNCTIONS FOR CALCULATING RANDOM VALUES
		//--------------------------------------------------

		//Return a random integer from a to b
		TInt32 Random(const TInt32& a, const TInt32& b);

		//Return a random float from a to b
		TFloat32 Random(const TFloat32& a, const TFloat32& b);

		//Return a random Vector3 based on given values
		Vector3 Random(const Vector3& minV, const Vector3& maxV);

		//Returns a random Vector3, inside the given sphere
		Vector3 RandomCircle(const Vector3& center, const TFloat32& radius);

		//--------------------------------------------------		


		//Tests if the given string is a number (Including negatives)
		//Returns true if it is
		bool IsNumber(const std::string& word);

		//DOT
		//---------------------------------------------

		TFloat32 Dot(const Vector2& v1, const Vector2& v2);
		TFloat32 Dot(const Vector3& v1, const Vector3& v2);
		TFloat32 Dot(const Vector4& v1, const Vector4& v2);

		//---------------------------------------------

		//CROSS
		//---------------------------------------------

		Vector3 Cross(const Vector3& v1, const Vector3& v2);
		Vector4 Cross(const Vector4& v1, const Vector4& v2);

		//---------------------------------------------

		//LERP/SLERP/NLERP
		//---------------------------------------------

		Vector3 Lerp(const Vector3& start, const Vector3& end, TFloat32 alpha);
		Vector4 Lerp(const Vector4& start, const Vector4& end, TFloat32 alpha);

		//---------------------------------------------
		

		//SPLINE
		//---------------------------------------------

		Vector3 CatmullRomSpline
		(
			const Vector3& p0,
			const Vector3& p1,
			const Vector3& p2,
			const Vector3& p3,
			const TFloat32& t
		);

		bool CatmullRomSpline
		(
			std::vector<Vector3> points,
			TFloat32 t,
			Vector3& output
		);

		Vector3 BezierSpline
		(
			const Vector3& p0,
			const Vector3& p1,
			const Vector3& p2,
			const Vector3& p3,
			const TFloat32& t
		);

		//---------------------------------------------


		//COLLISION DETECTION
		//---------------------------------------

		bool PointToSphereCollision(const math::Vector3& pos1, const math::Vector3& pos2, const TFloat32& radius);
		bool SphereToSphereCollision(const math::Vector3& pos1, const math::Vector3& pos2, const TFloat32& radius1, const TFloat32& radius2);
		bool PointToBoxCollision(const math::Vector3& pos1, const AABB&);
		bool BoxToBoxCollision(const math::Vector3& pos1, const TFloat32& boxSize1, const math::Vector3& pos2, const TFloat32& boxSize2);
		bool BoxToBoxCollision(const AABB& box1, const AABB& box2);

		//---------------------------------------


		//FUNCTIONS FOR CREATING DIFFERENT CAMERA PROJECTION MATRICES
		//------------------------------

		Matrix4x4 CreateViewMatrix(const Matrix4x4& worldMatrix);
		Matrix4x4 CreatePerspectiveMatrix(const Vector2& resolution, const TFloat32 nearClip, const TFloat32 farClip, const TFloat32 fov);
		Matrix4x4 CreateOrthographicMatrix(const TInt32& size, TFloat32 nearClip, TFloat32 farClip);

		//------------------------------
	}
}