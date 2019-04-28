#include"Header.h"

const float Enemy::jumpPower = 5.0f;
const float Enemy::e_Gravity = 0.3f;				// 重力加速度 

bool e_checkHitRect(rect r1, rect r2)				// 矩形ヒットチェック関数
{
	return ((r1.x < (r2.x + r2.w)) &&
		(r2.x < (r1.x + r1.w)) &&
		(r1.y < (r2.y + r2.h)) &&
		(r2.y < (r1.y + r1.h)));
}

void Enemy::InitEnemy()
{
	LoadDivGraph("image/ninzya.png", 4, 4, 1, 32, 32, imgEnemy);	// エネミーのグラフィックをメモリにロード
	
	x = 0.0f;
	y = 0.0f;
	vx = 0.0f;
	vy = 0.0f;
	aliveFlg = FALSE;
	hp = ENEMY_LIFE;
	Atke = 3;
	damagecont = 1.5f;
	aniNum = anim_Walk_Start;
}
//エネミーの表示
void Enemy::DrawEnemy(Player *player,Map *scr,Rule *rule,BitmapText *text)
{
	rect EnemyHitChecRect, PlayerrightAtkHitChec, PlayerLeftatkHitChec;
	PlayerLeftatkHitChec.x = player->x - scr->X + player->leftArkModification;
	PlayerLeftatkHitChec.y = player->y - scr->Y;
	PlayerLeftatkHitChec.w = w;
	PlayerLeftatkHitChec.h = h;
	PlayerrightAtkHitChec.x = player->x - scr->X + player->rightAtkModification;
	PlayerrightAtkHitChec.y = player->y - scr->Y;
	PlayerrightAtkHitChec.w = w;
	PlayerrightAtkHitChec.h = h;
	EnemyHitChecRect.x = x - scr->X;
	EnemyHitChecRect.y = y - scr->Y;
	EnemyHitChecRect.w = w;
	EnemyHitChecRect.h = h;
	if (aliveFlg == TRUE)
	{
		if (rule->frameCount % animeCount == 0)
		{
			aniNum++;
		}
		if (aniNum == anim_Walk_End)
		{
			aniNum =  anim_Walk_Start;
		}

		if (player->x> x)
		{
			if (vx <= 1)
			{
				vx += 0.1;
			}
			if (vx > MAX_OVERLAP_CAPACITY)
			{
				vx = MAX_OVERLAP_CAPACITY;
			}
			dir = TRUE;
		}
		else if (player->x-player->w < x)
		{
			if (vx >= -1)
			{
				vx -= 0.1;
			}
			if (vx > MAX_OVERLAP_CAPACITY)
			{
				vx = MAX_OVERLAP_CAPACITY;
			}
			dir = FALSE;
		}
	
		if (aliveFlg == TRUE)
		{
			if(!damageFlag)
			{
				DrawRotaGraph(x - scr->X, y - scr->Y + position_Modification, 1.0f, 0, imgEnemy[aniNum], TRUE, dir);
			}
			if (damageFlag)
			{
				/*text->setFontColor(255, 0, 0);*/
				DrawRotaGraph(x - scr->X, y - scr->Y + position_Modification, 1.0f, 0, imgEnemy[aniNum], TRUE, dir);
			}
		}
		/*if (player->dir == true)
		{
			if (player->atkDamage == true)
			{

				if (e_checkHitRect(PlayerrightAtkHitChec, EnemyHitChecRect))
				{
					if (aliveFlg == true)
					{
						hp -= 1;

						player->atkDamage = false;
					}
				}
				if (damagecont == 10)
				{
					player->atkDamage = false;
				}
			}
		}
		else
		{
			if (player->atkDamage == true)
			{
				if (e_checkHitRect(PlayerLeftatkHitChec, EnemyHitChecRect))
				{
					if (aliveFlg == true)
					{
						hp -= 1;

						player->atkDamage = false;
					}
				}
				if (damagecont == 10)
				{
					player->atkDamage = false;
				}
			}
		}
		if (!player->atkDamage)
		{
			damagecont = 0;
			player->atkDamage = false;
		}*/
	}
	if (hp <= 0)
	{
		aliveFlg = FALSE;
	}
	
	
}

