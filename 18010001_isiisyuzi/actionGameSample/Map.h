#pragma once
class Player;
class Rule;
class Map
{
public:

	int		X = 0;
	int		Y = 0;
	int		score;
	int		imgMapChip[75];		// 背景マップチップ画像
	//int CheckEliminatBlock()
	//{
	//	int k;
	//	int ClsFlag; // 一つでも消せたブロックがあったか、のフラグ

	//	do {
	//		// 一時使用用ブロックデータを初期化
	//		InitBufferBlock();

	//		// 消せたブロックがあるか、フラグを倒す
	//		ClsFlag = FALSE;

	//		// 各ブロックが消えるか調べる
	//		for (int i = 0; i < MAP_HEIGHT; i++)
	//		{
	//			for (int j = 0; j < MAP_WIDTH; j++)
	//			{
	//				// もしブロックがない場合は次に移る
	//				if (map[j][i] == 0) continue;

	//				// ブロックが消えるかどうか調べて調査結果をバッファに保存する
	//				BufferBlock[j][i] = CheckEliminatBlockToOne(j, i);
	//			}
	//		}

	//		// 消えると判断されたブロックを消す
	//		for (int i = 0; i < MAP_HEIGHT; i++)
	//		{
	//			for (int j = 0; j < MAP_WIDTH; j++)
	//			{
	//				if (BufferBlock[j][i] == 1)
	//				{
	//					ClsFlag = TRUE;
	//					map[j][i] = 0;
	//				}
	//			}
	//		}

	//		// 空きを積める
	//		for (int i = MAP_HEIGHT - 2; i > -1; i--)
	//		{
	//			for (int j = 0; j < MAP_WIDTH; j++)
	//			{
	//				if (map[j][i] != 0)
	//				{
	//					for ( k = i + 1; k < MAP_HEIGHT && map[j][k] == 0; k++) {}
	//					k--;

	//					if (k != i)
	//					{
	//						map[j][k] = map[j][i];
	//						map[j][i] = 0;
	//					}
	//				}
	//			}
	//		}

	//	} while (ClsFlag);	// 消せたブロックがあった場合再度チェック

	//						// 終了
	//	return 0;
	//}
	// アクティブブロックが画面上のブロックに当たっていないか調べる
	int CheckHitActiveBlock(int x, int y)
	{

		// ３つあるブロックがそれぞれ画面上のブロックに当たっていないか調べる
		for (int i = 0; y - i >= 0 && i < 3; i++)
		{
			// 当たっていたらここで終了
			if (map[x][y - i] != 0)
			{
				return -1;
			}
		}

		// 当たっていない場合だけ０を返す
		return 0;
	}
	// アクティブブロックを固定する
	// 及び次のブロックを出す
	// もし次のブロックを出すスペースがなかったらゲームオーバー
	//int LockActiveBlock(int x, int y)
	//{

	//	for (int i = 0; i < 3; i++)
	//	{
	//		// 画面上から外れている場合はセットしない
	//		if (y - i < 0) continue;

	//		// ブロックの固定
	//		map[x][y - i] = ActiveBlock[0][i];
	//	}

	//	// 消せるブロックがある場合は消す
	//	CheckEliminatBlock();

	//	// 新しいブロックをセット
	//	{
	//		// アクティブブロックの位置をセット
	//		ActiveX = MAP_WIDTH / 2;
	//		ActiveY = 2;

	//		// 新しいアクティブブロックを生成
	//		CreateNewActiveBlock();

	//	}
	//}
	//int		MoveActiveBlock(int MoveX, int MoveY)	// アクティブブロックの移動
	//{
	//	int NewX, NewY;

	//	// 移動後の座標をセットする
	//	NewX = MoveX + ActiveX;
	//	NewY = MoveY + ActiveY;

	//	// 左右移動の処理
	//	if (MoveX != 0 && NewX >= 0 && NewX <  MAP_WIDTH)
	//	{
	//		// 各３つのブロックが画面上のブロックに当たっていないか調べる
	//		if (CheckHitActiveBlock(NewX, NewY) == -1)
	//		{
	//			// あたっていたら左右移動を無効にする
	//			MoveX = 0;
	//		}
	//	}

	//	// 上下移動の処理
	//	if (MoveY != 0)
	//	{
	//		// 画面の一番下のブロック位置まで来ていたらブロックを固定させる
	//		if (NewY >= MAP_HEIGHT)
	//		{
	//			LockActiveBlock(ActiveX, ActiveY);

	//			// 移動を無効にする
	//			MoveY = 0;
	//		}
	//		else
	//			// 各３つのブロックが画面上のブロックに当たっていないか調べる
	//			if (CheckHitActiveBlock(NewX, NewY) == -1)
	//			{
	//				// あたっていたらブロックを固定する
	//				LockActiveBlock(ActiveX, ActiveY);

	//				// 移動を無効にする
	//				MoveY = 0;
	//			}
	//	}

	//	// 座標を移動する
	//	ActiveX += MoveX;
	//	ActiveY += MoveY;

	//}
	int CheckEliminatBlockToOne(int x, int y)
	{
		int CheckBlock;
		int i;
		int BlockNum;

		// チェックするブロックの種類を保存
		CheckBlock = map[x][y];


		// 左右にどれだけつながっているか調べる
		for (i = 0; x + i >= 0 && map[x + i][y] == CheckBlock; i--) {}
		i++;
		for (BlockNum = 0; x + i < MAP_WIDTH && map[x + i][y] == CheckBlock; BlockNum++, i++) {}

		// ３つ以上つながっていたらここで終了
		if (BlockNum >= 3) return 1;


		// 上下にどれだけつながっているか調べる
		for (i = 0; y + i >= 0 && map[x][y + i] == CheckBlock; i--) {}
		i++;
		for (BlockNum = 0; y + i < MAP_HEIGHT && map[x][y + i] == CheckBlock; BlockNum++, i++) {}

		// ３つ以上つながっていたらここで終了
		if (BlockNum >= 3) return 1;


		// 左上から右下にかけて繋がっている数を調べる
		for (i = 0; y + i >= 0 && x + i >= 0 && map[x + i][y + i] == CheckBlock; i--) {}
		i++;
		for (BlockNum = 0; x + i < MAP_WIDTH && y + i < MAP_HEIGHT && map[x + i][y + i] == CheckBlock; BlockNum++, i++) {}

		// ３つ以上つながっていたらここで終了
		if (BlockNum >= 3) return 1;


		// 右上から左下にかけて繋がっている数を調べる
		for (i = 0; y + i >= 0 && x - i < MAP_WIDTH && map[x - i][y + i] == CheckBlock; i--) {}
		i++;
		for (BlockNum = 0; x - i >= 0 && y + i < MAP_HEIGHT && map[x - i][y + i] == CheckBlock; BlockNum++, i++) {}

		// ３つ以上つながっていたらここで終了
		if (BlockNum >= 3) return 1;


		// ここまで来ていたら消えない
		return 0;
	}

	int		ActiveX, ActiveY;	// アクティブブロックの一番下のブロックの位置
	int		ActiveVY = MAP_CHIP_SIZE + 1000;
	
	char	ActiveBlock[73];
	void	scroll(Player *player);
	void	InitMap();
	void	DrawMap(Rule *rule);
	void	CreateNewActiveBlock();		// 新しいブロックの生成
	bool	rightMove;
};

typedef struct tag_rect
{
	int x;
	int y;
	int w;
	int h;
}rect;