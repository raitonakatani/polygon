#include "stdafx.h"
#include "EnemyPath.h"

void EnemyPath::Init(const char* filePath)
{
	//���x�����\�z����B
	m_level.Init(filePath, [&](LevelObjectData& objData)
		{
			if (objData.ForwardMatchName(L"path") == true)
			{
				// �i���o�[��ݒ肷��
				m_point.s_number = objData.number;
				// ���W��ݒ肷��
				m_point.s_position = objData.position;
				m_point.s_paintposi[0] = Vector3{ 0.0f,180.0f,0.0f };
				m_point.s_paintposi[1] = Vector3{ 0.0f,235.0f,0.0f };
				m_point.s_paintposi[2] = Vector3{ 0.0f,290.0f,0.0f };
				m_point.s_paintposi[3] = Vector3{ 0.0f,345.0f,0.0f };
				m_point.s_paintposi[4] = Vector3{ 0.0f,400.0f,0.0f };

				int number = objData.number;
				//�V�����v�f��}��
				m_pointlist.emplace(number, m_point);
				return true;
			}
			return true;
		});
}