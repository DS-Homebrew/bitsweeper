#include "BoardWaitStateClass.h"
#include "CommonDataClass.h"
#include <nds/arm9/input.h>
#include "StateMachineClass.h"
#include "BestScoresTableAppearStateClass.h"
#include "BoardCellClass.h"
#include "BoardCellChangeAppearStateClass.h"
#include "BoardCellChangeDisappearStateClass.h"
#include "BoardCellUncoverStateClass.h"
#include "OperationsClass.h"

BoardWaitStateClass::BoardWaitStateClass()
: StateClass()
{
}

void BoardWaitStateClass::Start(CommonDataClass* CommonData)
{
	int ElapsedTime;
	int ElapsedSeconds;
	int ElapsedMinutes;

	CommonData->HorizontalScrollCount = 0;
	CommonData->VerticalScrollCount = 0;
	if(CommonData->TimeStarted && !CommonData->LimitTimeReached)
	{
		ElapsedTime = ((CommonData->TickCount - CommonData->InitialTickCount) * 10000) / 598261;
		ElapsedSeconds = ElapsedTime % 60;
		CommonData->Second1 = ElapsedSeconds % 10;
		CommonData->Second10 = ElapsedSeconds / 10;
		ElapsedMinutes = ElapsedTime / 60;
		CommonData->Minute1 = ElapsedMinutes % 10;
		ElapsedMinutes = ElapsedMinutes / 10;
		CommonData->Minute10 = ElapsedMinutes % 10;
		CommonData->Minute100 = ElapsedMinutes / 10;
		if((CommonData->Second1 == 9)&&(CommonData->Second10 == 5)&&(CommonData->Minute1 == 9)&&(CommonData->Minute10 == 9)&&(CommonData->Minute100 == 9))
		{
			CommonData->LimitTimeReached = true;
		};
	};
}

void BoardWaitStateClass::Run(CommonDataClass* CommonData)
{
	int x;
	int z;
	int k;
	int ElapsedTime;
	int ElapsedMinutes;
	int ElapsedSeconds;

	if(((CommonData->IsLeftHanded)&&(((CommonData->KeysHeld & KEY_UP) != 0)||((CommonData->KeysHeld & KEY_DOWN) != 0)))||((!(CommonData->IsLeftHanded))&&(((CommonData->KeysHeld & KEY_B) != 0)||((CommonData->KeysHeld & KEY_X) != 0))))
	{
		CommonData->StateMachine->Switch(BEST_SCORES_TABLE_APPEAR_STATE);
	} else
	{
		if((CommonData->TouchX > 0)&&(CommonData->TouchY > 0))
		{
			if(!(CommonData->CellTouched))
			{
				z = ((int)(((CommonData->TouchY - 96.0) / 19.2) + (CommonData->BoardHeight / 2.0) - (CommonData->LocationZ / 0.015)));
				if((z >= 0)&&(z < CommonData->BoardHeight))
				{
					x = ((int)(((CommonData->TouchX - 128.0) / 19.2) + (CommonData->BoardWidth / 2.0) + (CommonData->LocationX / 0.015)));
					if((x >= 0)&&(x < CommonData->BoardWidth))
					{
						k = z * CommonData->BoardWidth + x;
						if(((CommonData->KeysHeld & KEY_L) != 0) || ((CommonData->KeysHeld & KEY_R) != 0))
						{
							if(CommonData->Board[k].State == CellCovered)
							{
								CommonData->CellBeingChanged = k;
								CommonData->CellBeingChangedNewState = CellFlagged;
								CommonData->StateMachine->Switch(BOARD_CELL_CHANGE_APPEAR_STATE);
							} else if(CommonData->Board[k].State == CellFlagged)
							{
								CommonData->CellBeingChanged = k;
								CommonData->CellBeingChangedNewState = CellUnknown;
								CommonData->StateMachine->Switch(BOARD_CELL_CHANGE_DISAPPEAR_STATE);
							} else if(CommonData->Board[k].State == CellUnknown)
							{
								CommonData->CellBeingChanged = k;
								CommonData->CellBeingChangedNewState = CellCovered;
								CommonData->StateMachine->Switch(BOARD_CELL_CHANGE_DISAPPEAR_STATE);
							};
						} else if(CommonData->Board[k].State == CellCovered)
						{
							CommonData->CellsBeingUncoveredList[0] = k;
							CommonData->CellsBeingUncoveredSize = 1;
							CommonData->Board[k].JustMarkedForUncover = true;
							CommonData->StateMachine->Switch(BOARD_CELL_UNCOVER_STATE);
						};
					};
				};
				CommonData->CellTouched = true;
			};
		} else
		{
			CommonData->CellTouched = false;
		};
		Operations::DoBoardScrolling(CommonData);
	};
	Operations::UpdateBoardCellBorders(CommonData);
	if((CommonData->TimeStarted)&&(!(CommonData->LimitTimeReached)))
	{
		ElapsedTime =  ((CommonData->TickCount - CommonData->InitialTickCount) * 10000) / 598261;
		ElapsedSeconds = ElapsedTime % 60;
		CommonData->Second1 = ElapsedSeconds % 10;
		CommonData->Second10 = ElapsedSeconds / 10;
		ElapsedMinutes = ElapsedTime / 60;
		CommonData->Minute1 = ElapsedMinutes % 10;
		ElapsedMinutes = ElapsedMinutes / 10;
		CommonData->Minute10 = ElapsedMinutes % 10;
		CommonData->Minute100 = ElapsedMinutes / 10;
		if((CommonData->Second1 == 9)&&(CommonData->Second10 == 5)&&(CommonData->Minute1 == 9)&&(CommonData->Minute10 == 9)&&(CommonData->Minute100 == 9))
		{
			CommonData->LimitTimeReached = true;
		};
	};
}

void BoardWaitStateClass::Draw(CommonDataClass* CommonData)
{
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
	Operations::DrawEmptyCells(CommonData, Top, Bottom);
	Operations::DrawNonEmptyCells(CommonData, Top, Bottom);
	Operations::DrawCellBorders(CommonData, Top, Bottom);
	if(CommonData->TimeStarted)
	{
		Operations::DrawSmallUpperRightClock(CommonData);
	};
}
