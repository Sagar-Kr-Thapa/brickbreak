#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <process.h>


/*some macros */
#define TEXTX 500
#define TEXTY 200
#define FONT_SIZE 3
#define LEFT -100
#define RIGHT 100
#define WIDTH 1600
#define HEIGHT 700

int blength=100;
int bthick=40;

/*border*/
typedef struct{
    char Name[90];
    long score;


}data;

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

float TIME;
int RX1=100,RY1=50,RX2=1100,RY2=650;
int current=0;

/*prototype */
void mainscreen(void);
void makebricks(void);
int brickdelete(int);
int changeKicker(int,int,int,int);
void drawKicker(int,int ,int);
void moveBall(int,int ,int ,int ,int);
void drawBall(int ,int ,int );
void deleteKicker(int,int,int);
void deleteBall(int,int,int);
void gameMenu(void);
void levelScreen(void);
void instructions(void);
void playerDetail(void);
void gameScreen(void);
int  points_gain(int);
void gameover(void);
int decide_brick(int,int,int);
int decide_point(int,int);
int firstscreen()
{   initwindow(WIDTH,HEIGHT,"Brick  breaker");
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    floodfill(10,50,10);
    int x=getmaxx()/2;
    int y=getmaxy()/2;
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,6);
    outtextxy(x-250,y-100,"**BRICK BREAKER**");
    settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
    outtextxy(x-400,y,"***Created By a Group Of Morons***");
    setlinestyle(1,1,10);
    rectangle(x-500,y-200,x+500,y+200);
    delay(100);
    getch();
	return 0;
}





int main(){
    int brick=0;
    int points=0;
    TIME=20;
    int arr[10]={0,0,0,0,0,0,0,0,0,0};
    char ch;
    data player;

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
    firstscreen();
    initwindow(WIDTH,HEIGHT,"Brick  breaker");
    mainscreen();
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, FONT_SIZE);
    outtextxy(TEXTX,TEXTY,(char *)"Enter your name");//casted to get rid of error:deprecated conversion
    getch();

   // gets(player.Name);
    gameMenu();
    cleardevice();
    mainscreen();




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
   // rectangle(300,100,1000,200);
    makebricks();
    while(1){
            points_gain(points);
            delay(TIME);
        /*ball at bound */
        if(b.k<(RY2+10)){
        if(b.h>=RX2-b.r || b.h<=RX1+5+b.r){  //5 is added for boundary effect
            b.vx=b.vx*(-1);
        }
        if (b.h>=l.curpos-13 && b.h<=l.curpos+l.len+13){
        if(b.k>=(RY2-b.r-l.thick)){
            b.vy=b.vy*(-1);
        }
        }
         if (b.k>=RY2-l.thick-2 && b.k<=RY2 ){
        if((b.h>=(l.curpos-b.r-3) && b.h<=(l.curpos)) || (b.h<=(l.curpos+b.r+l.len+3) && b.h>=(l.curpos+l.len))){
            b.vx=b.vx*(-1);
        }
        }
        if(b.k<=RY1+44+b.r){
             brick=brickdelete(b.h);
                                    //5 is added for boundary effect
            b.vy=b.vy*(-1);
            points++;
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
   int brick=0,x1=RX1+1,y1=RY1+1,i,j,a,c;
    i=x1;j=y1;
    for (a=0;a<=9;a++){
            {
                if(b>RX1+a*blength && b<=RX1+(a+1)*blength )
                {
                i=i+a*blength;
                setcolor(BROWN);
                rectangle(i+1,j,i+blength,j+bthick);
                brick=a;
                setcolor(BROWN);
    }
            }}
    return brick;
}
void makebricks(){
   int x1=RX1+1,y1=RY1+1,i,j;
    setcolor(RED);
    int a=9,b=0;
    for (i=x1;i<=(x1+blength*a);i+=blength){
            for (j=y1;j<=(y1+bthick*b);j+=bthick){
                rectangle(i+1,j,i+blength,j+bthick);}
    }
}
int  changeKicker(int cur,int dis,int len,int thick){


          deleteKicker(cur,thick,len);
          drawKicker(cur+dis,thick,len);
           current=cur;
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
    outtextxy(TEXTX,TEXTY+3*100,(char *)"4.View score");
    outtextxy(TEXTX,TEXTY+4*100, (char *)"5.Quit");
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
        playerDetail();
        gameMenu();
        break;
    case '5':
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
        TIME=20;
        return ;
    case '2':
        TIME=10;
        return ;
    case '3':
        TIME=5;
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
    outtextxy(200,210,(char *)"Press any key to go back");
    getch();
    return;


}

void playerDetail(){
    FILE *fp;
    char d;
   char buffer[1];
    int y=TEXTY;
    cleardevice();
    mainscreen();
    settextstyle( SIMPLEX_FONT, HORIZ_DIR, 1);
    fp=fopen("data.txt","r+");
    if(!fp){
            outtext((char *)"Error");
        return ;
    }
    while(1)
    {
        d=getc(fp);
        if(d==EOF)
           break;
        putc(d,fp);

    }
    fclose(fp);
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
    outtextxy(X+40,Y+50,point);
    outtextxy(X+3,Y+30,"YOUR SCORE IS");

}
void gameover(void){
   cleardevice();
   mainscreen();
   outtextxy((RX2-RX1-100)/2,(RY1+RY2)/2,"GAME OVER !!! PRESS ANY KEY TO EXIT");
   getch();
   exit(0);

}
int decide_brick(int flag,int k,int radius){
    int i,j=0,y_comp=1;
    int arr[]={1,2,3,4,5,6,7,8,9,10};
    int brr[10];
    for(i=0; i<10; i++){
        if (arr[i]==flag){
                brr[j]=flag;
                j++;
    }
    }   for (i=0; i<j; i++){
            if (brr[i]){
            if (k>=RX1+4+radius){  // k is the distance of ball from the top of the screen
                                   // 4 is added to avoid boundary effect
                y_comp=y_comp*(-1); // y_comp refers to the bvy
                return y_comp;
            }
        }
       if (!brr[i]){
       if(k>=RX1+44+radius)
        y_comp=y_comp*(-1);
        return y_comp;
    }
    }
    }
int decide_point(int points,int flag){
    int i,j=0,k;
    int arr[]={1,2,3,4,5,6,7,8,9,10};
    int brr[10];
    for(i=0; i<10; i++){
        if (arr[i]==flag){
                brr[j]=flag;
                j++;
    }
    }   for (i=0; i<j; i++){
            if (brr[i]){
                   return points;
        }else{
            points++;
            return points;
        }
}
}
