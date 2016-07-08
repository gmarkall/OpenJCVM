#include "vm.h"

#include "cardapplet.h"
#include "library.h"

VirtualMachine::VirtualMachine(void)
{
}

VirtualMachine::~VirtualMachine(void)
{
}

//int VirtualMachine::pc = 0;

u4 VirtualMachine::run()
{
	return (u4)0;
}

s2 VirtualMachine::jstack[JSTACK_BOTTOM];
int VirtualMachine::jstacktop = -1;
s2 VirtualMachine::jlocals[MAX_LOCALS];

s4 VirtualMachine::jstackint[JSTACK_BOTTOM];
int VirtualMachine::jstacktopint;
s4 VirtualMachine::jlocalsint[MAX_LOCALS];

s1* VirtualMachine::bytearrays[MAX_ARRAY];
s2* VirtualMachine::shortarrays[MAX_ARRAY];
s4* VirtualMachine::intarrays[MAX_ARRAY];
u2* VirtualMachine::objarrays[MAX_ARRAY];

int VirtualMachine::baCount=-1;
int VirtualMachine::saCount=-1;
int VirtualMachine::iaCount=-1;
int VirtualMachine::aaCount=-1;

JavaClass* VirtualMachine::javaClasses[MAX_CLASSES];

int VirtualMachine::jcCount = -1;

bool VirtualMachine::push(s2 value)
{
	if(jstacktop+1 == JSTACK_BOTTOM)
	{
		return false;
	}
	else
	{
		jstack[++jstacktop]=value;
		return true;
	}
}

s2 VirtualMachine::pop()
{
	if(jstacktop == -1)
	{
		return 0;
	}
	else
	{
		return jstack[jstacktop--];
	}
}

bool VirtualMachine::pushint(s4 value)
{
	if(jstacktopint+1 == JSTACK_BOTTOM)
	{
		return false;
	}
	else
	{
		jstackint[++jstacktopint]=value;
		return true;
	}
}

s4 VirtualMachine::popint()
{
	if(jstacktopint == -1)
	{
		return 0;
	}
	else
	{
		return jstackint[jstacktopint--];
	}
}


