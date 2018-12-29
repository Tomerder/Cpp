N-Body simulation sample

-Overview:
The C++ AMP N-Body simulation sample simulates a dynamic particle system of (n) bodies where each body exerts a gravitational force on all other bodies in the simulation.

-Hardware requirement:
This sample requires DirectX 11 capable card, if none detected sample will use DirectX 11 Reference Emulator.

-Running sample:
This sample contains NBodyDX project which builds a graphical sample which displays the N-Body simulation in a DirectX rendering window.  This sample uses the same DXUT framework and rendering path as the DirectX SDK sample only modifying the compute portions of the sample to use C++ AMP.

-References:
http://en.wikipedia.org/wiki/N-body_simulation
DirectX August 2009 SDK N-Body sample $(DXSDK)\Samples\C++\Direct3D11\NBodyGravityCS11


Known issue:
1. Warning message like below:
C:\Program Files\Microsoft Visual Studio 11.0\VC\include\xxamp.h(101): warning C4505: 'Concurrency::details::_Array_view_projection_helper<_T,_R>::_Project' : unreferenced local function has been removed
          with
          [
              _T=const PARTICLE,
              _R=1
          ]
	This is currently being worked on

2. Runtime exception while running in debug mode. This is due to mismatch in shader signature from one shader input to another
	vcamp110d.dll!Concurrency::details::_D3D_throw_runtime_exception(const char * _Main_error_msg, Concurrency::details::_D3D_status _Status)
 	vcamp110d.dll!Concurrency::details::_D3D_buffer_data::~_D3D_buffer_data()
 	vcamp110d.dll!Concurrency::details::_D3D_buffer_data::`scalar deleting destructor'(unsigned int)
 	vcamp110d.dll!Concurrency::details::_D3D_accelerator_view_impl::_Release_buffer(Concurrency::details::_Buffer * _Buf)
 	vcamp110d.dll!Concurrency::details::_Buffer::~_Buffer()
 	vcamp110d.dll!Concurrency::details::_Buffer::`scalar deleting destructor'(unsigned int)
 	vcamp110d.dll!Concurrency::details::_CPU_accelerator_view_impl::_Release()
 	vcamp110d.dll!Concurrency::details::_Reference_counter::_Remove_reference()
 	vcamp110d.dll!Concurrency::details::_Reference_counted_obj_ptr<Concurrency::details::_View_shape>::_UnInitialize(Concurrency::details::_View_shape * _Obj_ptr)
 	vcamp110d.dll!Concurrency::details::_Reference_counted_obj_ptr<Concurrency::details::_Buffer>::~_Reference_counted_obj_ptr<Concurrency::details::_Buffer>()
 	vcamp110d.dll!Concurrency::details::_Ubiquitous_buffer::~_Ubiquitous_buffer()
 	vcamp110d.dll!Concurrency::details::_Ubiquitous_buffer::`scalar deleting destructor'(unsigned int)
 	vcamp110d.dll!Concurrency::details::_CPU_accelerator_view_impl::_Release()
 	NBodyGravityCS11.exe!Concurrency::details::_Reference_counter::_Remove_reference()
 	NBodyGravityCS11.exe!Concurrency::details::_Buffer_descriptor::_Set_buffer_ptr(Concurrency::details::_Ubiquitous_buffer * _Buffer_ptr)
 	NBodyGravityCS11.exe!Concurrency::details::_Buffer_descriptor::~_Buffer_descriptor()
 	NBodyGravityCS11.exe!Concurrency::array<particle,1>::~array<particle,1>()
 	NBodyGravityCS11.exe!Concurrency::array<particle,1>::`scalar deleting destructor'(unsigned int)



FAQ:



Layout and Files needed to run this app:

<WorkingDir>dir /S .
	<DIR>          misc
	<DIR>          UI

05/11/2011  09:09 PM         3,335,168 D3DCompiler_44.dll
05/11/2011  09:09 PM           263,680 d3dx11_44.dll
05/11/2011  09:09 PM           263,680 d3dx11d_44.dll
05/11/2011  09:09 PM           263,680 d3dx9_44.dll
05/11/2011  09:09 PM           263,680 d3dx9d_44.dll
05/12/2011  12:51 AM         5,106,688 msvcp110*.*.pdb
04/27/2011  12:35 AM           865,888 msvcr110*.dll
05/16/2011  03:20 PM           641,024 NBodyGravityCS11.exe
05/16/2011  03:20 PM         4,287,488 NBodyGravityCS11.pdb
05/11/2010  10:56 AM             2,787 ParticleDraw.hlsl
05/12/2011  01:02 AM           306,688 vcdpc110*.dll
05/11/2011  11:34 AM         6,393,856 vcdpc110*.*.pdb


 Directory of <WorkingDir>\misc

05/13/2011  06:35 PM    <DIR>          .
05/13/2011  06:35 PM    <DIR>          ..
04/19/2010  05:56 AM           262,272 particle.dds
               1 File(s)        262,272 bytes

 Directory of <WorkingDir>\UI

05/13/2011  06:35 PM    <DIR>          .
05/13/2011  06:35 PM    <DIR>          ..
04/19/2010  05:56 AM            23,227 arrow.x
04/19/2010  05:56 AM           262,272 dxutcontrols.dds
04/19/2010  05:56 AM             2,594 DXUTShared.fx
04/19/2010  05:56 AM            76,128 Font.dds
               4 File(s)        364,221 bytes

