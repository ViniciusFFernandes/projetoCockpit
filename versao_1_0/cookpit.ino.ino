#include <Keyboard.h>

//Teclas de ações
word teclasMotores[] = {"KEY_F1", "KEY_F2", "KEY_F3", "KEY_F4"};
char teclaFlaps = 'F';
char teclaTremPouso = 'G';
word teclaEmbandeiramento = "KEY_F5";
char teclaCompartimentoBomba = '';
char teclaSerieBombas = '';
//Configuração de pinos dos controle
int pinoEmbandeiramento[] = {2, 3, 4, 5};
int pinoFlaps = 6;
int pinoTremPouso = 7;
int pinoPortaBombas = 8;
int pinoBombas = 9;
//Motores embandeirado
int motorEmbandeirado[] = {0, 0, 0, 0};
//Estado dos flaps
bool estadoFlaps = false;
//Estado do trem de pouso
bool estadoTremPouso = true;
//Estado do trem de pouso
bool estadoCompartimentoBomba = true;

void setup(){
    Serial.begin(9600);
    Keyboard.begin();
    //
    int motor = 0;
    while(motor <= 3){
        pinMode(pinoEmbandeiramento[motor], INPUT_PULLUP);
        Serial.println(pinoEmbandeiramento[motor]);
        motor++;
    }
    pinMode(pinoTremPouso, INPUT);
    pinMode(pinoFlaps, INPUT);
}

void loop(){
   liberarSerieBombas();
   abrirCompartimentoBombas(); 
   verificaFlaps();
   verificaTremPouso();
   verificaEmbandeiramento();   
}

//
//Rotina de Bombas
//
void liberarSerieBombas(){
  if(digitalRead(pinoBombas) == HIGH){
    Serial.println("Liberando Bombas!");
    Keyboard.write(teclaSerieBombas);
  }
}

//
//Rotina de Compartimento de Bombas
//
void abrirCompartimentoBombas(){
  if(digitalRead(pinoPortaBombas) == HIGH){
        //Se ele nao estiver ativo ira acionar
        if(!estadoCompartimentoBomba){
            Serial.println("Abrindo Compartimento de Bombas!");
            Keyboard.write(teclaCompartimentoBomba);
            estadoCompartimentoBomba = true;
        }
    }else{
        //Se ele estiver ativo ira desacionar
        if(estadoCompartimentoBomba){
            Serial.println("Fechando Compartimento de Bombas!");
            Keyboard.write(teclaCompartimentoBomba);
            estadoCompartimentoBomba = false;
        }
    }
}

//
//Rotina dos flaps
//
void verificaFlaps(){
    if(digitalRead(pinoPortaBombas) == HIGH){
        //Se ele nao estiver ativo ira acionar
        if(!estadoFlaps){
            Serial.println("Ativando flaps!");
            Keyboard.write(teclaFlaps);
            estadoFlaps = true;
        }
    }else{
        //Se ele estiver ativo ira desacionar
        if(estadoFlaps){
            Serial.println("Desativando flaps!");
            Keyboard.write(teclaFlaps);
            estadoFlaps = false;
        }
    }
}

//
//Rotina do trem de pouso
//
void verificaTremPouso(){
    if(digitalRead(pinoTremPouso) == HIGH){
        //Se ele nao estiver ativo ira acionar
        if(!estadoTremPouso){
            Serial.println("Abaixando trem de pouso!");
            Keyboard.write(teclaTremPouso);
            estadoTremPouso = true;
        }
    }else{
        //Se ele estiver ativo ira desacionar
        if(estadoTremPouso){
            Serial.println("Recolhendo trem de pouso!");
            Keyboard.write(teclaFlaps);
            estadoTremPouso = false;
        }
    }
}

//
//Rotina de embandeirar ou desembandeirar motores
//
void verificaEmbandeiramento(){
    //Testa todos os motores para saber se precisam ser alterados
    int motor = 0;
    while(motor <= 3){
      if(digitalRead(pinoEmbandeiramento[motor]) == HIGH){
          if(motorEmbandeirado[motor] == 0){
                //Se ele nao estiver embandeirado ira executar a rotina
                Serial.println("Iniciando Embandeiramento motor:" + String(motor + 1));
              embandeirarDesembandeirar(motor);
          }
        }else{
            if(motorEmbandeirado[motor] == 1){
                //Se ele nao estiver desembandeirado ira executar a rotina
                Serial.println("Iniciando Desembandeiramento motor:" + String(motor + 1));
              embandeirarDesembandeirar(motor);
          }
        }
        motor++;
    }
}

void embandeirarDesembandeirar(int motorAlterado){
    //Define moteres que sofrerão a ação
    selecionaMotores(motorAlterado);
    //Define a ação
    if(motorEmbandeirado[motorAlterado] == 1){
        Serial.println("Acao de desembandeiramento motor:" + String(motorAlterado + 1));
        Keyboard.write(teclasMotores[motorAlterado]);
        motorEmbandeirado[motorAlterado] = 0;
    }else{
        Serial.println("Acao de embandeiramento motor:" + String(motorAlterado + 1));
        //Executa a ação
        Keyboard.write(teclaEmbandeiramento);
        //desativa motor embandeirado
        Keyboard.write(teclasMotores[motorAlterado]);
        motorEmbandeirado[motorAlterado] = 1;
    }
    //Reativa Motores validos
    selecionaMotores(motorAlterado);
}

void selecionaMotores(int motorAlterado){
  int motor = 0;
    while(motor <= 3){
      if(motorEmbandeirado[motor] != 1 && motor != motorAlterado){
        Keyboard.write(teclasMotores[motor]); 
        Serial.println("Ativando/Desativando motor:" + String(motor + 1));
      }
      motor++;
    }
}
//
//Fim da rotina de embandeirar ou desembandeirar motores
//
