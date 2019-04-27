#include"Header.h"

const float Player::Accel				= 0.3f;					// �v���[���� �����������x 
const float Player::Brake_Ratio			= 0.2f;
const float Player::JumpPower			= 8.0f;
const float Player::Jumpbrake_Ratio		= 0.3f;
const float Player::Gravity				= 0.3f;
const float	Player::epsiron				= 0.4f;

bool p_checkHitRect(rect r1, rect r2)
{
		return ((r1.x < (r2.x + r2.w)) &&
				(r2.x < (r1.x + r1.w)) &&
				(r1.y < (r2.y + r2.h)) &&
				(r2.y < (r1.y + r1.h)));
}

void Player::InitPlayer()
{
	LoadDivGraph("image/player.png", 16, 16, 1, 32, 32, imgPlayer);
	LoadDivGraph("image/player2.png", 5, 5, 1, 32, 32, imgp_Atk);
	LoadDivGraph("image/kiru.png", 3, 3, 1, 32, 32,	imgp_zan);
	LoadDivGraph("image/efe_fire.png", 8, 8, 1, 32, 32, img_efe_fire);
	LoadDivGraph("image/recovery2.png", 6, 6, 1, 128, 126,img_recovery);
	LoadDivGraph("image/uke.png", 5, 5, 1, 120, 120, img_damege);

	capsule = LoadGraph("image/capser.bmp");
	x= 80.0f;
	y = 3110.0f;
	vx = 0.0f;
	vy = 0.0f;
	hp = PLAYER_LIFE;
	atk=1;
	p_xOffset = 13.0f;
	damagecont = 1.5f;
	animNum = anim_Walk_Start;
	atkAnimNum = 0;
	atkEfekt = 0;
	EfektAnimNum = 0;
	fireEfektAnimNum=0;
	damageEfektAnimNum=0;
	ani =false;
	atkFlag = false;
	iltemsGetto = false;
	damageFlag= false;
	damageEfctFlag = false;
	fireEfektFlag = false;
	efektFlag = false;
	damageFlag = false;
	ef = false;
	dir = FALSE;
}

//�A�j���[�V����
void Player::PlayerAnime(Map *scr,Rule *rule,BitmapText text,Sound *sound)
{
	
	if (ani == true)
	{
	
		//�ړ��A�j���\�V����
		if (rule->frameCount % walkingMotionCount == 0)
		{
			animNum++;
		}
	
		if (animNum >=anim_Walk_End)
		{
			animNum = anim_Walk_Start;
		}
		else if (!(INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT)) &&
			!(INPUT_INSTANCE.getInput(KEY_INPUT_LEFT)))
		{
			animNum = anim_Wait_Start;
		}
		//�W�����v�A�j���[�V����
		if (!p_onGround)
		{
			animNum = jnpAni;
		}
	}
	else
	{
		ani = false;
	}
	//�v���[���̍U���A�j���[�V����
	if (atkFlag == true)
	{
		vx = 0;

		if (rule->frameCount % atkMotionCount == 0)
		{
			atkAnimNum++;
		}
		if (rule->frameCount % atkEfektMotionCount == 0)
		{
			atkEfekt++;
		}
		if (atkEfekt == atkEfekt_End)
		{
			atkEfekt = atkEfekt_Start;
		}
		if (atkAnimNum == atkAnimNum_End)
		{
			atkAnimNum = atkAnimNum_Start;
			atkFlag = false;
		}
		if (dir == TRUE)
		{
			DrawRotaGraph(x + rightAtkModification - scr->X, y - scr->Y + 16, 1.0f, 0, imgp_zan[atkEfekt], TRUE, dir);
		}
		else
		{
			DrawRotaGraph(x - leftArkModification - scr->X, y - scr->Y + 16, 1.0f, 0, imgp_zan[atkEfekt], TRUE, dir);
		}
	}
	else
	{
		atkFlag = false;
	}
	
	//�v���C���[�U���摜�ւ̉摜�؂�ւ�
	if (atkFlag == true)
	{
		DrawRotaGraph(x + p_xOffset - scr->X, y - scr->Y + 16, 1.0f, 0, imgp_Atk[atkAnimNum], TRUE, dir);
	}
	if(!atkFlag )
	{
		if(!damageEfctFlag )
		{
			DrawRotaGraph(x + p_xOffset - scr->X, y - scr->Y + 16, 1.0f, 0, imgPlayer[animNum], TRUE, dir);	
		}
		if (damageEfctFlag== true|| fireEfektFlag == true)
		{
			
			if (rule->frameCount % 10 == 0)
			{
				text.setFontColor(255, 0, 0);
				DrawRotaGraph(x + p_xOffset - scr->X, y - scr->Y + 16, 1.0f, 0, imgPlayer[animNum], TRUE, dir);
				text.setFontColor(255, 255, 255);
			}
		}
	}
	//�_���[�W�G�t�F�N�g
	if (rule->frameCount % 5 == 0)
	{
		damageEfektAnimNum++;
	}
	
	if (damageEfctFlag == true)
	{
		DrawGraph(x - scr->X - 48, y - scr->Y - 32, img_damege[damageEfektAnimNum], TRUE);
	}
	if (damageEfektAnimNum == 4)
	{
		damageEfektAnimNum = 0;
	}
	//�񕜃G�t�F�N�g
	if (rule->frameCount % 8 == 0)
	{
		EfektAnimNum++;
		
	}
	if (EfektAnimNum == 5)
	{
		EfektAnimNum =0;
	}
	if (efektFlag == true)
	{
		
		DrawGraph(x - scr->X - 48, y - scr->Y - 32, img_recovery[EfektAnimNum], TRUE);
	}
	//�t�@�C�A�G�t�F�N�g
	if (rule->frameCount % 8 == 0)
	{
		fireEfektAnimNum++;
	}
	if (fireEfektAnimNum == 7)
	{
		fireEfektAnimNum = 1;
	}
	if (fireEfektFlag == true)
	{	
		DrawGraph(x - scr->X, y - scr->Y + 5, img_efe_fire[fireEfektAnimNum], TRUE);
	}
	
	/*if(!iltemsGetto)
	{
		DrawGraph(150-scr->X,2010-scr->Y, capsule,TRUE);
	}
	
	if (x<= 150 -scr->X&& y <= 2010-scr->Y)
	{
		iltemsGetto = true;
	}*/
	
}


