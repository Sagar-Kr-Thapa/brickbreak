#include <stdio.h>
#include <conio.h>
#include <graphics.h> //graphics functions prototype is declared
#include <windows.h>//here is prototype of beep()


/*some macros */
#define TEXTX 500
#define TEXTY 200
#define FONT_SIZE 3
#define LEFT -100
#define RIGHT 100
#define WIDTH 1600
#define HEIGHT 700
#define FREQ 2500
/*global variables*/
int blength=100;
int bthick=40;

/*ball*/

typedef struct{
    int inih,inik;//ini means initial
    int r,h,k;
    int vx,vy;

}ball;
/*launcher*/
typedef struct{
    int len;
    int thick;
    int inipos;
    int curpos;//current postion
}launcher;
struct brick{
    int flag;
}s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
float TIME;
int RX1=100,RY1=50,RX2=1100,RY2=650;
int current=0;

/*prototype */
void mainscreen(void);
void gameScreen(void);
int brickdelete(int);
void makebricks(void);
int changeKicker(int,int,int,int);
void drawKicker(int,int ,int);
void deleteKicker(int,int,int);
void drawBall(int ,int ,int );
void moveBall(int,int ,int ,int ,int);
void deleteBall(int,int,int);
void gameMenu(void);
void levelScreen(void);
void instructions(void);
int  points_gain(int);
void gameover(void);
int decide_brick(int,int,int);
int decide_point(int,int);





