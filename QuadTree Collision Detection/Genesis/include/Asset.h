#pragma once

//Any file type that can be loaded and used multiple times is considered an Asset
//E.g. Mesh, Audio Clips, Shaders, Materials
//Materials do not contain a File, but can be shared between models, so is considered an Asset

#include <string>

namespace Genesis
{
	class Asset
	{
		protected:
			std::string m_Name;			//Name given to asset when loaded
			std::string m_FileName;	//The name of the file
			std::string m_FilePath;	//Full Path of the file

		public:
			//Constructors
			//----------------------------------

			//For Assets with no files
			Asset()
			{
				m_Name = "";
				m_FileName = "";
				m_FilePath = "";
			}
			Asset(const std::string& name)
			{
				m_Name = name;
				m_FileName = "";
				m_FilePath = "";
			}
			Asset(const std::string& name, const std::string& fileName, const std::string& filePath)
			{
				m_Name = name;
				m_FileName = fileName;
				m_FilePath = filePath;
			}

			//----------------------------------

			//ACCESSORS
			//----------------------------------

			inline std::string GetName() const { return m_Name; }
			inline std::string GetFileName() const { return m_FileName; }
			inline std::string GetFilePath() const { return m_FilePath; }

			//----------------------------------
	};
}