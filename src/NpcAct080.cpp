#include "WindowsWrapper.h"

#include "NpcAct.h"

#include "MyChar.h"
#include "NpChar.h"
#include "Game.h"
#include "Sound.h"
#include "Back.h"
#include "Triangle.h"
#include "Caret.h"

//Igor (cutscene)
void ActNpc083(NPCHAR *npc)
{
	RECT rcLeft[8];
	RECT rcRight[8];

	rcLeft[0] = {0, 0, 40, 40};
	rcLeft[1] = {40, 0, 80, 40};
	rcLeft[2] = {80, 0, 120, 40};
	rcLeft[3] = {0, 0, 40, 40};
	rcLeft[4] = {120, 0, 160, 40};
	rcLeft[5] = {0, 0, 40, 40};
	rcLeft[6] = {160, 0, 200, 40};
	rcLeft[7] = {200, 0, 240, 40};

	rcRight[0] = {0, 40, 40, 80};
	rcRight[1] = {40, 40, 80, 80};
	rcRight[2] = {80, 40, 120, 80};
	rcRight[3] = {0, 40, 40, 80};
	rcRight[4] = {120, 40, 160, 80};
	rcRight[5] = {0, 40, 40, 80};
	rcRight[6] = {160, 40, 200, 80};
	rcRight[7] = {200, 40, 240, 80};

	switch (npc->act_no)
	{
		case 0:
			npc->xm = 0;
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			// Fallthrough
		case 1:
			if (++npc->ani_wait > 5)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 1)
				npc->ani_no = 0;

			break;

		case 2:
			npc->act_no = 3;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			// Fallthrough
		case 3:
			if (++npc->ani_wait > 3)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 5)
				npc->ani_no = 2;

			if (npc->direct == 0)
				npc->xm = -0x200;
			else
				npc->xm = 0x200;

			break;

		case 4:
			npc->xm = 0;
			npc->act_no = 5;
			npc->act_wait = 0;
			npc->ani_no = 6;
			// Fallthrough
		case 5:
			if (++npc->act_wait > 10)
			{
				npc->act_wait = 0;
				npc->act_no = 6;
				npc->ani_no = 7;
				PlaySoundObject(70, 1);
			}

			break;

		case 6:
			if (++npc->act_wait > 8)
			{
				npc->act_no = 0;
				npc->ani_no = 0;
			}

			break;

		case 7:
			npc->act_no = 1;
			break;
	}

	npc->ym += 0x40;
	if ( npc->ym > 0x5FF )
		npc->ym = 0x5FF;

	npc->x += npc->xm;
	npc->y += npc->ym;

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];
}

//Basu projectile (Egg Corridor)
void ActNpc084(NPCHAR *npc)
{
	if (npc->flag & 0xFF)
	{
		SetCaret(npc->x, npc->y, 2, 0);
		npc->cond = 0;
	}

	npc->y += npc->ym;
	npc->x += npc->xm;

	RECT rect_left[4];

	rect_left[0] = {48, 48, 64, 64};
	rect_left[1] = {64, 48, 80, 64};
	rect_left[2] = {48, 64, 64, 80};
	rect_left[3] = {64, 64, 80, 80};

	if (++npc->ani_wait > 2)
	{
		npc->ani_wait = 0;
		++npc->ani_no;
	}

	if (npc->ani_no > 3)
		npc->ani_no = 0;

	npc->rect = rect_left[npc->ani_no];

	if (++npc->count1 > 300)
	{
		SetCaret(npc->x, npc->y, 2, 0);
		npc->cond = 0;
	}
}

// Terminal
void ActNpc085(NPCHAR *npc)
{
	RECT rcLeft[3];
	RECT rcRight[3];

	rcLeft[0] = {256, 96, 272, 120};
	rcLeft[1] = {256, 96, 272, 120};
	rcLeft[2] = {272, 96, 288, 120};

	rcRight[0] = {256, 96, 272, 120};
	rcRight[1] = {288, 96, 304, 120};
	rcRight[2] = {304, 96, 320, 120};

	switch(npc->act_no)
	{
		case 0:
			npc->ani_no = 0;

			if (npc->x - 0x1000 < gMC.x && npc->x + 0x1000 > gMC.x && npc->y - 0x2000 < gMC.y && npc->y + 0x1000 > gMC.y)
			{
				PlaySoundObject(43, 1);
				npc->act_no = 1;
			}

			break;

		case 1:
			if (++npc->ani_no > 2)
				npc->ani_no = 1;

			break;
	}

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];
}

