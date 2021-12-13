#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include"startGame.h"
#include"menu.h"

/*================================= DRAW =======================================*/
void drawWall(){
  MLV_draw_filled_rectangle(0,0,40,800,MLV_COLOR_LIGHT_SEA_GREEN);
  MLV_draw_filled_rectangle(440,0,40,800, MLV_COLOR_LIGHT_SEA_GREEN);
}


void drawMap(MData map[MAP_SIZE_H][MAP_SIZE_W]){
  int h, w;

  for(h=0; h<MAP_SIZE_H; h++){
    for(w=0; w<MAP_SIZE_W; w++){
      if(map[h][w] == EMPTY){
	MLV_draw_filled_rectangle(w*40+40,h*40,38,38,MLV_COLOR_GRAY);
	MLV_actualise_window();
      }else if(map[h][w] == BLOCK){
	MLV_draw_filled_rectangle(w*40+40,h*40,38,38,MLV_COLOR_LIGHTCORAL);
	MLV_actualise_window();
      }
    }
  }
}

void drawSubShape(int shape[4][4]){
  int h, w;

  for(h=0; h<4 ;h++){
    for(w=0 ; w<4; w++){
      if(shape[h][w] == EMPTY){
	MLV_draw_filled_rectangle(w*40+530,h*40+70,35,35,MLV_COLOR_GRAY);
	MLV_actualise_window();
      }else if(shape[h][w] == BLOCK){
	MLV_draw_filled_rectangle(w*40+530,h*40+70,35,35,MLV_COLOR_LIGHTCORAL);
	MLV_actualise_window();
      }
    }
  }
}

void drawShape(MData map[MAP_SIZE_H][MAP_SIZE_W],int shape[4][4], Location curLoc){
  int h, w;

  for(h=0; h<4;h++){
    for(w=0; w<4;w++){
      if(shape[h][w] ==BLOCK){
	map[curLoc.Y+ h][curLoc.X +w]=BLOCK;
	MLV_draw_filled_rectangle((curLoc.X + w)*40+40,(curLoc.Y + h)*40,38,38,MLV_COLOR_LIGHTCORAL);
	MLV_actualise_window();
      }
    }
  }
}
/*===================================================================================*/

