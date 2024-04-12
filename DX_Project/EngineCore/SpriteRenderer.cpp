#include "PreCompile.h"
#include "SpriteRenderer.h"

#include "EngineShaderResources.h"

void USpriteAnimation::Update(float _DeltaTime)
{
	CurTime += _DeltaTime;

	if (CurTime > Inter[CurFrame])
	{
		CurTime -= Inter[CurFrame];
		++CurFrame;

		if (Frame.size() <= CurFrame)
		{
			if (Loop == true)
			{
				CurFrame = 0;
			}
			else
			{
				--CurFrame;
			}
		}
	}
}

USpriteRenderer::USpriteRenderer()
{
	SetMesh("Rect");
	SetMaterial("2DImage");
	Resources->SettingTexture("Image", "EngineBaseTexture.png", "POINT");
	CurTexture = nullptr;
	Resources->SettingConstantBuffer("ResultColorValue", PlusColor);
	Resources->SettingConstantBuffer("FCuttingData", CuttingDataValue);
}

USpriteRenderer::~USpriteRenderer()
{

}

void USpriteRenderer::SetSprite(std::string_view _Name, UINT _Index/* = 0*/)
{
	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes(_Name);

	if (Sprite == nullptr)
	{
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� �����Ϸ� �߽��ϴ�.");
		return;
	}

	FSpriteInfo Info = Sprite->GetSpriteInfo(_Index);
	SetSpriteInfo(Info);
}

void USpriteRenderer::SetPlusColor(float4 _Color)
{
	PlusColor = _Color;
}

void USpriteRenderer::SetSamplering(ETextureSampling _Value)
{
	if (CurTexture == nullptr)
	{
		MsgBoxAssert("�ؽ�ó�� ���õǾ� ���� ���� ���¿� ���ø����� �ٲ� ���� �����ϴ�.");
		return;
	}

	switch (_Value)
	{
	case ETextureSampling::NONE:
		break;
	case ETextureSampling::LINEAR:
	{
		Resources->SettingTexture("Image", CurTexture, "LINEAR");
		break;
	}
	case ETextureSampling::POINT:
	{
		Resources->SettingTexture("Image", CurTexture, "POINT");
		break;
	}
	default:
		break;
	}
}

void USpriteRenderer::SetAutoSize(float _ScaleRatio, bool _AutoSize)
{
	AutoSize = _AutoSize;
	ScaleRatio = _ScaleRatio;

	if (AutoSize == true && CurInfo.Texture != nullptr)
	{
		SetSpriteInfo(CurInfo);
	}
}

void USpriteRenderer::SetSpriteInfo(const FSpriteInfo& _Info)
{
	CuttingDataValue.CuttingPosition = _Info.CuttingPosition;
	CuttingDataValue.CuttingSize = _Info.CuttingSize;
	CurTexture = _Info.Texture;

	if (AutoSize == true)
	{
		float4 TexScale = _Info.Texture->GetScale();
		Transform.SetScale(TexScale * CuttingDataValue.CuttingSize * ScaleRatio);
	}

	if (Dir != EEngineDir::MAX)
	{
		float4 Scale = Transform.GetScale();

		switch (Dir)
		{
		case EEngineDir::Left:
		{
			if (Scale.X > 0)
			{
				Scale.X = -Scale.X;
			}
			break;
		}
		case EEngineDir::Right:
		{
			if (Scale.X < 0)
			{
				Scale.X = -Scale.X;
			}
			break;
		}
		case EEngineDir::MAX:
		default:
			break;
		}

		Transform.SetScale(Scale);
	}

	CurInfo = _Info;

	Resources->SettingTexture("Image", _Info.Texture, "POINT");
	SetSamplering(SamplingValue);
}

void USpriteRenderer::SetDir(EEngineDir _Dir)
{
	Dir = _Dir;

	if (CurInfo.Texture != nullptr)
	{
		SetSpriteInfo(CurInfo);
	}
}

void USpriteRenderer::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter,
	bool _Loop /*= true*/,
	int _Start /*= -1*/,
	int _End /*= -1*/)
{
	std::shared_ptr<UEngineSprite> FindSprite = UEngineSprite::FindRes(_SpriteName);

	if (FindSprite == nullptr)
	{
		MsgBoxAssert("��������Ʈ�� �������� �ʾ� �ִϸ��̼��� ���� �� �����ϴ�.");
		return;
	}

	std::vector<int> Frame;
	std::vector<float> Inter;

	int Start = _Start;
	int End = _End;

	if (_Start < 0)
	{
		Start = 0;
	}

	if (End < 0)
	{
		End = static_cast<int>(FindSprite->GetInfoSize()) - 1;
	}

	if (_Start > _End)
	{
		MsgBoxAssert("�ִϸ��̼��� ���������� ������ �� �����ϴ�.");
		return;
	}

	for (int i = 0; i < End; i++)
	{
		Inter.push_back(_Inter);
		Frame.push_back(i);
	}

	CreateAnimation(_AnimationName, _SpriteName, Inter, Frame, _Loop);
}

void USpriteRenderer::CreateAnimation(
	std::string_view _AnimationName, 
	std::string_view _SpriteName, 
	std::vector<float> _Inter, 
	std::vector<int> _Frame, 
	bool _Loop /*= true*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (Animations.contains(UpperName) == true)
	{
		MsgBoxAssert("�̹� �����ϴ� �̸��� �ִϸ��̼��� ���� �� �����ϴ�.");
		return;
	}

	std::shared_ptr<UEngineSprite> FindSprite = UEngineSprite::FindRes(_SpriteName);

	if (FindSprite == nullptr)
	{
		MsgBoxAssert("��������Ʈ�� �������� �ʾ� �ִϸ��̼��� ���� �� �����ϴ�.");
		return;
	}

	std::shared_ptr<USpriteAnimation> NewAnimation = std::make_shared<USpriteAnimation>();
	NewAnimation->Sprite = FindSprite;
	NewAnimation->Inter = _Inter;
	NewAnimation->Frame = _Frame;
	NewAnimation->Loop = _Loop;
	NewAnimation->Reset();

	Animations[UpperName] = NewAnimation;
}

void USpriteRenderer::ChangeAnimation(std::string_view _AnimationName)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (Animations.contains(UpperName) == false)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ������ �� �����ϴ�. : " + std::string(_AnimationName));
		return;
	}

	CurAnimation = Animations[UpperName];
}

void USpriteRenderer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (CurAnimation != nullptr)
	{
		CurAnimation->Update(_DeltaTime);

		FSpriteInfo Info = CurAnimation->GetCurSpriteInfo();
		SetSpriteInfo(Info);
	}
}