u4 VirtualMachine::runStatic(u1* pByteCode, int* pPC, AbstractApplet* pCA,int maxstack,int paras,int maxlocals)
{
#define READU1 (int)readU1(pByteCode,pPC)
#define READU2 (int)readU2(pByteCode,pPC)
#define READU4 (int)readU4(pByteCode,pPC)
#define READS1 readS1(pByteCode,pPC)
#define READS2 (int)readS2(pByteCode,pPC)
#define READS4 (int)readS4(pByteCode,pPC)

#define MAKEINT() makeInt(jlocals[index],jlocals[index+1])
	u1 bytecode = 0xFF;
	u1 bIndex = 0;//Used for sstore,...
	s1 bConst = 0;//Used for sinc,...
	s1 bValue = 0;//Used for bspush,...
	s2 sValue = 0;//Used for sspush,...
	u2 sIndex = 0;//Used for getstatic_<t>
	s4 iValue = 0;//Used for iipush,...
	int nPairs = 0;
	int lowValue = 0;
	int highValue = 0;
	int i = 0;

	for(i=paras;i>0;i--)
	{
		jlocals[i-1] = pop();
	}

	for(;;)
	{
		bytecode= readU1(pByteCode, pPC);
		//pc=*pPC;
		switch(bytecode)
		{
		case 0x0:
			COUT<<"nop"<<ENDL;
			break;
		case 0x1:
			COUT<<"aconst_null"<<ENDL;
			vm_aconst_null();
			break;
		case 0x2:
			COUT<<"sconst_m1"<<ENDL;
			vm_sconst(-1);
			break;
		case 0x3:
			COUT<<"sconst_0"<<ENDL;
			vm_sconst(0);
			break;
		case 0x4:
			COUT<<"sconst_1"<<ENDL;
			vm_sconst(1);
			break;
		case 0x5:
			COUT<<"sconst_2"<<ENDL;
			vm_sconst(2);
			break;
		case 0x6:
			COUT<<"sconst_3"<<ENDL;
			vm_sconst(3);
			break;
		case 0x7:
			COUT<<"sconst_4"<<ENDL;
			vm_sconst(4);
			break;
		case 0x8:
			COUT<<"sconst_5"<<ENDL;
			vm_sconst(5);
			break;
		case 0x9:
			COUT<<"iconst_m1"<<ENDL;
			vm_iconst(-1);
			break;
		case 0xa:
			COUT<<"iconst_0"<<ENDL;
			vm_iconst(0);
			break;
		case 0xb:
			COUT<<"iconst_1"<<ENDL;
			vm_iconst(1);
			break;
		case 0xc:
			COUT<<"iconst_2"<<ENDL;
			vm_iconst(2);
			break;
		case 0xd:
			COUT<<"iconst_3"<<ENDL;
			vm_iconst(3);
			break;
		case 0xe:
			COUT<<"iconst_4"<<ENDL;
			vm_iconst(4);
			break;
		case 0xf:
			COUT<<"iconst_5"<<ENDL;
			vm_iconst(5);
			break;
		case 0x10:
			bValue =READS1;
			COUT<<"bspush "<<(int)bValue<<ENDL;
			vm_bspush(bValue);
			break;
		case 0x11:
			sValue = READS2;
			COUT<<"sspush "<<(int)sValue<<ENDL;
			vm_sspush(sValue);
			break;
		case 0x12:
			COUT<<"bipush "<<READU1<<ENDL;
			break;
		case 0x13:
			sValue = READS2;
			COUT<<"sipush "<<(int)sValue<<ENDL;
			vm_sipush(sValue);
			break;
		case 0x14:
			iValue = READS4;
			COUT<<"iipush "<<iValue<<ENDL;
			vm_iipush(iValue);
			break;
		case 0x15:
			bIndex = READU1;
			COUT<<"aload "<<(int)bIndex<<ENDL;
			vm_aload(bIndex);
			break;
		case 0x16:
			bIndex = READU1;
			COUT<<"sload "<<(int)bIndex<<ENDL;
			vm_sload(bIndex);
			break;
		case 0x17:
			bIndex = READU1;
			COUT<<"iload "<<(int)bIndex<<ENDL;
			vm_iload(bIndex);
			break;
		case 0x18:
			COUT<<"aload0"<<ENDL;
			vm_aload(0);
			break;
		case 0x19:
			COUT<<"aload1"<<ENDL;
			vm_aload(1);
			break;
		case 0x1a:
			COUT<<"aload2"<<ENDL;
			vm_aload(2);
			break;
		case 0x1b:
			COUT<<"aload3"<<ENDL;
			vm_aload(3);
			break;
		case 0x1c:
			COUT<<"sload0"<<ENDL;
			vm_sload(0);
			break;
		case 0x1d:
			COUT<<"sload1"<<ENDL;
			vm_sload(1);
			break;
		case 0x1e:
			COUT<<"sload2"<<ENDL;
			vm_sload(2);
			break;
		case 0x1f:
			COUT<<"sload3"<<ENDL;
			vm_sload(3);
			break;
		case 0x20:
			COUT<<"iload0"<<ENDL;
			vm_iload(0);
			break;
		case 0x21:
			COUT<<"iload1"<<ENDL;
			vm_iload(1);
			break;
		case 0x22:
			COUT<<"iload2"<<ENDL;
			vm_iload(2);
			break;
		case 0x23:
			COUT<<"iload3"<<ENDL;
			vm_iload(3);
			break;
		case 0x24:
			COUT<<"aaload"<<ENDL;
			break;
		case 0x25:
			COUT<<"baload"<<ENDL;
			break;
		case 0x26:
			COUT<<"saload"<<ENDL;
			vm_saload();
			break;
		case 0x27:
			COUT<<"iaload"<<ENDL;
			break;
		case 0x28:
			bValue = READU1;
			COUT<<"astore "<<(int)bValue<<ENDL;
			vm_astore(bValue);
			break;
		case 0x29:
			bIndex = READU1;
			COUT<<"sstore "<<(int)bIndex<<ENDL;
			vm_sstore(bIndex);
			break;
		case 0x2a:
			bIndex = READU1;
			COUT<<"istore "<<(int)bIndex<<ENDL;
			vm_istore(bIndex);
			break;
		case 0x2b:
			COUT<<"astore_0"<<ENDL;
			vm_astore(0);
			break;
		case 0x2c:
			COUT<<"astore_1"<<ENDL;
			vm_astore(1);
			break;
		case 0x2d:
			COUT<<"astore_2"<<ENDL;
			vm_astore(2);
			break;
		case 0x2e:
			COUT<<"astore_3"<<ENDL;
			vm_astore(3);
			break;
		case 0x2f:
			COUT<<"sstore_0"<<ENDL;
			vm_sstore(0);
			break;
		case 0x30:
			COUT<<"sstore_1"<<ENDL;
			vm_sstore(1);
			break;
		case 0x31:
			COUT<<"sstore_2"<<ENDL;
			vm_sstore(2);
			break;
		case 0x32:
			COUT<<"sstore_3"<<ENDL;
			vm_sstore(3);
			break;
		case 0x33:
			COUT<<"istore_0"<<ENDL;
			vm_istore(0);
			break;
		case 0x34:
			COUT<<"istore_1"<<ENDL;
			vm_istore(1);
			break;
		case 0x35:
			COUT<<"istore_2"<<ENDL;
			vm_istore(2);
			break;
		case 0x36:
			COUT<<"istore_3"<<ENDL;
			vm_istore(3);
			break;
		case 0x37:
			COUT<<"aastore"<<ENDL;
			vm_aastore();
			break;
		case 0x38:
			COUT<<"bastore"<<ENDL;
			break;
		case 0x39:
			COUT<<"sastore"<<ENDL;
			vm_sastore();
			break;
		case 0x3a:
			COUT<<"iastore"<<ENDL;
			break;
		case 0x3b:
			COUT<<"pop"<<ENDL;
			break;
		case 0x3c:
			COUT<<"pop2"<<ENDL;
			break;
		case 0x3d:
			COUT<<"dup"<<ENDL;
			vm_dup();
			break;
		case 0x3e:
			COUT<<"dup2"<<ENDL;
			vm_dup2();
			break;
		case 0x3f:
			COUT<<"dup_x "<<READU1<<ENDL;
			vm_dup_x();
			break;
		case 0x40:
			COUT<<"swap_x"<<READU1<<ENDL;
			break;
		case 0x41:
			COUT<<"sadd"<<ENDL;
			vm_sadd();
			break;
		case 0x42:
			COUT<<"iadd"<<ENDL;
			vm_iadd();
			break;
		case 0x43:
			COUT<<"ssub"<<ENDL;
			vm_ssub();
			break;
		case 0x44:
			COUT<<"isub"<<ENDL;
			vm_isub();
			break;
		case 0x45:
			COUT<<"smul"<<ENDL;
			vm_smul();
			break;
		case 0x46:
			COUT<<"imul"<<ENDL;
			vm_imul();
			break;
		case 0x47:
			COUT<<"sdiv"<<ENDL;
			vm_sdiv();
			break;
		case 0x48:
			COUT<<"idiv"<<ENDL;
			vm_idiv();
			break;
		case 0x49:
			COUT<<"srem"<<ENDL;
			break;
		case 0x4a:
			COUT<<"irem"<<ENDL;
			break;
		case 0x4b:
			COUT<<"sneg"<<ENDL;
			break;
		case 0x4c:
			COUT<<"ineg"<<ENDL;
			break;
		case 0x4d:
			COUT<<"sshl"<<ENDL;
			break;
		case 0x4e:
			COUT<<"ishl"<<ENDL;
			break;
		case 0x4f:
			COUT<<"sshr"<<ENDL;
			break;
		case 0x50:
			COUT<<"ishr"<<ENDL;
			break;
		case 0x51:
			COUT<<"sushr"<<ENDL;
			break;
		case 0x52:
			COUT<<"iushr"<<ENDL;
			break;
		case 0x53:
			COUT<<"sand"<<ENDL;
			break;
		case 0x54:
			COUT<<"iand"<<ENDL;
			break;
		case 0x55:
			COUT<<"sor"<<ENDL;
			break;
		case 0x56:
			COUT<<"ior"<<ENDL;
			break;
		case 0x57:
			COUT<<"sxor"<<ENDL;
			break;
		case 0x58:
			COUT<<"ixor"<<ENDL;
			break;
		case 0x59:
			bIndex = READU1;
			bConst = READU1;
			COUT<<"sinc "<<(int)bIndex<<" "<<(int)bConst<<ENDL;
			vm_sinc(bIndex,bConst);
			break;
		case 0x5a:
			bIndex = READU1;
			bConst = READU1;
			COUT<<"iinc "<<(int)bIndex<<" "<<(int)bConst<<ENDL;
			vm_iinc(bIndex,bConst);
			break;
		case 0x5b:
			COUT<<"s2b"<<ENDL;
			vm_s2b();
			break;
		case 0x5c:
			COUT<<"s2i"<<ENDL;
			vm_s2i();
			break;
		case 0x5d:
			COUT<<"i2b"<<ENDL;
			vm_i2b();
			break;
		case 0x5e:
			COUT<<"i2s"<<ENDL;
			vm_i2s();
			break;
		case 0x5f:
			COUT<<"icmp"<<ENDL;
			break;
		case 0x60:
			bValue = READS1;
			COUT<<"ifeq "<<(int)bValue<<ENDL;
			vm_ifeq(bValue,pPC);
			break;
		case 0x61:
			bValue = READS1;
			COUT<<"ifne "<<(int)bValue<<ENDL;
			vm_ifne(bValue,pPC);
			break;
		case 0x62:
			COUT<<"iflt "<<READU1<<ENDL;
			break;
		case 0x63:
			COUT<<"ifge "<<READU1<<ENDL;
			break;
		case 0x64:
			COUT<<"ifgt "<<READU1<<ENDL;
			break;
		case 0x65:
			COUT<<"ifle "<<READU1<<ENDL;
			break;
		case 0x66:
			COUT<<"ifnull "<<READU1<<ENDL;
			break;
		case 0x67:
			COUT<<"ifnonnull "<<READU1<<ENDL;
			break;
		case 0x68:
			bIndex = READU1;
			COUT<<"if_acmpeq "<<(int)bIndex<<ENDL;
			//vm_acmpeq();
			break;
		case 0x69:
			COUT<<"if_acmpne "<<READU1<<ENDL;
			break;
		case 0x6a:
			COUT<<"ifscmpeq "<<READU1<<ENDL;
			break;
		case 0x6b:
			COUT<<"ifscmpne "<<READU1<<ENDL;
			break;
		case 0x6c:
			bValue = READS1;
			COUT<<"ifscmplt "<<(int)bValue<<ENDL;
			vm_ifscmplt(bValue,pPC);
			break;
		case 0x6d:
			bValue = READS1;
			COUT<<"ifscmpge "<<(int)bValue<<ENDL;
			vm_ifscmpge(bValue,pPC);
			break;
		case 0x6e:
			COUT<<"ifscmpgt "<<READU1<<ENDL;
			break;
		case 0x6f:
			COUT<<"ifscmple "<<READU1<<ENDL;
			break;
		case 0x70:
			bValue = READS1;
			COUT<<"goto "<<(int)bValue<<ENDL;
			vm_goto(bValue,pPC);
			break;
		case 0x71:
			COUT<<"jsr "<<READU2<<ENDL;
			break;
		case 0x72:
			COUT<<"ret "<<READU1<<ENDL;
			break;
		case 0x73:
			COUT<<"stableswitch \n\tdefault value:"<<READS2<<ENDL;
			lowValue = READS2;
			highValue = READS2;
			for(i=(int)lowValue;i<=(int)highValue;i++)
			{
				COUT<<"\tValue: "<<i<<" offset: "<<READS2<<ENDL;
			}
			COUT<<"End stableswitch"<<ENDL;
			break;
		case 0x74:
			COUT<<"itableswitch \n\tdefault value:"<<READS2<<ENDL;
			lowValue = READS4;
			highValue = READS4;
			for(i=(int)lowValue;i<=(int)highValue;i++)
			{
				COUT<<"\tValue: "<<i<<" offset: "<<READS2<<ENDL;
			}
			COUT<<"End itableswitch"<<ENDL;
			break;
		case 0x75:
			COUT<<"slookupswitch "<<"\n\tdefault value:"<<READS2<<ENDL;
			nPairs = READU2;
			for(i=0;i<nPairs;i++)
			{
				COUT<<"\tCase\t"<<READS2<<"\tgoto\t"<<READS2<<ENDL;
			};
			COUT<<"End slookupswitch"<<ENDL;
			break;
		case 0x76:
			COUT<<"ilookupswitch "<<"\n\tdefault value:"<<READS2<<ENDL;
			nPairs = READU2;
			for(i=0;i<nPairs;i++)
			{
				COUT<<"\tCase\t"<<READS4<<"\tgoto\t"<<READS2<<ENDL;
			};
			COUT<<"End ilookupswitch"<<ENDL;
			break;
		case 0x77:
			COUT<<"areturn"<<ENDL;
			return 1;
			break;
		case 0x78:
			COUT<<"sreturn"<<ENDL;
			return 2;
			break;
		case 0x79:
			COUT<<"ireturn"<<ENDL;
			return 3;
			break;
		case 0x7a:
			COUT<<"return"<<ENDL;
			return 0;
			break;
		case 0x7b:
			sIndex = READU2;
			COUT<<"getstatic_a "<<sIndex<<ENDL;
			vm_getstatic_a(sIndex,pCA);
			break;
		case 0x7c:
			sIndex = READU2;
			COUT<<"getstatic_b "<<sIndex<<ENDL;
			vm_getstatic_a(sIndex,pCA);
			break;
		case 0x7d:
			sIndex = READU2;
			COUT<<"getstatic_s "<<sIndex<<ENDL;
			vm_getstatic_s(sIndex,pCA);
			break;
		case 0x7e:
			COUT<<"getstatic_i "<<READU2<<ENDL;
			break;
		case 0x7f:
			COUT<<"putstatic_a"<<READU2<<ENDL;
			break;
		case 0x80:
			COUT<<"putstatic_b"<<READU2<<ENDL;
			break;
		case 0x81:
			sIndex = READU2;
			COUT<<"putstatic_s"<<sIndex<<ENDL;
			vm_putstatic_s(sIndex,pCA);
			break;
		case 0x82:
			COUT<<"putstatic_i"<<READU2<<ENDL;
			break;
		case 0x83:
			COUT<<"getfield_a "<<READU1<<ENDL;
			break;
		case 0x84:
			COUT<<"getfield_b "<<READU1<<ENDL;
			break;
		case 0x85:
			COUT<<"getfield_s "<<READU1<<ENDL;
			break;
		case 0x86:
			COUT<<"getfield_i "<<READU1<<ENDL;
			break;
		case 0x87:
			COUT<<"putfield_a "<<READU1<<ENDL;
			break;
		case 0x88:
			COUT<<"putfield_b "<<READU1<<ENDL;
			break;
		case 0x89:
			bIndex = READU1;
			COUT<<"putfield_s "<<(int)bIndex<<ENDL;
			vm_putfield_s(bIndex,pCA);
			break;
		case 0x8a:
			COUT<<"putfield_i "<<READU1<<ENDL;
			break;
		case 0x8b:
			sIndex = READU2;
			COUT<<"invokevirtual "<<(int)sIndex<<ENDL;
			vm_invokevirtual(sIndex,pCA);
			break;
		case 0x8c:
			sIndex = READU2;
			COUT<<"invokespecial "<<(int)sIndex<<ENDL;
			vm_invokespecial(sIndex,pCA);
			break;
		case 0x8d:
			sIndex = READU2;
			COUT<<"invokestatic "<<(int)sIndex<<ENDL;
			vm_invokestatic(sIndex,pCA);
			break;
		case 0x8e:
			COUT<<"invokeinterface "<<READU1<<" "<<READU2<<" "<<READU1<<ENDL;
			break;
		case 0x8f:
			sIndex = READU2;
			COUT<<"new "<<sIndex<<ENDL;
			vm_new(sIndex,pCA);
			break;
		case 0x90:
			bValue = READU1;
			COUT<<"newarray "<<(int)bValue<<ENDL;
			vm_newarray(bValue);
			break;
		case 0x91:
			sIndex = READU2;
			COUT<<"anewarray "<<(int)sIndex<<ENDL;
			vm_anewarray(sIndex,pCA);
			break;
		case 0x92:
			COUT<<"arraylength"<<ENDL;
			break;
		case 0x93:
			COUT<<"athrow"<<ENDL;
			break;
		case 0x94:
			COUT<<"checkcast "<<READU1<<" "<<READU2<<ENDL;
			break;
		case 0x95:
            bIndex = READU1;
            sIndex = READU2;
			COUT<<"instanceof "<<(int)bIndex<<" "<<(int)sIndex<<ENDL;
			vm_instanceof(bIndex,sIndex,pCA);
			break;
		case 0x96:
			COUT<<"sinc_w "<<READU1<<" "<<READU2<<ENDL;
			break;
		case 0x97:
			COUT<<"iinc_w "<<READU1<<" "<<READU2<<ENDL;
			break;
		case 0x98:
			COUT<<"ifeq_w "<<READU2<<ENDL;
			break;
		case 0x99:
			COUT<<"ifne_w "<<READU2<<ENDL;
			break;
		case 0x9a:
			COUT<<"iflt_w "<<READU2<<ENDL;
			break;
		case 0x9b:
			COUT<<"ifge_w "<<READU2<<ENDL;
			break;
		case 0x9c:
			COUT<<"ifgt_w "<<READU2<<ENDL;
			break;
		case 0x9d:
			COUT<<"ifle_w "<<READU2<<ENDL;
			break;
		case 0x9e:
			COUT<<"ifnull_w "<<READU2<<ENDL;
			break;
		case 0x9f:
			COUT<<"ifnonnull_w "<<READU2<<ENDL;
			break;
		case 0xa0:
			COUT<<"if_acmpeq_w "<<READU2<<ENDL;
			break;
		case 0xa1:
			COUT<<"if_acmpne_w "<<READU2<<ENDL;
			break;
		case 0xa2:
			COUT<<"scmpeq_w "<<READU1<<" "<<READU1<<ENDL;
			break;
		case 0xa3:
			COUT<<"scmpne_w "<<READU1<<" "<<READU1<<ENDL;
			break;
		case 0xa4:
			COUT<<"scmplt_w "<<READU1<<" "<<READU1<<ENDL;
			break;
		case 0xa5:
			COUT<<"scmpge_w "<<READU1<<" "<<READU1<<ENDL;
			break;
		case 0xa6:
			COUT<<"scmpgt_w "<<READU1<<" "<<READU1<<ENDL;
			break;
		case 0xa7:
			COUT<<"scmple_w "<<READU1<<" "<<READU1<<ENDL;
			break;
		case 0xa8:
			COUT<<"goto_w "<<READU1<<" "<<READU1<<ENDL;
			break;
		case 0xa9:
			COUT<<"getfield_a_w "<<READU2<<ENDL;
			break;
		case 0xaa:
			COUT<<"getfield_b_w "<<READU2<<ENDL;
			break;
		case 0xab:
			COUT<<"getfield_s_w "<<READU2<<ENDL;
			break;
		case 0xac:
			COUT<<"getfield_i_w "<<READU2<<ENDL;
			break;
		case 0xad:
			COUT<<"getfield_a_this "<<READU1<<ENDL;
			break;
		case 0xae:
			COUT<<"getfield_b_this "<<READU1<<ENDL;
			break;
		case 0xaf:
			bIndex = READU1;
			COUT<<"getfield_s_this "<<bIndex<<ENDL;
			vm_getfield_s_this(bIndex,pCA);
			break;
		case 0xb0:
			COUT<<"getfield_i_this "<<READU1<<ENDL;
			break;
		case 0xb1:
			COUT<<"putfield_a_w "<<READU2<<ENDL;
			break;
		case 0xb2:
			COUT<<"putfield_b_w "<<READU2<<ENDL;
			break;
		case 0xb3:
			COUT<<"putfield_s_w "<<READU2<<ENDL;
			break;
		case 0xb4:
			COUT<<"putfield_i_w "<<READU2<<ENDL;
			break;
		case 0xb5:
			COUT<<"putfield_a_this "<<READU1<<ENDL;
			break;
		case 0xb6:
			COUT<<"putfield_b_this "<<READU1<<ENDL;
			break;
		case 0xb7:
			COUT<<"putfield_s_this "<<READU1<<ENDL;
			break;
		case 0xb8:
			COUT<<"putfield_i_this "<<READU1<<ENDL;
			break;
		case 0xFE:
			break;
		case 0xFF:
			break;
		default:
			COUT<<"Unknown byte code!"<<ENDL;
			break;
		}
		//*pPC = pc;
	}
#undef READU1
#undef READU2
#undef READU4
#undef READS2
#undef READS4
};

