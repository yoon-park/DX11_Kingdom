#pragma once
#include "EngineResources.h"

enum class EImageLoadType
{
	IMG_Folder,
	IMG_Cutting,
};

enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

class UImageInfo 
{
public:
	HBITMAP hBitMap;
	HDC ImageDC = nullptr;
	FTransform CuttingTrans;
	UImageInfo* RotationMaskImage = nullptr;
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
};

class UEngineWindow;

class UWindowImage : public UEngineResources<UWindowImage>
{
	friend UEngineWindow;

public:
	UWindowImage();
	~UWindowImage();

	UWindowImage(const UWindowImage& _Other) = delete;
	UWindowImage(UWindowImage&& _Other) noexcept = delete;
	UWindowImage& operator=(const UWindowImage& _Other) = delete;
	UWindowImage& operator=(UWindowImage&& _Other) noexcept = delete;

	HDC GetImageDC()
	{
		return ImageDC;
	}

	EWIndowImageType GetImageType()
	{
		return ImageType;
	}

	const UImageInfo& ImageInfo(int _Index)
	{
		if (_Index >= Infos.size())
		{
			MsgBoxAssert("커팅된 것보다 더 큰 이미지 인덱스를 사용하려 했습니다.");
		}

		return Infos[_Index];
	}

	FVector GetScale();
	Color8Bit GetColor(int _X, int _Y, Color8Bit _DefaultColor);

	void SetCuttingTransform(const FTransform& _CuttingTrans, int _Index = 0);

	void SetRotationMaskImage(int _Index, std::shared_ptr<UWindowImage> _RotationMaskImage, int _MaskIndex)
	{
		UImageInfo& Ref = _RotationMaskImage->Infos[_MaskIndex];
		Infos[_Index].RotationMaskImage = &Ref;
	}

	void SetRotationMaskImageFolder(std::shared_ptr<UWindowImage> _RotationMaskImage)
	{
		if (Infos.size() != _RotationMaskImage->Infos.size())
		{
			MsgBoxAssert("이미지정보의 사이즈가 다른 이미지끼리 매칭할 수 없습니다.");
			return;
		}

		for (int i = 0; i < static_cast<int>(Infos.size()); i++)
		{
			SetRotationMaskImage(i, _RotationMaskImage, i);
		}
	}

	bool Load(std::shared_ptr<UWindowImage> _Image);
	bool LoadFolder(std::shared_ptr<UWindowImage> _Image);

	bool Create(std::shared_ptr<UWindowImage> _Image, const FVector& _Scale);
	void Cutting(int _X, int _Y);

	void BitCopy(std::shared_ptr<UWindowImage> _CopyImage, const FTransform& _Trans);
	void TransCopy(std::shared_ptr<UWindowImage> _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Black);
	void AlphaCopy(std::shared_ptr<UWindowImage> _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Black);
	void PlgCopy(std::shared_ptr<UWindowImage> _CopyImage, const FTransform& _Trans, int _Index, float _RadAngle);

	void TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color /*= Color8Bit::Black*/);
	void TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _OutLineColor, Color8Bit _FillColor);
	void TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Gdiplus::StringAlignment _SortOption1, Gdiplus::StringAlignment _SortOption2, Color8Bit _FillColor);
	void TextCopyBold(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color /*= Color8Bit::Black*/);
	void TextCopyFormat(const std::string& _Text, const std::string& _Font, const Gdiplus::StringFormat& stringFormat, float _Size, const FTransform& _Trans, Color8Bit _Color /*= Color8Bit::Black*/);

	void DrawRectangle(const FTransform& _Trans);
	void DrawEllipse(const FTransform& _Trans);

	void TextPrint(std::string_view _Text, FVector _Pos);

protected:

private:
	EImageLoadType LoadType = EImageLoadType::IMG_Cutting;
	HBITMAP hBitMap = 0;
	HDC ImageDC = 0;
	BITMAP BitMapInfo = BITMAP();
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;

	std::vector<UImageInfo> Infos;

	bool Create(HDC _MainDC);
};