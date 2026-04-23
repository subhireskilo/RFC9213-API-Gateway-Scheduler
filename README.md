# RFC 9213 Uyumlu Modüler API Gateway İstek Zamanlayıcısı

**Veri Yapıları ve Algoritmalar Dersi Final Projesi**

Bu proje, C dili kullanılarak geliştirilmiş, endüstri standardı olan **RFC 9213 (Extensible HTTP Priorities)** protokolüne uygun bir API Gateway İstek Zamanlayıcısıdır. Projede geleneksel FIFO veya O(N) karmaşıklığına sahip diziler yerine, yüksek performanslı **Min-Heap (Öncelikli Kuyruk)** veri yapısı kullanılmıştır.

## 🚀 Projenin Özellikleri
- **RFC 9213 Parser:** Gelen karmaşık metin tabanlı HTTP başlıklarını (Örn: `u=3, i`) güvenle ayrıştırır.
- **O(log N) Performansı:** Min-Heap mimarisi sayesinde saniyede binlerce isteği en hızlı şekilde sıraya sokar.
- **Dinamik Ölçeklenebilirlik:** Sistem kapasitesi dolduğunda çökmek yerine `realloc` ile kendini otomatik olarak büyütür.
- **Sıfır Bellek Sızıntısı:** İşlem bitiminde tüm dinamik bellek, işletim sistemine temiz bir şekilde iade edilir.
- **Modüler Mimari:** "Separation of Concerns" prensibiyle `.c` ve `.h` dosyaları tamamen izole edilmiştir.

## 📂 Dosya Yapısı
- `main.c`: Merkezi kontrolcü ve test ortamı.
- `request.h / .c`: Ortak veri yapısı (Struct).
- `rfc_parser.h / .c`: Güvenli metin ayrıştırıcı.
- `min_heap.h / .c`: Min-Heap algoritma motoru.

## 🛠️ Nasıl Çalıştırılır?
Linux veya macOS ortamında (ya da Makefile destekli bir terminalde) projeyi derlemek için:
```bash
make
./gateway

Hazırlayan: Suphi - Kırklareli Üniversitesi Yazılım Mühendisliği
