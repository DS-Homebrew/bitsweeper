#include "BoardDisappearStateClass.h"
#include "CommonDataClass.h"
#include "StateMachineClass.h"
#include "BoardCellClass.h"
#include "LogoEnlargeStateClass.h"
#include "OperationsClass.h"

BoardDisappearStateClass::BoardDisappearStateClass()
: StateClass()
{
}

void BoardDisappearStateClass::Start(CommonDataClass* CommonData)
{
	int i;

	Disappearing.SetLength(16);
	Disappearing.Start[0] = 210.0 / 255.0;
	Disappearing.Start[1] = 180.0 / 255.0;
	Disappearing.Start[2] = 140.0 / 255.0;
	Disappearing.Start[3] = 255.0 / 255.0;
	Disappearing.Start[4] = 225.0 / 255.0;
	Disappearing.Start[5] = 175.0 / 255.0;
	Disappearing.Start[6] = 240.0 / 255.0;
	Disappearing.Start[7] = 205.0 / 255.0;
	Disappearing.Start[8] = 160.0 / 255.0;
	Disappearing.Start[9] = 168.0 / 255.0;
	Disappearing.Start[10] = 144.0 / 255.0;
	Disappearing.Start[11] = 112.0 / 255.0;
	Disappearing.Start[12] = 184.0 / 255.0;
	Disappearing.Start[13] = 156.0 / 255.0;
	Disappearing.Start[14] = 122.0 / 255.0;
	Disappearing.Start[15] = 0;
	for(i = 0; i < 15; i += 3)
	{
		Disappearing.Finish[i] = 34.0 / 255.0;
		Disappearing.Finish[i + 1] = 139.0 / 255.0;
		Disappearing.Finish[i + 2] = 34.0 / 255.0;
	};
	Disappearing.Finish[15] = 0.06;
	Disappearing.SetMax(10);
}

void BoardDisappearStateClass::Run(CommonDataClass* CommonData)
{
	Disappearing.Step();
	if(Disappearing.Finished())
	{
		delete[] CommonData->BoardCellZCoordinates;
		CommonData->BoardCellZCoordinates = 0;
		delete[] CommonData->BoardCellXCoordinates; 
		CommonData->BoardCellXCoordinates = 0;
		delete[] CommonData->CellsBeingUncoveredList;
		CommonData->CellsBeingUncoveredList = 0;
		delete[] CommonData->Board; 
		CommonData->Board = 0;
		CommonData->CellTouched = false;
		CommonData->LocationX = 0;
		CommonData->LocationZ = 0;
		CommonData->StateMachine->Switch(LOGO_ENLARGE_STATE);
	};
}

void BoardDisappearStateClass::Draw(CommonDataClass* CommonData)
{
	int i;
	int j;
	int x;
	int z;
	int k;
	int Top;
	int Bottom;

	Operations::DrawSmallUpperLeftLogo(CommonData);
	if(CommonData->Board != 0)
	{
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
		glColor3f(Disappearing.Value[0], Disappearing.Value[1], Disappearing.Value[2]);
		k = Top * CommonData->BoardWidth + CommonData->LeftCell;
		z = Top * 3;
		for(j = Top; j < Bottom; j++)
		{
			x = CommonData->LeftCell * 3;
			glBegin(GL_QUADS);
			for(i = CommonData->LeftCell; i < CommonData->RightCell; i++)
			{
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
				glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
				k++;
				x = x + 3;
			};
			glEnd();
			k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
			z = z + 3;
		};
		glColor3f(Disappearing.Value[3], Disappearing.Value[4], Disappearing.Value[5]);
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
		glColor3f(Disappearing.Value[6], Disappearing.Value[7], Disappearing.Value[8]);
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
		glColor3f(Disappearing.Value[9], Disappearing.Value[10], Disappearing.Value[11]);
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
		glColor3f(Disappearing.Value[12], Disappearing.Value[13], Disappearing.Value[14]);
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
	};
	Operations::DrawSmallUpperRightClock(CommonData, Disappearing.Value[15]);
}
