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
		City(string,double,double);
		string getName();
                void setName(string inName);
		double getLongitude();
		void setLongitude(double newLong);
		double getLatitude();
                void setLatitude(double newLat);
	private:
		string name;
		double longitude, latitude;		
};
City::City(string inName, double inLong, double inLat){
	name=inName;
	longitude=inLong;
	latitude=inLat;
}
string City::getName(){
	return(name);
}
void City::setName(string inName){
    name=inName;
}
double City::getLongitude(){
	return(longitude);
}
void City::setLongitude(double newLong){
	longitude=newLong;
}
double City::getLatitude(){
	return(latitude);
}
void City::setLatitude(double newLat){
	latitude=newLat;
}

#endif	/* CITY_H */

