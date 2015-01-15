/*************************************************
 * Fullmoon - MathUtil
 * Copyright (c) 2010-2012,2015 Queue Sakura-Shiki
 * Released under the MIT license
 */
#pragma once
#include <Windows.h>

class MathUtil
{
public:
	static void initialize();

	static double sin( INT32 angle );
	static double sinUp( double percent );
	static double sinDown( double percent );

	static double cos( INT32 angle );
	static double cosUp( double percent );
	static double cosDown( double percent );

	static INT32 upDown( INT32 length, INT32 value, INT32 range );

	static void MathUtil::atan ( double *resultX, double *resultY, double sourceX, double targetX, double sourceY, double targetY );
	static INT32 MathUtil::atanAngle ( double sourceX, double targetX, double sourceY, double targetY );
private:
	MathUtil(void);
	~MathUtil(void);
};
