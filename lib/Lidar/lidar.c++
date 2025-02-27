#include <Arduino.h>
#include <RPLidar.h>

TaskHandle_t task0Handle;

RPLidar lidar;

int DIST_OBSTACLE = 550;
int QUALITY = 14;
int MEAN_ALLOWED=2;

HardwareSerial lidarSerial(1);

static portMUX_TYPE my_spinlock = portMUX_INITIALIZER_UNLOCKED;
   
bool lidarHasObstaclePiped = false;

bool lidarHasObstacle = false;

float prevAngle = 0.0;
int sumPoints = 0;
int countPoints=0;

// FONCTION COEUR 0 (COUEUR LIDAR)
typedef struct
{
    float distance = 0;
    float angle = 0;
    float quality = 0;
} LIDAR_MESURE_RES;

LIDAR_MESURE_RES mesure;
// FONCTION COEUR 0 (COUEUR LIDAR)
bool angleInRange()
{
    return (mesure.angle >= 270 && mesure.angle <= 360) || (mesure.angle >= 120 && mesure.angle <= 180) || (mesure.angle >= 0 && mesure.angle <= 45);
}
// FONCTION COEUR 0 (COUEUR LIDAR)
void get_point_lidar()
{
    if (IS_OK(lidar.waitPoint()))
    {
        mesure.angle = lidar.getCurrentPoint().angle;
        if (angleInRange())
        {
            if(prevAngle>mesure.angle){
                if((sumPoints/countPoints)<MEAN_ALLOWED){
                    sendObstacleData(false);
                }
                sumPoints=0;
                countPoints=0;
            }
            mesure.distance = lidar.getCurrentPoint().distance; // distance value in mm unit
            mesure.quality = lidar.getCurrentPoint().quality;
            prevAngle=mesure.angle;
            countPoints++;
            if (mesure.quality > QUALITY)
            {
                if (obstacle())
                {
                    sumPoints++;
                    sendObstacleData(true);
                }
            }
            else
            {
                reset_point();
            }
        }
    }
}
// FONCTION COEUR 0 (COUEUR LIDAR)
void LidarTask(void *pvParameters)
{
    for (;;)
    {
        get_point_lidar();
    }
}

// FONCTION A EXECUTER COTE COEUR 1 (COEUR DE MOUVEMENT)
void initLidar()
{
    lidar.begin(lidarSerial);
    xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
}

// FONCTION COEUR 0 (COUEUR LIDAR)
void sendObstacleData(bool obstacleVal){
    taskENTER_CRITICAL(&my_spinlock);
    lidarHasObstaclePiped=obstacleVal;
    taskEXIT_CRITICAL(&my_spinlock);
}

// FONCTION A EXECUTER COTE COEUR 1 (COEUR DE MOUVEMENT)
bool getLidarStatus() {
    taskENTER_CRITICAL(&my_spinlock);
    lidarHasObstacle=lidarHasObstaclePiped;
    taskEXIT_CRITICAL(&my_spinlock);
    return lidarHasObstacle;
}
// FONCTION COEUR 0 (COUEUR LIDAR)
bool Angle_in_range_scare()
{
    if (mesure.angle >= 300 && mesure.angle <= 360)
    {
        if (mesure.distance < DIST_OBSTACLE / sin(mesure.angle))
        {
            return true;
        }
    }
    return false;
}
// FONCTION COEUR 0 (COUEUR LIDAR)
bool obstacle()
{
    if (mesure.distance < DIST_OBSTACLE && mesure.distance > 10)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// FONCTION COEUR 0 (COUEUR LIDAR)
void reset_point()
{
    mesure.distance = 0;
    mesure.angle = 0;
    mesure.quality = 0;
}
