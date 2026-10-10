#include "stdlib.h"
HWND hWin = NULL;
DWORD pid = NULL;
DWORD old = NULL;
HANDLE hProcess = NULL;

HWND GetWindowHandle(DWORD tPID)
{
	//Get first window handle
	HWND res = FindWindow(NULL,NULL);
	DWORD mPID = NULL;
	while(res != 0)
	{
		if(!GetParent(res))
		{
			GetWindowThreadProcessId(res,&mPID);
			if (mPID == tPID)
				return res;
		}
		res = GetWindow(res, GW_HWNDNEXT);
	}


}

void GetID(char * name)
{
	hWin = ::FindWindow(name, NULL);
	::GetWindowThreadProcessId(hWin, &pid);
}

char * GetString(DWORD address, DWORD length)
{
	char * result = new char[length];
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, length, PAGE_READWRITE, &old);
	::ReadProcessMemory(hProcess, (LPVOID)address, result, length, 0);
	::CloseHandle(hProcess);
	return result;
}

void SetString(DWORD address, char * value)
{
	DWORD length = strlen(value);
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, length, PAGE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, value, length, 0);
	::CloseHandle(hProcess);
}

float GetFloat(DWORD address)
{
	float result = NULL;
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 4, PAGE_READWRITE, &old);
	::ReadProcessMemory(hProcess, (LPVOID)address, &result, 4, 0);
	::CloseHandle(hProcess);
	return result;
}
void SetFloat(DWORD address, float value)
{
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 4, PAGE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, &value, 4, 0);
	::CloseHandle(hProcess);
}
BYTE GetByte(DWORD address)
{
	BYTE result = NULL;
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 1, PAGE_READWRITE, &old);
	::ReadProcessMemory(hProcess, (LPVOID)address, &result, 1, 0);
	::CloseHandle(hProcess);
	return result;
}
void SetByte(DWORD address, BYTE value)
{
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 1, PAGE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, &value, 1, 0);
	::CloseHandle(hProcess);
}
void SetBytes(DWORD address, BYTE * value, DWORD length)
{
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, length,PAGE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, value, length, 0);
	::CloseHandle(hProcess);
}

DWORD GetLong(DWORD address)
{
	DWORD result = NULL;
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 4, PAGE_READWRITE, &old);
	::ReadProcessMemory(hProcess, (LPVOID)address, &result, 4, 0);
	::CloseHandle(hProcess);
	return result;
}	

void SetLong(DWORD address, DWORD value)
{
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, 4, PAGE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, &value, 4, 0);
	::CloseHandle(hProcess);
}

BYTE   * HexToBytes(char * value,  DWORD * length)
{

	int abytecount = strlen(value)/2;

	BYTE * byteArray = new BYTE[abytecount];

	char * separator;

	char token[4];

	for (int bx = 0; bx < abytecount; bx ++)
	{		
		token[0] = value[bx*2 +0];
		token[1] = value[bx*2 +1];
		token[2] = 0x58;
		token[3] = 0;
		int i = (BYTE)strtol( (char *)token, &separator, 16);
		byteArray[bx] = (BYTE) i;
	}

	
	*length =  abytecount; 
	
	return byteArray;
}

void SetHex(DWORD address, char * value)
{
	DWORD length = 0;
	BYTE * result = HexToBytes(value,&length);
	
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)pid);
	::VirtualProtectEx(hProcess, (LPVOID)address, length, PAGE_READWRITE, &old);
	::WriteProcessMemory(hProcess, (LPVOID)address, result, length, 0);
	::CloseHandle(hProcess);
	delete[] result;
}

void SetCall(DWORD address, DWORD calladdress )
{
	DWORD endaddress = address + 5;
	DWORD waddress = calladdress - endaddress;
	
	BYTE * bytearray = new BYTE[5];
	bytearray[0] = 0xE8;
	memcpy(bytearray+1,&waddress,4);
	
	SetBytes(address, bytearray,5);

	delete[] bytearray;
}
void SetJump(DWORD address, DWORD calladdress )
{
	DWORD endaddress = address + 5;
	DWORD waddress = calladdress - endaddress;
	
	BYTE * bytearray = new BYTE[5];
	bytearray[0] = 0xE9;
	memcpy(bytearray+1,&waddress,4);
	
	SetBytes(address, bytearray,5);

	delete[] bytearray;
}
DWORD GetLong_ASM(long address)
{
	DWORD res = 0;

	__asm 
	{
		push	eax
		mov		eax,address
		mov		eax,[eax]
		mov		res,eax
		pop		eax
	}
	return res;
}