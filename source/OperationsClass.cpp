#include "OperationsClass.h"
#include "CommonDataClass.h"
#include <nds/arm9/videoGL.h>
#include "BoardCellClass.h"
#include <nds/arm9/input.h>
#include <math.h>

void OperationsClass::DoBoardScrolling(CommonDataClass* CommonData)
{
	if((((CommonData->IsLeftHanded)&&((CommonData->KeysHeld & KEY_Y) != 0))||((!(CommonData->IsLeftHanded))&&((CommonData->KeysHeld & KEY_LEFT) != 0)))&&(CommonData->HorizontalScrollCount > -10))
	{
		CommonData->HorizontalScrollCount = CommonData->HorizontalScrollCount - 2;
	};
	if((((CommonData->IsLeftHanded)&&((CommonData->KeysHeld & KEY_A) != 0))||((!(CommonData->IsLeftHanded))&&((CommonData->KeysHeld & KEY_RIGHT) != 0)))&&(CommonData->HorizontalScrollCount < 10))
	{
		CommonData->HorizontalScrollCount = CommonData->HorizontalScrollCount + 2;
	};
	if(CommonData->HorizontalScrollCount > 0)
	{
		CommonData->HorizontalScrollCount--;
	} else if(CommonData->HorizontalScrollCount < 0)
	{
		CommonData->HorizontalScrollCount++;
	};
	if((((CommonData->IsLeftHanded)&&((CommonData->KeysHeld & KEY_B) != 0))||((!(CommonData->IsLeftHanded))&&((CommonData->KeysHeld & KEY_DOWN) != 0)))&&(CommonData->VerticalScrollCount > -10))
	{
		CommonData->VerticalScrollCount = CommonData->VerticalScrollCount - 2;
	};
	if((((CommonData->IsLeftHanded)&&((CommonData->KeysHeld & KEY_X) != 0))||((!(CommonData->IsLeftHanded))&&((CommonData->KeysHeld & KEY_UP) != 0)))&&(CommonData->VerticalScrollCount < 10))
	{
		CommonData->VerticalScrollCount = CommonData->VerticalScrollCount + 2;
	};
	if(CommonData->VerticalScrollCount > 0)
	{
		CommonData->VerticalScrollCount--;
	} else if(CommonData->VerticalScrollCount < 0)
	{
		CommonData->VerticalScrollCount++;
	};
	UpdateBoardLocation(CommonData);
}

void OperationsClass::UpdateBoardLocation(CommonDataClass* CommonData)
{
	CommonData->LocationX = CommonData->LocationX + 0.01 * sin((M_PI * CommonData->HorizontalScrollCount) / (2.0 * 10.0));
	if(CommonData->LocationX > (0.08 + CommonData->BoardWidth * 0.015 / 2.0))
	{
		CommonData->LocationX = 0.08 + CommonData->BoardWidth * 0.015 / 2.0;
		CommonData->HorizontalScrollCount = 0;
	};
	if(CommonData->LocationX < (-0.08 - CommonData->BoardWidth * 0.015 / 2.0))
	{
		CommonData->LocationX = -0.08 - CommonData->BoardWidth * 0.015 / 2.0;
		CommonData->HorizontalScrollCount = 0;
	};
	CommonData->LocationZ = CommonData->LocationZ + 0.01 * sin((M_PI * CommonData->VerticalScrollCount) / (2.0 * 10.0));
	if(CommonData->LocationZ > (0.05 + CommonData->BoardHeight * 0.015 / 2.0))
	{
		CommonData->LocationZ = 0.05 + CommonData->BoardHeight * 0.015 / 2.0;
		CommonData->VerticalScrollCount = 0;
	};
	if(CommonData->LocationZ < (-0.25 - CommonData->BoardHeight * 0.015 / 2.0))
	{
		CommonData->LocationZ = -0.25 - CommonData->BoardHeight * 0.015 / 2.0;
		CommonData->VerticalScrollCount = 0;
	};
}

