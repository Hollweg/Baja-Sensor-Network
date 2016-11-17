
//*****************************************************************************************************
//************************                 BJ14 Bombaja Software         ******************************
//************************          Sensor Network, datalogger and RF    ******************************
//************************             Last modification on 20/10        ******************************
//************************                   Available in                ******************************
//************************              https://github.com/Hollweg       ******************************
//*****************************************************************************************************

#include <SD.h>
#include <SPI.h>
#include "Wire.h"
#include "U8glib.h"
//#include "nRF24L01.h"

typedef signed char                 int8_t;
typedef unsigned char               uint8_t;
typedef const short signed int      csint8_t;
typedef const short unsigned int    csuint8_t;
typedef short signed int            sint8_t;
typedef short unsigned int          suint8_t;
typedef signed long int             int32_t;
typedef unsigned long int           uint32_t;
typedef float                       float32_t;

void velocidade_cont ();
void rpm_cont ();
void seta_data_hora();
byte converte_BCD(byte Val);
byte converte_decimal(byte Val);
void mostra_relogio();
void draw_intro_bombaja();
void draw_intro_bombaja_prog();
void draw_cartao_inserido(); 
void draw_cartao_nao_inserido();
void draw_cartao_defeito();
void draw_atualiza_tela(); 

//I2C RTC pins - SDA: 20 SCL: 21
#define DS1307_ADDRESS 0x68

//GLCD initialization
U8GLIB_ST7920_128X64_1X u8g(5, 6, 4);	//serial mode (enable, rw, rs)  

//Chip Select SPI configuration pin 
csint8_t Chip_Select_SD = 49; 

//Variable definitions for archives creation
File myFile;
sint8_t Creation_Archive = 0;

//Temperature variables
float32_t Valorlido_Temp = 0;
float32_t Media_Temperatura = 0;
float32_t Acumulador_Temperatura = 0;
sint8_t Contador_Temperatura = 0;

//Motor Rotation and velocity variables
suint8_t Media_Rotacao = 0;
suint8_t Contador_Rotacao = 0;

suint8_t Veloc = 0;
volatile float32_t Veloc_Display = 0;

float32_t Rpm = 0;
volatile unsigned int Rpm_Display = 0;

suint8_t State = LOW;
suint8_t Teste = 0;
suint8_t Media_RPM = 0;

/* Delay without delay using millis. ~1 and ~2 seconds velocity/rotation and
SD card saving */
csuint8_t Interval_Rot = 100;
csuint8_t Interval = 1000;
csuint8_t Interval_SD = 5000;
csuint8_t Interval_Tela = 460;
csuint8_t Interval_Atualiza_Tela = 450;
csuint8_t Interval_Nivel_Combustivel = 6000;

int32_t Previous_Millis = 0; 
int32_t Previous_Millis_SD = 0;
int32_t Previous_Millis_Rot = 0; 
int32_t Previous_Millis_Tela = 0;
int32_t Previous_Millis_Atualiza_Tela = 0;
int32_t Previous_Millis_Nivel_Combustivel = 0; 

//RTC variables
byte Zero = 0x00; 
uint8_t Dia_Completo;
suint8_t Dia_SD, Mes_SD, Ano_SD, Horas_SD, Minutos_SD, Segundos_SD;

//Screen swap
const suint8_t Botao_Tela = 7;                //pin where it is connected screen swap button
boolean Troca_Tela = HIGH;

//Fuel Level
const suint8_t LED_Reabastecimento = 8;
const suint8_t Sinal_Capacitivo = 17;
boolean Gas = 0; 

//SD card variable
suint8_t Cont_SD = 0;

/***********************************************
 * Name:
 *    velocidade_cont
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    Function to measure velocity indutive sensor pulses
 *    and convert the result to km/h
 * 
 *    Funcao para contar os pulsos do sensor indutivo
 *    de velocidade e efetuar conversao para km/h
 ************************************************/
