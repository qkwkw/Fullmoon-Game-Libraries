/*************************************************
 * Fullmoon - MathUtil
 * Copyright (c) 2010-2012,2015 Queue Sakura-Shiki
 * Released under the MIT license
 */
class MathUtil
{
public:
	static void initialize();

	static double sin( int angle );
	static double sinUp( double percent );
	static double sinDown( double percent );

	static double cos( int angle );
	static double cosUp( double percent );
	static double cosDown( double percent );

	static void MathUtil::atan ( double *resultX, double *resultY, double sourceX, double targetX, double sourceY, double targetY );
	static int MathUtil::atanAngle ( double sourceX, double targetX, double sourceY, double targetY );
private:
	MathUtil(void);
	~MathUtil(void);
};
