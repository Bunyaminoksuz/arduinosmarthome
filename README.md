
# Arduino İle Akıllı Ev Sistemi Projesi

Bu benim yaptığım ilk proje. Bu proje ile kendimize ait akıllı ev sistemimiz olmuş oluyor 
bu proje bize hava sıcaklığını,nemini,havanın yağışlı olup olmadığını
evimizde gaz kaçağı olup olmadığını,yangın çıkıp çıkmadığını bize söylüyor Seri Ekranda Söylüyor. 
Saksılarımızın topraklarının nemli nemsiz olup olmadığını bize söyleyip kendisi sulama yapıyor
ve bunları ayrıca hem LCD hem de led'ler ile bize bildiriyor

- Arkadaşlar Alev Sensörünün D0(Dijital 0)pinini Arduinoda Dijital 11 Pine Bağlıyoruz
Gaz Sensörünün A0(Analog 0)pinini Arduinoda A2 Pinine Bağlıyoruz
Toprak Ve Nem Sensörünün A0(Analog 0)pinini Arduinoda A1 Pinine Bağlıyoruz
Yağmur Sensörünün A0(Analog 0)pinini Arduinoda A0 Bağlıyoruz
DHT11 Sensörünün Sinyal Pinini Arduinoda D2 Pinine Bağlıyoruz
LCD Ekranın SCL Pinini Arduinoda A5 Pinine Bağlıyoruz
LCD Ekranın SDA Pinini Arduinoda A4 Pinine Bağlıyoruz

- Bütün GND'ler Ve VCC'ler Ortaktır
- VCC'ler +5V Bağlanılacak
- GND'ler GND Pinine Bağlanacak

## Özellikler

- Sıcaklık Ve Nem Bildirme
- Toprak Kuru ise Otomatik Sulama
- Gaz Kaçağı Var İse Bildirme
- Yangın Var İse Bildirme
- Hava Durumunu Bildirme
- Verileri LCD Ekrana Ve Seri Monitöre Yazdırma

# Pin Bağlantıları
- Pin Bağlantıları;

- Yağmur Sensörü: A0 
- Yağmur Ledi: D5

- Toprak Ve Nem Sensörü Pini: A1
- Toprak Kırmızı Led: D3
- Toprak Yeşil Led: D4
- Toprak Sarı Led: D1 
- Toprak Su Motoru: D6

- MQ-6 Gaz Sensörü: A2
- Gaz Sensörü Buzzer: D7
- Gaz Sensörü Yeşil Led: D9
- Gaz Sensörü Kırmızı Led: D10


- LCD Ekran I2C Pinleri: 
- SCL = A5 
- SDA = A4

- Alev Sensörü: D11
- Alev Sensörü Yesil Led: D12
- Alev Sensörü Kırmızı Led: D13
- Alev Sensörü Buzzer: D8 

- DHT11 Sensörü: D2

- Boş Pinler;
- Analog 3 pin ve Dijital 0 Pinleri Boştur


## Katkı

Bu Projeyi İstediğiniz Gibi Geliştirebilirsiniz
Ve Burada Bizimle Paylaşabilirsiniz.

  
## Destek

Bana Destek Olmak için Bunyaminoksuz321@gmail.com Adresine Mail Atabilirsiniz. 
https://www.youtube.com/c/BünyaminÖksüz

  
## Lisans

[MIT](https://choosealicense.com/licenses/mit/)

  
