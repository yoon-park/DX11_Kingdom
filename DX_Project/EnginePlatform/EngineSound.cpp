#include "PreCompile.h"
#include "EngineSound.h"

#ifdef _DEBUG
// Debug
#pragma comment(lib, "fmodL_vc.lib")
#else
// Release
#pragma comment(lib, "fmod_vc.lib")
#endif

FMOD::System* SoundSystem = nullptr;

class ResControl
{
public:
	ResControl()
	{
		if (FMOD::System_Create(&SoundSystem) != FMOD_RESULT::FMOD_OK)
		{
			MsgBoxAssert("사운드시스템 생성에 실패했습니다.");
			return;
		}

		if (SoundSystem->init(32, FMOD_DEFAULT, nullptr) != FMOD_RESULT::FMOD_OK)
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
		MsgBoxAssert("이미 로드한 사운드를 다시 로드하려 했습니다.");
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
		MsgBoxAssert("로드하지 않은 사운드를 재생하려 했습니다. : " + UpperName);
		return UEngineSoundPlayer();
	}

	std::shared_ptr <UEngineSound> FindSound = FindRes(UpperName);
	UEngineSoundPlayer Result;
	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Result.Control);
	Result.Control->setLoopCount(0);
	Result.SetVolume(1.0f);

	if (Result.Control == nullptr)
	{
		MsgBoxAssert("사운드재생에 대한 제어 권한을 가져오지 못했습니다.");
		return Result;
	}

	return Result;
}

void UEngineSound::ResLoad(std::string_view _Path)
{
	SoundSystem->createSound(_Path.data(), FMOD_LOOP_NORMAL, nullptr, &SoundHandle);

	if (SoundHandle == nullptr)
	{
		MsgBoxAssert("사운드 로드에 실패했습니다. : " + std::string(_Path));
		return;
	}
}

void UEngineSoundPlayer::SetVolume(float _Volume)
{
	Control->setVolume(_Volume * UEngineSound::GlobalVolume);
}

UEngineSound::UEngineSound() 
{

}

UEngineSound::~UEngineSound() 
{

}