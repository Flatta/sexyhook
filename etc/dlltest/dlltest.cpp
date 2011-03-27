// dlltest.cpp : DLL �A�v���P�[�V�����p�̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

extern "C" __declspec(dllexport) int CALLBACK DllAdd(int a , int b)
{
	return a + b;
}

extern "C" __declspec(dllexport) int CALLBACK DllMessageBoxAPI(int a , int b)
{
	char buf[1024];
	_snprintf(buf , 1023 , "Ans : %d" , a , b);

	return MessageBoxA(NULL , buf , "dll" , 0 ); 
}

extern "C" __declspec(dllexport) int CALLBACK DllMul(int a , int b)
{
	//�ʂ̃��C�u�����ɖ{�̂��������Ă�.
	HMODULE mod = LoadLibrary("dlltest2.dll");
	if (mod == NULL)
	{
		printf("dlltest2.dll���Ăяo���܂���");
		return -1;
	}

	//export
	PROC orignalProc = GetProcAddress(mod , "Dll2Mul" );
	if (orignalProc == NULL)
	{
		printf("dlltest2.dll �� Dll2Mul���Ăяo���܂���");
		return -2;
	}
	int r =  ((int (__stdcall *) (int,int))orignalProc)(4,2);


	FreeLibrary(mod);

	return r;
}
