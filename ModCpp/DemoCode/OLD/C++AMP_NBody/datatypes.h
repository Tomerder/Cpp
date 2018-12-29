
#pragma once

class float_4
{
public:
	float_4() restrict(direct3d,cpu) : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 0.0f) {};
	float_4( float a_x, float a_y, float a_z, float a_w ) restrict(direct3d,cpu) : x( a_x ), y( a_y ), z( a_z ), w( a_w ) {};
	void set( float a_x, float a_y, float a_z, float a_w ) restrict(direct3d,cpu) { x = a_x; y = a_y; z = a_z; w = a_w; }
	float sqrlength() const restrict(direct3d,cpu) { return x * x + y * y + z * z + w * w; }
	float dot( const float_4 a_v ) const restrict(direct3d,cpu) { return x * a_v.x + y * a_v.y + z * a_v.z + w * a_v.w; }
	
	float_4 operator- () const restrict(direct3d,cpu) { return float_4( -x, -y, -z, -w ); }
	
	void operator += ( const float_4& a_v ) restrict(direct3d,cpu) { x += a_v.x; y += a_v.y; z += a_v.z; w += a_v.w; }
	void operator -= ( const float_4& a_v ) restrict(direct3d,cpu) { x -= a_v.x; y -= a_v.y; z -= a_v.z; w -= a_v.w; }
	void operator *= ( const float_4& a_v ) restrict(direct3d,cpu) { x *= a_v.x; y *= a_v.y; z *= a_v.z; w *= a_v.w; }

	void operator *= ( const float f ) restrict(direct3d,cpu) { x *= f; y *= f; z *= f; w *= f; }

	float_4 operator+ (const float_4& a_v) restrict(direct3d,cpu) 
    {
        return float_4(x + a_v.x, y + a_v.y, z + a_v.z, w + a_v.w);
    }
	float_4 operator- (const float_4& a_v) restrict(direct3d,cpu) 
    {
        return float_4(x - a_v.x, y - a_v.y, z - a_v.z, w - a_v.w);
    }
	float_4 operator* (const float_4& a_v) restrict(direct3d,cpu) 
    {
        return float_4(x * a_v.x, y * a_v.y, z * a_v.z, w * a_v.w);
    }

	float_4 operator/ (const float_4& a_v) restrict(direct3d,cpu) 
    {
        return float_4(x / a_v.x, y / a_v.y, z / a_v.z, w / a_v.w);
    }

	float_4 operator+ (const float f) restrict(direct3d,cpu) 
    {
        return float_4(x + f, y + f, z + f, w + f);
    }
	float_4 operator- (const float f) restrict(direct3d,cpu) 
    {
        return float_4(x - f, y - f, z - f, w - f);
    }
	float_4 operator* (const float f) restrict(direct3d,cpu) 
    {
        return float_4(x * f, y * f, z * f, w * f);
    }
	float_4 operator/ (const float f) restrict(direct3d,cpu) 
    {
        return float_4(x / f, y / f, z / f, w / f);
    }

	float x, y, z, w;
};
