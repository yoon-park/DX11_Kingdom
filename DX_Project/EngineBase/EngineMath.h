#pragma once

class UEngineMath
{
public:
	UEngineMath();
	~UEngineMath();

	UEngineMath(const UEngineMath& _Other) = delete;
	UEngineMath(UEngineMath&& _Other) noexcept = delete;
	UEngineMath& operator=(const UEngineMath& _Other) = delete;
	UEngineMath& operator=(UEngineMath&& _Other) noexcept = delete;

	static const float PI;
	static const float PI2;

	static const float DToR;
	static const float RToD;

protected:

private:

};

struct float4
{
public:
	static const float4 Zero;
	static const float4 One;
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;

	static const float4 White;
	static const float4 Black;
	static const float4 Red;

	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		struct
		{
			float R;
			float G;
			float B;
			float A;
		};

		float Arr1D[4];
		float Arr2D[1][4];
	};

	float4()
		: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
	{

	}

	float4(int _X, int _Y)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	float4(int _X, int _Y, int _Z)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(static_cast<float>(_Z)), W(1.0f)
	{

	}

	float4(int _X, int _Y, int _Z, int _W)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(static_cast<float>(_Z)), W(static_cast<float>(_W))
	{

	}

	float4(long _X, long _Y)
		: X(static_cast<float>(_X)), Y(static_cast<float>(_Y)), Z(0.0f), W(1.0f)
	{

	}

	float4(float _X, float _Y)
		: X(_X), Y(_Y), Z(1.0f), W(1.0f)
	{

	}

	float4(float _X, float _Y, float _Z)
		: X(_X), Y(_Y), Z(_Z), W(1.0f)
	{

	}

	float4(float _X, float _Y, float _Z, float _W)
		: X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}

