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

void level1()
{
    int k;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_A, VK_S, VK_D, VK_ESCAPE};
    initializeKeyInput();
    Audio audio1;
    openAudioFile("song2.wav", &audio1);
    playAudio(&audio1);
    /*Audio sample*/
    Audio audio[3];
    openAudioFile("DR220A_CH.wav", &audio[0]);
    openAudioFile("DR220A_SD.wav", &audio[1]);
    openAudioFile("DR220A_HT.wav", &audio[2]);
    openMidi();
    /*
    Your code here
    In this part, you need to declare the string in logo , large font and read_image into a Image struct type
    */
    char logo[] = "Pikachu Breakout clone";
    Pika pika;
    pika.jump[0]=read_image("pi2.pixel","pi2.color");
    pika.jump[1]=read_image("pi3.pixel","pi3.color");
    pika.jump[2]=read_image("pi4.pixel","pi4.color");
    pika.jump[3]=read_image("pi5.pixel","pi5.color");
    pika.jump[4]=read_image("pi6.pixel","pi6.color");
    pika.jump[5]=read_image("pi7.pixel","pi7.color");
    pika.x = 180;
    pika.y = 100;
    pika.jump_mode=0;
    pika.moveleft_mode = 0;
    pika.moveright_mode = 0;
    pika.side=0;
    Font *large_font = read_font("font.txt");
    Image *grayblock = read_image("grayblock.pixel","grayblock.color");
    Image *blueblock = read_image("blueblock.pixel","blueblock.color");
    Image *redblock = read_image("redblock.pixel","redblock.color");
    Image *greenblock = read_image("greenblock.pixel","greenblock.color");
    Image *yellowblock = read_image("yellowblock.pixel","yellowblock.color");
    Image *whiteblock = read_image("whiteblock.pixel","whiteblock.color");
    Image *ball= read_image("ball.pixel","ball.color");
    int score=0;
    int x=180,y=95,a=1,b=-1,i,j;
    int arrayblock1[4][9];
    for(i=0;i<4;i++){
        for(j=0;j<9;j++){
            arrayblock1[i][j]=1;
        }
    }

    while (1)
    {
       for (k = 0 ; k < NUM_KEYS ; k++)
        {
            // 按鍵處在被按下的狀態  把這個事件記錄在key_down[k] //
            if(KEY_DOWN(key_val[k]) && !key_down[k])//
            {
                key_down[k] = 1;//
                // 在這個例子裡 按下 A, S, D會撥放不同音效//

                switch (key_val[k])//
                {
                case VK_A:
                    // 播放對應的音效 //
                    playAudio(&audio[0]);
                    break;
                case VK_S:
                    // 播放對應的音效 //
                    playAudio(&audio[1]);
                    break;
                case VK_D:
                    // 播放對應的音效 //
                    playAudio(&audio[2]);
                 break;
            }
            }
            //按鍵從原本被按下的狀態,變成放開的狀態//
            if(KEY_UP(key_val[k]) && key_down[k])
            {
                key_down[k] = 0;
           }
        }

        /* Your code here
        In this part, you need to show_image, and putString
        */
        if (KEY_DOWN(VK_LEFT)) {
            if (pika.moveleft_mode==0)
                pika.moveleft_mode = 1;
            pika.side=3;
        }
        if (KEY_DOWN(VK_RIGHT)) {
            if (pika.moveright_mode==0)
                pika.moveright_mode = 1;
            pika.side=0;
        }
        if (KEY_DOWN(VK_SPACE)) {
            playMidi(0, 72, 100);
        }

        clearScreen();
        //putString(0,0,logo,15,3);
        char score_c[3];
        //score_c = _itoa_s(score,score_c,sizeof(score_c),10);
        score_c[0]=(score%10)+'0';
        score_c[1]=(score-score%10)+'0';
        putStringLarge(large_font, 10, 1, logo, 9);
        putStringLarge(large_font, 100, 110, score_c, 9);
        //flag = (flag+1)%2;
        //if(flag==0)
        //else
    /*level1*/
        /*邊界*/
        show_image(grayblock,0,0);
        show_image(grayblock,0,42);
        show_image(grayblock,0,84);
        show_image(grayblock,0,126);
        show_image(grayblock,343,0);
        show_image(grayblock,343,42);
        show_image(grayblock,343,84);
        show_image(grayblock,343,126);
        int i,j;
        for (i=0;i<4;i++)
        {
            for (j=0;j<9;j++)
            {
                if (arrayblock1[i][j]==1)
                {
                    if ((i*9+j)%5==0)
                        show_image(redblock,30+j*33,31-i*7);
                    if ((i*9+j)%5==1)
                        show_image(greenblock,30+j*33,31-i*7);
                    if ((i*9+j)%5==2)
                        show_image(yellowblock,30+j*33,31-i*7);
                    if ((i*9+j)%5==3)
                        show_image(whiteblock,30+j*33,31-i*7);
                    if ((i*9+j)%5==4)
                        show_image(blueblock,30+j*33,31-i*7);
                }

            }
        }
        x=x+a;
        y=y+b;

        if(y>105)break;
        if(y-5==32||y+5==32){
            if(x>=30&&x<63){
                    if(arrayblock1[0][0]!=0){
                        arrayblock1[0][0]=0; b=b*-1;
                        score=score+1;
                    }
            }
            else if(x>=63&&x<96){
                    if(arrayblock1[0][1]!=0){
                        arrayblock1[0][1]=0; b=b*-1;
                        score=score+1;
                    }
            }
            else if(x>=96&&x<129){
                    if(arrayblock1[0][2]!=0){
                        arrayblock1[0][2]=0;  b=b*-1;
                        score=score+1;
                    }
            }
            else if(x>=129&&x<162){
                    if(arrayblock1[0][3]!=0){
                        arrayblock1[0][3]=0;  b=b*-1;
                        score=score+1;
                    }
            }
            else if(x>=162&&x<195){
                if(arrayblock1[0][4]!=0){
                    arrayblock1[0][4]=0;  b=b*-1;
                    score=score+1;
                }
            }
            else if(x>=195&&x<228){
                if(arrayblock1[0][5]!=0){
                    arrayblock1[0][5]=0;  b=b*-1;
                    score=score+1;
                }
            }
            else if(x>=228&&x<261){
                if(arrayblock1[0][6]!=0){
                    arrayblock1[0][6]=0;  b=b*-1;
                    score=score+1;
                }
            }
            else if(x>=261&&x<294){
                if(arrayblock1[0][7]!=0){
                    arrayblock1[0][7]=0;  b=b*-1;
                    score=score+1;
                }
            }
            else if(x>=294&&x<327){
                if(arrayblock1[0][8]!=0){
                    arrayblock1[0][8]=0;  b=b*-1;
                    score=score+1;
                }
            }
            else if(x>=327&&x<360){
                if(arrayblock1[0][9]!=0){
                    arrayblock1[0][9]=0;  b=b*-1;
                    score=score+1;
                }
            }
        }
        if(y-5==25||y+5==25){
            if(x>=30&&x<63){
                if(arrayblock1[1][0]!=0){
                    arrayblock1[1][0]=0; b=b*-1;
                    score=score+1;
                }
            }
            else if(x>=63&&x<96){
            if(arrayblock1[1][1]!=0){
                arrayblock1[1][1]=0; b=b*-1;
                score=score+1;
                }
            }
            else if(x>=96&&x<129){
                if(arrayblock1[1][2]!=0){
                    arrayblock1[1][2]=0;  b=b*-1;
                    score=score+1;
                }
            }
            else if(x>=129&&x<162){
                if(arrayblock1[1][3]!=0){
                    arrayblock1[1][3]=0;  b=b*-1;
                    score=score+1;
                }
            }
            else if(x>=162&&x<195){
                if(arrayblock1[1][4]!=0){
                    arrayblock1[1][4]=0;  b=b*-1;
                    score=score+1;
                }
            }
            else if(x>=195&&x<228){
                if(arrayblock1[1][5]!=0){
                    arrayblock1[1][5]=0;  b=b*-1;
                    score=score+1;
                }
            }
           else if(x>=228&&x<261){
                if(arrayblock1[1][6]!=0){
                    arrayblock1[1][6]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=261&&x<294){
                if(arrayblock1[1][7]!=0){
                    arrayblock1[1][7]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=294&&x<327){
                if(arrayblock1[1][8]!=0){
                    arrayblock1[1][8]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=327&&x<36){
                if(arrayblock1[1][9]!=0){
                    arrayblock1[1][9]=0;  b=b*-1;
                    score=score+1;
                    }
            }

        }
        if(y-5==18||y+5==18){
            if(x>=30&&x<63){
                if(arrayblock1[2][0]!=0){
                        arrayblock1[2][0]=0; b=b*-1;
                        score=score+1;
                }
            }
            else if(x>=63&&x<96){
                    if(arrayblock1[2][1]!=0){
                        arrayblock1[2][1]=0; b=b*-1;
                        score=score+1;
                    }
            }
            else if(x>=96&&x<129){
                    if(arrayblock1[2][2]!=0){
                        arrayblock1[2][2]=0;  b=b*-1;
                        score=score+1;
                    }
            }
            else if(x>=129&&x<162){
                    if(arrayblock1[2][3]!=0){
                        arrayblock1[2][3]=0;  b=b*-1;
                        score=score+1;
                    }
            }
            else if(x>=162&&x<195){
                if(arrayblock1[2][4]!=0){
                        arrayblock1[2][4]=0;  b=b*-1;
                        score=score+1;
                }
            }
            else if(x>=195&&x<228){
                    if(arrayblock1[2][5]!=0){
                        arrayblock1[2][5]=0;  b=b*-1;
                        score=score+1;
                    }
            }
            else if(x>=228&&x<261){
                    if(arrayblock1[2][6]!=0){
                            arrayblock1[2][6]=0;  b=b*-1;
                            score=score+1;
                    }
            }
            else if(x>=261&&x<294){
                    if(arrayblock1[2][7]!=0){
                            arrayblock1[2][7]=0;  b=b*-1;
                            score=score+1;
                    }
            }
            else if(x>=294&&x<327){
                    if(arrayblock1[2][8]!=0){
                            arrayblock1[2][8]=0;  b=b*-1;
                            score=score+1;
                    }
            }
               else if(x>=327&&x<360){
                    if(arrayblock1[2][9]!=0){
                            arrayblock1[2][9]=0;  b=b*-1;
                            score=score+1;
                    }
            }
        }
        if(y-5==11||y+5==11){
            if(x>=30&&x<63){
                    if(arrayblock1[3][0]!=0){
                        arrayblock1[3][0]=0; b=b*-1;
                        score=score+1;
                        }
                }
            else if(x>=63&&x<96){
                if(arrayblock1[3][1]!=0){
                    arrayblock1[3][1]=0; b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=96&&x<129){
                if(arrayblock1[3][2]!=0){
                    arrayblock1[3][2]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=129&&x<162){
                if(arrayblock1[3][3]!=0){
                    arrayblock1[3][3]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=162&&x<195){
                if(arrayblock1[3][4]!=0){
                    arrayblock1[3][4]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=195&&x<228){
                if(arrayblock1[3][5]!=0){
                    arrayblock1[3][5]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=228&&x<261){
                if(arrayblock1[3][6]!=0){
                    arrayblock1[3][6]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=261&&x<294){
                if(arrayblock1[3][7]!=0){
                    arrayblock1[3][7]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=294&&x<327){
                if(arrayblock1[3][8]!=0){
                    arrayblock1[3][8]=0;  b=b*-1;
                    score=score+1;
                    }
            }
            else if(x>=327&&x<360){
                if(arrayblock1[3][9]!=0){
                    arrayblock1[3][9]=0;  b=b*-1;
                    score=score+1;
                    }
            }
        }
        if ((x<=pika.x+15&&x>=pika.x+5)&&(y<=pika.y&&y>pika.y-10)&&b>0&&a<0)
        {
            b=-b;
            a=-a;
        }

        if ((x>=pika.x-15&&x<pika.x+5)&&(y<=pika.y&&y>pika.y-10)&&b>0&&a>0)
        {
            b=-b;
            a=-a;
        }
        if ((x<=pika.x+20&&x>=pika.x)&&(y<=pika.y&&y>pika.y-10)&&b>0&&a>=0)
            b=-b;
        if ((x>=pika.x-15&&x<pika.x)&&(y<=pika.y&&y>pika.y-10)&&b>0&&a<=0)
            b=-b;
        show_image(ball,x,y);
        if(x==0||x==330)a=a*-1;
        if (y==1) b=-b;
        show_pika(&pika);
        drawCmdWindow();
        move_pika(&pika);
        Sleep(10);

}
pauseAudio(&audio1);
end1();
destroy_image(grayblock);
        destroy_image(blueblock);
        destroy_image(redblock);
        destroy_image(greenblock);
        destroy_image(yellowblock);
        destroy_image(whiteblock);
        destroy_image(ball);
        destroy_image(pika.jump[0]);
        destroy_image(pika.jump[1]);
        destroy_image(pika.jump[2]);
        destroy_image(pika.jump[3]);
}
void level2()
{
    int k;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_A, VK_S, VK_D, VK_ESCAPE};
    initializeKeyInput();
    Audio audio1;
    openAudioFile("song2.wav", &audio1);
    playAudio(&audio1);
    /*Audio sample*/
    Audio audio[3];
    openAudioFile("DR220A_CH.wav", &audio[0]);
    openAudioFile("DR220A_SD.wav", &audio[1]);
    openAudioFile("DR220A_HT.wav", &audio[2]);
    openMidi();
    /*
    Your code here
    In this part, you need to declare the string in logo , large font and read_image into a Image struct type
    */
    Pika pika;
    pika.jump[0]=read_image("pi2.pixel","pi2.color");
    pika.jump[1]=read_image("pi3.pixel","pi3.color");
    pika.jump[2]=read_image("pi4.pixel","pi4.color");
    pika.jump[3]=read_image("pi5.pixel","pi5.color");
    pika.jump[4]=read_image("pi6.pixel","pi6.color");
    pika.jump[5]=read_image("pi7.pixel","pi7.color");
    pika.x = 180;
    pika.y = 100;
    pika.jump_mode=0;
    pika.moveleft_mode = 0;
    pika.moveright_mode = 0;
    pika.side=0;
    Font *large_font = read_font("font.txt");
    Image *grayblock = read_image("grayblock.pixel","grayblock.color");
    Image *blueblock = read_image("blueblock.pixel","blueblock.color");
    Image *redblock = read_image("redblock.pixel","redblock.color");
    Image *greenblock = read_image("greenblock.pixel","greenblock.color");
    Image *yellowblock = read_image("yellowblock.pixel","yellowblock.color");
    Image *whiteblock = read_image("whiteblock.pixel","whiteblock.color");
    Image *ball= read_image("ball.pixel","ball.color");
    int x=180,y=94,a=2,b=-2,i,j;
    int arrayblock2[5][9];
    for(i=0;i<5;i++){
        for(j=0;j<9;j++){
            arrayblock2[i][j]=1;
        }
    }

    while (1)
    {
       for (k = 0 ; k < NUM_KEYS ; k++)
        {
            // 按鍵處在被按下的狀態  把這個事件記錄在key_down[k] //
            if(KEY_DOWN(key_val[k]) && !key_down[k])//
            {
                key_down[k] = 1;//
                // 在這個例子裡 按下 A, S, D會撥放不同音效//

                switch (key_val[k])//
                {
                case VK_A:
                    // 播放對應的音效 //
                    playAudio(&audio[0]);
                    break;
                case VK_S:
                    // 播放對應的音效 //
                    playAudio(&audio[1]);
                    break;
                case VK_D:
                    // 播放對應的音效 //
                    playAudio(&audio[2]);
                 break;
            }
            }
            //按鍵從原本被按下的狀態,變成放開的狀態//
            if(KEY_UP(key_val[k]) && key_down[k])
            {
                key_down[k] = 0;
           }
        }

        /* Your code here
        In this part, you need to show_image, and putString
        */
        if (KEY_DOWN(VK_LEFT)) {
            if (pika.moveleft_mode==0)
                pika.moveleft_mode = 1;
            pika.side=3;
        }
        if (KEY_DOWN(VK_RIGHT)) {
            if (pika.moveright_mode==0)
                pika.moveright_mode = 1;
            pika.side=0;
        }
        if (KEY_DOWN(VK_SPACE)) {
            pika.jump_mode = 1;
            playMidi(0, 72, 100);
        }

        clearScreen();
        //putString(0,0,logo,15,3);
        putStringLarge(large_font, 10, 1, "pikachu Breakout clone", 9);
        //flag = (flag+1)%2;
        //if(flag==0)
        //else
    /*level2*/
        /*邊界*/
        show_image(grayblock,0,0);
        show_image(grayblock,0,42);
        show_image(grayblock,0,84);
        show_image(grayblock,0,126);
        show_image(grayblock,343,0);
        show_image(grayblock,343,42);
        show_image(grayblock,343,84);
        show_image(grayblock,343,126);

        /*第一排*/
        if(arrayblock2[4][0]==1)show_image(blueblock,150,10);
        /*第二排*/
        if(arrayblock2[3][0]==1)show_image(whiteblock,117,17);
        if(arrayblock2[3][1]==1)show_image(yellowblock,150,17);
        if(arrayblock2[3][2]==1)show_image(redblock,183,17);
        /*第三排*/
        if(arrayblock2[2][0]==1)show_image(yellowblock,51,24);
        if(arrayblock2[2][1]==1)show_image(blueblock,84,24);
        if(arrayblock2[2][2]==1)show_image(redblock,117,24);
        if(arrayblock2[2][3]==1)show_image(greenblock,150,24);
        if(arrayblock2[2][4]==1)show_image(yellowblock,183,24);
        if(arrayblock2[2][5]==1)show_image(whiteblock,216,24);
        if(arrayblock2[2][6]==1)show_image(blueblock,249,24);
        /*第四排*/
        if(arrayblock2[1][0]==1)show_image(greenblock,117,31);
        if(arrayblock2[1][1]==1)show_image(yellowblock,150,31);
        if(arrayblock2[1][2]==1)show_image(blueblock,183,31);;
        /*第五排*/
        if(arrayblock2[0][0]==1)show_image(whiteblock,150,38);
        /*ball*/
        x=x+a;
        y=y+b;

        if(y>105)break;
        if(y==38){
            if(x>=150&&x<184){
                    if(arrayblock2[0][0]!=0){
                        arrayblock2[0][0]=0; b=b*-1;
                    }
            }
        }
        if(y==32){
            if(x>=116&&x<150){
                if(arrayblock2[1][0]!=0){
                    arrayblock2[1][0]=0; b=b*-1;
                }
            }
            else if(x>=150&&x<184){
            if(arrayblock2[1][1]!=0){
                arrayblock2[1][1]=0; b=b*-1;
                }
            }
            else if(x>=184&&x<=216){
                if(arrayblock2[1][2]!=0){
                    arrayblock2[1][2]=0;  b=b*-1;
                }
            }
        }
        if(y==24){
            if(x>=50&&x<84){
                if(arrayblock2[2][0]!=0){
                        arrayblock2[2][0]=0; b=b*-1;
                }
            }
            else if(x>=84&&x<117){
                    if(arrayblock2[2][1]!=0){
                        arrayblock2[2][1]=0; b=b*-1;
                    }
            }
            else if(x>=117&&x<150){
                    if(arrayblock2[2][2]!=0){
                        arrayblock2[2][2]=0;  b=b*-1;
                    }
            }
            else if(x>=150&&x<183){
                    if(arrayblock2[2][3]!=0){
                        arrayblock2[2][3]=0;  b=b*-1;
                    }
            }
            else if(x>=183&&x<216){
                if(arrayblock2[2][4]!=0){
                        arrayblock2[2][4]=0;  b=b*-1;
                }
            }
            else if(x>=216&&x<249){
                    if(arrayblock2[2][5]!=0){
                        arrayblock2[2][5]=0;  b=b*-1;
                    }
            }
            else if(x>=249&&x<282){
                    if(arrayblock2[2][6]!=0){
                            arrayblock2[2][6]=0;  b=b*-1;
                    }
            }
        }
        if(y==18){
            if(x>=117&&x<150){
                    if(arrayblock2[3][0]!=0){
                        arrayblock2[3][0]=0; b=b*-1;
                        }
                }
            else if(x>=150&&x<183){
                if(arrayblock2[3][1]!=0){
                    arrayblock2[3][1]=0; b=b*-1;
                    }
            }
            else if(x>=183&&x<216){
                if(arrayblock2[3][2]!=0){
                    arrayblock2[3][2]=0;  b=b*-1;
                    }
            }
        }
        if(y==10){
            if(x>=150&&x<183){
                if(arrayblock2[4][0]!=0){
                    arrayblock2[4][0]=0; b=b*-1;
                }
            }
        }
        if ((x<=pika.x+15&&x>pika.x+5)&&(y<=pika.y&&y>pika.y-10)&&b>0)
            b=-b;
        if ((x>pika.x-15&&x<pika.x+5)&&(y<=pika.y&&y>pika.y-10)&&b>0)
        {
            b=-b;
            a=-a;
        }
        show_image(ball,x,y);
        if(x==0||x==340)a=a*-1;
        if (y==0) b=-b;
        show_pika(&pika);
        drawCmdWindow();
        move_pika(&pika);

        Sleep(30);
    }
    pauseAudio(&audio1);
    end2();
    destroy_image(grayblock);
    destroy_image(blueblock);
    destroy_image(redblock);
    destroy_image(greenblock);
    destroy_image(yellowblock);
    destroy_image(whiteblock);
    destroy_image(ball);
    destroy_image(pika.jump[0]);
    destroy_image(pika.jump[1]);
    destroy_image(pika.jump[2]);
    destroy_image(pika.jump[3]);
    return ;
}
void level3()
{
    int k;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_A, VK_S, VK_D, VK_ESCAPE};
    initializeKeyInput();
    Audio audio1;
    openAudioFile("song2.wav", &audio1);
    playAudio(&audio1);
    /*Audio sample*/
    Audio audio[3];
    openAudioFile("DR220A_CH.wav", &audio[0]);
    openAudioFile("DR220A_SD.wav", &audio[1]);
    openAudioFile("DR220A_HT.wav", &audio[2]);
    openMidi();
    /*
    Your code here
    In this part, you need to declare the string in logo , large font and read_image into a Image struct type
    */
    Pika pika;
    pika.jump[0]=read_image("pi2.pixel","pi2.color");
    pika.jump[1]=read_image("pi3.pixel","pi3.color");
    pika.jump[2]=read_image("pi4.pixel","pi4.color");
    pika.jump[3]=read_image("pi5.pixel","pi5.color");
    pika.jump[4]=read_image("pi6.pixel","pi6.color");
    pika.jump[5]=read_image("pi7.pixel","pi7.color");
    pika.x = 180;
    pika.y = 100;
    pika.jump_mode=0;
    pika.moveleft_mode = 0;
    pika.moveright_mode = 0;
    pika.side=0;
    Font *large_font = read_font("font.txt");
    Image *grayblock = read_image("grayblock.pixel","grayblock.color");
    Image *blueblock = read_image("blueblock.pixel","blueblock.color");
    Image *redblock = read_image("redblock.pixel","redblock.color");
    Image *greenblock = read_image("greenblock.pixel","greenblock.color");
    Image *yellowblock = read_image("yellowblock.pixel","yellowblock.color");
    Image *whiteblock = read_image("whiteblock.pixel","whiteblock.color");
    Image *ball= read_image("ball.pixel","ball.color");
    int x=180,y=94,a=2,b=-2,i,j;
    int arrayblock3[5][9];
    for(i=0;i<5;i++){
        for(j=0;j<9;j++){
            arrayblock3[i][j]=1;
        }
    }

    while (1)
    {
       for (k = 0 ; k < NUM_KEYS ; k++)
        {
            // 按鍵處在被按下的狀態  把這個事件記錄在key_down[k] //
            if(KEY_DOWN(key_val[k]) && !key_down[k])//
            {
                key_down[k] = 1;//
                // 在這個例子裡 按下 A, S, D會撥放不同音效//

                switch (key_val[k])//
                {
                case VK_A:
                    // 播放對應的音效 //
                    playAudio(&audio[0]);
                    break;
                case VK_S:
                    // 播放對應的音效 //
                    playAudio(&audio[1]);
                    break;
                case VK_D:
                    // 播放對應的音效 //
                    playAudio(&audio[2]);
                 break;
            }
            }
            //按鍵從原本被按下的狀態,變成放開的狀態//
            if(KEY_UP(key_val[k]) && key_down[k])
            {
                key_down[k] = 0;
           }
        }

        /* Your code here
        In this part, you need to show_image, and putString
        */
        if (KEY_DOWN(VK_LEFT)) {
            if (pika.moveleft_mode==0)
                pika.moveleft_mode = 1;
            pika.side=3;
        }
        if (KEY_DOWN(VK_RIGHT)) {
            if (pika.moveright_mode==0)
                pika.moveright_mode = 1;
            pika.side=0;
        }
        if (KEY_DOWN(VK_SPACE)) {
            pika.jump_mode = 1;
            playMidi(0, 72, 100);
        }

        clearScreen();
        //putString(0,0,logo,15,3);
        putStringLarge(large_font, 10, 1, "pikachu Breakout clone", 9);
        //flag = (flag+1)%2;
        //if(flag==0)
        //else
    /*level3*/
        /*邊界*/
        show_image(grayblock,0,0);
        show_image(grayblock,0,42);
        show_image(grayblock,0,84);
        show_image(grayblock,0,126);
        show_image(grayblock,343,0);
        show_image(grayblock,343,42);
        show_image(grayblock,343,84);
        show_image(grayblock,343,126);

        /*第一排*/
        if(arrayblock3[4][0]==1)show_image(yellowblock,51,10);
        if(arrayblock3[4][1]==1)show_image(blueblock,84,10);
        if(arrayblock3[4][2]==1)show_image(redblock,117,10);
        if(arrayblock3[4][3]==1)show_image(greenblock,150,10);
        if(arrayblock3[4][4]==1)show_image(yellowblock,183,10);
        if(arrayblock3[4][5]==1)show_image(whiteblock,216,10);
        if(arrayblock3[4][6]==1)show_image(blueblock,249,10);
        /*第二排*/
        if(arrayblock3[3][0]==1)show_image(whiteblock,117,17);
        if(arrayblock3[3][1]==1)show_image(yellowblock,150,17);
        if(arrayblock3[3][2]==1)show_image(redblock,183,17);
        /*第三排*/
        if(arrayblock3[2][0]==1)show_image(blueblock,150,24);
        /*第四排*/
        if(arrayblock3[1][0]==1)show_image(greenblock,117,31);
        if(arrayblock3[1][1]==1)show_image(yellowblock,150,31);
        if(arrayblock3[1][2]==1)show_image(blueblock,183,31);;
        /*第五排*/
        if(arrayblock3[0][0]==1)show_image(yellowblock,51,38);
        if(arrayblock3[0][1]==1)show_image(blueblock,84,38);
        if(arrayblock3[0][2]==1)show_image(redblock,117,38);
        if(arrayblock3[0][3]==1)show_image(greenblock,150,38);
        if(arrayblock3[0][4]==1)show_image(yellowblock,183,38);
        if(arrayblock3[0][5]==1)show_image(whiteblock,216,38);
        if(arrayblock3[0][6]==1)show_image(blueblock,249,38);
        /*ball*/
        x=x+a;
        y=y+b;

        if(y>105)break;
        if(y==38){
            if(x>=51&&x<84){
                    if(arrayblock3[0][0]!=0){
                        arrayblock3[0][0]=0; b=b*-1;
                    }
            }
            else if(x>=84&&x<117){
                    if(arrayblock3[0][1]!=0){
                        arrayblock3[0][1]=0; b=b*-1;
                    }
            }
            else if(x>=117&&x<150){
                    if(arrayblock3[0][2]!=0){
                        arrayblock3[0][2]=0; b=b*-1;
                    }
            }
            else if(x>=150&&x<184){
                    if(arrayblock3[0][3]!=0){
                        arrayblock3[0][3]=0; b=b*-1;
                    }
            }
            else if(x>=184&&x<216){
                    if(arrayblock3[0][4]!=0){
                        arrayblock3[0][4]=0; b=b*-1;
                    }
            }
            else if(x>=216&&x<249){
                    if(arrayblock3[0][5]!=0){
                        arrayblock3[0][5]=0; b=b*-1;
                    }
            }
            else if(x>=249&&x<282){
                    if(arrayblock3[0][6]!=0){
                        arrayblock3[0][6]=0; b=b*-1;
                    }
            }
        }
        if(y==32){
            if(x>=116&&x<150){
                if(arrayblock3[1][0]!=0){
                    arrayblock3[1][0]=0; b=b*-1;
                }
            }
            else if(x>=150&&x<184){
                if(arrayblock3[1][1]!=0){
                    arrayblock3[1][1]=0; b=b*-1;
                }
            }
            else if(x>=184&&x<=216){
                if(arrayblock3[1][2]!=0){
                    arrayblock3[1][2]=0;  b=b*-1;
                }
            }
        }
        if(y==24){
            if(x>=150&&x<183){
                if(arrayblock3[2][0]!=0){
                        arrayblock3[2][0]=0; b=b*-1;
                }
            }
        }
        if(y==18){
            if(x>=117&&x<150){
                    if(arrayblock3[3][0]!=0){
                        arrayblock3[3][0]=0; b=b*-1;
                        }
                }
            else if(x>=150&&x<183){
                if(arrayblock3[3][1]!=0){
                    arrayblock3[3][1]=0; b=b*-1;
                    }
            }
            else if(x>=183&&x<216){
                if(arrayblock3[3][2]!=0){
                    arrayblock3[3][2]=0;  b=b*-1;
                    }
            }
        }
        if(y==10){
            if(x>=51&&x<84){
                if(arrayblock3[4][0]!=0){
                    arrayblock3[4][0]=0; b=b*-1;
                }
            }
            else if(x>=84&&x<117){
                if(arrayblock3[4][1]!=0){
                    arrayblock3[4][1]=0; b=b*-1;
                }
            }
            else if(x>=117&&x<150){
                if(arrayblock3[4][2]!=0){
                    arrayblock3[4][2]=0; b=b*-1;
                }
            }
            else if(x>=150&&x<183){
                if(arrayblock3[4][3]!=0){
                    arrayblock3[4][3]=0; b=b*-1;
                }
            }
            else if(x>=183&&x<216){
                if(arrayblock3[4][4]!=0){
                    arrayblock3[4][4]=0; b=b*-1;
                }
            }
            else if(x>=216&&x<249){
                if(arrayblock3[4][5]!=0){
                    arrayblock3[4][5]=0; b=b*-1;
                }
            }
            else if(x>=249&&x<282){
                if(arrayblock3[4][6]!=0){
                    arrayblock3[4][6]=0; b=b*-1;
                }
            }
        }
        if ((x<=pika.x+15&&x>pika.x+5)&&(y<=pika.y&&y>pika.y-10)&&b>0)
            b=-b;
        if ((x>pika.x-15&&x<pika.x+5)&&(y<=pika.y&&y>pika.y-10)&&b>0)
        {
            b=-b;
            a=-a;
        }
        show_image(ball,x,y);
        if(x==0||x==340)a=a*-1;
        if (y==0) b=-b;
        show_pika(&pika);
        drawCmdWindow();
        move_pika(&pika);

        Sleep(25);
    }
    pauseAudio(&audio1);
    end3();
    destroy_image(grayblock);
    destroy_image(blueblock);
    destroy_image(redblock);
    destroy_image(greenblock);
    destroy_image(yellowblock);
    destroy_image(whiteblock);
    destroy_image(ball);
    destroy_image(pika.jump[0]);
    destroy_image(pika.jump[1]);
    destroy_image(pika.jump[2]);
    destroy_image(pika.jump[3]);
    return ;
}
/* ************************************************** */
void level4()
{
    int k;
    int key_down[NUM_KEYS] = {0};
    int key_val[NUM_KEYS] = {VK_A, VK_S, VK_D, VK_ESCAPE};
    initializeKeyInput();
    Audio audio1;
    openAudioFile("song2.wav", &audio1);
    playAudio(&audio1);
    /*Audio sample*/
    Audio audio[3];
    openAudioFile("DR220A_CH.wav", &audio[0]);
    openAudioFile("DR220A_SD.wav", &audio[1]);
    openAudioFile("DR220A_HT.wav", &audio[2]);
    openMidi();
    /*
    Your code here
    In this part, you need to declare the string in logo , large font and read_image into a Image struct type
    */
    Pika pika;
    pika.jump[0]=read_image("pi2.pixel","pi2.color");
    pika.jump[1]=read_image("pi3.pixel","pi3.color");
    pika.jump[2]=read_image("pi4.pixel","pi4.color");
    pika.jump[3]=read_image("pi5.pixel","pi5.color");
    pika.jump[4]=read_image("pi6.pixel","pi6.color");
    pika.jump[5]=read_image("pi7.pixel","pi7.color");
    pika.x = 180;
    pika.y = 100;
    pika.jump_mode=0;
    pika.moveleft_mode = 0;
    pika.moveright_mode = 0;
    pika.side=0;
    Font *large_font = read_font("font.txt");
    Image *grayblock = read_image("grayblock.pixel","grayblock.color");
    Image *blueblock = read_image("blueblock.pixel","blueblock.color");
    Image *redblock = read_image("redblock.pixel","redblock.color");
    Image *greenblock = read_image("greenblock.pixel","greenblock.color");
    Image *yellowblock = read_image("yellowblock.pixel","yellowblock.color");
    Image *whiteblock = read_image("whiteblock.pixel","whiteblock.color");
    Image *ball= read_image("ball.pixel","ball.color");
    int x=180,y=94,a=2,b=-2,i,j;
    int arrayblock4[7][9];
    for(i=0;i<7;i++){
        for(j=0;j<9;j++){
            arrayblock4[i][j]=1;
        }
    }

    while (1)
    {
       for (k = 0 ; k < NUM_KEYS ; k++)
        {
            // 按鍵處在被按下的狀態  把這個事件記錄在key_down[k] //
            if(KEY_DOWN(key_val[k]) && !key_down[k])//
            {
                key_down[k] = 1;//
                // 在這個例子裡 按下 A, S, D會撥放不同音效//

                switch (key_val[k])//
                {
                case VK_A:
                    // 播放對應的音效 //
                    playAudio(&audio[0]);
                    break;
                case VK_S:
                    // 播放對應的音效 //
                    playAudio(&audio[1]);
                    break;
                case VK_D:
                    // 播放對應的音效 //
                    playAudio(&audio[2]);
                 break;
            }
            }
            //按鍵從原本被按下的狀態,變成放開的狀態//
            if(KEY_UP(key_val[k]) && key_down[k])
            {
                key_down[k] = 0;
           }
        }

        /* Your code here
        In this part, you need to show_image, and putString
        */
        if (KEY_DOWN(VK_LEFT)) {
            if (pika.moveleft_mode==0)
                pika.moveleft_mode = 1;
            pika.side=3;
        }
        if (KEY_DOWN(VK_RIGHT)) {
            if (pika.moveright_mode==0)
                pika.moveright_mode = 1;
            pika.side=0;
        }
        if (KEY_DOWN(VK_SPACE)) {
            pika.jump_mode = 1;
            playMidi(0, 72, 100);
        }

        clearScreen();
        //putString(0,0,logo,15,3);
        putStringLarge(large_font, 10, 1, "pikachu Breakout clone", 9);
        //flag = (flag+1)%2;
        //if(flag==0)
        //else
    /*level4*/
        /*邊界*/
        show_image(grayblock,0,0);
        show_image(grayblock,0,42);
        show_image(grayblock,0,84);
        show_image(grayblock,0,126);
        show_image(grayblock,343,0);
        show_image(grayblock,343,42);
        show_image(grayblock,343,84);
        show_image(grayblock,343,126);

        /*第一排*/
        if(arrayblock4[6][0]==1)show_image(greenblock,150,10);
        /*第二排*/
        if(arrayblock4[5][0]==1)show_image(whiteblock,133,17);
        if(arrayblock4[5][1]==1)show_image(yellowblock,167,17);
        /*第三排*/
        if(arrayblock4[4][0]==1)show_image(blueblock,116,24);
        if(arrayblock4[4][1]==1)show_image(blueblock,184,24);
        /*第四排*/
        if(arrayblock4[3][0]==1)show_image(greenblock,99,31);
        if(arrayblock4[3][1]==1)show_image(yellowblock,133,31);
        if(arrayblock4[3][2]==1)show_image(blueblock,167,31);
        if(arrayblock4[3][3]==1)show_image(greenblock,201,31);
        /*第五排*/
        if(arrayblock4[2][0]==1)show_image(yellowblock,116,38);
        if(arrayblock4[2][1]==1)show_image(blueblock,184,38);
        /*第六排*/
        if(arrayblock4[1][0]==1)show_image(whiteblock,133,45);
        if(arrayblock4[1][1]==1)show_image(yellowblock,167,45);
        /*第七排*/
        if(arrayblock4[0][0]==1)show_image(greenblock,150,52);
        /*ball*/
        x=x+a;
        y=y+b;
        int flag=0;
        if(y>105)break;
        flag++;
        if(y==52){
            if(x>=150&&x<184){
                    if(arrayblock4[0][0]!=0){
                        arrayblock4[0][0]=0; b=b*-1;
                    }
            }
        }
        if(y==44){
            if(x>=133&&x<166){
                if(arrayblock4[1][0]!=0){
                    arrayblock4[1][0]=0; b=b*-1;
                }
            }
            else if(x>=167&&x<200){
                if(arrayblock4[1][1]!=0){
                    arrayblock4[1][1]=0; b=b*-1;
                }
            }
        }
        if(y==38){
            if(x>=116&&x<149){
                if(arrayblock4[2][0]!=0){
                        arrayblock4[2][0]=0; b=b*-1;
                }
            }
             else if(x>=184&&x<217){
                if(arrayblock4[2][1]!=0){
                        arrayblock4[2][1]=0; b=b*-1;
                }
            }
        }
        if(y==32){
            if(x>=99&&x<130){
                    if(arrayblock4[3][0]!=0){
                        arrayblock4[3][0]=0; b=b*-1;
                        }
                }
            else if(x>=133&&x<166){
                if(arrayblock4[3][1]!=0){
                    arrayblock4[3][1]=0; b=b*-1;
                    }
            }
            else if(x>=167&&x<200){
                if(arrayblock4[3][2]!=0){
                    arrayblock4[3][2]=0;  b=b*-1;
                    }
            }
            else if(x>=201&&x<234){
                if(arrayblock4[3][3]!=0){
                    arrayblock4[3][3]=0;  b=b*-1;
                    }
            }
        }
        if(y==24){
            if(x>=116&&x<149){
                if(arrayblock4[4][0]!=0){
                    arrayblock4[4][0]=0; b=b*-1;
                }
            }
            else if(x>=184&&x<217){
                if(arrayblock4[4][1]!=0){
                    arrayblock4[4][1]=0; b=b*-1;
                }
            }
        }
        if(y==18){
            if(x>=133&&x<166){
                if(arrayblock4[5][0]!=0){
                    arrayblock4[5][0]=0; b=b*-1;
                }
            }
            else if(x>=167&&x<200){
                if(arrayblock4[5][1]!=0){
                    arrayblock4[5][1]=0; b=b*-1;
                }
            }
        }
         if(y==10){
            if(x>=150&&x<184){
                    if(arrayblock4[6][0]!=0){
                        arrayblock4[6][0]=0; b=b*-1;
                    }
            }
        }
        if ((x<=pika.x+15&&x>pika.x+5)&&(y<=pika.y&&y>pika.y-10)&&b>0)
            b=-b;
        if ((x>pika.x-15&&x<pika.x+5)&&(y<=pika.y&&y>pika.y-10)&&b>0)
        {
            b=-b;
            a=-a;
        }
        show_image(ball,x,y);
        if(x==0||x==340)a=a*-1;
        if (y==0) b=-b;
        show_pika(&pika);
        drawCmdWindow();
        move_pika(&pika);

        Sleep(20);
    }
    pauseAudio(&audio1);
    end4();
    destroy_image(grayblock);
    destroy_image(blueblock);
    destroy_image(redblock);
    destroy_image(greenblock);
    destroy_image(yellowblock);
    destroy_image(whiteblock);
    destroy_image(ball);
    destroy_image(pika.jump[0]);
    destroy_image(pika.jump[1]);
    destroy_image(pika.jump[2]);
    destroy_image(pika.jump[3]);
    return ;
}
/* ***************************************************** */
void move_pika(Pika *rp)
{

    if (rp->moveleft_mode>0) {
        if (rp->x>10) rp->x-=5;
        rp->moveleft_mode--;
    }

    if (rp->moveright_mode>0) {
        if (rp->x<394) rp->x+=5;
        rp->moveright_mode--;
    }

}
/* *************************************************** */
void show_pika(Pika *rp)
{

    if (rp->jump_mode>0) {
            if (rp->side==0)show_image(rp->jump[1], rp->x, rp->y);
            else show_image(rp->jump[4], rp->x, rp->y);
            rp->jump_mode--;
    }
    else show_image(rp->jump[rp->side], rp->x, rp->y);
}
