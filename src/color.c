#include <color.h>
#include <raymath.h>

// LATER 20230409 Create test suites for color conversions.

static double scale_4117(double v)
	{
	v /= 255.0;
	if (v > 0.04045)
		v = pow((v+0.055)/1.055, 2.4);
	else
		v /= 12.92;

	return 100 * v;
	}

triple color_rgb_xyz(triple color)
	{
	double rx = color.x;
	double gx = color.y;
	double bx = color.z;

	double vr = scale_4117(rx);
	double vg = scale_4117(gx);
	double vb = scale_4117(bx);

	return (triple){ vr, vg, vb };
	}

static double scale_7761(double v)
	{
	double v3 = pow(v,3);
	if (v3 > 0.00856)
		return v3;
	else
		// LATER check this case, we never hit it.
		return (v - 16.0/116.0) / 7.787;
	}

triple color_lab_xyz(triple color)
	{
	double lx = color.x;
	double ax = color.y;
	double bx = color.z;

	double vy = (lx+16) / 116;
	double vx = vy + ax/500;
	double vz = vy - bx/200;

	vx = 94.811 * scale_7761(vx);
	vy = 100 * scale_7761(vy);
	vz = 107.304 * scale_7761(vz);

	return (triple){vx,vy,vz};
	}

static double scale_0813(double v)
	{
	if (v > 0.0031308)
		v = 1.055 * (pow(v,(1.0/2.4)) - 0.055);
	else
		v *= 12.92;

	return ceil(255 * v);
	}

triple color_xyz_rgb(triple color)
	{
	double xx = color.x;
	double yx = color.y;
	double zx = color.z;

	double vx = xx / 100;
	double vy = yx / 100;
	double vz = zx / 100;

	double vr = scale_0813((vx  * 3.2406) + (vy * -1.5372) + (vz * -0.4986));
	double vg = scale_0813((vx * -0.9689) + (vy *  1.8758) + (vz *  0.0415));
	double vb = scale_0813((vx *  0.0557) + (vy * -0.2040) + (vz *  1.0570));

	return (triple){ vr, vg, vb };
	}

triple color_lab_rgb(triple color)
	{
	return color_xyz_rgb(color_lab_xyz(color));
	}