void VirtualMachine::vm_sconst(short s)
{
	COUT<<"\t"<<(short)s<<" - has been put into stack"<<ENDL;
	push(s);
}

void VirtualMachine::vm_sstore(u1 index)
{
	jlocals[index] = pop();
	COUT<<"\tLocal ["<<(int)index<<"]="<<(int)jlocals[index]<<ENDL;
}

void VirtualMachine::vm_sload(u1 index)
{
	push(jlocals[index]);
	COUT<<"\tLocal ["<<(int)index<<"]="<<(int)jlocals[index]<<" has been push into stack"<<ENDL;
}

void VirtualMachine::vm_sadd()
{
	COUT<<"\tShort Add success!"<<ENDL;
	push(pop()+pop());
}

void VirtualMachine::vm_ssub()
{
	COUT<<"\tShort Sub success!"<<ENDL;
	push(-(pop()-pop()));
}

void VirtualMachine::vm_smul()
{
	//push((pop()*pop()));
	s2 value1 = pop();
	s2 value2 = pop();
	push(value1*value2);
	COUT<<"\tShort Mul success! The result is "<<value1*value2<<ENDL;
}

void VirtualMachine::vm_sdiv()
{
	COUT<<"\tShort Div success!"<<ENDL;
	short s1 = pop();
	short s2 = pop();
	push(s2/s1);
}

