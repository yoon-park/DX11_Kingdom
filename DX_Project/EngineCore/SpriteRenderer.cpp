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
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� �����Ϸ� �߽��ϴ�.");
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