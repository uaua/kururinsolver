//#define _GLIBCXX_DEBUG
#include <array>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <queue>

using namespace std;

unsigned short g[1111][1111];
vector<unsigned short> g2;
int w, h;
ifstream ifs("kururin.GBA");
char get(unsigned int i) {
  if (i >= 0x08000000) {
    i -= 0x08000000;
    ifs.seekg(i, ios_base::beg);
    char b;
    ifs.read(&b, 1);
    return b;
  } else {
  	assert(0);
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
  	assert(0);
  }
}

short dxy[][17][2] = {
#include "ae.txt"
};

inline unsigned short zx(int ang, int i) {
  assert(ang >= 0 && ang < 65536);
  assert(i >= 0 && i < 17);
  return dxy[ang/256][i][0];
}

inline unsigned short zy(int ang, int i) {
  assert(ang >= 0 && ang < 65536);
  assert(i >= 0 && i < 17);
  return dxy[ang/256][i][1];
}

class list {
 public:
  list *l;
  int val;
  list() {
    l = nullptr;
    val = -1145141919;
  }
  list(list *n, int v) {
    l = n;
    val = v;
  }
};

int gx, gy;

struct state {
  unsigned x, y;
  int cost;
  list *l;
  
  state(unsigned x, unsigned y, int cost, list* l)
      : x(x), y(y), cost(cost), l(l) {}
  bool operator>(const state& e) const {
    // return cost+abs(gx-x)+abs(gy-y) > e.cost+abs(gx-e.x)+abs(gy-e.y);
    // return x < e.x;
    return cost > e.cost;
  }
};

// bool cost[555][222][65536];
#define USE_LIM 1
#if USE_LIM
// vector<vector<vector<int>>> cnt;
std::array<std::array<std::array<char, 1000>, 1000>, 1000> cnt;
#else
vector<vector<int>> cnt;
#endif
// int cnt[555][222];
const int lim = 1555;

