#include "HX711.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSerifItalic9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMono12pt7b.h>



//#include <Pushbutton.h>

// HX711 circuit wiring
#define DT 27
#define SCK 26


HX711 escala;


 int peso = 0;
 int n = 0;
 int pesoAntigo = 0;
 
 int threshold = 27;
 int pinModo = T8; 
 int pinMais = T5; 
 int pinMenos = T6; 
 int tempoParado = 500;
 int dormir = 10000;
 int habilitarDormir = 1;
 unsigned long tempoModo = (millis() );
 unsigned long tempoMais = (millis() );
 unsigned long tempoMenos = (millis());
 unsigned long tempoDormir = (millis());
 int Tela = 1;
 int ValorTemperatura = 22;
 int controle = 1;

 


//OLED Display
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



void tela_nivel(){

  if(peso <= 0)
   {
     peso = 0;
     
   }

  //ret amarelo
  display.setFont(&FreeMono9pt7b);  
  display.clearDisplay();
  display.drawRect(0, 0, 128, 16, WHITE);
 
  //titulo superior
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(37, 12); 
  display.println("Nivel");
  //display.display();
 

  
  
  // ret azul maior
  display.drawRect(0, 17, 80, 47, WHITE);
  //display.display();
  


  //ret azul garrafa
  display.drawRect(100, 17, 28, 47, WHITE);
  display.display();
 

  if(peso > 99)
  {
    display.setFont(&FreeMonoBold18pt7b); 
    display.setTextColor(WHITE);
    display.setCursor(6, 49);
    display.setTextSize(1);
    display.print(peso);   
    display.setFont(&FreeMono9pt7b); 
    display.setTextColor(WHITE);
    display.setCursor(57, 60);
    display.setTextSize(1);
    display.print("ml");
    display.display();  
  }

  if(peso >9 & peso <=99)
  {
    display.setFont(&FreeMonoBold18pt7b); 
    display.setTextColor(WHITE);
    display.setCursor(13, 50);
    display.setTextSize(1);
    display.print(peso);
    display.setFont(&FreeMono9pt7b); 
    display.print("ml");
    display.display();  
  }

  if(peso <=9)
  {
    display.setFont(&FreeMonoBold18pt7b); 
    display.setTextColor(WHITE);
    display.setCursor(27, 50);
    display.setTextSize(1);
    display.print(peso);
    display.setFont(&FreeMono9pt7b); 
    display.print("ml");
    display.display();  
  }
 

  
 
  display.fillRect(100, n, 28, (64-n), WHITE);
  display.display();
 
  
}



void tela_temperatura(){

 
  //ret amarelo
  display.setFont(&FreeMono9pt7b);  
  display.clearDisplay(); 
  display.drawRect(0, 0, 128, 16, WHITE);
 
  //titulo superior
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 12); 
  display.println("Temperatura");
  //display.display();
 

  
  
  // ret azul maior
  display.drawRect(0, 17, 80, 47, WHITE);
  //display.display();
  


  //ret azul SET
  display.drawRect(90, 17, 38, 47, WHITE);
  display.drawLine(90, 34, 128, 34, WHITE);
  display.drawLine(90, 35, 128, 35, WHITE);
  display.setFont(&FreeSerif9pt7b); 
  display.setTextColor(WHITE);
  display.setCursor(93, 31);
  display.print("SET");

  if(ValorTemperatura >= 0 & ValorTemperatura <= 9)
  {
     display.setFont(&FreeMonoBold12pt7b); 
     display.setTextColor(WHITE);
     display.setCursor(103, 55);
     display.print(ValorTemperatura);
     display.display();
  }

  if(ValorTemperatura >= 10)
  {
     display.setFont(&FreeMonoBold12pt7b); 
     display.setTextColor(WHITE);
     display.setCursor(95, 55);
     display.print(ValorTemperatura);
     display.display();
  }
  if(ValorTemperatura < 0)
  {
     display.setFont(&FreeMono12pt7b);
     display.setTextColor(WHITE);
     display.setCursor(94, 55);
     display.print(ValorTemperatura);
     display.display();
  }
 

   
  display.setFont(&FreeMonoBold18pt7b); 
  display.setTextColor(WHITE);
  display.setCursor(10, 50);
  display.print("22");
  display.setFont(&FreeMonoBold12pt7b); 
  display.setTextColor(WHITE);
  display.setCursor(57, 43);
  display.print("C");
  display.drawCircle(52, 30, 2, WHITE);

  display.display();  
 
  
}


