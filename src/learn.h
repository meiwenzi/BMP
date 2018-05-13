#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifndef _LEARN_H_
#define _LEARN_H_

// 2byte
struct bmp_magic
{
 unsigned char magic[2];
}magic;


// 4 * 3 = 12 Byte
struct bmp_header
{
 unsigned file_size;    //file size in Byte ,w * h * 3 + 54
 unsigned short creater1;   //0
 unsigned short creater2;   //0
 unsigned offset;   //offset to image data: 54D, 36H
}header;

//10 * 4 =  40 Byte
struct bmp_info
{
 unsigned header_size; //info size in bytes, equals 4o D, or 28H
 unsigned width;     //file wideth in pide
 unsigned height;    //file height in pide

 unsigned short nplanes;   //number of clor planes , 1
 unsigned short bitspp;    //bits per pidel, 24d, 18h

 unsigned compress_type;  //compress type,default 0
 unsigned image_size;   //image size in Byte.  w * h * 3
 unsigned hres;      //pideles per meter, 0
 unsigned vres;      //pideles per meter, 0
 unsigned ncolors;   //number of colors, 0
 unsigned nimpcolors; //important colors, 0
}info;

struct bmp_rgb
{
 unsigned char red;
 unsigned char green;
 unsigned char blue;
};

#define WHITH ((rgb) {0xFF, 0xFF, 0xFF})
#define BLACK ((rgb) {0x00, 0x00, 0x00})
#define RED ((rgb) {0xFF, 0x00, 0x00})
#define GREEN ((rgb) {0x00, 0xFF, 0x00})
#define BLUE ((rgb) {0x00, 0x00, 0xFF})
#define limit_width 15360
#define limit_height 15360
#endif

unsigned pider_number;
unsigned char bitmap[limit_width * limit_height * 3 + 1]; //bitmap size
struct bmp_rgb *rgbmap = (struct bmp_rgb *) &bitmap;

void init_bmp_header(unsigned w, unsigned h); //creat a bmp header
void show_bmp_header();

void read_bmp_header();
void read_bmp_file();

void write_bmp_header();
void write_bmp_file();
void set_background(unsigned char r,unsigned g,unsigned b);
 void color_bar();
void set_pixel(unsigned x,unsigned y,unsigned char r,unsigned g,unsigned b);
void verify_bmp_header();
void lane4();


void set_pixel(unsigned x,unsigned y,unsigned char r,unsigned g,unsigned b)
{
 if(x >= info.width || y >= info.height) return ;
 unsigned p = info.image_size - (y+1)* info.width*3 + x* 3;
 //while(p < info.image_size)
 //{
  bitmap[p] = b;
  bitmap[p+1] = g;
  bitmap[p+2] = r;
 //}
}
void set_background(unsigned char r,unsigned g,unsigned b)
{
 unsigned i = 0;
 unsigned j = 0;
 for(j=0;j<info.height;j++){
    for(i=0;i<info.width;i++){
        set_pixel(i, j, r, g, b);
    }
 }
}

 void color_bar()
{
 unsigned i = 0;
 unsigned j = 0;
 for(j=0;j<info.height;j++){
    for(i=0;i<info.width;i++){
        if(i <= (info.width/3)){
            set_pixel(i, j, 0xFF, 0x00, 0x00);
        }
        else if(i <= (info.width*2/3)){
            set_pixel(i, j, 0x00, 0xFF, 0x00);
        }
        else {
            set_pixel(i, j, 0x00, 0x00, 0xFF);
        }
    }
 }
}

void lane4()
{
 unsigned i = 0;
 unsigned j = 0;
 unsigned n = 0;
 for(j=0;j<info.height;j++){
    for(i=0;i<info.width;i++){
        n = i%4;

        if(n == 0){
            set_pixel(i, j, 0xFF, 0x00, 0x00);
        }
        else if(n == 1){
            set_pixel(i, j, 0x00, 0xFF, 0x00);
        }
        else if(n == 2){
            set_pixel(i, j, 0x00, 0x00, 0xFF);
        }
        else{
            set_pixel(i, j, 0xFF, 0xFF, 0xFF);
        }
    }
 }
}

