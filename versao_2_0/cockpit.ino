//#include <Keyboard.h>

//Teclas de ações
//String teclasMotores[] = {"KEY_F1", "KEY_F2", "KEY_F3", "KEY_F4"};
//String teclaFlaps = "F";
//String teclaTremPouso = "G";
//String teclaEmbandeiramento = "KEY_F5";
//Configuração de pinos dos controle
    //Pinos do arduino ligados ao multiplexador (do mais para o menos relevante) 
    int pinoMultiplexador[] = {2, 3, 4, 5};
    int pitoRetornoMultiplex = 0; 

    //Pinos do multiplexador onde ou botoes entao ligados
    int pinoMotor[] = {0, 1, 2, 3};
    int posiFlaps = 4;
    int posiTremPouso = 5;
    int pinoPortaBombas = 8;
    int pinoBombas = 9;

//Motores embandeirado
int motorEmbandeirado[] = {0, 0, 0, 0};
//Estado dos flaps
bool estadoFlaps = false;
//Estado do trem de pouso
bool estadoTremPouso = true;

void setup(){
  	Serial.begin(9600);
  	//Keyboard.begin();
  	//
    //Comfiguração dos pinos do multiplexador
    Serial.println("Configurando pinos do multiplexador...")
    int i = 0;
    while(i <= 3){
        pinMode(pinoMultiplexador[i], OUTPUT);
      	Serial.println(pinoMultiplexador[i]);
        i++;
    }
    Serial.println("Pinos configurados com sucesso");
    Serial.println("");
    pimMode(pitoRetornoMultiplex, INPUT);

    //Comfigurando pinos dos motores
    Serial.println("Configurando pinos dos motores...")
    int i = 0;
    while(i <= 3){
        pinMode(pinoMotor[i], INPUT);
      	Serial.println(pinoMotor[i]);
        i++;
    }
    Serial.println("Pinos configurados com sucesso");
    Serial.println("");

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

}

//
//Rotina de Compartimento de Bombas
//
void abrirCompartimentoBombas(){

}

//
//Rotina dos flaps
//
void verificaFlaps(){
    if(digitalRead(pinoFlaps) == HIGH){
        //Se ele nao estiver ativo ira acionar
        if(!estadoFlaps){
            Serial.println("Ativando flaps!");
            //Keyboard.write(teclaFlaps);
            estadoFlaps = true;
        }
    }else{
        //Se ele estiver ativo ira desacionar
        if(estadoFlaps){
            Serial.println("Desativando flaps!");
            //Keyboard.write(teclaFlaps);
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
            //Keyboard.write(teclaTremPouso);
            estadoTremPouso = true;
        }
    }else{
        //Se ele estiver ativo ira desacionar
        if(estadoTremPouso){
            Serial.println("Recolhendo trem de pouso!");
            //Keyboard.write(teclaFlaps);
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
    	if(lePortaMultiplex(pinoMotor[i]) == TRUE){
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
    	//Keyboard.write(teclasMotores[motor]);
    	motorEmbandeirado[motorAlterado] = 0;
  	}else{
        Serial.println("Acao de embandeiramento motor:" + String(motorAlterado + 1));
    	motorEmbandeirado[motorAlterado] = 1;
  	}
  	//Executa a ação
  	//Keyboard.write(teclaEmbandeiramento);
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


//
//Rotina de acesso ao multiplexador
//
//Coloque o pino do multiplexador no qual o botao esta ligado 
bool lePortaMultiplex(int pitoMultiplex ){
    int matrixDecodBinario[][]{
        {0,0,0,0}
        {0,0,0,1}
        {0,0,1,0}
        {0,0,1,1}
        {0,1,0,0}
        {0,1,0,1}
        {0,1,1,0}
        {0,1,1,1}
        {1,0,0,0}
        {1,0,0,1}
        {1,0,1,0}
        {1,0,1,1}
        {1,1,0,0}
        {1,1,0,1}
        {1,1,1,0}
        {1,1,1,1}
    };
    for (i=0; i<=3; i++){
        digitalWrite( pinoMultiplexador[i], matrixDecodBinario[pitoMultiplex][i];);
    }
    if (digitalRead(pitoRetornoMultiplex) == HIGT){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
