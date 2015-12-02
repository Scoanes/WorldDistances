/* 
 * File:   City.h
 * Author: Tristan
 *
 * Created on 04 November 2015, 15:18
 */

#include<string>

#ifndef CITY_H
#define	CITY_H

using namespace std;

class City{
    public:
        City(string,string,double,double);
        string getName();
        void setName(string inName);
        string getCountry();
        void setCountry(string inCountry);
        double getLongitude();
        void setLongitude(double newLong);
        double getLatitude();
        void setLatitude(double newLat);
    private:
        string name,country;
        double longitude, latitude;		
};

#endif	/* CITY_H */