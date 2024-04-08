#pragma once
#include "DirectXHelper.h"

class UVertexLayoutInfo
{
public:
	UINT OffsetSize = 0;
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;

	void AddInputLayout(
		LPCSTR _SemanticName,
		DXGI_FORMAT _Format,
		UINT _SemanticIndex = 0,
		UINT _InputSlot = 0,
		UINT _AlignedByteOffset = -1,
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
		UINT _InstanceDataStepRate = 0
	)
	{
		D3D11_INPUT_ELEMENT_DESC Desc;

		Desc.SemanticName = _SemanticName;
		Desc.SemanticIndex = _SemanticIndex;
		Desc.Format = _Format;
		Desc.InputSlot = _InputSlot;
		Desc.AlignedByteOffset = _InputSlot;

		if (_AlignedByteOffset == -1)
		{
			Desc.AlignedByteOffset += OffsetSize;
		}

		OffsetSize += UDirectXHelper::DirectFormatSize(_Format);

		Desc.InputSlotClass = _InputSlotClass;
		Desc.InstanceDataStepRate = _InstanceDataStepRate;

		Descs.push_back(Desc);
	}
};

#define VERTEXMEM(Type, Name) Type Name

struct FEngineVertex
{
	static UVertexLayoutInfo Info;

	float4 POSITION;
	float4 TEXCOORD;
};