//敵を１００フレーム毎に追加
void Enemy::AddEnemy(int ex, int ey,int evx,int evy)
{
	x = ex;
	y = ey;
	vx= evx;
	vy= evy;
	aliveFlg = TRUE;
	
}
void Enemy::BlocRectEnemy()
{
	rect enemyRect, blocrect;

	//暫定エネミーの位置算出
	nextE_x = x + vx;
	nextE_y = y + vy;
	//エネミーの暫定端渓
	enemyRect.x = (int)nextE_x;
	enemyRect.y = (int)nextE_y;
	enemyRect.w = w;
	enemyRect.h = h;
	//ブロック矩形
	blocrect.w = MAP_CHIP_SIZE;
	blocrect.h = MAP_CHIP_SIZE;
	//エネミーが属するマップ添え字番号を算出
	//左下
	int chkxe = enemyRect.x / MAP_CHIP_SIZE;
	int chkye = enemyRect.y / MAP_CHIP_SIZE;
	int maxchkxe = (enemyRect.x + enemyRect.w) / MAP_CHIP_SIZE;
	int maxchkye = (enemyRect.y + enemyRect.h) / MAP_CHIP_SIZE;
	if ((chkxe >= 0 && chkye > 0) || (chkxe <= MAP_WIDTH && chkye <= MAP_HEIGHT))
	{
		//当たる可能性のあるすべてのブロックを調べる
		for (int x = chkxe; x <= maxchkxe; x++)
		{
			for (int y = chkye; y <= maxchkye; y++)
			{
				//そこは通行不可能なブロックか
				if (map[y][x] != 3&&68)
				{
					//衝突ブロックの左上座標を計算
					blocrect.x = x * MAP_CHIP_SIZE;
					blocrect.y = y * MAP_CHIP_SIZE;
					//ブロックとぶつかったか
					if (e_checkHitRect(enemyRect, blocrect))
					{
						//
						if ((enemyRect.y + enemyRect.h) - blocrect.y+2 <= MAX_OVERLAP_CAPACITY
							&& vy > 0.0f)
						{
							enemyRect.y = blocrect.y - enemyRect.h;
							vy = 0;
						}
						if (map[y][x] == 68)
						{
							vy -= 10;
							if (vy <= -10)
							{
								vy = -10;
							}
						}
						// ブロックの下端とぶつかった
						if ((blocrect.y + blocrect.h) - enemyRect.y <= MAX_OVERLAP_CAPACITY
							&& vy < 0.0f)
						{
							enemyRect.y = blocrect.y + blocrect.h + 5;
							vy = 0;
						}

						// ブロックの左端とぶつかった
						if ((enemyRect.x + enemyRect.w) - blocrect.x < MAX_OVERLAP_CAPACITY &&
							vx > 0.0f)
						{
							enemyRect.x = blocrect.x - enemyRect.w-1;
							vx = 0;
							if (onGround)
							{

							vy = -jumpPower;
							onGround = false;
							}
						}

						// ブロックの右端とぶつかった
						if ((blocrect.x + blocrect.w) - enemyRect.x < MAX_OVERLAP_CAPACITY &&
							vx < 0)
						{
							if (onGround)
							{

							vy = -jumpPower;
							onGround = false;
							}
							enemyRect.x = blocrect.x + blocrect.w;
							vx = 0;
						}
					}
				}
			}
		}

		// エネミーの1dot下に地面ブロックがあるかの確認
		// エネミー左下点のマップ番号算出
		chkye = (enemyRect.y + enemyRect.h) / MAP_CHIP_SIZE;
		chkxe = (enemyRect.x + 1) / MAP_CHIP_SIZE;
		onGround = true;

		if (map[chkye][chkxe] == 3)										// 左下点は空中か？
		{
			chkxe = (enemyRect.x + enemyRect.w - 1) / MAP_CHIP_SIZE;	//右下点も空中か？
			if (map[chkye][chkxe] == 3)
			{
				onGround = false;										//両足とも空中にいる
			}
		}
		//エネミー位置確定
		x = (float)enemyRect.x;
		y = (float)enemyRect.y;
	}

	if (!onGround)							//エネミーが空中にいるとき
	{
		vy += e_Gravity;					// y方向に重力加速度分加速させる
		
		if (vy > 10.0f)
		{
			vy = 10.0f;		// 落下最高速度以上いかないようにする
		}
	}
}