////////////////////////////////////////////////////////
// �v���[���[�ړ�����
////////////////////////////////////////////////////////
//�v���[���[�̈ړ�
void Player::MovePlayer(Sound *sound)
{

	//�E�ړ�����
	if (INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT))
	{
		//����
		dir = TRUE;
		if (!ef)
		{
			ani = true;
		}
		if (INPUT_INSTANCE.getInput(KEY_INPUT_D)
			&&p_onGround)
		{
			if (vx <= 5.0f)
			{
				vx = 5.0f ;
			}
		}
		else if (vx <= 2.0f)
		{
			vx += Accel;
		}
		if (vx > MAX_OVERLAP_CAPACITY)
		{
			vx = MAX_OVERLAP_CAPACITY;
		}
	}
	//���ړ�����
	if (INPUT_INSTANCE.getInput(KEY_INPUT_LEFT))
	{
		dir = FALSE;
		if(!ef)
		{
			ani = true;
		}
		if (INPUT_INSTANCE.getInput(KEY_INPUT_D)
			&& p_onGround)
		{
			if (vx >= -5.0f)
			{
				vx += -5.0f;
			}
		}
		if (vx >= -2.0f)
		{
			vx -=Accel;
		}
		if (vx < -MAX_OVERLAP_CAPACITY)
		{
			vx = -MAX_OVERLAP_CAPACITY;
		}
	}
	//�U��
	if (INPUT_INSTANCE.getInput(KEY_INPUT_Z) == 1)
	{
		PlaySoundMem(sound->p_atk, DX_PLAYTYPE_BACK); // �U�����ʉ����Đ�����
		zan = true;
		atkFlag = true;
		atkDamage = true;
		damageFlag =true;
		if (vx < 0.0f && vx > -epsiron)
		{
			vx = 0.0f;
		}
		
	}
	else
	{
		fraicount = 100;
	}
	
	//�u���[�L
	if (!(INPUT_INSTANCE.getInput(KEY_INPUT_RIGHT)) &&
		!(INPUT_INSTANCE.getInput(KEY_INPUT_LEFT)))
	{
		vx *= Brake_Ratio;
	}

	//����h�~
	/*if (vx < 0.0f && vx > -epsiron)
	{
		vx = 0.0f;
	}*/
	/*if (vy< 0.0f && vy > -epsiron)
	{
		vy = 0.0f;
	}*/

	// �W�����v�{�^��������
	if (INPUT_INSTANCE.getInput(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN
		&& p_onGround)
	{
		ani = true;
		vy = -JumpPower;
		p_onGround = false;
		PlaySoundMem(sound->jump, DX_PLAYTYPE_BACK); // �W�����v���ʉ����Đ�����
	}
	
	//�󒆂ɂ���Ƃ�
	if (!p_onGround)
	{
		ani = true;
		// y�����ɏd�͉����x������������
		vy += Gravity;
		// �����ō����x�ȏア���Ȃ��悤�ɂ���
		if (vy >=10.0f)
		{
			vy =10.0f;
		}
	}
	if (!p_onGround)
	{
		if (INPUT_INSTANCE.getInput(KEY_INPUT_C))
		{
			vy += 1.0f;
		}
	}
	
	//�b��v���[���[�ʒu�Z�o
	next_x = x + vx;
	next_y = y + vy;
}

