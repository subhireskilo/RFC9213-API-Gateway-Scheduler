#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "request.h"

// Min-Heap (Öncelikli Kuyruk) yapisi
typedef struct {
    Request *array; // Istekleri tutacagimiz dinamik dizi
    int capacity;   // Dizinin maksimum alabilecegi eleman sayisi
    int size;       // Su anda içinde bulunan eleman sayisi
} MinHeap;

// Algoritma Fonksiyonlarinin Tanimlari
MinHeap* init_heap(int capacity);               // Kuyrugu baslatir
void insert(MinHeap *heap, Request req);        // Kuyruga yeni eleman ekler (Heapify Up)
Request extract_min(MinHeap *heap);             // En acil elemani alir ve kuyruktan siler (Heapify Down)
void free_heap(MinHeap *heap);                  // Bellegi temizler (Zero Memory Leak)

#endif
