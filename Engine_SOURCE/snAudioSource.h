#pragma once
#include "snComponent.h"
#include "snAudioClip.h"

namespace sn
{
	class AudioSource : public Component
	{
	public:
		AudioSource();
		~AudioSource();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Play();
		void Stop();
		void SetLoop(bool loop);
		void SetVolume(int _i) { mAudioClip->SetVolume(_i); }
		void VolumeDown(int _i) { mAudioClip->VolumeDown(_i); }

		void SetClip(std::shared_ptr<AudioClip> clip) { mAudioClip = clip; }
		std::shared_ptr<AudioClip> GetClip() { return mAudioClip; }

	private:
		std::shared_ptr<AudioClip> mAudioClip;
	};
}