void OperationsClass::UpdateBoardCellBorders(CommonDataClass* CommonData)
{
	CommonData->UpperTopCell = ((int)(((0 - 96.0) / 19.2) + (CommonData->BoardHeight / 2.0) - ((CommonData->LocationZ + 0.2) / 0.015))) - 1;
	if(CommonData->UpperTopCell < 0)
	{
		CommonData->UpperTopCell = 0;
	} else if(CommonData->UpperTopCell > CommonData->BoardHeight)
	{
		CommonData->UpperTopCell = CommonData->BoardHeight;
	};
	CommonData->UpperBottomCell = ((int)(((192 - 96.0) / 19.2) + (CommonData->BoardHeight / 2.0) - ((CommonData->LocationZ + 0.2) / 0.015))) + 1;
	if(CommonData->UpperBottomCell < 0)
	{
		CommonData->UpperBottomCell = 0;
	} else if(CommonData->UpperBottomCell > CommonData->BoardHeight)
	{
		CommonData->UpperBottomCell = CommonData->BoardHeight;
	};
	CommonData->LeftCell = ((int)(((0 - 128.0) / 19.2) + (CommonData->BoardWidth / 2.0) + (CommonData->LocationX / 0.015))) - 1;
	if(CommonData->LeftCell < 0)
	{
		CommonData->LeftCell = 0;
	} else if(CommonData->LeftCell > CommonData->BoardWidth)
	{
		CommonData->LeftCell = CommonData->BoardWidth;
	};
	CommonData->RightCell = ((int)(((256 - 128.0) / 19.2) + (CommonData->BoardWidth / 2.0) + (CommonData->LocationX / 0.015))) + 1;
	if(CommonData->RightCell < 0)
	{
		CommonData->RightCell = 0;
	} else if(CommonData->RightCell > CommonData->BoardWidth)
	{
		CommonData->RightCell = CommonData->BoardWidth;
	};
	CommonData->LowerTopCell = ((int)(((0 - 96.0) / 19.2) + (CommonData->BoardHeight / 2.0) - (CommonData->LocationZ / 0.015))) - 1;
	if(CommonData->LowerTopCell < 0)
	{
		CommonData->LowerTopCell = 0;
	} else if(CommonData->LowerTopCell > CommonData->BoardHeight)
	{
		CommonData->LowerTopCell = CommonData->BoardHeight;
	};
	CommonData->LowerBottomCell = ((int)(((192 - 96.0) / 19.2) + (CommonData->BoardHeight / 2.0) - (CommonData->LocationZ / 0.015))) + 1;
	if(CommonData->LowerBottomCell < 0)
	{
		CommonData->LowerBottomCell = 0;
	} else if(CommonData->LowerBottomCell > CommonData->BoardHeight)
	{
		CommonData->LowerBottomCell = CommonData->BoardHeight;
	};
}

void OperationsClass::DrawSmallUpperLeftLogo(CommonDataClass* CommonData)
{
	glBindTexture(0, CommonData->Textures[LOGO_SMALL_IMG]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(10), inttot16(5));
	glVertex3f(-0.09 + CommonData->LocationX, 0.001, 0.16 + CommonData->LocationZ);
	glTexCoord2t16(inttot16(10), inttot16(27));
	glVertex3f(-0.09 + CommonData->LocationX, 0.001, 0.1425 + CommonData->LocationZ);
	glTexCoord2t16(inttot16(54), inttot16(27));
	glVertex3f(-0.055 + CommonData->LocationX, 0.001, 0.1425 + CommonData->LocationZ);
	glTexCoord2t16(inttot16(54), inttot16(5));
	glVertex3f(-0.055 + CommonData->LocationX, 0.001, 0.16 + CommonData->LocationZ);
	glEnd();
}

void OperationsClass::DrawLargeCenteredLogo(CommonDataClass* CommonData)
{
	glBindTexture(0, CommonData->Textures[LOGO_IMG]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(32), inttot16(16));
	glVertex3f(-0.075, 0.001, 0.1375);
	glTexCoord2t16(inttot16(32), inttot16(112));
	glVertex3f(-0.075, 0.001, 0.0625);
	glTexCoord2t16(inttot16(225), inttot16(112));
	glVertex3f(0.075, 0.001, 0.0625);
	glTexCoord2t16(inttot16(225), inttot16(16));
	glVertex3f(0.075, 0.001, 0.1375);
	glEnd();
}

void OperationsClass::DrawOneCell(CommonDataClass* CommonData, int t, int x, int z)
{
	glBindTexture(0, CommonData->Textures[t]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(0), inttot16(0));
	glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
	glTexCoord2t16(inttot16(0), inttot16(16));
	glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
	glTexCoord2t16(inttot16(16), inttot16(16));
	glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
	glTexCoord2t16(inttot16(16), inttot16(0));
	glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
	glEnd();
}

void OperationsClass::DrawEmptyCells(CommonDataClass* CommonData, int Top, int Bottom)
{
	int k;
	int z;
	int j;
	int x;
	int i;

	glColor3f(210.0 / 255.0, 180.0 / 255.0, 140.0 / 255.0);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for(j = Top; j < Bottom; j++)
	{
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for(i = CommonData->LeftCell; i < CommonData->RightCell; i++)
		{
			if(IsEmptyCell(CommonData, k))
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
			};
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
}

void OperationsClass::DrawNonEmptyCells(CommonDataClass* CommonData, int Top, int Bottom)
{
	int k;
	int z;
	int j;
	int x;
	int i;
	int t;
	int c;

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
				Operations::DrawOneCell(CommonData, t, x, z);
			};
			k++;
			x = x + 3;
		};
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
}

