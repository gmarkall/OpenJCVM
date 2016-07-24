/**
 * Copyright 2008 - present Oliver Lusing / Louis Liu
 *
 * This file is part of OpenJCVM; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation version 2.
 *
 * You should have received a copy of the GNU General Public License along with
 * OpenJCVM; see the file COPYING. If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef vm_h_
#define vm_h_
#include "base.h"
#include "javaclass.h"

class AbstractApplet;

#define JSTACK_BOTTOM 256
#define MAX_LOCALS 256
#define MAX_ARRAY 256

#define MAX_CLASSES 256

static const int T_BOOLEAN = 10;
static const int T_BYTE = 11;
static const int T_SHORT = 12;
static const int T_INT = 13;

class VirtualMachine
{
public:
	u4 run();
	static s2 jstack[JSTACK_BOTTOM];
	static int jstacktop;
	static s2 jlocals[MAX_LOCALS];

	//Use a new structure for int commands.
	static s4 jstackint[JSTACK_BOTTOM];
	static int jstacktopint;
	static s4 jlocalsint[MAX_LOCALS];

	static bool push(s2 value);
	static s2 pop();

	static bool pushint(s4 value);
	static s4 popint();

	static u1* getStaticFieldAddress(u2 sIndex,AbstractApplet* pCA);

	static u4 runStatic(u1* pByteCode, int* pPC,AbstractApplet* pCA,int maxstack,int paras,int maxlocals);
	VirtualMachine(void);
	virtual ~VirtualMachine(void);
private:
	static s1* bytearrays[MAX_ARRAY];
	static s2* shortarrays[MAX_ARRAY];
	static s4* intarrays[MAX_ARRAY];
	static u2* objarrays[MAX_ARRAY];

	static int baCount;
	static int saCount;
	static int iaCount;
	static int aaCount;

	static JavaClass* javaClasses[MAX_CLASSES];
	static int jcCount;

	static void vm_sconst(short s);
	static void vm_sstore(u1 index);
	static void vm_sload(u1 index);
	static void vm_sadd();
	static void vm_ssub();
	static void vm_smul();
	static void vm_sdiv();
	static void vm_sinc(u1 index,u1 bconst);
	static void vm_bspush(s1 b);
	static void vm_sspush(short s);
	static void vm_s2b();

	static void vm_newarray(int arrayType);
	static void vm_anewarray(u2 sIndex, AbstractApplet* pCA);
	static void vm_astore(u1 index);
	static void vm_aload(u1 index);
	static void vm_sastore();
	static void vm_saload();
	static void vm_aconst_null();
	static void vm_aastore();

	static void vm_dup();
	static void vm_dup2();
	static void vm_dup_x();

	static void vm_goto(s1 bValue,int* pPC);
	static void vm_ifscmpge(s1 bValue,int* pPC);
	static void vm_ifscmplt(s1 bValue,int* pPC);
	static void vm_ifne(s1 bValue,int* pPC);
	static void vm_ifeq(s1 bValue,int* pPC);

	static void vm_getstatic_s(u2 sIndex, AbstractApplet* pCA);
	static void vm_putstatic_s(u2 sIndex,AbstractApplet* pCA);

	static void vm_new(u2 index, AbstractApplet* pCA);
	static void vm_invokespecial(u2 index,AbstractApplet* pCA);
	static void vm_invokevirtual(u2 index,AbstractApplet* pCA);
	static void vm_invokestatic(u2 index,AbstractApplet* pCA);
	static void vm_putfield_s(u1 index,AbstractApplet* pCA);
	static void vm_getfield_s_this(u1 index,AbstractApplet* pCA);
	static void vm_getstatic_a(u2 index,AbstractApplet* pCA);

	static void vm_instanceof(u1 aType, u2 sIndex,AbstractApplet* pCA);

	static void vm_iconst(int iValue);
	static void vm_istore(u1 index);
	static void vm_iload(u1 index);
	static void vm_iadd();
	static void vm_isub();
	static void vm_imul();
	static void vm_idiv();
	static void vm_iinc(u1 index,u1 bconst);
	static void vm_sipush(short sValue);
	static void vm_iipush(int iValue);
	static void vm_i2b();
	static void vm_s2i();
	static void vm_i2s();

	static void createClass(u2 sOffset, AbstractApplet* pCA);
	static inline void invokestaticCommon(u2 index,AbstractApplet* pCA);
};

#endif
