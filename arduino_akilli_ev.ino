/*
 * Bu Projeyi Geliştirebilirsiniz
 * Yapımcı TulparHan
 * Kodu Çalıp Kendiniz Yapmışsınız Gibi Paylaşmayınız
 * Github Sayfasında Hangi Pinin Hangi Sensöre Veya Lede Bağlı Olduğu Yazıyor.
 * Kullanan arkadaşlara Teşekkürler.
*/
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include "DHT.h" // DHT 11 kütüphanesi
#define DHTPIN 2 //DHT Pini
#define DHTTYPE DHT11   // DHT 11 Tanımı

DHT dht(DHTPIN, DHTTYPE);
// Pinleri Tanımlıyoruz
int yagmurPin = A0;
int yagmurledPin = 5;
int nemdeger = 0;

// şuanda boşta olan pin sayısı Dijital: D0 Analog: A3

//Toprak Ve Nem
int Tkirmiziled = 11;
int Tyesilled = 7;
int Tsariled = 1;

// Alev Ve Gaz Sensorlerinin Pinler
int Gkirmiziled1 = 10;
int Gyesilled1 = 9;
int Gbuzzer1 = 4; 
int gazpin = A2;

int Akirmiziled2 = 13;
int Ayesilled2 = 12;
int Abuzzer2 = 8;
int alevpin = 3;

//toprak ve nem sensor
int topsensor = A1;
const int sumotor = 6;

// sensör esik değerleri
int gazsensoresigi = 400;
int yagmurdegeri;
int yagmurEsikdegeri = 800; 



void setup() {
  lcd.begin();
  
  // yagmur 
  pinMode(yagmurPin, INPUT); // Pin Çıkışları Ve Girişleri
  pinMode(yagmurledPin, OUTPUT);


  //Toprak Ve Nem
  pinMode(topsensor, INPUT);
  pinMode(Tkirmiziled, OUTPUT);
  pinMode(Tyesilled, OUTPUT);
  pinMode(Tsariled, OUTPUT);
  pinMode(Tkirmiziled, OUTPUT);
  
  
  // alev ve gaz 
  pinMode(Gkirmiziled1, OUTPUT);  
  pinMode(Akirmiziled2, OUTPUT);
  pinMode(Gyesilled1, OUTPUT);
  pinMode(Ayesilled2, OUTPUT);
  pinMode(Gbuzzer1, OUTPUT);
  pinMode(Abuzzer2, OUTPUT);
  pinMode(gazpin, INPUT);
  pinMode(alevpin, INPUT); 
   
  Serial.begin(9600); 
  Serial.println("Akıllı Ev Sistemi"); // Seri Port Ekranına Yazılacak Başlıklar

  lcd.clear();      
  lcd.setCursor(0,0); 
  lcd.print("Akilli Ev");
  lcd.setCursor(0,1); 
  lcd.print("Sistemi");
  delay(2000); 
   
  // dht 11 
  Serial.println(F("DHT Sensör Testi")); // Sensör Testi
  Serial.println("-------------------------");
  Serial.println("");
   
 dht.begin();
}

