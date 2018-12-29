
#pragma once

#include "datatypes.h"

struct D3DXVECTOR3
{
public:
  D3DXVECTOR3() restrict(direct3d,cpu) {x = 0; y = 0; z = 0;}
  D3DXVECTOR3(float _x, float _y, float _z) restrict(direct3d,cpu) {x = _x; y = _y; z = _z;}
  float x, y, z;
};

struct D3DXVECTOR4
{
    float x, y, z, w;
};

D3DXVECTOR4 create_d3dxv4(float x, float y, float z, float w)
{
	D3DXVECTOR4 temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	temp.w = w;
	return temp;
}

// init D3DXVECTOR4
D3DXVECTOR4 to_d3dxv4(float_4 v) restrict(direct3d,cpu)
{
	D3DXVECTOR4 temp;
	temp.x = v.x;
	temp.y = v.y;
	temp.z = v.z;
	temp.w = v.w;
	return temp;
}