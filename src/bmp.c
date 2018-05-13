/////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>
#include "learn.h"
#include <time.h>

void test()
{
 freopen("bar1.bmp","r",stdin);
 read_bmp_file();
 show_bmp_header();
}

void test1()
{
 unsigned w = 15350;
 unsigned h = 15350;
 // int r = 0x00;
 // int g = 0x00;
 // int b = 0x00;
 // int r,g,b;
 // srand((unsigned) time(NULL));
 // r =  rand()%255;
    // g =  rand()%255;
 // b =  rand()%255;
 char file_name[250];
// srand((unsigned) time(NULL));
  sprintf(file_name,"pic%dx%d.bmp", w, h);
//  printf("#1\n");
    freopen(file_name,"wb",stdout);
  //printf("#2\n");
  init_bmp_header(w,h);
  //printf("#3\n");
  //set_background(0xFF,0xFF,0xFF);
  //set_pixel(30,30,r,g,b);
  //set_blockcode(w, h);
  //set_background(0x00, 0xFF, 0x00);
  //color_bar();
  lane4();
  //set_pixel(499, 499, 0xFF ,0xFF, 0xFF);
  write_bmp_file();
  fclose(stdout);
//  return 0;
//  num++;
// }
}

int main()
{
 test1();
}
