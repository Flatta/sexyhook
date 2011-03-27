//
//SEXYHOOK sample and TEST
//
//by rti
//
//new BSD ���C�Z���X / NYSL���C�Z���X �D���Ɏg���΂��������ȃC�J ^p^
//
#ifdef WIN32
	#include <windows.h>
#endif //WIN32
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sexyhook.h"	//�Z�N�V�[�t�b�N
//#include "sexyhook_addrutil.h"	//�Z�N�V�[�t�b�N ���[�e�B���e�B

//�֐��̃e�X�g
int add(int a,int b)
{
	return a + b;
}

//�N���X�̃e�X�g
class testclass
{
public:
	int add(int a , int b)
	{
		return a + b;
	}
};


class testclass2
{
public:
	bool check()
	{
		if (this->checkCore(1))
		{
			return true;
		}
		else
		{
			//�������e�X�g�ł��Ȃ��B
			return false;
		}
	}
	bool checkCore(int a )
	{
		return a ? true : false;
	}

	//2000�N�ȏォ�H
	bool isOver2000year()
	{
		return time(NULL) >= 946652400;	//2000-01-01 00:00:00
	}

	static void test()
	{
		{
			printf("\r\n�N���X���\�b�h�̃t�b�N����2\r\n");
			//����ŏ��������Ă��܂��΂������vw
			SEXYHOOK_BEGIN(bool,SEXYHOOK_CLASS,&testclass2::checkCore,(int a))
			{
				return false;
			}
			SEXYHOOK_END();

			testclass2 cls;
			SEXYHOOK_ASSERT( !cls.check() );
		}
		//time() �𖄂ߍ���ł���v���O�������ق点�����
		{
			printf("\r\ntime�֐��̃t�b�N����2\r\n");
			//����ŏ��������Ă��܂��΂������vw
			SEXYHOOK_BEGIN(time_t,SEXYHOOK_CDECL,&time,(time_t * a))
			{
				return 915116400;//1999-01-01 00:00:00
			}
			SEXYHOOK_END();

			//�e�X�g
			testclass2 cls;
			bool r = cls.isOver2000year();
			SEXYHOOK_ASSERT( r == false );	//1999�N�ł�.
		}
		{
			printf("\r\ntime�֐��̃t�b�N���I����Ă��邱��\r\n");
			//�X�R�[�v�𔲂����̂�time()�֐��͂����㏑������Ȃ��B
			testclass2 cls;
			bool r = cls.isOver2000year();
			SEXYHOOK_ASSERT( r == true );	//2000�N�ȏ�ł�.
		}

	}
};

//���z/�������z���\�b�h�̃e�X�g
class Parent 
{
	int Dummy;
public:
	virtual int f() 
	{
		return 1;
	}
	virtual int g() =0;
};

class Child : public Parent 
{
	int Dummy2;
public:
	int aaa()
	{
		return 0;
	}
	virtual int f() 
	{
		return 2;
	}
	virtual int g() 
	{
		return 3;
	}
};

//�e���v���[�g�N���X�̃e�X�g
template<typename _T> class TempTest
{
public:
	int add(_T a,_T b)
	{
		return a + b;
	}
};

//�I�y���[�^�I�[�o�[���[�h�̃e�X�g
class OpClass
{
	int A;
public:
	OpClass(int inA) : A(inA)
	{
	}
	int getA() const
	{
		return this->A;
	}

	OpClass operator+( const OpClass& x )
	{
		OpClass z( this->A + x.A );
		return z;
	}

};

//�O���[�o���ȃI�y���[�^�[�I�[�o�[���[�h�ɂ́A�܂����Ή��ł��B���߂�Ȃ����B
bool operator==(const OpClass& x, const OpClass& y) 
{
	return x.getA() == y.getA();
}

//�I�[�o�[���[�h�̃e�X�g
int uadd(int a,int b)
{
	return a + b;
}
char uadd(char a,char b)
{
	return a + b;
}


//�e���v���[�g�֐��̃e�X�g
//�|���Z
template<typename T> T mul( const T& a,const T& b ){
       return a * b;
}

