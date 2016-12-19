#include <Arduino.h>
#include "Timer.h"
#include "MatrixLed.h"
#include "MusicLib.h"

const int motionPin = 2;
const int joyXPin = A0;
const int joyYPin = A1;

int motion = 0;
int joyX = 0;
int joyY = 0;
int action = 0;

int currentLogo = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(motionPin, INPUT);
    pinMode(joyYPin, INPUT);
    pinMode(joyXPin, INPUT);

    initMatrix();
    musicInit();
    delay(1000);
    playMusic();
}

void loop()
{
    /* attend de capter un truc */
    /* debutVeille(); */
    /* sortieVeille(); */
}

/*
    1 => droite
    2 => gauche
    3 => entrer
    4 => sortir
*/
int measureAction()
{
    joyX = analogRead(joyXPin);

    if (joyX < 400){
        Serial.println("droite");
        return 1;
    } else if (joyX > 700){
        Serial.println("gauche");
        return 2;
    } else {
        joyY = analogRead(joyYPin);

        if (joyY < 400){
            Serial.println("entrer");
            return 3;
        } else if (joyY > 700){
            Serial.println("sortir");
            return 4;
        } else {
            return 0;
        }
    }
}

int waitForAction()
{
    while(true)
    {
        action = measureAction();
        if (action != 0){
            break;
        }
        delay(100);
    }
    return action;
}

void sortieVeille()
{
    Serial.println("sortie veille");
    /* Lancer la sortie de veille */
    matrixIntro(3);

    while (true){
        action = waitForAction();
        if (action == 1){ // droite
            currentLogo = transition(currentLogo, 1);
        } else if (action == 2){ // gauche
            currentLogo = transition(currentLogo, 0);
        } else if (action == 3){ // entrer
            faireActionMatrice(currentLogo);
            attendSortieAction(currentLogo);
        }        delay(500);
    }
}

void attendSortieAction(int currentLogo)
{
    while (true){
        action = waitForAction();
        if (action == 4){ // sortir
            retourListeMatrice(currentLogo);
            break;
        }
        delay(10);
    }
}

void retourListeMatrice(int currentLogo)
{
    switch (currentLogo) {
        case 0: //
            musicPause();
            break;
        case 1: //
            musicPause();
            break;
        case 2: //
            musicPause();
            break;
        case 3: //

            break;
        default:
            break;
    }
}


void faireActionMatrice(int currentLogo)
{
    switch (currentLogo) {
        case 0: //
            playMessage();
            break;
        case 1: //
            playRepondeur();
            break;
        case 2: //
            playMusic();
            break;
        case 3: //
            break;
        default:
            break;
    }
}

void debutVeille()
{
    Serial.println("debut veille");
    while(true){
        motion = digitalRead(motionPin);
        if (motion == 1)
        {
            break;
        }
        delay(100);
    }
}
