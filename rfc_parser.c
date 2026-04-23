#include <stdio.h>
#include <string.h> // strstr ve strncpy fonksiyonlari için
#include "rfc_parser.h"

Request parse_rfc9213(int id, const char* raw_str) {
    Request req; // Istegimizi olusturuyoruz
    req.id = id;
    
    // RFC 9213 standardina göre, eger aciliyet belirtilmezse varsayilan deger 3'tür.
    req.urgency = 3; 
    req.incremental = false;
    
    // Gelen ham metni (raw_str), istegimizin içindeki raw_priority dizisine güvenlice kopyaliyoruz
    strncpy(req.raw_priority, raw_str, sizeof(req.raw_priority) - 1);
    req.raw_priority[sizeof(req.raw_priority) - 1] = '\0'; // Dizinin sonuna bitis karakteri ekliyoruz

    // --- 1. URGENCY (u=) DEGERINI BULMA ---
    // strstr fonksiyonu, bir metin içinde baska bir metni arar.
    char *u_ptr = strstr(raw_str, "u="); 
    if (u_ptr != NULL) {
        // "u=" metnini bulduysak, hemen yanindaki tam sayiyi (%d) urgency içine kaydet
        sscanf(u_ptr, "u=%d", &req.urgency);
        
        // Güvenlik kalkani: Standartlara göre urgency 0 ile 7 arasinda olmalidir.
        if (req.urgency < 0) req.urgency = 0;
        if (req.urgency > 7) req.urgency = 7;
    }

    // --- 2. INCREMENTAL (i) DEGERINI BULMA ---
    char *i_ptr = strstr(raw_str, "i");
    if (i_ptr != NULL) {
        // Eger metnin içinde 'i' harfi varsa, incremental true olur.
        req.incremental = true;
    }

    return req; // Içini doldurdugumuz paketi geri gönderiyoruz
}
