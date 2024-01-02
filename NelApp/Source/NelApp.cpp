#include "../../NelLib/Source/NelLib.h"
#include "../../NelLib/Source/DirectX/Renderer.h"

void Init()
{
	window("Nel Game", 960, 540);
}
void Input()
{

}
void Update()
{

}
void Draw()
{
	RENDERER.Begin();

	RENDERER.End();
}
void Uninit()
{
}

void gmain()
{
	Init();
	while (!quit())
	{
		if (escKeyPressed()) { closeWindow(); }
		// ˆÈ‰º‚ÉƒQ[ƒ€‚Ìˆ—‚ğ‘‚­
		// ===== “ü—Íˆ— =====
		Input();
		// ===== XVˆ— =====
		Update();
		// ===== •`‰æˆ— =====
		Draw();
	}
	Uninit();
}