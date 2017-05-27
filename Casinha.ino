// Programa: Casinha de Bonecas com IR e Leds RGB
// Autor: Fábio Ferreira de Souza
// Para minhas filhas Cecilia e Milena

#include <avr/power.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6       //Pino controle leds
#define RECV_PIN 2  //Pino receptor IR

// Mapeamento das telclas do Controle Remoto Xinda
// (http://www.filipeflop.com/pd-6b86d-kit-controle-remoto-ir.html)
#define Xinda1 16738455
#define Xinda2 16750695
#define Xinda3 16756815
#define Xinda4 16724175
#define Xinda5 16718055
#define Xinda6 16743045
#define Xinda7 16716015
#define Xinda8 16726215
#define Xinda9 16734885
#define Xinda0 16730805
#define XindaAsteristico 16728765
#define XindaSustenido 16732845
#define XindaOK 16712445
#define XindaLeft 16720605
#define XindaRight 16761405
#define XindaUp 16736925
#define XindaDown 16754775
#define NUMLEDS 10

// Configurando os Leds RGB WS2812B
// (http://www.filipeflop.com/pd-2047e8-led-rgb-x10-ws2812b-5050-enderecavel.html?ct=&p=1&s=1)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);
IRrecv irrecv(RECV_PIN);
decode_results results;

uint32_t roomColor[NUMLEDS];
bool roomStatus[NUMLEDS];
int currentRoom = 0;

void ShowRoomLeds()
{
  Serial.print("Leds: ");

  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    if (roomStatus[i])
    {
      strip.setPixelColor(i, roomColor[i]);
      Serial.print("O");
    }
    else
    {
      strip.setPixelColor(i, 0);
      Serial.print("_");
    }
  }

  strip.show();
  Serial.println();
}

void ShowLoop(int n)
{

  // n giros
  for (int h = 0; h < n; h++) {

    uint32_t cor;
    if ( h % 3 == 0 )
      cor = strip.Color(255, 0, 0);
    else if ( h % 3 == 1 )
      cor = strip.Color(0, 255, 0);
    else // if ( h % 3 == 2 )
      cor = strip.Color(0, 0, 255);

    // gira
    for (int i = 0; i < NUMLEDS; i++) {
      for (int j = 0; j < NUMLEDS; j++) {

        if (i == j)
        {
          strip.setPixelColor(j, cor);
          Serial.print("O");
        }
        else
        {
          strip.setPixelColor(j, 0);
          Serial.print("_");
        }
      }

      Serial.println();
      strip.show();
      delay(30);
    }
  }

  Serial.println();
}

void ShowFader(int n)
{
  // n vezes
  for (int h = 0; h < n; h++) {
    // efeito
    for (int i = 0; i < 256; i += 16) {
      uint32_t cor = strip.Color(i, i, i);
      // define as cores iguais oara tdos os leds
      for (int j = 0; j < NUMLEDS; j++) {
        strip.setPixelColor(j, cor);
      }
      strip.show();
      delay(30);
    }
  }
}


void ReceiveIR()
{
  Serial.print(" => ");
  switch (results.value)
  {
    case Xinda0:
      Serial.print("0");
      currentRoom = 0;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;
    case Xinda1:
      Serial.print("1");
      currentRoom = 1;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;
    case Xinda2:
      Serial.print("2");
      currentRoom = 2;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;
    case Xinda3:
      Serial.print("3");
      currentRoom = 3;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;
    case Xinda4:
      Serial.print("4");
      currentRoom = 4;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;
    case Xinda5:
      Serial.print("5");
      currentRoom = 5;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;
    case Xinda6:
      Serial.print("6");
      currentRoom = 6;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;
    case Xinda7:
      Serial.print("7");
      currentRoom = 7;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;
    case Xinda8:
      Serial.print("8");
      currentRoom = 8;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;
    case Xinda9:
      Serial.print("9");
      currentRoom = 9;
      roomStatus[currentRoom] = !roomStatus[currentRoom];
      break;

    case XindaAsteristico:
      Serial.println("* ShowFader");
      ShowFader(5);
      //strip.setBrightness(255); // Brilho máximo (padrão)
      break;

    case XindaSustenido:
      Serial.println("# ShowLoop");
      ShowLoop(15);
      //strip.setBrightness(100); // Reduz o Brilho
      break;

    case XindaOK:
      Serial.print("OK");
      roomColor[currentRoom] = strip.Color(255, 255, 255);
      break;

    case XindaLeft:
      Serial.print("Left");
      roomColor[currentRoom] = strip.Color(255, 0, 255);
      break;

    case XindaRight:
      Serial.print("Right");
      roomColor[currentRoom] = strip.Color(0, 0, 255);
      break;

    case XindaUp:
      Serial.print("Up");
      roomColor[currentRoom] = strip.Color(0, 255, 0);
      break;

    case XindaDown:
      Serial.print("Down");
      roomColor[currentRoom] = strip.Color(255, 0, 0);
      break;

    default:
      Serial.print("?");
      break;
  }
}

void setup()
{
  // Serial para informações de debug
  Serial.begin(9600);
  Serial.println();
  Serial.println("Inicializando Casinha");
  Serial.println();

  // Inicializa o receptor IR
  irrecv.enableIRIn();

  // Por padrão liga tudo em branco
  for (int i = 0; i < NUMLEDS; i++)
  {
    roomColor[i] = strip.Color(255, 255, 255);
    roomStatus[i] = true;
  }

  // Inicia os Leds
  strip.begin();
  ShowRoomLeds();
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println();
    Serial.print("IR=");
    Serial.print(results.value);
    ReceiveIR();

    Serial.println();
    ShowRoomLeds(); // Atualiza os leds

    irrecv.resume(); // Le o próximo valor
    delay(100);
  }
}
