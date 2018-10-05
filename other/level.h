#ifndef LEVEL_H
#define LEVEL_H
typedef struct {
    int x;
    int y;
    int jump_mode;
    int moveleft_mode;
    int moveright_mode;
    Image *jump[6];
    int side;
} Pika;
extern void move_pika(Pika *rp);
extern void show_pika(Pika *rp);
extern void level1();
void level2();
void level3();
void level4();


#endif // LEVEL_H_INCLUDED
