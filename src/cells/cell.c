#include "common.h"

Cell createCell(int id, int x, int y){
  Cell cell;
  cell.id = id;
  cell.pos = (Vector2){ x, y };
  cell.alive = false;
  return cell;
}

void initCellArr(Cell *cellArr){
  int index = 0;
  for(int y = 0; y < GRIDHEIGHT; y++){
    for(int x = 0; x < GRIDWIDTH; x++){
      int posX = x * CELLSIZE;
      int posY = y * CELLSIZE;
      printf("x: %d, y: %d\n", posX, posY);
      cellArr[index] = createCell(index, posX, posY);
      index++;
    }
  }
}

void drawCells(Cell *cellArr){
  for(int i = 0; i < (GRIDWIDTH * GRIDHEIGHT); i++){
    if(cellArr[i].alive){
      DrawRectangle(cellArr[i].pos.x, cellArr[i].pos.y, CELLSIZE, CELLSIZE, GREEN);
    }
  }
}

int findTileIndex(int x, int y){
  return (y / CELLSIZE) * GRIDHEIGHT + (x / CELLSIZE);
}

void placeCell(Cell *cellArr, Camera2D *camera){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT)){
    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
    int posX = ((int)mousePos.x / CELLSIZE) * CELLSIZE;
    int posY = ((int)mousePos.y / CELLSIZE) * CELLSIZE;
    int cellIndex = findTileIndex(posX, posY);
    cellArr[cellIndex].alive = true;
  }
}

void deleteCell(Cell *cellArr, Camera2D *camera){
  if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
    int posX = ((int)mousePos.x / CELLSIZE) * CELLSIZE;
    int posY = ((int)mousePos.y / CELLSIZE) * CELLSIZE;
    int cellIndex = findTileIndex(posX, posY);
    cellArr[cellIndex].alive = false;
  }
}

bool withinBounds(int x, int y){
  if(x >= 0 && x <= GRIDWIDTH * CELLSIZE){
    if(y >= 0 && y <= GRIDHEIGHT * CELLSIZE){
      return true;
    }
  }
  return false;
}

int *findNeighbours(Cell *cell, Cell *cellArr){
  int *tiles = malloc(sizeof(int) * 8);
  int dx[8] = { 0, CELLSIZE, 0, -CELLSIZE, -CELLSIZE, CELLSIZE, -CELLSIZE, CELLSIZE};
  int dy[8] = { -CELLSIZE, 0, CELLSIZE, 0, -CELLSIZE, -CELLSIZE, CELLSIZE, CELLSIZE};
  for(int i = 0; i < 8; i++){
    int x = cell->pos.x + dx[i];
    int y = cell->pos.y + dy[i];
    int index = findTileIndex(x, y);
    if(cellArr[index].alive && withinBounds(x, y)){
      tiles[i] = index;
    }else{
      tiles[i] = -1;
    }
  }
  return tiles;
}

void cellBehaviour(Cell *cellArr){
  bool *nextState = malloc(sizeof(bool) * GRIDWIDTH * GRIDHEIGHT);
  for(int i = 0; i < GRIDWIDTH * GRIDHEIGHT; i++){
    int *tiles = findNeighbours(&cellArr[i], cellArr);
    int count = 0;
    for(int j = 0; j < 8; j++){
      if(tiles[j] != -1) count++;
    }
    if(cellArr[i].alive && (count < 2 || count > 3)){
      nextState[i] = false;
    } else if(!cellArr[i].alive && count == 3){
      nextState[i] = true;
    } else {
      nextState[i] = cellArr[i].alive;
    }

    free(tiles);
  }
  for(int i = 0; i < GRIDWIDTH * GRIDHEIGHT; i++){
    cellArr[i].alive = nextState[i];
  }
  free(nextState);
}


void updateCellArr(Cell *cellArr, Camera2D *camera){
  drawCells(cellArr);
  placeCell(cellArr, camera);
  deleteCell(cellArr, camera);
}
