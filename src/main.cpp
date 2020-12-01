#include <iostream>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "textures.h"
#include "game.h"

#define MAX 22

using namespace std;

Textures *texture = new Textures();
Level *level1 = new Level(); 

int jumpFlag=0,up=0,down;
int jumpFlag2=0,up2=0,down2;
bool direction[4] = {0,0,0,0};
bool direction2[4] = {0,0,0,0};
int direction_goomba = 1;

void die(){
    exit(1);
}

void createLevel(){
    for(int i=0;i<MAX;i++){ 
        // level1->baseWall[i] = (i%7);
        level1->baseWall[i] = 1;
        level1->pipe[i] = (i%5==0);
        level1->cloud[i]=1;
        level1->bush[i]=1;
        if(level1->pipe[i-1]==1 && ((i-1)%5==0))
            level1->pipe[i]=1;
    }
    level1->pipe[0]=0;
}

void moveBack(Mario* mario){
   
   
    if(level1->pipe[(mario->mariox)/64]==0 && mario->base)
        direction[3]=1;
   
   
    if(level1->pipe[(mario->mariox-1)/64]){
        if(mario->marioy/64>=3) {

            mario->mariox-=8;
        }
        else
            mario->mariox=mario->mariox;
    }
    else if(level1->baseWall[(mario->mariox+31)/64])
                                                 {

        mario->mariox-=8;
        
    }
    else
        die();
}

void moveFront(Mario* mario){
    if(level1->pipe[(mario->mariox)/64]==0 && mario->base)
        direction[3]=1;


    if(level1->pipe[(mario->mariox+65)/64]){
        if(mario->marioy/64>=3){

            mario->mariox+=8;
        }
        else
            mario->mariox=mario->mariox;
    }
    else if(level1->baseWall[(mario->mariox+33)/64])
                                            {

        mario->mariox+=8;
    }
    else if(mario->marioy){

        mario->mariox+=8;
    }
    else
        die();
}

void moveUp(Mario* mario){
    if(!jumpFlag){
        jumpFlag=mario->marioy+224;
        up=1;
    }
    if(jumpFlag && (mario->marioy<=jumpFlag) && up){

        mario->marioy+=8;
    }
    else
        up=0;
    if(!up)
    {
        if(level1->pipe[(mario->mariox+64)/64] || level1->pipe[(mario->mariox+4)/64]){
            mario->base=1;
            if(mario->marioy>=188)
                mario->marioy-=8;
            if(mario->marioy==192){
                direction[2]=0;
                jumpFlag=0;
            }
        }
        else if(!(level1->pipe[(mario->mariox+64)/64]) || !(level1->pipe[(mario->mariox+4)/64]) ){
            mario->base=0;
            if(mario->marioy>=4)
                mario->marioy-=8;
            if(mario->marioy==0){
                direction[2]=0;
                jumpFlag=0;
            }
        }
    }

    if(!jumpFlag2){
        jumpFlag2=mario->marioy+224;
        up2=1;
    }
    if(jumpFlag2 && (mario->marioy<=jumpFlag2) && up2){

        mario->marioy+=8;
    }
    else
        up2=0;
    if(!up2)
    {
        if(level1->pipe[(mario->mariox+64)/64] || level1->pipe[(mario->mariox+4)/64]){
            mario->base=1;
            if(mario->marioy>=188)
                mario->marioy-=8;
            if(mario->marioy==192){
                direction2[2]=0;
                jumpFlag2=0;
            }
        }
        else if(!(level1->pipe[(mario->mariox+64)/64]) || !(level1->pipe[(mario->mariox+4)/64]) ){
            mario->base=0;
            if(mario->marioy>=4)
                mario->marioy-=8;
            if(mario->marioy==0){
                direction2[2]=0;
                jumpFlag2=0;
            }
        }
    }
}

void moveDown(Mario* mario){
    if(level1->pipe[(mario->mariox)/64]==0 && level1->pipe[(mario->mariox+64)/64]==0){
        if(mario->marioy>0){
            mario->marioy-=8;
        }
        else{
            mario->base=0;
            direction[3]=0;
            direction2[3] = 0;
        }
    }
}

