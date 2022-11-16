#include "stdafx.h"
#include "GameSound.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

namespace
{
	const int PRIORITY = 0;								//プライオリティ 優先権
}


bool GameSound::Start()
{
	// サウンドを読み込む。
	// プレイヤー
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/footsteps.wav");
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/attack.wav");

	return true;
}

void GameSound::PlayerStepSE(float volume)
{
	// プレイヤークラス
	// 足音
	SoundSource* stepse = NewGO<SoundSource>(PRIORITY);
	stepse->Init(0);
	stepse->Play(false);
	stepse->SetVolume(volume);
}

void GameSound::PlayerAttackSE(float volume)
{
	// プレイヤークラス
	// 足音
	SoundSource* stepse = NewGO<SoundSource>(PRIORITY);
	stepse->Init(1);
	stepse->Play(false);
	stepse->SetVolume(volume);
}
