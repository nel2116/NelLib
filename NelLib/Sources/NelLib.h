#pragma once
// ====== インクルード部 ======
#include <System/window.h>
#include <System/Geometory.h>
#include <System/Input.h>

// ====== 定数・マクロ定義 ======
// グリッドサイズ
#define DEBUG_GRID_NUM (10) // グリッド中心から端までの線の数
#define DEBUG_GRID_MARGIN (1.0f) // グリッド配置幅(メートル換算)

void window(const char* appName, int width, int height);
void DrawGrid();