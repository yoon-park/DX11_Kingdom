#include "PreCompile.h"
#include "ContentsConstValue.h"

const float UContentsConstValue::TileSize = 64.0f;
std::shared_ptr<UEngineTexture> UContentsConstValue::MapTex;
float4 UContentsConstValue::MapTexScale;
//const float4 UContentsConstValue::InitLocation = { 7800.0f, -32.0f, 0.0f, 0.0f };