void VirtualMachine::vm_sinc(u1 index,u1 bconst)
{
	jlocals[index]+=bconst;
	COUT<<"\tLocal ["<<(int)index<<"]="<<(int)jlocals[index]<<ENDL;
}

void VirtualMachine::vm_sspush(short s)
{
	push(s);
	COUT<<"\t"<<(int)s<<" - has been put into stack"<<ENDL;
}

void VirtualMachine::vm_bspush(s1 b)
{
	push((short)b);
	COUT<<"\t"<<(int)b<<" - has been put into stack"<<ENDL;
}

void VirtualMachine::vm_iconst(int iValue)
{
	/*
	COUT<<"\t"<<makeInt(s1,s2)<<" - has been put into stack"<<ENDL;
	push(s1);
	push(s2);
	*/
	COUT<<"\t"<<iValue<<" - has been put into stack"<<ENDL;
	pushint(iValue);
}

void VirtualMachine::vm_istore(u1 index)
{
	/*
	jlocals[index+1] = pop();
	jlocals[index] = pop();
	COUT<<"\tLocal ["<<(int)index<<"]="<<MAKEINT()<<ENDL;
	*/
	jlocalsint[index] = popint();
	COUT<<"\tLocalInt ["<<(int)index<<"]="<<jlocalsint[index]<<ENDL;
}

