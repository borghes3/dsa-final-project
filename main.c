#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AIR_ROUTES 5
#define MAX_COST 100
#define INF 0x3f3f3f3f

typedef struct {
  uint32_t dest;
} AirRoute;
typedef struct {
  uint8_t cost;
  AirRoute routes[MAX_AIR_ROUTES];
  uint8_t routes_count;
} Hexagon;
typedef struct {
  int index;  
  int dist;   
} HeapNode;

typedef struct {
  HeapNode* nodes;
  int size;
  int capacity;
} MinHeap;

typedef struct {
  int start, dest;
  int cost;
  int gen;
} Cache;

Hexagon template = {.routes_count = 0, .cost = 1};
Hexagon* map;
int rows = 0, cols = 0;

Cache cache[2048];
int cacheGeneration = 1;
int cachePos = 0;  

void init() {
  
  if (map != NULL) {
    free(map);
    map = NULL;
  }
  
  if (scanf("%d %d", &cols, &rows) == 2) {
    map = malloc(rows * cols * sizeof(Hexagon));
    if (map == NULL) {
      printf("KO\n");
      return;
    }
    
    map[0] = template;
    int copied = 1;
    while (copied < rows * cols) {
      int copy =
          (copied < rows * cols - copied) ? copied : (rows * cols - copied);
      memcpy(&map[copied], map, copy * sizeof(Hexagon));
      copied += copy;
    }
    
    cacheGeneration++;
    cachePos = 0;
    printf("OK\n");
  }
}

bool validateCoords(int x, int y) {
  if (x < 0 || y < 0 || x >= cols || y >= rows) {
    return false;
  }
  return true;
}
int hash(int x, int y) { return y * cols + x; }
int safeIncrement(int base, int increment) {
  int t = base + increment;
  if (t < 0)
    return 0;
  else if (t > 100)
    return 100;
  else
    return t;
}
int distance(int x1, int y1, int x2, int y2) {
  int dx = x2 - x1;
  int dy = y2 - y1;

  if ((y1 & 1) == 0) {  
    return (abs(dx) + abs(dy) + abs(dx - dy)) / 2;
  } else {  
    return (abs(dx) + abs(dy) + abs(dx + dy)) / 2;
  }
}

void toggleAirRoute() {
  
  if (map == NULL) {
    printf("KO\n");
    return;
  }
  int x1, x2, y1, y2;
  if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) == 4) {
    if (!validateCoords(x1, y1) || !validateCoords(x2, y2)) {
      printf("KO\n");
      return;
    }
    int startHash = hash(x1, y1);
    int destHash = hash(x2, y2);
    Hexagon* start = &map[startHash];

    
    if (start->routes_count == 0) {
      start->routes[0] = (AirRoute){.dest = destHash};
      start->routes_count++;
      
      cacheGeneration++;
      cachePos = 0;
      printf("OK\n");
      return;
    }

    
    for (int i = 0; i < start->routes_count; i++) {
      
      if (start->routes[i].dest == destHash) {
        start->routes[i] = start->routes[start->routes_count - 1];
        start->routes_count--;
        
        cacheGeneration++;
        cachePos = 0;
        printf("OK\n");
        return;
      }
    }

    
    if (start->routes_count == MAX_AIR_ROUTES) {
      printf("KO\n");
      return;
    } else {
      
      start->routes[start->routes_count] = (AirRoute){.dest = destHash};
      start->routes_count++;
      
      cacheGeneration++;
      cachePos = 0;
      printf("OK\n");
      return;
    }
  }
}

