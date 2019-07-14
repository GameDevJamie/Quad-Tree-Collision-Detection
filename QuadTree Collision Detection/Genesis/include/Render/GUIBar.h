/**********************************
@File: GUIBar.h

@Summary: -An Editor style GUI Bar, to allow editing of variables in real time
					-Mostly suited for demo purposes
					-Can be created via the RenderEngine

					var def types:
					-group: Adds the added variable to a group
					-min / max: Set a minimum and maximum value of a numerical variable.
				  -step: Set a step value for a numerical variable
					-visible: Show or hide variable

***********************************/

#pragma once

#include "..\Math\Vector3.h"
#include <string>

namespace Genesis
{
	namespace render
	{
		class GUIBar
		{
			public:
				virtual ~GUIBar() {}

				//EDITOR BAR SETTERS
				//-------------------------------

				virtual void SetAlpha(const TInt32&) = 0;
				virtual void SetColour(const math::Vector3&) = 0;
				virtual void SetTitle(const std::string&) = 0;

				virtual void IsVisible(bool) = 0;

				//-------------------------------


				//EDITOR BAR GETTERS
				//-------------------------------

				virtual inline bool IsVisible() = 0;

				//The name of the GUI Bar
				virtual inline std::string GetName() = 0;

				//-------------------------------
				

				//FUNCTIONS FOR ADDING DIFFERENT PARTS TO THE EDITOR BAR
				//THE ORDER CALLED DETERMINES THEIR POSITION IN THE BAR
				//-----------------------------------------

				virtual bool AddButton(const char* name, GUIButtonCallback, void* clientData, const char* def = "") = 0;
				virtual bool AddVarRW(const char* name, const EType&, void* var, const char* def = "") = 0;
				virtual bool AddSeperator(const char* name, const char* def) = 0;
				
				//-----------------------------------------

				//Define optional paramters for this GUI Bar
				//Returns true on success
				virtual bool DefineBar(const std::string& def) = 0;

				//Define optional paramters for the given variable (Must have first been created)
				//Returns true on success
				virtual bool DefineVAR(const std::string& name, const std::string& def) = 0;
		};
	}
}