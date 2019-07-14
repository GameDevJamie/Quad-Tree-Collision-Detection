/**********************************
	Range.h

	* Struct datatype. Used to hold Min and Max floating point values

***********************************/

#pragma once

#include "Defines.h"

namespace Genesis
{
	namespace math
	{
		struct Range
		{
			TFloat32 Min;
			TFloat32 Max;
		};
	}
}