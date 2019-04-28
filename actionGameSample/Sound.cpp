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
	IltemuGet= LoadSoundMem("sound/iltemget.mp3");
}

void Sound::ringSound(Rule *rule)
{

		 //ƒ^ƒCƒgƒ‹.
	if(rule->state==STATE_TITLE)
	{
		if (CheckSoundMem(loos) == 1)
		{
				
			StopSoundMem(loos);
		}
		if (CheckSoundMem(win) == 1)
		{
			StopSoundMem(win);
		}

		if(CheckSoundMem(title_s)==0)
		{
			PlaySoundMem(title_s, DX_PLAYTYPE_BACK);//BGM‚ğÄ¶‚·‚é
		}
	}

	if (rule->state == STATE_GAME)
	{
		int check = CheckSoundMem(title_s);
 		if (check == 1)
		{
			StopSoundMem(title_s);
		}
		if (CheckSoundMem(battle) == 0)
		{
			PlaySoundMem(battle, DX_PLAYTYPE_BACK);//í“¬BGM‚ğÄ¶‚·‚é
		}
	
	}
	if (rule->state == STATE_CLEAR)
	{

		if (CheckSoundMem(battle) == 1)
		{
			StopSoundMem(battle);
		}
		if (CheckSoundMem(win) == 0)
		{
			PlaySoundMem(win, DX_PLAYTYPE_BACK);//BGM‚ğÄ¶‚·‚é
		}

	}
	if (rule->state == STATE_GAMEOVER)
	{

		if (CheckSoundMem(battle) == 1)
		{
			StopSoundMem(battle);
		}
		if (CheckSoundMem(loos) == 0)
		{
			PlaySoundMem(loos, DX_PLAYTYPE_BACK);//BGM‚ğÄ¶‚·‚é
		}
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
		PlaySoundMem(title_s, DX_PLAYTYPE_BACK);//BGM‚ğÄ¶‚·‚é
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
		PlaySoundMem(battle, DX_PLAYTYPE_BACK);//í“¬BGM‚ğÄ¶‚·‚é
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
		PlaySoundMem(loos, DX_PLAYTYPE_BACK);//BGM‚ğÄ¶‚·‚é
	}

}