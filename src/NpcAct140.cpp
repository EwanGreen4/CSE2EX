#include "WindowsWrapper.h"

#include "NpcAct.h"

#include "MyChar.h"
#include "NpChar.h"
#include "Game.h"
#include "Sound.h"
#include "Back.h"
#include "Triangle.h"
#include "Caret.h"
#include "Frame.h"
#include "Flash.h"
#include "Bullet.h"

//Toroko (frenzied)
void ActNpc140(NPCHAR *npc)
{
	RECT rcLeft[14];
	RECT rcRight[14];

	rcLeft[0] = {0, 0, 32, 32};
	rcLeft[1] = {32, 0, 64, 32};
	rcLeft[2] = {64, 0, 96, 32};
	rcLeft[3] = {96, 0, 128, 32};
	rcLeft[4] = {128, 0, 160, 32};
	rcLeft[5] = {160, 0, 192, 32};
	rcLeft[6] = {192, 0, 224, 32};
	rcLeft[7] = {224, 0, 256, 32};
	rcLeft[8] = {0, 64, 32, 96};
	rcLeft[9] = {32, 64, 64, 96};
	rcLeft[10] = {64, 64, 96, 96};
	rcLeft[11] = {96, 64, 128, 96};
	rcLeft[12] = {128, 64, 160, 96};
	rcLeft[13] = {0, 0, 0, 0};

	rcRight[0] = {0, 32, 32, 64};
	rcRight[1] = {32, 32, 64, 64};
	rcRight[2] = {64, 32, 96, 64};
	rcRight[3] = {96, 32, 128, 64};
	rcRight[4] = {128, 32, 160, 64};
	rcRight[5] = {160, 32, 192, 64};
	rcRight[6] = {192, 32, 224, 64};
	rcRight[7] = {224, 32, 256, 64};
	rcRight[8] = {0, 96, 32, 128};
	rcRight[9] = {32, 96, 64, 128};
	rcRight[10] = {64, 96, 96, 128};
	rcRight[11] = {96, 96, 128, 128};
	rcRight[12] = {128, 96, 160, 128};
	rcRight[13] = {0, 0, 0, 0};

	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 9;
			npc->act_wait = 0;
			npc->bits &= ~0x2000;
			// Fallthrough
		case 1:
			if (++npc->act_wait > 50)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 8;
			}

			break;

		case 2:
			if (++npc->ani_no > 10)
				npc->ani_no = 9;

			if (++npc->act_wait > 50)
			{
				npc->act_no = 3;
				npc->act_wait = 0;
				npc->ani_no = 0;
			}

			break;

		case 3:
			if (++npc->act_wait > 50)
			{
				npc->act_no = 10;
				npc->bits |= 0x20;
			}

			break;

		case 10:
			npc->bits = npc->bits;
			npc->act_no = 11;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			npc->act_wait = Random(20, 130);
			npc->xm = 0;
			// Fallthrough
		case 11:
			if (gMC.x < npc->x)
				npc->direct = 0;
			else
				npc->direct = 2;

			if (++npc->ani_wait > 4)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 1)
				npc->ani_no = 0;

			if (CountArmsBullet(6) || CountArmsBullet(3) > 3)
				npc->act_no = 20;

			if (npc->act_wait)
			{
				--npc->act_wait;
			}
			else
			{
				if (Random(0, 99) % 2)
					npc->act_no = 20;
				else
					npc->act_no = 50;
			}

			break;

		case 20:
			npc->act_no = 21;
			npc->ani_no = 2;
			npc->act_wait = 0;
			// Fallthrough
		case 21:
			if (++npc->act_wait > 10)
			{
				npc->act_no = 22;
				npc->act_wait = 0;
				npc->ani_no = 3;
				npc->ym = -0x5FF;

				if (npc->direct == 0)
					npc->xm = -0x200u;
				else
					npc->xm = 0x200;
			}

			break;

		case 22:
			if (++npc->act_wait > 10)
			{
				npc->act_no = 23;
				npc->act_wait = 0;
				npc->ani_no = 6;
				SetNpChar(141, 0, 0, 0, 0, 0, npc, 0);
			}

			break;

		case 23:
			if (++npc->act_wait > 30)
			{
				npc->act_no = 24;
				npc->act_wait = 0;
				npc->ani_no = 7;
			}

			if (gMC.x < npc->x)
				npc->direct = 0;
			else
				npc->direct = 2;

			break;

		case 24:
			if (++npc->act_wait > 3)
			{
				npc->act_no = 25;
				npc->ani_no = 3;
			}

			break;

		case 25:
			if (npc->flag & 8)
			{
				npc->act_no = 26;
				npc->act_wait = 0;
				npc->ani_no = 2;
				PlaySoundObject(26, 1);
				SetQuake(20);
			}

			break;

		case 26:
			npc->xm = 8 * npc->xm / 9;

			if (++npc->act_wait > 20)
			{
				npc->act_no = 10;
				npc->ani_no = 0;
			}

			break;

		case 50:
			npc->act_no = 51;
			npc->act_wait = 0;
			npc->ani_no = 4;
			SetNpChar(141, 0, 0, 0, 0, 0, npc, 0);
			// Fallthrough
		case 51:
			if (++npc->act_wait > 30)
			{
				npc->act_no = 52;
				npc->act_wait = 0;
				npc->ani_no = 5;
			}

			if (gMC.x < npc->x)
				npc->direct = 0;
			else
				npc->direct = 2;

			break;

		case 52:
			if (++npc->act_wait > 3)
			{
				npc->act_no = 10;
				npc->ani_no = 0;
			}

			break;

		case 100:
			npc->ani_no = 3;
			npc->act_no = 101;
			npc->bits &= ~0x20;
			npc->damage = 0;

			for (int i = 0; i < 8; ++i)
				SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600u, 0), 0, 0, 0x100);

			break;

		case 101:
			if (npc->flag & 8)
			{
				npc->act_no = 102;
				npc->act_wait = 0;
				npc->ani_no = 2;
				PlaySoundObject(26, 1);
				SetQuake(20);
			}

			break;

		case 102:
			npc->xm = 8 * npc->xm / 9;

			if (++npc->act_wait > 50)
			{
				npc->act_no = 103;
				npc->act_wait = 0;
				npc->ani_no = 10;
			}

			break;

		case 103:
			if (++npc->act_wait > 50)
			{
				npc->ani_no = 9;
				npc->act_no = 104;
				npc->act_wait = 0;
			}

			break;

		case 104:
			if (++npc->ani_no > 10)
				npc->ani_no = 9;

			if (++npc->act_wait > 100)
			{
				npc->act_wait = 0;
				npc->ani_no = 9;
				npc->act_no = 105;
			}

			break;

		case 105:
			if (++npc->act_wait > 50)
			{
				npc->ani_wait = 0;
				npc->act_no = 106;
				npc->ani_no = 11;
			}

			break;

		case 106:
			if (++npc->ani_wait > 50)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 12)
				npc->ani_no = 12;

			break;

		case 140:
			npc->act_no = 141;
			npc->act_wait = 0;
			npc->ani_no = 12;
			PlaySoundObject(29, 1);
			// Fallthrough
		case 141:
			if (++npc->ani_no > 13)
				npc->ani_no = 12;

			if (++npc->act_wait > 100)
			{
				for (int i = 0; i < 4; ++i)
					SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, 0, 0x100);

				npc->cond = 0;
			}

			break;
	}

	if (npc->act_no > 100 && npc->act_no < 105 && npc->act_wait % 9 == 0)
		SetNpChar(4, npc->x + (Random(-12, 12) * 0x200), npc->y + (Random(-12, 12) * 0x200), Random(-341, 341), Random(-0x600, 0), 0, 0, 0x100);

	npc->ym += 0x20;

	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	if (npc->ym < -0x5FF)
		npc->ym = -0x5FF;

	npc->x += npc->xm;
	npc->y += npc->ym;

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];
}

