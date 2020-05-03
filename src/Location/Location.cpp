#include "Location.h"

inline double DegreeToRadian(double angle)
{
	return M_PI * angle / 180.0;
}

double HaversineDistance(const float p1Lat,const float p1Lng,const float p2Lat,const float p2Lng)
{
	double latRad1 = DegreeToRadian(p1Lat);
	double latRad2 = DegreeToRadian(p2Lat);
	double lonRad1 = DegreeToRadian(p1Lng);
	double lonRad2 = DegreeToRadian(p2Lng);
 
	double diffLa = latRad2 - latRad1;
	double doffLo = lonRad2 - lonRad1;
 
	double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
	return 2 * EarthRadiusKm * computation;
}

Location::Location(string name,float lat,float lng)
{
    this->name = name;
    this->lat = lat;
    this->lng = lng;
}

float Location::getLat(){
    return this->lat;
}

float Location::getLng(){
    return this->lng;
}

string Location::getName(){
    return this->name;
}
