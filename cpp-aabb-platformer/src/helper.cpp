#include "helper.h"

float Helper::restrictNum(float number, float maxVal){
    if(number > maxVal) return maxVal;
    else return number;
}
