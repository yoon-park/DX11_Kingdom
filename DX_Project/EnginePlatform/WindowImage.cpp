#include "WindowImage.h"

#include <Windows.h>

#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Gdiplus.lib")

UWindowImage::UWindowImage()
{

}

UWindowImage::~UWindowImage()
{
	switch (LoadType)
	{
	case EImageLoadType::IMG_Folder:
	{
		for (size_t i = 0; i < Infos.size(); i++)
		{
			DeleteObject(Infos[i].hBitMap);
			DeleteDC(Infos[i].ImageDC);
		}
		break;
	}
	case EImageLoadType::IMG_Cutting:
		DeleteObject(hBitMap);
		DeleteDC(ImageDC);
		break;
	default:
		break;
	}
}

FVector UWindowImage::GetScale()
{
	return FVector(BitMapInfo.bmWidth, BitMapInfo.bmHeight);
}

void UWindowImage::SetCuttingTransform(const FTransform& _CuttingTrans, int _Index)
{
	Infos[_Index].CuttingTrans = _CuttingTrans;
}

bool UWindowImage::Create(HDC _MainDC)
{
	ImageDC = _MainDC;

	if (ImageDC == nullptr)
	{
		return false;
	}

	return true;
}

bool UWindowImage::Create(std::shared_ptr<UWindowImage> _Image, const FVector& _Scale)
{
	HANDLE ImageHandle = CreateCompatibleBitmap(_Image->ImageDC, _Scale.iX(), _Scale.iY());

	if (ImageHandle == nullptr)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다.");
		return false;
	}

	hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);

	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (ImageDC == nullptr)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다.");
		return false;
	}

	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	return true;
}

bool UWindowImage::Load(std::shared_ptr<UWindowImage> _Image)
{
	LoadType = EImageLoadType::IMG_Cutting;

	UEnginePath Path = GetEnginePath();

	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	if (UpperExt == ".BMP")
	{
		HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
		ImageType = EWIndowImageType::IMG_BMP;
	}
	else if (UpperExt == ".PNG")
	{
		ULONG_PTR gdiplusToken = 0;
		Gdiplus::GdiplusStartupInput gdistartupinput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);

		std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());

		Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
		Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());

		Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitMap);

		if (stat != Gdiplus::Status::Ok)
		{
			MsgBoxAssert(".png 형식 리소스 로드에 실패했습니다.");
		}

		delete pBitMap;
		delete pImage;

		ImageType = EWIndowImageType::IMG_PNG;
	}

	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (ImageDC == nullptr)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다.");
		return false;
	}

	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	UImageInfo Info;
	Info.hBitMap = hBitMap;
	Info.ImageDC = ImageDC;
	Info.CuttingTrans.SetPosition({0,0});
	Info.CuttingTrans.SetScale(GetScale());
	Info.ImageType = ImageType;
	Infos.push_back(Info);

	return true;
}

bool UWindowImage::LoadFolder(std::shared_ptr<UWindowImage> _Image)
{
	LoadType = EImageLoadType::IMG_Folder;

	UEnginePath EnginePath = GetEnginePath();

	if (EnginePath.IsDirectory() == false)
	{
		MsgBoxAssert("디렉토리 경로가 아닌 경로로 폴더를 로드하려고 했습니다");
	}

	UEngineDirectory Dir = EnginePath;

	std::list<UEngineFile> NewList = Dir.AllFile({ ".png", ".bmp" }, false);
	Infos.reserve(NewList.size());

	for (UEngineFile& File : NewList)
	{
		UEnginePath Path = File;

		std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

		if (UpperExt == ".BMP")
		{
			HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
			ImageType = EWIndowImageType::IMG_BMP;
		}
		else if (UpperExt == ".PNG")
		{
			ULONG_PTR gdiplusToken = 0;
			Gdiplus::GdiplusStartupInput gdistartupinput;
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);
			std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());
			Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
			Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());
			Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitMap);

			if (stat != Gdiplus::Status::Ok)
			{
				MsgBoxAssert(".png 형식 리소스 로드에 실패했습니다.");
			}

			delete pBitMap;
			delete pImage;

			ImageType = EWIndowImageType::IMG_PNG;
		}
		ImageDC = CreateCompatibleDC(_Image->ImageDC);

		if (ImageDC == nullptr)
		{
			MsgBoxAssert("이미지 생성에 실패했습니다.");
			return false;
		}

		HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
		DeleteObject(OldBitMap);
		GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

		UImageInfo Info;
		Info.hBitMap = hBitMap;
		Info.ImageDC = ImageDC;
		Info.CuttingTrans.SetPosition({ 0,0 });
		Info.CuttingTrans.SetScale(GetScale());
		Infos.push_back(Info);
	}

	return true;
}

