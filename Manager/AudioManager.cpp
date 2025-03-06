#include "AudioManager.h"
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")

std::map<AudioType, const WCHAR*> dataMap = {
	{AudioType::TitleBackground, TEXT("Assets/Audio/Title.wav")},
	{AudioType::PresetBackground, TEXT("Assets/Audio/Preset.wav")},
	{AudioType::PlayBackground, TEXT("Assets/Audio/Play.wav")},
	{AudioType::EndBackground, TEXT("Assets/Audio/End.wav")},
};


// Loop
void AudioManager::PlayLoop(AudioType AudioType) {

	if (!dataMap.contains(AudioType)) {
		return;
		//std::cout << ( int ) AudioType << "의 오디오 데이터가 테이블에 존재하지 않습니다..\n";
	}
	
	const WCHAR* fileName = dataMap.at(AudioType);
	PlaySound(fileName, 0, SND_FILENAME | SND_LOOP | SND_NOWAIT | SND_ASYNC);
}


void AudioManager::StopLoop() {
	PlaySound(nullptr, nullptr, 0);
}