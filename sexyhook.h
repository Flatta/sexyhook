#ifdef _MSC_VER 
	//for VC++
	#pragma once
#endif
#ifndef ____SEXYHOOK____72
#define ____SEXYHOOK____72
//
//�ڍ����������ɍ쐬����
//SEXYHOOK
//
//
// by rti
//
//
// new BSD ���C�Z���X / NYSL ���C�Z���X �D���Ɏg���΂��������Ȃ��H ^q^
//

//include�Ƃ���`�Ƃ�.
#ifdef _WINDOWS_
	//windows
	#include <windows.h>
	#include <imagehlp.h>
	#ifdef _MSC_VER 
		#if _MSC_VER <= 1200 
			typedef int intptr_t; 
			typedef unsigned int uintptr_t; 
		#endif 
	#else 
	#endif 
#else
	//linux
	#include <stdarg.h>
	#include <inttypes.h>
	#include <sys/mman.h>
	#include <string.h>
	typedef void* PROC;
#endif

//�����I�Ƀ|�C���^�ɂ���(�ד�)
#ifdef __GNUC__
	// ... �����p�����Z
	static void* SEXYHOOK_DARKCAST(int dummy, ... )
	{
//		return *(void**)(&dummy + 1);
		va_list ap;
		va_start(ap, dummy);
		void* p = va_arg(ap, void*);
		va_end(ap);

		return p;
	}
#else
	//msvc �̂� gcc ���ƃG���[���ł邯�ǁA�A�[�L�e�N�`���ˑ����Ȃ��̂ōD����!
	template<typename _T> static void* SEXYHOOK_DARKCAST(int dummy, _T p)
	{
		return *reinterpret_cast<void**>(&p);
	}
#endif

//�u���[�N�|�C���g�ƃA�T�[�V����
#ifdef __GNUC__
	//gcc
	#define SEXYHOOK_BREAKPOINT	{ asm ("int $3") ; }
	#define SEXYHOOK_ASSERT(f) \
		if (!(f) ) \
		{ \
			asm ("int $3") ; \
		} 
#else
	//msvc
	#define SEXYHOOK_BREAKPOINT	{ DebugBreak(); }
	#define SEXYHOOK_ASSERT(f) \
		if (!(f) ) \
		{ \
			MSG msg;	\
			BOOL bQuit = PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);	\
			if (bQuit)	PostQuitMessage((int)msg.wParam);	\
			DebugBreak(); \
		} 
#endif

//�Ăяo���K��
#ifdef __GNUC__
	//gcc
	#define SEXYHOOK_STDCALL			__attribute__ ((stdcall))
	#define SEXYHOOK_CDECL				__attribute__ ((cdecl))
	#define SEXYHOOK_FASTCALL			__attribute__ ((regparm(3)))
	#define SEXYHOOK_FASTCALLN(N)		__attribute__ ((regparm(N)))
	#define SEXYHOOK_CLASS											//__thiscall __cdecl �Ƃ͈Ⴄ�炵��.
	#define SEXYHOOK_CLASS_STDCALL		__attribute__ ((stdcall))
	#define SEXYHOOK_CLASS_CDECL		__attribute__ ((cdecl))
	#define SEXYHOOK_CLASS_FASTCALL		__attribute__ ((regparm(3)))
	#define SEXYHOOK_CLASS_FASTCALLN(N)	__attribute__ ((regparm(N)))
#else
	//msvc
	#define SEXYHOOK_STDCALL		__stdcall
	#define SEXYHOOK_CDECL			__cdecl
	#define SEXYHOOK_FASTCALL		__fastcall
	#define SEXYHOOK_CLASS										//__thiscall __cdecl �Ƃ͈Ⴄ�炵��.
	#define SEXYHOOK_CLASS_STDCALL	__stdcall
	#define SEXYHOOK_CLASS_CDECL	__cdecl
	#define SEXYHOOK_CLASS_FASTCALL	__fastcall
#endif

//__LINE__�𕶎���ɂ��邽�߂̃}�N��
//�Q�l:http://oshiete1.goo.ne.jp/qa1219076.html
#define SEXYHOOK_LINE_TOSTR(x) SEXYHOOK_LINE_TOSTR_(x)
#define SEXYHOOK_LINE_TOSTR_(x) #x

#define SEXYHOOK_LINE_STRCAT(x,y) SEXYHOOK_LINE_STRCAT_(x,y)
#define SEXYHOOK_LINE_STRCAT_(x,y) x##y

//�}�N�����ēx�W�J����.
#define SEXYHOOK_REMACRO(MACRO)	MACRO

//�N���X���\�b�h�łȂ��ꍇ�́A static �w��ɂ��Ȃ��Ƃ����Ȃ��̂ŁA������ static����������o��.
#define SEXYHOOK_STDCALL__STATIC			static
#define SEXYHOOK_CDECL__STATIC				static
#define SEXYHOOK_FASTCALL__STATIC			static
#define SEXYHOOK_FASTCALLN__STATIC			static
#define SEXYHOOK_CLASS__STATIC	
#define SEXYHOOK_CLASS_STDCALL__STATIC	
#define SEXYHOOK_CLASS_CDECL__STATIC	
#define SEXYHOOK_CLASS_FASTCALL__STATIC	
#define SEXYHOOK_CLASS_FASTCALLN__STATIC	

