#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SCREENWIDTH 2000 
#define SCREENHEIGHT 1300 
#define TARGETFPS 60 

#define CELLSIZE 20 //10x10
#define GRIDWIDTH 40
#define GRIDHEIGHT 40 // cells

typedef struct{
  int id;
  Vector2 pos;
  bool alive;
}Cell;

#endif
