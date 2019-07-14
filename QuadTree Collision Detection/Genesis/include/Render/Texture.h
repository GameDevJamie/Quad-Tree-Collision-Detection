#pragma once

#include "..\Asset.h"
#include <string>

namespace Genesis
{
	namespace render
	{
		class Texture : public Asset
		{
			public:
				virtual ~Texture() {}
		};
	}
}