//�N���X���\�b�h�̏ꍇ�� this ���B�����łȂ���� NULL ���쐬����.
#define SEXYHOOK_STDCALL__THIS			NULL
#define SEXYHOOK_CDECL__THIS			NULL
#define SEXYHOOK_FASTCALL__THIS			NULL
#define SEXYHOOK_FASTCALLN__THIS		NULL
#define SEXYHOOK_CLASS__THIS			this
#define SEXYHOOK_CLASS_STDCALL__THIS	this
#define SEXYHOOK_CLASS_CDECL__THIS		this
#define SEXYHOOK_CLASS_FASTCALL__THIS	this

//�֐��Ȃ̂����\�b�h�Ȃ̂��� typedef �̏���ւ���.
#define SEXYHOOK_STDCALL__HOOKDEF			
#define SEXYHOOK_CDECL__HOOKDEF			
#define SEXYHOOK_FASTCALL__HOOKDEF			
#define SEXYHOOK_FASTCALLN__HOOKDEF			
#define SEXYHOOK_CLASS__HOOKDEF				SEXYHOOKFuncBase::
#define SEXYHOOK_CLASS_STDCALL__HOOKDEF		SEXYHOOKFuncBase::
#define SEXYHOOK_CLASS_CDECL__HOOKDEF		SEXYHOOKFuncBase::
#define SEXYHOOK_CLASS_FASTCALL__HOOKDEF	SEXYHOOKFuncBase::
#define SEXYHOOK_CLASS_FASTCALLN__HOOKDEF	SEXYHOOKFuncBase::

//const����
#define SEXYHOOK_STDCALL__CONST			
#define SEXYHOOK_CDECL__CONST			
#define SEXYHOOK_FASTCALL__CONST			
#define SEXYHOOK_FASTCALLN__CONST			
#define SEXYHOOK_CLASS__CONST				const
#define SEXYHOOK_CLASS_STDCALL__CONST		const
#define SEXYHOOK_CLASS_CDECL__CONST			const
#define SEXYHOOK_CLASS_FASTCALL__CONST		const
#define SEXYHOOK_CLASS_FASTCALLN__CONST		const


