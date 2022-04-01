#include "BoardCellUncoverStateClass.h"
#include "CommonDataClass.h"
#include "StateMachineClass.h"
#include "BoardWaitStateClass.h"
#include "BoardCellClass.h"
#include "BoardCellExplodeStateClass.h"
#include "GameWonAppearStateClass.h"
#include "OperationsClass.h"

BoardCellUncoverStateClass::BoardCellUncoverStateClass()
: StateClass()
{
}

void BoardCellUncoverStateClass::Start(CommonDataClass* CommonData)
{
	int j;
	int k;
	int l;

	int i = 0;
	if (CommonData->Board[CommonData->CellsBeingUncoveredList[i]].Explodes) {
		while (i < CommonData->BoardLength) {
			if (i != CommonData->CellsBeingUncoveredList[0] && CommonData->Board[i].Explodes) {
				CommonData->CellsBeingUncoveredList[CommonData->CellsBeingUncoveredSize] = i;
				CommonData->CellsBeingUncoveredSize++;
				CommonData->Board[i].JustMarkedForUncover = true;
			}
			i++;
		}
	} else {
		while (i < CommonData->CellsBeingUncoveredSize) {
			k = CommonData->CellsBeingUncoveredList[i];
			if (CommonData->Board[k].ExplodingCellsAround != 0) {
				i++;
				continue;
			}

			l = CommonData->CellsBeingUncoveredList[i] - CommonData->BoardWidth - 1;
			if (l >= 0 && l < CommonData->BoardLength && CommonData->Board[k].X > 0 && CommonData->Board[k].Z > 0){
				if (!CommonData->Board[l].Explodes && CommonData->Board[l].State == CellCovered) {
					for (j = 0; j < CommonData->CellsBeingUncoveredSize; j++) {
						if (CommonData->CellsBeingUncoveredList[j] == l)
							break;
					}

					if (j >= CommonData->CellsBeingUncoveredSize) {
						CommonData->CellsBeingUncoveredList[CommonData->CellsBeingUncoveredSize] = l;
						CommonData->CellsBeingUncoveredSize++;
						CommonData->Board[l].JustMarkedForUncover = true;
					}
				}
			}

			l++;
			if (l >= 0 && l < CommonData->BoardLength && CommonData->Board[k].Z > 0) {
				if (!CommonData->Board[l].Explodes && CommonData->Board[l].State == CellCovered) {
					for (j = 0; j < CommonData->CellsBeingUncoveredSize; j++) {
						if (CommonData->CellsBeingUncoveredList[j] == l)
							break;
					}

					if(j >= CommonData->CellsBeingUncoveredSize) {
						CommonData->CellsBeingUncoveredList[CommonData->CellsBeingUncoveredSize] = l;
						CommonData->CellsBeingUncoveredSize++;
						CommonData->Board[l].JustMarkedForUncover = true;
					}
				}
			}

			l++;
			if (l >= 0 && l < CommonData->BoardLength && CommonData->Board[k].X < CommonData->BoardWidth - 1 && CommonData->Board[k].Z > 0) {
				if (!CommonData->Board[l].Explodes && CommonData->Board[l].State == CellCovered) {
					for (j = 0; j < CommonData->CellsBeingUncoveredSize; j++) {
						if (CommonData->CellsBeingUncoveredList[j] == l)
							break;
					}

					if (j >= CommonData->CellsBeingUncoveredSize) {
						CommonData->CellsBeingUncoveredList[CommonData->CellsBeingUncoveredSize] = l;
						CommonData->CellsBeingUncoveredSize++;
						CommonData->Board[l].JustMarkedForUncover = true;
					}
				}
			}

			l += CommonData->BoardWidth;
			if (l >= 0 && l < CommonData->BoardLength && CommonData->Board[k].X < CommonData->BoardWidth - 1) {
				if (!CommonData->Board[l].Explodes && CommonData->Board[l].State == CellCovered) {
					for (j = 0; j < CommonData->CellsBeingUncoveredSize; j++) {
						if (CommonData->CellsBeingUncoveredList[j] == l)
							break;
					}

					if (j >= CommonData->CellsBeingUncoveredSize) {
						CommonData->CellsBeingUncoveredList[CommonData->CellsBeingUncoveredSize] = l;
						CommonData->CellsBeingUncoveredSize++;
						CommonData->Board[l].JustMarkedForUncover = true;
					}
				}
			}

			l -= 2;
			if (l >= 0 && l < CommonData->BoardLength && CommonData->Board[k].X > 0) {
				if (!CommonData->Board[l].Explodes && CommonData->Board[l].State == CellCovered) {
					for (j = 0; j < CommonData->CellsBeingUncoveredSize; j++) {
						if (CommonData->CellsBeingUncoveredList[j] == l)
							break;
					}

					if(j >= CommonData->CellsBeingUncoveredSize) {
						CommonData->CellsBeingUncoveredList[CommonData->CellsBeingUncoveredSize] = l;
						CommonData->CellsBeingUncoveredSize++;
						CommonData->Board[l].JustMarkedForUncover = true;
					}
				}
			}

			l = l + CommonData->BoardWidth;
			if (l >= 0 && l < CommonData->BoardLength && CommonData->Board[k].X > 0 && CommonData->Board[k].Z < CommonData->BoardHeight - 1) {
				if (!CommonData->Board[l].Explodes && CommonData->Board[l].State == CellCovered) {
					for (j = 0; j < CommonData->CellsBeingUncoveredSize; j++) {
						if (CommonData->CellsBeingUncoveredList[j] == l)
							break;
					}

					if (j >= CommonData->CellsBeingUncoveredSize) {
						CommonData->CellsBeingUncoveredList[CommonData->CellsBeingUncoveredSize] = l;
						CommonData->CellsBeingUncoveredSize++;
						CommonData->Board[l].JustMarkedForUncover = true;
					}
				}
			}

			l++;
			if (l >= 0 && l < CommonData->BoardLength && CommonData->Board[k].Z < CommonData->BoardHeight - 1) {
				if (!CommonData->Board[l].Explodes && CommonData->Board[l].State == CellCovered) {
					for (j = 0; j < CommonData->CellsBeingUncoveredSize; j++) {
						if (CommonData->CellsBeingUncoveredList[j] == l)
							break;
					}

					if (j >= CommonData->CellsBeingUncoveredSize) {
						CommonData->CellsBeingUncoveredList[CommonData->CellsBeingUncoveredSize] = l;
						CommonData->CellsBeingUncoveredSize++;
						CommonData->Board[l].JustMarkedForUncover = true;
					}
				}
			}

			l++;
			if (l >= 0 && l < CommonData->BoardLength && CommonData->Board[k].X < CommonData->BoardWidth - 1 && CommonData->Board[k].Z < CommonData->BoardHeight - 1) {
				if (!CommonData->Board[l].Explodes && CommonData->Board[l].State == CellCovered) {
					for (j = 0; j < CommonData->CellsBeingUncoveredSize; j++) {
						if (CommonData->CellsBeingUncoveredList[j] == l)
							break;
					}

					if (j >= CommonData->CellsBeingUncoveredSize) {
						CommonData->CellsBeingUncoveredList[CommonData->CellsBeingUncoveredSize] = l;
						CommonData->CellsBeingUncoveredSize++;
						CommonData->Board[l].JustMarkedForUncover = true;
					}
				}
			}

			i++;
		}
	}

	Uncovering.SetLength(13);
	Uncovering.Start[0] = 255.0 / 255.0;
	Uncovering.Start[1] = 225.0 / 255.0;
	Uncovering.Start[2] = 175.0 / 255.0;
	Uncovering.Start[3] = 240.0 / 255.0;
	Uncovering.Start[4] = 205.0 / 255.0;
	Uncovering.Start[5] = 160.0 / 255.0;
	Uncovering.Start[6] = 168.0 / 255.0;
	Uncovering.Start[7] = 144.0 / 255.0;
	Uncovering.Start[8] = 112.0 / 255.0;
	Uncovering.Start[9] = 184.0 / 255.0;
	Uncovering.Start[10] = 156.0 / 255.0;
	Uncovering.Start[11] = 122.0 / 255.0;
	Uncovering.Start[12] = (CommonData->TimeStarted ? 0 : 0.06);

	Uncovering.Finish[0] = 168.0 / 255.0;
	Uncovering.Finish[1] = 144.0 / 255.0;
	Uncovering.Finish[2] = 112.0 / 255.0;
	Uncovering.Finish[3] = 184.0 / 255.0;
	Uncovering.Finish[4] = 156.0 / 255.0;
	Uncovering.Finish[5] = 122.0 / 255.0;
	Uncovering.Finish[6] = 255.0 / 255.0;
	Uncovering.Finish[7] = 225.0 / 255.0;
	Uncovering.Finish[8] = 175.0 / 255.0;
	Uncovering.Finish[9] = 240.0 / 255.0;
	Uncovering.Finish[10] = 205.0 / 255.0;
	Uncovering.Finish[11] = 160.0 / 255.0;
	Uncovering.Finish[12] = 0;
	Uncovering.SetMax(5);
}

