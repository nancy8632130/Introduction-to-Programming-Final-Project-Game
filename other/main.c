#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "image.h"
#include "font.h"
#include "audio.h"
#include "framework.h"
#include "level.h"
#define WIDTH     30
#define HEIGHT    20
#define OFFSET_X  5
#define OFFSET_Y  5
#define NUM_KEYS 7
#define REFRESH_RATE 10
int timer(void);
void setMainmenu(Menu *m);
void setMainmenu3(Menu *m);
void setMainmenu2(Menu *m);
void setMainmenu4(Menu *m);
void setMainmenu5(Menu *m);
extern void putStringLarge(Font *fp, int x, int y, char *p, int color);
int start(void);
int end1(void);
int end2(void);
int end3(void);
int end4(void);
int end5(void);
void move_pika(Pika *rp);
void show_pika(Pika *rp);
int begin(void);
/* ******************************************************** */
int about(void){
    int IsEnding3 = 0;
    Font *large_font = read_font("font.txt");
    Menu mainmenu;
    Image* background1;
    background1 = read_image("­I´º11.pixel", "­I´º11.color");
    Audio audio;
    openAudioFile("Pikachu smstone.wav", &audio);
    setMainmenu3(&mainmenu);
    while (!IsEnding3) {
            clearScreen();
            show_image(background1, 0, 0);
            showMenu(&mainmenu);
            putStringLarge(large_font, 80, 35, "Game For Pika  Breakout clone", 12);
            putStringLarge(large_font, 90, 45, "left mouse button", 9);
            putStringLarge(large_font, 110, 55, "turn left", 11);
            putStringLarge(large_font, 90, 65, "right mouse button", 9);
            putStringLarge(large_font, 110, 75, "turn right", 11);
            drawCmdWindow();
            saveScreen();
            drawCmdWindow();
            if(KEY_DOWN(VK_RETURN)) {
                 clearScreen();
                 playAudio(&audio);
                 return 0;
            }
      }
      destroy_image(background1);
      return 0;
}
/* ******************************************************** */
int main(void)
{
    Menu mainmenu;
    initializeKeyInput();
    setMainmenu(&mainmenu);
    saveScreen();
    begin();
    return 0;
}
/* ****************************************************** */
void setMainmenu(Menu *m)
{
    int i;
    m->large_font = read_font("font.txt");
    m->x = 2;
    m->y = 2;
    m->fgcolor = 15;
    m->bgcolor = 13;
    m->num_options = 3;
    m->cursor = 0;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = 0;
    }
    m->state[m->cursor] = m->state[m->cursor] | 1;
    strcpy(m->text[0], "START");
    strcpy(m->text[1], "ABOUT");
    strcpy(m->text[2], "EXIT");
    strcpy(m->alt_text[0], "START");
    strcpy(m->alt_text[1], "ABOUT");
    strcpy(m->alt_text[2], "EXIT");
}
/*--------------------------------------------------------------*/
int begin(void)
{
    int IsEnding = 0,k,i=0,j=380,flag;
    char str[40] = {'\0'};
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_ESCAPE, VK_RETURN, VK_SPACE};
    Menu mainmenu;
    Image* background;
    background = read_image("­I´º6.pixel", "­I´º6.color");
    Audio audio;
    openAudioFile("Pikachu smstone.wav", &audio);
    initializeKeyInput();
    Image* pika;
    Image* pika1;
    Image* pika2;
    Image* pika3;
    pika = read_image("pi2.pixel", "pi2.color");
    pika1 = read_image("pi5.pixel", "pi5.color");
    pika2 = read_image("pi3.pixel", "pi3.color");
    pika3 = read_image("pi6.pixel", "pi6.color");
    setMainmenu(&mainmenu);
    saveScreen();
    while (!IsEnding) {
            clearScreen();
            restoreScreen();
            show_image(background, -80, 5);
            putStringLarge(mainmenu.large_font, OFFSET_X, OFFSET_Y-1, str, 14);
            if(i<380&&j==380)/*°Êµe*/
            {
                     flag =(flag+1)%2;
                     if(flag==0)
                            show_image(pika,0+i,90);
                     else
                            show_image(pika2,0+i,90);
                     i=i+10;
                     if(i==380)
                            j=0;
             }
              Sleep(300);
              if(i==380)
              {
                 flag =(flag+1)%2;
                 if(flag==0)
                     show_image(pika1,380-j,100);
                 else
                     show_image(pika3,380-j,100);
                j=j+10;
                if(j==380)
                     i=0;
              }
            showMenu(&mainmenu);
            drawCmdWindow();

        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_UP(key_val[k]) && key_down[k]) {
                key_down[k] = 0;
            }
        }
        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_DOWN(key_val[k]) && !key_down[k]) {
                key_down[k] = 1;

                switch (key_val[k]) {
                case VK_UP:
                    scrollMenu(&mainmenu, -1);
                    break;
                case VK_DOWN:
                    scrollMenu(&mainmenu, +1);
                    break;
                case VK_RETURN:
                       radioMenu(&mainmenu);
                        if (IsItemSelected(&mainmenu, 0)) {
                            playAudio(&audio);
                            clearScreen();
                            start();
                        }
                        if (IsItemSelected(&mainmenu, 1)) {
                            playAudio(&audio);
                            clearScreen();
                            about();
                        }
                        else if (IsOnItem(&mainmenu, 2)) {
                        radioMenu(&mainmenu);
                        IsEnding = 1;
                    }
                    break;
                }
            }
        }
    }
    destroy_image(background);
    destroy_image(pika1);
    destroy_image(pika);
    destroy_image(pika2);
    destroy_image(pika3);
    return 0;
}
/* ********************************************** */
int start(void)
{
    int k,IsEnding2 = 0;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_ESCAPE, VK_RETURN, VK_SPACE};
    Menu mainmenu;
    Image* background1;
    background1 = read_image("­I´º9.pixel", "­I´º9.color");
    Audio audio;
    openAudioFile("Pikachu smstone.wav", &audio);
    initializeKeyInput();
    setMainmenu2(&mainmenu);
    saveScreen();
    while (!IsEnding2) {
            clearScreen();
            restoreScreen();
            show_image(background1, 0, 0);
            radioMenu(&mainmenu);
            showMenu(&mainmenu);
            drawCmdWindow();
        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_UP(key_val[k]) && key_down[k]) {
                key_down[k] = 0;
            }
        }
        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_DOWN(key_val[k]) && !key_down[k]) {
                key_down[k] = 1;

                switch (key_val[k]) {
                case VK_UP:
                    scrollMenu(&mainmenu, -1);
                    break;
                case VK_DOWN:
                    scrollMenu(&mainmenu, +1);
                    break;
                case VK_RETURN:
                        if (IsItemSelected(&mainmenu, 0)) {
                            playAudio(&audio);
                            clearScreen();
                            level1();
                        }
                        if (IsItemSelected(&mainmenu, 1)) {
                            playAudio(&audio);
                            clearScreen();
                            level2();
                        }
                        if (IsItemSelected(&mainmenu, 2)) {
                            playAudio(&audio);
                            clearScreen();
                            level3();
                        }
                        if (IsItemSelected(&mainmenu, 3)) {
                            playAudio(&audio);
                            clearScreen();
                            level4();
                        }
                        if (IsItemSelected(&mainmenu, 4)) {
                            playAudio(&audio);
                           // level5();
                        }
                        else if (IsOnItem(&mainmenu, 5)) {
                        playAudio(&audio);
                        clearScreen();
                        return 0;
                    }
                    break;
                }
            }
        }
     }
    destroy_image(background1);
    return 0;
}
/* ************************************************ */
void setMainmenu2(Menu *m)
{
    int i;
    m->large_font = read_font("font.txt");
    m->x = 2;
    m->y = 1;
    m->fgcolor = 15;
    m->bgcolor = 13;
    m->num_options = 6;
    m->cursor = 0;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = 0;
    }
    m->state[m->cursor] = m->state[m->cursor] | 1;
    strcpy(m->text[0], "Level 1");
    strcpy(m->text[1], "Level 2");
    strcpy(m->text[2], "Level 3");
    strcpy(m->text[3], "Level 4");
    strcpy(m->text[4], "Level 5");
    strcpy(m->text[5], "RETURN");
    strcpy(m->alt_text[0], "Level 1");
    strcpy(m->alt_text[1], "Level 2");
    strcpy(m->alt_text[2], "Level 3");
    strcpy(m->alt_text[3], "Level 4");
    strcpy(m->alt_text[4], "Level 5");
    strcpy(m->alt_text[5], "RETURN");
}
/* ****************************************************** */
void setMainmenu3(Menu *m)
{
    int i;
    m->large_font = read_font("font.txt");
    m->x = 2;
    m->y = 2;
    m->fgcolor = 15;
    m->bgcolor = 13;
    m->num_options = 1;
    m->cursor = 0;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = 0;
    }
    m->state[m->cursor] = m->state[m->cursor] | 1;
    strcpy(m->text[0], "RETURN");
    strcpy(m->alt_text[0], "RETURN");
}
/* ****************************************************** */
int end1(void)
{
    int k;
    int IsEnding4 = 0;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_ESCAPE, VK_RETURN, VK_SPACE};
    Menu mainmenu;
    Image* background4;
    background4 = read_image("pikacry02.pixel", "pikacry02.color");
    Audio audio;
    openAudioFile("Pikachu smstone.wav", &audio);
    initializeKeyInput();
    setMainmenu4(&mainmenu);
    saveScreen();
    while (!IsEnding4) {
            clearScreen();
            restoreScreen();
            show_image(background4, 0, 0);
            radioMenu(&mainmenu);
            showMenu(&mainmenu);
            drawCmdWindow();
        for (k=0; k<NUM_KEYS; k++) {

           if(KEY_UP(key_val[k]) && key_down[k]) {
                key_down[k] = 0;
            }
        }
        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_DOWN(key_val[k]) && !key_down[k]) {
                key_down[k] = 1;

                switch (key_val[k]) {
                case VK_UP:
                    scrollMenu(&mainmenu, -1);
                    break;
                case VK_DOWN:
                    scrollMenu(&mainmenu, +1);
                    break;
                case VK_RETURN:
                        if (IsItemSelected(&mainmenu, 0)) {
                            playAudio(&audio);
                            clearScreen();
                            level1();
                        }
                        if (IsItemSelected(&mainmenu, 1)) {
                            playAudio(&audio);
                            clearScreen();
                            level2();
                        }
                        else if (IsOnItem(&mainmenu, 2)) {
                        playAudio(&audio);
                        clearScreen();
                        return 0;
                    }
                    break;
                }
            }
        }
     }
    destroy_image(background4);
    return 0;
}
/* **************************************************** */
void setMainmenu4(Menu *m)
{
    int i;
    m->large_font = read_font("font.txt");
    m->x = 2;
    m->y = 2;
    m->fgcolor = 15;
    m->bgcolor = 13;
    m->num_options = 3;
    m->cursor = 0;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = 0;
    }
    m->state[m->cursor] = m->state[m->cursor] | 1;
    strcpy(m->text[0], "PLAY AGAIN");
    strcpy(m->text[1], "NEXT LEVEL");
    strcpy(m->text[2], "MENU");
    strcpy(m->alt_text[0], "PLAY AGAIN");
    strcpy(m->alt_text[1], "NEXT LEVEL");
    strcpy(m->alt_text[2], "MENU");
}
/* **************************************************** */
void setMainmenu5(Menu *m)
{
    int i;
    m->large_font = read_font("font.txt");
    m->x = 2;
    m->y = 2;
    m->fgcolor = 15;
    m->bgcolor = 13;
    m->num_options = 3;
    m->cursor = 0;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = 0;
    }
    m->state[m->cursor] = m->state[m->cursor] | 1;
    strcpy(m->text[0], "PLAY AGAIN");
    strcpy(m->text[1], "NEXT LEVEL");
    strcpy(m->text[2], "MENU");
    strcpy(m->alt_text[0], "PLAY AGAIN");
    strcpy(m->alt_text[1], "NEXT LEVEL");
    strcpy(m->alt_text[2], "MENU");
}
/* ************************************************ */
int end2(void)
{
    int k;
    int IsEnding4 = 0;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_ESCAPE, VK_RETURN, VK_SPACE};
    Menu mainmenu;
    Image* background4;
    background4 = read_image("pikacry02.pixel", "pikacry02.color");
    Audio audio;
    openAudioFile("Pikachu smstone.wav", &audio);
    initializeKeyInput();
    setMainmenu4(&mainmenu);
    saveScreen();
    while (!IsEnding4) {
            clearScreen();
            restoreScreen();
            show_image(background4, 0, 0);
            radioMenu(&mainmenu);
            showMenu(&mainmenu);
            drawCmdWindow();
        for (k=0; k<NUM_KEYS; k++) {

           if(KEY_UP(key_val[k]) && key_down[k]) {
                key_down[k] = 0;
            }
        }
        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_DOWN(key_val[k]) && !key_down[k]) {
                key_down[k] = 1;

                switch (key_val[k]) {
                case VK_UP:
                    scrollMenu(&mainmenu, -1);
                    break;
                case VK_DOWN:
                    scrollMenu(&mainmenu, +1);
                    break;
                case VK_RETURN:
                        if (IsItemSelected(&mainmenu, 0)) {
                            playAudio(&audio);
                            clearScreen();
                            level2();
                        }
                        if (IsItemSelected(&mainmenu, 1)) {
                            playAudio(&audio);
                            clearScreen();
                            level3();
                        }
                        else if (IsOnItem(&mainmenu, 2)) {
                        playAudio(&audio);
                        clearScreen();
                        return 0;
                    }
                    break;
                }
            }
        }
     }
    destroy_image(background4);
    return 0;
}
/* *********************************************** */
int end3(void)
{
    int k;
    int IsEnding4 = 0;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_ESCAPE, VK_RETURN, VK_SPACE};
    Menu mainmenu;
    Image* background4;
    background4 = read_image("pikacry02.pixel", "pikacry02.color");
    Audio audio;
    openAudioFile("Pikachu smstone.wav", &audio);
    initializeKeyInput();
    setMainmenu4(&mainmenu);
    saveScreen();
    while (!IsEnding4) {
            clearScreen();
            restoreScreen();
            show_image(background4, 0, 0);
            radioMenu(&mainmenu);
            showMenu(&mainmenu);
            drawCmdWindow();
        for (k=0; k<NUM_KEYS; k++) {
           if(KEY_UP(key_val[k]) && key_down[k]) {
                key_down[k] = 0;
            }
        }
        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_DOWN(key_val[k]) && !key_down[k]) {
                key_down[k] = 1;

                switch (key_val[k]) {
                case VK_UP:
                    scrollMenu(&mainmenu, -1);
                    break;
                case VK_DOWN:
                    scrollMenu(&mainmenu, +1);
                    break;
                case VK_RETURN:
                        if (IsItemSelected(&mainmenu, 0)) {
                            playAudio(&audio);
                            clearScreen();
                            level3();
                        }
                        if (IsItemSelected(&mainmenu, 1)) {
                            playAudio(&audio);
                            clearScreen();
                            level4();
                        }
                        else if (IsOnItem(&mainmenu, 2)) {
                        playAudio(&audio);
                        clearScreen();
                        return 0;
                    }
                    break;
                }
            }
        }
     }
    destroy_image(background4);
    return 0;
}
/* ************************************************* */
int end4(void)
{
    int k;
    int IsEnding4 = 0;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_ESCAPE, VK_RETURN, VK_SPACE};
    Menu mainmenu;
    Image* background4;
    background4 = read_image("pikacry02.pixel", "pikacry02.color");
    Audio audio;
    openAudioFile("Pikachu smstone.wav", &audio);
    initializeKeyInput();
    setMainmenu4(&mainmenu);
    saveScreen();
    while (!IsEnding4) {
            clearScreen();
            restoreScreen();
            show_image(background4, 0, 0);
            radioMenu(&mainmenu);
            showMenu(&mainmenu);
            drawCmdWindow();
        for (k=0; k<NUM_KEYS; k++) {
           if(KEY_UP(key_val[k]) && key_down[k]) {
                key_down[k] = 0;
            }
        }
        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_DOWN(key_val[k]) && !key_down[k]) {
                key_down[k] = 1;

                switch (key_val[k]) {
                case VK_UP:
                    scrollMenu(&mainmenu, -1);
                    break;
                case VK_DOWN:
                    scrollMenu(&mainmenu, +1);
                    break;
                case VK_RETURN:
                        if (IsItemSelected(&mainmenu, 0)) {
                            playAudio(&audio);
                            clearScreen();
                            level4();
                        }
                        if (IsItemSelected(&mainmenu, 1)) {
                            playAudio(&audio);
                            clearScreen();
                            //level5();
                        }
                        else if (IsOnItem(&mainmenu, 2)) {
                        playAudio(&audio);
                        clearScreen();
                        return 0;
                    }
                    break;
                }
            }
        }
     }
    destroy_image(background4);
    return 0;
}

