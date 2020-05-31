#include <windows.h> 
#include "NexInput.h"

#define DLLEXPORT extern "C" __declspec(dllexport)

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH: {
			break;
		}

		case DLL_PROCESS_DETACH: {
			break;
		}
	}
	return true;
}

DLLEXPORT DWORD __stdcall NEXInputGetState(__in DWORD dwUserIndex, __out NEX_INPUT_STATE *pState)
{
	pState->Buttons = 0; //0 .. 255
	pState->LeftTrigger = 0; //0 .. 255
	pState->RightTrigger = 0; //0 .. 255
	pState->AxisLX = 0; //-32768 .. 32767
	pState->AxisLY = 0; //-32768 .. 32767
	pState->AxisRX = 0; //-32768 .. 32767
	pState->AxisRY = 0; //-32768 .. 32767

	pState->Yaw = 0;	// -179.99 .. 179.99
	pState->Pitch = 0;	// -179.99 .. 179.99
	pState->Roll = 0;	// -179.99 .. 179.99
	
	if (dwUserIndex == 0)
		return ERROR_SUCCESS;
	else
		return ERROR_DEVICE_NOT_CONNECTED;
}

DLLEXPORT DWORD __stdcall NEXInputSetState(__in DWORD dwUserIndex, __in NEX_OUTPUT_STATE *pOutputState)
{
	//Vibration
	/*
	pOutputState->LeftMotorSpeed	//0 .. 65535
	pOutputState->RightMotorSpeed	//0 .. 65535
	*/

	//RGB-LED
	/*
	pOutputState->LEDBrightness	//0 .. 255
	pOutputState->LEDRed		//0 .. 255
	pOutputState->LEDGreen		//0 .. 255
	pOutputState->LEDBlue		//0 .. 255
	*/

	if (dwUserIndex == 0)
		return ERROR_SUCCESS;
	else
		return ERROR_DEVICE_NOT_CONNECTED;
}

DLLEXPORT DWORD __stdcall NEXInputGetInfo(__in DWORD dwUserIndex, __out NEX_CONTROLLER_INFO *pControllerInfo)
{
	pControllerInfo->ControllerType = NEX_UNKNOWN_CONTROLLER; //or MICROSOFT_XBOX_ONE_CONTROLLER, SONY_DUALSHOCK_4_CONTROLLER, NEX_UNKNOWN_CONTROLLER or another 
	pControllerInfo->ConnectType = NEX_CONTROLLER_WIRED; //or NEX_CONTROLLER_WIRELESS
	pControllerInfo->BatteryLevel = NEX_BATTERY_NONE; //1 .. 5 or NEX_BATTERY_NONE
	pControllerInfo->SupportRotation = false; //Gyroscope

	if (dwUserIndex == 0)
		return ERROR_SUCCESS;
	else
		return ERROR_DEVICE_NOT_CONNECTED;
}

DLLEXPORT DWORD __stdcall NEXInputPowerOff(__in DWORD dwUserIndex)
{
	//Turn off controller
	if (dwUserIndex == 0)
		return ERROR_SUCCESS;
	else
		return ERROR_DEVICE_NOT_CONNECTED;
}
