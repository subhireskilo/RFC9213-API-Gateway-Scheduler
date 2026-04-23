#ifndef REQUEST_H
#define REQUEST_H

#include <stdbool.h>

// Sisteme gelen tek bir HTTP istegini (Request) temsil eden yapi
typedef struct {
    int id;               // Istegin numarasi
    int urgency;          // RFC 9213 Aciliyet degeri (0 en yüksek, 7 en düsük)
    bool incremental;     // true/false
    char raw_priority[50]; // Orijinal metin (Örn: "u=3, i")
} Request;

// Ekrana yazdirma fonksiyonunun tanimini ekliyoruz:
void print_request(Request req);

#endif
