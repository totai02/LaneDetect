#include "carcontrol.h"

CarControl::CarControl()
{
    carPos.x = 120;
    carPos.y = 300;
    pca9685 = new PCA9685() ;
    api_pwm_pca9685_init( pca9685 );
}

CarControl::~CarControl() {}


void CarControl::manual(double &maxSpeed)
{
//    if (getkey() == 56)
//    {
//        api_set_FORWARD_control(pca9685, maxSpeed);
//    }
//    if (getKey() == 50)
//    {
//        api_set_REVERSE_control(pca9685, maxSpeed);
//    }
//    if (getKey() == 53)
//    {
//        api_set_FORWARD_control(pca9685, 0);
//    }
//    if (getKey() == 52)
//    {
//        api_set_STEERING_control(pca9685, -45.0);
//    }
//    if (getKey() == 54)
//    {
//        api_set_STEERING_control(pca9685, 45.0);
//    }
    if (getkey() == 52)
    {
        api_set_FORWARD_control(pca9685, maxSpeed);
    }
}


float CarControl::errorAngle(const Point &dst)
{
    if (dst.x == carPos.x) return 0;
    if (dst.y == carPos.y) return (dst.x < carPos.x ? -90 : 90);
    double pi = acos(-1.0);
    double dx = dst.x - carPos.x;
    double dy = carPos.y - dst.y; 
    if (dx < 0) return -atan(-dx / dy) * 180 / pi;
    return atan(dx / dy) * 180 / pi;
}

void CarControl::driverCar(const vector<Point> &left, const vector<Point> &right, float velocity)
{
    int i = left.size() - 11;
    float error = preError;
    while (left[i] == DetectLane::null && right[i] == DetectLane::null) {
        i--;
        if (i < 0) return;
    }
    if (left[i] != DetectLane::null && right[i] !=  DetectLane::null)
    {
        error = errorAngle((left[i] + right[i]) / 2);
    } 
    else if (left[i] != DetectLane::null)
    {
        error = errorAngle(left[i] + Point(laneWidth / 2, 0));
    }
    else
    {
        error = errorAngle(right[i] - Point(laneWidth / 2, 0));
    }

//    angle.data = error;
//    speed.data = velocity;

//    steer_publisher.publish(angle);
//    speed_publisher.publish(speed);
} 
