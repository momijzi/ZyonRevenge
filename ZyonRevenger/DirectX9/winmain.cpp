﻿#include <Windows.h>
#pragma comment(lib,"winmm.lib")

#include <tchar.h>

#include"Direct3D.h"

#include "Sprite.h"
#include "Texture.h"

#include "DirectInput.h"

#include"time.h"

#define screenWidth 980
#define screenHeight 840
#define Pixel 24

/*ギミック（悪魔の能力）

・敵が止まる　
　スイッチ分で敵のスピードの部分を０に設定攻撃はできるが金縛りにする

 ・氷
 マップの属性変更すれば完了

 ・


*/




//ウィンドウプロシージャ
LRESULT CALLBACK WndPrc
(
	HWND hWnd,	//ウィンドウのハンドル
	UINT msg,	//メッセージ
	WPARAM wParam,
	LPARAM lParam
)
{
	//メッセージ処理のための関数
	//DispatchMessageによって呼び出される

	//ウィンドウクラスの登録時に
	//各ウィンドウに設定される

	//アプリケーションがメッセージを
	//取得したら呼び出される

	//メッセージの例

	//WM_DESTROY ウィンドウが破棄された
	//			 ×ボタンが押された時など
	//WM_MOVE    ウィンドウが移動
	//WM_SIZE    ウィンドウサイズの変更
	//等

	//特別な処理を必要とする場合
	//または自分で独自の処理を定義したい場合
	//ここでメッセージの種類に応じた
	//処理を行う

	//取りあえず WM_DESTROYが来た時の
	//終了処理のみ定義

	switch (msg)
	{
		case WM_DESTROY:

			PostQuitMessage(0);

			//メッセージキューに
			//新しくWM_QUITメッセージを送る

			//いずれメッセージキューから
			//取り出され
			//メインループが終了する
			//(メインループの終了条件を
			//そのように作る)
			break;
	}

	//独自の処理を行ったら
	//デフォルトのウィンドウプロシージャを実行

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ウィンドウ設定の名前
static const TCHAR* WC_BASIC = _T("Basic");

//作りたいウィンドウの設定を
//登録する関数
HRESULT RegistClassEx(HINSTANCE hInstance)
{
	//ウィンドウの設定を保存する構造体
	WNDCLASSEX wcex;
	
	//wcexの先頭アドレスから
	//WNDCLASSEXの長さ分のメモリを
	//全て0で埋める
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	//つまりはwcexが使用しているメモリ領域を
	//全て0で初期化する処理

	//ウィンドウの設定

	//構造体のサイズ
	wcex.cbSize = sizeof(WNDCLASSEX);

	//ウィンドウの設定情報に追加する捕捉を付けないので
	//0で固定
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	//Windowのスタイル
	//それぞれがビット単位のフラグであるため
	//オア演算で合成したものがスタイルの最終的な設定
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//CS_HREDRAW 横サイズが変わったときウィンドウ全体の再描画
	//   VREDRAW 縦サイズが変わったときウィンドウ全体の再描画
	//   DBLCLKS ダブルクリックが発生したことをウィンドウに通知

	//WinMainのインスタンスハンドル
	wcex.hInstance = hInstance;

	//ウィンドウプロシージャのアドレス
	//関数ポインタの設定
	//ウィンドウプロシージャをOSが呼び出せるようにする
	wcex.lpfnWndProc = (WNDPROC)WndPrc;

	//背景色
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//メニュー　なし
	wcex.lpszMenuName = NULL;

	//ウィンドウクラスの名前　このウィンドウ設定の名前
	wcex.lpszClassName = WC_BASIC;

	//アイコン　デフォルトのを使う
	wcex.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0, 
		0, 
		LR_DEFAULTSIZE | LR_SHARED);
	wcex.hIconSm = NULL;

	//カーソル デフォルトのものを使う
	wcex.hCursor= (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	//設定したウィンドウクラスを登録
	//登録したウィンドウ設定でないと
	//ウィンドウを作ることができない
	return RegisterClassEx(&wcex); 
	//HRESULT型の実行結果が戻される
}


//登録した設定を基にウィンドウを作成する
HRESULT MakeWindow
(HINSTANCE hInstance,//WinMainの識別子
	HWND &refHWnd,	//ウィンドウの識別子
				   //正しくウィンドウの作成ができたら
				   //この変数に識別子を代入する
	int width = screenWidth,	//クライアント領域の幅
	int height = screenHeight)	//クライアント領域の高さ
	//クライアント領域はウィンドウ全体から
	//外枠やメニューの部分を除いた物と今は思っておけばOK
{
	//クライアント領域のおおきさを決める
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = width;
	rect.bottom = height;

	//クライアント領域を保持するのに必要な
	//ウィンドウのおおきさを計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE/*TRUE*/);
	//正しく実行されるとrectの値が更新される

	//WS_OVERLAPPEDWINDOWはウィンドウのスタイルの一つ

	//ウィンドウのハンドル
	//ウィンドウの識別に使用する
	HWND hWnd;

	hWnd = CreateWindowEx
	(	0,						//ウィンドウ拡張スタイル
		WC_BASIC,				//作りたいウィンドウクラス
								//あらかじめ登録されたもの
		_T("タイトル"),			//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW,	//ウィンドウのスタイル
		CW_USEDEFAULT,			//位置x座標 デフォルトの値
		CW_USEDEFAULT,			//位置y座標 デフォルトの値
		rect.right - rect.left,	//ウィンドウ全体の幅
		rect.bottom - rect.top, //ウィンドウ全体の高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューのハンドル
		hInstance,				//WinMainのハンドル

		NULL);					//ウィンドウ作成データ
								//ウィンドウに好きな32ビットのデータを
								//付属させることができる
								//追加情報構造体へのポインタなど
								//を付けるのが無難な使い方か
								//今回は使わない

	//ウィンドウが正しく作れたかをチェック
	//正しく作れたらhWndにNULL以外が入るはず
	if (hWnd == NULL)
	{
		return S_FALSE;//HRESULT型　失敗を表す識別子の一つ
	}

	//ウィンドウをアクティブにして表示
	//hWndでウィンドウの識別をしていることに注目
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//クライアント領域の更新
	UpdateWindow(hWnd);

	//参照渡しになっている引数に
	//ウィンドウの識別ハンドルをコピーする
	//これによって今作ったウィンドウの識別ハンドルを
	//呼び出し元のプログラムで得ることができる
	refHWnd = hWnd;

	//HRESULT型　成功を表す識別子の一つ
	return S_OK;
}

//スプライトのインスタンスを作成
//パラメータは適当で
Sprite sprite;
Sprite sprite2;

Texture textureWall;
Texture textureFloor;
Texture textureStair;

Texture textureWater;
Texture textureIce;


Texture textureStart;
Texture textureOver;
Texture textureClear;



//エントリーポイント
//プログラムの開始関数

int _stdcall WinMain
(HINSTANCE hInstance,	//プログラムを識別するハンドル
	HINSTANCE hPrevInstance,//アプリケーションの前のインスタンスハンドル
							//win32だと常にNULL
	LPSTR lpCmdLine,		//コマンドライン引数
	int nCmdShow)		//ウィンドウの表示状態
{
	//変数の宣言-------------------------------------

	//プレイヤーの関連
	int PlayerX, PlayerY;	//プレイヤーの座標
	float PlayerSpeed;		//プレイヤーのスピード

	//マップ関係//今回壁はこの外にかってに描画することにする　のちのち配列に組み込むかも
	
	//マップのサイズ
	//enum MapDate { WALL, FLOOR, PLAYER, STAIRS };//左から　壁、床、プレイヤー、階段
	//MapDate StageMap[MapSizeX][MapSizeY];

	int StageMapT1[30][40] = 
	{	 				  //10				   //20  //異端児		 //30				   //40
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,4,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,1,1,1,1,1,1,1,0 },
		{ 0,0,0,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,0,0,0,0,0,0 , 0,0,1,1,1,1,1,1,1,0 },
		{ 0,0,0,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,0,0,0,0,0,0 , 0,0,1,1,1,1,1,1,1,0 },
		{ 0,0,0,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,0,0,0,0,0,0 , 0,0,1,1,1,1,1,1,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,1,1,1,1,1,1,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,1,1,1,1,1,1,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,1,1,1,1,1,1,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,1,1,1,1,1,1,1,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,1,1,1,0,0,0 },
		//---------------------------------------------------------------------------------------
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,1,1,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,1,1,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,1,1,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,1,1,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,1,1,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,1,1,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,1,1,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,1,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,0,0,0 },
		//---------------------------------------------------------------------------------------
		{ 0,0,0,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,1,1,1 , 1,1,1,1,1,1,1,0,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0 , 0,0,0,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0 , 0,0,0,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0 , 0,0,0,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0 , 0,0,0,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,1,0,0 , 0,0,0,0,0,0,0,0,1,1 , 1,1,1,1,1,1,1,1,1,1 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,1,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,1,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,1,1,1,1,1,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 },
	};
	
	int StageMapT2[30][30] =
	{					  //10				   //20 				  //30
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,1 , 4,4,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,1 , 4,4,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,1 , 4,4,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,1,1,1,1,1,1,1 , 4,4,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		//-----------------------------------------------------------------
		{ 0,0,0,0,0,0,0,0,0,0 , 2,2,2,2,2,2,2,2,2,2 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 2,2,2,2,2,2,2,2,2,2 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 2,2,2,2,2,2,2,2,2,2 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 2,2,2,2,2,2,2,2,2,2 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 2,2,2,2,2,2,2,2,2,2 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 2,2,2,2,2,2,2,2,2,2 , 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,0,0,0,0,0,0,0,0 },
		//-----------------------------------------------------------------
		{ 0,0,0,0,0,0,0,0,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,0,0,0,0,0,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,2,2,2 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 4,4,1,1,1,1,1,1,4,4 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 4,4,1,1,1,1,1,1,4,4 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 4,4,1,1,1,1,1,1,4,4 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,2,2,2,2,2,2,2 , 4,4,1,1,1,1,1,1,4,4 , 2,2,2,2,2,2,2,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 , 0,0,0,0,0,0,0,0,0,0 },
	};
	//ステージ
	enum StageArea { Area1, Area2 };//現在の階層のエリアを意味する
	StageArea stageArea = Area2;

	
	enum STAGE { TUTORIAL, YEUNG, ICECAVE, RUINS};	//現在のステージ 最初はチュートリアルから
	STAGE Stage = TUTORIAL;					//次に森、氷の洞窟、最後に廃墟
	

	//現在のゲームの状態
	enum GameMode { START, ZERO, PLAY, OVER };
	GameMode game = ZERO;

	srand((unsigned int)time(NULL));//乱数の初期値設定

	

	

	
	////メッセージボックス
	//MessageBox(NULL,		//ウィンドウのハンドル 
	//	TEXT("最初の設定に成功しましたぱちぱち"),		//本文
	//	TEXT( "テスト-タイトル"),//タイトル
	//	MB_OK);				//メッセージボックスのタイプ
	//						//MB_OK  okのボタンが表示

	if (FAILED(RegistClassEx(hInstance)))
	{
		MessageBox(NULL,
			TEXT("ウィンドウクラス設定失敗"),
			TEXT("テスト-タイトル"),
			MB_OK);
		return 0;
	}

	HWND hWnd = NULL;

	/*正しくウィンドウが作成されれば
	hWndにウィンドウの識別ハンドルが入る*/
	if (FAILED(MakeWindow(hInstance, hWnd)))
	{
		MessageBox(NULL,
			TEXT("ウィンドウ作成失敗"),
			TEXT("テスト-タイトル"),
			MB_OK);
		return 0;
	}

	//Direct3Dを管理するクラス(シングルトン)への参照を取得
	Direct3D& d3d = Direct3D::GetInstance();

	//Direct3DDeviceの作成を試みる
	if (d3d.TryCreate(hWnd))
	{
		/*MessageBox(NULL,
			TEXT("Direct3D Device作成成功"),
			TEXT("テスト-タイトル"),
			MB_OK);*/
	}

	//レンダーステートの設定  αブレンド
	d3d.SetRenderState(RENDERSTATE::RENDER_ALPHABLEND);


	sprite.SetAlpha(0.1);						//透明度の設定
	sprite.SetSize(Pixel, Pixel);				//画像の大きさ
	sprite.SetAngle(0);							//画像の回転

	//テクスチャのインスタンスを作成
	textureWall.Load(_T("Texture/Wall.png"));	
	textureFloor.Load(_T("Texture/Bed.png"));
	textureStair.Load(_T("Texture/Stair.png"));
	textureWater.Load(_T("Texture/Water.png"));
	textureIce.Load(_T("Texture/Ice.png"));

	//ここで読み込んだ画像の分割処理
	

	DirectInput * pDi = DirectInput::GetInstance();
	pDi->Init(hWnd);

	//メインループ
	//メッセージループ

	MSG msg = {};

	//quitメッセージが出てくるまでループを繰り返す
	//quitメッセージは上記のウィンドウプロシージャから送信
	//送信の条件などはウィンドウプロシージャを確認
	while (msg.message != WM_QUIT )
	{

		//PeekMessage
		//メッセージキューの中にメッセージがあるかを調べて
		//msgの中に書き込みtrueを返す
		//メッセージがなければfalseを返す
		//PM_REMOVEを設定しているとメッセージの書き込みのあとに
		//メッセージキューから元のメッセージを消す

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//仮想キーメッセージを文字メッセージに変換し
			//それをメッセージキューにポストする
			TranslateMessage(&msg);

			//メッセージの割り当て
			//ウィンドウプロシージャでメッセージを処理
			DispatchMessage(&msg);
		}
		else
		{
			//メッセージキューにメッセージが無かったとき
			//こちらの処理
			//ここにゲーム処理を書き込んでいく

			pDi->Update();//キー状態の更新

			if (pDi->KeyJustPressed(DIK_A))
			{
				MessageBox(NULL,
					TEXT("キー入力確認"),
					TEXT("テスト-タイトル"),
					MB_OK);
			}

			if (pDi->MouseButtonJustPressed(MOUSE_BUTTON_LEFT))
				Vector2<int> vec = pDi->MousePosition();
			{
				int breakpoint = 0;
			}

			//sprite.SetAngle(sprite.GetAngle_Rad()+0.0f);//回転ここのfを大きい値にするほど回転速度が上がる

			static int dir = 1;//α
			sprite.SetAlpha(sprite.GetAlpha() + (dir*0.01));
			switch (dir)
			{
				case 1:
					if (sprite.GetAlpha() >= 1)
					{
						dir = -1;
					}
					break;
				case -1:
					if (sprite.GetAlpha() <= 0)
					{
						dir = 1;
					}
					break;
			}
			switch (game)
			{
				case ZERO://エリア移動毎にここに入ればマップデータ変更
					d3d.ClearScreen();

					
					
					game = START;

					break;
				case START:
					//今回難易度設定ではなくコンフィグいじりにしてみる
					//エンター押したときPLAYへ
					if (pDi->KeyJustPressed(DIK_RETURN))
					{
						game = PLAY;
					}
					break;
				case PLAY:
					switch (Stage)
					{
						case TUTORIAL://初期エリア
							switch (stageArea)
							{
								case Area1:
									//各ギミックを書いていく
									if (PlayerX == 5 && PlayerY == 1)
									{
										stageArea = Area2;
									}
									break;
								case Area2:
									if (PlayerX == 5 && PlayerY == 1)
									{
										stageArea = Area2;
									}
									break;
							}
							break;
						case YEUNG:		//森エリア

							break;
						case ICECAVE:	//氷の洞窟

							break;
						case RUINS:		//廃墟

							break;
					}
					/*if (StageMap[PlayerX][PlayerY] == STAIRS && pDi->KeyJustPressed(DIK_RETURN))
					{
						game = OVER;
					}*/
					break;
				case OVER:

					if (pDi->KeyJustPressed(DIK_RETURN))
					{
						game = ZERO;
					}
					break;
			}
			//まず描画 
			d3d.BeginScene();//描画開始
			//描画
			d3d.ClearScreen();

			//ゲームのスタートとオーバー時に表示する画像描画//--------------------------------------------------------------------------------------------
		
			switch (stageArea)
			{
				case Area1://初期チュートリアルエリア
					//マップデータの描画
					for (int y = 0; y < 30; y++)
					{
						for (int x = 0; x < 40; x++)
						{
							//壁
							if (StageMapT1[y][x] == 0)
							{
								sprite.SetPos((Pixel / 2) + (Pixel * x), (Pixel / 2) + (Pixel * y));
								sprite.Draw(textureWall);
							}
							//床
							else if (StageMapT1[y][x] == 1)
							{
								sprite.SetPos((Pixel / 2) + (Pixel * x), (Pixel / 2) + (Pixel * y));
								sprite.Draw(textureFloor);
							}
						}
					}
					break;
				case Area2://チュートリアルの二番目のエリア
					//マップデータの描画
					for (int y = 0; y < 30; y++)
					{
						for (int x = 0; x < 30; x++)
						{
							//壁の描画　
							if (StageMapT2[y][x] == 0)//壁
							{
								sprite.SetPos((Pixel / 2) + (Pixel * x), (Pixel / 2) + (Pixel * y));
								sprite.Draw(textureWall);
							}
							//床の描画
							else if (StageMapT2[y][x] == 1)//床
							{
								sprite.SetPos((Pixel / 2) + (Pixel * x), (Pixel / 2) + (Pixel * y));
								sprite.Draw(textureFloor);
							}
							else if (StageMapT2[y][x] == 2)//水
							{
								sprite.SetPos((Pixel / 2) + (Pixel * x), (Pixel / 2) + (Pixel * y));
								sprite.Draw(textureWater);
							}
							else if (StageMapT2[y][x] == 3)//氷
							{
								sprite.SetPos((Pixel / 2) + (Pixel * x), (Pixel / 2) + (Pixel * y));
								sprite.Draw(textureIce);
							}
							else//階段
							{
								sprite.SetPos((Pixel / 2) + (Pixel * x), (Pixel / 2) + (Pixel * y));
								sprite.Draw(textureStair);
							}
						}
					}
					break;
			}

			//描画終了の合図//--------------------------------------------------------------------------------------------

			d3d.EndScene();

			//バックバッファをフロントへ反映
			d3d.Present();
		}
	}
	return 0;
}