void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);

  
  //ret amarelo
  display.setFont(&FreeMono9pt7b);  
  display.clearDisplay();
  display.drawRect(0, 0, 128, 16, WHITE);
 
  //titulo superior
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(37, 12);  
  display.println("Nivel");
  display.display();
 
 
  
  // ret azul maior
  display.drawRect(0, 17, 90, 47, WHITE);
  //display.display();
  


  //ret azul garrafa
  display.drawRect(100, 17, 28, 47, WHITE);
  display.display();

   display.setFont(&FreeMonoBold18pt7b); 
    display.setTextColor(WHITE);
    display.setCursor(27, 50);
    display.setTextSize(1);
    display.print(peso);
    display.setFont(&FreeMono9pt7b); 
    display.print("ml");
    display.display();  

  //atualizar nivel do ret da garrafa
  for(int x = 62; x >=17; x --){
  display.drawLine(100, x, 128, x, WHITE);
  display.drawLine(100, x, 128, x, WHITE);
  display.display();
  delay(10);
  }

  
  delay(300);
  
  escala.begin (DT, SCK);
  Serial.begin(115200);
  Serial.print("Leitura da Tara:  ");
  Serial.println(escala.read());             // Aguada o termino de verificação do peso
  Serial.println("Aguarde!");
  Serial.println("Iniciando ...");
  escala.set_scale(241076.428);             // Utiliza uma escala padrão de verificação
 
  escala.tare(20);                         // Fixa o peso como tara


  touchAttachInterrupt(pinModo, AcionarModo, threshold);
  touchAttachInterrupt(pinMais, AcionarMais, threshold);
  touchAttachInterrupt(pinMenos, AcionarMenos, threshold); 

 


  
}

void loop() {
    
   Serial.print("Peso:  ");
   Serial.println(escala.get_units(5), 2); //retorna a leitura da variavel escala com a unidade quilogramas
   delay(100);
   peso = (   escala.get_units(13)   *  1000      );
   n = map(peso,0,1000,62,17);

   if (Tela == 1 & habilitarDormir == 1)
   {
      if(controle == 1)
      {
        tela_nivel();
        controle = 0;
      }
      if(peso > (pesoAntigo + 4)  || peso < (pesoAntigo - 4)  ){
      tela_nivel(); 
      pesoAntigo = peso;
   }
   }
   

   if(Tela == 2 & habilitarDormir == 1)
   {
      tela_temperatura();
      controle = 1;
   }
   
  

   if ((millis() - tempoDormir) > dormir)
   {
     tempoDormir = millis();
     display.clearDisplay();
     display.display();  
     habilitarDormir = 0;
   }

   Serial.println(Tela);
}




void AcionarModo (){
  
  if ((millis() - tempoModo) > tempoParado){
    Serial.println("Touch Modo pressionado por interrupção");
    tempoModo = millis();
    tempoDormir = millis();
    habilitarDormir = 1;
    if(Tela == 1)
    {
      Tela = 2;
    }
   else
    {
      Tela = 1;
    }
  }
  
}

void AcionarMais (){
  
  if ((millis() - tempoMais) > tempoParado){
    Serial.println("Touch Mais pressionado por interrupção");
    tempoMais = millis();
    tempoDormir = millis();
    habilitarDormir = 1;
    if(ValorTemperatura <= 46)
    {
      ValorTemperatura ++;
    }
    
  }
}

void AcionarMenos (){
  
  if ((millis() - tempoMenos) > tempoParado){
    Serial.println("Touch Menos pressionado por interrupção");
    tempoMenos = millis();
    tempoDormir = millis();
    habilitarDormir = 1;
    if(ValorTemperatura >= -9)
    {
      ValorTemperatura --;
    }
    
  }
}
