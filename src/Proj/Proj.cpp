#include "Proj.h"

Proj::Proj(int width,int height)
{
    this->width = width;
    this->height = height;
}

int Proj::latToYCoordinate(double lat){
        
        double latRad = lat* M_PI/180;
        double mercN = log(tan((M_PI_4)+(latRad/2)));
        return round((this->height/2)-(this->width*mercN/(2*M_PI)));
}

int Proj::lngToXCoordinate(double lng){
    return (lng+180)*(this->width/360);
}