#ifndef RFC_PARSER_H
#define RFC_PARSER_H

#include "request.h"

// Gelen ID'yi ve metni alip, içini doldurdugu bir Request nesnesi döndüren fonksiyon
Request parse_rfc9213(int id, const char* raw_str);

#endif