void velocidade_cont ()
{
    unsigned long int Current_Millis = millis();
    
    Veloc++;
    if((Current_Millis - Previous_Millis >= Interval))
       { 
         Previous_Millis = Current_Millis;        //Velocity in km/h        
         Veloc_Display = Veloc*0.11;              //1 second acquisition    
         Veloc = 0;                               //pulses per revolution = 17; Wheel = 0.53 m
       }                                          //1 pulse = 0.031m 
                                                  //Equation = pulses * 0.03 * 3.6 = 0.11
}
//~~ final velocidade_cont

/***********************************************
 * Name:
 *    rpm_cont
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    Function to measure and convert motor rotation
 *    to RPM 
 *
 *    Funcao para contar e efetuar conversao 
 *    de unidaes para rpm dos pulsos do 
 *    sensor indutivo de rotacao
 ************************************************/
void rpm_cont ()
{    
    uint32_t Current_Millis_Rot = millis();
    Rpm++;                                                
    if((Current_Millis_Rot - Previous_Millis_Rot >= Interval_Rot))
       {
         Previous_Millis_Rot = Current_Millis_Rot;             
         Rpm_Display = Rpm*300;                                       
         Rpm = 0;                                                                    
       }
}      
//~~final rpm_cont

/***********************************************
 * Name:
 *    seta_data_hora
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    Function to set timestamp on RTC
 *
 *    Funcao para setar hora no RTC 
 *    utilizando o CI DS1307
 ************************************************/
void seta_data_hora()          
{
     byte Segundos = 00;                      //Values from 0 to 59
     byte Minutos = 40;                       //Values from 0 to 59
     byte Horas = 15;                         //Values from 0 to 23
     byte Dia_Semana = 2;                     //Values from 0 to 6 - 0 = Sunday, 1 = Monday, etc.
     byte Dia_Mes = 15;                       //Values from 1 to 31
     byte Mes = 11;                           //Values from 1 to 12
     byte Ano = 16;                           //Values from 0 to 99
     Wire.beginTransmission(DS1307_ADDRESS);
     Wire.write(Zero);                        //Stop DS1307 to receive data
    
     //Values conversion and transmission
     Wire.write(converte_BCD(Segundos));
     Wire.write(converte_BCD(Minutos));
     Wire.write(converte_BCD(Horas));
     Wire.write(converte_BCD(Dia_Semana));
     Wire.write(converte_BCD(Dia_Mes));
     Wire.write(converte_BCD(Mes));
     Wire.write(converte_BCD(Ano));
     Wire.write(Zero);                        
     Wire.endTransmission(); 
}
//~~final seta_data_hora

/***********************************************
 * Name:
 *    converte_BCD
 * In:
 *    Val
 * Out:
 *    Val in BCD
 * Description:
 *    Function that converts input value in BCD
 *
 *    Funcao que converte o valor de entrada em BCD 
 ************************************************/
byte converte_BCD(byte Val)
{
      return ( (Val/10*16) + (Val%10) );
}
//~~final converte_BCD

/***********************************************
 * Name:
 *    converte_BCD
 * In:
 *    Val
 * Out:
 *    Val in BCD
 * Description:
 *    Function that converts input value in BCD
 *
 *    Funcao que converte o valor de entrada em BCD 
 ************************************************/
byte converte_decimal(byte Val)  
{ 
     return ( (Val/16*10) + (Val%16) );
}
//~~final converte_decimal

/***********************************************
 * Name:
 *    mostra_relogio
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    Function that receive RTC values and convert
 *    it to decimal and print it via serial
 *
 *    Funcao que recebe valores do RTC, converte
 *    para decimal, e printa os valores na serial
 *
 ************************************************/
void mostra_relogio()
{
     Wire.beginTransmission(DS1307_ADDRESS);
     Wire.write(Zero);
     Wire.endTransmission();
     Wire.requestFrom(DS1307_ADDRESS, 7);
     
     int Segundos = converte_decimal(Wire.read());
     int Minutos = converte_decimal(Wire.read());
     int Horas = converte_decimal(Wire.read() & 0b111111); 
     int Dia_Semana = converte_decimal(Wire.read()); 
     int Dia_Mes = converte_decimal(Wire.read());
     int Mes = converte_decimal(Wire.read());
     int Ano = converte_decimal(Wire.read());
     
     Dia_SD = Dia_Mes;
     Mes_SD = Mes;
     Ano_SD = Ano;
     Horas_SD = Horas;
     Minutos_SD = Minutos;
     Segundos_SD = Segundos;
}
//~~final mostra_relogio

