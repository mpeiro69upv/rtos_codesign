
#ifndef INC_VGA_H_
#define INC_VGA_H_

void VGA_text(int x, int y, char * text_ptr, volatile char *character_buffer);
void VGA_box (int x1, int y1, int x2, int y2, short pixel_color, volatile short *pixel_buffer);
void VGA_Clean_Lines(int inicio, int lineas,volatile char *character_buffer);
void VGA_Clean_Full_Lines(int inicio, int lineas, volatile char *character_buffer);

#endif /* INC_VGA_H_ */