void VirtualMachine::vm_iload(u1 index)
{
	/*
	push(jlocals[index]);
	push(jlocals[index]+1);
	COUT<<"\tLocal ["<<(int)index<<"]="<<MAKEINT()<<" has been push into stack"<<ENDL;
	*/
	pushint(jlocalsint[index]);
	COUT<<"\tLocalInt ["<<(int)index<<"]="<<(int)jlocalsint[index]<<" has been push into stack"<<ENDL;
}

void VirtualMachine::vm_iadd()
{
	/*
	short sh1 = pop();
	short sh2 = pop();

	//Reverse because of stack
	int i1 = makeInt(s2,s1);
	short sh3 = pop();
	short sh4 = pop();
	int i2 = makeInt(s4,s3);
	int i3 = i1+i2;
	//In order push, reverse pop
	push(getShortHigh(i3));
	push(getShortLow(i3));
	*/
	COUT<<"\tInt Add success!"<<ENDL;
	pushint(popint()+popint());
}

void VirtualMachine::vm_isub()
{
	COUT<<"\tInt Sub success!"<<ENDL;
	pushint(-(popint()-popint()));
}

void VirtualMachine::vm_imul()
{
	COUT<<"\tInt Mul success!"<<ENDL;
	pushint((popint()*popint()));
}

void VirtualMachine::vm_idiv()
{
	COUT<<"\tShort Div success!"<<ENDL;
	int i1 = popint();
	int i2 = popint();
	pushint(i2/i1);
}

void VirtualMachine::vm_iinc(u1 index,u1 bconst)
{
	/*
	// Local is in order
	int i1 = MAKEINT();
	i1+=bconst;
	jlocals[index]=getShortHigh(i1);
	jlocals[index+1]=getShortLow(i1);
	COUT<<"\tLocal ["<<(int)index<<"]="<<MAKEINT()<<ENDL;
	*/
	jlocalsint[index]+=bconst;
	COUT<<"\tLocal ["<<(int)index<<"]="<<(int)jlocalsint[index]<<ENDL;
}

void VirtualMachine::vm_sipush(short s)
{
	pushint((int)s);
	COUT<<"\t"<<(int)s<<" - has been put into stack"<<ENDL;
}

void VirtualMachine::vm_iipush(int iValue)
{
	pushint(iValue);
	COUT<<"\t"<<iValue<<" - has been put into stack"<<ENDL;
}

