#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

//=========Configuracoes do Access point===========
const char* SSID = "xicrinho";
const char* SENHA = "cupheadxicras";

WebServer servidorWeb(80); // instancia um objeto para criar um WebServer.

// Funcao para gerar a pagina HTML que aparece no navegador.
void paginaInicial()
{
  String status = digitalRead(48) ? "Ligado":"Desligado";

  String nana_html =
  "<meta name='viewport' content='width=device-width'>"
  "<p>LED: <b>"+ status +"</b></p>" 
  "<a href='/on'><button>LIGAR</button></a>"
  "<a href='/off'><button>DESLIGAR</button></a>";

  servidorWeb.send(200, "text/html", nana_html);
}

void ligar()
{
  rgbLedWrite(48, 127, 255, 212);
  paginaInicial();
}

void desligar()
{
  rgbLedWrite(48, 0, 0, 0);
  paginaInicial();
}

void setup() 
{
  Serial.begin(115200);

  WiFi.mode(WIFI_AP); // habilita do modo AP para criar uma rede wifi.
  WiFi.softAP(SSID, SENHA); // cria a rede wifi.

  Serial.println();
  Serial.println("---MODO AP ATIVO---");
  Serial.printf("Rede(SSID): %s\n\r", SSID);
  Serial.printf("Senha: %s\n\r", SENHA);
  Serial.printf("IP: %s\n\r", WiFi.softAPIP().toString().c_str());
  Serial.printf("MAC ADDRESS: %s\n\r", WiFi.softAPmacAddress().c_str());

//========ROTAS==========
// ensina o servidor qual a funcao chamar dependendo da URL que o usuario acessar.
  servidorWeb.on("/", paginaInicial);
  servidorWeb.on("/on", ligar);
  servidorWeb.on("/off", desligar);

// coloca o servidor no ar para comecar.
  servidorWeb.begin();

}

void loop() 
{
  servidorWeb.handleClient();
}