void BoardCellUncoverStateClass::Run(CommonDataClass* CommonData)
{
	int i;

	Uncovering.Step();
	if (!Uncovering.Finished())
		return;

	for (i = 0; i < CommonData->CellsBeingUncoveredSize; i++) {
		CommonData->Board[CommonData->CellsBeingUncoveredList[i]].State = CellUncovered;
		CommonData->Board[CommonData->CellsBeingUncoveredList[i]].JustMarkedForUncover = false;
	}

	if (CommonData->Board[CommonData->CellsBeingUncoveredList[0]].Explodes) {
		CommonData->TimeStarted = true;
		CommonData->StateMachine->Switch(BOARD_CELL_EXPLODE_STATE);
	} else {
		i = 0;
		while (i < CommonData->BoardLength) {
			if ((CommonData->Board[i].Explodes && (CommonData->Board[i].State == CellUncovered))
			|| (!CommonData->Board[i].Explodes && (CommonData->Board[i].State != CellUncovered)))
				break;

			i++;
		}

		if (i < CommonData->BoardLength) {
			if (!CommonData->TimeStarted) {
				CommonData->TimeStarted = true;
				CommonData->InitialTickCount = CommonData->TickCount; 
			}
			CommonData->StateMachine->Switch(BOARD_WAIT_STATE);
		} else {
			CommonData->LastGameWon = true;
			CommonData->StateMachine->Switch(GAME_WON_APPEAR_STATE);
		}
	}
	CommonData->CellsBeingUncoveredSize = 0;
}