// Toroko block projectile
void ActNpc141(NPCHAR *npc)
{
	RECT rect[2]; // [sp+8h] [bp-24h]@1

	rect[0] = {288, 32, 304, 48};
	rect[1] = {304, 32, 320, 48};

	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->act_wait = 0;
			// Fallthrough
		case 1:
			if (npc->pNpc->direct == 0)
				npc->x = npc->pNpc->x + 0x1400;
			else
				npc->x = npc->pNpc->x - 0x1400;

			npc->y = npc->pNpc->y - 0x1000;

			if (npc->pNpc->act_no == 24 || npc->pNpc->act_no == 52)
			{
				npc->act_no = 10;

				if (npc->pNpc->direct == 0)
					npc->x = npc->pNpc->x - 0x2000;
				else
					npc->x = npc->pNpc->x + 0x2000;

				npc->y = npc->pNpc->y;

				const unsigned char deg = GetArktan(npc->x - gMC.x, npc->y - gMC.y);
				npc->ym = 4 * GetSin(deg);
				npc->xm = 4 * GetCos(deg);

				PlaySoundObject(39, 1);
			}

			break;

		case 10:
			if (npc->flag & 0xF)
			{
				npc->act_no = 20;
				npc->act_wait = 0;
				SetCaret(npc->x, npc->y, 2, 0);
				PlaySoundObject(12, 1);

				for (int i = 0; i < 4; ++i)
					SetNpChar(4, npc->x, npc->y, Random(-0x200, 0x200), Random(-0x200, 0x200), 0, 0, 0x100);
			}
			else
			{
				npc->x += npc->xm;
				npc->y += npc->ym;
			}

			break;

		case 20:
			npc->x += npc->xm;
			npc->y += npc->ym;

			if (++npc->act_wait > 4)
			{
				for (int i = 0; i < 4; ++i)
					SetNpChar(4, npc->x, npc->y, Random(-0x200, 0x200), Random(-0x200, 0x200), 0, 0, 0x100);

				npc->code_char = 142;
				npc->ani_no = 0;
				npc->act_no = 20;
				npc->xm = 0;
				npc->bits &= ~4;
				npc->bits |= 0x20;
				npc->damage = 1;
			}

			break;
	}

	if (++npc->ani_no > 1)
		npc->ani_no = 0;

	npc->rect = rect[npc->ani_no];
}

