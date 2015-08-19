#include <cassert>
#include <cstdio>
#include <fstream>

using namespace std;

int r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13;
ifstream ifs("kururin.GBA");

char res[0x80000];

char get(unsigned int i) {
  if (i >= 0x08000000) {
    i -= 0x08000000;
    ifs.seekg(i, ios_base::beg);
    char b;
    ifs.read(&b, 1);
    return b;
  } else if (i >= 0x02000000) {
    i -= 0x02000000;
    return res[i];
  }
}

int get4(unsigned int i) {
  if (i >= 0x08000000) {
    i -= 0x08000000;
    ifs.seekg(i, ios_base::beg);
    int b;
    ifs.read((char*)&b, 4);
    return b;
  } else if (i >= 0x02000000) {
    i -= 0x02000000;
    return res[i];
  }
}

short get2(unsigned int i) {
  if (i >= 0x08000000) {
    i -= 0x08000000;
    ifs.seekg(i, ios_base::beg);
    short b;
    ifs.read((char*)&b, 2);
    return b;
  } else if (i >= 0x02000000) {
    i -= 0x02000000;
    return res[i];
  }
}

void write(unsigned int i, char x) {
  if (i == 0x02000C0A) {
    // printf("%x %x\n", i, x);
  }
  if (i >= 0x02000000) {
    i -= 0x02000000;
    if (i == 0 || i == 1) {
      // fprintf(stderr, "0x%x\n", x);
    }
    res[i] = x;
  }
}

void init2() {
  r5 = r0; // 読み込み元
  r4 = r1; // 書き込み先
  r6 = r2;
  r7 = 0x7f;
  if (r6 <= 0) {
    goto x00003b8e;
  }
x00003b52:
  if (r2 == 0x3c86) {
    // printf("%x %x %x %x %x %x %x %x\n", r0, r1, r2, r3, r4, r5, r6, r7);
  }
  /*
    printf(" r0:0x%x\n",r0);
    printf(" r1:0x%x\n",r1);
    printf(" r2:0x%x\n",r2);
    printf(" r3:0x%x\n",r3);
    printf(" r4:0x%x\n",r4);
    printf(" r5:0x%x\n",r5);
    printf(" r6:0x%x\n",r6);
    printf(" r7:0x%x\n",r7);
  */
  
  r3 = 0;
  // r3 = r5[r3]; // 1byte 繰り返し回数
  r3 = (char)get(r5+r3); // 符号あり
  if (r1 == 0x02000000) {
    // fprintf(stderr, "%x %x\n", r3, r5+r3);
  }
  // fprintf(stderr, "%x %x\n", r3, r5);
  r5 += 1;
  if (r3 < 0) {
    goto x00003b70;
  }
  r3 += 1;
  r2 = r2-r3;
  
x0003b60:
  
  r0 = (unsigned char)get(r5); // 1byte
  // fprintf(stderr, "r0: %x\n", r0);
  // *r4 = r0; // 1byte
  write(r4, r0);
  r5 += 1;
  r4 += 1;
  r3 -= 1;
  if (r3 != 0) {
    goto x0003b60;
  }
  goto x00003b8a;
  
x00003b70:
  
  r3 &= r7; // 繰り返し回数が負の数だった場合下7bitを取り出す
  r3 += 3;
  r2 = r2-r3;
  r0 = (unsigned char)get(r5); // 1byte データを取り出して
  if (r5 == 0x81e9c5b+1) {
    // printf("%x %x\n", get(r5), (unsigned char)get(r5));
    // printf("%x %x %x %x %x %x %x %x\n", r0, r1, r2, r3, r4, r5, r6, r7);
  }
  r1 = r4-r0;
  r5 += 1;
  
x00003b7c:
  
  r0 = (unsigned char)get(r1); // 1byte
  // *r4 = r0; // 1byte
  write(r4, r0);
  r1 += 1;
  r4 += 1;
  r3 -= 1;
  if (r3 != 0) {
    goto x00003b7c;
  }
  
x00003b8a:
  
  if (r2 > 0) {
    goto x00003b52;
  }
  
x00003b8e:
  
  if (r2 != 0) {
    goto x00003b96;
  }
  r0 = r6;
  goto x00003b98;
  
x00003b96:
  
  r0 = 0;
  
x00003b98:

  // fprintf(stderr, "%x %x %x %x %x %x %x %x\n", r0, r1, r2, r3, r4, r5, r6, r7);
  return;
}

