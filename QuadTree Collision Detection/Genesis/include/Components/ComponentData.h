#pragma once

#include "..\Defines.h"

namespace Genesis
{
	namespace entity
	{
		inline TComponentID GetComponentTypeId()
		{
			static TComponentID id = 1;
			return id++;
		}

		template<typename T>
		inline TComponentID GetComponentTypeId()
		{
			if (!std::is_base_of<ComponentData, T>()) return INVALID_COMPONENT;

			static TComponentID typeId = GetComponentTypeId();
			return typeId;
		}


		class ComponentData
		{
			private:
				bool m_IsEnabled;

			public:
				ComponentData() { m_IsEnabled = true; }
				virtual ~ComponentData() {}

				bool IsEnabled() { return m_IsEnabled; }
				void IsEnabled(bool enabled) { m_IsEnabled = enabled; }
		};
	}
}