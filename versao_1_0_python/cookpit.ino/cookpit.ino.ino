//
//Teclas de ações
word teclasMotores[] = {"KEY_F1", "KEY_F2", "KEY_F3", "KEY_F4"};
char teclaFlaps = 'f';
char teclaTremPouso = 'g';
word teclaEmbandeiramento = "KEY_F5";
int teclaCompartimentoBomba = 89;
int teclaSerieBombas = 84;
//Configuração de pinos dos controle
int pinoEmbandeiramento[] = {2, 3, 4, 5};
int pinoFlaps = 6;
int pinoTremPouso = 7;
int pinoPortaBombas = 8;
int pinoBombas = 9;
//Motores embandeirado
bool motorEmbandeirado[] = {false, false, false, false};
//Estado dos flaps
bool estadoFlaps = false;
//Estado do trem de pouso
bool estadoTremPouso = true;
//Estado do trem de pouso
bool estadoCompartimentoBomba = false;
//estado do botao das bombas 
bool estadoBombas = false;

void setup(){
    Serial.begin(9600);
    //
    int motor = 0;
    while(motor <= 3){
        pinMode(pinoEmbandeiramento[motor], INPUT_PULLUP);
        Serial.println(pinoEmbandeiramento[motor]);
        motor++;
    }
    pinMode(pinoTremPouso, INPUT);
    pinMode(pinoFlaps, INPUT);
    pinMode(pinoPortaBombas, INPUT);
    pinMode(pinoBombas, INPUT);
}

void loop(){
   liberarSerieBombas();
   abrirCompartimentoBombas(); 
   //verificaFlaps();
   //verificaTremPouso();
   //verificaEmbandeiramento();   
   delay(100);
}

//
//Rotina de Bombas
//
void liberarSerieBombas(){
  if(digitalRead(pinoBombas) == HIGH && !estadoBombas){
    Serial.print(teclaSerieBombas);
    estadoBombas = true;
  }
  if(digitalRead(pinoBombas) == LOW && estadoBombas){
    estadoBombas = false;
  }
}

//
//Rotina de Compartimento de Bombas
//
void abrirCompartimentoBombas(){
    //Se ele nao estiver ativo ira acionar   
    if(digitalRead(pinoPortaBombas) == HIGH && estadoCompartimentoBomba == false ){     
        Serial.print(teclaCompartimentoBomba);
        estadoCompartimentoBomba = true;  
    }
    //Se ele estiver ativo ira desacionar
    if(digitalRead(pinoPortaBombas) == LOW && estadoCompartimentoBomba == true){
        Serial.print(teclaCompartimentoBomba);
        estadoCompartimentoBomba = false;
    }
}

//
//Rotina dos flaps
//
void verificaFlaps(){
    if(digitalRead(pinoFlaps) == HIGH && !estadoFlaps){
        //Se ele nao estiver ativo ira acionar
        Serial.println("Ativando flaps!");
        //Keyboard.write(teclaFlaps);
        estadoFlaps = true;
    }
    //Se ele estiver ativo ira desacionar
    if(digitalRead(pinoFlaps) == LOW && estadoFlaps){
        Serial.println("Desativando flaps!");
        //Keyboard.write(teclaFlaps);
        estadoFlaps = false;
    }
}

//
//Rotina do trem de pouso
//
void verificaTremPouso(){
    if(digitalRead(pinoTremPouso) == HIGH && !estadoTremPouso){
        //Se ele nao estiver ativo ira acionar
        Serial.println("Abaixando trem de pouso!");
        //Keyboard.write(teclaTremPouso);
        estadoTremPouso = true;
    }
    //Se ele estiver ativo ira desacionar
    if(digitalRead(pinoTremPouso) == LOW && estadoTremPouso){
        Serial.println("Recolhendo trem de pouso!");
        //Keyboard.write(teclaFlaps);
        estadoTremPouso = false;
    }
    
}

//
//Rotina de embandeirar ou desembandeirar motores
//
void verificaEmbandeiramento(){
    //Testa todos os motores para saber se precisam ser alterados
    int motor = 0;
    while(motor <= 3){
      if(digitalRead(pinoEmbandeiramento[motor]) == HIGH && !motorEmbandeirado[motor]){
            //Se ele nao estiver embandeirado ira executar a rotina
            Serial.println("Iniciando Embandeiramento motor:" + String(motor + 1));
            embandeirarDesembandeirar(motor);
      }
      if(digitalRead(pinoEmbandeiramento[motor]) == LOW && motorEmbandeirado[motor]){
            //Se ele nao estiver desembandeirado ira executar a rotina
            Serial.println("Iniciando Desembandeiramento motor:" + String(motor + 1));
            embandeirarDesembandeirar(motor);
      }
        motor++;
    }
}

void embandeirarDesembandeirar(int motorAlterado){
    //Define moteres que sofrerão a ação
    selecionaMotores(motorAlterado);
    //Define a ação
    if(motorEmbandeirado[motorAlterado]){
        Serial.println("Acao de desembandeiramento motor:" + String(motorAlterado + 1));
        //Keyboard.write(teclasMotores[motorAlterado]);
        motorEmbandeirado[motorAlterado] = false;
    }else{
        Serial.println("Acao de embandeiramento motor:" + String(motorAlterado + 1));
        //Executa a ação
        //Keyboard.write(teclaEmbandeiramento);
        //desativa motor embandeirado
        //Keyboard.write(teclasMotores[motorAlterado]);
        motorEmbandeirado[motorAlterado] = true;
    }
    //Reativa Motores validos
    selecionaMotores(motorAlterado);
}

void selecionaMotores(int motorAlterado){
  int motor = 0;
    while(motor <= 3){
      if(motorEmbandeirado[motor] != 1 && motor != motorAlterado){
        //Keyboard.write(teclasMotores[motor]); 
        Serial.println("Ativando/Desativando motor:" + String(motor + 1));
      }
      motor++;
    }
}
//
//Fim da rotina de embandeirar ou desembandeirar motores
//
