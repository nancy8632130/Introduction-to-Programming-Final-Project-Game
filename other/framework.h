#include "font.h"
#ifndef FRAMEWORK_
#define FRAMEWORK_
struct t_menu {
    int x;
    int y;
    int fgcolor;
    int bgcolor;
    int cursor;
    int num_options;
    int state[15];
    char text[15][30]; /* �̦h�s�Q�Ӧr��  �C�Ӧr����׳̦h 79 �Ӧr�� */
    char alt_text[15][30]; /* �̦h�s�Q�Ӧr��  �C�Ӧr����׳̦h 79 �Ӧr�� */
    Font *large_font;
};
typedef struct t_menu Menu;

extern void showMenu(Menu *m);


extern int IsOnItem(Menu *m, int index);
extern int IsItemSelected(Menu *m, int index);
extern int IsItemSelected2(Menu *m, int index);
extern void showMenu(Menu *m);
extern void scrollMenu(Menu *m, int diff);
extern void radioMenu(Menu *m);
extern void toggleMenu(Menu *m);


#endif