void OperationsClass::DrawCellBorders(CommonDataClass* CommonData, int Top, int Bottom)
{
	int k;
	int z;
	int j;
	int x;
	int i;

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
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
			} else
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
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
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
			} else
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
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
				glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
			} else
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
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
				glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
			} else
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
			};
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
}

void OperationsClass::DrawSmallUpperRightClock(CommonDataClass* CommonData, float TimeHeight)
{
	glBindTexture(0, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0.051 + CommonData->LocationX, 0.0003, 0.1405 + CommonData->LocationZ + TimeHeight);
	glVertex3f(0.092 + CommonData->LocationX, 0.0003, 0.1405 + CommonData->LocationZ + TimeHeight);
	glVertex3f(0.092 + CommonData->LocationX, 0.0003, 0.162 + CommonData->LocationZ + TimeHeight);
	glVertex3f(0.051 + CommonData->LocationX, 0.0003, 0.162 + CommonData->LocationZ + TimeHeight);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(0.052 + CommonData->LocationX, 0.0006, 0.1415 + CommonData->LocationZ + TimeHeight);
	glVertex3f(0.091 + CommonData->LocationX, 0.0006, 0.1415 + CommonData->LocationZ + TimeHeight);
	glVertex3f(0.091 + CommonData->LocationX, 0.0006, 0.161 + CommonData->LocationZ + TimeHeight);
	glVertex3f(0.052 + CommonData->LocationX, 0.0006, 0.161 + CommonData->LocationZ + TimeHeight);
	glEnd();
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(0.053 + CommonData->LocationX, 0.001, 0.1425 + CommonData->LocationZ + TimeHeight);
	glVertex3f(0.09 + CommonData->LocationX, 0.001, 0.1425 + CommonData->LocationZ + TimeHeight);
	glVertex3f(0.09 + CommonData->LocationX, 0.001, 0.16 + CommonData->LocationZ + TimeHeight);
	glVertex3f(0.053 + CommonData->LocationX, 0.001, 0.16 + CommonData->LocationZ + TimeHeight);
	glEnd();
	glColor3f(1, 1, 1);
	glBindTexture(0, CommonData->Textures[TIME_0_IMG + CommonData->Second1]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(0), inttot16(0));
	glVertex3f(0.083 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(0), inttot16(9));
	glVertex3f(0.083 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(9));
	glVertex3f(0.089 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(0));
	glVertex3f(0.089 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glEnd();
	glBindTexture(0, CommonData->Textures[TIME_0_IMG + CommonData->Second10]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(0), inttot16(0));
	glVertex3f(0.077 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(0), inttot16(9));
	glVertex3f(0.077 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(9));
	glVertex3f(0.083 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(0));
	glVertex3f(0.083 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glEnd();
	glBindTexture(0, CommonData->Textures[TIME_COLON_IMG]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(0), inttot16(0));
	glVertex3f(0.071 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(0), inttot16(9));
	glVertex3f(0.071 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(9));
	glVertex3f(0.077 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(0));
	glVertex3f(0.077 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glEnd();
	glBindTexture(0, CommonData->Textures[TIME_0_IMG + CommonData->Minute1]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(0), inttot16(0));
	glVertex3f(0.065 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(0), inttot16(9));
	glVertex3f(0.065 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(9));
	glVertex3f(0.071 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(0));
	glVertex3f(0.071 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glEnd();
	glBindTexture(0, CommonData->Textures[TIME_0_IMG + CommonData->Minute10]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(0), inttot16(0));
	glVertex3f(0.059 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(0), inttot16(9));
	glVertex3f(0.059 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(9));
	glVertex3f(0.065 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(0));
	glVertex3f(0.065 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glEnd();
	glBindTexture(0, CommonData->Textures[TIME_0_IMG + CommonData->Minute100]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(0), inttot16(0));
	glVertex3f(0.053 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(0), inttot16(9));
	glVertex3f(0.053 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(9));
	glVertex3f(0.059 + CommonData->LocationX, 0.0013, 0.148 + CommonData->LocationZ + TimeHeight);
	glTexCoord2t16(inttot16(8), inttot16(0));
	glVertex3f(0.059 + CommonData->LocationX, 0.0013, 0.154 + CommonData->LocationZ + TimeHeight);
	glEnd();
}

bool OperationsClass::IsEmptyCell(CommonDataClass* CommonData, int k)
{
	bool res;

	res = (CommonData->Board[k].State == CellCovered);
	if(!res)
	{
		res = (CommonData->Board[k].State == CellUncovered) 
		   && (!(CommonData->Board[k].Explodes)) 
		   && (CommonData->Board[k].ExplodingCellsAround == 0);
	};
	return res;
}
