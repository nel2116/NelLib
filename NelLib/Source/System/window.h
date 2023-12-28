#pragma once
// ====== インクルード部 ======
#include"common.h"

// ====== グローバル変数 ======
extern int ClientWidth;			// ウィンドウの幅
extern int ClientHeight;		// ウィンドウの高さ
extern unsigned ActiveWindow;	// アクティブウィンドウのハンドル
extern int MouseDelta;			// マウスの移動量
extern bool Windowed;			// ウィンドウモードかどうか
extern float DeltaTime;			// デルタタイム

// ====== プロトタイプ宣言 ======
/// <summary>
/// ウィンドウプロシージャー
/// </summary>
bool quit();
bool escKeyPressed();
/// <summary>
/// ウィンドウを閉じる関数
/// </summary>
/// <remarks>この関数を呼ぶと、ウィンドウが閉じる</remarks>
void closeWindow();
/// <summary>
/// ウィンドウを作成する関数
/// </summary>
/// <param name="appName">ウィンドウのタイトル</param>
/// <param name="windowWidth">ウィンドウの幅</param>
/// <param name="windowHeight">ウィンドウの高さ</param>
/// <remarks>この関数を呼ぶと、ウィンドウが作成される</remarks>
/// <remarks>この関数は、ゲームの初期化処理の中で呼ぶ</remarks>
void createWindow(const char* appName, int windowWidth, int windowHeight);

#define delta DeltaTime			// デルタタイムの別名
/// <summary>
/// デルタタイムを初期化する関数
/// </summary>
/// <remarks>この関数を呼ぶと、デルタタイムが初期化される</remarks>
/// <remarks>この関数は、ゲームの初期化処理の中で呼ぶ</remarks>
/// <remarks>この関数は、createWindow()の後に呼ぶ</remarks>
void initDeltaTime();
/// <summary>
/// デルタタイムを更新する関数
/// </summary>
/// <remarks>この関数を呼ぶと、デルタタイムが更新される</remarks>
/// <remarks>この関数は、ゲームの更新処理の中で呼ぶ</remarks>
void setDeltaTime();
/// <summary>
/// デルタタイムを取得する関数
/// </summary>
/// <returns>デルタタイム</returns>
/// <remarks>この関数は、ゲームの更新処理の中で呼ぶ</remarks>
/// <remarks>この関数は、setDeltaTime()の後に呼ぶ</remarks>
unsigned getTime();