void changeCost() {
  
  if (map == NULL) {
    printf("KO\n");
    return;
  }
  int x, y, v, r;
  if (scanf("%d %d %d %d", &x, &y, &v, &r) == 4) {
    if (!validateCoords(x, y) || abs(v) > 10 || r <= 0) {
      printf("KO\n");
      return;
    }
    if (r == 1) {  
      int targetHash = hash(x, y);
      map[targetHash].cost = safeIncrement(map[targetHash].cost, v);
      
      cacheGeneration++;
      cachePos = 0;
      printf("OK\n");
      return;
    } else {  
      
      int cq = x - (y - (y & 1)) / 2;
      int cr = y;
      
      for (int dq = -r + 1; dq <= r - 1; dq++) {
        for (int dr = -r + 1; dr <= r - 1; dr++) {
          int ds = -dq - dr;
          int nq = cq + dq;
          int nr = cr + dr;
          

          
          int dist = fmax(fmax(abs(dq), abs(dr)), abs(ds));
          if (dist >= r) continue;

          
          int nx = nq + (nr - (nr & 1)) / 2;
          int ny = nr;

          if (!validateCoords(nx, ny)) continue;

          
          int numeratore = v * (r - dist);  
          int inc = numeratore / r;         
          if (numeratore < 0 && (numeratore % r) != 0)
            inc -= 1;  

          if (inc != 0) {
            int h = hash(nx, ny);
            map[h].cost = safeIncrement(map[h].cost, inc);
          }
        }
      }
      
      cacheGeneration++;
      cachePos = 0;
      printf("OK\n");
      return;
    }
  }
}

void heapSwap(HeapNode* a, HeapNode* b) {
  HeapNode tmp = *a;
  *a = *b;
  *b = tmp;
}

void heapifyUp(MinHeap* heap, int i) {
  while (i > 0) {
    int parent = (i - 1) / 2;
    if (heap->nodes[parent].dist <= heap->nodes[i].dist) break;
    heapSwap(&heap->nodes[parent], &heap->nodes[i]);
    i = parent;
  }
}

void heapifyDown(MinHeap* heap, int i) {
  int left, right, smallest;
  while (1) {
    left = 2 * i + 1;
    right = 2 * i + 2;
    smallest = i;
    if (left < heap->size &&
        heap->nodes[left].dist < heap->nodes[smallest].dist)
      smallest = left;
    if (right < heap->size &&
        heap->nodes[right].dist < heap->nodes[smallest].dist)
      smallest = right;
    if (smallest == i) break;
    heapSwap(&heap->nodes[i], &heap->nodes[smallest]);
    i = smallest;
  }
}

void heapInsert(MinHeap* heap, int index, int dist) {
  if (heap->size == heap->capacity) return;  
  heap->nodes[heap->size].index = index;
  heap->nodes[heap->size].dist = dist;
  heapifyUp(heap, heap->size);
  heap->size++;
}

HeapNode heapExtractMin(MinHeap* heap) {
  HeapNode res = heap->nodes[0];
  heap->size--;
  if (heap->size > 0) {
    heap->nodes[0] = heap->nodes[heap->size];
    heapifyDown(heap, 0);
  }
  return res;
}

uint32_t* dist = NULL;
uint16_t* distGen = NULL;
uint16_t* visitedGen = NULL;
int generation = 0;

void initGlobals(int totalCells) {
  int oldCapacity = 0;

  if (!dist) {
    dist = malloc(sizeof(int) * totalCells);
    distGen = malloc(sizeof(int) * totalCells);
    visitedGen = malloc(sizeof(int) * totalCells);
  } else if (totalCells > oldCapacity) {
    dist = realloc(dist, sizeof(int) * totalCells);
    distGen = realloc(distGen, sizeof(int) * totalCells);
    visitedGen = realloc(visitedGen, sizeof(int) * totalCells);
  }

  
  for (int i = 0; i < totalCells; i++) {
    distGen[i] = 0;
    visitedGen[i] = 0;
  }

  oldCapacity = totalCells;
}

int getDist(int idx) { return (distGen[idx] == generation) ? dist[idx] : INF; }

void setDist(int idx, int value) {
  dist[idx] = value;
  distGen[idx] = generation;
}