//���܂� dump����֐�
static void hexDump(void* p,int size)
{
	printf("\r\nDUMP %p:",p);

	int i = 0;
	for( ; i < size ; i ++)
	{
		printf(" %02X",
			0x000000ff &  (unsigned int)*(((char*)p)+i));
		if (i % 16 == 15)
		{
			printf("\r\n");
		}
	}
	printf("\r\n");
}

#ifdef __GNUC__
	//__stdcall�ȃN���X���\�b�h.
	class stdcallclass
	{
	public:
		int __attribute__ ((stdcall)) add(int a , int b)
		{
			return a + b;
		}
	};
	//fastcall�̃e�X�g
	int __attribute__ ((regparm(3))) fast_add(int a,int b)
	{
		return a + b;
	}

	//__fastcall�ȃN���X���\�b�h.
	class fastcallclass
	{
	public:
		int __attribute__ ((regparm(3))) add(int a , int b)
		{
			return a + b;
		}
	};
#else
	//__stdcall�ȃN���X���\�b�h.
	class stdcallclass
	{
	public:
		int __stdcall add(int a , int b)
		{
			return a + b;
		}
	};
	//fastcall�̃e�X�g
	int __fastcall fast_add(int a,int b)
	{
		return a + b;
	}

	//__fastcall�ȃN���X���\�b�h.
	class fastcallclass
	{
	public:
		int __fastcall add(int a , int b)
		{
			return a + b;
		}
	};
#endif



class classMethodCallTest
{
private:
public:
	int Secret;
	classMethodCallTest()
	{
		this->Secret = 0;
	}
	classMethodCallTest(int a)
	{
		this->Secret = a;
	}
	int Add(int a) const
	{
		return a + this->Secret;
	}
	int Sub(int a) const
	{
		return a - this->Secret;
	}
	int setA(int a)
	{
		this->Secret = a;
	}
};

class constdoumei
{
public:
	int add(int a, int b) const
	{
		return a + b + 10;
	}
	int add(int a, int b) 
	{
		return a + b + 20;
	}
};


//private
class private_testclass
{
private:
	int private_add(int a , int b)
	{
		return a + b;
	}
public:
	int public_add(int a , int b)
	{
		return private_add(a,b);
	}
};



