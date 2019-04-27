#pragma once
#define PLAYER_LIFE			50		// プレイヤーのライフ

class Enemy;
class Map;
class Rule;
class Sound;
class BitmapText;
class Player
{
public:
	float				x;								// プレーヤの x座標
	float				y;								// プレーヤの y座標
	float				vx;						// プレーヤの x方向速度
	float				vy ;						// プレーヤの y方向速度   
	float				next_x ;
	float				next_y ;
	const int			w = 24;							// プレーヤーの当たり判定幅
	const int			h = 32;							// プレーヤーの当たり判定高さ
	int					state;							//プレーヤーの状態 0 待ち 1歩き
	int					animNum;						// アニメーション番号
	int					p_modeflg ;					// プレーヤの 状態フラグ( 0:地面上 1:空中 )
	int					atkAnimNum;
	int					atk;
	int					atkEfekt;
	int					atke;
	int					hp;
	const int			hp_max=50;
	int					fraicount = 100;
	int					imgPlayer[16];					// プレーヤー画像
	int					imgp_Atk[5];
	int					imgp_zan[3];
	int					p_xOffset;					// 描画位置修正
	int					damagecont;					//プレーヤーが次にダメージを受けるまでの秒
	int					EfektAnimNum;
	int					fireEfektAnimNum;
	int					damageEfektAnimNum;
	int					img_recovery[5];
	int					img_damege[4];
	int					img_efe_fire[7];
	int					capsule;
	bool				dir;					//向き
	bool				ani ;					//アニメーションフラグ
	bool				atkFlag ;
	bool				p_onGround = true;				// プレーヤは地面に立っているか？
	bool				zan = false;
	bool				ef;
	bool				damageFlag ;
	bool				damageEfctFlag ;
	bool				atkDamage = false;
	bool				efektFlag ;
	bool				fireEfektFlag ;
	bool				iltemsGetto;
	const int			anim_Wait_Start = 0;			//待ち
	const int			anim_Walk_Start = 1;			// 歩き開始 
	const int			anim_Walk_End = 7;				// 歩き終了 
	const int			jnpAni = 12;					//ジャンプナンバー
	const int			atkAnimNum_End = 4;				//攻撃モーション終了
	const int			atkAnimNum_Start = 0;			//攻撃モーション開始
	const int			atkEfekt_Start = 0;				//攻撃エフェクト開始
	const int			atkEfekt_End = 3;				//攻撃エフェクト終了
	const int			rightAtkModification = 40;		//攻撃エフェクトの位置修正（右）
	const int			leftArkModification = 17;		//攻撃エフェクトの位置修正（左）
	const int			walkingMotionCount = 4;
	const int			atkEfektMotionCount = 2;
	const int			atkMotionCount = 7;
	static const float	epsiron;
	static const float	Accel;							// プレーヤの 横方向加速度 
	static const float	Brake_Ratio;					// プレーヤの ブレーキ係数 ( 1.0 ブレーキなし 0.0 ブレーキ完全　)
	static const float	JumpPower;						// プレーヤーのジャンプ力 （MAX_OVERLAPを超えない範囲で)
	static const float	Jumpbrake_Ratio;				// ジャンプボタンが離されたときのブレーキ係数（押し続けで高く飛べる）
	static const float	Gravity;						// 重力加速度 
	static const int	MAX_OVERLAP_CAPACITY = 15.0f;		// 壁最大めり込み量

	void				PlayerBlocrect(Sound *sound, Rule *rule,Map *scr);
	void				MovePlayer(Sound *sound);
	void				PlayerAnime(Map *scr, Rule *rule, BitmapText text,Sound *sound);
	void				PlayerHitChec(Enemy *enemy,Map map,Sound *sound);
	void				InitPlayer();
};