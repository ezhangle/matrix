#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IS_NEWLINE(_c) ('\r' == (_c) || '\n' == (_c))
#define IS_SPACE(_c) (' ' == (_c) || '\t' == (_c) || IS_NEWLINE(_c))

static float readFloat(char **cur) {
  char *p = *cur;
  char str[100];
  int len;
  float ret = 0;
  while (p && *p && !IS_SPACE(*p)) {
    ++p;
  }
  len = p - *cur;
  if (len < sizeof(str)) {
    memcpy(str, *cur, len);
    str[len] = '\0';
    ret = atof(str);
  }
  *cur = p;
  return ret;
}

static char *findNextItem(char *cur) {
  char *p = cur;
  while (p && *p && !IS_SPACE(*p)) {
    ++p;
  }
  while (p && *p && IS_SPACE(*p)) {
    ++p;
  }
  return p;
}

int main(int argc, char *argv[]) {
  FILE *fpIn = fopen("airboat.obj", "rb");
  FILE *fpOut = fopen("airboat_rotate.obj", "wb");
  char line[1024];
  matrix matTmp;
  matrix matFinal;
  matrixLoadIdentity(&matFinal);
  matrixAppend(&matFinal, matrixRotateX(&matTmp, 45));
  matrixAppend(&matFinal, matrixRotateZ(&matTmp, 45));
  matrixAppend(&matFinal, matrixScale(&matTmp, 0.5, 1, 1));
  while (fgets(line, sizeof(line), fpIn)) {
    if ('v' == line[0] && ' ' == line[1]) {
      char *cur = line;
      float vec[3];
      int i;
      for (i = 0; i < 3; ++i) {
        cur = findNextItem(cur);
        vec[i] = readFloat(&cur);
      }
      matrixTransformVector(&matFinal, vec);
      fprintf(fpOut, "v %.6f %.6f %.6f\n", vec[0], vec[1], vec[2]);
    } else {
      fputs(line, fpOut);
    }
  }
  fclose(fpOut);
  fclose(fpIn);
  return 0;
}
