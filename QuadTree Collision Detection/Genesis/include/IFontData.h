#pragma once

/*
	SUMMARY:
	-Contains information/data about a Font file
	-Used primarly with the TextComponentData, to help display text in the Scene

	-To be used in conjuction with a Texture Atlas, containing the Font letters
*/

#include "Defines.h"

#include <string>

namespace Genesis
{
	namespace render
	{
		enum class ETextAlignment
		{
			LEFT,	//Default
			RIGHT,	//TODO
			CENTER,
			JUSTIFIED	//TODO
		};

		class IFontData
		{
			public:
				virtual ~IFontData() {}

				//ACCESSORS
				//------------------------------

				//Name of mesh given when loaded
				virtual std::string GetName() const = 0;

				//Name of mesh file
				virtual std::string GetFileName() const = 0;

				virtual TUInt32 GetVertexSize() const = 0;
				virtual TUInt32 GetVertexCount() const = 0;
				virtual TUInt32 GetIndexCount() const = 0;
				//------------------------------
		};
	}
}