/***********************************************
 * Name
 *    intro_bombaja
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    First page write
 *
 *    Primeira GLCD página
 *
 ************************************************/
void draw_intro_bombaja() 
{
    u8g.setFont(u8g_font_fub17);
    u8g.drawStr( 17, 20, "Bombaja "); 
    u8g.drawStr( 28, 45, "UFSM"); 
}
//~~final draw_intro_bombaja

/***********************************************
 * Name:
 *    draw_intro_bombaja_prog
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    Second GLCD page
 *
 *    Segunda página de escrita
 *
 ************************************************/
void draw_intro_bombaja_prog() 
{
    u8g.setFont(u8g_font_fub17);
    u8g.drawStr( 17, 20, "Bombaja "); 
    u8g.drawStr( 28, 45, "UFSM"); 
    u8g.setFont(u8g_font_6x12);
    u8g.drawStr( 0, 60, "  Bernardo e Hollweg");
}
//~~final draw_intro_bombaja_prog

/***********************************************
 * Name:
 *    draw_cartao_inserido
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    GLCD write funcion called when SD card is OK
 *
 *    Funcao de escrita chamada quando o cartao esta
 *    inserido corretamente
 *
 ************************************************/
void draw_cartao_inserido() 
{
    u8g.setFont(u8g_font_fub17);
    u8g.drawStr( 17, 20, "Bombaja "); 
    u8g.drawStr( 28, 45, "UFSM"); 
    u8g.setFont(u8g_font_6x12);
    u8g.drawStr( 5, 60, " Cartao Inserido OK");
}
//~~final draw_cartao_inserido
  
/***********************************************
 * Name:
 *    draw_cartao_nao_inserido
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    GLCD function called when SD card is not OK
 *
 *    Funcao de escrita chamada quando o cartao 
 *    nao esta inserido corretamente
 *
 ************************************************/
void draw_cartao_nao_inserido() 
{
    u8g.setFont(u8g_font_fub17);
    u8g.drawStr( 17, 20, "Bombaja "); 
    u8g.drawStr( 28, 45, "UFSM"); 
    u8g.setFont(u8g_font_6x12);
    u8g.drawStr( 5, 60, " Cartao Nao Inserido");
}
//~~final draw_cartao_nao_inserido

/***********************************************
 * Name:
 *    draw_cartao_defeito
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    GLCD function to inform SD card malfunction
 *
 *    Funcao de escrita chamada quando o cartao esta
 *    apresentando algum problema de leitura
 *
 ************************************************/
void draw_cartao_defeito() 
{
    u8g.setFont(u8g_font_fub17);
    u8g.drawStr( 17, 20, "Cartao com "); 
    u8g.drawStr( 28, 45, "Defeito"); 
    u8g.setFont(u8g_font_6x12);
    u8g.drawStr( 5, 60, "Verificar e Reiniciar");
}
//~~final draw_cartao_defeito


/***********************************************
 * Name:
 *    draw_atualiza_tela
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    Third GLCD page, refresh screen in 400ms 
 *    intervals, verifying screen_swap button
 * 
 *    Terceira página de escrita
 *    Atualiza a tela a cada 400ms
 *    Verificando o estado do botao alto/baixo
 *
 ************************************************/
