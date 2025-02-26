#include <Arduino.h>
#include <RPLidar.h>


TaskHandle_t task0Handle;

RPLidar lidar;

int DIST_OBSTACLE = 550;

HardwareSerial lidarSerial(1);

static portMUX_TYPE my_spinlock = portMUX_INITIALIZER_UNLOCKED;

bool lidarHasObstaclePiped = false;

bool lidarHasObstacle = false;

typedef struct
{
    float distance = 0;
    float angle = 0;
    float quality = 0;
} LIDAR_MESURE_RES;

LIDAR_MESURE_RES mesure;
bool angleInRange(){
    return (mesure.angle >= 270 && mesure.angle <= 360)|| (mesure.angle >= 120 && mesure.angle <= 180)|| (mesure.angle >= 0 && mesure.angle <= 45);
}
void get_point_lidar()
{
    if (IS_OK(lidar.waitPoint()))
    {
        mesure.angle = lidar.getCurrentPoint().angle;
        if(angleInRange()){
            
        }
    }
}
void LidarTask(void *pvParameters)
{
    for (;;)
    {
        get_point_lidar();
    }
}

void init(){
    lidar.begin(lidarSerial);
    xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
}
bool getLidarStatus(){}

bool Angle_in_range_scare(){
    if (mesure.angle >= 300 && mesure.angle <= 360)
    {
      if (mesure.distance < DIST_OBSTACLE/sin(mesure.angle))
      {
        return true;
      }
    }
    return false;
}

void obstacle(){
    
}
