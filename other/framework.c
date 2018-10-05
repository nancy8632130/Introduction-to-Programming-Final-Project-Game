#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>


#include "console_draw3.h"
#include "kb_input2.h"
#include "font.h"
#include "framework.h"

/*----------------------------------------------------------*/


int IsOnItem(Menu *m, int index)
{
    return (m->state[index] & 1); /* �Φ줸�B��ӧP�_�ثe��ܪ����� */
}
int IsItemSelected(Menu *m, int index)
{
    return (m->state[index] & 2);
}
void showMenu(Menu *m)
{
    int i;
    int fg;
    char *str;

    for (i=0; i< m->num_options; i++) {

        if ( !IsOnItem(m, i) ) {
            fg = m->fgcolor;
        } else {
            fg = m->bgcolor;
        }

        if ( !IsItemSelected(m, i) ) {
            str = m->text[i];
        } else {
            str = m->alt_text[i];
        }

        putStringLarge(m->large_font, (m->x)*(m->large_font->width+2),
            (m->y+i)*(m->large_font->height+2), str, fg);
    }
}

void scrollMenu(Menu *m, int diff)
{
    m->state[m->cursor] = m->state[m->cursor] & (~1);  /* ��ثe��ЩҦb���ﶵ���A�M�� */
    m->cursor = (m->cursor + diff + m->num_options) % m->num_options; /* ��C�в���U�@�ӿﶵ */
    m->state[m->cursor] = m->state[m->cursor] | 1; /* ��ܥثe��ЩҦb���ﶵ */
}

void radioMenu(Menu *m)
{
    int i;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = m->state[i] & (~2); /* �M���������ﶵ */
    }
    m->state[m->cursor] = m->state[m->cursor] | 2; /* �]�w�ثe��� */
}
void toggleMenu(Menu *m)
{
    m->state[m->cursor] = m->state[m->cursor] ^ 2;  /* �Q�Φ줸�B�� ���� toggle ���ĪG */
}



