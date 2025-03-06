#pragma once

#include <map>
#include "AbstractClass/Singleton.h"
#include <Windows.h>

enum class AudioType {
	TitleBackground,
	PresetBackground,
	PlayBackground,
	EndBackground,
};

extern std::map<AudioType, const WCHAR*> dataMap;

class AudioData {

};

class AudioManager : public Singleton<AudioManager> {

public:
	void PlayLoop(AudioType AudioType);
	void StopLoop();
};