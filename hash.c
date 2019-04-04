typedef struct List List;
struct List{
  char* key;
  int value;
  List* next;
};

List* table[HASH_SIZE];

void init_table(){
  for(int i = 0; i < HASH_SIZE; i++){
    table[i] = NULL;
  }
}

void display() {
  int i = 0;
  for(i = 0; i < HASH_SIZE; i++){
    if (table[i] != NULL) {
      printf("[%s, %d]\n", table[i]->key, table[i]->value);
    }
  }
}

unsigned int hash(char* str){
  unsigned int h;
  unsigned char *p;
  h = 0;
  for(p = (unsigned char*)str; *p != '\0'; p++){
    h = MULTIPLIER * h + *p;
  }
  return h % HASH_SIZE;
}

List* lookup(char* s){
  int index = hash(s);
  while (table[index] != NULL) {
    if (strcmp(table[index]->key, s)) {
      return table[index];
    }
    index++;
    index %= HASH_SIZE;
  }
  return NULL;
}

void insert(char* k, int val){
  int index;
  List* new = (List*)malloc(sizeof(struct List));
  index = hash(k);
  new->key = k;
  new->value = val;
  new->next = table[index];
  table[index] = new;
}

int getHashValue(List* p){
  return p->value;
}

char* getHashKey(List* p){
  return p->key;
}
