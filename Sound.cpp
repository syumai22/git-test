#include"Header.h"

void Sound::InitSound()
{
	win = LoadSoundMem("sound/wins.mp3");
	loos = LoadSoundMem("sound/looses.mp3");
	jump = LoadSoundMem("sound/jump.mp3");
	p_atk = LoadSoundMem("sound/p_atk.mp3");
	e_atk = LoadSoundMem("sound/e_atk.mp3");
	battle = LoadSoundMem("sound/battle.mp3");
	title_s = LoadSoundMem("sound/title.mp3");
	decide = LoadSoundMem("sound/kettei.mp3");
	idou = LoadSoundMem("sound/sentakuidou.mp3");
	powerJump = LoadSoundMem("sound/jump02.mp3");
	cure = LoadSoundMem("sound/magic-cure2.mp3");
	flame = LoadSoundMem("sound/magic-flame2.mp3");
	Decision = LoadSoundMem("sound/kettei-02.wav");
}

void Sound::ringSound(Rule *rule,int sou)
{
	WaitTimer(STATE_CHANGE_WAIT);

	rule->state = sou;
	switch (rule->state)
	{
		
		 //タイトル.
	case STATE_TITLE:
		StopSoundMem(win);
		StopSoundMem(loos);
		PlaySoundMem(title_s, DX_PLAYTYPE_BACK);//BGMを再生する
		
	break;
	 //ゲーム中.
	case STATE_GAME:
	
		StopSoundMem(title_s);
		PlaySoundMem(battle, DX_PLAYTYPE_BACK);//戦闘BGMを再生する

	break;
	 //クリア画面.
	case STATE_CLEAR:
		
		StopSoundMem(battle);
		PlaySoundMem(win, DX_PLAYTYPE_BACK);//BGMを再生する
		
		break;

	case STATE_GAMEOVER:
	
			StopSoundMem(battle);
			PlaySoundMem(loos, DX_PLAYTYPE_BACK);//BGMを再生する

		break;
	default:
		break;
		
	}
	
	
}

void Sound::TitleSound(Rule *rule)
{
	if(rule->state== STATE_TITLE)
	{
		if (CheckSoundMem(loos|| win) == 1)
		{
			StopSoundMem(loos);
			StopSoundMem(win);
		}
		PlaySoundMem(title_s, DX_PLAYTYPE_BACK);//BGMを再生する
	}
	
}
void Sound::GameSound(Rule *rule)
{
	if (rule->state == STATE_GAME)
	{
		if (CheckSoundMem(title_s) == 1)
		{
			StopSoundMem(title_s);
		}
		PlaySoundMem(battle, DX_PLAYTYPE_BACK);//戦闘BGMを再生する
	}
	

}
void Sound::GameoverSound(Rule *rule)
{
	if (rule->state == STATE_GAMEOVER)
	{
		if (CheckSoundMem(battle) == 1)
		{
			StopSoundMem(battle);
		}
		PlaySoundMem(loos, DX_PLAYTYPE_BACK);//BGMを再生する
	}

}