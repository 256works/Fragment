#include "stdafx.h"
#include "SoundController.h"


SoundController::SoundController()
{
}


SoundController::~SoundController()
{
}

void SoundController::Init()
{
	System_Create(&fmod_system);
	fmod_system->init(SOUNDBUFFER, FMOD_INIT_NORMAL, NULL);
	soundList = new Sound*[SOUNDBUFFER];
	channel = new Channel*[SOUNDBUFFER];

	memset(soundList, 0, sizeof(Sound*) * SOUNDBUFFER);
	memset(channel, 0, sizeof(Channel*) * SOUNDBUFFER);

}

void SoundController::Release()
{
	dsp->release();
	fmod_system->release();
	fmod_system->close();
}

void SoundController::Update()
{
}

void SoundController::AddSound(snd sound, string fname, bool stream, bool isLoop)
{
	if (isLoop)
	{
		if (stream)
		{
			fmod_system->createStream(fname.c_str(), FMOD_LOOP_NORMAL, NULL, &soundList[totalSounds.size()]);
		}
		else
		{
			fmod_system->createSound(fname.c_str(), FMOD_LOOP_NORMAL, NULL, &soundList[totalSounds.size()]);
		}
	}
	else
	{
		if (stream)
		{
			fmod_system->createStream(fname.c_str(), FMOD_DEFAULT, NULL, &soundList[totalSounds.size()]);
		}
		else
		{
			fmod_system->createSound(fname.c_str(), FMOD_DEFAULT, NULL, &soundList[totalSounds.size()]);
		}
	}
	totalSounds.push_back(sound);
}

void SoundController::Play(snd sound, float volume)
{
	Stop(sound);

	for (unsigned int cnt = 0; cnt < totalSounds.size(); ++cnt)
	{
		if (totalSounds.at(cnt) == sound && !SOUND_MUTE)
		{
			fmod_system->playSound(FMOD_CHANNEL_FREE, soundList[cnt], false, &channel[cnt]);
			channel[cnt]->setVolume(volume);
			break;
		}
	}
}

void SoundController::Stop(snd sound)
{
	for (unsigned int cnt = 0; cnt < totalSounds.size(); ++cnt)
	{
		if (totalSounds.at(cnt) == sound)
		{
			channel[cnt]->stop();
			break;
		}
	}
}

void SoundController::Pause(snd sound)
{
	for (unsigned int cnt = 0; cnt < totalSounds.size(); ++cnt)
	{
		if (totalSounds.at(cnt) == sound)
		{
			channel[cnt]->setPaused(true);
			break;
		}
	}
}

void SoundController::Resume(snd sound)
{
	for (unsigned int cnt = 0; cnt < totalSounds.size(); ++cnt)
	{
		if (totalSounds.at(cnt) == sound)
		{
			channel[cnt]->setPaused(false);
			break;
		}
	}
}

void SoundController::SetSoundFrequency(snd sound, float frequency)
{
	channel[(int)sound]->setFrequency(frequency);
}

bool SoundController::isPlaying(snd sound)
{
	bool isPlay = false;

	for (unsigned int cnt = 0; cnt < totalSounds.size(); ++cnt)
	{
		if (totalSounds.at(cnt) == sound)
		{
			channel[cnt]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool SoundController::isPaused(snd sound)
{
	bool isPause = false;

	for (unsigned int cnt = 0; cnt < totalSounds.size(); ++cnt)
	{
		if (totalSounds.at(cnt) == sound)
		{
			channel[cnt]->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}

void SoundController::DspHighpassSetting(snd sound)
{
	if (dsp == NULL)
	{
		fmod_system->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &dsp);
		dsp->setActive(true);
		dsp->setBypass(false);
		channel[(int)sound]->addDSP(dsp, NULL);
	}
}

void SoundController::DspSetHighpass(float amount)
{
	dsp->setParameter(FMOD_DSP_HIGHPASS_CUTOFF, amount);
}