int main()
{
	//�t�b�N���Ăяo���Ȃǂ̃e�X�g
	{
		classMethodCallTest c(2);
		{
			int r = c.Add(10);		//10 + 2 = 12
			SEXYHOOK_ASSERT(r == 12);
		}
		//�����̃t�b�N ����2 �����̃`�F�b�N
		{ 
			SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&classMethodCallTest::Add,(int a))
			{
				SEXYHOOK_ASSERT(a == 10);
				return 20;
			}
			SEXYHOOK_END();

			int r = c.Add(10);
			SEXYHOOK_ASSERT(r == 20);
		}
		//�����̃t�b�N
		{
			SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&classMethodCallTest::Add,(int a))
			{
				return 10;
			}
			SEXYHOOK_END();

			int r = c.Add(10);
			SEXYHOOK_ASSERT(r == 10);
		}
		//�ʂ̃��\�b�h�̌Ăяo��
		{
			SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&classMethodCallTest::Add,(int a))
			{
				return a * SEXYHOOK_THIS(classMethodCallTest*)->Sub(5);
			}
			SEXYHOOK_END();

			int r = c.Add(10);		//10 * (5 - 2) = 30
			SEXYHOOK_ASSERT(r == 30);
		}
		//�ʂ̃����o�ϐ��̌Ăяo��(������ public ����)
		{
			SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&classMethodCallTest::Add,(int a))
			{
				return a * SEXYHOOK_THIS(classMethodCallTest*)->Secret;
			}
			SEXYHOOK_END();

			int r = c.Add(10);		//10 * 2 = 20
			SEXYHOOK_ASSERT(r == 20);
		}

		//�������g�̍ČĂяo�� ����1
		{
			SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&classMethodCallTest::Add,(int a))
			{
				{
					//�ꎞ�I�Ƀt�b�N������
					SEXYHOOK_UNHOOK();
					//���̊֐����Ăяo��
					return SEXYHOOK_THIS(classMethodCallTest*)->Add(a);
				}
			}
			SEXYHOOK_END();

			int r = c.Add(10);		//10 + 2 = 12
			SEXYHOOK_ASSERT(r == 12);
		}
		//�������g�̍ČĂяo�� ����2
		{
			SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&classMethodCallTest::Add,(int a))
			{
				{
					//�ꎞ�I�Ƀt�b�N������
					SEXYHOOK_UNHOOK();
					//���̊֐����Ăяo��
					return CallOrignalFunction(a);
				}
			}
			SEXYHOOK_END();

			int r = c.Add(10);		//10 + 2 = 12
			SEXYHOOK_ASSERT(r == 12);
		}
	}

	//���z���\�b�h
	{
		printf("\r\n���z���\�b�h�̃e�X�g\r\n");
		int cf,cg,pf,pg;
		Child child;

		printf("�܂��t�b�N���Ă��Ȃ�\r\n");
		cf = child.f();
		cg = child.g();
		pf = ((Parent*)&child)->f();
		pg = ((Parent*)&child)->g();
		printf("child.f : %d\r\n",cf);
		printf("child.g : %d\r\n",cg);
		printf("((Parent*)&child)->f : %d\r\n",pf);
		printf("((Parent*)&child)->g : %d\r\n",pg);

		{
			//��������t�b�N
			SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&Child::g,())
			{
				return 103;	//Child::g
			}
			SEXYHOOK_END(&child);

			printf("Child.g���t�b�N\r\n");
			cf = child.f();
			cg = child.g();
			pf = ((Parent*)&child)->f();
			pg = ((Parent*)&child)->g();
			printf("child.f : %d\r\n",cf);
			printf("child.g : %d\r\n",cg);
			printf("((Parent*)&child)->f : %d\r\n",pf);
			printf("((Parent*)&child)->g : %d\r\n",pg);
			SEXYHOOK_ASSERT(cg == 103);
			SEXYHOOK_ASSERT(pg == 103);
		}
		{
			//��������t�b�N
			SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&Child::f,())
			{
				return 102;	//Child::f
			}
			SEXYHOOK_END(&child);

			printf("Child.f���t�b�N\r\n");
			cf = child.f();
			cg = child.g();
			pf = ((Parent*)&child)->f();
			pg = ((Parent*)&child)->g();
			printf("child.f : %d\r\n",cf);
			printf("child.g : %d\r\n",cg);
			printf("((Parent*)&child)->f : %d\r\n",pf);
			printf("((Parent*)&child)->g : %d\r\n",pg);
			SEXYHOOK_ASSERT(cf == 102);
			SEXYHOOK_ASSERT(pf == 102);
		}
	}


	//�e���v���[�g�֐��̃e�X�g
	{

		//����Z�ɕύX
		SEXYHOOK_BEGIN( int, SEXYHOOK_CDECL, &mul<int>, (const int& a , const int& b))
		{
			return a  / b;
		}
		SEXYHOOK_END();

		int r1 = mul(9,3);			//�������̂ݏ���������
		long r2 = mul<long>(9,3);

		printf("\r\n�e���v���[�g�֐��̃e�X�g\r\n");
		printf("r1:%d // ��������������Z��\r\n", r1);
		printf("r2:%d\r\n",(int) r2);
		SEXYHOOK_ASSERT(r1 == 3);
		SEXYHOOK_ASSERT(r2 == 27);
	}


	//�O���[�o���ȃI�y���[�^�[�I�[�o�[���[�h
	{
		OpClass a(10);
		OpClass b(10);

		bool br = (a == b);

		SEXYHOOK_BEGIN(bool,SEXYHOOK_CDECL,&operator==,(const OpClass& x, const OpClass& y))
		{
			return false;
		}
		SEXYHOOK_END();

		//���������ē������Ȃ�����.
		bool br2 = (a == b);

		printf("\r\n�O���[�o���ȃI�y���[�^�[�I�[�o�[���[�h�̃e�X�g\r\n");
		printf("�t�b�N�O %d //�������̂�true \r\n",(int)br);
		printf("�t�b�N�� %d //���false \r\n",(int)br2);

		SEXYHOOK_ASSERT(br == true);
		SEXYHOOK_ASSERT(br2 != true);
	}

	//�I�[�o�[���[�h(�ʌ^��`)�̃e�X�g
	{
		SEXYHOOK_BEGIN(int,SEXYHOOK_CDECL,&uadd,(int a,int b))
		{
			return a - b;
		}
		SEXYHOOK_END();

		int r = uadd(1,2);
		printf("\r\n�I�[�o�[���[�h(�ʌ^��`)�̃e�X�g\r\n");
		printf("r1:%d //�����Z�������Z�� \r\n",r);
		SEXYHOOK_ASSERT(r == -1);
	}

	//���Z�q�I�[�o�[���[�h�̃e�X�g
	{
		OpClass a(10);
		OpClass b(20);
		//�t�b�N�֐����`����O������t�b�N����Ȃ�
		OpClass c = a + b;

		//��������t�b�N
		SEXYHOOK_BEGIN(OpClass,SEXYHOOK_CLASS,&OpClass::operator +,(const OpClass& x))
		{
//			OpClass z( this->A - x.A );	//this�͎g���Ȃ�...
//			OpClass z( 1000 - x.A );	//�������A�N���X�̒��ł͂Ȃ��̂�...������firiend��(ry
			OpClass z( 1000 );
			return z;
		}
		SEXYHOOK_END();

		//����̓t�b�N�����.
		OpClass d = a + b;
		printf("\r\n���Z�q�I�[�o�[���[�h�̃e�X�g\r\n");
		printf("OpClass(C) %d //�Œ�l \r\n" , c.getA());
		printf("OpClass(D) %d\r\n" , d.getA());
		SEXYHOOK_ASSERT(c.getA() == 30);
		SEXYHOOK_ASSERT(d.getA() == 1000);	//�Œ�l
	}
	//�e���v���[�g�N���X�̃e�X�g
	{
		int r;

		TempTest<int> t;
		//��������t�b�N
		SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&TempTest<int>::add,(int a,int b))
		{
			return a - b;
		}
		SEXYHOOK_END();

		r = t.add(1,2);
		printf("\r\n�e���v���[�g�N���X�̃e�X�g\r\n");
		printf("TempTest<int> : %d //�����Z�������Z��\r\n",r);
		SEXYHOOK_ASSERT(r == -1);
	}
	//�N���X���\�b�h�̃e�X�g
	{
		//�N���X���\�b�h�̏ꍇ�� SEXYHOOK_CLASS_HOOK_2_BEGIN ���g���Ă��������B 
		//2�͈����̐��ł��B
		SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&testclass::add,(int a,int b))
		{
			return a - b;	//�����Z�������Z�ɏ㏑������.
		}
		SEXYHOOK_END();

		testclass myclass;
		int r = myclass.add(10,20);	//�����Z�������Z�ɏ㏑������.

		printf("\r\n�N���X���\�b�h�̃e�X�g\r\n");
		printf("r1 : %d\r\n",r);
		SEXYHOOK_ASSERT(r == -10);
	}