void init()
{
    glClearColor(0.48,0.47,1.0,1.0);	
    glOrtho(0.0,1360.0,0.0,760.0,-10.0,10.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}

void display(Mario* mario, Mario* waluigi, Mario* goomba)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    GLint startx=0,starty=0;
    int j=1;
    int y1=0;
    // cout<<mario->marioy/64<<endl;
    for(int i=0;i<MAX;i++)
    {
        if(level1->baseWall[i])
            texture->drawBaseWall(startx, starty);
        if(level1->cloud[i] && (i%3==0))
            if(j%2==0){ 
                y1+=64;
                texture->drawCloud(startx,y1);
            }
            else
                {texture->drawCloud(startx,starty);
                }
            j++;
        if(level1->bush[i] && (i%4==0))
            texture->drawBush(startx, starty);   
        if(level1->pipe[i] && (i%5==0))
            texture->drawPipe(startx, starty);
        startx+=64;
        y1=0;

    }

    glPushMatrix();
        glTranslatef(mario->mariox,mario->marioy,0);
        texture->drawMario(0, 0);
            glPopMatrix();
    glPushMatrix();

        glTranslatef(waluigi->mariox,waluigi->marioy,0);
        texture->drawWaluigi(0, 0);
            glPopMatrix();
    glPushMatrix();

        glTranslatef(goomba->mariox,goomba->marioy,0);
        texture->drawGoomba(0,0);
        // texture->draw(0, 0);
        
    glPopMatrix();
}

int main(int argc, char** argv)
{

    Mario *mario = new Mario();
    Mario *waluigi = new Mario();
    Mario *goomba = new Mario();

    mario->mariox=0;
    mario->marioy=0;
    mario->base=0;

    waluigi->mariox=0;
    waluigi->marioy=0;
    waluigi->base=0;

    goomba->mariox=440;
    goomba->marioy=00;
    goomba->base=0;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(1344, 768, 32, SDL_SWSURFACE|SDL_OPENGL | SDL_FULLSCREEN);
    // screen = SDL_SetVideoMode(1344, 768, 32, SDL_SWSURFACE|SDL_OPENGL );
    bool running = true;
    const int FPS = 30;
    Uint32 start;
    SDL_Event event;

    createLevel();

    init();

    while(running) {
        start = SDL_GetTicks();
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                        case SDLK_LEFT:
                            direction[0]=1;
                            break;
                        case SDLK_RIGHT:
                            direction[1]=1;
                            break;
                        case SDLK_UP:
                            // jumpFlag=0;
                            direction[2]=1;
                            break;
                        case SDLK_DOWN:
                            // if(direction[2]==0)
                            direction[3]=1;
                            break;
                        case SDLK_a:
                            direction2[0]=1;
                            break;
                        case SDLK_d:
                            direction2[1]=1;
                            break;
                        case SDLK_w:
                            // jumpFlag=0;
                            direction2[2]=1;
                            break;
                        case SDLK_s:
                            // if(direction[2]==0)
                            direction2[3]=1;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            direction[0]=0;
                            break;
                        case SDLK_RIGHT:
                            direction[1]=0;
                            break;
                        case SDLK_UP:
                            // direction[2]=0;
                            // jumpFlag=0;
                            break;
                        case SDLK_DOWN:
                            // if(jumpFlag==1)
                            direction[3]=0;
                            break;
                        case SDLK_a:
                            direction2[0]=0;
                            break;
                        case SDLK_d:
                            direction2[1]=0;
                            break;
                        case SDLK_w:
                            // direction[2]=0;
                            // jumpFlag=0;
                            break;
                        case SDLK_s:
                            // if(jumpFlag==1)
                            direction2[3]=0;
                            break;
                    }
                    break; 
            }
        }

        if(direction[0])
            moveBack(mario);

        if(direction[1])
            moveFront(mario);

        if(direction[2])
            moveUp(mario);

        if(direction[3])
            moveDown(mario);

        if(direction2[0])
            moveBack(waluigi);

        if(direction2[1])
            moveFront(waluigi);

        if(direction2[2])
            moveUp(waluigi);

        if(direction2[3])
            moveDown(waluigi);

        if(level1->pipe[(goomba->mariox+65)/64]){
            if(goomba->marioy/64>=3){
                direction_goomba = 1;
            }
            else
                direction_goomba = -1;
        }

        if(level1->pipe[(goomba->mariox-1)/64]){
            if(goomba->marioy/64>=3) {

                direction_goomba = -1;
            }
            else
                direction_goomba = 1;
        }

        goomba->mariox += direction_goomba * 8;

        display(mario, waluigi, goomba);
        SDL_GL_SwapBuffers();
        // angle += 0.9;
        // if(angle > 360)
        // 	angle -= 360;
        if(1000/FPS > SDL_GetTicks()-start)
            SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
    }
    //SDL_Quit();
    atexit(SDL_Quit);
    return 0;
}