void loop() {

 lcd.clear();
  
   // DHT 11 Kısmı Ve Hava Durumu Kısmı
   // DHT11 İçin Ondalıklı Değişken Belirleyip Sıcaklığı Ve Nemi Okuyoruz 
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   float f = dht.readTemperature(true);
  

   if (isnan(h) || isnan(t) || isnan(f)) { // Eger Dht 11 İçin belirlediğimiz değişkenlerden 1 tanesi okumuyorsa
    Serial.println(F("---------------------"));
    Serial.println(F("DHT SENSORU CALISMIYOR")); // Seri Ekrana DHT SENSORU ÇALIŞMIYOR Yazdırsın
    Serial.println(F("---------------------\n"));
    
    lcd.clear();      
    lcd.setCursor(0,0); 
    lcd.print("DHT SENSORU");
    lcd.setCursor(0,1); 
    lcd.print("CALISMIYOR!!!");
    delay(3000); 
    return;
   }
 
   float hif = dht.computeHeatIndex(f, h);

   float hic = dht.computeHeatIndex(t, h, false);
   
   // DHT 11 Seri Ekrana Yazdırılıcak Kısım
   Serial.print("---------------------");
   Serial.print("\nHava Durumu; ");
   Serial.print(F("\nNem: %"));
   Serial.print(h);
   Serial.print(F("\nSıcaklık: "));
   Serial.print(t);
   Serial.print(F("C "));
   Serial.print(f);
   Serial.print(F("F \nOrtalama Sıcaklık: ")); 
   Serial.print(hic);
   Serial.print(F("C "));
   Serial.print(hif);
   Serial.println(F("F"));
   Serial.print("---------------------\n");
   delay(1000);

   //DHT11 Verilerini LCD ekrana Yansıtıyoruz
   lcd.clear();      
   lcd.setCursor(0,0);
   lcd.print("Sicaklik:"); 
   lcd.print(t);
   lcd.print("C");
   lcd.setCursor(0,1); 
   lcd.print("Nem:%");
   lcd.print(h);
   delay(7000); 
  

   //Yağmur Sensörünün Olduğu Kısım
   yagmurdegeri = analogRead(yagmurPin);
   
   if(yagmurdegeri > 980){
   Serial.print("---------------------");
   Serial.print("\n");
   Serial.println("Hava Durumu: ");
   delay(500);

   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("Hava Durumu:");
   lcd.setCursor(0,1); 
   lcd.print("Gunesli");
   delay(3000);
   }
                                 
   if(yagmurdegeri > 700 && yagmurdegeri <= 979){
   Serial.print("\n---------------------"); 
   Serial.print("\n");
   Serial.println("Hava Durumu: Hafif Sağanak Yağmur");
   delay(500);
   
   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("Hava Durumu: Hafif ");
   lcd.setCursor(0,1); 
   lcd.print("Hafif Saganak");
   delay(3000); 
   }

   if(yagmurdegeri > 351 && yagmurdegeri <= 699){
   Serial.print("\n---------------------"); 
   Serial.print("\n");
   Serial.println("Hava Durumu: Sağanak Yağmur");
   delay(500);
   
   lcd.clear();   
   lcd.setCursor(0,0); 
   lcd.print("Hava Durumu:");
   lcd.setCursor(0,1); 
   lcd.print("Saganak Yagmur");
   delay(3000); }

   if(yagmurdegeri > 151 && yagmurdegeri <= 350){
   Serial.print("\n---------------------"); 
   Serial.print("\n");
   Serial.println("Hava Durumu: Şiddetli Sağanak");
   delay(500);
   
   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("Hava Durumu:");
   lcd.setCursor(0,1); 
   lcd.print("Siddetli Saganak");
   delay(3000);}

   if(150 > yagmurdegeri){
   Serial.print("\n---------------------"); 
   Serial.print("\n");
   Serial.println("Hava Durumu: Gök Gürültülü Fırtınalı ");
   delay(500);
   
   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("Hava Durumu: Gok");
   lcd.setCursor(0,1); 
   lcd.print("Gurultulu Firtinali");
   delay(3000);  }
   
   if(yagmurdegeri < yagmurEsikdegeri) //Yagmur Değeri yağmur Eşik Değerinden Küçükse Led'i Yakıcak 
    {
    digitalWrite(yagmurledPin, HIGH);
  }
  else // Eger Yagmur Degeri Büyükse Led Sönücek
  {
    digitalWrite(yagmurledPin, LOW);
  }
   
   delay(2000); 
    
   nemdeger = analogRead(A1); // Burası Toprak Ve Nem Sensörünün Olduğu Kısım
   
   if(nemdeger > 901){ 
   Serial.print("\n---------------------");
   Serial.print("\n");
   Serial.println("Durum: Toprak Kuru");
   digitalWrite(Tkirmiziled,HIGH);
   
   lcd.setCursor(0,0); 
   lcd.print("Durum:");
   lcd.setCursor(0,1); 
   lcd.print("Toprak Kuru");
   delay(2000);
 
   // Toprak Kuru ise Su pompası Çalışacak Ve LCD Ekrana Yazdırılacak
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Su Motoru Acildi");
   
   digitalWrite(sumotor, HIGH);
   delay(3000);

   //Su Motorunun Kapandığını Yazdırdık Ve Su Motorunu Kapattık
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Su Motoru Kapandi");
   delay(500);
   
   digitalWrite(sumotor, LOW);
   delay(500);
   } 

  if(nemdeger > 251 && nemdeger <= 900){
   Serial.print("\n---------------------");
   Serial.print("\n");
   Serial.println("Durum: Toprak Nemli");
   digitalWrite(Tyesilled, HIGH);
   delay(500);

   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("Durum:");
   lcd.setCursor(0,1); 
   lcd.print("Toprak Nemli");
   delay(3000);}

  
   if(250 > nemdeger){
   Serial.print("\n---------------------");
   Serial.print("\n");
   Serial.println("Durum: Toprak Yas");
   digitalWrite(Tsariled, HIGH);
   delay(500);

   lcd.clear();
   lcd.setCursor(0,0); 
   lcd.print("Durum:");
   lcd.setCursor(0,1); 
   lcd.print("Toprak Yas"); 
   delay(3000);}


  
  
  
  // Alev Ve Gaz Sensor
  int gazsensor = analogRead(gazpin);
  int alevsensor = digitalRead(alevpin);
  Serial.println("-------------------------");
  Serial.print("Gaz sensör degeri: ");
  Serial.println(gazsensor);
  Serial.print("alev sensör değeri: ");
  Serial.println(alevsensor);
  delay(1000);
  
  if (gazsensor > gazsensoresigi  && alevsensor==LOW){
    Serial.print("---------------------\n");
    Serial.print("Yangın: Yangın Var");
    Serial.print("\nGaz: Gaz Kaçağı Var");
    digitalWrite(Gkirmiziled1, HIGH);
    digitalWrite(Akirmiziled2, HIGH);
    
    digitalWrite(Gbuzzer1, HIGH);
    digitalWrite(Abuzzer2, HIGH);
    
    digitalWrite(Ayesilled2, LOW);
    digitalWrite(Gyesilled1, LOW);

    lcd.clear();  
    lcd.setCursor(0,0); 
    lcd.print("Gaz Kacagi Var!!");
    lcd.setCursor(0,1); 
    lcd.print("Yangin Var!!");
    delay(5000); 
  }
   else if (gazsensor > gazsensoresigi)
  {
    Serial.print("---------------------\n");
    Serial.print("Gaz: Gaz Kacağı Var");
    digitalWrite(Gkirmiziled1, HIGH);
    digitalWrite(Akirmiziled2, LOW);
    
    digitalWrite(Gbuzzer1, HIGH);
    digitalWrite(Abuzzer2, LOW);
    
    digitalWrite(Ayesilled2, LOW);

    lcd.clear();  
    lcd.setCursor(0,0); 
    lcd.print("Durum:");
    lcd.setCursor(0,1); 
    lcd.print("Gaz Kacagi Var!!!");
    delay(5000); 
  }
  else if (alevsensor==LOW){ // yangın VAR
    Serial.print("---------------------\n");
    Serial.println("Yangın Var\n");
    digitalWrite(Akirmiziled2, HIGH);
    digitalWrite(Gkirmiziled1, LOW);
    
     digitalWrite(Gbuzzer1, LOW);
     digitalWrite(Abuzzer2, HIGH); 
        
    digitalWrite(Ayesilled2, LOW);
    digitalWrite(Gyesilled1, LOW);

    lcd.clear();  
    lcd.setCursor(0,0); 
    lcd.print("Durum:");
    lcd.setCursor(0,1); 
    lcd.print("Yangin Var!!!");
    delay(5000);  
    }
  
  else
  {
    Serial.print("---------------------\n");
    Serial.print("Gaz: Gaz Kaçağı Yok\n");
    Serial.print("Yangın Yok");;
    digitalWrite(Gkirmiziled1, LOW);
    digitalWrite(Akirmiziled2, LOW);
    
    digitalWrite(Gbuzzer1, LOW);
    digitalWrite(Abuzzer2, LOW);
    
    digitalWrite(Gyesilled1, HIGH);   
    digitalWrite(Ayesilled2, HIGH);

    lcd.clear();  
    lcd.setCursor(0,0); 
    lcd.print("Gaz Kacagi Yok");
    lcd.setCursor(0,1); 
    lcd.print("Yangin Yok");
    delay(3000); 
  }

   
}