void draw_atualiza_tela() 
{ 
    if(Troca_Tela == LOW)
        {
         u8g.setFont(u8g_font_fub14);
         u8g.drawStr( 0, 15, "V:         Km/h");
         u8g.drawStr( 0, 35, "R:          rpm");
         u8g.drawStr( 0, 60, "Caixa:       ");
       
         u8g.setPrintPos(25,15);
         u8g.print(Veloc_Display);             
         
         if (Rpm_Display < 4000) 
             { 
              u8g.setPrintPos(25,35);
              u8g.print(Rpm_Display);               
             }
        
         u8g.setPrintPos(65,60);
         u8g.print(Media_Temperatura); 
         }
  
    if (Troca_Tela == HIGH)
        {
         u8g.setFont(u8g_font_ncenB14);
         u8g.drawStr( 0, 20, "          :      :  ");
         u8g.drawStr( 0, 60, "           ");
         
         if (Horas_SD > 9)
            {
             u8g.setPrintPos(20,20);
             u8g.print(Horas_SD);
             }
             
          else 
             {
              u8g.setPrintPos(35,20);
              u8g.print(Horas_SD);
             }
                
          u8g.setPrintPos(60,20);
          u8g.print(Minutos_SD);
          u8g.setPrintPos(95,20);
          u8g.print(Segundos_SD);
          if (Gas == 1){
              u8g.setPrintPos(40, 60);
              u8g.drawStr(0, 60,  "Tank: Vazio"); 
          }
          
          else{
              u8g.setPrintPos(40, 60);
              u8g.drawStr(0, 60,  "Tank: Cheio"); 
         }
         }
 }
 //~~final draw_atualiza_tela

/***********************************************
 * Name:
 *    setup
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    Initialize all things
 *  
 *    Recebe todas e quaisquer inicializacao de 
 *    protocolos e bibliotecas
 ************************************************/
void setup() 
{ 
    attachInterrupt(4, velocidade_cont, FALLING );  //pin 19
    attachInterrupt(5, rpm_cont, FALLING);          //pin 18

    pinMode(19, INPUT_PULLUP);
    pinMode(18, INPUT_PULLUP);
    
    pinMode(Sinal_Capacitivo, INPUT_PULLUP);        //Capacitive sensor read pin
    pinMode(LED_Reabastecimento, OUTPUT);           //Refuel LED
    pinMode(Chip_Select_SD, OUTPUT);                //SD card CS pin
    
    pinMode(Botao_Tela, INPUT);                     //Screen Swap input button
    digitalWrite(Botao_Tela, LOW);                 
    
    pinMode(A0, INPUT);                             //Temperature sensor input
    //Serial.begin (9600);
      
    Wire.begin();
    
    u8g.firstPage();  
    do {
        draw_intro_bombaja();
        } while( u8g.nextPage());
    delay(1500);
    
    u8g.firstPage();  
    do {
        draw_intro_bombaja_prog();
        }while( u8g.nextPage());
    delay(1500);  
    
    /*Function that calls RTC Timestamp adjust 
    Comment it after used */
    
    //seta_data_hora(); 
    
testa_cartao:
    if (!SD.begin(Chip_Select_SD)) 
       {
        u8g.firstPage();  
        do{
              draw_cartao_nao_inserido();
           }while(u8g.nextPage());
              
        delay(2000);
        Troca_Tela = digitalRead(Botao_Tela);
        if (Troca_Tela == HIGH){
            return; 
        }
        goto testa_cartao;
       }
  
    else
       {
        u8g.firstPage();  
        do{
              draw_cartao_inserido();
           }while(u8g.nextPage());      
        delay(2000);
       }
 }
 //~~final do setup
 
/***********************************************
 * Name:
 *    loop
 * In:
 *    --
 * Out:
 *    --
 * Description:
 *    Standard Arduino function. Infinite loop    
 *
 *    Funcao padrao da IDE do Arduino
 *    Equivalente a while (TRUE)
 ************************************************/ 
