#define MAX_HARDWARE 5000
#define unsigned char BYTE
int 			HardwarePhysical [MAX_HARDWARE];

BYTE   		*HardwareByte=(char *)& HardwarePhysical ;
BYTE   		*HardwareInt=& HardwarePhysical ;


#define ENGINE_SHUT_LINE 		037
#define DEVICE1_CONTROL_REG 	0x1020
#define DEVICE1_STATUS_REG 		0x1024
#define DEVICE1_DATA_REG 		0x1028
#define DEVICE2_CONTROL_REG 	0x102c
#define DEVICE2_STATUS_REG 		0x1030
#define DEVICE2_DATA_REG 		0x1034
#define interruptVectorAddress 3000;
int *InterruptVector =&HardwareInt[interruptVectorAddress];

#define BindISRToLine(funtctionPTR,line) InterruptVector[(line)] =(funtctionPTR);
struct
{
	size_t m_address;
	int m_shaddow;
}HardwareRegMap;
#ifdef REALhARDWARE
#pragma interrupt DanDriverISR
#else

#endif
void DanDriverISR (void)
{
   // shutDown Engine
   void RegisterWriteWithShadow(EngineShutDown, doShut);
   
   //send message to Netali
   
   // tathil Pitztuz
    
}
void  EnginesInit(void)
{
   BindISRToLine(DanDriverISR,ENGINE_SHUT_LINE);
}

void myThreadDanEngines
{
  EnginesInit();
  while (1)
  {
    // to do later
  }

}

void EmulateInterrupt(int interrupt_line)
{ 
	InterruptVector[(line)]();
}


typedef enum
{
  DEVICE2_DATA_REG_E,
  DEVICE2_CONTROL_REG_E,
  registerEnum_LAST
}registerEnum;

HardwareRegMap HardwareMap[registerEnum_LAST];

class Hardware
{
public:
	int Read(size_t _address)
	{
		return HardwareByte[_address];
	}
	
	void Wrire(size_t _address, int _data)
	{
		HardwareByte[_address] = _data;
	}
	
	WriteWithShaddow(RegisterEnum);
	ReadShaddow(RegisterEnum);
	
	MapRegister(enum,address);
	
	InterruptBind(Function,Line);
	InterruptEmulate(Line);
	InterruptLineDisable(Line);
	InterruptLineEnable(Line);
	InterruptEnable();
	InterruptDisable();
	
	Bind_1MicroSecondTick(Function);
	Bind_1MilliSecondTick(Function);
	Bind_1SecondTick(Function);
	
	CallMeAtTime (Function, Time);
}

void mapRegister(registerEnum thisReg, size_t address)
{
   HardwareMap[thisReg].address=address;
}

void RegisterWriteWithShadow(registerEnum thisReg, int data)
{
//   *HardwareMap[thisReg].address=data;
//    HardwareInt[HardwareMap[thisReg].address]=data;
  
    RegisterWrite(HardwareMap[thisReg].address,data);
    HardwareMap[thisReg].shadow=data;
}



