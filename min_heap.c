#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

// 1. Heap'i Bellekte Olusturma (malloc kullanimi)
MinHeap* init_heap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    // Istekleri tutacak diziyi bellekte ayiriyoruz
    heap->array = (Request*)malloc(capacity * sizeof(Request)); 
    return heap;
}

// Yardimci Fonksiyon: Iki istegin yerini degistirme
void swap(Request *a, Request *b) {
    Request temp = *a;
    *a = *b;
    *b = temp;
}

// 2. Eleman Ekleme ve Yukari Kaydirma (Insert & Heapify Up)
void insert(MinHeap *heap, Request req) {
    // EGER DIZI DOLDUYSA: realloc ile kapasiteyi 2 katina çikar! (Bellek yönetimi puani)
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->array = (Request*)realloc(heap->array, heap->capacity * sizeof(Request));
        printf(" -> [Sistem] Heap kapasitesi %d'ye cikarildi.\n", heap->capacity);
    }

    // Yeni elemani dizinin en sonuna ekle
    int i = heap->size;
    heap->array[i] = req;
    heap->size++;

    // HEAPIFY UP (Yukari Kaydirma): Eklenen eleman, anne/babasindan (parent) daha küçük bir urgency'ye 
    // sahipse (yani daha acilse) onunla yer degistir. Ta ki dogru yeri bulana kadar.
    // Parent formülü: (i - 1) / 2
    while (i != 0 && heap->array[(i - 1) / 2].urgency > heap->array[i].urgency) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Yardimci Fonksiyon: Asagi Kaydirma (Heapify Down)
void heapify_down(MinHeap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Sol çocuk daha acilse (urgency daha küçükse) onu seç
    if (left < heap->size && heap->array[left].urgency < heap->array[smallest].urgency)
        smallest = left;

    // Sag çocuk daha acilse onu seç
    if (right < heap->size && heap->array[right].urgency < heap->array[smallest].urgency)
        smallest = right;

    // Eger en küçük eleman ebeveyn (i) degilse, yer degistir ve asagi dogru kontrol etmeye devam et
    if (smallest != i) {
        swap(&heap->array[i], &heap->array[smallest]);
        heapify_down(heap, smallest);
    }
}

// 3. En Yüksek Öncelikli Elemani Çekme (Extract Min)
Request extract_min(MinHeap *heap) {
    if (heap->size <= 0) {
        // Heap bossa hatali bir istek döndür
        Request empty_req = {-1, -1, false, "BOS"};
        return empty_req;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->array[0]; // Sadece 1 eleman varsa onu ver ve bitir
    }

    // Kök dügümdeki (index 0) en acil elemani kaydet
    Request root = heap->array[0];

    // Dizinin en sonundaki elemani alip köke (en tepeye) koyuyoruz
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    // Tepedeki eleman kurali bozdugu için onu "Asagi Kaydir" (Heapify Down) fonksiyonuyla dogru yere itiyoruz
    heapify_down(heap, 0);

    return root; // En acil elemani teslim et
}

// 4. Bellek Temizligi (free)
void free_heap(MinHeap *heap) {
    free(heap->array); // Önce içindeki diziyi yok et
    free(heap);        // Sonra heap'in kendisini yok et
    printf("\n[Sistem] Bellek basariyla temizlendi (Sifir Bellek Sizintisi).\n");
}
