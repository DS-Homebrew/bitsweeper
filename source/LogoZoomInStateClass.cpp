#include "LogoZoomInStateClass.h"
#include "CommonDataClass.h"
#include "OperationsClass.h"
#include "StateMachineClass.h"
#include "StartButtonZoomInStateClass.h"
#include <math.h>

LogoZoomInStateClass::LogoZoomInStateClass()
: StateClass()
{
}

void LogoZoomInStateClass::Start(CommonDataClass* CommonData)
{
	Count = 0;
	Factor = 0;
}

void LogoZoomInStateClass::Run(CommonDataClass* CommonData)
{
	Count++;
	Factor = sin((Count * 5 * M_PI) / (6 * 10));
	if(Count >= 10)
	{
		CommonData->StateMachine->Switch(START_BUTTON_ZOOM_IN_STATE);
	};
}

void LogoZoomInStateClass::Draw(CommonDataClass* CommonData)
{
	glBindTexture(0, CommonData->Textures[LOGO_IMG]);
	glBegin(GL_QUADS);
	glTexCoord2t16(inttot16(32), inttot16(16));
	glVertex3f(-0.15 * Factor, 0.0, 0.1 + 0.075 * Factor);
	glTexCoord2t16(inttot16(32), inttot16(113));
	glVertex3f(-0.15 * Factor, 0.0, 0.1 - 0.075 * Factor);
	glTexCoord2t16(inttot16(225), inttot16(113));
	glVertex3f(0.15 * Factor, 0.0, 0.1 - 0.075 * Factor);
	glTexCoord2t16(inttot16(225), inttot16(16));
	glVertex3f(0.15 * Factor, 0.0, 0.1 + 0.075 * Factor);
	glEnd();
}
