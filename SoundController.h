#pragma once
#include "SingletonBase.h"

#define SOUNDBUFFER (int)snd::__max_count


class SoundController :
	public SingletonBase<SoundController>
{
private:
	typedef vector<snd>			vSound;
	typedef vector<snd>			vChannel;
	typedef vSound::iterator	vSound_it;
	typedef vChannel::iterator	vChannel_it;

	System* fmod_system;
	Sound** soundList;
	Channel** channel;

	vSound totalSounds;

	DSP *dsp = NULL;
public:
	SoundController();
	~SoundController();

	void Init();
	void Release();
	void Update();

	void AddSound(snd sound, string fname, bool stream, bool isLoop);
	void Play(snd sound, float volume = 1.0f);
	void Stop(snd sound);
	void Pause(snd sound);
	void Resume(snd sound);

	void SetSoundFrequency(snd sound, float frequency);

	bool isPlaying(snd sound);
	bool isPaused(snd sound);

	void DspHighpassSetting(snd sound);
	void DspSetHighpass(float amount = 5000.0f);
};