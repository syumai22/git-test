#pragma once


#define LIMIT_TIME_COUNT	80		// �Q�[���̐�������.
#define STATE_CHANGE_WAIT	500		// �X�e�[�g�؂�ւ��E�F�C�g(�~���b).

class Player;
class Sound;
class Enemy;

// ���[��.
// ���.
enum STATE
{
	STATE_INIT,
	STATE_TITLE,		// �^�C�g��.
	STATE_GAME,			// �Q�[����.
	STATE_CLEAR,		// �N���A.
	STATE_GAMEOVER,		// �Q�[���I�[�o�[.
};
class Rule
{
public:
	int				gameStartTime	;
	int				state			;
	int				prevKeyInput	;
	int				frameCount		;

	bool			keyOn;
	bool			prevKeyOn;
	bool			keyRelease;
	bool			ProgramLooping = true;		// �Q�[�����[�v�𑱂��邩�H
	const int		enemuyCount=150;
	void			InitRule();
	void			ChangeState(Player *player,Enemy *enemy,Map *map,Sound *sound,int pstate);
	void			UpdateRule(Player *player,Enemy *enemy,Map *map, Sound *sound,Rule *rule);
}; 
