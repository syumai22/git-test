#pragma once

#define SHOT_POWER			1		// �V���b�g�̈З�.
#define SHOT_SPEED			15		// �ʏ�V���b�g�̃X�s�[�h.S
#define SHOT_INTERVAL		5		// �ʏ�V���b�g�̔��˃C���^�[�o��.
#define SHOT				3		// �V���b�g�̍ő吔.

class Rule;

class Shot
{
public:
	int		    graph = -1;
	int         x;                      //�e�̍��W
	int         y;                      //�e�̍��W
	int			img_Shot[2];
	int			shotAnimNum;
	const int	shotAnimNum_End = 1;
	const int	shotAnimNum_Start = 0;
	bool        shotFlag = false;
	int			pshotHitFlag = false;
	bool	    visibleFlag = false;
	int         ss = 15;                //�e�̃X�s�[�h
	int		    w;
	int		    h;
	bool		dir = FALSE;
	void		InitShot();
	void		DrawShot(Rule *rule, Map *scr);
};