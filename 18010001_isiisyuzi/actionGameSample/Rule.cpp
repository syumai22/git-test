#include"Header.h"

// ������.
void Rule::InitRule()
{
	gameStartTime = 0;
	state = STATE_INIT;
	gameStartTime = 0;
	prevKeyInput = 0;
	frameCount = 0;
	keyOn = false;
	prevKeyOn = false;
	keyRelease = false;
}

// �X�e�[�g�؂�ւ�.
void Rule::ChangeState(Player *player,Enemy *enemy,Map *map,Sound *sound,int pstate)
{
	
	// �����ɐ؂�ւ�肷����̂ŁA������Ǝ��Ԃ��~�߂�.
	WaitTimer(STATE_CHANGE_WAIT);

	// �X�e�[�g���؂�ւ�����u�Ԃ̓L�[��������������Z�b�g.
	keyOn = false;
	keyRelease = false;

	state = pstate;
	
	switch (state)
	{

	case STATE_INIT:
		enemy->InitEnemy();
		sound->InitSound();
		// �^�C�g��.
	case STATE_TITLE:
		break;
		// �Q�[����.
	case STATE_GAME:
		gameStartTime = GetNowCount();
		sound->InitSound();
		player->InitPlayer();
		enemy->InitEnemy();
		map->InitMap();
		break;
	
		// �N���A���.
	case STATE_CLEAR:
		sound->InitSound();
		break;
		// �Q�[���I�[�o�[.
	case STATE_GAMEOVER:
		sound->InitSound();
	default:
		break;
	}

}

// �A�b�v�f�[�g.
void Rule::UpdateRule(Player *player, Enemy *enemy,Map *map, Sound *sound,Rule *rule)
{
	
	
	// �L�[�������u�Ԃ����.
	if (keyOn)
	{
		if (CheckHitKey(KEY_INPUT_SPACE) == 0)
		{
			keyOn = false;
			keyRelease = true;
			
		}
	}
	else if (prevKeyOn == false && CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		keyRelease = false;
		keyOn = true;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) == 11)
	{
		prevKeyOn = true;
	}
	else
	{
		prevKeyOn = false;
	}
	
	// �X�e�[�g���Ƃɏ������킯��.
	switch (state)
	{
		// �^�C�g��.
	case STATE_TITLE:
		if (keyRelease)
		{
			PlaySoundMem(sound->Decision, DX_PLAYTYPE_BACK);
			if(frameCount%20==0)
			{
				sound->ringSound(rule,STATE_GAME);
				ChangeState(player,enemy,map,sound,STATE_GAME);
			}
		}
		break;
		// �Q�[����.
	case STATE_GAME:
		
		if (player->y <= 210 && player->x <= -100 - map->X)
		{
			if (frameCount % 20 == 0)
			{
				sound->ringSound(rule, STATE_CLEAR);
				ChangeState(player, enemy, map, sound, STATE_CLEAR);
			}
		}
		else if ( player->hp <= 0|| GetNowCount() - gameStartTime > LIMIT_TIME_COUNT * 1000)
		{
			if (frameCount % 20 == 0)
			{
				sound->ringSound(rule, STATE_GAMEOVER);
				ChangeState(player, enemy, map, sound, STATE_GAMEOVER);
			}
		}
		
		break;
		// �N���A���.
	case STATE_CLEAR:
		if (keyRelease)
		{
		
			PlaySoundMem(sound->Decision, DX_PLAYTYPE_BACK);
			if (frameCount % 20 == 0)
			{
				sound->ringSound(rule, STATE_TITLE);
				ChangeState(player, enemy, map, sound, STATE_INIT);
			}
		}
		break;
		// �Q�[���I�[�o�[.
	case STATE_GAMEOVER:
		if (keyRelease)
		{
			
			PlaySoundMem(sound->Decision, DX_PLAYTYPE_BACK);
			if (frameCount % 20 == 0)
			{
				sound->ringSound(rule, STATE_TITLE);
				ChangeState(player, enemy, map, sound, STATE_INIT);
			}
		}
		break;
	default:
		break;
	}
}
