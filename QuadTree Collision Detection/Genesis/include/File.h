#pragma once

#include <string>

namespace Genesis
{
	namespace file
	{
		//Returns the Full File Path for where the given File is located.
		//Uses the startingDirectory as the starting folder
		std::string GetFilePath(const std::string& startingDirectory, const std::string& fileName);

		//Returns the Full File Path for where the given File is located.
		//Uses default Starting Path in Defines.h
		std::string GetFilePath(const std::string& fileName);
	}
}