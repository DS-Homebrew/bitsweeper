#ifndef COMMONDATACLASS_H
#define COMMONDATACLASS_H

#define LOGO_IMG 0
#define START_BUTTON_IMG 1
#define LEGEND_IMG 2
#define MENU_IMG 3
#define SELECTED_ITEM_IMG 4
#define UNSELECTED_ITEM_IMG 5
#define ONE_IMG 6
#define FLAG_IMG 14
#define QUESTION_IMG 15
#define BOMB_IMG 16
#define YOU_WIN_IMG 17
#define YOU_LOSE_IMG 18
#define TIME_0_IMG 19
#define TIME_COLON_IMG 29
#define BEST_SCORES_PLUS_EXPERT_PLUS_INSANE_IMG 30
#define BEGINNER_PLUS_INTERMEDIATE_IMG 31
#define LOGO_SMALL_IMG 32

#include <nds/ndstypes.h>
#include <nds/arm9/sprite.h>
#include <nds/arm9/videoGL.h>
#include "BoardCellStateEnum.h"

class CommonDataClass
{
public:
	CommonDataClass();

	bool ToBottomScreen;

	uint32 KeysHeld;

	int16 TouchX;

	int16 TouchY;

	bool CellTouched;

	class StateMachineClass* StateMachine;

	uint8 ClearColorR;

	uint8 ClearColorG;

	uint8 ClearColorB;

	m4x4* POV;

	float LocationX;

	float LocationZ;

	float LegendX;

	int* Textures;

	int* Palettes;

	int Level;

	bool LastGameWon;

	class RandomNumberGeneratorClass* RandomNumberGenerator;

	class BoardCellClass* Board;

	int BoardLength;

	int BoardWidth;

	int BoardHeight;

	int HorizontalScrollCount;

	int VerticalScrollCount;

	int* CellsBeingUncoveredList;

	int CellsBeingUncoveredSize;

	int CellBeingChanged;

	BoardCellStateEnum CellBeingChangedNewState;

	v16* BoardCellXCoordinates;

	v16* BoardCellZCoordinates;

	int UpperTopCell;

	int UpperBottomCell;

	int LeftCell;

	int RightCell;

	int LowerTopCell;

	int LowerBottomCell;

	int TickCount;

	bool TimeStarted;

	int InitialTickCount;

	bool LimitTimeReached;

	int Second1;

	int Second10;

	int Minute1;

	int Minute10;

	int Minute100;

	class BestScoresTableClass* BestScoresTable;

	bool FilesystemEnabled;

	bool IsLeftHanded;

	bool Finished;

	virtual ~CommonDataClass();

};

#endif
