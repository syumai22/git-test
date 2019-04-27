#include"DxLib.h"

// UI文字列.
#define	TITLE_STR			"ゴリラ忍者vs勇者"
#define	GAME_OVER_STR		"ゲームオーバー"
#define	GAME_CLEAR_STR		"ゲームクリア！"
#define	STARTBUTTON_STR		"スペースキーでスタート"
#define	RETURN_TITLE_STR	"スペースキーでタイトルへ"
#define	TIME_STR			"残り："

#define	TITLE_STR_OFFSET_Y - 100	// 見出し文字のyオフセット.
#define	PRESS_STR_OFFSET_Y		100		// ボタンを押してください系UIのyオフセット.
#define	TIME_STR_OFFSET_X		-100	// 制限時間(「残り」)のxオフセット.
#define	TIME_STR_POS_Y			25		// 残り時間UIのyポジション.
#define	TITLE_FONT_SIZE			64		// 見出し文字のフォントサイズ.
#define	PRESS_STR_FONT_SIZE		24		// ボタンを押してください系UIのサイズ.
#define	TIME_STR_FONT_SIZE		24		// 制限時間(「残り」)のフォントサイズ.
#define	TIME_NUM_STR_FONT_SIZE	40		// 制限時間(数字)のフォントサイズ.
#define	PLAYER_HP_FONT_SIZE		10		// プレイヤーの体力サイズ.
#define	PLAYER_HP_OFFSET_Y		5		// プレイヤー体力のオフセット.

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
	void DrawUI(Rule *rule,Player *player, Map *map,BitmapText text);
};

