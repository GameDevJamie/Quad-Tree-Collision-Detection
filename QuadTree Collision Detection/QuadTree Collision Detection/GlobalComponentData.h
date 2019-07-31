#pragma once

#include <Genesis.h>

using namespace Genesis;
using namespace Genesis::entity;

class GlobalComponentData : public ComponentData
{
	private:
		std::shared_ptr<render::GUIBar> mp_GUIBar;
		std::unique_ptr<math::QuadTree<TEntityUID>> mp_QuadTree;

		//Spawn and Movement Zones
		math::Vector3 m_MinSpawn, m_MaxSpawn;

	public:
		GlobalComponentData(std::shared_ptr<render::GUIBar> guiBar)
		{
			mp_GUIBar = guiBar;
			mp_QuadTree = std::make_unique<math::QuadTree<TEntityUID>>(math::Vector2::kZero, 50.0f * 2.0f, 8, 2);
		}
		~GlobalComponentData()
		{
			mp_GUIBar.reset();
			mp_QuadTree.reset(nullptr);
		}

		std::shared_ptr<render::GUIBar> GetGUIBar() { return mp_GUIBar; }
		math::QuadTree<TEntityUID>* GetQuadTree() { return mp_QuadTree.get(); }
		inline math::Vector3 GetMinSpawn() const { return m_MinSpawn; }
		inline math::Vector3 GetMaxSpawn() const { return m_MaxSpawn; }


		void SetSize(const TFloat32& size)
		{
			mp_QuadTree->SetSize(size * 2.0f);

			m_MinSpawn = math::Vector3::kOne * -(size - 5.0f);
			m_MinSpawn.y = 0.0f;
			m_MaxSpawn = math::Vector3::kOne * (size - 5.0f);
			m_MaxSpawn.y = 0.0f;
		}
};