void init(int id, int sid) {
  assert(0);
  r0 = 0x03004420;
  r1 = id;
  r9 = r1;
  r0 = sid;
  r10 = r0;
  r2 = 0x03004398;
  r8 = r2;
  r2 = 0x080b8c1c;
  r1 <<= 1;
  r1 += r9;
  r1 <<= 2;
  r0 = r1+r2;
  fprintf(stderr, "r0: %x\n", r0);
  r4 = get4(r0);
  fprintf(stderr, "r4: %x\n", r4);
  r0 = r8;
  // *r0 = r4;
  r7 = 0x03004394;
  r0 = r2+4;
  r0 = r1+r0;
  fprintf(stderr, "r0: %x\n", r0);
  r0 = get4(r0);
  fprintf(stderr, ">r0: %x\n", r0);
  // *r7 = r0;
  r3 = 0x03004390;
  r2 += 8;
  r1 = r1+r2;
  fprintf(stderr, "r1: %x\n", r1);
  r1 = get4(r1);
  fprintf(stderr, "r1: %x\n", r1);
  // *r3 = r1;
  r6 = 0x03000DC0;
  r1 = 0x80;
  r1 <<= 12;
  // r6[10] = r1;
  r2 = get4(r4);
  fprintf(stderr, "r2: %x\n", r2);
  r0 = r0+r2;
  r2 = get4(r4+4);
  fprintf(stderr, "r2: %x\n", r2);
  fprintf(stderr, "r0: %x\n", r0);
  r0 = 0x81e73b0;
  return;
}

/*
  r0: なにかの配列 0x03003134
  r1: heri.x
  r2: heri.y
*/
void chk(int w, int h) {
  r5 = r1;
  r5 <<= 0x10;
  r2 <<= 0x10;
  r6 = 0x02000004; // r6 = r0[0xc];
  r1 = r5>>0x10;
  r9 = r1;
  r7 = r2>>0x10;
  r1 = w; // r1 = r0[0x8];
  r8 = r1;
  r1 = h; // r1 = r0[0
  r0 = 0x081d2870;
  r10 = r0;
  r2 >>= 0x13; // yを8で割ったの
  r0 = r5;
  r1 = r8;
  
}

int main(void) {
  // init(0, 1);
  /*
    r0 = 0x081e73b0;
    r1 = 0x02000000;
    r2 = 0x8000;
  */
  
  // r0 = 0x081e9c40; int w = 0x80; int h = 0x40; // 0-0
  // r0 = 0x081ec764; int w = 0x80; int h = 0x40; // 0-1
  // r0 = 0x081ef448; int w = 0x80; int h = 0x40; // 0-2
  // r0 = 0x081F2220; int w = 0x40; int h = 0x40; // 0-3
  // r0 = 0x081F4E64; int w = 0x80; int h = 0x40; // 0-4
  // r0 = 0x081FF3E4; int w = 0x80; int h = 0x40; // 1-0
  // r0 = 0x081E9EF4; int w = 0x80; int h = 0x40; dame
  // r0 = 0x08201E78; int w = 0x80; int h = 0x40;
  // r0 = 0x082056C8; int w = 0x80; int h = 0x80;
  // r0 = 0x082168FC; int w = 0x80; int h = 0x40;
  // r0 = 0x08218F34; int w = 0x80; int h = 0x80;
  // r0 = 0x0821D0F8; int w = 0x80; int h = 0x80;
  // r0 = 0x0822E01C; int w = 0x80; int h = 0x80;
  // r0 = 0x08231EB4; int w = 0xC0; int h = 0x40;
  // r0 = 0x08283F0C; int w = 0xC0; int h = 0x80;
  // r0 = 0x082A273C; int w = 0x80; int h = 0xC0;
  r0 = 0x0829B9D8; int w = 0x80; int h = 0x80; // 7-0
  r1 = 0x02000000;
  // r1 = 0x02004004;
  r2 = w*2*h+0x4;
  // int base = r1;
  int len = r2;
  
  init2();
  // printf("%x %x %x %x %x %x %x %x\n", r0, r1, r2, r3, r4, r5, r6, r7);
  //ofstream ofs("dump.dat", std::ofstream::binary);
  /*
    for (int i = 0; i < r2; i++) {
    char c = get(base+i);
    ofs.write(&c, 1);
    }
  */
  // ofs.write(res, len);
  //*
  int x, y;
  printf("%d %d\n", w, h);
  /*
    for (int i = 0; i < w*2*h+0x4*2; i++) {
    printf("%02x ", res[w*2*h+i]&0xff);
    if ((i+1)%16 == 0) puts("");
    }
  */
  
#if 1
  for (y = 0; y < h; y += 1) {
    for (x = 0; x < w*2; x += 1) {
      //*
      printf("%02x", ((res[y*w*2+x/2*2+(1-x%2)])&0xff));
      if (x%2 == 1) printf(" ");
      // */
      /*
        if ((res[y*w*2+x]&0xff) == 0xea ||
        (res[y*w*2+x]&0xff) == 0xfd ||
        (res[y*w*2+x]&0xff) == 0xfe) {
        printf("o");
        } else if (res[y*w*2+x] != 0) {
        printf("#");
        } else {
        printf(" ");
        }
        // */
    }
    puts("");
  }
#endif
  //*/
  
  /*
    for (int i = 0; i < len; i++) {
    if (i%16 == 0) {
    printf("%08X: ", base+i);
    }
    printf("%02x ", res[i]&0xff);
    if ((i+1)%16 == 0) {
    puts("");
    }
    }
  //*/
}