void UWindowImage::BitCopy(std::shared_ptr<UWindowImage> _CopyImage, const FTransform& _Trans)
{
	if (_CopyImage == nullptr)
	{
		MsgBoxAssert("nullptr인 이미지를 복사할 수 없습니다.");
	}

	HDC hdc = ImageDC;
	HDC hdcSrc = _CopyImage->ImageDC;

	BitBlt(
		hdc, 						
		_Trans.iLeft(), 			
		_Trans.iTop(), 				
		_Trans.GetScale().iX(), 	
		_Trans.GetScale().iY(),		
		hdcSrc,						
		0,							
		0,							
		SRCCOPY						
	);
}

void UWindowImage::TransCopy(std::shared_ptr<UWindowImage> _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color)
{
	if (_CopyImage == nullptr)
	{
		MsgBoxAssert("nullptr인 이미지를 복사할 수 없습니다.");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + " : 이미지정보의 인덱스를 초과했습니다.");
	}

	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;

	int RenderLeft = _Trans.iLeft();
	int RenderTop = _Trans.iTop();
	int RenderScaleX = _Trans.GetScale().iX();
	int RenderScaleY = _Trans.GetScale().iY();

	int ImageLeft   = ImageTrans.GetPosition().iX();
	int ImageTop    = ImageTrans.GetPosition().iY();
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();

	HDC hdc = ImageDC;
	HDC hdcSrc = _CopyImage->Infos[_Index].ImageDC;

	TransparentBlt(
		hdc, 			
		RenderLeft, 	
		RenderTop, 		  
		RenderScaleX,	
		RenderScaleY,	
		hdcSrc,			
		ImageLeft,   	
		ImageTop,   	
		ImageScaleX, 	
		ImageScaleY, 	
		_Color.Color	
	);
}

void UWindowImage::AlphaCopy(std::shared_ptr<UWindowImage> _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color)
{
	if (_CopyImage == nullptr)
	{
		MsgBoxAssert("nullptr인 이미지를 복사할 수 없습니다.");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + " : 이미지정보의 인덱스를 초과했습니다.");
	}

	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;

	int RenderLeft = _Trans.iLeft();
	int RenderTop = _Trans.iTop();
	int RenderScaleX = _Trans.GetScale().iX();
	int RenderScaleY = _Trans.GetScale().iY();

	int ImageLeft = ImageTrans.GetPosition().iX();
	int ImageTop = ImageTrans.GetPosition().iY();
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();

	HDC hdc = ImageDC;
	HDC hdcSrc = _CopyImage->Infos[_Index].ImageDC;

	BLENDFUNCTION Function;
	Function.BlendOp = AC_SRC_OVER;
	Function.BlendFlags = 0;
	Function.SourceConstantAlpha = _Color.A;
	Function.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
		hdc, 			
		RenderLeft, 	
		RenderTop, 		
		RenderScaleX,	
		RenderScaleY,	
		hdcSrc,			
		ImageLeft,   	
		ImageTop,   	
		ImageScaleX, 	
		ImageScaleY, 	
		Function
	);
}