void Player::PlayerBlocrect(Sound *sound,Rule *rule,Map *scr)
{
	rect playerRect, blocrect,activeBlocrect;
	//////////////////////////////
	//�v���C���[�ƕǂ̓����蔻��
	/////////////////////////////

	//�v���[���[�̎b���̒Z�`
	playerRect.x = next_x;
	playerRect.y = next_y;
	playerRect.w = w;
	playerRect.h = h;

	//�u���b�N��`
	blocrect.w = MAP_CHIP_SIZE;
	blocrect.h = MAP_CHIP_SIZE;
	activeBlocrect.w= MAP_CHIP_SIZE;
	activeBlocrect.h = MAP_CHIP_SIZE;
	
	//�v���C���[��������}�b�v�Y�����ԍ����Z�o
	//����
	int chkx = playerRect.x / MAP_CHIP_SIZE;
	int chky = playerRect.y / MAP_CHIP_SIZE;
	//�E��
	int maxchkx = (playerRect.x + playerRect.w) / MAP_CHIP_SIZE;
	int maxchky = (playerRect.y + playerRect.h) / MAP_CHIP_SIZE;
	
	if ((chkx >= 0 && chky > 0) || (chkx <= MAP_WIDTH && chky <= MAP_HEIGHT))
	{
		//������\���̂��邷�ׂẴu���b�N�𒲂ׂ�
		for (int x = chkx; x <= maxchkx; x++)
		{
			for (int y = chky; y <= maxchky; y++)
			{
				//�����͒ʍs�s�\�ȃu���b�N��
				if (map[y][x] != 3&&map[y][x] != 73)
				{
					//�Փ˃u���b�N�̍�����W���v�Z
					blocrect.x = x * MAP_CHIP_SIZE;
					blocrect.y = y * MAP_CHIP_SIZE;
					//�u���b�N�ƂԂ�������
					if (p_checkHitRect(playerRect, blocrect))
					{
						if ((playerRect.y + playerRect.h) - blocrect.y+4<= MAX_OVERLAP_CAPACITY
							&& vy > 0.0f)
						{
							
							playerRect.y = blocrect.y - playerRect.h;
							vy = 0;
							
							if (map[y][x] == 68)
							{

								vy -= 10.0f;
								if (vy <= -10.0f)
								{
									vy = -10.0f;
								}
								PlaySoundMem(sound->powerJump, DX_PLAYTYPE_BACK);
							}
						}
					
						// �u���b�N�̉��[�ƂԂ�����
						if ((blocrect.y + blocrect.h) - playerRect.y <= MAX_OVERLAP_CAPACITY
							&& vy < 0.0f)
						{
							playerRect.y = blocrect.y + blocrect.h + 5.0f;
							vy = 0.0f;
						}

						// �u���b�N�̍��[�ƂԂ�����
						if ((playerRect.x + playerRect.w) - blocrect.x+2.0f < MAX_OVERLAP_CAPACITY &&
							vx > 0.0f)
						{
							playerRect.x = blocrect.x - playerRect.w+0.8f;
							vx = 0.0f;
						}

						// �u���b�N�̉E�[�ƂԂ�����
						if ((blocrect.x + blocrect.w) - playerRect.x< MAX_OVERLAP_CAPACITY &&
							vx < 0.0f)
						{
							playerRect.x = blocrect.x + blocrect.w;
							vx = 0.0f;
						}
		
					
					}
					
				}
			
				if (map[y][x] == 73)
				{
					vy-=1.0f;
					if (vy <= 10.0f)
					{
						vy = 10.0f;
					}
				}
				if (map[y][x] == 10)
				{
					fireEfektFlag = true;
					
					if(rule->frameCount%10==0)
					{ 
						
						hp -= 1;
					}
					if (rule->frameCount % 60 == 0)
					{
						PlaySoundMem(sound->flame, DX_PLAYTYPE_BACK);
					}
				}
				else
				{
					fireEfektFlag = false;
				}
				if (map[y][x] == 9)
				{
					vx+=0.6f;
					if (vx <= 5.0f)
					{
						vx = 5.0f;
					}
				}
				if (map[y][x] == 19)
				{
					vx-=0.6f;
					if (vx <= -5.0f)
					{
						vx = -5.0f;
					}
				}

				if (map[y][x] == 24)
				{
					
					if (hp < 50)
					{
						efektFlag = true;
						if (rule->frameCount % 10 == 0)
						{	
							
							hp+=1;
						}
						if (rule->frameCount % 60 == 0)
						{
							PlaySoundMem(sound->cure, DX_PLAYTYPE_BACK);
						}
					}
				}
				else
				{
					efektFlag = false;
				}
			}
		}
		
		
	}
	//if ((chkx >= 0) || (chkx <= 3))
	//{
	//	for (int x = chkx; x <= maxchkx; x++)
	//	{
	//		if (scr->ActiveBlock[x] == 8)
	//		{
	//			if (p_checkHitRect(playerRect, activeBlocrect))
	//			{
	//				activeBlocrect.x = x * MAP_CHIP_SIZE;
	//				activeBlocrect.y = MAP_CHIP_SIZE;
	//				if ((playerRect.y + playerRect.h) - activeBlocrect.y + 4 <= MAX_OVERLAP_CAPACITY
	//					&& vy > 0.0f)
	//				{

	//					playerRect.y = activeBlocrect.y - playerRect.h;
	//					vy = 0;
	//				}

	//				// �u���b�N�̉��[�ƂԂ�����
	//				if ((activeBlocrect.y + activeBlocrect.h) - playerRect.y <= MAX_OVERLAP_CAPACITY
	//					&& vy < 0.0f)
	//				{
	//					playerRect.y = activeBlocrect.y + activeBlocrect.h + 5.0f;
	//					vy = 0.0f;
	//				}

	//				// �u���b�N�̍��[�ƂԂ�����
	//				if ((playerRect.x + playerRect.w) - activeBlocrect.x + 2.0f < MAX_OVERLAP_CAPACITY &&
	//					vx > 0.0f)
	//				{
	//					playerRect.x = activeBlocrect.x - playerRect.w + 0.8f;
	//					vx = 0.0f;
	//				}

	//				// �u���b�N�̉E�[�ƂԂ�����
	//				if ((activeBlocrect.x + activeBlocrect.w) - playerRect.x < MAX_OVERLAP_CAPACITY &&
	//					vx < 0.0f)
	//				{
	//					playerRect.x = activeBlocrect.x + activeBlocrect.w;
	//					vx = 0.0f;
	//				}


	//			}
	//		}
	//	}
	//}
	// �v���[���[��1dot���ɒn�ʃu���b�N�����邩�̊m�F
	// �v���[���[�����_�̃}�b�v�ԍ��Z�o
	chky = (playerRect.y + playerRect.h) / MAP_CHIP_SIZE;
	chkx = (playerRect.x + 1 ) / MAP_CHIP_SIZE;

	p_onGround = true;
	// �����_�͋󒆂��H
	if (map[chky][chkx] == 3)
	{
		//�E���_���󒆂��H
		chkx = (playerRect.x + playerRect.w - 1) / MAP_CHIP_SIZE;
		if (map[chky][chkx] == 3)
		{
			//�����Ƃ��󒆂ɂ���
			p_onGround = false;
		}
	}
	// �v���[���ʒu�m��
	x = (float)playerRect.x;
	y = (float)playerRect.y;

	
}