//SEXYHOOK�{�� �N���X���N���X�Ƃ��Ď�������.
#define SEXYHOOK_BEGIN(RET,CALLTYPE,FUNCADDRESS,ARGS) \
	class SEXYHOOK_LINE_STRCAT(SEXYHOOKFunc,__LINE__) : public SEXYHOOKFuncBase { \
	public: \
		SEXYHOOK_LINE_STRCAT(SEXYHOOKFunc,__LINE__)() \
		{ \
		} \
		void Hook(void* inVCallThisPointer = NULL,void* inFuncAddress2 = NULL) \
		{ \
			*(getSexyhookThisPointer()) =  (uintptr_t)this; \
			void* p = inFuncAddress2; \
			if (!p) p = EvalLoad(#FUNCADDRESS); \
			if (!p) p = SEXYHOOK_DARKCAST(0,(HookDef)FUNCADDRESS); \
			FunctionHookFunction( \
					 p \
					,SEXYHOOK_DARKCAST(0,&SEXYHOOK_LINE_STRCAT(SEXYHOOKFunc,__LINE__)::HookFunction) \
					,SEXYHOOK_DARKCAST(0,&SEXYHOOK_LINE_STRCAT(SEXYHOOKFunc,__LINE__)::CallOriginalFunction) \
					,inVCallThisPointer \
					); \
		} \
		void UnHook() \
		{ \
			FunctionUnHookFunction(); \
		} \
		virtual ~SEXYHOOK_LINE_STRCAT(SEXYHOOKFunc,__LINE__)() \
		{ \
			FunctionUnHookFunction(); \
		} \
		typedef RET ( SEXYHOOK_REMACRO(CALLTYPE##__HOOKDEF)* HookDef) ARGS ; \
		typedef RET ( SEXYHOOK_REMACRO(CALLTYPE##__HOOKDEF)* HookDefConst) ARGS SEXYHOOK_REMACRO(CALLTYPE##__CONST); \
		static uintptr_t* getSexyhookThisPointer() \
		{ \
			static uintptr_t thisSaver = 0; \
			return &thisSaver ; \
		} \
		SEXYHOOK_REMACRO(CALLTYPE##__STATIC) RET  CALLTYPE CallOriginalFunction ARGS \
		{ \
			volatile int mizumashi = 1 ; for(volatile int i = 0 ; i < 1000 ; i++){ mizumashi= mizumashi * i + 1; }; \
			throw 0;\
		} \
		SEXYHOOK_REMACRO(CALLTYPE##__STATIC) RET  CALLTYPE HookFunction ARGS \
		{ \
			SEXYHOOK_LINE_STRCAT(SEXYHOOKFunc,__LINE__)* sexyhookThis = ((SEXYHOOK_LINE_STRCAT(SEXYHOOKFunc,__LINE__)*)(*getSexyhookThisPointer()) ); \
			void * sexyhookOrignalThis = (void*) SEXYHOOK_REMACRO(CALLTYPE##__THIS);

#define SEXYHOOK_END \
	} } SEXYHOOK_LINE_STRCAT(objectFUNCHook,__LINE__);\
	SEXYHOOK_LINE_STRCAT(objectFUNCHook,__LINE__).Hook

#define SEXYHOOK_END_AS() \
	} } 



//�ꎞ�I�Ƀt�b�N����߂� �s�v�ɂȂ�܂����B
#define SEXYHOOK_UNHOOK()	

//�I���W�i���� this pointer
#define SEXYHOOK_THIS(cast)	((cast) sexyhookOrignalThis )

//�����������肵�āA���O�������܂��Ȃ����ꍇ�̉���������[�U�[�ɒ񋟂���.
#define SEXYHOOK_AUTOCAST_CONST(func)	(HookDefConst)(func)

//DLL�����[�h����\���B
//����ANULL�Ԃ��Ă��邾���Ɍ������ˁB����B�����ǂˁA�����Ɠ���������S���Ăق����B
#define SEXYHOOK_DYNAMICLOAD(DLLNAME,FUNCNAME)	NULL

//�֐��t�b�N���s���ۂɏ���������̈�̃T�C�Y
typedef  char FUNCTIONHOOK_ASM[14*3] ;

//�֐�/���\�b�h���t�b�N����.
class SEXYHOOKFuncBase
{
	//�����������A�h���X�̐擪
	void*			 OrignalFunctionAddr;
	//�����������̈��ێ�����̈�
	FUNCTIONHOOK_ASM OrignalAsm;
	//�t�b�N����̂Ɏg�����R�[�h
	FUNCTIONHOOK_ASM HookAsm;
	//�g�����|�����𐶐�����R�[�h�̃T�C�Y
	int              HookAsmSize;
	//�I�y�R�[�h�������������Č��肵���A�㏑�������T�C�Y assert(SaveAsmSize >= HookAsmSize)
	int	             SaveAsmSize;

	//DLL�C���X�^���X
	void*			 APIHookDLLHandle;

public:
	enum SEXYHOOK_CPU_ARCHITECTURE
	{
		 SEXYHOOK_CPU_ARCHITECTURE_X86
		,SEXYHOOK_CPU_ARCHITECTURE_X64
	};

	//�֐��t�b�N���J�n����.
	void FunctionHookFunction(void * inUkeFunctionProc , void * inSemeFunctionProc ,void * inCallOriginalFunctionProc , void * inVCallThisPointer )
	{
		//�t�b�N����֐�(�U��)���J�n����A�h���X�����߂�
		uintptr_t semeFunctionAddr = CalcSemeFunctionAddress(inSemeFunctionProc );
		//�t�b�N�����֐�(��)���J�n����A�h���X�����߂�
		uintptr_t ukeFunctionAddr =  CalcUkeFunctionAddress(inUkeFunctionProc , inVCallThisPointer);


		//����������}�V����
		//�g�����|�����t�b�N���s���I�y�R�[�h�𐶐����A������Ԃ�.
		this->HookAsmSize = MakeTrampolineHookAsm( &this->HookAsm , ukeFunctionAddr , semeFunctionAddr) ;
		//�I�y�����h�����l�����āA�j�󂷂�o�C�g�T�C�Y�����肷��.
		this->SaveAsmSize = CalcSeparateOpecodeLength(ukeFunctionAddr,this->HookAsmSize);

		this->OrignalFunctionAddr = (void*)ukeFunctionAddr;
		//�t�b�N�����֐��̐擪�����������āA�t�b�N���[�`���֐�����ڂ��悤�ɂ���B
		BackupFunction(this->OrignalFunctionAddr ,&this->OrignalAsm,this->SaveAsmSize);
		OverraideFunction(this->OrignalFunctionAddr , this->HookAsm,this->HookAsmSize);

		//�t�b�N�p�ɑޔ����������[�`���̖����Ɍ��̃R�[�h�ɖ߂�jmp�R�[�h�𖄂ߍ���
		uintptr_t orignalCallFunctionAddr = CalcSemeFunctionAddress(inCallOriginalFunctionProc );
		int orginalCallAsmSize = MakeTrampolineHookAsm(
			 (FUNCTIONHOOK_ASM*) (((uintptr_t)&this->OrignalAsm) + this->SaveAsmSize)
			, orignalCallFunctionAddr + this->SaveAsmSize 
			, ukeFunctionAddr + this->SaveAsmSize ) ;
		OverraideFunction((void*)orignalCallFunctionAddr , OrignalAsm ,this->SaveAsmSize + orginalCallAsmSize);
		return ;
	}

	//�t�b�N����Ɏg��ꂽ�\�������āA
	//SEXYHOOK_APILOAD ��������Adll�̃��[�h���d���ށB eval�Ȃ�ʁAevil�B
	void* EvalLoad(const char * inAddress)
	{
		//����������.
		this->APIHookDLLHandle = NULL;

		const char * p = inAddress;

		p = strstr(p , "SEXYHOOK_DYNAMICLOAD");
		if (!p) return NULL;

		//��1���� DLL��
		const char * dll1 = strstr(p , "\"");
		if (!dll1) return NULL;
		const char * dll2 = strstr(dll1+1 , "\"");
		if (!dll2) return NULL;

		//��2���� �֐���
		const char * func1 = strstr(dll2+1 , "\"");
		if (!func1) return NULL;
		const char * func2 = strstr(func1+1 , "\"");
		if (!func2) return NULL;


		//��������o�b�t�@�ɕ�������.
		char buffer[1024];
		int len = (int)(func2 - inAddress) + 1;
		if (len >= sizeof(buffer) )
		{
			//������f�J����.
			return NULL;
		}
		memcpy(buffer , inAddress , len );

		//�I�[���ߍ���ŁA
		buffer[(int)(dll2 - inAddress) ] = '\0';
		buffer[(int)(func2 - inAddress) ] = '\0';
		//�擪�̕ێ�
		const char * apiHookDLLName = buffer + (int)(dll1 - inAddress + 1);
		const char * apiHookFuncName = buffer + (int)(func1 - inAddress + 1);
#ifdef _WINDOWS_
		//DLL�ǂݍ���
		HMODULE mod = LoadLibraryA(apiHookDLLName);
		if ( mod == NULL )
		{
			//DLL���ǂݍ��߂܂���!
			SEXYHOOK_BREAKPOINT;
			return NULL;
		}
		//API�̃A�h���X�����߂�.
		void* orignalProc = (void*)GetProcAddress(mod , apiHookFuncName );
		if ( orignalProc == NULL )
		{
			//API�����[�h�ł��܂���B
			SEXYHOOK_BREAKPOINT;
			FreeLibrary(mod);
			return NULL;
		}
		//�J���̂��߂̋L�^.
		this->APIHookDLLHandle = (void*)mod;
		
		return orignalProc;
#else
		return NULL;
#endif
	}

	//�֐��t�b�N����߂�
	void FunctionUnHookFunction()
	{
		if (this->OrignalFunctionAddr == NULL)
		{
			return ;
		}
		OverraideFunction(this->OrignalFunctionAddr , this->OrignalAsm , this->SaveAsmSize);
		this->OrignalFunctionAddr = NULL;

		//API���A�����[�h���Ȃ��Ă͂����Ȃ��ꍇ�͊J������.
		if(this->APIHookDLLHandle)
		{
#ifdef _WINDOWS_
			FreeLibrary((HMODULE)this->APIHookDLLHandle);
#endif
			this->APIHookDLLHandle = NULL;
		}
	}
private:
	//�t�b�N�����֐��̃A�h���X��Ԃ�.
	void* getOrignalFunctionAddr()  const
	{
		return this->OrignalFunctionAddr;
	}

	//�t�b�N����֐�(�U��)���J�n����A�h���X�����߂�
	uintptr_t CalcSemeFunctionAddress(void * inSemeFunctionProc )
	{
		//�t�b�N�֐����J�n������΃A�h���X
		if (*((unsigned char*)inSemeFunctionProc+0) == 0xe9)
		{
			//�t�b�N�֐��� ILT�o�R�Ŕ��ł���ꍇ
			//0xe9 call [4�o�C�g���΃A�h���X]          4�o�C�g���΂�64bit �ł��ς�炸
			uintptr_t jmpaddress = *((unsigned long*)((unsigned char*)inSemeFunctionProc+1));
			return (((uintptr_t)inSemeFunctionProc) + jmpaddress) + 5;
		}
		else
		{
			//���A�v���O�����̈�ɔ��ł���ꍇ
			return (uintptr_t)inSemeFunctionProc ;
		}
	}

	//MSVC++ �� vcall����͂���.
	uintptr_t CalcVCall(uintptr_t overraideFunctionAddr , void * inVCallThisPointer )
	{
		//���z�֐��� vcall�������ꍇ...
		int vcallhead = 0;
		if (
				*((unsigned char*)overraideFunctionAddr+0) == 0x8B
			&&	*((unsigned char*)overraideFunctionAddr+1) == 0x01
			&&	*((unsigned char*)overraideFunctionAddr+2) == 0xFF
			)
		{
			vcallhead = 3;
		}
		else if (
				*((unsigned char*)overraideFunctionAddr+0) == 0x48
			&&	*((unsigned char*)overraideFunctionAddr+1) == 0x8B
			&&	*((unsigned char*)overraideFunctionAddr+2) == 0x01
			&&	*((unsigned char*)overraideFunctionAddr+3) == 0xFF
			)
		{
			vcallhead = 4;
		}
		else
		{
			//vcall�ł͂Ȃ�.
			return 0;
		}

		int plusAddress = 0;
		if (*((unsigned char*)overraideFunctionAddr+vcallhead ) == 0x20)
		{
			//[[this] + 0] �ɃW�����v
			plusAddress = 0;
		}
		else if (*((unsigned char*)overraideFunctionAddr+vcallhead ) == 0x60)
		{
			//[[this] + ?] �ɃW�����v
			plusAddress = (int) *((unsigned char*)overraideFunctionAddr+ (vcallhead + 1) );	//4�o�C�g�ڂ�1�o�C�g�������Z����l
		}
		else
		{
			//[[this] + ?] �ɃW�����v���v�Z�o���܂���ł���...
			SEXYHOOK_BREAKPOINT;
		}
		//C����̂����������ŁA�|�C���^�͌^���v���X���Ă��܂��̂ŁA�|�C���^�̃T�C�Y�Ŋ����Ƃ�.
		plusAddress = plusAddress / sizeof(void*);

		//���̂悤�Ȋ֐��Ɉꎞ�I�ɔ�΂���Ă���ꍇ...
		//			vcall:
		//			00402BA0   mov         eax,dword ptr [ecx]
		//			00402BA2   jmp         dword ptr [eax]
		//8B 01 FF 20
		//
		// or
		//
		//004025D0   mov         eax,dword ptr [ecx]
		//004025D2   jmp         dword ptr [eax+4]
		//8B 01 FF 60 04
		if ( inVCallThisPointer == NULL )
		{
			//vcall�̃t�b�N�ɂ́A this�|�C���^���K�v�ł��B
			//SEXYHOOK_CLASS_END_VCALL(thisClass) �𗘗p���Ă��������B
			SEXYHOOK_BREAKPOINT;
		}

		/*
			//�����������Z��������  inVCallThisPointer = &this;
		_asm
		{
			mov ecx,inVCallThisPointer;
			mov ecx,[ecx];
			mov ecx,[ecx];
			mov overraideFunctionAddr,ecx;
		}

					or 
		_asm
		{
			mov ecx,inVCallThisPointer;
			mov ecx,[ecx];
			mov ecx,[ecx+4];			//+? �͒�`���ꂽ�֐��� virtual�̐������������
			mov overraideFunctionAddr,ecx;
		}
		*/
		//��������Ȋ���,,,�����Ă���L���X�g��.
		overraideFunctionAddr = (uintptr_t) *((void**)*((void***)inVCallThisPointer) + plusAddress);
		//�����ɂ���̂�  �֐��̖{�� jmp �ւ̖��߂̂͂�.
		if (*((unsigned char*)overraideFunctionAddr+0) == 0xe9)
		{
			//���łȂ̂Ŋ֐��̒������������邽�߁A�֐��̎��̂ւ̃A�h���X�����߂�.
			uintptr_t jmpaddress = *((unsigned long*)((unsigned char*)overraideFunctionAddr+1));
			overraideFunctionAddr = (((uintptr_t)overraideFunctionAddr) + jmpaddress) + 5;	//+5�� e9 00 00 00 00 (ILT�̃T�C�Y)
		}

		return overraideFunctionAddr;
	}


	//�t�b�N�����֐�(��)���J�n����A�h���X�����߂�
	uintptr_t CalcUkeFunctionAddress(void * inUkeFunctionProc , void * inVCallThisPointer)
	{
		#ifdef __GNUC__
			//gcc�ł͉��z�֐��̃|�C���^���擾���悤�Ƃ���ƁA vtable ����� index ��Ԃ��Ă��܂��B
			if ( (uintptr_t)inUkeFunctionProc < 100 )
			{
				//�N���X�̃C���X�^���X(this�|�C���^)���n����Ă���΁Aindex������̂̏ꏊ���v�Z�\�B
				if (inVCallThisPointer == NULL)
				{
					//this���Ȃ��Ȃ�v�Z�s�\�Ȃ̂ŁA�Ƃ肠�����Ƃ߂�.
					SEXYHOOK_BREAKPOINT;
				}
				//this������Όv�Z���ăA�h���X�����߂�.
				//�Q�l: http://d.hatena.ne.jp/Seasons/20090208/1234115944
				uintptr_t* vtable = (uintptr_t*) (*((uintptr_t*)inVCallThisPointer));
				//�Ƃ肠�����A (index - 1) / sizeof(void*) �ŃA�h���X�����܂�݂���.
				//�R���ł����Ă���̂��s�������ǁA�Ƃ肠����������.
				uintptr_t index = ((uintptr_t)inUkeFunctionProc - 1) / sizeof(void*);

				//vtable ���� index ���v�Z����.
				inUkeFunctionProc = (void*) (vtable[index] );
			}
		#endif
		
		//�t�b�N�����֐��̎��̈�����߂�.
		uintptr_t overraideFunctionAddr = 0;
		if (*((unsigned char*)inUkeFunctionProc+0) == 0xe9)
		{
			//�t�b�N�֐��� ILT�o�R�Ŕ��ł���ꍇ
			//0xe9 call [4�o�C�g���΃A�h���X]
			uintptr_t jmpaddress = *((unsigned long*)((unsigned char*)inUkeFunctionProc+1));
			overraideFunctionAddr = (((uintptr_t)inUkeFunctionProc) + jmpaddress) + 5;	//+5�� e9 00 00 00 00 (ILT�̃T�C�Y)
		}
		else
		{
			//���A�v���O�����̈�ɔ��ł���ꍇ
			overraideFunctionAddr = (uintptr_t)inUkeFunctionProc;
		}

		//���z�֐��� vcall�������ꍇ...
		uintptr_t vcallFunctionAddr = this->CalcVCall(overraideFunctionAddr,inVCallThisPointer);
		if (vcallFunctionAddr != 0)
		{
			return vcallFunctionAddr;
		}
		return overraideFunctionAddr;
	}


	//�g�����|�����t�b�N�̍쐬
	int MakeTrampolineHookAsm(FUNCTIONHOOK_ASM* outBuffer , uintptr_t inUkeFunctionAddr, uintptr_t inSemeFunctionAddr) const
	{
#if (_WIN64 || __x86_64__)
		//�Q�l http://www.artonx.org/diary/200809.html
		//     http://hrb.osask.jp/wiki/?faq/asm
		if (inSemeFunctionAddr - inUkeFunctionAddr < 0x80000000)
		{//2G�ȉ���jmp
			// 0xe9 ���΃A�h���X   = 5�o�C�g �̖���
			*((unsigned char*)outBuffer+0) = 0xe9;	//�ߗ׃W�����v JMP
			*((unsigned long*)((unsigned char*)outBuffer+1)) = (unsigned long) (inSemeFunctionAddr - inUkeFunctionAddr - 5);	//-5��jmp���ߎ��M�̃T�C�Y

			return 5;
		}
		else
		{//2G�ȏ��jmp
			//Nikolay Igotti����̕����𗘗p����. 14�o�C�g�̖���
			//push 64bit ; ret; �Ŕ�����B ret �Ȃ̂� ���΂ł͂Ȃ���΃A�h���X(inSemeFunctionAddr)������B
			//push 64bit �����̂܂܂��Ƃł��Ȃ��̂ŁA�������� push ����B
			//http://blogs.sun.com/nike/entry/long_absolute_jumps_on_amd64
			//http://www.ragestorm.net/blogs/?p=107
			*((unsigned char*)outBuffer+0) = 0x68;	//push imm32, subs 8 from rsp
			*((unsigned long*)((unsigned char*)outBuffer+1)) = 0x00000000ffffffff & inSemeFunctionAddr;

			*((unsigned char*)outBuffer+5) = 0xc7;	//mov imm32, 4(%rsp)
			*((unsigned char*)outBuffer+6) = 0x44;
			*((unsigned char*)outBuffer+7) = 0x24;
			*((unsigned char*)outBuffer+8) = 0x04;
			*((unsigned long*)((unsigned char*)outBuffer+9)) = inSemeFunctionAddr >> 32;

			*((unsigned char*)outBuffer+13) = 0xc3;	//ret

			return 14;
		}
#else
//#elif (_WIN32 || __i386__)
		//i386

		// 0xe9 ���΃A�h���X   = 5�o�C�g �̖���
		*((unsigned char*)outBuffer+0) = 0xe9;	//�ߗ׃W�����v JMP
		*((unsigned long*)((unsigned char*)outBuffer+1)) = (unsigned long) (inSemeFunctionAddr - inUkeFunctionAddr - 5);	//-5��jmp���ߎ��M�̃T�C�Y

		return 5;
#endif
	}

	//���S�ɏ㏑���ł���T�C�Y���v�Z����.
	int CalcSeparateOpecodeLength(uintptr_t inAddr , int orderriadeSize) const
	{
		int len = 0;
		while(len < orderriadeSize)
		{
#if (_WIN64 || __x86_64__)
			const SEXYHOOK_CPU_ARCHITECTURE type = SEXYHOOK_CPU_ARCHITECTURE_X64;
#else
			const SEXYHOOK_CPU_ARCHITECTURE type = SEXYHOOK_CPU_ARCHITECTURE_X86;
#endif
			len += OperandLength(((const unsigned char*)inAddr) + len ,type);
		}
		SEXYHOOK_ASSERT(sizeof(FUNCTIONHOOK_ASM) > len );
		SEXYHOOK_ASSERT(len >= orderriadeSize);
		return len;
	}

	void BackupFunction(void* inAddr , void* outOldSrc , int size)
	{
		//���荞�ރR�[�h���������݂܂��B
		SEXYHOOK_ASSERT(outOldSrc != NULL);

		//�o�b�N�A�b�v
		memcpy(outOldSrc , inAddr , size );
	}

	void OverraideFunction(void* inAddr , void* inNewSrc , int size)
	{
		#ifdef _WINDOWS_
			//������������
			unsigned long oldProtect = 0;
			VirtualProtect( inAddr , size , PAGE_EXECUTE_READWRITE , &oldProtect);
			//��������
			memcpy(inAddr , inNewSrc , size );
			//���������ɖ߂�
			VirtualProtect( inAddr , size , oldProtect , &oldProtect);
		#else
			//mprotect �ɓn���l�́A�y�[�W���E(4K)�ɍ��킹��
			//http://d.hatena.ne.jp/kanbayashi/20081005/p2
			void *pageAddr = (void*)(((uintptr_t)inAddr) & 0xFFFFF000);
			//������������
			mprotect( pageAddr, 0x1000 , PROT_READ | PROT_WRITE | PROT_EXEC);
			//��������
			memcpy(inAddr , inNewSrc , size );
			//���Ƃɖ߂������񂾂��ǂǂ�����΂����́H
		#endif
	}

	//�}�V����̒��������߂܂��B
	//http://www2.odn.ne.jp/~hab81760/modrm_sib.htm
	//http://dl.dropbox.com/u/2476414/TechResources/x86_opcodemap_1_b4.pdf
	//http://download.intel.com/jp/developer/jpdoc/IA32_Arh_Dev_Man_Vol2B_i.pdf
	//http://www.logix.cz/michal/doc/i386/app-a.htm
	//http://www.wdic.org/w/SCI/REX%E3%83%97%E3%83%AA%E3%83%95%E3%82%A3%E3%83%83%E3%82%AF%E3%82%B9
	//http://www.wdic.org/w/SCI/%E3%82%AA%E3%83%9A%E3%82%B3%E3%83%BC%E3%83%89%20(IA-32)
	//http://iwaohanma.web.fc2.com/
	static int OperandLength(const unsigned char* code,SEXYHOOK_CPU_ARCHITECTURE cputype)
	{
		//1�o�C�g����
		//0x00  �d�l���悭�킩��Ȃ�����
		//0x01  1�o�C�g�̖���
		//0x02  2�o�C�g�̖���
		//...
		//0xff	modrm
		//0xfd	modrm + 4
		//0xfc	modrm + 1
		//0xfb  modrm + 4 or modrm + 1 or 2
		//0xfa  modrm + 1 or 2
		//0xf5	66 �̉e�����󂯂� 5�o�C�g���̖���
		//0xe5	66 �̉e�����󂯂� 5�o�C�g���̖���  64bit��48������� 64bit�ɂȂ閽��
		static unsigned char codeTable[] = {
//		0		1		2		3		4		5		6		7		8		9		a		b		c		d		e		f
/*0*/	0xff,	0xff,	0xff,	0xff,	0x02,	0xf5,	0x01,	0x01,	0xff,	0xff,	0xff,	0xff,	0x02,	0xf5,	0x01,	0x00,//0
/*1*/	0xff,	0xff,	0xff,	0xff,	0x02,	0xf5,	0x01,	0x01,	0xff,	0xff,	0xff,	0xff,	0x02,	0xf5,	0x01,	0x01,//1
/*2*/	0xff,	0xff,	0xff,	0xff,	0x02,	0xf5,	0x01,	0x01,	0xff,	0xff,	0xff,	0xff,	0x02,	0xf5,	0x01,	0x01,//2
/*3*/	0xff,	0xff,	0xff,	0xff,	0x02,	0xf5,	0x01,	0x01,	0xff,	0xff,	0xff,	0xff,	0x02,	0xf5,	0x01,	0x01,//3
/*4*/	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,//4
/*5*/	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,//5
/*6*/	0x01,	0x01,	0xff,	0xff,	0x00,	0x00,	0x00,	0x00,	0x05,	0xfd,	0x02,	0xfc,	0x01,	0x01,	0x00,	0x00,//6
/*7*/	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,//7
/*8*/	0xfc,	0xfd,	0xfd,	0xfc,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,//8
/*9*/	0x01,	0x01,	0x05,	0x05,	0x01,	0x05,	0x05,	0x05,	0x01,	0x01,	0x00,	0x01,	0x01,	0x01,	0x01,	0x01,//9
/*a*/	0x05,	0x05,	0x05,	0x05,	0x01,	0x01,	0x01,	0x01,	0x02,	0xf5,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,//a
/*b*/	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0xe5,	0xe5,	0xe5,	0xe5,	0xe5,	0xe5,	0xe5,	0xe5,//b
/*c*/	0xfc,	0xfc,	0x03,	0x01,	0xff,	0xff,	0xfc,	0xfd,	0x01,	0x01,	0x01,	0x03,	0x01,	0x02,	0x01,	0x01,//c
/*d*/	0xff,	0xff,	0xff,	0xff,	0x02,	0x02,	0x01,	0x01,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,//d
/*e*/	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x02,	0x05,	0x05,	0xf5,	0x02,	0xff,	0xff,	0xff,	0xff,//e
/*f*/	0x01,	0x00,	0x01,	0x00,	0x01,	0x00,	0xfa,	0xfb,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0xff,	0xff //f
		};

		//f0����n�܂� 2�o�C�g����
		static unsigned char codeTableF0[] = {
//		0		1		2		3		4		5		6		7		8		9		a		b		c		d		e		f
/*0*/	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,//0
/*1*/	0xff,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0x00,	0xff,//1
/*2*/	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0xff,	0xff,	0x00,	0xff,	0xff,	0xff,	0xff,//2
/*3*/	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,//3
/*4*/	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,//4
/*5*/	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,//5
/*6*/	0xff,	0xff,	0xff,	0xff,	0x00,	0x00,	0x00,	0xff,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0xff,//6
/*7*/	0xfc,	0xfc,	0xfc,	0xfc,	0xff,	0xff,	0xff,	0x01,	0xff,	0xff,	0x00,	0x00,	0x00,	0x00,	0xff,	0xff,//7
/*8*/	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,	0x05,//8
/*9*/	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0x02,	0x02,	0x02,	0x02,	0xff,	0xff,	0xff,	0xff,//9
/*a*/	0x00,	0x00,	0x01,	0xff,	0xfc,	0xff,	0x00,	0x00,	0x00,	0x00,	0x00,	0xff,	0xfc,	0xff,	0xff,	0xff,//a
/*b*/	0x02,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0x00,	0x00,	0xfc,	0xff,	0xff,	0xff,	0xff,	0xff,//b
/*c*/	0x00,	0xff,	0xfc,	0x00,	0x00,	0x00,	0x00,	0xff,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,//c
/*d*/	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,//d
/*e*/	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,//e
/*f*/	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0xff,	0x00,	0x00 //f
		};

		unsigned char len = codeTable[*code];
		unsigned char ex = 0;
		unsigned char registersize = 0;
		unsigned char registersize64 = 0;

		if (cputype == SEXYHOOK_CPU_ARCHITECTURE_X64)
		{//64bit�Ή� ����1
			if (*code == 0xf2 || *code == 0xf3)
			{
				code =	code + 1;
				ex += 1;

				len = codeTable[*code];
			}
		}

		//prefix �Ղ�Ղ悾�ƃ_�C�A�L���[�g�݂�����
		if (*code >= 0x64 && *code <= 0x67 )
		{
			registersize = *code;

			code =	code + 1;
			ex += 1;
			len = codeTable[*code];
		}

		if (cputype == SEXYHOOK_CPU_ARCHITECTURE_X64)
		{//64bit�Ή� ����2
			if ( registersize == 0x66 && *code == 0x2e)
			{//66 2e 0f 1f 84 00 00 00 00 00  ����not �̂悤�ɁA 66 2e �Ɠ���Ƃ�������炵���B
				code =	code + 1;
				ex += 1;
			}

			if (*code >= 0x40 && *code <= 0x4f )
			{
				registersize64 = *code;

				code =	code + 1;
				ex += 1;
				len = codeTable[*code];
			}
		}

		//lock prefix
		if (*code == 0xf0)
		{
			code = code + 1;
			ex += 1;
			len = codeTable[*code];
		}

		//9b �͓�w 
		if (*code == 0x9b)
		{
			if (*(code+1) == 0xdd)
			{// 9b dd b4 24 50 02 00 00  fsave  0x250(%rsp)
				return ex + 2 + 2 + 4;
			}
			else if (*(code+1) == 0x97)
			{//9b 97 66 00 ???
				return ex + 1 + 3;
			}
			else if (*(code+1) == 0x3f)
			{//9b 3f 08 ???
				return ex + 1 + 2;
			}
			else if (*(code+1) == 0xc4)
			{//9b c4 20   ???
				return ex + 1 + 2;
			}
			else
			{
				return ex + 1;
			}
		}

		//2�o�C�g�̒����I�y�R�[�h�̏���
		if (*code == 0x0f)
		{
			code = code + 1;
			ex += 1;
			len = codeTableF0[*code];
		}

		//repne / reps �� ���̃R�[�h�����Ȃ��Ƃ킩��Ȃ�
		if (*code == 0xf2 || *code == 0xf3)
		{
			if ( (*(code + 1) & 0xf0)  == 0xa0)
			{
				return ex + 2;
			}
			return ex + 1;
		}

		if (len == 0)
		{
		}
		else if ( len <= 0x10)
		{
			return len + ex;
		}
		else if ( len == 0xf5 || len == 0xe5)
		{
			if (registersize == 0x66)
			{//66 bf �Ɨ���� word �P�ʂŃA�N�Z�X����炵��
				return 3 + ex;
			}
			else
			{
				if (len == 0xe5 && (registersize64 >= 0x48 && registersize64 <= 0x4f) )
				{//64bit�g���� 8�o�C�g�ŃA�N�Z�X�ł��閽��
					return 9 + ex;
				}
				return 5 + ex;
			}
		}
		else
		{
			unsigned char mod = 0;
			unsigned char reg = 0;
			unsigned char rw =  0;
			int modlen = modrmLen( *(code + 1) ,*(code + 2) ,&mod,&reg,&rw);

			if ( len == 0xff)
			{
				return 1 + 1 + modlen + ex;
			}
			if ( len == 0xfd)
			{//c7 85 00 fc ff ff 00 00 00 00
			 //mov         dword ptr [ebp-400h],0
				if (registersize == 0x66)
				{//66 c7 �Ɨ���� word �P�ʂŃA�N�Z�X����炵��
					return 1 + 1 + modlen + 2 + ex;
				}
				else
				{
					return 1 + 1 + modlen + 4 + ex;
				}
			}
			if ( len == 0xfc)
			{//c1 f8 0a
			 //sar	eax,0x0a
				return 1 + 1 + modlen + 1 + ex;
			}
			if ( len == 0xfb)
			{//modrm �ɂ���Ē������ς��
				if (reg == 0)
				{
					if (registersize == 0x66)
					{
						return 1 + 1 + 2 + modlen + ex;
					}
					else
					{
						return 1 + 1 + 4 + modlen + ex;
					}
				}
				else if (reg >= 2) return 1 + 1 + modlen + ex;
				else return 1 + 1 + ex;
			}
			if ( len == 0xfa)
			{//modrm �ɂ���Ē������ς��
				if (reg == 0) return 1 + 1 + 1 + modlen + ex;
				else if (reg >= 2) return 1 + 1 + modlen + ex;
				else return 1 + 1 + ex;
			}
		}

		SEXYHOOK_BREAKPOINT;
		return 0;
	}

	static int modrmLen(unsigned char modrm,unsigned char sib,unsigned char *mod,unsigned char *reg,unsigned char *rw) 
	{
		*mod = (modrm & 0xc0) >> 6;
		*reg = (modrm & 0x38) >> 3;
		*rw =  (modrm & 0x07);

		switch (*mod)
		{
		case 0:
			switch(*rw)
			{
			case 0:		return 0;//eax
			case 1:		return 0;//ecx
			case 2:		return 0;//edx
			case 3:		return 0;//ebx
			case 4:
				{//SIB    sib��base�r�b�g�ɂ���Ē������Ⴄ
					unsigned char base = (sib & 0x07);
					if (base == 5)	return 1 + 4;
					else			return 1;
				}
			case 5:		return 4;//disp32
			case 6:		return 0;//esi
			case 7:		return 0;//edi
			}
			break;
		case 1:
			switch(*rw)
			{
			case 0:		return 1;//eax + disp8
			case 1:		return 1;//ecx + disp8
			case 2:		return 1;//edx + disp8
			case 3:		return 1;//ebx + disp8
			case 4:		return 1 + 1;//SIB
			case 5:		return 1;//ebp + disp8
			case 6:		return 1;//esi + disp8
			case 7:		return 1;//edi + disp8
			}
		case 2:
			switch(*rw)
			{
			case 0:		return 4;//eax + disp32
			case 1:		return 4;//ecx + disp32
			case 2:		return 4;//edx + disp32
			case 3:		return 4;//ebx + disp32
			case 4:		return 1 + 4;//SIB
			case 5:		return 4;//ebp + disp32
			case 6:		return 4;//esi + disp32
			case 7:		return 4;//edi + disp32
			}
		case 3:
			switch(*rw)
			{
			case 0:		return 0;//al/ax/eax/mm0/xmm0
			case 1:		return 0;//cl/cx/ecx/mm1/xmm1
			case 2:		return 0;//dl/dx/edx/mm2/xmm2
			case 3:		return 0;//bl/bx/ebx/mm3/xmm3
			case 4:		return 0;//ah/sp/esp/mm4/xmm4
			case 5:		return 0;//ch/bp/ebp/mm5/xmm5
			case 6:		return 0;//dh/si/esi/mm6/xmm6
			case 7:		return 0;//bh/di/edi/mm7/xmm7
			}
		}
		SEXYHOOK_BREAKPOINT;
		return 0;
	}

};

#endif //____SEXYHOOK____72
