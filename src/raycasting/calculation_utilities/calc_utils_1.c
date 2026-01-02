#include "include.h"

double	deg_to_rad(double angle)
{
	double	ang;

	ang = angle;
	if (ang < 0)
		while (ang < 0)
			ang += 360;
	if (ang > 360)
		ang = fmod(ang, 360);
	ang *= (M_PI / 180);
	return (ang);
}

double	rad_to_deg(double angle)
{
	double	ang;

	ang = angle;
	ang *= (180 / M_PI);
	if (ang < 0)
		while (ang < 0)
			ang += 360;
	if (ang > 360)
		ang = fmod(ang, 360);
	return (ang);
}
