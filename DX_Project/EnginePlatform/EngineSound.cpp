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
			MsgBoxAssert("����ý��� ������ �����߽��ϴ�.");
			return;
		}

		if (FMOD_RESULT::FMOD_OK != SoundSystem->init(32, FMOD_DEFAULT, nullptr))
		{
			MsgBoxAssert("����ý��� ������ �����߽��ϴ�.");
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
		MsgBoxAssert("�̹� �ε�� ���带 �ٽ� �ε��Ϸ� �߽��ϴ�. : " + UpperName);
		return;
	}

	std::shared_ptr<UEngineSound> NewSound = CreateResName(_Path, _Name);
	NewSound->ResLoad(_Path);
}

void UEngineSound::Update()
{
	if (SoundSystem == nullptr)
	{
		MsgBoxAssert("����ý��ۿ� ġ������ ������ �ֽ��ϴ�.");
	}

	SoundSystem->update();
}

UEngineSoundPlayer UEngineSound::SoundPlay(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (IsRes(UpperName.c_str()) == false)
	{
		MsgBoxAssert("�ε���� ���� ���带 ����Ϸ��� �߽��ϴ�. : " + UpperName);
		return UEngineSoundPlayer();
	}

	std::shared_ptr <UEngineSound> FindSound = FindRes(UpperName);

	UEngineSoundPlayer Result;
	SoundSystem->playSound(FindSound->SoundHandle, nullptr, false, &Result.Control);
	Result.Control->setLoopCount(0);
	Result.SetVolume(1.0f);

	if (Result.Control == nullptr)
	{
		MsgBoxAssert("���� ����� ���� ��������� �������� ���߽��ϴ�.");
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
		MsgBoxAssert("���� �ε忡 �����߽��ϴ�. : " + std::string(_Path));
		return;
	}

	//SoundSystem->playSound(SoundHandle, nullptr, false, nullptr);
}