#ifdef _WINDOWS_
	//API�t�b�N�̃e�X�g
	{
		//HeapCreate API �����s�����Ă݂�B
		//������������Awin95�n���Ƃ��߂����A�A�A����Ȃ̒N���g���Ă��Ȃ����炢�����B
		SEXYHOOK_BEGIN(int,SEXYHOOK_STDCALL,&HeapCreate,(HANDLE a1,DWORD a2,SIZE_T a3))
		{
			return NULL;
		}
		SEXYHOOK_END();

		//�t�b�N���� 
		HANDLE h = HeapCreate(0,0,100);
		printf("\r\nAPI�t�b�N�̃e�X�g\r\n");
		printf("HeapCreate : %p\r\n" , h);
		SEXYHOOK_ASSERT(h == NULL);
	}
	//API�t�b�N�̃e�X�g ����2
	{
		
		//HeapCreate API �����s�����Ă݂�B
		//������������Awin95�n���Ƃ��߂����A�A�A����Ȃ̒N���g���Ă��Ȃ����炢�����B
		SEXYHOOK_BEGIN(int,SEXYHOOK_STDCALL,SEXYHOOK_DYNAMICLOAD
					("kernel32.dll","HeapCreate"),(HANDLE a1,DWORD a2,SIZE_T a3))
		{
			return NULL;
		}
		SEXYHOOK_END();

		//�t�b�N���� 
		HANDLE h = HeapCreate(0,0,100);
		printf("\r\nAPI�t�b�N�̃e�X�g\r\n");
		printf("HeapCreate : %p\r\n" , h);
		SEXYHOOK_ASSERT(h == NULL);
	}

	//�_�C�i�~�b�N�����N�̃t�b�N
	{
		printf("�_�C�i�~�b�N�����N �̃e�X�g\r\n");

		SEXYHOOK_BEGIN(int,SEXYHOOK_STDCALL,SEXYHOOK_DYNAMICLOAD("dlltest.dll","DllAdd"),(int a , int b))
		{
			return a - b;
		}
		SEXYHOOK_END();


		HMODULE mod = LoadLibraryA("dlltest.dll");
		SEXYHOOK_ASSERT(mod != NULL);
		//export
		PROC orignalProc = GetProcAddress(mod , "DllAdd" );
		SEXYHOOK_ASSERT(orignalProc != NULL);

		int r = ((int (__stdcall *) (int,int))orignalProc)(1,2);
		printf("dlltest.dll : DllAdd : %d\r\n" , r);
		SEXYHOOK_ASSERT(r == -1);

		FreeLibrary(mod);
	}

	//�_�C�i�~�b�N�����N�̒��� windows api�̃t�b�N
	{
		printf("�_�C�i�~�b�N�����N�̒��� windows api�̃t�b�N�̃e�X�g\r\n");

		//�ӂ[�ɂ��̂܂�API��
		SEXYHOOK_BEGIN(int,SEXYHOOK_STDCALL, MessageBoxA ,
					(HWND hWnd, LPCSTR lpText , LPCSTR lpCaption ,  UINT uType))
		{
			printf("lpText:%s , lpCaption:%s\r\n" , lpText,lpCaption);

			return -99;
		}
		SEXYHOOK_END();

		HMODULE mod = LoadLibraryA("dlltest.dll");
		SEXYHOOK_ASSERT(mod != NULL);
		//export
		PROC orignalProc = GetProcAddress(mod , "DllMessageBoxAPI" );
		SEXYHOOK_ASSERT(orignalProc != NULL);

		//�t�b�N���� 
		int r = ((int (__stdcall *) (int,int))orignalProc)(1,2);
		printf("dlltest.dll : DllMessageBoxAPI : %d\r\n" , r);
		SEXYHOOK_ASSERT(r == -99);

		FreeLibrary(mod);
	}
	//�_�C�i�~�b�N�����N�̒��ł���Ƀ_�C�i�~�b�N�����N�̃t�b�N
	{
		printf("�_�C�i�~�b�N�����N�̒��ł���Ƀ_�C�i�~�b�N�����N�̃e�X�g\r\n");
		//dlltest.dll �� DllMul �́A dlltest2.dll �� Dll2Mul ���Ăяo���Ċ|���Z���s���Č��ʂ�Ԃ�.

		//dlltest"2".dll �� Dll2Mul ���t�b�N����.
		SEXYHOOK_BEGIN(int,SEXYHOOK_STDCALL,SEXYHOOK_DYNAMICLOAD("dlltest2.dll","Dll2Mul"),(int a , int b))
		{
			return a / b;
		}
		SEXYHOOK_END();

		HMODULE mod = LoadLibraryA("dlltest.dll");
		SEXYHOOK_ASSERT(mod != NULL);
		//export
		PROC orignalProc = GetProcAddress(mod , "DllMul" );	//dlltest.dll �� DllMul �́A dlltest2.dll �� Dll2Mul ���Ăяo��.
		SEXYHOOK_ASSERT(orignalProc != NULL);

		int r = ((int (__stdcall *) (int,int))orignalProc)(4,2);	//4 * 2 �ł͂Ȃ��A 4 / 2�����s
		printf("dlltest.dll : DllMul : %d\r\n" , r);
		SEXYHOOK_ASSERT(r == 2);	// 4 / 2 = 2

		FreeLibrary(mod);
	}
