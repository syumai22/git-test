#pragma once
#define PLAYER_LIFE			50		// �v���C���[�̃��C�t

class Enemy;
class Map;
class Rule;
class Sound;
class BitmapText;
class Player
{
public:
	float				x;								// �v���[���� x���W
	float				y;								// �v���[���� y���W
	float				vx;						// �v���[���� x�������x
	float				vy ;						// �v���[���� y�������x   
	float				next_x ;
	float				next_y ;
	const int			w = 24.0f;							// �v���[���[�̓����蔻�蕝
	const int			h = 32.0f;							// �v���[���[�̓����蔻�荂��
	int					state;							//�v���[���[�̏�� 0 �҂� 1����
	int					animNum;						// �A�j���[�V�����ԍ�
	int					p_modeflg ;					// �v���[���� ��ԃt���O( 0:�n�ʏ� 1:�� )
	int					atkAnimNum;
	int					atk;
	int					atkEfekt;
	int					atke;
	int					hp;
	int					hp_max;
	int					fraicount = 150;
	int					imgPlayer[16];					// �v���[���[�摜
	int					imgp_Atk[5];
	int					imgp_zan[3];
	int					p_xOffset;					// �`��ʒu�C��
	int					damagecont;					//�v���[���[�����Ƀ_���[�W���󂯂�܂ł̕b
	int					EfektAnimNum;
	int					fireEfektAnimNum;
	int					damageEfektAnimNum;
	int					img_recovery[5];
	int					img_damege[4];
	int					img_efe_fire[7];
	int					capsule;
	int					hpba;
	bool				dir;					//����
	bool				ani ;					//�A�j���[�V�����t���O
	bool				atkFlag ;
	bool				p_onGround = true;				// �v���[���͒n�ʂɗ����Ă��邩�H
	bool				zan = false;
	bool				ef;
	bool				damageFlag ;
	bool				damageEfctFlag ;
	bool				atkDamage;
	bool				efektFlag ;
	bool				fireEfektFlag ;
    bool                rightbrokflag;
    bool                leftbrokflag;
	bool				iltemsGetto[9];
	const int			anim_Wait_Start = 0;			//�҂�
	const int			anim_Walk_Start = 1;			// �����J�n 
	const int			anim_Walk_End = 7;				// �����I�� 
	const int			damageEfektAnim_Start = 0;
	const int			damageEfektAnim_End=4;
	const int			recoveryEfektAnim_Start=0;
	const int			recoveryEfektAnim_End = 5;
	const int			fireEfektAnim_start = 1;
	const int			fireEfektAnim_End = 7;
	const int			jnpAni = 12;					//�W�����v�i���o�[
	const int			Modification = 16;				//�`��ʒu�C��
	const int			efektModification_x = 48;
	const int			efektModification_y = 32;
	const int			atkAnimNum_End = 4;				//�U�����[�V�����I��
	const int			atkAnimNum_Start = 0;			//�U�����[�V�����J�n
	const int			atkEfekt_Start = 0;				//�U���G�t�F�N�g�J�n
	const int			atkEfekt_End = 3;				//�U���G�t�F�N�g�I��
	const int			rightAtkModification = 40;		//�U���G�t�F�N�g�̈ʒu�C���i�E�j
	const int			leftArkModification = 17;		//�U���G�t�F�N�g�̈ʒu�C���i���j
	const int			walkingMotionCount = 4;
	const int			atkEfektMotionCount = 2;
	const int			atkMotionCount = 7;
	static const float	epsiron;
	static const float	Accel;							// �v���[���� �����������x 
	static const float	Brake_Ratio;					// �v���[���� �u���[�L�W�� ( 1.0 �u���[�L�Ȃ� 0.0 �u���[�L���S�@)
	static const float	JumpPower;						// �v���[���[�̃W�����v�� �iMAX_OVERLAP�𒴂��Ȃ��͈͂�)
	static const float	Jumpbrake_Ratio;				// �W�����v�{�^���������ꂽ�Ƃ��̃u���[�L�W���i���������ō�����ׂ�j
	static const float	Gravity;						// �d�͉����x 
	static const int	MAX_OVERLAP_CAPACITY = 15;		// �Ǎő�߂荞�ݗ�

	void				PlayerBlocrect(Sound *sound, Rule *rule,Map *scr);
	void				MovePlayer(Sound *sound);
	void				PlayerAnime(Map *scr, Rule *rule, BitmapText text,Sound *sound);
	void				PlayerHitChec(Enemy *enemy,Map map,Sound *sound);
	void				InitPlayer();
	void				IitemHit(Map *scr,Enemy *enemy,Sound *sound);
};