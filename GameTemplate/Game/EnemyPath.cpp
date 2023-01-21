#include "stdafx.h"
#include "EnemyPath.h"

void EnemyPath::Init(const char* filePath)
{
	m_level.Init(filePath, [&](LevelObjectData& objData)
		{
			if (objData.ForwardMatchName(L"path") == true)
			{

				m_point.s_number = objData.number;
				m_point.s_position = objData.position;
				m_point.s_paintposi[0] = Vector3{ 0.0f,250.0f,0.0f };
				m_point.s_paintposi[1] = Vector3{ 0.0f,350.0f,0.0f };
				m_point.s_paintposi[2] = Vector3{ 0.0f,550.0f,0.0f };
				m_point.s_paintposi[3] = Vector3{ 0.0f,750.0f,0.0f };

				int number = objData.number;
				m_pointlist.emplace(number, m_point);
				return true;
			}
			return true;
		});
}