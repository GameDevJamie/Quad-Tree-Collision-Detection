#pragma once

#include "Buffer.h"
#include "..\Defines.h"

namespace Genesis
{
	namespace render
	{
		class VertexBuffer : public Buffer
		{
			public:
				virtual ~VertexBuffer() {}

				//ACCESSORS
				//-------------------------------

				virtual inline TUInt32 GetVertexCount() = 0;
				virtual inline TUInt32 GetVertexSize() = 0;

				//-------------------------------
		};
	}
}