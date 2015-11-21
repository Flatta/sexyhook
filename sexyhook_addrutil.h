//
// SEXYHOOK addrutil
// �֐��̃A�h���X�� �f�o�b�O��񂩂�擾����.
//
//
// by rti
//
//

#ifdef _MSC_VER
# pragma once
#endif

#ifndef ____SEXYHOOK_ADDRUTIL____72
#define ____SEXYHOOK_ADDRUTIL____72

#ifdef _WIN32
# include <Windows.h>
# include <Imagehlp.h>
# ifdef _MSC_VER
#  if _MSC_VER <= 1200
typedef int intptr_t;
typedef unsigned int uintptr_t;
#  endif
# else
#  include <inttypes.h>
# endif
# pragma comment(lib, "Imagehlp.lib")
# pragma comment(lib, "Dbghelp.lib")
#else
# include <inttypes.h>
# include <sys/mman.h>
# include <string.h>
typedef void *PROC;
#endif

class SEXYHOOKAddrUtil {
public:
#ifdef _WIN32
	// �Q�l :pdb2map.
	static void *strstr_addr(const char *inFunctionName) {
		BOOL r;
		char filename[MAX_PATH] = {0};
		r = ::GetModuleFileNameA(NULL, filename, MAX_PATH);
		if (!r) {
			// �����̃t�@�C�������擾�ł��܂���
			SEXYHOOK_BREAKPOINT;
		}
		// �V���{���G���W���̏�����
		r = ::SymInitialize(NULL, NULL, FALSE);
		if (!r) {
			// �G���W�����������ł��܂���.
			SEXYHOOK_BREAKPOINT;
		}
		// �����̃t�@�C�����J��.
		IMAGEHLP_MODULE imageModule = {sizeof(IMAGEHLP_MODULE)};
		HANDLE fileHandle = CreateFileA(
			filename,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (INVALID_HANDLE_VALUE == fileHandle) {
			// �����̃t�@�C�����J���܂���
			SEXYHOOK_BREAKPOINT;
		}
		DWORD64 baseAddress = SymLoadModule64(NULL, fileHandle, filename, NULL, 0, 0);
		if (!baseAddress) {
			CloseHandle(fileHandle);
			SEXYHOOK_BREAKPOINT;
		}
		class EnumSymProcCallbackClass {
		public:
			EnumSymProcCallbackClass(const char* inFunctionName) {
				this->FunctionName = inFunctionName;
				this->FoundAddress = NULL;
			}
			// �߂�ǂ����炱���ł���w
			const char *FunctionName;
			void *FoundAddress;
			/*
			static BOOL CALLBACK EnumSymProc(
				PSTR  SymbolName,
				ULONG SymbolAddress,
				ULONG SymbolSize,
				PVOID UserContext
			) {
				// debug
				//printf("%08X %4u %s\n", SymbolAddress, SymbolSize, SymbolName);
				EnumSymProcCallbackClass *myThis = (EnumSymProcCallbackClass *)UserContext;
				if (strstr(SymbolName, myThis->FunctionName) == NULL) {
					// ������Ȃ��̂Ŏ���
					return TRUE;
				}
				// ��������!
				myThis->FoundAddress = (void *)SymbolAddress;
				return FALSE;
			}
			*/			
			static BOOL CALLBACK EnumSymProc2(
				PSYMBOL_INFO pSymInfo,
				ULONG SymbolSize,
				PVOID UserContext
			) {
				// debug
				//printf("%08X %4u %s\n", pSymInfo->Address, SymbolSize, pSymInfo->Name);
				EnumSymProcCallbackClass *myThis = (EnumSymProcCallbackClass *)UserContext;
				if (strstr(pSymInfo->Name, myThis->FunctionName) == NULL) {
					// ������Ȃ��̂Ŏ���
					return TRUE;
				}
				// ��������!
				myThis->FoundAddress = (void *)pSymInfo->Address;
				return FALSE;
			}
		} enumcallback(inFunctionName);
		// �V���{���̗�
		//r = SymEnumerateSymbols(NULL, baseAddress, (PSYM_ENUMSYMBOLS_CALLBACK)EnumSymProcCallbackClass::EnumSymProc, (void *)&enumcallback);
		r = SymEnumSymbols(NULL, baseAddress, NULL, (PSYM_ENUMERATESYMBOLS_CALLBACK)EnumSymProcCallbackClass::EnumSymProc2, (void *)&enumcallback);
		if (!r) {
			CloseHandle(fileHandle);
			SEXYHOOK_BREAKPOINT;
		}
		SymCleanup(NULL);
		CloseHandle(fileHandle);
		// ������Ȃ������H
		if (enumcallback.FoundAddress == NULL) {
			SEXYHOOK_BREAKPOINT;
		}
		return enumcallback.FoundAddress;
	}
#endif	// _WIN32
};

#endif	// !____SEXYHOOK_ADDRUTIL____72