unsigned char blockcode[22][22][3];
void set_blockcode(unsigned w, unsigned h)
{
 unsigned int i,j;

 for(i = 0; i < 20; i++)
 {
  for(j = 0; j < 20; j++)
  {
   blockcode[i][j][0] = rand()%255;
   blockcode[i][j][1] = rand()%255;
   blockcode[i][j][2] = rand()%255;
  }
 }
 for(i = 0; i < h; i++)
 {
  for(j = 0; j < w*3;)
  {
   bitmap[i*w*3+j] = blockcode[i/20][j/60][0];
   bitmap[i*w*3+j+1] = blockcode[i/20][j/60][1];
   bitmap[i*w*3+j+2] = blockcode[i/20][j/60][2];
  }
 }
}




// unsigned get_block4(unsigned x,unsigned y,unsigned * que)
// {
 // unsigned char *vis = (unsigned char *) malloc(info.width * info.height);

// }

void init_bmp_header(unsigned w, unsigned h)
{
 magic.magic[0] = 'B';
 magic.magic[1] = 'M';

 header.file_size = w * h * 3 + 54;
 header.creater1 = 0;
 header.creater2 = 0;
 header.offset = 54;

 info.header_size = 40;
 info.width = w;
 info.height = h;
 info.nplanes = 1;
 info.bitspp = 3 * 8;
 info.compress_type = 0;
// printf("#1 image_size:%o\n", info.image_size);
 info.image_size = w * h * 3;
// printf("#2 image_size:%o %d\n", info.image_size, info.image_size);
 info.hres = 0;
 info.vres = 0;
 info.ncolors = 100;
 info.nimpcolors = 0;

 pider_number = w * h;
}

//implementations of bmp i/o functions
void read_bmp_header()  //读取头信息，是基本的，通用
{
 fread(&magic, 1 , 2, stdin);

 fread(&header, 4, 3, stdin);

 fread(&info, 4 , 10, stdin);

 pider_number = info.image_size / 3;
}


void read_bmp_file()   //读取文件信息，是调用头信息，然后在读入文件fread(buffer, size, count, fp)
{
 read_bmp_header();

 fread(bitmap, 1, info.image_size, stdin);
}

void write_bmp_header()
{
 fwrite(&magic, 1, 2, stdout);

 fwrite(&header, 4, 3, stdout);

 fwrite(&info, 4, 10, stdout);

 //set_background(unsigned char r,unsigned g,unsigned b)
}

void write_bmp_file()
{
 write_bmp_header();
 fwrite(bitmap, 1, info.image_size, stdout);
}

//void color_bar(unsigned color_bar_num, unsigned col_row_sel, unsigned w, unsigned h)
//{
//    unsigned i;
//
//}


void show_bmp_header()
{
 printf("/n/n");
 printf("bmp header info:/n");

 printf("pider_number/t%d/n/n/n",pider_number);


 printf("magic char:/t/t%c%c/n", magic.magic[0], magic.magic[1]);
 printf("width = %d, height = %d/n",info.width,info.height);
 printf("file size:/t/t%d/n", header.file_size);
 printf("creaters:/t/t%d %d/n", header.creater1, header.creater2);
 printf("offset/t/t/t%d/n", header.offset);

 printf("header size:/t/t%d/n", info.header_size);
 //printf("image scale:/t/tw=%d h=%d/n", info.width, info.height);
 printf("color planes:/t/t%d/n", info.nplanes);
 printf("bit per pidel:/t/t%d/n", info.bitspp);
 printf("compress type:/t/t%d/n", info.compress_type);
 printf("image size:/t/t%d/n", info.image_size);
 printf("pidels per meter:/th=%d v=%d/n", info.hres, info.vres);
 printf("color number:/t/t%d/n", info.ncolors);
 printf("important color:/t%d/n", info.nimpcolors);

 printf("/n/n");
}
