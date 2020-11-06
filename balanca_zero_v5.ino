// bibliotecas****************************************************
#include <SPI.h>
#include <Ethernet.h>
#include "HX711.h"
// codigo da balanca OK
// comunicacao com o servidor OK
/*******************************************declaracao de variaveis**************************************************/
//balanca ok
//comunicacao com o servidor ok 
//dado sendo mostrado no php
//enviando dados para o sql automaticamente
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 10, 139);
byte servidor[] = {192, 168, 10, 141 };
//char servidor[] = " "                    //inserir servidor
#define portaHTTP 80
#define DOUT A0
#define CLK A1


HX711 balanca;
EthernetClient clienteArduino;


//=================================================================================================================
//                              declarar sensores
float calibration_factor = 20000;
float peso = 0;

//=================================================================================================================

void setup(){
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  Serial.print("Conectado ao servidor, no ip: ");
  Serial.println(Ethernet.localIP());
  balanca.begin(DOUT, CLK);
  Serial.println("Balanca com HX711 - Celula de carga 50Kg");
  Serial.println("Pressione t para TARA");
  balanca.set_scale(calibration_factor);
  balanca.tare(); 

}
void loop (){

  peso = balanca.get_units();
  char recebe_serial = Serial.read();
  if(recebe_serial == 't' || recebe_serial == 'T'){
      balanca.tare();
      Serial.println("Balança zerada");
  }
  if (recebe_serial== 'p' || recebe_serial == 'P'){
     Serial.print("Peso: ");                       //imprime no monitor serial
      Serial.print(balanca.get_units(), 3);         //imprime peso na balanla com 3 casas decimais
      Serial.println ("Kg");
  }
    /*
   if(clienteArduino.available()){
      char dadosRetornados = clienteArduino.read();
      Serial.print(dadosRetornados);

    }

    if(!clienteArduino.connected()){
      clienteArduino.stop();
      }
    
    
    if(recebe_serial == '1' ){

      
    Serial.println("Conectando ao servidor e enviando os dados: ");
    Serial.print("Peso:");
    Serial.println(peso);
    */
    if(clienteArduino.connect(servidor, portaHTTP)) {
      
      
      //clienteArduino.println("GET /arduino/teste.php HTTP/1.0");
      clienteArduino.print("GET /arduino/salvar.php");
      clienteArduino.print("?Peso=");
      clienteArduino.print(peso);
      clienteArduino.println(" HTTP/1.0"); 
      
      clienteArduino.println("Host: 192.168.10.141");
      clienteArduino.println("connection: close");
      clienteArduino.println();

      clienteArduino.stop();
  
       }else{
      Serial.println("Falha na conexao com o servidor");
      clienteArduino.stop();
    }
  
 //}
  delay(60000);
}

 
