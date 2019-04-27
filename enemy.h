#pragma once

#define ENEMY_SPEED			3		// 敵のスピード.
#define ENEMY_LIFE			5	// 敵のライフ.

class Player;
class Map;
class Rule;
class BitmapText;

class Enemy
{
public:
	float				x;									//x.yの座標
	float				y;									
	float				vx;									//vx,vyの座標
	float				vy;
	float				nextE_x ;
	float				nextE_y ;
	int					imgEnemy[4];								//エネミー画像	
	int					aniNum;
	const int			w = 24;										// エネミーの当たり判定幅
	const int			h = 32;										// エネミーの当たり判定高さ
	int					onGround = true;
	int					hp;
	int					Atke;
	int					damagecont ;					//次にダメージを受けるまでの秒
	bool				damageFlag = false;
	//ランダムに敵を沸かせる
	int ranodmRange(int min, int max)
	{
		int				range = max - min;
		int				ret;
		if (min < 0)
		{
						ret = rand() % range - (range / 2);
		}
		else
		{
						ret = rand() % range;
		}
		return ret;
	}
	int GetDrawStringWidthFull(char* str)
	{
		return GetDrawStringWidth(str, (int)strlen(str));
	}
	const int			anim_Walk_Start = 0;						// 歩き開始 
	const int			anim_Walk_End = 4;							// 歩き終了 
	bool				dir = FALSE;
	bool				aliveFlg = FALSE;									//生きているか
	bool				dame = FALSE;

	static const float  jumpPower;
	static const float  e_Gravity;									// 重力加速度 
	const int			MAX_OVERLAP_CAPACITY = 15;					// 壁最大めり込み量
	
	void				InitEnemy();
	void				DrawEnemy(Player *playe,Map *scr,Rule *rule, BitmapText *text);
	void				AddEnemy(int ex,int ey, int evx, int evy);
	void				BlocRectEnemy();
};