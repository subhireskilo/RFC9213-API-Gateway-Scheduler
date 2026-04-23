#include <stdio.h>
#include <stdlib.h>
#include "request.h"
#include "rfc_parser.h"
#include "min_heap.h"

int main() {
    printf("--- API Gateway Priority Scheduler ---\n\n");
    
    // 1. Min-Heap olustur. (Kapasiteyi bilerek 2 verdik ki realloc'un çalistigini görelim)
    MinHeap *gateway_queue = init_heap(2);
    
    // 2. Istekleri kuyruga KARISIK sirayla ekleyelim (u=5, u=1, u=7, u=0)
    printf("--- Istekler Gateway'e Geliyor ---\n");
    
    Request r1 = parse_rfc9213(101, "u=5");
    insert(gateway_queue, r1);
    printf("Eklendi: ID %d (Urgency: 5)\n", r1.id);

    Request r2 = parse_rfc9213(102, "u=1, i");
    insert(gateway_queue, r2);
    printf("Eklendi: ID %d (Urgency: 1)\n", r2.id);

    // 3. elemani eklerken kapasite 2 oldugu için realloc çalisacak!
    Request r3 = parse_rfc9213(103, "u=7"); 
    insert(gateway_queue, r3);
    printf("Eklendi: ID %d (Urgency: 7)\n", r3.id);

    Request r4 = parse_rfc9213(104, "u=0"); // En acil istek!
    insert(gateway_queue, r4);
    printf("Eklendi: ID %d (Urgency: 0)\n", r4.id);

    // 3. Istekleri Gateway'den Islenmek Üzere Çikaralim (Extract)
    // Beklentimiz: Ne sirayla eklendigine bakilmaksizin 0, 1, 5, 7 sirasiyla çikmasi!
    printf("\n--- Kuyruktan Cekilen Istekler (Oncelik Sirasiyla) ---\n");
    
    while (gateway_queue->size > 0) {
        Request islenecek_istek = extract_min(gateway_queue);
        printf("ISLENIYOR -> ");
        print_request(islenecek_istek);
    }

    // 4. Tahsis edilen bellegi isletim sistemine geri ver
    free_heap(gateway_queue);

    return 0;
}
