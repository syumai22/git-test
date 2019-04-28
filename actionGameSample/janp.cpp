#include "DxLib.h"
#include "Game.h"

// ゲームループを続けるか？
bool ProgramLooping = true;

// マップデータ
unsigned char map[][MAP_WIDTH] =
//    0  1  2  3  4  5  6  7  8  9 10 11 12 13
{ 
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // 0
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, }, // 1
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, }, // 2
	{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, }, // 3
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, }, // 4
	{ 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, }, // 5
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, }, // 6
	{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, }, // 7
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, }, // 8
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, }, // 9
};

// 画像ハンドル
int imgMapChip[2];  // 背景マップチップ画像
int imgPlayer;  // プレーヤー画像

				  // プレーヤー関連のデータ
typedef struct Player
{
	float       x = 100.0f;           // プレーヤの x座標
	float       y = 140.0f;           // プレーヤの y座標
	float       vx = 0.0f;            // プレーヤの x方向速度
	float       vy = 0.0f;            // プレーヤの y方向速度         
	int         w = 40;               // プレーヤーの当たり判定幅
	int         h = 56;               // プレーヤーの当たり判定高さ
	const float accel = 0.3f;         // プレーヤの 横方向加速度
	const float brake_Ratio = 0.8f;   // プレーヤの ブレーキ係数
}Player;

Player player;
const int MAX_OVERLAP_CAPACITY = 10;   // 壁最大めり込み量

typedef struct tag_rect
{
	int x;
	int y;
	int w;
	int h;
}rect;

// 矩形ヒットチェック関数
bool checkHitRect(rect r1, rect r2)
{
	return ((r1.x < (r2.x + r2.w)) &&
		(r2.x < (r1.x + r1.w)) &&
		(r1.y < (r2.y + r2.h)) &&
		(r2.y < (r1.y + r1.h)));
}
///////////////
//関数宣言
//////////////
//マップ描画用関数
void  DrawMap();
//プレーヤーの移動
void MovePlauer();
int		WINAPI		myWinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR     CmdLine, int CmdShow,
	int screen_x, int screen_y, bool FullScreen)
{
#ifdef WINDOW_MODE
	ChangeWindowMode(TRUE);
#endif 
	/////////////////////////////////////////////////////////
	// DXLIB初期化関連
	/////////////////////////////////////////////////////////
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, 60);
	DxLib_Init();   // DXライブラリ初期化処理

	SetMouseDispFlag(true);
	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定

	/////////////////////////////////////////////////////////
	// ゲーム中の画像読み込み
	/////////////////////////////////////////////////////////
	imgPlayer = LoadGraph("image/player.png");

	LoadDivGraph("image/mapchip.png", 2, 2, 1, MAP_CHIP_SIZE, MAP_CHIP_SIZE, imgMapChip);
	/////////////////////////////////////////////////////////
	// ゲームループ
	/////////////////////////////////////////////////////////
	while (ProgramLooping)
	{
		if (ProcessMessage() != 0) {
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}

		//ゲーム関連処理
		INPUT_INSTANCE.update(); // 入力キーすべて調べる
		//プレーヤーの移動
		MovePlauer();

		//描画関連
		ClearDrawScreen();

		//マップ描画
		DrawMap();

		//画面フリップ
		ScreenFlip();
	}

	
	DxLib_End();
	return 0;
}






////////////////////////////////////////////////////////////////////////////////////////
// コンソール画面からWindowsのお作法に飛ぶためのコード
////////////////////////////////////////////////////////////////////////////////////////
void windowOpen(int screen_x, int screen_y, bool FullScreen)
{
	HINSTANCE	hInstance	= GetModuleHandle(0);
	int			iCmdShow	= SW_SHOWDEFAULT ;

	myWinMain( hInstance, NULL, NULL, iCmdShow, screen_x, screen_y, FullScreen);
}

// DOS窓時のエントリーポイント
int main(void)
{
	windowOpen( 1440, 900, false);

	return 0;
}

// ウィンドウシステムの時のエントリーポイント
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	main();
	return 0;
}