void VirtualMachine::vm_s2b()
{
	short s= pop();
	s1 b = (s1) s;
	push((s2)b);
	COUT<<"\tTranc short "<<(int)s<<" to byte "<<(int)b<<" success!"<<ENDL;
}

void VirtualMachine::vm_i2b()
{
	int i1 = popint();
	s1 b1 = (s1)i1;
	push((s2)b1);
	COUT<<"\tTranc int "<<(int)i1<<" to byte "<<(int)b1<<" success!"<<ENDL;
}

void VirtualMachine::vm_s2i()
{
	short st1 = pop();
	pushint((int)st1);
	COUT<<"\tTranc short "<<(int)st1<<" to int "<<(int)st1<<" success!"<<ENDL;
}

void VirtualMachine::vm_i2s()
{
	int i1 = popint();
	short sh1 = (short)i1;
	push(sh1);
	COUT<<"\tTranc int "<<i1<<" to short "<<(int)sh1<<" success!"<<ENDL;
}

void VirtualMachine::vm_newarray(int arrayType)
{
	int count = (int)pop();
	if(count<0)
		return;
	switch(arrayType)
	{
	case T_BOOLEAN:

	case T_BYTE:
		if(baCount<MAX_ARRAY)
		{
			bytearrays[++baCount] = new s1[count];
			for(int i=0;i<count;i++)
			{
				bytearrays[baCount][i] = 0;
			}
			push((u2)baCount);
			COUT<<"\tByte Array "<<(int)baCount<<" has been created with "<<(int)count<<" items!"<<ENDL;
		}

		break;
	case T_SHORT:
		if(saCount<MAX_ARRAY)
		{
			shortarrays[++saCount] = new s2[count];
			for(int i=0;i<count;i++)
			{
				shortarrays[saCount][i] = 0;
			}
			push((u2)saCount);
			COUT<<"\tShort Array "<<(int)saCount<<" has been created with "<<(int)count<<" items!"<<ENDL;
		}
		break;
	case T_INT:
		break;
	default:
		return;
	}
}

void VirtualMachine::vm_anewarray(u2 sIndex, AbstractApplet* pCA)
{
	int count = (int)pop();
	if(count<0)
		return;

	objarrays[++aaCount] = new u2[count];
	for(int i=0;i<count;i++)
	{
		objarrays[aaCount][i] = 0;
	}
	push((u2)aaCount);
	COUT<<"\tObject Array "<<(int)aaCount<<" has been created with "<<(int)count<<" items!"<<ENDL;
}

void VirtualMachine::vm_astore(u1 index)
{
	jlocals[index] = (u2)pop();
	COUT<<"\tLocal ["<<(int)index<<"]= reference type: "<<(int)jlocals[index]<<ENDL;
}

void VirtualMachine::vm_aload(u1 index)
{
	push(jlocals[index]);
	COUT<<"\tLocal ["<<(int)index<<"]="<<(int)jlocals[index]<<" has been push into stack"<<ENDL;
}

void VirtualMachine::vm_aastore()
{
	s2 value = pop();
	s2 index = pop();
	s2 arrayref = pop();

	objarrays[arrayref][(int)index] = value;

	//[index]=value;
	COUT<<"\tObject Array "<<(int)arrayref<<"["<<(int)index<<"]<= "<<(int)value<<ENDL;
}

void VirtualMachine::vm_sastore()
{
	s2 value = pop();
	s2 index = pop();
	s2 arrayref = pop();

	shortarrays[arrayref][(int)index] = value;

	//[index]=value;
	COUT<<"\tShort Array "<<(int)arrayref<<"["<<(int)index<<"]<= "<<(int)value<<ENDL;
}

void VirtualMachine::vm_saload()
{
	s2 index = pop();
	s2 arrayref = pop();

	s2 value = shortarrays[arrayref][index];
	push(value);

	COUT<<"\t"<<(int)value<<" has put into stack from array"<<ENDL;
}

void VirtualMachine::vm_dup()
{
	s2 stemp = pop();
	push(stemp);
	push(stemp);

	COUT<<"\t"<<(int)stemp<<" is duplicated."<<ENDL;

}

void VirtualMachine::vm_dup2()
{
	s2 short1 = pop();
	s2 short2 = pop();

	push(short2);
	push(short1);
	push(short2);
	push(short1);

	COUT<<"\t"<<(int)short2<<" "<<(int) short1<<" is duplicated."<<ENDL;
}

void VirtualMachine::vm_dup_x()
{
	//TODO:
}

void VirtualMachine::vm_ifscmpge(s1 bValue,int *pPC)
{
	s2 value2 = pop();
	s2 value1 = pop();

	if(value1>=value2)
	{
		COUT<<"\t"<<(int)value1<<" >= "<<(int)value2<<" go! "<<ENDL;
		(*pPC)+=bValue;
		(*pPC)-=2;
	}
	else
	{
		COUT<<"\t"<<(int)value1<<" < "<<(int)value2<<" not go "<<ENDL;
	}
}

void VirtualMachine::vm_ifscmplt(s1 bValue,int *pPC)
{
	s2 value2 = pop();
	s2 value1 = pop();

	if(value1<value2)
	{
		COUT<<"\t"<<(int)value1<<" < "<<(int)value2<<" go! "<<ENDL;
		(*pPC)+=bValue;
		(*pPC)-=2;
	}
	else
	{
		COUT<<"\t"<<(int)value1<<" >= "<<(int)value2<<" not go "<<ENDL;
	}
}

void VirtualMachine::vm_ifne(s1 bValue,int* pPC)
{
	s2 sValue = pop();

	if(sValue == 0)
	{
		COUT<<"\t"<<(int)sValue<<"==0 not go!"<<ENDL;
	}
	else
	{
		COUT<<"\t"<<(int)sValue<<"!=0 go! "<<ENDL;
		(*pPC)+=bValue;
		(*pPC)-=2;
	}
}

