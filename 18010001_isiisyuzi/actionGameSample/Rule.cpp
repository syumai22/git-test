#include"Header.h"

// 初期化.
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

// ステート切り替え.
void Rule::ChangeState(Player *player,Enemy *enemy,Map *map,Sound *sound,int pstate)
{
	
	// 即座に切り替わりすぎるので、ちょっと時間を止める.
	WaitTimer(STATE_CHANGE_WAIT);

	// ステートが切り替わった瞬間はキー離した判定をリセット.
	keyOn = false;
	keyRelease = false;

	state = pstate;
	
	switch (state)
	{

	case STATE_INIT:
		enemy->InitEnemy();
		sound->InitSound();
		// タイトル.
	case STATE_TITLE:
		break;
		// ゲーム中.
	case STATE_GAME:
		gameStartTime = GetNowCount();
		sound->InitSound();
		player->InitPlayer();
		enemy->InitEnemy();
		map->InitMap();
		break;
	
		// クリア画面.
	case STATE_CLEAR:
		sound->InitSound();
		break;
		// ゲームオーバー.
	case STATE_GAMEOVER:
		sound->InitSound();
	default:
		break;
	}

}

// アップデート.
void Rule::UpdateRule(Player *player, Enemy *enemy,Map *map, Sound *sound,Rule *rule)
{
	
	
	// キー離した瞬間を取る.
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
	
	// ステートごとに処理をわける.
	switch (state)
	{
		// タイトル.
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
		// ゲーム中.
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
		// クリア画面.
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
		// ゲームオーバー.
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
