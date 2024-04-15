#include "PreCompile.h"
#include "Monster.h"

AMonster::AMonster()
{
	USpriteRenderer* Ptr = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Ptr);

	SetActorScale3D({ 150.0f, 150.0f ,150.0f });
}

AMonster::~AMonster()
{

}