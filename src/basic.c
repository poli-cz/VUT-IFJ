#include<stdio.h>
#include<stdlib.h>
#include "basic.h"



void error_handler(int code){

  switch (code) {
    case 1:
      fprintf(stderr, "Exited with code 1\n");
      exit(1);
    case 2:
      fprintf(stderr, "Exited with code 2\n");
      exit(2);
    case 3:
      fprintf(stderr, "Exited with code 3\n");
      exit(3);
    case 4:
      fprintf(stderr, "Exited with code 4\n");
      exit(4);
    case 5:
      fprintf(stderr, "Exited with code 5\n");
      exit(5);
    case 6:
      fprintf(stderr, "Exited with code 6\n");
      exit(6);
    case 7:
      fprintf(stderr, "Exited with code 7\n");
      exit(7);
    case 9:
      fprintf(stderr, "Exited with code 9\n");
      exit(9);
    default:
      fprintf(stderr, "Exited with code 99\n");
      exit(99);
    };
}
