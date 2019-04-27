#pragma once


#define LIMIT_TIME_COUNT	60		// ゲームの制限時間.
#define STATE_CHANGE_WAIT	500		// ステート切り替えウェイト(ミリ秒).

class Player;
class Sound;
class Enemy;

// ルール.
// 状態.
enum STATE
{
	STATE_INIT,
	STATE_TITLE,		// タイトル.
	STATE_GAME,			// ゲーム中.
	STATE_CLEAR,		// クリア.
	STATE_GAMEOVER,		// ゲームオーバー.
};
class Rule
{
public:
	int		gameStartTime	;
	int		state			;
	int		prevKeyInput	;
	int		frameCount		;

	bool	keyOn;
	bool	prevKeyOn;
	bool	keyRelease;
	bool	ProgramLooping = true;		// ゲームループを続けるか？

	void	InitRule();
	void	ChangeState(Player *player,Enemy *enemy,Map *map,Sound *sound,int pstate);
	void	UpdateRule(Player *player,Enemy *enemy,Map *map, Sound *sound,Rule *rule);
}; 
