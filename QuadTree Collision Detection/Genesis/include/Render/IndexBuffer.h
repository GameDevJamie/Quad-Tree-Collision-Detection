#pragma once

#include "Buffer.h"
#include "..\Defines.h"

namespace Genesis
{
	namespace render
	{
		class IndexBuffer : public Buffer
		{
			public:
				virtual ~IndexBuffer() {}

				//ACCESSORS
				//--------------------------------

				virtual inline TUInt32 GetIndexCount() = 0;

				//--------------------------------
		};
	}
}