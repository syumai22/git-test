#pragma once

#define SHOT_POWER			1		// ショットの威力.
#define SHOT_SPEED			15		// 通常ショットのスピード.S
#define SHOT_INTERVAL		5		// 通常ショットの発射インターバル.
#define SHOT				3		// ショットの最大数.

class Rule;

class Shot
{
public:
	int		    graph = -1;
	int         x;                      //弾の座標
	int         y;                      //弾の座標
	int			img_Shot[2];
	int			shotAnimNum;
	const int	shotAnimNum_End = 1;
	const int	shotAnimNum_Start = 0;
	bool        shotFlag = false;
	int			pshotHitFlag = false;
	bool	    visibleFlag = false;
	int         ss = 15;                //弾のスピード
	int		    w;
	int		    h;
	bool		dir = FALSE;
	void		InitShot();
	void		DrawShot(Rule *rule, Map *scr);
};