public:
	static float4 VectorRotationXToDeg(float4 _OriginVector, float _Angle)
	{
		return VectorRotationXToRad(_OriginVector, _Angle * UEngineMath::DToR);
	}

	static float4 VectorRotationXToRad(float4 _OriginVector, float _Angle)
	{
		float4 Result;
		Result.X = _OriginVector.X;
		Result.Y = (_OriginVector.Z * sinf(_Angle)) + (_OriginVector.Y * cosf(_Angle));
		Result.Z = (_OriginVector.Z * cosf(_Angle)) - (_OriginVector.Y * sinf(_Angle));
		return Result;
	}

	static float4 VectorRotationYToDeg(float4 _OriginVector, float _Angle)
	{
		return VectorRotationYToRad(_OriginVector, _Angle * UEngineMath::DToR);
	}

	static float4 VectorRotationYToRad(float4 _OriginVector, float _Angle)
	{
		float4 Result;
		Result.X = (_OriginVector.X * cosf(_Angle)) - (_OriginVector.Z * sinf(_Angle));
		Result.Y = _OriginVector.Y;
		Result.Z = (_OriginVector.X * sinf(_Angle)) + (_OriginVector.Z * cosf(_Angle));
		return Result;
	}
	static float4 VectorRotationZToDeg(float4 _OriginVector, float _Angle)
	{
		return VectorRotationZToRad(_OriginVector, _Angle * UEngineMath::DToR);
	}

	static float4 VectorRotationZToRad(float4 _OriginVector, float _Angle)
	{
		float4 Result;
		Result.X = (_OriginVector.X * cosf(_Angle)) - (_OriginVector.Y * sinf(_Angle));
		Result.Y = (_OriginVector.X * sinf(_Angle)) + (_OriginVector.Y * cosf(_Angle));
		Result.Z = _OriginVector.Z;
		return Result;
	}

	static float DotProduct3D(float4 _Left, float4 _Right)
	{
		float Result = (_Left.X * _Right.X) + (_Left.Y * _Right.Y) + (_Left.Z * _Right.Z);
		return Result;
	}

	static float4 Cross3D(float4 _Left, float4 _Right)
	{
		float4 Result;
		Result.X = (_Left.Y * _Right.Z) - (_Left.Z * _Right.Y);
		Result.Y = (_Left.Z * _Right.X) - (_Left.X * _Right.Z);
		Result.Z = (_Left.X * _Right.Y) - (_Left.Y * _Right.X);
		return Result;
	}

	static float4 DegToDir(float _Angle)
	{
		return RadToDir(_Angle * UEngineMath::DToR);
	}

	static float4 RadToDir(float _Angle)
	{
		return float4(cosf(_Angle), sinf(_Angle));
	}

	static float4 LerpClamp(float4 p1, float4 p2, float d1)
	{
		if (d1 <= 0.0f)
		{
			d1 = 0.0f;
		}

		if (d1 >= 1.0f)
		{
			d1 = 1.0f;
		}

		return Lerp(p1, p2, d1);
	}

	static float4 Lerp(float4 p1, float4 p2, float d1) 
	{
		return (p1 * (1.0f - d1)) + (p2 * d1);
	}

	float Size2D()
	{
		return std::sqrtf((X * X) + (Y * Y));
	}

	float Size3D()
	{
		return std::sqrtf((X * X) + (Y * Y) + (Z * Z));
	}

	void Normalize2D() 
	{
		float Size = Size2D();
		if (Size > 0.0f && isnan(Size) == false)
		{
			X /= Size;
			Y /= Size;
			Z = 0.0f;
			W = 0.0f;
		}
	}

	float4 Normalize2DReturn() const
	{
		float4 Result = *this;
		Result.Normalize2D();
		return Result;
	}

	void Normalize3D()
	{
		float Size = Size3D();
		if (Size > 0.0f && isnan(Size) == false)
		{
			X /= Size;
			Y /= Size;
			Z /= Size;
			W = 0.0f;
		}
	}

	float4 Normalize3DReturn() const
	{
		float4 Result = *this;
		Result.Normalize3D();
		return Result;
	}
	
	void RotationXToDeg(float _Angle)
	{
		RotationXToRad(_Angle * UEngineMath::DToR);
	}

	void RotationXToRad(float _Angle)
	{
		*this = VectorRotationXToRad(*this, _Angle);
		return;
	}

	void RotationYToDeg(float _Angle)
	{
		RotationYToRad(_Angle * UEngineMath::DToR);
	}

	void RotationYToRad(float _Angle)
	{
		*this = VectorRotationYToRad(*this, _Angle);
		return;
	}

	void RotationZToDeg(float _Angle)
	{
		RotationZToRad(_Angle * UEngineMath::DToR);
	}

	void RotationZToRad(float _Angle)
	{
		*this = VectorRotationZToRad(*this, _Angle);
		return;
	}

	int iX() const
	{
		return std::lround(X);
	}

	int iY() const
	{
		return std::lround(Y);
	}

	float hX() const
	{
		return X * 0.5f;
	}

	float hY() const
	{
		return Y * 0.5f;
	}

	int ihY() const
	{
		return std::lround(hY());
	}

	int ihX() const
	{
		return std::lround(hX());
	}

	float4 Half2D()
	{
		return { hX(), hY() };
	}

	POINT ConvertToWinApiPOINT()
	{
		return { iX(),iY() };
	}

	bool IsZeroVector2D() const
	{
		return X == 0.0f && Y == 0.0f;
	}

	std::string ToString()
	{
		return "[X : " + std::to_string(X) + " Y : " + std::to_string(Y) + " Z : " + std::to_string(Z) + " W : " + std::to_string(W) + "]";
	}

	float4 operator-() const
	{
		float4 Result;
		Result.X = -X;
		Result.Y = -Y;
		Result.Z = -Z;
		return Result;
	}

	float4& operator=(const float4& _Other)
	{
		X = _Other.X;
		Y = _Other.Y;
		Z = _Other.Z;
		W = _Other.W;
		return *this;
	}

	float4 operator+(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X += _Other.X;
		Result.Y += _Other.Y;
		Result.Z += _Other.Z;
		return Result;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X -= _Other.X;
		Result.Y -= _Other.Y;
		Result.Z -= _Other.Z;
		return Result;
	}

	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}

	float4 operator*(float _Value) const
	{
		float4 Result = *this;
		Result.X *= _Value;
		Result.Y *= _Value;
		Result.Z *= _Value;
		return Result;
	}

	float4& operator*=(float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	float4& operator/=(float _Value)
	{
		X /= _Value;
		Y /= _Value;
		Z /= _Value;

		return *this;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X *= _Other.X;
		Result.Y *= _Other.Y;
		Result.Z *= _Other.Z;
		return Result;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4 operator*(const class float4x4& _Other) const;
	float4& operator*=(const class float4x4& _Other);
};

using FVector = float4;
using FColor = float4;

class float4x4 operator*(const class float4x4& _Left, const class float4x4& _Right);

class float4x4
{
public:
	union
	{
		struct
		{
			float v00; 
			float v01; 
			float v02;
			float v03;

			float v10; 
			float v11; 
			float v12;
			float v13;

			float v20; 
			float v21; 
			float v22;
			float v23;

			float v30; 
			float v31; 
			float v32;
			float v33;
		};

		float4 ArrVector[4];
		float Arr1D[16] = { };
		float Arr2D[4][4];
	};

	float4x4()
	{
		Identity();
	}

	float4x4& operator=(const float4x4& _Value)
	{
		memcpy_s(Arr1D, sizeof(float) * 16, _Value.Arr1D, sizeof(float) * 16);

		return *this;
	}

	float4x4 operator*(const float4x4& _Value)
	{
		return ::operator*(*this, _Value);
	}

	void Identity()
	{
		memset(Arr1D, 0, sizeof(float) * 16);
		Arr2D[0][0] = 1.0f;
		Arr2D[1][1] = 1.0f;
		Arr2D[2][2] = 1.0f;
		Arr2D[3][3] = 1.0f;
	}

	void Transpose()
	{
		float4x4 Result = *this;
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				Result.Arr2D[y][x] = Arr2D[x][y];
			}
		}

		*this = Result;
	}

	float4x4 TransposeReturn()
	{
		float4x4 Result = *this;
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				Result.Arr2D[y][x] = Arr2D[x][y];
			}
		}
		return Result;
	}

	void Scale(float4 _Value)
	{
		Identity();
		Arr2D[0][0] = _Value.X;
		Arr2D[1][1] = _Value.Y;
		Arr2D[2][2] = _Value.Z;
		Arr2D[3][3] = 1.0f;
	}

	float4x4 RotationDeg(const float4 _Value)
	{
		Identity();
		float4x4 X;
		X.RotationXDeg(_Value.X);
		float4x4 Y;
		Y.RotationYDeg(_Value.Y);
		float4x4 Z;
		Z.RotationZDeg(_Value.Z);
		return X * Y * Z;
	}

	void RotationXDeg(float _Angle)
	{
		RotationXRad(_Angle * UEngineMath::DToR);
	}

	void RotationXRad(float _Angle)
	{
		Identity();
		Arr2D[1][1] = cosf(_Angle);
		Arr2D[1][2] = sinf(_Angle);
		Arr2D[2][1] = -sinf(_Angle);
		Arr2D[2][2] = cosf(_Angle);
	}

	void RotationYDeg(float _Angle)
	{
		RotationYRad(_Angle * UEngineMath::DToR);
	}

	void RotationYRad(float _Angle)
	{
		Identity();
		Arr2D[0][0] = cosf(_Angle);
		Arr2D[0][2] = -sinf(_Angle);
		Arr2D[2][0] = sinf(_Angle);
		Arr2D[2][2] = cosf(_Angle);
	}

	void RotationZDeg(float _Angle)
	{
		RotationZRad(_Angle * UEngineMath::DToR);
	}

	void RotationZRad(float _Angle)
	{
		Identity();
		Arr2D[0][0] = cosf(_Angle);
		Arr2D[0][1] = sinf(_Angle);
		Arr2D[1][0] = -sinf(_Angle);
		Arr2D[1][1] = cosf(_Angle);
	}

	void Position(float4 _Value)
	{
		Identity();
		Arr2D[3][0] = _Value.X;
		Arr2D[3][1] = _Value.Y;
		Arr2D[3][2] = _Value.Z;
	}

	float4x4 View(const float4 _EyePos, const float4 _EyeDir, const float4 _EyeUp)
	{
		float4x4 View;

		FVector Up = _EyeUp.Normalize3DReturn();
		FVector Forward = _EyeDir.Normalize3DReturn();
		FVector Right = FVector::Cross3D(Up, Forward);
		Up.W = 0.0f;
		Forward.W = 0.0f;
		Right.W = 0.0f;

		View.ArrVector[0] = Right;
		View.ArrVector[1] = Up;
		View.ArrVector[2] = Forward;
		View.Transpose();

		float4 NegEyePos = -_EyePos;
		NegEyePos.W = 1.0f;

		View.ArrVector[3].X = float4::DotProduct3D(Right, NegEyePos);
		View.ArrVector[3].Y = float4::DotProduct3D(Up, NegEyePos);
		View.ArrVector[3].Z = float4::DotProduct3D(Forward, NegEyePos);

		*this = View;

		return View;
	}

	void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	{
		Identity();

		float fRange = 1.0f / (_Far - _Near);

		Arr2D[0][0] = 2.0f / _Width;
		Arr2D[1][1] = 2.0f / _Height;
		Arr2D[2][2] = fRange;

		Arr2D[3][2] = -fRange * _Near;
	}

	void PerspectiveFovDeg(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	{
		PerspectiveFovRad(_FovAngle * UEngineMath::DToR, _Width, _Height, _Near, _Far);
	}

	void PerspectiveFovRad(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	{
		Identity();

		Arr2D[2][3] = 1.0f;
		Arr2D[3][3] = 0.0f;
		
		float Ratio = _Width / _Height;
		float DivFov = _FovAngle / 2.0f;

		Arr2D[0][0] = 1.0f / (tanf(DivFov) * Ratio);
		Arr2D[1][1] = 1.0f / tanf(DivFov);
		Arr2D[2][2] = _Far / (_Far - _Near);

		Arr2D[3][2] = -(_Near * _Far) / (_Far - _Near);
	}

	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin, float _ZMax)
	{
		Identity();

		Arr2D[0][0] = _Width * 0.5f;
		Arr2D[1][1] = -_Height * 0.5f;
		Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;

		Arr2D[3][0] = Arr2D[0][0] + _Left;
		Arr2D[3][1] = -Arr2D[1][1] + _Right;
		Arr2D[3][2] = _ZMax != 0.0f ? 0.0f : _ZMin / _ZMax;
		Arr2D[3][3] = 1.0f;
	}

	float4 LeftVector()
	{
		return -ArrVector[0].Normalize3DReturn();
	}

	float4 RightVector()
	{
		return ArrVector[0].Normalize3DReturn();
	}

	float4 UpVector()
	{
		return ArrVector[1].Normalize3DReturn();
	}

	float4 DownVector()
	{
		return -ArrVector[1].Normalize3DReturn();
	}

	float4 ForwardVector()
	{
		return ArrVector[2].Normalize3DReturn();
	}

	float4 BackVector()
	{
		return -ArrVector[2].Normalize3DReturn();
	}
};

using FMatrix = float4x4;

class Color8Bit
{
public:
	static const Color8Bit Black;
	static const Color8Bit Red;
	static const Color8Bit Green;
	static const Color8Bit Blue;
	static const Color8Bit Yellow;
	static const Color8Bit White;
	static const Color8Bit Magenta;
	static const Color8Bit Orange;

	static const Color8Bit BlackA;
	static const Color8Bit RedA;
	static const Color8Bit GreenA;
	static const Color8Bit BlueA;
	static const Color8Bit YellowA;
	static const Color8Bit WhiteA;
	static const Color8Bit MagentaA;
	static const Color8Bit OrangeA;
	static const Color8Bit CyanA;

	union
	{
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};

		unsigned char Arr1D[4] = { 0,0,0,255 };
		unsigned int Color;
	};

	Color8Bit()
	{

	}

	Color8Bit(
		unsigned char _R,
		unsigned char _G,
		unsigned char _B,
		unsigned char _A
	)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}

	bool operator==(Color8Bit _Color)
	{
		return Color == _Color.Color;
	}

	Color8Bit ZeroAlphaColor() const
	{
		return Color8Bit{ R,G,B,0 };
	}
};