// Flower Cub
void ActNpc142(NPCHAR *npc)
{
	RECT rect[5];

	rect[0] = {0, 128, 16, 144};
	rect[1] = {16, 128, 32, 144};
	rect[2] = {32, 128, 48, 144};
	rect[3] = {48, 128, 64, 144};
	rect[4] = {64, 128, 80, 144};

	switch (npc->act_no)
	{
		case 10:
			npc->act_no = 11;
			npc->ani_no = 0;
			npc->act_wait = 0;
			// Fallthrough
		case 11:
			if (++npc->act_wait > 30)
			{
				npc->act_no = 12;
				npc->ani_no = 1;
				npc->ani_wait = 0;
			}

			break;

		case 12:
			if (++npc->ani_wait > 8)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no == 3)
			{
				npc->act_no = 20;
				npc->ym = -0x200;

				if (gMC.x < npc->x)
					npc->xm = -0x200;
				else
					npc->xm = 0x200;
			}

			break;

		case 20:
			if (npc->ym > -0x80)
				npc->ani_no = 4;
			else
				npc->ani_no = 3;

			if (npc->flag & 8)
			{
				npc->ani_no = 2;
				npc->act_no = 21;
				npc->act_wait = 0;
				npc->xm = 0;
				PlaySoundObject(23, 1);
			}

			break;

		case 21:
			if (++npc->act_wait > 10)
			{
				npc->act_no = 10;
				npc->ani_no = 0;
			}

			break;
	}

	npc->ym += 0x40;

	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;
	if (npc->ym < -0x5FF)
		npc->ym = -0x5FF;

	npc->x += npc->xm;
	npc->y += npc->ym;

	npc->rect = rect[npc->ani_no];
}

// Jenka (collapsed)
void ActNpc143(NPCHAR *npc)
{
	RECT rcLeft[1];
	RECT rcRight[1];

	rcLeft[0] = {208, 32, 224, 48};

	rcRight[0] = {208, 48, 224, 64};

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];
}

