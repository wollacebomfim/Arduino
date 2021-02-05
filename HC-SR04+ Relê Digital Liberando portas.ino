//=============Programa Desenvolvido por Wollace Bomfim=======================

int trig = 8; //Pino Trigger do sensor utrasonico
int eco = 9; //Pino Echo do sensor ultrasonico
int rele = 7; //Pino da placa controladora 
int duracao; //Variavel de duração
int distancia; //Variavel de distancia
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(eco, INPUT);
  pinMode(rele, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  duracao = pulseIn(eco, HIGH);
  distancia = duracao / 50;
  Serial.println(distancia);
  delay(100);
  if(distancia <= 30 && distancia >= 0){
    digitalWrite(rele, HIGH);
    delay(distancia * 300);
    digitalWrite(rele, LOW);
  }
}