#endif //_WINDOWS_

	//�֐��̃t�b�N�̃e�X�g
	{
		//add�֐������������Ĉ����Z�ɂ���B
		SEXYHOOK_BEGIN(int,SEXYHOOK_CDECL,&add,(int a,int b))
		{
			return a - b;
		}
		SEXYHOOK_END();

		int cc = add(10,20);
		printf("\r\n�֐��̃t�b�N�̃e�X�g\r\n");
		printf("cc: %d\r\n",cc);
		SEXYHOOK_ASSERT(cc == -10);
	}
	//C�֐�strstr�̃t�b�N
	{
		//����ŏ��������Ă��܂��΂������vw
		SEXYHOOK_BEGIN(const char *,SEXYHOOK_CDECL,&strstr,(const char * p,const char *p2))
		{
			return NULL;
		}
		SEXYHOOK_END();

		const char * str1 = "hello";
		const char * str2 = "hel";
		const char * p2 = strstr(str1,str2);	//strstr("hello","hel") ���� gcc �� -O0�Ȃ̂ɍœK������炵��.
		printf("\r\nC�֐�strstr�̃t�b�N\r\n");
		printf("strstr: %p //�q�b�g�������� NULL \r\n",p2);
		SEXYHOOK_ASSERT(p2 == NULL);
	}
	//�N���X���\�b�h�ł̃e�X�g��
	{
		testclass2::test();
	}

	//__stdcall�ȃN���X���\�b�h�̃e�X�g
	{
		SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS_STDCALL,&stdcallclass::add,(int a,int b))
		{
			return a - b;
		}
		SEXYHOOK_END();

		printf("\r\n__stdcall�ȃN���X���\�b�h�̃t�b�N\r\n");
		stdcallclass c;
		int r = c.add(10,20);
		SEXYHOOK_ASSERT(r == -10);
	}

	//__fastcall�̃e�X�g
	{
		SEXYHOOK_BEGIN(int,SEXYHOOK_FASTCALL,&fast_add,(int a,int b))
		{
			return a - b;
		}
		SEXYHOOK_END();

		printf("\r\n__fastcall�̃t�b�N\r\n");
		int r = fast_add(10,20);
		SEXYHOOK_ASSERT(r == -10);
	}
	

	//__fastcall class method �̃e�X�g
	{
		SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS_FASTCALL,&fastcallclass::add,(int a,int b))
		{
			return a - b;
		}
		SEXYHOOK_END();

		printf("\r\n__fastcall class method�̃t�b�N\r\n");
		fastcallclass c;
		int r = c.add(10,20);
		SEXYHOOK_ASSERT(r == -10);
	}