void VirtualMachine::vm_ifeq(s1 bValue,int* pPC)
{
	s2 sValue = pop();

	if(sValue == 0)
	{
		COUT<<"\t"<<(int)sValue<<"==0 go!"<<ENDL;
		(*pPC)+=bValue;
		(*pPC)-=2;

	}
	else
	{
		COUT<<"\t"<<(int)sValue<<"!=0 not go! "<<ENDL;
	}
}

void VirtualMachine::vm_goto(s1 bValue,int *pPC)
{
	(*pPC)+=bValue;
	//The length of goto ins is 2.
	(*pPC)-=2;
	COUT<<"\tGoto "<<(int)bValue<<ENDL;
}

void VirtualMachine::vm_putstatic_s(u2 sIndex, AbstractApplet* pCA)
{
	u1* pData = getStaticFieldAddress(sIndex,pCA);
	s2 value = pop();

	pData[0] = value / 0x100;
	pData[1] = value % 0x100;

	COUT<<"\t"<<(int)value<<" has been put to static field "<<(int)sIndex<<ENDL;
}

void VirtualMachine::vm_getstatic_s(u2 sIndex, AbstractApplet* pCA)
{
	u1* pData = getStaticFieldAddress(sIndex,pCA);
	u1 byte1 = pData[0];
	u1 byte2 = pData[1];
	s2 value = (s2)makeU2(byte1,byte2);
	COUT<<"\t"<<(int)value<<" has read from static field "<<(int)sIndex<<ENDL;
	push(value);
}

void VirtualMachine::vm_getstatic_a(u2 sIndex,AbstractApplet* pCA)
{
	u1* pData = getStaticFieldAddress(sIndex,pCA);
	u1 byte1 = pData[0];
	u1 byte2 = pData[1];
	u2 value = makeU2(byte1,byte2);
	COUT<<"\t"<<(int)value<<" has read from static field "<<(int)sIndex<<ENDL;
	push(value);
}

u1* VirtualMachine::getStaticFieldAddress(u2 sIndex,AbstractApplet* pCA)
{
	CpInfo* pCI = pCA->pConstPool->pConstantPool[sIndex];
	//COUT<<"\tThe tag of the static field is "<<(int)pCI->Tag<<ENDL;
	s1 value1 = pCI->info[0];
	u2 sOffset = makeU2(pCI->info[1],pCI->info[2]);

	if(value1 == 0)
	{
		//COUT<<"\tIt is an internal static field."<<ENDL;
		//COUT<<"\tIt's offest in static field component is "<<sOffset<<ENDL;
		return pCA->pStaticField->pStaticFieldImage+sOffset;
	}
	else
	{
		COUT<<"\tIt is defined in package "<<(int)value1<<ENDL;
		return NULL;
	}
}

void VirtualMachine::vm_new(u2 index, AbstractApplet* pCA)
{
	CpInfo* pCI = pCA->pConstPool->pConstantPool[index];

	s1 value1 = pCI->info[0];

	if(value1 == 0)
	{
		u2 sOffset = makeU2(pCI->info[0],pCI->info[1]);
		COUT<<"\tIt is an internal class."<<ENDL;
		COUT<<"\tIt's offest in class component is "<<sOffset<<ENDL;

		createClass(sOffset,pCA);

	}
	else
	{
		u1 packageIndex = value1 & 0x7F;
		PackageInfo* pPI = pCA->pImport->packages[packageIndex];

		CardLibrary *pCL = CardLibList::findLibrary(pPI);

		if(pCL != NULL)
		{
			COUT<<"\tExternal library found!"<<ENDL;
			u1 classtoken = pCI->info[1];

			u2 coffset = pCL->pExport->pClassExport[classtoken]->classOffset;

			createClass(coffset,pCL);

		}
		else
		{
			COUT<<"\tIt is defined in package "<<(int)packageIndex<<" the token is "<<(int)pCI->info[1]<<ENDL;
			COUT<<"\tCannot found the library!"<<ENDL;
		}
	}
}

void VirtualMachine::vm_invokestatic(u2 index,AbstractApplet* pCA)
{
	invokestaticCommon(index,pCA);
}

void VirtualMachine::vm_invokespecial(u2 index,AbstractApplet* pCA)
{
	invokestaticCommon(index,pCA);
}

void VirtualMachine::vm_putfield_s(u1 index, AbstractApplet *pCA)
{
	CpInfo* pCI = pCA->pConstPool->pConstantPool[index];

	//ClassRef thisclass(makeU2(pCI->info[0],pCI->info[1]));

	u1 token = pCI->info[2];

	s2 value = pop();

	u2 thisclassobject = (u2)pop();

	javaClasses[(thisclassobject-0x100)]->pInstance[index] = value;

	COUT<<"\t Field referenc is object "<<(int)thisclassobject<<" field "<<(int)token<<ENDL;
	COUT<<"\t The value is set to "<<(int)javaClasses[(thisclassobject-0x100)]->pInstance[index]<<ENDL;
}

void VirtualMachine::vm_invokevirtual(u2 index, AbstractApplet *pCA)
{
	CpInfo* pCI = pCA->pConstPool->pConstantPool[index];

	u1 byte1 = pCI->info[0];

	if((byte1 & 0x80) == 0x80)
	{
		u1 packageIndex = byte1 & 0x7F;
		PackageInfo* pPI = pCA->pImport->packages[packageIndex];

		CardLibrary *pCL = CardLibList::findLibrary(pPI);

		if(pCL != NULL)
		{
			COUT<<"\tExternal library found!"<<ENDL;
			u1 classtoken = pCI->info[1];

			u2 sOffset = pCL->pExport->pClassExport[classtoken]->classOffset;

			ClassInfo* pClInf = (ClassInfo*)pCL->pClass->pClasses[sOffset];

			u1 token = pCI->info[2];

			pCL->pMethod->executeByteCode(pClInf->publicVirtualMethodTable[token-pClInf->publicMethodTableBase],pCL);
		}
		else
		{
			COUT<<"\tInvoke package "<<(int)pCI->info[0]<<" class "<<(int)pCI->info[1]<<" method "<<(int)pCI->info[2]<<ENDL;
			COUT<<"\tCannot found the library!"<<ENDL;
		}
	}
	else
	{
		u2 offset = makeU2(pCI->info[0],pCI->info[1]);
		u1 token = pCI->info[2];
		COUT<<"\tInvoke class "<<(int)offset<<" method "<<(int)token<<ENDL;
		ClassInfo* pClInf = (ClassInfo*)pCA->pClass->pClasses[offset];
		if((token & 0x80)==0x80)
		{
			COUT<<"This is a TODO function here!"<<ENDL;
		}
		else
		{
			pCA->pMethod->executeByteCode(pClInf->publicVirtualMethodTable[token - pClInf->publicMethodTableBase],pCA);
		}
	}
}