void Player::PlayerHitChec(Enemy *enemy,Map scr,Sound *sound)
{
	
	rect PlayerHitChecRect, EnemyHitChecRect;
	PlayerHitChecRect.x = x-scr.X;
	PlayerHitChecRect.y = y-scr.Y;
	PlayerHitChecRect.w = w;
	PlayerHitChecRect.h = h;

	EnemyHitChecRect.x = enemy->x - scr.X;
	EnemyHitChecRect.y = enemy->y - scr.Y;
	EnemyHitChecRect.w = enemy->w;
	EnemyHitChecRect.h = enemy->h;

	/*rect PlayerrightAtkHitChec, PlayerLeftatkHitChec;
	PlayerrightAtkHitChec.x=  x-scr.X+ rightAtkModification;
	PlayerrightAtkHitChec.y =y-scr.Y;
	PlayerrightAtkHitChec.w=w;
	PlayerrightAtkHitChec.h=h;

	PlayerLeftatkHitChec.x= x - scr.X + leftArkModification;
	PlayerLeftatkHitChec.y = y - scr.Y;
	PlayerLeftatkHitChec.w=w;
	PlayerLeftatkHitChec.h=h;
	
	if(dir==true)
	{
		if(atkDamage == true)
		{
			if (p_checkHitRect(PlayerrightAtkHitChec, EnemyHitChecRect))
			{
				if(enemy->aliveFlg == true)
				{
					enemy->hp-=1;
					enemy->damagecont=0;
					atkDamage = false;
				}
			}
		}
	}
	else
	{
		if (atkDamage == true)
		{
			if (p_checkHitRect(PlayerLeftatkHitChec, EnemyHitChecRect))
			{
				if (enemy->aliveFlg == true)
				{
					enemy->hp -= 1;
					enemy->damagecont = 0;
					atkDamage = false;
				}
			}
		}
	}
	if (!atkDamage)
	{
		if(enemy->damagecont==30)
		{ 
			atkDamage = false;
		}
	}*/
	if (ef)
	{
		if (p_checkHitRect(PlayerHitChecRect, EnemyHitChecRect))
		{
			//�G�̏�[
			if ((PlayerHitChecRect.y + PlayerHitChecRect.h) - EnemyHitChecRect.y + 2 <= MAX_OVERLAP_CAPACITY
				&& vy > 0.0f)
			{
				PlayerHitChecRect.y = EnemyHitChecRect.y - PlayerHitChecRect.h;
				vy -= 4.0f;
				if (dir = true)
				{
					enemy->vx+=4.0f;
				}
				else
				{
					enemy->vx -= 4.0f;
				}
			}
			// �G�̉��[
			if ((EnemyHitChecRect.y + EnemyHitChecRect.h) - PlayerHitChecRect.y <= MAX_OVERLAP_CAPACITY
			&& vy < 0.0f)
			{
				PlayerHitChecRect.y = EnemyHitChecRect.y + EnemyHitChecRect.h + 5;
				vy = 0.0f;
			}

			//�G�̍��[ 
			if ((PlayerHitChecRect.x + PlayerHitChecRect.w) - EnemyHitChecRect.x < 24 &&
				vx > 0.0f)
			{
				PlayerHitChecRect.x = EnemyHitChecRect.x - PlayerHitChecRect.w;
				vx = 0.0f;
				damagecont = 0;
				ani = false;
				if (enemy->dir)
				{
					vx+=4.0f;
				}
				else
				{
					vx -= 4.0f;
				}
				PlaySoundMem(sound->e_atk, DX_PLAYTYPE_BACK);
				hp -= enemy->Atke;//�q�b�g�|�C���g���Z				
				ef = false;//�����薳��
				damageEfctFlag=true;
			}
			
			//�G�̉E�[ 
			if ((EnemyHitChecRect.x + EnemyHitChecRect.w) - PlayerHitChecRect.x < 24 &&
			vx < 0)
			{
				PlayerHitChecRect.x = EnemyHitChecRect.x + EnemyHitChecRect.w;
				vx = 0.0f;
				damagecont = 0;
				ani = false;
				if (enemy->dir)
				{
					vx += 4.0f;
				}
				else
				{
					vx -= 4.0f;
				}
				PlaySoundMem(sound->e_atk, DX_PLAYTYPE_BACK);
				hp -= enemy->Atke;//�q�b�g�|�C���g���Z
				ef = false;//�����薳��
				damageEfctFlag = true;
			}
		}
	}
	if (!ef)
	{
		if (damagecont == 60)
		{
			ef = true;//������L��
		;
		}
		if (damagecont == 10)
		{
			damageEfctFlag = false;
		}
		
	}
	
	/*printfDx("leftPos:%  leftHbaPos:%d\n", leftPos, leftHbaPos);*/
}