// Missile
void ActNpc086(NPCHAR *npc)
{
	RECT rect1[2];
	RECT rect3[2];
	RECT rcLast[1];

	rect1[0] = {0, 80, 16, 96};
	rect1[1] = {16, 80, 32, 96};

	rect3[0] = {0, 112, 16, 128};
	rect3[1] = {16, 112, 32, 128};

	rcLast[0] = {16, 0, 32, 16};

	if (npc->direct == 0)
	{
		if (++npc->ani_wait > 2)
		{
			npc->ani_wait = 0;
			++npc->ani_no;
		}

		if (npc->ani_no > 1)
			npc->ani_no = 0;
	}

	if (gBack.type == 5 || gBack.type == 6)
	{
		if (npc->act_no == 0)
		{
			npc->act_no = 1;
			npc->ym = Random(-0x20, 0x20);
			npc->xm = Random(0x7F, 0x100);
		}

		npc->xm -= 8;

		if (npc->x < 0xA000)
			npc->cond = 0;

		if (npc->x < -0x600)
			npc->x = -0x600;

		if (npc->flag & 1)
			npc->xm = 0x100;

		if (npc->flag & 2)
			npc->ym = 0x40;

		if (npc->flag & 8)
			npc->ym = -0x40;

		npc->x += npc->xm;
		npc->y += npc->ym;
	}

	switch (npc->exp)
	{
		case 1:
			npc->rect = rect1[npc->ani_no];
			break;

		case 3:
			npc->rect = rect3[npc->ani_no];
			break;
	}

	if (npc->direct == 0)
		++npc->count1;

	if (npc->count1 > 550)
		npc->cond = 0;

	if (npc->count1 > 500 && npc->count1 / 2 % 2)
		npc->rect.right = 0;

	if (npc->count1 > 547)
		npc->rect = rcLast[0];;
}

// Heart
void ActNpc087(NPCHAR *npc)
{
	RECT rect2[5];
	RECT rect6[2];
	RECT rcLast[1];

	rect2[0] = {32, 80, 48, 96};
	rect2[1] = {48, 80, 64, 96};

	rect6[0] = {64, 80, 80, 96};
	rect6[1] = {80, 80, 96, 96};

	rcLast[0] = {16, 0, 32, 16};

	if (npc->direct == 0)
	{
		if (++npc->ani_wait > 2)
		{
			npc->ani_wait = 0;
			++npc->ani_no;
		}

		if (npc->ani_no > 1)
			npc->ani_no = 0;
	}

	if (gBack.type == 5 || gBack.type == 6)
	{
		if (npc->act_no == 0)
		{
			npc->act_no = 1;
			npc->ym = Random(-0x20, 0x20);
			npc->xm = Random(0x7F, 0x100);
		}

		npc->xm -= 8;

		if (npc->x < 0xA000)
			npc->cond = 0;

		if (npc->x < -0x600)
			npc->x = -0x600;

		if (npc->flag & 1)
			npc->xm = 0x100;

		if (npc->flag & 2)
			npc->ym = 0x40;

		if (npc->flag & 8)
			npc->ym = -0x40;

		npc->x += npc->xm;
		npc->y += npc->ym;
	}

	switch (npc->exp)
	{
		case 2:
			npc->rect = rect2[npc->ani_no];
			break;

		case 6:
			npc->rect = rect6[npc->ani_no];
			break;
	}

	if (npc->direct == 0)
		++npc->count1;

	if (npc->count1 > 550)
		npc->cond = 0;

	if (npc->count1 > 500 && npc->count1 / 2 % 2)
		npc->rect.right = 0;

	if (npc->count1 > 547)
		npc->rect = rcLast[0];
}
