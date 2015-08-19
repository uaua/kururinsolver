#include <cstdio>

using namespace std;

unsigned short g[1111][1111];

int main(void) {
	int w, h;
	scanf("%d %d", &w, &h);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			scanf("%hx", &g[i][j]);
      // g[i][j] = g[i][j]>>8 | g[i][j]<<8;
			printf("%04x ", g[i][j]);
		}
    puts("");
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			unsigned short p = (g[i][j]&0x3ff)-1;
			if (p <= 0x9e) {
				printf("%04x", p);
			} else {
				printf("    ");
			}
		}
		puts("");
	}
	return 0;
}