//マップ描画用関数
void DrawMap()
{
	//マップ描画
	for (int iy = 0; iy < MAP_HEIGHT; iy++)
	{
		for (int ix = 0; ix < MAP_WIDTH; ix++)
		{
			/*int mapType = map[iy][ix];*/
			DrawGraph(ix *  MAP_CHIP_SIZE, iy *  MAP_CHIP_SIZE, imgMapChip[map[iy][ix]], FALSE);
		}
	}
	DrawGraph(player.x, player.y, imgPlayer, TRUE);
}
//プレーヤーの移動
void MovePlauer()
{
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT))
	{
		player.vx += player.accel;
		if (player.vx > MAX_OVERLAP_CAPACITY)
		{
			player.vx = MAX_OVERLAP_CAPACITY;
		}
	}

	if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT))
	{
		player.vx -= player.accel;
		if (player.vx < -MAX_OVERLAP_CAPACITY)
		{
			player.vx = -MAX_OVERLAP_CAPACITY;
		}
	}
	if (INPUT_INSTANCE.getInput(KEY_INPUT_DOWN))
	{
		player.vy += player.accel;
		if (player.vy > MAX_OVERLAP_CAPACITY)
		{
			player.vy = MAX_OVERLAP_CAPACITY;
		}
	}
	if (INPUT_INSTANCE.getInput(KEY_INPUT_UP))
	{
		player.vy -= player.accel;
		if (player.vy < -MAX_OVERLAP_CAPACITY)
		{
			player.vy = -MAX_OVERLAP_CAPACITY;
		}
	}

	if (!(INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT)) &&
		!(INPUT_INSTANCE.getInput(KEY_INPUT_LEFT)))
	{
		player.vx *= player.brake_Ratio;
	}
	if (!(INPUT_INSTANCE.getInput(KEY_INPUT_UP)) &&
		!(INPUT_INSTANCE.getInput(KEY_INPUT_DOWN)))
	{
		player.vy *= player.brake_Ratio;
	}

	player.x += player.vx;
	player.y += player.vy;

	//////////////////////////////
	//プレイヤーと壁の当たり判定
	/////////////////////////////
	rect playerRect, blocrect;
	playerRect.x = (int)player.x;
	playerRect.y = (int)player.y;
	playerRect.w = player.w;
	playerRect.h = player.h;

	//ブロック矩形
	blocrect.w = MAP_CHIP_SIZE;
	blocrect.h = MAP_CHIP_SIZE;

	//プレイヤーが属するマップ添え字番号を算出
	//左下
	int chkx = playerRect.x / MAP_CHIP_SIZE;
	int chky = playerRect.y / MAP_CHIP_SIZE;
	//右下
	int maxchkx = (playerRect.x + playerRect.w) / MAP_CHIP_SIZE;
	int maxchky = (playerRect.y + playerRect.h) / MAP_CHIP_SIZE;
	//当たる可能性のあるすべてのブロックを調べる
	for (int y = chky; y <= maxchky; y++)
	{
		for (int x = chkx; x <= maxchkx; x++)
		{
			//そこは通行不可能なブロックか
			if (map[y][x] != 0)
			{
				//衝突ブロックの左上座標を計算
				blocrect.x = x * MAP_CHIP_SIZE;
				blocrect.y = y * MAP_CHIP_SIZE;
				//ブロックとぶつかったか
				if (checkHitRect(playerRect, blocrect))
				{
					//ロックの右端と当たっていたら
					if ((x + 1)*MAP_CHIP_SIZE - player.x < MAX_OVERLAP_CAPACITY&&
						player.vx < 0)
					{
						playerRect.x = (x + 1)*MAP_CHIP_SIZE;
						player.vx = 0;
					}
					if ((player.x + player.w) - x * MAP_CHIP_SIZE < MAX_OVERLAP_CAPACITY&&
						player.vx > 0)
					{
						playerRect.x = x * MAP_CHIP_SIZE - playerRect.w;
						player.vx = 0;
					}
					if ((y + 1)*MAP_CHIP_SIZE - player.y < MAX_OVERLAP_CAPACITY&&
						player.vy < 0)
					{
						playerRect.y = (y + 1)*MAP_CHIP_SIZE;
						player.vy = 0;
					}
					if ((player.y + player.h) - y * MAP_CHIP_SIZE < MAX_OVERLAP_CAPACITY&&
						player.vy > 0)
					{
						playerRect.y = y * MAP_CHIP_SIZE - playerRect.h;
						player.vy = 0;
					}
				}
			}

		}
	}
	player.x = playerRect.x;
	player.y = playerRect.y;
	printf("[ %4.3f,%4.3f ],\n", player.x, player.y);
}