void UWindowImage::PlgCopy(std::shared_ptr<UWindowImage> _CopyImage, const FTransform& _Trans, int _Index, float _RadAngle)
{
	if (_CopyImage == nullptr)
	{
		MsgBoxAssert("nullptr인 이미지를 복사할 수 없습니다.");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + " : 이미지정보의 인덱스를 초과했습니다.");
	}

	UImageInfo& CurInfo = _CopyImage->Infos[_Index];
	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;
	POINT Arr[3];

	{
		FTransform Trans = FTransform(float4::Zero, _Trans.GetScale());

		FVector LeftTop = Trans.LeftTop();
		FVector RightTop = Trans.RightTop();
		FVector LeftBot = Trans.LeftBottom();

		LeftTop.RotationZToRad(_RadAngle);
		RightTop.RotationZToRad(_RadAngle);
		LeftBot.RotationZToRad(_RadAngle);

		LeftTop += _Trans.GetPosition();
		RightTop += _Trans.GetPosition();
		LeftBot += _Trans.GetPosition();

		Arr[0] = LeftTop.ConvertToWinApiPOINT();
		Arr[1] = RightTop.ConvertToWinApiPOINT();
		Arr[2] = LeftBot.ConvertToWinApiPOINT();
	}

	int ImageLeft = ImageTrans.GetPosition().iX();
	int ImageTop = ImageTrans.GetPosition().iY();
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();

	if (CurInfo.RotationMaskImage == nullptr)
	{
		MsgBoxAssert("회전시킬 이미지가 존재하지 않습니다.");
	}

	HDC hdc = ImageDC;
	HDC hdcSrc = _CopyImage->Infos[_Index].ImageDC;

	PlgBlt(
		hdc, 							
		Arr,
		hdcSrc,							
		ImageLeft,   					
		ImageTop,   						
		ImageScaleX, 						
		ImageScaleY, 						
		CurInfo.RotationMaskImage->hBitMap,
		ImageLeft,   						
		ImageTop   							
	);
}

void UWindowImage::TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color)
{
	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	TextCopyFormat(_Text, _Font, stringFormat, _Size, _Trans, _Color);
}

void UWindowImage::TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _OutLineColor, Color8Bit _FillColor)
{
	Gdiplus::Graphics graphics(ImageDC);
	std::wstring WFont = UEngineString::AnsiToUniCode(_Font);
	Gdiplus::Font fnt(WFont.c_str(), _Size, Gdiplus::FontStyleBold | Gdiplus::FontStyleItalic, Gdiplus::UnitPixel);

	Gdiplus::SolidBrush OutLineBrush(Gdiplus::Color(_OutLineColor.R, _OutLineColor.G, _OutLineColor.B));
	Gdiplus::SolidBrush fillBrush(Gdiplus::Color(_FillColor.R, _FillColor.G, _FillColor.B));

	FVector Pos = _Trans.GetPosition();
	Gdiplus::RectF rectF(Pos.X, Pos.Y, 0, 0);

	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	std::wstring WText = UEngineString::AnsiToUniCode(_Text);

	float offsetsX[] = { -3.f, 3.f };
	float offsetsY[] = { -2.f, 2.f };
	for (float dx : offsetsX)
	{
		for (float dy : offsetsY)
		{
			Gdiplus::RectF borderRect = rectF;
			borderRect.X += dx;
			borderRect.Y += dy;
			graphics.DrawString(WText.c_str(), -1, &fnt, borderRect, &stringFormat, &OutLineBrush);
		}
	}

	float offsets_X[] = { -2.f, 2.f };
	float offsets_Y[] = { -1.f, 1.f };
	for (float dx : offsets_X)
	{
		for (float dy : offsets_Y)
		{
			Gdiplus::RectF borderRect = rectF;
			borderRect.X += dx;
			borderRect.Y += dy;
			graphics.DrawString(WText.c_str(), -1, &fnt, borderRect, &stringFormat, &fillBrush);
		}
	}
}

