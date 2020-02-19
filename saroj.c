#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <process.h>
#define LEFT -100
#define RIGHT 100
#define WIDTH 1600
#define HEIGHT 700
int blength=100;
int bthick=40;
/*border*/
typedef struct{
    int inih,inik;//ini means initial
    int r,h,k;
    int vx,vy;

}ball;
typedef struct{
    int len;
    int thick;
    int inipos;
    int curpos;//current postion
}launcher;

int RX1=100,RY1=50,RX2=1100,RY2=650;
#define rect_h 1050
#define rect_w 600



void screen(void);
void makebricks(void);
int brickdelete(int);
int changeKicker(int,int,int,int);
void drawKicker(int,int ,int);
void moveBall(int,int ,int ,int ,int);
void drawBall(int ,int ,int );
void deleteKicker(int,int,int);
void deleteBall(int,int,int);
int  points_gain(int);
void control(void);




int main(){
    int points=0;
    int vary=44;
    int brick=0;
    launcher l;
    char ch;//to check which key is hit
    /*laucher/kicker */
    l.len=100;
    l.thick=20;



    /*BALL */
    ball b;
    b.r=10;

    b.inih =(RX2-RX1)/2;
    b.inik = RY2-l.thick-b.r;
    b.vx = 5;

    b.vy = 5;
    l.inipos=500;


    screen();
     outtext((char *)"Press any key to start!!!!");
    getch();
    drawBall(b.inih,b.inik,b.r);
    drawKicker(l.inipos,l.thick,l.len);
    l.curpos=l.inipos;
    b.h=b.inih;
    b.k=b.inik;
    makebricks();
   // floodfill()
    while(1){
            points_gain(points); // for storing the points scored by the player
    delay(20);
        /*ball at bound */
        if(b.h>=RX2-b.r || b.h<=RX1+5+b.r){  //5 is added for boundary effect
            b.vx=b.vx*(-1);
        }
        if (b.h>=l.curpos && b.h<=l.curpos+l.len ){
        if(b.k>=(RY2-b.r-l.thick)){
            b.vy=b.vy*(-1);
        }
        }
         if (b.k>=RY2-l.thick && b.k<=RY2 ){
        if(b.h==(l.curpos-b.r-1) || b.h==(l.curpos+b.r+l.len+1)){
            b.vy=b.vy*(-1);
            b.vx=b.vx*(-1);
        }
        }
        if(b.k<=RY1+vary+b.r){
                brick=brickdelete(b.h);
                points++;
            b.vy=b.vy*(-1);
        }
        b.h+=b.vx;
        b.k+=b.vy;

        delay(0.00001);

        moveBall(b.inih,b.inik,b.h,b.k,b.r);
        b.inih=b.h;
        b.inik=b.k;




        /* kicker */


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
}
    return 0;
}
void screen(){
    initwindow(WIDTH,HEIGHT,"Brick  breaker");
    setfillstyle(SOLID_FILL,BROWN);
    floodfill(10,50,10);
    setcolor(YELLOW);
    rectangle(RX1,RY1,RX2,RY2+4);

}
int brickdelete( int b){
    int brick=0;
    int x1=RX1+1,y1=RY1+1;
    if(b<=RX1+blength){
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=1;
    }else if(b>RX1+blength && b<=RX1+2*blength){
        x1=x1+blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=2;
    }else if (b>RX1+2*blength && b<=RX1+3*blength){
         x1=x1+2*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=3;
    }else if(b>RX1+3*blength && b<=RX1+4*blength){
        x1=x1+3*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=4;
    }else if (b>RX1+4*blength && b<=RX1+5*blength){
         x1=x1+4*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=5;
    }else if(b>RX1+5*blength && b<=RX1+6*blength){
        x1=x1+5*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=6;
    }else if (b>RX1+6*blength && b<=RX1+7*blength){
         x1=x1+6*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=7;
    }else if(b>RX1+7*blength && b<=RX1+8*blength){
        x1=x1+7*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=8;
    }else if(b>RX1+8*blength && b<=RX1+9*blength){
        x1=x1+8*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=9;
    }else if(b>RX1+9*blength && b<=RX1+10*blength){
        x1=x1+9*blength;
        setcolor(BROWN);
        rectangle(x1+1,y1,x1+blength,y1+bthick);
        brick=10;
    }
    else{
        return 0;
    }
    return brick;
}
void makebricks(){
    int i=0;
    int x1=RX1,y1=RY1+1;
    setcolor(RED);
    while(i<10){
    rectangle(x1+1,y1,x1+blength,y1+bthick);
    x1=x1+blength;
    i++;
    }
}
int  changeKicker(int in,int dis,int len,int thick){
          deleteKicker(in,thick,len);
          drawKicker(in+dis,thick,len);
          return (in+dis);

    return in;


}
void drawKicker(int pos,int thick ,int len){
    setcolor(BLACK);
    rectangle(pos,RY2-thick,pos+len,RY2);


}
void deleteKicker(int pos,int thick,int len){
    setcolor(BROWN);
    rectangle(pos,RY2-thick,pos+len,RY2);

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
int points_gain(int points){
    char point[11];
    int X,Y;
    X=RX2+10;
    Y=RY1;
    setcolor(WHITE);
    sprintf(point,"%d",points);
    outtextxy(X+40,Y+50,point);
    outtextxy(X+5,Y+30,"YOUR SCORE IS");

}