int main(){
    int brick=0;
    int points=0;
    TIME=10;
    char ch;


//launcher properties
    launcher l;
    l.len=100;
    l.thick=20;
    l.inipos=500;



    /*BALL properties*/
    ball b;
    b.r=10;
    b.inih =(RX2-RX1+l.len)/2;
    b.inik = RY2-l.thick-b.r;
    b.vx = 5;
    b.vy = 5;
    initwindow(WIDTH,HEIGHT,"Brick  breaker");
    mainscreen();
    gameMenu();
    cleardevice();
    mainscreen();


// these flags determine whether the ball is bounced from boundary or not
    s1.flag=0;
    s2.flag=0;
    s3.flag=0;
    s4.flag=0;
    s5.flag=0;
    s6.flag=0;
    s7.flag=0;
    s8.flag=0;
    s9.flag=0;
    s10.flag=0;



    /*game starts */


    gameScreen();
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
   setcolor(YELLOW);
    outtext((char *)"Press any key to start!!!!");
    getch();
    mainscreen();
    gameScreen();
    drawBall(b.inih,b.inik,b.r);
    drawKicker(l.inipos,l.thick,l.len);
    l.curpos=l.inipos;
    b.h=b.inih;
    b.k=b.inik;
    setcolor(RED);
    makebricks();
    while(1){
            points_gain(points);
            delay(TIME);

        /*ball at bound */
        if(b.k<(RY2+10)){
        if(b.h>=RX2-b.r || b.h<=RX1+5+b.r){
                //5 is added for boundary effect
            b.vx=b.vx*(-1);
            Beep(FREQ,TIME);
        }
        if (b.h>=l.curpos-13 && b.h<=l.curpos+l.len+13){
        if(b.k>=(RY2-b.r-l.thick)){

            b.vy=b.vy*(-1);
            Beep(FREQ,TIME);
        }
        }
         if (b.k>=RY2-l.thick-3 && b.k<=RY2 ){
        if((b.h>=(l.curpos-b.r-4) && b.h<=(l.curpos)) || (b.h<=(l.curpos+b.r+l.len+3) && b.h>=(l.curpos+l.len))){
            b.vx=b.vx*(-1);
           Beep(FREQ,TIME);
        }
        }
        if(b.k<=RY1+44+b.r){
             if (b.h<=RX1+blength && s1.flag==0){
                s1.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h<=RX1+blength && s1.flag==1) {
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);//KHALI
                                    }
                        }
             if (b.h>RX1+blength && b.h<=RX1+2*blength && s2.flag==0){
                s2.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h>RX1+blength && b.h<=RX1+2*blength && s2.flag==1){
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);
                                    }
                        }
            if (b.h>RX1+2*blength && b.h<=RX1+3*blength && s3.flag==0){
                s3.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h>RX1+2*blength && b.h<=RX1+3*blength && s3.flag==1) {
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);
                                    }
                        }
            if (b.h>RX1+3*blength && b.h<=RX1+4*blength && s4.flag==0){
                s4.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h>RX1+3*blength && b.h<=RX1+4*blength && s4.flag==1){
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);
                                    }
                        }
           if (b.h>RX1+4*blength && b.h<=RX1+5*blength && s5.flag==0){
                s5.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h>RX1+4*blength && b.h<=RX1+5*blength && s5.flag==1){
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);
                                    }
                        }
            if (b.h>RX1+5*blength && b.h<=RX1+6*blength && s6.flag==0){
                s6.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h>RX1+5*blength && b.h<=RX1+6*blength && s6.flag==1){
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);
                                    }
                        }
            if (b.h>RX1+6*blength && b.h<=RX1+7*blength && s7.flag==0){
                s7.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h>RX1+6*blength && b.h<=RX1+7*blength && s7.flag==1) {
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);
                                    }
                        }
            if (b.h>RX1+7*blength && b.h<=RX1+8*blength && s8.flag==0){
                s8.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h>RX1+7*blength && b.h<=RX1+8*blength && s8.flag==1){
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);
                                    }
                        }
            if (b.h>RX1+8*blength && b.h<=RX1+9*blength && s9.flag==0){
                s9.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if(b.h>RX1+8*blength && b.h<=RX1+9*blength && s9.flag==1) {
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);
                                    }
                        }
            if (b.h>RX1+9*blength && b.h<=RX1+10*blength && s10.flag==0){
                s10.flag=brickdelete(b.h);
                b.vy=b.vy*(-1);
                Beep(FREQ,TIME);
                points+=100;
                }else if (b.h>RX1+9*blength && b.h<=RX1+10*blength && s10.flag==1){
                    if(b.k<=RY1+5+b.r){
                    b.vy=b.vy*(-1);
                    Beep(FREQ,TIME);
                                    }
                        }
        }
        }else{
            gameover();
        }



        b.h+=b.vx;
        b.k+=b.vy;
        moveBall(b.inih,b.inik,b.h,b.k,b.r);
        b.inih=b.h;
        b.inik=b.k;




        /* kicker */

        fflush(stdin);
        if (l.curpos>RX1 && l.curpos<RX2-l.len){
        if(kbhit()){
            ch=getch();
            switch(ch)
            {
            case 'a' : case 'A':
                l.curpos=changeKicker(l.curpos,LEFT,l.len,l.thick);
                break;

            case 'd': case 'D':
                l.curpos=changeKicker(l.curpos,RIGHT,l.len,l.thick);
                break;
            default:
                break;

            }
        }
        }else{
            deleteKicker(l.curpos,l.thick,l.len);
            if(l.curpos<=RX1){
                l.curpos=RX1+1;
            }
            if(l.curpos>=RX2-l.len){
                l.curpos=RX2-l.len-1;
            }
            drawKicker(l.curpos,l.thick,l.len);
                continue;
        }



}
    return 0;
}
void mainscreen(){

    setfillstyle(SOLID_FILL,BROWN);
    floodfill(10,50,10);


}
void gameScreen(){
    setcolor(YELLOW);
    rectangle(RX1,RY1,RX2,RY2);
}
int brickdelete( int b){
    int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10;
    int x1=RX1+1,y1=RY1+1;
    if(b<=RX1+blength){
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a1=1;
        return a1;
    }else if(b>RX1+blength && b<=RX1+2*blength){
        x1=x1+blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a2=1;
        return a2;
    }else if (b>RX1+2*blength && b<=RX1+3*blength){
         x1=x1+2*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a3=1;
        return a3;
    }else if(b>RX1+3*blength && b<=RX1+4*blength){
        x1=x1+3*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a4=1;
        return a4;
    }else if (b>RX1+4*blength && b<=RX1+5*blength){
         x1=x1+4*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a5=1;
        return a5;
    }else if(b>RX1+5*blength && b<=RX1+6*blength){
        x1=x1+5*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
       a6=1;
        return a6;
    }else if (b>RX1+6*blength && b<=RX1+7*blength){
         x1=x1+6*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a7=1;
        return a7;
    }else if(b>RX1+7*blength && b<=RX1+8*blength){
        x1=x1+7*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a8=8;
        return a8;
    }else if(b>RX1+8*blength && b<=RX1+9*blength){
        x1=x1+8*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a9=1;
        return a9;
    }else if(b>RX1+9*blength && b<=RX1+10*blength){
        x1=x1+9*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        a10=1;
        return a10;
    }
    else{
        return 0;
    }
}
void makebricks(){
    int x1=RX1+1,y1=RY1+1;  //margin
    setcolor(RED);
    rectangle(x1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
   x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
     rectangle(x1+1,y1,x1+blength,y1+bthick);
}
int  changeKicker(int cur,int dis,int len,int thick){


          deleteKicker(cur,thick,len);
          drawKicker(cur+dis,thick,len);
          return (cur+dis);
}
void drawKicker(int pos,int thick ,int len){
    setcolor(BLACK);
    if(pos>RX1 && pos+len<RX2)
    rectangle(pos,RY2-thick,pos+len,RY2-5);
    return ;


}
void deleteKicker(int pos,int thick,int len){
    setcolor(BROWN);
    if(pos>RX1 && pos+len<RX2)
    rectangle(pos,RY2-thick,pos+len,RY2-5);

}
void drawBall(int h,int k,int r){
    setcolor(BLACK);
    circle(h,k,r);

}
void moveBall(int inih,int inik,int h,int k,int r){
    deleteBall(inih,inik,r);
    setcolor(BLACK);
    drawBall(h,k,r);

}
void deleteBall(int h,int k,int r){
    setcolor(BROWN);
    circle(h,k,r);
}
void gameMenu(){
    cleardevice();
    mainscreen();
    char choice;
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(TEXTX,TEXTY,    (char *)"1.Start game");
    outtextxy(TEXTX,TEXTY+100,(char *)"2.Select Level");
    outtextxy(TEXTX,TEXTY+2*100,(char *)"3.Instructions");
    outtextxy(TEXTX,TEXTY+3*100, (char *)"4.Quit");
    choice=getch();
    switch(choice){
    case '1':
        return ;
    case '2':
        levelScreen();
        gameMenu();
        break;

    case '3':
        instructions();
        gameMenu();
        break;
    case '4':
        outtextxy(500,500,(char *)"QUITTING");
        delay(25);
        exit(0);
    default:
        gameMenu();
        break;
    }

  return ;




}
void levelScreen(){
    cleardevice();
    mainscreen();

    char choice;
      settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(TEXTX,TEXTY,(char *)"1.Easy");
    outtextxy(TEXTX,TEXTY+1*100,(char *)"2.Medium");
    outtextxy(TEXTX,TEXTY+2*100,(char *)"3.Hard");
    choice=getch();
    switch(choice){
    case '1':
        TIME=10;
        return ;
    case '2':
        TIME=5;
        return ;
    case '3':
        TIME=1;
        break;
    default:
        levelScreen();
        return ;

    }
    return ;

}
void  instructions(){
    cleardevice();
    mainscreen();
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(200,200,(char *)"Hit 'A' to move left or 'D' to move right ");
    outtextxy(200,250,(char *)"Press any key to go back");
    getch();
    return;


}
int points_gain(int points){
    char point[11];
    int X,Y;
    X=RX2+10;
    Y=RY1;
    setcolor(WHITE);
    sprintf(point,"%d",points); //converts integer to character string
    outtextxy(X+60,Y+80,point);

    outtextxy(X+60,Y+20,(char *)"SCORE");

}
void gameover(void){
    int i;
   cleardevice();
   mainscreen();
   outtextxy((RX2-RX1)/3,(RY1+RY2)/2,(char *)"GAME OVER !!! PRESS ANY KEY TO RETURN ");
   getch();
   main();
   return ;

}