void UWindowImage::TextCopy(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Gdiplus::StringAlignment _SortOption1, Gdiplus::StringAlignment _SortOption2, Color8Bit _FillColor)
{
	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(_SortOption1);
	stringFormat.SetLineAlignment(_SortOption2);
	TextCopyFormat(_Text, _Font, stringFormat, _Size, _Trans, _FillColor);
}

void UWindowImage::TextCopyBold(const std::string& _Text, const std::string& _Font, float _Size, const FTransform& _Trans, Color8Bit _Color)
{
	Gdiplus::StringFormat stringFormat;
	stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
	stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);

	Gdiplus::Graphics graphics(ImageDC);
	std::wstring WFont = UEngineString::AnsiToUniCode(_Font);
	Gdiplus::Font fnt(WFont.c_str(), _Size, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush hB(Gdiplus::Color(_Color.R, _Color.G, _Color.B));
	FVector Pos = _Trans.GetPosition();
	Gdiplus::RectF  rectF(_Trans.GetPosition().X, _Trans.GetPosition().Y, 0, 0);

	std::wstring WText = UEngineString::AnsiToUniCode(_Text);
	graphics.DrawString(WText.c_str(), -1, &fnt, rectF, &stringFormat, &hB);
}

void UWindowImage::TextCopyFormat(const std::string& _Text, const std::string& _Font, const Gdiplus::StringFormat& stringFormat, float _Size, const FTransform& _Trans, Color8Bit _Color)
{
	Gdiplus::Graphics graphics(ImageDC);
	std::wstring WFont = UEngineString::AnsiToUniCode(_Font);
	Gdiplus::Font fnt(WFont.c_str(), _Size, 0, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush hB(Gdiplus::Color(_Color.R, _Color.G, _Color.B));
	FVector Pos = _Trans.GetPosition();
	Gdiplus::RectF  rectF(_Trans.GetPosition().X, _Trans.GetPosition().Y, 0, 0);

	std::wstring WText = UEngineString::AnsiToUniCode(_Text);
	graphics.DrawString(WText.c_str(), -1, &fnt, rectF, &stringFormat, &hB);
}

void UWindowImage::Cutting(int _X, int _Y)
{
	Infos.clear();

	FVector CuttingScale = { GetScale().X / _X,  GetScale().Y / _Y };
	FVector CuttingPos = { 0, 0 };

	for (int i = 0; i < _Y; i++)
	{
		for (int i = 0; i < _X; i++)
		{
			UImageInfo Info;
			Info.ImageDC = ImageDC;
			Info.CuttingTrans.SetPosition(CuttingPos);
			Info.CuttingTrans.SetScale(CuttingScale);
			Infos.push_back(Info);

			CuttingPos.X += CuttingScale.X;
		}

		CuttingPos.X = 0.0f;
		CuttingPos.Y += CuttingScale.Y;
	}
}

Color8Bit UWindowImage::GetColor(int _X, int _Y, Color8Bit _DefaultColor)
{
	if (_X < 0)
	{
		return _DefaultColor;
	}

	if (_Y < 0)
	{
		return _DefaultColor;
	}

	if (_X >= GetScale().iX())
	{
		return _DefaultColor;
	}

	if (_Y >= GetScale().iY())
	{
		return _DefaultColor;
	}

	Color8Bit Color;
	Color.Color = ::GetPixel(ImageDC, _X, _Y);

	return Color;
}

void UWindowImage::DrawRectangle(const FTransform& _Trans)
{
	Rectangle(ImageDC, _Trans.iLeft(), _Trans.iTop(), _Trans.iRight(), _Trans.iBottom());
}

void UWindowImage::DrawEllipse(const FTransform& _Trans)
{
	Ellipse(ImageDC, _Trans.iLeft(), _Trans.iTop(), _Trans.iRight(), _Trans.iBottom());
}

void UWindowImage::TextPrint(std::string_view _Text, FVector _Pos)
{
	TextOutA(ImageDC, _Pos.iX(), _Pos.iY(), _Text.data(), static_cast<int>(_Text.size()));
}