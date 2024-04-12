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
		MsgBoxAssert("존재하지 않는 스프라이트를 세팅하려 했습니다.");
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
		MsgBoxAssert("텍스처가 세팅되어 있지 않은 상태에 샘플링부터 바꿀 수는 없습니다.");
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
		MsgBoxAssert("스프라이트가 존재하지 않아 애니메이션을 만들 수 없습니다.");
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
		MsgBoxAssert("애니메이션을 역방향으로 생성할 수 없습니다.");
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
		MsgBoxAssert("이미 존재하는 이름의 애니메이션을 만들 수 없습니다.");
		return;
	}

	std::shared_ptr<UEngineSprite> FindSprite = UEngineSprite::FindRes(_SpriteName);

	if (FindSprite == nullptr)
	{
		MsgBoxAssert("스프라이트가 존재하지 않아 애니메이션을 만들 수 없습니다.");
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
		MsgBoxAssert("존재하지 않는 애니메이션으로 변경할 수 없습니다. : " + std::string(_AnimationName));
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