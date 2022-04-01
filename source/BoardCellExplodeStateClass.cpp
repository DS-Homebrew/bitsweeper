#include "BoardCellExplodeStateClass.h"
#include "CommonDataClass.h"
#include "RandomNumberGeneratorClass.h"
#include "StateMachineClass.h"
#include "BoardDisappearStateClass.h"
#include "BoardCellClass.h"
#include "GameLostAppearStateClass.h"
#include "OperationsClass.h"
#include <math.h>

BoardCellExplodeStateClass::BoardCellExplodeStateClass()
: StateClass()
{
}

void BoardCellExplodeStateClass::Start(CommonDataClass* CommonData)
{
	double Radius;

	Count = 0;
	Radius = CommonData->RandomNumberGenerator->Next() * 2 * M_PI;
	XDisplacement = floattov16(cos(Radius) * 0.01);
	ZDisplacement = floattov16(sin(Radius) * 0.01);
}

void BoardCellExplodeStateClass::Run(CommonDataClass* CommonData)
{
	double Radius;

	Count++;
	Radius = CommonData->RandomNumberGenerator->Next() * 2 * M_PI;
	XDisplacement = floattov16(cos(Radius) * 0.01 * ((30.0 - Count) / 30.0));
	ZDisplacement = floattov16(sin(Radius) * 0.01 * ((30.0 - Count) / 30.0));
	if(Count >= 30)
	{
		CommonData->HorizontalScrollCount = 0;
		CommonData->VerticalScrollCount = 0;
		CommonData->StateMachine->Switch(GAME_LOST_APPEAR_STATE);
	};
}

void BoardCellExplodeStateClass::Draw(CommonDataClass* CommonData)
{
	int i;
	int j;
	int k;
	int x;
	int z;
	int c;
	int t;
	int Top;
	int Bottom;

	Operations::DrawSmallUpperLeftLogo(CommonData);
	if(CommonData->ToBottomScreen)
	{
		Top = CommonData->LowerTopCell;
		Bottom = CommonData->LowerBottomCell;
	} else
	{
		Top = CommonData->UpperTopCell;
		Bottom = CommonData->UpperBottomCell;
	};
	glBindTexture(0, 0);
	glColor3f(210.0 / 255.0, 180.0 / 255.0, 140.0 / 255.0);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for(j = Top; j < Bottom; j++)
	{
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for(i = CommonData->LeftCell; i < CommonData->RightCell; i++)
		{
			if(Operations::IsEmptyCell(CommonData, k))
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
			};
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	glColor3f(1, 1, 1);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for(j = Top; j < Bottom; j++)
	{
		x = CommonData->LeftCell * 3;
		for(i = CommonData->LeftCell; i < CommonData->RightCell; i++)
		{
			t = -1;
			if(CommonData->Board[k].State == CellUncovered)
			{
				if(CommonData->Board[k].Explodes)
				{
					t = BOMB_IMG;
				} else 
				{
					c = CommonData->Board[k].ExplodingCellsAround;
					if(c > 0)
					{
						t = ONE_IMG + c - 1; 
					};
				};
			} else if(CommonData->Board[k].State == CellFlagged)
			{
				t = FLAG_IMG;
			} else if(CommonData->Board[k].State == CellUnknown)
			{
				t = QUESTION_IMG;
			};
			if(t >= 0)
			{
				glBindTexture(0, CommonData->Textures[t]);
				glBegin(GL_QUADS);
				glTexCoord2t16(inttot16(0), inttot16(0));
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
				glTexCoord2t16(inttot16(0), inttot16(16));
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glTexCoord2t16(inttot16(16), inttot16(16));
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glTexCoord2t16(inttot16(16), inttot16(0));
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
				glEnd();
			};
			k++;
			x = x + 3;
		};
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	glBindTexture(0, 0);
	glColor3f(255.0 / 255.0, 225.0 / 255.0, 175.0 / 255.0);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for(j = Top; j < Bottom; j++)
	{
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for(i = CommonData->LeftCell; i < CommonData->RightCell; i++)
		{
			if(CommonData->Board[k].State == CellUncovered)
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 3] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 3] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
			} else
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z] + ZDisplacement);
			}
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	glColor3f(240.0 / 255.0, 205.0 / 255.0, 160.0 / 255.0);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for(j = Top; j < Bottom; j++)
	{
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for(i = CommonData->LeftCell; i < CommonData->RightCell; i++)
		{
			if(CommonData->Board[k].State == CellUncovered)
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 3] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z] + ZDisplacement);
			} else
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 3] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
			};
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	glColor3f(168.0 / 255.0, 144.0 / 255.0, 112.0 / 255.0);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for(j = Top; j < Bottom; j++)
	{
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for(i = CommonData->LeftCell; i < CommonData->RightCell; i++)
		{
			if(CommonData->Board[k].State == CellUncovered)
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z] + ZDisplacement);
			} else
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 3] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 3] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
			};
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	glColor3f(184.0 / 255.0, 156.0 / 255.0, 122.0 / 255.0);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for(j = Top; j < Bottom; j++)
	{
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for(i = CommonData->LeftCell; i < CommonData->RightCell; i++)
		{
			if(CommonData->Board[k].State == CellUncovered)
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 3] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
			} else
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 1] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 2] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z + 3] + ZDisplacement);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3] + XDisplacement, 0, CommonData->BoardCellZCoordinates[z] + ZDisplacement);
			};
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	Operations::DrawSmallUpperRightClock(CommonData);
}
