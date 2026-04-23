#include <stdio.h>
#include "request.h"

// Istegin detaylarini terminale (siyah ekrana) yazdiran fonksiyon
void print_request(Request req) {
    printf("Request ID: %d | Urgency: %d | Incremental: %s | Raw: [%s]\n", 
           req.id, 
           req.urgency, 
           req.incremental ? "true" : "false", 
           req.raw_priority);
}
