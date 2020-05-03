#ifndef LOCATION_DEF
#define LOCATION_DEF

#include <iostream>
#include <string>
#include <math.h>

using namespace std;
/**
 * Earth Radius in Km
 */
const static double EarthRadiusKm = 6372.8;
/**
 * Degree To Radian
 * @param angle Angle value in degree
 * @return Angle value in rads
 */
inline double DegreeToRadian(double angle);
/**
 * Distance of two points on earth calculated by Haversine Formula
 * @param p1Lat
 * @param p1Lng
 * @param p2Lat
 * @param p2Lng
 * @return
 */
double HaversineDistance(float p1Lat,const float p1Lng,const float p2Lat,const float p2Lng);
/**
 * A location on earth
 */
class Location
{
private:
    /**
     * Location name
     */
    string name;
    /**
     * Location Lat in degree
     */
    float lat;
    /**
     * Location Lng in degree
     */
    float lng;
public:
    /**
     * Constructor
     * @param name Location name
     * @param lat Location Lat in degree
     * @param lng Location Lng in degree
     */
    Location(string name,float lat,float lng);
    /**
     * Return the Location Latitude
     * @return Location Lat in degree
     */
    float getLat();
    /**
     * Return the Location Longitude
     * @return Location Lng in degree
     */
    float getLng();
    /**
     * Return the Location name
     * @return Location Name
     */
    string getName();
};

#endif