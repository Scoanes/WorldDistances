#include "City.h"
#include<string>

using namespace std;

City::City(string inName, string inCountry, double inLong, double inLat){
    name=inName;
    country=inCountry;
    longitude=inLong;
    latitude=inLat;
}
string City::getName(){
    return(name);
}
void City::setName(string inName){
    name=inName;
}
string City::getCountry(){
    return(country);
}
void City::setCountry(string inCountry){
    country=inCountry;
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