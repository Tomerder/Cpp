#ifndef _HARDWARE_
#define _HARDWARE_

#include <iostream>
#include <stdio.h>

using namespace std;

/*---------------------------------------------------------------*/

#define REG1_ADR 0x1024
#define REG2_ADR 0x2048
#define REG3_ADR 0x4096

/*---------------------------------------------------------------*/

#define MAX_HARDWARE 5000
#define unsigned char BYTE
int 			HardwarePhysical [MAX_HARDWARE];

BYTE   		*HardwareByte=(char *)& HardwarePhysical ;
BYTE   		*HardwareInt=& HardwarePhysical ;

/*---------------------------------------------------------------*/

int *InterruptVector =&HardwareInt[interruptVectorAddress];

#define BindISRToLine(funtctionPTR,line) InterruptVector[(line)] =(funtctionPTR);

/*---------------------------------------------------------------*/

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

/*---------------------------------------------------------------*/

typedef enum
{
	REG1,
	REG2,
	REG3,
	REG_LAST
}RegEnum;

/*---------------------------------------------------------------*/

struct RegEntry
{
	int* m_address,
	int m_shaddow
};

/*---------------------------------------------------------------*/

class Hardware   
{
public:
	void Write(int* _address, int _data)  { *_address = _data; }
	int Read(int* _address)  { return *_address; }

	void WriteShaddow(RegEnum _reg, int _data) { m_regs[_reg]->m_address = _data; 
												 m_regs[_reg].m_shaddow = _data;  }
	
	int ReadShaddow(RegEnum _reg) { return m_regs[_reg].m_shaddow; }

	void MapReg(RegEnum _reg, int* _address) { m_regs[_reg].m_address = _address ; }

	void Init() 
	{
		m_regs[REG1].m_address = REG1_ADR;
		m_regs[REG2].m_address = REG2_ADR;
		m_regs[REG3].m_address = REG3_ADR;
	}

	static Hardware* GetInstance() 
	{ 
		if(!m_insance) {
	        m_insance = new Hardware;	  								
	    }
		return m_insance;					    
	}

	void Destroy()  {  delete m_insance;  }

	InterruptBind(Func _func, size_t Line);
	InterruptEmulate(size_t Line)
	InterruptLineDisable(size_t Line); 		
	InterruptLineEnable(size_t Line)
	InterruptEnable(); 		
	InterruptDisable(); 

	Bind_Every(Func _func, Time _every);
	CallMeAtTime (Func _func, Time _time);

private:
	Hardware() {  Init();  }

	static Hardware* m_insance;
	
	RegEntry m_regs[RegEnum.REG_LAST];   //registers array

										 //interupt vector
}

/*---------------------------------------------------------------*/

#endif  //HARDWARE