//Toroko (teleporting in)
void ActNpc144(NPCHAR *npc)
{
	RECT rcLeft[5];
	RECT rcRight[5];

	rcLeft[0] = {0, 64, 16, 80};
	rcLeft[1] = {16, 64, 32, 80};
	rcLeft[2] = {32, 64, 48, 80};
	rcLeft[3] = {16, 64, 32, 80};
	rcLeft[4] = {128, 64, 144, 80};

	rcRight[0] = {0, 80, 16, 96};
	rcRight[1] = {16, 80, 32, 96};
	rcRight[2] = {32, 80, 48, 96};
	rcRight[3] = {16, 80, 32, 96};
	rcRight[4] = {128, 80, 144, 96};

	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			npc->tgt_x = npc->x;
			PlaySoundObject(29, 1);
			// Fallthrough
		case 1:
			if (++npc->act_wait == 64)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
			}

			break;

		case 2:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 3)
				npc->ani_no = 2;

			if (npc->flag & 8)
			{
				npc->act_no = 4;
				npc->act_wait = 0;
				npc->ani_no = 4;
				PlaySoundObject(23, 1);
			}

			break;

		case 10:
			npc->act_no = 11;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			// Fallthrough
		case 11:
			if (Random(0, 120) == 10)
			{
				npc->act_no = 12;
				npc->act_wait = 0;
				npc->ani_no = 1;
			}

			break;

		case 12:
			if (++npc->act_wait > 8)
			{
				npc->act_no = 11;
				npc->ani_no = 0;
			}

			break;
	}

	if (npc->act_no > 1)
	{
		npc->ym += 0x20;
		if (npc->ym > 0x5FF)
			npc->ym = 0x5FF;

		npc->y += npc->ym;
	}

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];

	if (npc->act_no == 1)
	{
		npc->rect.bottom = npc->rect.top + npc->act_wait / 4;

		if (npc->act_wait / 2 % 2)
			npc->x = npc->tgt_x;
		else
			npc->x = npc->tgt_x + 0x200;
	}
}

//King's sword
void ActNpc145(NPCHAR *npc)
{
	RECT rcLeft[1];
	RECT rcRight[1];

	rcLeft[0] = {96, 32, 112, 48};
	rcRight[0] = {112, 32, 128, 48};

	if (npc->act_no == 0)
	{
		if (npc->pNpc->count2 == 0)
		{
			if (npc->pNpc->direct == 0)
				npc->direct = 0;
			else
				npc->direct = 2;
		}
		else
		{
			if (npc->pNpc->direct == 0)
				npc->direct = 2;
			else
				npc->direct = 0;
		}

		if (npc->direct == 0)
			npc->x = npc->pNpc->x - 0x1400;
		else
			npc->x = npc->pNpc->x + 0x1400;

		npc->y = npc->pNpc->y;
	}

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];
}

//Lightning
void ActNpc146(NPCHAR *npc)
{
	RECT rect[5];

	rect[0] = {0, 0, 0, 0};
	rect[1] = {256, 0, 272, 240};
	rect[2] = {272, 0, 288, 240};
	rect[3] = {288, 0, 304, 240};
	rect[4] = {304, 0, 320, 240};

	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;

			if (npc->direct == 2)
				SetFlash(0, 0, 2);
			// Fallthrough
		case 1:
			if (++npc->act_wait > 10)
			{
				npc->act_no = 2;
				PlaySoundObject(101, 1);
			}

			break;

		case 2:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no == 2)
				npc->damage = 10;

			if (npc->ani_no > 4)
			{
				SetDestroyNpChar(npc->x, npc->y, 0x1000, 8);
				npc->cond = 0;
			}

			break;
	}

	npc->rect = rect[npc->ani_no];
}

