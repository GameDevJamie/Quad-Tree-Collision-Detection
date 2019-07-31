#pragma once

/*****************************************************

-Axis-Aligned Bounding Box

-Bottom Left = Min
-Top Right = Max

******************************************************/

#include "..\Defines.h"
#include "Vector3.h"

namespace Genesis
{
	namespace math
	{
		struct AABB
		{
			public:
				Vector3 Centre;	//Centre point of Box
				Vector3 Size;		//Width, Height and Depth
				Vector3 Min;		//Minimum value of Box (Bottom Left corner)
				Vector3 Max;		//Maximum value of Box (Top Right corner)

				//Constructors
				//----------------------------

				AABB()
				{
					Centre = Vector3::kZero;
					Size = Vector3::kZero;
					Min = Vector3::kZero;
					Max = Vector3::kZero;
				}
				AABB(const Vector3& centre, const Vector2& size)
				{
					Centre = centre;
					Size = math::Vector3(size, 0.0f);

					Min = Centre - (Size / 2.0f);
					Max = Centre + (Size / 2.0f);
				}
				AABB(const Vector3& centre, const Vector3& size)
				{
					Centre = centre;
					Size = size;

					Min = Centre - (Size / 2.0f);
					Max = Centre + (Size / 2.0f);
				}

				//----------------------------

				void SetSize(const math::Vector2& size)
				{
					Size = math::Vector3(size, 0.0f);

					Min = Centre - (Size / 2.0f);
					Max = Centre + (Size / 2.0f);
				}
				void SetSize(const math::Vector3& size)
				{
					Size = size;

					Min = Centre - (Size / 2.0f);
					Max = Centre + (Size / 2.0f);
				}

				//Returns true if the given Point is inside the Box
				bool Contains(const math::Vector2& point) const
				{
					return (point > Min.GetVector2() && point < Max.GetVector2());
				}
				bool Contains(const math::Vector3& point) const
				{
					return (point > Min && point < Max);
				}
				bool Contains(const AABB& box) const
				{
					return !(
						(this->Max.x < box.Min.x) 
						|| (box.Max.x < this->Min.x) 
						
						|| (this->Max.y < box.Min.y) 
						|| (box.Max.y < this->Min.y) 
						
						|| (this->Max.z < box.Min.z) 
						|| (box.Max.z < this->Min.z));
				}
		};
	}
}