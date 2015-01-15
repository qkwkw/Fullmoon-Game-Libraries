/*************************************************
 * Fullmoon - MathUtil
 * Copyright (c) 2010-2012,2015 Queue Sakura-Shiki
 * Released under the MIT license
 */
#include "MathUtil.h"

#include <math.h>

static double sinTmp[3600];
static double cosTmp[3600];

#define PI 3.141592

void MathUtil::initialize() {
	for ( int i=0 ; i<3600 ; i++ ) {
		sinTmp[i] = 180 <  ((double)i/10.0) <  360 ? sinf((float)(i* PI / 1800.0)) : -sinf((float)(i * PI / 1800.0));
		cosTmp[i] =  90 <  ((double)i/10.0) <  270 ? cosf((float)(i* PI / 1800.0)) : -cosf((float)(i * PI / 1800.0));
	}
}

double  MathUtil::sin ( INT32 angle ) {
	while ( angle < 0 ) { angle += 3600; }
	return sinTmp[angle%3600];
}

double MathUtil::sinUp( double percent ) {
	if ( percent < 0 ) { percent=0; }
	if ( percent > 100 ) { percent=100; }
	return sinTmp[(INT32)percent*9];
}
double MathUtil::sinDown( double percent ) {
	if ( percent < 0 ) { percent=0; }
	if ( percent > 100 ) { percent=100; }
	return 1.0-sinTmp[(INT32)percent*9];
}

double  MathUtil::cos ( INT32 angle ) {
	while ( angle < 0 ) { angle += 3600; }
	return cosTmp[angle%3600];
}

double MathUtil::cosDown( double percent ) {
	if ( percent < 0 ) { percent=0; }
	if ( percent > 100 ) { percent=100; }
	return cosTmp[(INT32)percent*9];
}
double MathUtil::cosUp( double percent ) {
	if ( percent < 0 ) { percent=0; }
	if ( percent > 100 ) { percent=100; }
	return 1.0-cosTmp[(INT32)percent*9];
}

void MathUtil::atan ( double *resultX, double *resultY, double sourceX, double targetX, double sourceY, double targetY ) {
	DOUBLE diffX = targetX - sourceX;
	DOUBLE diffY = targetY - sourceY;
	DOUBLE l = sqrt( diffX*diffX + diffY*diffY );
	*resultX = (diffX/l);
	*resultY = (diffY/l);
}
INT32 MathUtil::atanAngle ( double sourceX, double targetX, double sourceY, double targetY ) {
	return (3600-10*(180* atan2(targetY-sourceY,targetX-sourceX)/PI))+900;
}

INT32 MathUtil::upDown( INT32 length, INT32 value, INT32 range ) {
	INT32 v = value%length;
	if ( v < length/2 ) {
		return range*v/(length/2);
	} else {
		return range*(length-v)/(length/2);
	}
}