void BoardCellUncoverStateClass::Draw(CommonDataClass* CommonData)
{
	int i;
	int j;
	int k;
	int x;
	int z;
	int Top;
	int Bottom;

	Operations::DrawSmallUpperLeftLogo(CommonData);
	if (CommonData->ToBottomScreen) {
		Top = CommonData->LowerTopCell;
		Bottom = CommonData->LowerBottomCell;
	} else {
		Top = CommonData->UpperTopCell;
		Bottom = CommonData->UpperBottomCell;
	};
	glBindTexture(0, 0);
	glColor3f(210.0 / 255.0, 180.0 / 255.0, 140.0 / 255.0);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for (j = Top; j < Bottom; j++) {
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for (i = CommonData->LeftCell; i < CommonData->RightCell; i++) {
			if(Operations::IsEmptyCell(CommonData, k)) {
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
	Operations::DrawNonEmptyCells(CommonData, Top, Bottom);
	glBindTexture(0, 0);
	glColor3f(255.0 / 255.0, 225.0 / 255.0, 175.0 / 255.0);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for (j = Top; j < Bottom; j++) {
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for (i = CommonData->LeftCell; i < CommonData->RightCell; i++) {
			if(!(CommonData->Board[k].JustMarkedForUncover)) {
				if(CommonData->Board[k].State == CellUncovered) {
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
				} else {
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
				}
			};
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
	for (j = Top; j < Bottom; j++) {
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for (i = CommonData->LeftCell; i < CommonData->RightCell; i++) {
			if (!CommonData->Board[k].JustMarkedForUncover) {
				if(CommonData->Board[k].State == CellUncovered) {
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
				} else {
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
				}
			}
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
	for (j = Top; j < Bottom; j++) {
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for (i = CommonData->LeftCell; i < CommonData->RightCell; i++) {
			if (!CommonData->Board[k].JustMarkedForUncover) {
				if (CommonData->Board[k].State == CellUncovered) {
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
				} else {
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
				}
			}
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
	for (j = Top; j < Bottom; j++) {
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for (i = CommonData->LeftCell; i < CommonData->RightCell; i++) {
			if (!CommonData->Board[k].JustMarkedForUncover) {
				if (CommonData->Board[k].State == CellUncovered) {
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
				} else {
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
				}
			}
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	glColor3f(Uncovering.Value[0], Uncovering.Value[1], Uncovering.Value[2]);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for (j = Top; j < Bottom; j++) {
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for (i = CommonData->LeftCell; i < CommonData->RightCell; i++) {
			if (CommonData->Board[k].JustMarkedForUncover) {
				if (CommonData->Board[k].State == CellUncovered) {
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
				} else {
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
				}
			}
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	glColor3f(Uncovering.Value[3], Uncovering.Value[4], Uncovering.Value[5]);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for(j = Top; j < Bottom; j++) {
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for (i = CommonData->LeftCell; i < CommonData->RightCell; i++) {
			if (CommonData->Board[k].JustMarkedForUncover) {
				if (CommonData->Board[k].State == CellUncovered) {
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
				} else {
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
				}
			}
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	glColor3f(Uncovering.Value[6], Uncovering.Value[7], Uncovering.Value[8]);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for (j = Top; j < Bottom; j++) {
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for (i = CommonData->LeftCell; i < CommonData->RightCell; i++) {
			if (CommonData->Board[k].JustMarkedForUncover) {
				if (CommonData->Board[k].State == CellUncovered) {
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
				} else {
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
				}
			}
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	glColor3f(Uncovering.Value[9], Uncovering.Value[10], Uncovering.Value[11]);
	k = Top * CommonData->BoardWidth + CommonData->LeftCell;
	z = Top * 3;
	for (j = Top; j < Bottom; j++) {
		x = CommonData->LeftCell * 3;
		glBegin(GL_QUADS);
		for (i = CommonData->LeftCell; i < CommonData->RightCell; i++) {
			if (CommonData->Board[k].JustMarkedForUncover) {
				if (CommonData->Board[k].State == CellUncovered) {
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 1], 0, CommonData->BoardCellZCoordinates[z + 1]);
				} else {
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 1]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 2], 0, CommonData->BoardCellZCoordinates[z + 2]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z + 3]);
					glVertex3v16(CommonData->BoardCellXCoordinates[x + 3], 0, CommonData->BoardCellZCoordinates[z]);
				}
			}
			k++;
			x = x + 3;
		};
		glEnd();
		k = k + CommonData->BoardWidth - CommonData->RightCell + CommonData->LeftCell;
		z = z + 3;
	};
	Operations::DrawSmallUpperRightClock(CommonData, Uncovering.Value[12]);
}