//Quote
void ActNpc150(NPCHAR *npc)
{
	RECT rcLeft[9];
	RECT rcRight[9];
	
	rcLeft[0] = {0, 0, 16, 16};
	rcLeft[1] = {48, 0, 64, 16};
	rcLeft[2] = {144, 0, 160, 16};
	rcLeft[3] = {16, 0, 32, 16};
	rcLeft[4] = {0, 0, 16, 16};
	rcLeft[5] = {32, 0, 48, 16};
	rcLeft[6] = {0, 0, 16, 16};
	rcLeft[7] = {160, 0, 176, 16};
	rcLeft[8] = {112, 0, 128, 16};
	
	rcRight[0] = {0, 16, 16, 32};
	rcRight[1] = {48, 16, 64, 32};
	rcRight[2] = {144, 16, 160, 32};
	rcRight[3] = {16, 16, 32, 32};
	rcRight[4] = {0, 16, 16, 32};
	rcRight[5] = {32, 16, 48, 32};
	rcRight[6] = {0, 16, 16, 32};
	rcRight[7] = {160, 16, 176, 32};
	rcRight[8] = {112, 16, 128, 32};
	
	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			
			if (npc->direct > 10)
			{
				npc->x = gMC.x;
				npc->y = gMC.y;
				npc->direct -= 10;
			}
			break;
		case 2:
			npc->ani_no = 1;
			break;
		case 10:
			npc->act_no = 11;
			for (int i = 0; i < 4; i++)
				SetNpChar(4, npc->x, npc->y, Random(-0x155, 0x155), Random(-0x600, 0), 0, 0, 0x100);
			PlaySoundObject(71, 1);
		case 11:
			npc->ani_no = 2;
			break;
		case 20:
			npc->act_no = 21;
			npc->act_wait = 64;
			PlaySoundObject(29, 1);
		case 21:
			if (!--npc->act_wait)
				npc->cond = 0;
			break;
		case 50:
			npc->act_no = 51;
			npc->ani_no = 3;
			npc->ani_wait = 0;
		case 51:
			if (++npc->ani_wait > 4)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}
			if (npc->ani_no > 6)
				npc->ani_no = 3;
			
			if ( npc->direct )
				npc->x += 0x200;
			else
				npc->x -= 0x200;
			break;
		case 60:
			npc->act_no = 61;
			npc->ani_no = 7;
			npc->tgt_x = npc->x;
			npc->tgt_y = npc->y;
		case 61:
			npc->tgt_y += 0x100;
			npc->x = npc->tgt_x + (Random(-1, 1) << 9);
			npc->y = npc->tgt_y + (Random(-1, 1) << 9);
			break;
		case 70:
			npc->act_no = 71;
			npc->act_wait = 0;
			npc->ani_no = 3;
			npc->ani_wait = 0;
		case 0x47:
			if ( npc->direct )
				npc->x -= 0x100;
			else
				npc->x += 0x100;
			
			if (++npc->ani_wait > 8)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}
			if (npc->ani_no > 6)
				npc->ani_no = 3;
			break;
		case 80:
			npc->ani_no = 8;
			break;
		case 99:
		case 100:
			npc->act_no = 101;
			npc->ani_no = 3;
			npc->ani_wait = 0;
		case 101:
			npc->ym += 0x40;
			if (npc->ym > 0x5FF)
				npc->ym = 0x5FF;
			if (npc->flag & 8)
			{
				npc->ym = 0;
				npc->act_no = 102;
			}
			npc->y += npc->ym;
			break;
		case 102:
			if (++npc->ani_wait > 8)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}
			if (npc->ani_no > 6)
				npc->ani_no = 3;
			break;
		default:
			break;
	}
	
	if (npc->direct)
		npc->rect = rcRight[npc->ani_no];
	else
		npc->rect = rcLeft[npc->ani_no];
	
	if (npc->act_no == 21)
	{
		npc->rect.bottom = npc->act_wait / 4 + npc->rect.top;
		if (npc->act_wait / 2 & 1)
			++npc->rect.left;
	}
	
	if (gMC.equip & 0x40)
	{
		npc->rect.top += 32;
		npc->rect.bottom += 32;
	}
}

//Blue robot (standing)
void ActNpc151(NPCHAR *npc)
{
	RECT rcLeft[2];
	RECT rcRight[2];

	rcLeft[0] = {192, 0, 208, 16};
	rcLeft[1] = {208, 0, 224, 16};

	rcRight[0] = {192, 16, 208, 32};
	rcRight[1] = {208, 16, 224, 32};

	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			// Fallthrough

		case 1:
			if (Random(0, 100) == 0)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 1;
			}

			break;

		case 2:
			if (++npc->act_wait > 16)
			{
				npc->act_no = 1;
				npc->ani_no = 0;
			}

			break;
	}

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];
}