void VirtualMachine::vm_getfield_s_this(u1 index,AbstractApplet *pCA)
{
	s2 value = javaClasses[((u2)jlocals[0]-0x100)]->pInstance[index];

	push(value);

	COUT<<"\t Field referenc is object "<<(int)((u2)jlocals[0]-0x100)<<" Index "<<(int)index<<" is "<<(int)value<<ENDL;
}

void VirtualMachine::vm_aconst_null()
{
	COUT<<"\tA null object has been put into stack"<<ENDL;
	push((u2)0);
}

//===

void VirtualMachine::createClass(u2 sOffset,AbstractApplet* pCA)
{
	ClassInfo* pClInf = (ClassInfo*)pCA->pClass->pClasses[sOffset];

	ClassRef* pCR = &pClInf->superClassRef;

	int declaredInstanceSize = pClInf->declaredInstanceSize;

	javaClasses[++jcCount] = new JavaClass(ClassRef(sOffset),*pCR,declaredInstanceSize);
	push((u2)(jcCount+0x100));

	COUT<<"\tClass "<<(int)(jcCount+0x100)<<" has been created! "<<ENDL;
}

void VirtualMachine::invokestaticCommon(u2 index,AbstractApplet* pCA)
{
	CpInfo* pCI = pCA->pConstPool->pConstantPool[index];

	s1 value1 = pCI->info[0];

	if(value1 == 0)
	{
		u2 sOffset = makeU2(pCI->info[1],pCI->info[2]);
		COUT<<"\tMethod in offset "<<(int)sOffset<<" has been invoked!"<<ENDL;
		//jlocals[0] = (u2)pop();
		pCA->pMethod->executeByteCode(sOffset,pCA);
	}
	else
	{
		u1 packageIndex = value1 & 0x7F;
		PackageInfo* pPI = pCA->pImport->packages[packageIndex];

		CardLibrary *pCL = CardLibList::findLibrary(pPI);

		if(pCL != NULL)
		{
			COUT<<"\tExternal library found!"<<ENDL;
			u1 classtoken = pCI->info[1];

			u2 sOffset = pCL->pExport->pClassExport[classtoken]->pStaticMethodOffsets[pCI->info[2]];

			pCL->pMethod->executeByteCode(sOffset,pCL);
		}
		else
        {
			COUT<<"\tInvoke package "<<(int)pCI->info[0]<<" class "<<(int)pCI->info[1]<<" method "<<(int)pCI->info[2]<<ENDL;
			COUT<<"\tCannot found the library!"<<ENDL;
		}
	}
}

void VirtualMachine::vm_instanceof(u1 aType,u2 sIndex,AbstractApplet* pCA)
{
    u2 objRef = pop();
	JavaClass* pObj = javaClasses[objRef - 0x100];

    switch(aType){
        case TYPE_ARRAY_OF_BOOLEAN:
			COUT<<"\tThis is a boolean array!"<<ENDL;
            break;
        case TYPE_ARRAY_OF_BYTE:
			COUT<<"\tThis is a byte array!"<<ENDL;
            break;
        case TYPE_ARRAY_OF_SHROT:
			COUT<<"\tThis is a short array!"<<ENDL;
            break;
        case TYPE_ARRAY_OF_INT:
			COUT<<"\tThis is an int array!"<<ENDL;
            break;
        case TYPE_ARRAY_OF_REFERENCE:
			COUT<<"\tThis is a reference array!"<<ENDL;
            break;
        default:
			COUT<<"\tThis is not an array!"<<ENDL;
			CpInfo* pCI = pCA->pConstPool->pConstantPool[sIndex];
			if(pCI->Tag != 1){
				COUT<<"\t\tError! It is not a classref!"<<ENDL;
			}
			else
			{
				COUT<<"\t\tIt is a classref!"<<ENDL;

				//If it is the directly inherited from a class, then we can check the classref with the object's superClassRef.

				if(pObj->superClass.classref == makeU2(pCI->info[0],pCI->info[1])){
					COUT<<"The current object is an instance of class "<<(int)pObj->superClass.classref<<ENDL;
					push((s2)1);
					return;
				}

				s1 value1 = pCI->info[0];
				if(value1 == 0)
				{
					u2 sOffset = makeU2(pCI->info[0],pCI->info[1]);
					COUT<<"\tIt is an internal class."<<ENDL;
					COUT<<"\tIt's offest in class component is "<<sOffset<<ENDL;

					AbstractClassInfo* pACI = pCA->pClass->pClasses[sOffset];

					if(!pACI->isInterface()){
						COUT<<"\tIt's an class"<<ENDL;
						ClassInfo* pCI = (ClassInfo*) pACI;
						//pCI->
					}

					//pObj->superClass;
				}
				else
				{
					u1 packageIndex = value1 & 0x7F;
					PackageInfo* pPI = pCA->pImport->packages[packageIndex];
					CardLibrary *pCL = CardLibList::findLibrary(pPI);

					if(pCL != NULL)
					{
						COUT<<"\tExternal library found!"<<ENDL;
						u1 classtoken = pCI->info[1];

						u2 coffset = pCL->pExport->pClassExport[classtoken]->classOffset;

						COUT<<"\tThe class offset is "<<coffset<<ENDL;

					}
					else
					{
						COUT<<"\tIt is defined in package "<<(int)packageIndex<<" the token is "<<(int)pCI->info[1]<<ENDL;
						COUT<<"\tCannot found the library! As a result, we set the value to false."<<ENDL;
						push((s2)0);
						return;
					}
				}
			}

            break;
    }

    push((s2)0);
}
