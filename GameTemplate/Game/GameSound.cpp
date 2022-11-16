#include "stdafx.h"
#include "GameSound.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

namespace
{
	const int PRIORITY = 0;								//�v���C�I���e�B �D�挠
}


bool GameSound::Start()
{
	// �T�E���h��ǂݍ��ށB
	// �v���C���[
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/footsteps.wav");
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/attack.wav");

	return true;
}

void GameSound::PlayerStepSE(float volume)
{
	// �v���C���[�N���X
	// ����
	SoundSource* stepse = NewGO<SoundSource>(PRIORITY);
	stepse->Init(0);
	stepse->Play(false);
	stepse->SetVolume(volume);
}

void GameSound::PlayerAttackSE(float volume)
{
	// �v���C���[�N���X
	// ����
	SoundSource* stepse = NewGO<SoundSource>(PRIORITY);
	stepse->Init(1);
	stepse->Play(false);
	stepse->SetVolume(volume);
}
