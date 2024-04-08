#include "PreCompile.h"
#include "SpriteRenderer.h"

#include "EngineShaderResources.h"
#include "EngineSprite.h"

USpriteRenderer::USpriteRenderer()
{
	SetMesh("Rect");
	SetMaterial("2DImage");
	Resources->SettingTexture("Image", "EngineBaseTexture.png", "POINT");
	CurTexture = nullptr;
	Resources->SettingConstantBuffer("ResultColorValue", PlusColor);
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
	CurTexture = Info.Texture;

	Resources->SettingTexture("Image", Info.Texture, "POINT");
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