#ifndef __GNUC__
	//const����
	//gcc �œ����Ȃ��A�A�A�A
	{
		SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,&constdoumei::add,(int a,int b))
		{
			return a - b;
		}
		SEXYHOOK_END();

		printf("\r\nconst�����̃t�b�N const�����Ȃ���\r\n");
		constdoumei c;
		int r = c.add(10,20);		//�t�b�N
		SEXYHOOK_ASSERT(r == -10);

		const constdoumei c2;
		r = c2.add(10,20);
		SEXYHOOK_ASSERT(r == 30 + 10);
	}
	{
		SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,SEXYHOOK_AUTOCAST_CONST(&constdoumei::add),(int a,int b))
		{
			return a - b;
		}
		SEXYHOOK_END();

		printf("\r\nconst�����̃t�b�N const������\r\n");

		constdoumei c;
		int r = c.add(10,20);
		SEXYHOOK_ASSERT(r == 30 + 20);

		const constdoumei c2;
		r = c2.add(10,20);	//�t�b�N
		SEXYHOOK_ASSERT(r == -10);
	}
#endif	//__GNUC__

/*
	//private ���\�b�h�̃A�h���X���Z�o���ăt�b�N. 
	//���̂Ƃ��� VC6 + PlatformSDK�ł������삵�Ȃ��A�A�Ȃ�ŁH
	{
		printf("\r\nprivate ���\�b�h�̃A�h���X���Z�o���ăt�b�N\r\n");


		private_testclass c;
		//�����ł͂܂��t�b�N���Ă��Ȃ�
		int r = c.public_add(10,20);
		SEXYHOOK_ASSERT(r == 30);

		//private ���\�b�h�̃A�h���X���Z�o���ăt�b�N.
		SEXYHOOK_BEGIN(int,SEXYHOOK_CLASS,SEXYHOOKAddrUtil::strstr_addr("private_testclass::private_add"),(int a,int b))
		{
			return a - b;
		}
		SEXYHOOK_END();	

		//�t�b�N�ł������Ƃ��m�F!
		r = c.public_add(10,20);
		SEXYHOOK_ASSERT(r == -10);
	}
*/
	puts("ok");
	return 0;
}
