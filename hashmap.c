#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {
  int pos=hash(key, map->capacity); 
  if(map->buckets[pos] != NULL){ 
    while(map->buckets[pos] != NULL){
      if(pos==map->capacity-1){
        pos=0;
      }else{
        pos +=1;
      }
    }
  }
  Pair* aux = (Pair*)malloc(sizeof(Pair*)); 
  aux->key = key;
  aux->value = value;
  map->buckets[pos] = aux;
  map->size += 1;
}
void enlarge(HashMap * map){
    enlarge_called = 1; //no borrar (testing purposes)
  int DobleCap=map->capacity*2;
  Pair** OldBuck=map->buckets;
  map->buckets=(Pair**)malloc(DobleCap*sizeof(Pair*));
  map->size=0;
  map->capacity=DobleCap;
  map->current=-1;
  for(int i=0;i<map->capacity/2;i++){
    if(OldBuck[i]!=NULL){
      insertMap(map,OldBuck[i]->key,OldBuck[i]->value);
    }
  }
}

HashMap * createMap(long capacity) {
  HashMap*mapa=(HashMap*)malloc(capacity*sizeof(HashMap*));
  mapa->buckets=(Pair**)calloc(capacity,sizeof(Pair*));
  mapa->capacity=capacity;
  mapa->current=-1;
  return mapa;
}

void eraseMap(HashMap * map,  char * key) {   
  int pos=hash(key,map->capacity);
  while(map->buckets[pos]!=NULL){
    if(is_equal(key,map->buckets[pos]->key)!=0){
      map->current=pos;
      map->buckets[pos]->key=NULL;
      map->size-=1;
    }
    if(pos==map->capacity-1){
      pos=0;
    }
    else{
      pos+=1;
    }
  }
}

Pair * searchMap(HashMap * map,  char * key) {   
  int pos=hash(key,map->capacity);
  while(map->buckets[pos]!=NULL){
    if(is_equal(key,map->buckets[pos]->key)!=0)){
      map->current=pos;
      return map->buckets[pos];
    }
    if(pos==map->capacity-1){
      pos=0;
    }
    else{
      pos+=1;
    }
  }
    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