void loop() 
{  
    volatile short int Reserva = 0;
    short int nivel_combustivel = 0;
    unsigned long Current_Millis_Tela = millis();
    unsigned long int Current_Millis_SD = millis();  
    unsigned long int Current_Millis_Atualiza_Tela = millis();
    unsigned long Current_Millis_Combustivel = millis();
     
    //logica da amostra de temperatura - OK!
    Valorlido_Temp = analogRead(A0);
    Acumulador_Temperatura = Acumulador_Temperatura + ((Valorlido_Temp*850.0)/1024);   //10mV/C to Celsius Degree conversion
    Contador_Temperatura = Contador_Temperatura + 1;                                   //counts until 10 to compare and do average calculation
                                                                                       //killing outliers
    if (Contador_Temperatura == 10)                                                     
      {
        Media_Temperatura = (Acumulador_Temperatura / 10);  
        Acumulador_Temperatura = 0;
        Contador_Temperatura = 0; 
      }   
    
    //logica para verificacao do combustivel 
    nivel_combustivel = digitalRead(Sinal_Capacitivo);
    if (nivel_combustivel == HIGH)
        {
         digitalWrite (LED_Reabastecimento, LOW);
         Previous_Millis_Nivel_Combustivel = Current_Millis_Combustivel;
         Gas = 0;
        }
        
    else if ((nivel_combustivel == LOW) && (Current_Millis_Combustivel - Previous_Millis_Nivel_Combustivel >= Interval_Nivel_Combustivel))
        {
          digitalWrite (LED_Reabastecimento, HIGH);
          Gas = 1;
          Reserva = 1;
        }

    //Test select screen and do Time update
    int Tela_Loop = digitalRead(Botao_Tela);
    mostra_relogio();
   
    //debounce and GLCD screen verification - OK!   
    if ((Tela_Loop == HIGH) && (Current_Millis_Tela - Previous_Millis_Tela >= Interval_Tela))
     {
         Troca_Tela = !Troca_Tela;                                                      //Low state - one screen, High State - another one
         Previous_Millis_Tela = Current_Millis_Tela;                                   
     }   
     
     if(Current_Millis_Atualiza_Tela - Previous_Millis_Atualiza_Tela >= Interval_Atualiza_Tela)
      {  
         Previous_Millis_Atualiza_Tela = Current_Millis_Atualiza_Tela; 
         u8g.firstPage();  
         do{
             draw_atualiza_tela();
            }while(u8g.nextPage());
      }
     
criacao_arquivo_SD:                                                //Verify or create a header in SD file. 
    if (Creation_Archive == 0)                                     //It will be executed only once.
       {
        myFile = SD.open("bombaja.txt", FILE_WRITE);
        if (myFile) 
           {
            myFile.println();
            myFile.println("Bombaja UFSM");
            myFile.println("Engenharia Eletrica");
            myFile.println("Datalogger de Sensoriamento Embarcado da Equipe Bombaja");
            myFile.println("por Guilherme Hollweg e Bernardo Campanher");
            myFile.println();
            myFile.println("Inicio de Aquisicao de Dados ");
            myFile.println();
            myFile.println();
            myFile.close();
            } 
      
         /*else
           {
            u8g.firstPage();  
            do{
                draw_cartao_defeito();
               }while(u8g.nextPage()); 
            delay(2000);   
           }*/
           
       Creation_Archive = 1;
       } 
       
testa_tempo_entre_escrita:
    Current_Millis_SD = millis();
    if((Current_Millis_SD - Previous_Millis_SD >= Interval_SD))
       {
        myFile = SD.open("bombaja.txt", FILE_WRITE);
        if (myFile) 
           {
            myFile.print ("Dia: ");
            myFile.print (Dia_SD);
            myFile.print("/");  
            myFile.print (Mes_SD);
            myFile.print("/");  
            myFile.print (Ano_SD);
            myFile.print("   Hora: ");  
            myFile.print (Horas_SD);
            myFile.print(":");  
            myFile.print (Minutos_SD);
            myFile.print(":");  
            myFile.println (Segundos_SD);
            
            myFile.print("Velocidade: ");
            myFile.println (Veloc_Display);
            myFile.print("RPM: ");
            myFile.println (Rpm_Display);
            myFile.print("Temperatura: ");
            myFile.print (Media_Temperatura, 2);
            myFile.println (" ºC");
            //myFile.print("Vazao de Combustivel: ");
            //myFile.print (Gas);
            //myFile.println("mL");
            myFile.print("Aviso de Tanque na Reserva: ");
            
            if (Reserva == 1)
                myFile.println ("SIM");
            
            else
                myFile.println ("NAO");
                
            myFile.println();
            myFile.close();
           } 
          
         else if (Cont_SD < 4)
            { 
             u8g.firstPage();  
             do{
                 draw_cartao_defeito();
                }while(u8g.nextPage()); 
             delay(2000);
             Cont_SD++;   
            }
         Previous_Millis_SD = Current_Millis_SD;
        }
}
//~~final do main