int main(void) {
	scanf("%d %d", &w, &h);
#if USE_LIM
  // cnt.resize(1000, vector<vector<int>>(1000, vector<int>(lim, 0)));
#else
  cnt.resize(1777, vector<int>(1777, 0));
#endif
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			scanf("%hx", &g[i][j]);
      g2.push_back(g[i][j]);
		}
	}

  int sx = -1, sy = -1;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
      if (g[i][j] == 0x00fb) {
        sx = j-1;
        sy = i+1;
        fprintf(stderr, "%d %d\n", sx, sy);
        fprintf(stderr, "%d %d\n", sx*8, sy*8);
      }
      if (g[i][j] == 0x00ff) {
        gx = j*8 << 16;
        gy = i*8 << 16;
      }
      /*
			unsigned short p = g[i][j]&0x3ff;
			if (p <= 0x9e) {
      // ok
			} else {
      // ng
			}
      */
		}
	}

  assert(sx >= 0 && sy >= 0);

  priority_queue<state, vector<state>, greater<state> > q;
  q.push(state((sx*8)<<16, (sy*8)<<16, 0, nullptr));
  /*
  for (int j = 0; j < 16; j++) {
    printf("%d %d:%d %d\n", ((sx*8)), ((sy*8)), unsigned(zx(256*4, j)), unsigned(zy(256*4, j)));
    unsigned px = ((sx*8)<<16) + (unsigned(zx(256*4, j))<<16);
    unsigned py = ((sy*8)<<16) + (unsigned(zy(256*4, j))<<16);
    int pi = (py>>16);
    int pj = (px>>16);
    printf("%d %d\n", pj, pi);
    }*/
  // return 0;

  std::array<unsigned, 24> dx {
        0x00000000, 0x00000000, 0x00000000, // ue
        0x00018000, 0x00024000, 0x00030000, // migi
        0x00000000, 0x00000000, 0x00000000, // shita
        0xfffe8000, 0xfffdc000, 0xfffd0000, // hidari
        0x00010f80, 0x00019740, 0x00021f00, // migi ue
        0x00010f80, 0x00019740, 0x00021f00, // migi shita
        0xfffef080, 0xfffe68c0, 0xfffde100, // hidari shita
        0xfffef080, 0xfffe68c0, 0xfffde100, // hidari ue
            // 0 // houchi
        };
  
  std::array<unsigned, 24> dy {
        0xfffe8000, 0xfffdc000, 0xfffd0000, // ue
        0x00000000, 0x00000000, 0x00000000, // migi
        0x00018000, 0x00024000, 0x00030000, // shita
        0x00000000, 0x00000000, 0x00000000, // hidari
        0xfffef080, 0xfffe68c0, 0xfffde100, // migi ue
        0x00010f80, 0x00019740, 0x00021f00, // migi shita
        0x00010f80, 0x00019740, 0x00021f00, // hidari shita
        0xfffef080, 0xfffe68c0, 0xfffde100, // hidari ue
            // 0, // houchi
        };
  
  std::array<const char*, 24> key{
        "u",  "au",  "abu",
        "r",  "ar",  "abr",
        "d",  "ad",  "abd",
        "l",  "al",  "abl",
        "ru", "aru", "abru",
        "rd", "ard", "abrd",
        "ld", "ald", "abld",
        "lu", "alu", "ablu",
            // "",
  };

  /*
  for (int i = 0; i < 16; i++) {
    printf("%d %d\n", zx(2184, i), zy(2184, i));
  }
  */
  
  int ccc = 0, mx = 0;
  int mini = 1145141919;
  list *l = nullptr;
  
  while (!q.empty()) {
    const state p = q.top(); q.pop();
    // printf("%x %x %d\n", p.x, p.y, p.cost);
    const unsigned x = p.x;
    const unsigned y = p.y;
    // fprintf(stderr, "%x %x %d %d %d %d %d %d\n", x, y, x>>16, y>>16, x>>16>>3, y>>16>>3, (p.cost*0xb6)&0xffff, p.cost);
    if (ccc < p.cost) {
      // fprintf(stderr, "%d %d %d %x %x\n", p.cost, p.x>>16, p.y>>16, p.x, p.y);
      // fflush(stdout);
      ccc = p.cost;
    }
    if (p.cost >= mini) continue;
    if (mx < (p.x>>16)) {
      mx = p.x>>16;
      // fprintf(stderr, "%d\n", mx);
    }
    if (/*g[(y>>16)/8][(x>>16)/8]*/g2[(y>>16)/8*w + (x>>16)/8 + 2] == 0x00fe/* || p.cost == 94*/){
      if (mini > p.cost) {
        printf("cost: %d\n", p.cost);
        mini = p.cost;
        l = p.l;
      }
      // continue;
      // list *l = p.l;
      // break;
      continue;
    }
#if USE_LIM
    if (p.cost >= lim-1) continue;
#endif
    const int ang = ((p.cost) * 0xb6)&0xffff;
    
    // printf("%x %x %d\n", x, y, ang);
    for (int i = 0; i < int(dx.size()); i++) {
    // {
      // int i = history[p.cost];
      const unsigned nx = x+dx[i];
      const unsigned ny = y+dy[i];
      const int nang = (ang + 0xb6)&0xffff;
      bool ok = true;
      for (int j = 0; j < 17; j++) {
        const unsigned px = nx + ((unsigned(zx(nang, j))&0xffff)<<16);
        const unsigned py = ny + ((unsigned(zy(nang, j))&0xffff)<<16);
        const int pi = (py>>16)/8;
        const int pj = (px>>16)/8;
        const unsigned p = unsigned(g2[pi*w+pj+2]&0x3ff)-1;
        if (p <= 0x9eu) {
          ok = false;
        }
      }
      if (ok) {
#if USE_LIM
        if (cnt[ny>>16][nx>>16][p.cost+1] < 100) {
          cnt[ny>>16][nx>>16][p.cost+1] += 1;
#else
        if (cnt[ny>>16][nx>>16] < 100) {
          cnt[ny>>16][nx>>16] += 1;
#endif
          // printf("%d %d %d\n", nx>>16, ny>>16, cnt[ny>>16][nx>>16][p.cost+1]);
          q.push(state(nx, ny, p.cost+1, new list(p.l, i)));
        }
      }
    }
  }
    
    if (l != nullptr) {
      vector<int> keys;
      while (l != nullptr) {
        keys.push_back(l->val);
        // c += 1;
        l = l->l;
      }

      /*
      int ang = 0;
      unsigned x = (sx*8)<<16;
      unsigned y = (sy*8)<<16;
      for_each(keys.rbegin(), keys.rend(), [&x, &y, &ang, dx, dy, key](int i) {
          // printf("\"%s\",", key[i]);
          x += dx[i];
          y += dy[i];
          ang += 0xb6;
          printf("%x, %x, %d\n", x, y, ang);
        });
      */
      for_each(keys.rbegin(), keys.rend(), [key](int i) {
          printf("\"%s\",", key[i]);
        });
      puts("");
      for_each(keys.rbegin(), keys.rend(), [](int i) {
          printf("%d,", i);
        });
      puts("");
      // puts("");
      // printf("%d\n", c);
    }
    return 0;
  }
