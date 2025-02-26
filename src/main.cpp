#include <Arduino.h>
#include <RobotMove.hpp>
#include <lidar.c++>

RobotMove robot;

enum struct ACTION
{
    FORWARD,
    BACKWARD,
    TURN,   // tourne retation relative
    TURNTO, // tourne jusqu'a votre un angle donnée
    MOVETO,
    PAUSE, // arret des mouvement
    RESUME,
    WAIT, // attendre  un certains temps des ordre du h
    BUZZ
};

typedef struct
{
    ACTION action;
    int distance, speed, angle, time, tonality;
    Coord target;
} ActionItem;

float Waitstart = 0;
bool actionfinished(ActionItem action)
{
    if (action.action == ACTION::WAIT)
    {
        if (millis() > Waitstart + action.time * 1000)
            return true;
        else
        {
            return false;
        }
    }
    else
    {
        return robot.reachedTarget();
    }
}

bool callAction(ActionItem action)
{
    if (action.speed == 0)
        action.speed = ROBOT_VARIABLES::STEPPER::DEFAULT_SPEED;
    switch (action.action)
    {
    case ACTION::FORWARD:
        return robot.forward(action.distance, action.speed);
        break;
    case ACTION::BACKWARD:
        return robot.backward(action.distance, action.speed);
        break;
    case ACTION::TURN:
        return robot.turn(action.angle, action.speed);
        break;
    case ACTION::TURNTO:
        return robot.turnTo(action.angle, action.speed);
        break;
    case ACTION::MOVETO:
        return robot.moveTo(action.target, action.speed);
        break;
    case ACTION::PAUSE:
        return robot.pause();
        break;
    case ACTION::RESUME:
        return robot.resume();
        break;
    case ACTION::WAIT:
        return true;
        break;
    case ACTION::BUZZ:
        tone(12, action.tonality, action.time);
        return true;
        break;
    default:
        return false;
    }
}

typedef ActionItem Actions[DEV_VARIABLES::MAX_ACTION_AMOUNT]; // attention au deux type d'actions/Actions/ACTION
Actions actions = {
    // liste des action que fera le robot
    // {.action=ACTION::MOVETO,.speed=100,.target={100,100,0}}
    {.action = ACTION::FORWARD, .distance = 10, .speed = 100},
    {.action = ACTION::WAIT, .time = 2},
    {.action = ACTION::TURN, .angle = 90}};
int actionIndex = 0;
enum struct STATE
{
    INITIALIZING,
    IDLE,
    RUNNING,
    PAUSED // paused by security and not by external event => pause non programmed in action list (e.g. lidar detects obstacle)
};
STATE state = STATE::INITIALIZING;



// put function declarations here:
void waitTirette()
{
    tone(12, 666, 250);
    while (digitalRead(PIN::DIVERS::TIRETTE))
    {
        Serial.println("Tirette absente");
        delay(500);
    }
    tone(12, 260, 250);
    Serial.println("Tirette en place");
    delay(1000);
    while (!digitalRead(PIN::DIVERS::TIRETTE))
        ;
    Serial.println("Tirette retirée");
    delay(1000);
    tone(12, 175, 250);
}
// int startTime=0;
void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Préinitialisation");
    tone(12, 444, 250);
    // lidarSerial.begin(115200, 134217756U, RX, TX);
    
    delay(500);
    pinMode(PIN::DIVERS::TIRETTE, INPUT_PULLUP);
    tone(12, 300, 250);
    waitTirette();
    robot.resume();
    robot.printHello();
    Serial.println("Fin initialisation");
    state = STATE::IDLE;
    robot.setCurrentCoords(Coord{0, 0, 0});
    // startTime= millis();
}
void loop()
{
    robot.Run();
    if (actionfinished(actions[actionIndex]) && state == STATE::RUNNING)
    {
        state = STATE::IDLE;
    }
    if (state == STATE::IDLE)
    {
        if (actionIndex < DEV_VARIABLES::MAX_ACTION_AMOUNT)
        {
            state = STATE::RUNNING;
            bool error = callAction(actions[actionIndex]);
            if (!error)
            {
                Serial.println("Erreur dans l'action");
            }
            actionIndex++;
        }
    }
}