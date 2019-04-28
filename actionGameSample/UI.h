#include"DxLib.h"

// UI������.
#define	TITLE_STR			"�S�����E��vs�E��"
#define	GAME_OVER_STR		"�Q�[���I�[�o�["
#define	GAME_CLEAR_STR		"�Q�[���N���A�I"
#define	STARTBUTTON_STR		"�X�y�[�X�L�[�ŃX�^�[�g"
#define	RETURN_TITLE_STR	"�X�y�[�X�L�[�Ń^�C�g����"
#define	TIME_STR			"�c��F"

#define	TITLE_STR_OFFSET_Y - 100	// ���o��������y�I�t�Z�b�g.
#define	PRESS_STR_OFFSET_Y		100		// �{�^���������Ă��������nUI��y�I�t�Z�b�g.
#define	TIME_STR_OFFSET_X		-100	// ��������(�u�c��v)��x�I�t�Z�b�g.
#define	TIME_STR_POS_Y			25		// �c�莞��UI��y�|�W�V����.
#define	TITLE_FONT_SIZE			64		// ���o�������̃t�H���g�T�C�Y.
#define	PRESS_STR_FONT_SIZE		24		// �{�^���������Ă��������nUI�̃T�C�Y.
#define	TIME_STR_FONT_SIZE		24		// ��������(�u�c��v)�̃t�H���g�T�C�Y.
#define	TIME_NUM_STR_FONT_SIZE	40		// ��������(����)�̃t�H���g�T�C�Y.
#define	PLAYER_HP_FONT_SIZE		10		// �v���C���[�̗̑̓T�C�Y.
#define	PLAYER_HP_OFFSET_Y		5		// �v���C���[�̗͂̃I�t�Z�b�g.

class Rule;
class Player;
class sound;
class BitmapText;
class UI
{
public:
	int		hpGraph;
	int		hpber;
	int		hp_x;
	int		hp_y;
	int		titleBak;
	int		title;
	int		hiScore=0;
	int		gameOverBak;
	int		sky;
	int ae;
	int		R;
	int		G;
	int		B;
	int		colorCount;
	int GetDrawStringWidthFull(char* str)
	{
		return GetDrawStringWidth(str, (int)strlen(str));
	}

	void InitUI();
	void DrawUI(Rule *rule,Player *player,BitmapText text);
};

