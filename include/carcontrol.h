#ifndef CARCONTROL_H
#define CARCONTROL_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <vector>
#include <math.h>

#include "detectlane.h"
#include "api_i2c_pwm.h"

using namespace std;
using namespace cv;

class CarControl 
{
public:
    CarControl();
    ~CarControl();
    void driverCar(const vector<Point> &left, const vector<Point> &right, float velocity);
    void manual(double &maxSpeed);

private:
    PCA9685 *pca9685 = nullptr;
	
    float errorAngle(const Point &dst);

    Point carPos;

    float laneWidth = 50;

    float minVelocity = 10;
    float maxVelocity = 50;

    float preError;
};

#endif
