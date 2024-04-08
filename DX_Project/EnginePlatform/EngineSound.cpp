#include "PreCompile.h"
#include "EngineSound.h"

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

FMOD::System* SoundSystem = nullptr;

class ResControl
{
public:
	ResControl()
	{
		if (FMOD_RESULT::FMOD_OK != FMOD::System_Create(&SoundSystem))
		{
			MsgBoxAssert("사운드시스템 생성에 실패했습니다.");
			return;
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("사운드시스템 생성에 실패했습니다.");
			return;
		}
	}

	~ResControl()
	{
		if (SoundSystem != nullptr)
		{
			SoundSystem->release();
			SoundSystem = nullptr;
		}
	}
};

ResControl Inst;

void UEngineSoundPlayer::SetVolume(float _Volume)
{
	Control->setVolume(_Volume * UEngineSound::GlobalVolume);
}

float UEngineSound::GlobalVolume = 1.0f;

void UEngineSound::SetGlobalVolume(float _Value)
{
	GlobalVolume = _Value;

	if (GlobalVolume <= 0.0f)
	{
		GlobalVolume = 0.0f;
	}

	if (GlobalVolume >= 1.0f)
	{
		GlobalVolume = 1.0f;
	}
}

void UEngineSound::Load(std::string_view _Path, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (IsRes(UpperName) == true)
	{
		MsgBoxAssert("이미 로드된 사운드를 다시 로드하려 했습니다. : " + UpperName);
		return;
	}

	std::shared_ptr<UEngineSound> NewSound = CreateResName(_Path, _Name);
	NewSound->ResLoad(_Path);
}

void UEngineSound::Update()
{
	if (SoundSystem == nullptr)
	{
		MsgBoxAssert("사운드시스템에 치명적인 오류가 있습니다.");
	}

	SoundSystem->update();
}

UEngineSoundPlayer UEngineSound::SoundPlay(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (IsRes(UpperName.c_str()) == false)
	{
		MsgBoxAssert("로드되지 않은 사운드를 재생하려고 했습니다. : " + UpperName);
		return UEngineSoundPlayer();
	}

	std::shared_ptr <UEngineSound> FindSound = FindRes(UpperName);

	UEngineSoundPlayer Result;
	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Result.Control);
	Result.Control->setLoopCount(0);
	Result.SetVolume(1.0f);

	if (Result.Control == nullptr)
	{
		MsgBoxAssert("사운드 재생에 대한 제어권한을 가져오지 못했습니다.");
		return Result;
	}

	return Result;
}

UEngineSound::UEngineSound()
{

}

UEngineSound::~UEngineSound()
{

}

void UEngineSound::ResLoad(std::string_view _Path)
{
	SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);
	
	if (SoundHandle == nullptr)
	{
		MsgBoxAssert("사운드 로드에 실패했습니다. : " + std::string(_Path));
		return;
	}

	//SoundSystem->playSound(SoundHandle, nullptr, false, nullptr);
}