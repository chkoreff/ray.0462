typedef struct triple
	{
	double x;
	double y;
	double z;
	} triple;

extern triple color_rgb_xyz(triple color);
extern triple color_lab_xyz(triple color);
extern triple color_xyz_rgb(triple color);
extern triple color_lab_rgb(triple color);
