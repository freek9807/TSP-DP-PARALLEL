#ifndef PROJ_DEF
#define PROJ_DEF

#include <cmath>
/**
 * Describe a projection on Map with Mercatore Formulas
 */
class Proj
{
private:
    /**
     * Map width
     */
    int width;
    /**
     * Map height
     */
    int height;
public:
    /**
     * Constructor
     * @param width Map width
     * @param height Map height
     */
    Proj(int width,int height);
    /**
     * Latitude projection on Y Map Coordinate
     * @param lat latitude in degree
     * @return coordinate on Y
     */
    int latToYCoordinate(double lat);
    /**
     * Longitude projection on X Map Coordinate
     * @param lng longitude in degree
     * @return coordinate on X
     */
    int lngToXCoordinate(double lng);
};
#endif