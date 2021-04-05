/* GIMP RGB C-Source image dump (GRNBORDER.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[40 * 40 * 2 + 1];
} GRNBORDERIMAGE = {
  40, 40, 2,
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t"
  "*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t*t",
};