void mapInit(MData map[MAP_SIZE_H][MAP_SIZE_W]){
  int i, j=0;
  for(i=0;i<MAP_SIZE_H;i++){
    for(j=0; j<MAP_SIZE_W; j++){
      map[i][j] = EMPTY;
      MLV_draw_filled_rectangle(j*40+40,i*40,38,38,MLV_COLOR_GRAY);
      MLV_actualise_window();
    }
  }
}
void locationInit(Location * curLoc){
  curLoc->X =3;
  curLoc->Y =0;
}
void copyBlock(int blockShape[4][4], int copy[4][4]){
  int i, j;
  for(i=0;i<4;i++){
    for(j=0; j<4;j++){
      blockShape[i][j] = copy[i][j];
    }
  }
}
void setBlock(int blockShape[4][4]){

  int shape[7][4][4] = {
			{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
			{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
			{{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},
			{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
			{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
			{{0,0,0,0},{0,1,0,0},{0,1,1,1},{0,0,0,0}},
			{{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,0,0}}
  };
  /*
    int shapeLong[4][4] = {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}};
    int shapeRock[4][4] = {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}};
    int shapeHorn[4][4] = {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}};
    int shapeStair[4][4] = {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}};
    int shapeRStair[4][4] = {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}};
    int shapeNienun[4][4] = {{0,0,0,0},{0,1,0,0},{0,1,1,1},{0,0,0,0}};
    int shapeRNieun[4][4] = {{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,0,0}};
  */
  
  switch(rand()%7) {
  case 0:
    copyBlock(blockShape, shape[0]);
    break;
  case 1:
    copyBlock(blockShape, shape[1]);
    break;
  case 2:
    copyBlock(blockShape, shape[2]);
    break;
  case 3:
    copyBlock(blockShape, shape[3]);
    break;
  case 4:
    copyBlock(blockShape, shape[4]);
    break;
  case 5:
    copyBlock(blockShape, shape[5]);
    break;
  case 6:
    copyBlock(blockShape, shape[6]);
    break;
  default :
    break;
  }
}

/*============================================================================================*/

void removeShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location * curLoc){
  int h, w;
  for(h=0; h<4;h++){
    for(w=0; w<4;w++){
      if(blockShape[h][w] == BLOCK){
	map[curLoc->Y + h][curLoc->X + w]=EMPTY;
      }
    }
  }
  drawMap(map);
}

int getShapeLeftLoc(int blockShape[4][4]){
  int h, w, leftW=4;
  for(w=0; w<4;w++){
    for(h=0; h<4;h++){
      if(blockShape[h][w] == BLOCK){
	if(leftW > w)
	  leftW = w;
      }
    }
  }
  return leftW;
}
int getShapeRightLoc(int blockShape[4][4]){
  int h, w, rightW=0;
  for(w=3; w>=0;w--){
    for(h=3; h>=0;h--){
      if(blockShape[h][w] == BLOCK){
	if(rightW < w)
	  rightW = w;
      }
    }
  }
  return rightW+1;
}
int getShapeBottomLoc(int blockShape[4][4]){
  int h, w, bottomH=0;
  for(w=3; w>=0;w--){
    for(h=3; h>=0;h--){
      if(blockShape[h][w] == BLOCK){
	if(bottomH < h)
	  bottomH =h;
      }
    }
  }
  return bottomH+1;
}
int getEachBottomLoc(int blockShape[4][4], int w){
  int h, bottomH=-1;
  for(h=3; h>=0;h--){
    if(blockShape[h][w] == BLOCK){
      if(bottomH < h)
	bottomH =h;
    }
  }
  return bottomH;
}
int getEachLeftLoc(int blockShape[4][4], int h){
  int w, leftW= 5;
  for(w=0; w<4;w++){
    if(blockShape[h][w] == BLOCK){
      if(leftW > w)
	leftW = w;
    }
  }
  return leftW;
}
int getEachRightLoc(int blockShape[4][4], int h){
  int w, rightW= -1;
  for(w=0; w<4;w++){
    if(blockShape[h][w] == BLOCK){
      if(rightW < w)
	rightW = w;
    }
  }
  return rightW;
}
void goLeft(MData map[MAP_SIZE_H][MAP_SIZE_W],int blockShape[4][4], Location *curLoc){
  int leftW = getShapeLeftLoc(blockShape);
  int boundaryArr[4] ={0};
  int i;
  for(i=0; i<4;i++){
    boundaryArr[i] = getEachLeftLoc(blockShape, i);
  }
  if((curLoc->X) + leftW > 0){
    if(!((boundaryArr[0] != 5 && map[curLoc->Y][curLoc->X + boundaryArr[0] -1] != EMPTY)
	 ||(boundaryArr[1] != 5 && map[curLoc->Y +1][curLoc->X + boundaryArr[1] -1] != EMPTY)
	 ||(boundaryArr[2] != 5 && map[curLoc->Y +2][curLoc->X + boundaryArr[2] -1] != EMPTY)
	 ||(boundaryArr[3] != 5 && map[curLoc->Y +3][curLoc->X + boundaryArr[3] -1] != EMPTY))){

      removeShape(map, blockShape,curLoc);
      (curLoc->X)--;
    }
  }

}
void goRight(MData map[MAP_SIZE_H][MAP_SIZE_W],int blockShape[4][4], Location *curLoc){
  int rightW = getShapeRightLoc(blockShape);
  int boundaryArr[4] ={0};
  int i;
  for(i=0; i<4;i++){
    boundaryArr[i] = getEachLeftLoc(blockShape, i);

  }

  if((curLoc->X) + rightW < MAP_SIZE_W){
    if(!((boundaryArr[0] != 5 && map[curLoc->Y][curLoc->X + boundaryArr[0] +1] != EMPTY)
	 ||(boundaryArr[1] != 5 && map[curLoc->Y +1][curLoc->X + boundaryArr[1] +1] != EMPTY)
	 ||(boundaryArr[2] != 5 && map[curLoc->Y +2][curLoc->X + boundaryArr[2] +1] != EMPTY)
	 ||(boundaryArr[3] != 5 && map[curLoc->Y +3][curLoc->X + boundaryArr[3] +1] != EMPTY))){

      removeShape(map, blockShape,curLoc);
      (curLoc->X)++;
    }

  }

}

void fixShape(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location *curLoc){
  int w, h;
  for(w=0; w<4; w++){
    for(h=0; h<4 ; h++){
      if(blockShape[h][w] ==1){
	map[curLoc->Y+ h][curLoc->X +w]=BLOCK;
      }
    }
  }
  drawMap(map);
}

int goDown(MData map[MAP_SIZE_H][MAP_SIZE_W], int blockShape[4][4], Location *curLoc){
  int bottomH = getShapeBottomLoc(blockShape);
  int bottomArr[4] = {0};
  int i;
  for(i=0; i<4; i++){
    bottomArr[i] = getEachBottomLoc(blockShape, i);
  }
  if(curLoc->Y + bottomH  == MAP_SIZE_H
     ||(bottomArr[1] != -1 && map[curLoc->Y + bottomArr[1] +1][curLoc->X + 1] != EMPTY)
     ||(bottomArr[0] != -1 && map[curLoc->Y + bottomArr[0] +1][curLoc->X + 0] != EMPTY)
     ||(bottomArr[3] != -1 && map[curLoc->Y + bottomArr[3] +1][curLoc->X + 3] != EMPTY)
     ||(bottomArr[2] != -1 && map[curLoc->Y + bottomArr[2] +1][curLoc->X + 2] != EMPTY)
     ){

    fixShape(map, blockShape, curLoc);
    return TRUE;
  }


  if(curLoc->Y + bottomH < MAP_SIZE_H){
    removeShape(map, blockShape, curLoc);
    (curLoc->Y)++;
  }

  return FALSE;
}

void rotate(MData map[MAP_SIZE_H][MAP_SIZE_W],int blockShape[4][4], Location * curLoc){
  int i, j;
  int tmp[4][4];
  int leftW, rightW, bottomH;
  
  for(i=0; i<4;i++){
    for(j=0; j<4;j++){
      if(blockShape[i][j] == BLOCK){
	tmp[j][3-i] = BLOCK;
	blockShape[i][j] = EMPTY;
      }
    }
  }

  drawMap(map);

  for(i=0; i<4;i++){
    for(j=0; j<4;j++){
      if(tmp[i][j] == 1){
	blockShape[i][j] = BLOCK;
      }
    }
  }
  
  /*when rotate near the wall.*/
  leftW= getShapeLeftLoc(blockShape);
  if(curLoc->X + leftW <0){
    goRight(map, blockShape, curLoc);
    if(leftW == 0) goRight(map, blockShape, curLoc); /*long shape*/
  }

  rightW = getShapeRightLoc(blockShape);
  if(curLoc->X + rightW >MAP_SIZE_W){
    goLeft(map, blockShape, curLoc);
    if(rightW == 4)goLeft(map, blockShape, curLoc); /*long shape*/
  }

  bottomH = getShapeBottomLoc(blockShape);
  if(curLoc->Y + bottomH > MAP_SIZE_H){
    removeShape(map, blockShape, curLoc);
    (curLoc->Y)--;
    if(bottomH ==4) (curLoc->Y)--;      /*long shape*/
  }
}

int goSpace(MData map[MAP_SIZE_H][MAP_SIZE_W],int blockShape[4][4],Location * curLoc){
  int bottomH = getShapeBottomLoc(blockShape);
  int bottomArr[4] = {0};
  int i;
  for(i=0; i<4; i++){
    bottomArr[i] = getEachBottomLoc(blockShape, i);
  }
  while(1){
    if(curLoc->Y + bottomH  == MAP_SIZE_H
       ||(bottomArr[1] != -1 && map[curLoc->Y + bottomArr[1] +1][curLoc->X + 1] != EMPTY)
       ||(bottomArr[0] != -1 && map[curLoc->Y + bottomArr[0] +1][curLoc->X + 0] != EMPTY)
       ||(bottomArr[3] != -1 && map[curLoc->Y + bottomArr[3] +1][curLoc->X + 3] != EMPTY)
       ||(bottomArr[2] != -1 && map[curLoc->Y + bottomArr[2] +1][curLoc->X + 2] != EMPTY)
       ){

      fixShape(map, blockShape, curLoc);
      return TRUE;
    }
    if(curLoc->Y + bottomH < MAP_SIZE_H){
      removeShape(map, blockShape, curLoc);
      (curLoc->Y)++;
    }
  }
  return FALSE;
}


void deleteLine(MData map[MAP_SIZE_H][MAP_SIZE_W], int h){
  int w;
  for(w=0 ; w < MAP_SIZE_W ; w++){
    map[h][w] = EMPTY;
  }
}
void organizeLine(MData map[MAP_SIZE_H][MAP_SIZE_W], int h){
  int w;
  while(h > 1){
    for(w=0; w<MAP_SIZE_W;w++){
      map[h][w] = map[h-1][w];
    }
    h--;
  }
}
void checkLine(MData map[MAP_SIZE_H][MAP_SIZE_W], Location curLoc, int * score){
  int h, w, full;

  for(h=MAP_SIZE_H ; h >= (curLoc.Y -1); h--){
    full =0;
    for(w=0; w<MAP_SIZE_W  ;w++){
      if(map[h][w] == EMPTY){
	break;
      }else{
	full++;
      }
    }

    if(full == MAP_SIZE_W){
      (*score) += 5;
      deleteLine(map, h);
      organizeLine(map, h);
    }
  }
  drawMap(map);
}
int GameOver(MData map[MAP_SIZE_H][MAP_SIZE_W],int score, int bestScore){
  FILE * wfp;
  int w=0;
  MLV_Font* font = MLV_load_font("jeu_font.ttf", 50);
  
  for(w=0; w<MAP_SIZE_W; w++){
    if(map[0][w] == BLOCK){
      MLV_draw_text_with_font(100, 100, "GAME OVER", font, MLV_COLOR_RED);
      
      if(score >= bestScore){
	wfp = fopen("score.txt", "w");
	fprintf(wfp, "%d", score);
	fclose(wfp);
      }
      return TRUE;
    }
  }

  return FALSE;
}

/*============================================================================================*/

int GameStart(MData map[MAP_SIZE_H][MAP_SIZE_W]){
  int width = 740;
  int height = 800;
  
  MLV_change_window_size(width, height);

  MLV_actualise_window();

  int reachBottom = FALSE;
  int score =0, bestScore =0;
  int blockShape[4][4] ={0};
  int blockShapeSub[4][4] = {0};
  Location curLoc = {2,2};
  FILE * rfp;
  if((rfp = fopen("score.txt", "r")) == NULL){
    FILE * wfp;
    wfp = fopen("score.txt", "w");
    fprintf(wfp, "%d", 0);
    fclose(wfp);
  }
  fscanf(rfp, "%d", &bestScore);

  mapInit(map);
  drawWall();
  drawMap(map);

  locationInit(&curLoc);
  setBlock(blockShape);
  setBlock(blockShapeSub);
  drawSubShape(blockShapeSub);

  MLV_draw_text(530,400, "UP: Rotate", MLV_COLOR_GREEN);
  MLV_draw_text(530,440, "DOWN: go Down", MLV_COLOR_GREEN);
  MLV_draw_text(530,480, "LEFT: go left", MLV_COLOR_GREEN);
  MLV_draw_text(530,520, "RIGHT: go Right", MLV_COLOR_GREEN);
  MLV_draw_text(530,560, "m : Menu", MLV_COLOR_GREEN);

  while(1){
    if(reachBottom == TRUE){
      if(GameOver(map,score, bestScore)){
	MLV_wait_seconds(5);
	menuboard();
      }

      checkLine(map, curLoc, &score);
      checkLine(map, curLoc, &score);
      locationInit(&curLoc);
      copyBlock(blockShape, blockShapeSub);
      setBlock(blockShapeSub);
      drawSubShape(blockShapeSub);
      reachBottom = FALSE;
    }
    
    drawShape(map,blockShape, curLoc);
    drawMap(map);
    reachBottom = goDown(map, blockShape, &curLoc);
    
    if(reachBottom == TRUE) continue;

    if( MLV_get_keyboard_state( MLV_KEYBOARD_UP ) == MLV_PRESSED){
      rotate(map, blockShape, &curLoc);
    }
    if( MLV_get_keyboard_state( MLV_KEYBOARD_SPACE ) == MLV_PRESSED){
      goSpace(map, blockShape, &curLoc);
    }
    if( MLV_get_keyboard_state( MLV_KEYBOARD_LEFT ) == MLV_PRESSED){
      goLeft(map, blockShape, &curLoc);
    }
    if( MLV_get_keyboard_state( MLV_KEYBOARD_RIGHT ) == MLV_PRESSED){
      goRight(map, blockShape, &curLoc);
    }
    if( MLV_get_keyboard_state( MLV_KEYBOARD_m) == MLV_PRESSED){
      SaveGame(map, score);
      menuboard();
    }
    
  }
  return 0;
}

int ReStartGame(MData map[MAP_SIZE_H][MAP_SIZE_W]){
  int width = 740;
  int height = 800;
  
  MLV_change_window_size(width, height);

  MLV_actualise_window();

  int reachBottom = FALSE;
  int score =0, bestScore =0;
  int blockShape[4][4] ={0};
  int blockShapeSub[4][4] = {0};
  Location curLoc = {2,2};
  FILE * rfp;
  if((rfp = fopen("score.txt", "r")) == NULL){
    FILE * wfp;
    wfp = fopen("score.txt", "w");
    fprintf(wfp, "%d", 0);
    fclose(wfp);
  }
  fscanf(rfp, "%d", &bestScore);
  
  drawWall();
  drawMap(map);

  locationInit(&curLoc);
  setBlock(blockShape);
  setBlock(blockShapeSub);
  drawSubShape(blockShapeSub);

  MLV_draw_text(530,400, "UP: Rotate", MLV_COLOR_GREEN);
  MLV_draw_text(530,440, "DOWN: go Down", MLV_COLOR_GREEN);
  MLV_draw_text(530,480, "LEFT: go left", MLV_COLOR_GREEN);
  MLV_draw_text(530,520, "RIGHT: go Right", MLV_COLOR_GREEN);
  MLV_draw_text(530,560, "m : Menu", MLV_COLOR_GREEN);

  while(1){
    if(reachBottom == TRUE){
      if(GameOver(map,score, bestScore)){
	MLV_wait_seconds(5);
	menuboard();
      }

      checkLine(map, curLoc, &score);
      checkLine(map, curLoc, &score);
      locationInit(&curLoc);
      copyBlock(blockShape, blockShapeSub);
      setBlock(blockShapeSub);
      drawSubShape(blockShapeSub);
      reachBottom = FALSE;
    }
    
    drawShape(map,blockShape, curLoc);
    drawMap(map);
    reachBottom = goDown(map, blockShape, &curLoc);
    
    if(reachBottom == TRUE) continue;

    if( MLV_get_keyboard_state( MLV_KEYBOARD_UP ) == MLV_PRESSED){
      rotate(map, blockShape, &curLoc);
    }
    if( MLV_get_keyboard_state( MLV_KEYBOARD_SPACE ) == MLV_PRESSED){
      goSpace(map, blockShape, &curLoc);
    }
    if( MLV_get_keyboard_state( MLV_KEYBOARD_LEFT ) == MLV_PRESSED){
      goLeft(map, blockShape, &curLoc);
    }
    if( MLV_get_keyboard_state( MLV_KEYBOARD_RIGHT ) == MLV_PRESSED){
      goRight(map, blockShape, &curLoc);
    }
    if( MLV_get_keyboard_state( MLV_KEYBOARD_m) == MLV_PRESSED){
      SaveGame(map, score);
      menuboard();
    }
    
  }
  return 0;
}


void LoadGame(MData map[MAP_SIZE_H][MAP_SIZE_W]){
  int h,w;
  
  FILE* loadGame;
  loadGame = fopen("loadGame.txt", "r");

  for(h=0; h<MAP_SIZE_H; h++){
    for(w=0; w<MAP_SIZE_W; w++){
      map[h][w]=fgetc(loadGame)-48;
    }
  }
  fclose(loadGame);

  ReStartGame(map);
}

void SaveGame(MData map[MAP_SIZE_H][MAP_SIZE_W], int score ){
  int h,w;
  FILE * loadGame;
  loadGame = fopen("loadGame.txt", "w");
  for(h=0; h<MAP_SIZE_H; h++){
    for(w=0; w<MAP_SIZE_W; w++){
      fprintf(loadGame, "%d", map[h][w]);			
    }
  }
  /*fprintf(loadGame, "\n%d", score);*/
  fclose(loadGame);
}