int isVisited(int idx) { return (visitedGen[idx] == generation); }
void setVisited(int idx) { visitedGen[idx] = generation; }

int cacheGet(int start, int dest) {
  for (int i = 0; i < 2048; i++) {
    if (cache[i].gen == cacheGeneration && cache[i].start == start &&
        cache[i].dest == dest) {
      return cache[i].cost;
    }
  }
  return -2;  
              
}
void cachePut(int start, int dest, int cost) {
  cache[cachePos].start = start;
  cache[cachePos].dest = dest;
  cache[cachePos].cost = cost;
  cache[cachePos].gen = cacheGeneration;

  cachePos = (cachePos + 1) % 2048;
}

void travelCost() {
  if (map == NULL) {
    printf("-1\n");
    return;
  }

  int x1, y1, x2, y2;
  if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4) return;
  if (!validateCoords(x1, y1) || !validateCoords(x2, y2)) {
    printf("-1\n");
    return;
  }

  int startHash = hash(x1, y1);
  int destHash = hash(x2, y2);

  if (map[startHash].cost == 0) {
    printf("-1\n");
    return;
  }
  if (startHash == destHash) {
    printf("0\n");
    return;
  }

  
  int cached = cacheGet(startHash, destHash);
  if (cached != -2) {
    printf("%d\n", cached);
    return;
  }

  
  int totalCells = rows * cols;
  initGlobals(totalCells);
  generation++;

  setDist(startHash, 0);

  MinHeap heap;
  heap.capacity = totalCells;
  heap.size = 0;
  heap.nodes = malloc(sizeof(HeapNode) * totalCells);
  heapInsert(&heap, startHash, 0);

  while (heap.size > 0) {
    HeapNode hn = heapExtractMin(&heap);
    int u = hn.index;
    int currentDist = hn.dist;

    if (isVisited(u)) continue;
    setVisited(u);

    if (u == destHash) {
      printf("%d\n", currentDist);
      free(heap.nodes);
      
      cachePut(startHash, destHash, currentDist);
      return;
    }

    
    
    if (map[u].cost == 0) continue;

    int ux = u % cols;
    int uy = u / cols;

    
    int cq = ux - (uy - (uy & 1)) / 2;
    int cr = uy;
    

    int dq[6] = {+1, +1, 0, -1, -1, 0};
    int dr[6] = {0, -1, -1, 0, +1, +1};

    for (int k = 0; k < 6; k++) {
      int nq = cq + dq[k];
      int nr = cr + dr[k];
      int nx = nq + (nr - (nr & 1)) / 2;
      int ny = nr;

      if (!validateCoords(nx, ny)) continue;
      int v = hash(nx, ny);

      
      if (map[v].cost == 0 && v != destHash) continue;

      int alt = currentDist + map[u].cost;
      if (alt < getDist(v)) {
        setDist(v, alt);
        heapInsert(&heap, v, alt);
      }
    }

    
    for (int r = 0; r < map[u].routes_count; r++) {
      int v = map[u].routes[r].dest;

      
      if (map[v].cost == 0 && v != destHash) continue;

      int alt = currentDist + map[u].cost;
      if (alt < getDist(v)) {
        setDist(v, alt);
        heapInsert(&heap, v, alt);
      }
    }
  }

  
  
  cachePut(startHash, destHash, -1);
  printf("-1\n");
  free(heap.nodes);
}

int main() {
  setbuf(stdout, NULL);
  char istruzione[50] = "";

  while (scanf("%s", istruzione) > 0) {
    if (strcmp(istruzione, "init") == 0) {
      init();
    }
    if (strcmp(istruzione, "toggle_air_route") == 0) {
      toggleAirRoute();
    }
    if (strcmp(istruzione, "change_cost") == 0) {
      changeCost();
    }
    if (strcmp(istruzione, "travel_cost") == 0) {
      travelCost();
    }
  }
  return 0;
}