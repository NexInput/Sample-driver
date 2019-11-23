#include <windows.h> 

#define DLLEXPORT extern "C" __declspec(dllexport)

#define NEX_GAMEPAD_DPAD_UP				0x0001
#define NEX_GAMEPAD_DPAD_DOWN			0x0002
#define NEX_GAMEPAD_DPAD_LEFT			0x0004
#define NEX_GAMEPAD_DPAD_RIGHT			0x0008
#define NEX_GAMEPAD_START				0x0010
#define NEX_GAMEPAD_BACK				0x0020
#define NEX_GAMEPAD_LEFT_THUMB			0x0040
#define NEX_GAMEPAD_RIGHT_THUMB			0x0080
#define NEX_GAMEPAD_LEFT_SHOULDER		0x0100
#define NEX_GAMEPAD_RIGHT_SHOULDER		0x0200
#define NEX_GAMEPAD_A					0x1000
#define NEX_GAMEPAD_B					0x2000
#define NEX_GAMEPAD_X					0x4000
#define NEX_GAMEPAD_Y					0x8000

#define NEX_CONTROLLER_WIRED			0
#define NEX_CONTROLLER_WIRELESS			1
#define NEX_BATTERY_NONE				0
#define NEX_BATTERY_LOW					1
#define NEX_BATTERY_FULL				5

#define NEX_INPUT_MAX_COUNT				4

#define ERROR_DEVICE_NOT_CONNECTED		1
#define ERROR_SUCCESS					0

#define NEX_UNKNOWN_CONTROLLER			0;

#define MICROSOFT_XBOX_360_CONTROLLER	1
#define MICROSOFT_XBOX_ONE_CONTROLLER	2

#define SONY_DUALSHOCK_3_CONTROLLER		26
#define SONY_DUALSHOCK_4_CONTROLLER		27
#define SONY_DUALSHOCK_5_CONTROLLER		27

#define NINTENDO_SWITCH_PRO_CONTROLLER	51

typedef struct _NEX_INPUT_STATE
{
	WORD								Buttons;
	BYTE								LeftTrigger;
	BYTE								RightTrigger;
	SHORT								AxisLX;
	SHORT								AxisLY;
	SHORT								AxisRX;
	SHORT								AxisRY;
	float								Yaw;
	float								Pitch;
	float								Roll;
} NEX_INPUT_STATE, *PNEX_INPUT_STATE;

typedef struct _NEX_OUTPUT_STATE
{
	WORD								LeftMotorSpeed;
	WORD								RightMotorSpeed;
	BYTE								LEDBrightness;
	BYTE								LEDRed;
	BYTE								LEDGreen;
	BYTE								LEDBlue;
} NEX_OUTPUT_STATE, *PNEX_OUTPUT_STATE;

typedef struct _NEX_CONTROLLER_INFO
{
	WORD								ControllerType;
	BYTE								ConnectType;
	BYTE								BatteryLevel;
	bool								SupportRotation;
} NEX_CONTROLLER_INFO, *PNEX_CONTROLLER_INFO;

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
