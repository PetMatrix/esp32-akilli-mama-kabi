# esp32-akilli-mama-kabi

# 🐱 ESP32 ile Akıllı Kedi Mama Kabı  
Bluetooth ve Wi-Fi destekli, zaman ayarlı otomatik mama verme sistemi  

Bu proje, ESP32 kullanılarak geliştirilen bir akıllı kedi mama kabıdır.  
Sistem, belirlenen saatlerde otomatik mama verir ve porsiyon miktarı Bluetooth üzerinden değiştirilebilir.  
Wi-Fi bağlantısı sayesinde saat internet üzerinden senkronize edilir.  

## 🔧 Kullanılan Bileşenler
- ESP32 Geliştirme Kartı  
- DS3231 RTC Modülü  
- DRV8825 Step Motor Sürücü  
- NEMA17 Step Motor  
- LM2596 Voltaj Düşürücü (Buck Converter)  
- 100 µF elektrolitik kondansatör  
- 0.1 µF seramik kondansatör  
- Manuel buton ve LED göstergeler  

## 💡 Özellikler
- Saat bazlı mama verme  
- Bluetooth üzerinden porsiyon kontrolü  
- Wi-Fi ile otomatik saat güncelleme  
- Güvenli besleme voltaj devresi  
- Manuel test tuşu ve LED durum göstergeleri  

## 🧠 Kurulum
1. Arduino IDE’ye ESP32 kart desteğini ekleyin  
2. Gerekli kütüphaneleri yükleyin:  
   - `RTClib`  
   - `WiFi.h`  
   - `BluetoothSerial.h`  
3. Kodun içindeki saat ve porsiyon ayarlarını düzenleyin  
4. ESP32’ye yükleyin ve beslemeyi 12V adaptörle yapın  

## 📦 3D Parçalar
Tüm STL dosyaları `3D_Files` klasöründe yer alıyor.  
Parçalar 0.2mm katman yüksekliğiyle PLA olarak yazdırılabilir.  

## 🔒 Lisans
© 2025 **Ali Yıldırım**  
Bu proje **Creative Commons BY-NC 4.0 (Attribution–NonCommercial)** lisansı ile paylaşılmıştır.  

> Ticari amaçla kullanılamaz, ancak kişisel ve hobi amaçlı projelerde serbestçe kullanılabilir.  
> Herhangi bir paylaşımda veya türev çalışmada kaynak olarak **Ali Yıldırım** ve bu sayfa belirtilmelidir.  

Lisans metni: [https://creativecommons.org/licenses/by-nc/4.0/](https://creativecommons.org/licenses/by-nc/4.0/)

---

## 📷 Görseller
`Images` klasöründe proje fotoğrafları ve devre şeması bulunur.

## 📫 İletişim
Proje sahibi: **Ali Yıldırım**  
Instagram: [@petmatrix.tech](https://instagram.com/petmatrix.tech)  
