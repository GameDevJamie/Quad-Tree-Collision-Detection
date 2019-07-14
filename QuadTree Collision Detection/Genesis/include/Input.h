#pragma once

#include "Math\Vector2.h"
#include "KeyCodes.h"

namespace Genesis
{
	namespace input
	{
		math::Vector2 MousePosition();

		//Check if the given key has been pressed
		bool IsKeyDown(const EKeyCode& key);

		//Check if the given key is currently being held down
		bool IsKeyHeld(const EKeyCode& key);

		//Lock the given key and prevent pressed/held events
		void LockKey(const EKeyCode& key);

		//Unlock the given key and allow pressed/held events
		void UnLockKey(const EKeyCode& key);
	}

	namespace system
	{
		TFloat32 DeltaTime();

		math::Vector2 ScreenResolution();
	}
}