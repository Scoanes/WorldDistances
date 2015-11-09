#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include "City.h"

using namespace std;
using std::vector;

int getCityPos(string cityName, vector<City>& cityVector){
    for(unsigned int i=0;i<cityVector.size();i++){
        if(cityVector[i].getName()==(cityName)){    //when city is found
            return(i);                              //returns index location
        }
    }
    return(-1);                 //otherwise returns -1
}

void displayVector(vector<City>& cityVector){
    for(unsigned int i=0;i<cityVector.size();i++){  //loops through vector
        cout<<cityVector[i].getName()<<" ";         //prints details of all objects in the vector
        cout<<cityVector[i].getLongitude()<<" ";
        cout<<cityVector[i].getLatitude()<<" "<<endl;
    }
}

string duplicateCheck(vector<City>& cityVector, string cityCheck){
    for(unsigned int i=0;i<cityVector.size();i++){  //looping through the vector
        if(cityCheck==cityVector[i].getName()){     //comparing with each city in the vector
            cout<<"The city you have entered already exists! please enter a differnt city name"<<endl;
            cout<<"If the city is in a specific country add that to the name"<<endl;
            cout<<"Enter the new name here: ";getline(cin,cityCheck);
            return(duplicateCheck(cityVector, cityCheck));  //calls function again if name is already in the vector
        }
    }
    return(cityCheck);  //if the city isn't in the vector then return it
}

double calculateDistance(vector<City> cityVector, int cityPos1, int cityPos2){
    double totalDistance, long1, lat1, long2, lat2;
    //assigning the longitude and latitude values
    long1=cityVector[cityPos1].getLongitude()*(M_PI/180);  //converting into radians
    lat1=cityVector[cityPos1].getLatitude()*(M_PI/180);
    long2=cityVector[cityPos2].getLongitude()*(M_PI/180);
    lat2=cityVector[cityPos2].getLatitude()*(M_PI/180);
    totalDistance=acos((sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(long1-long2)));   //first part of calculation
    totalDistance=totalDistance*(180/M_PI);  //converted into degrees
    totalDistance=((6371*M_PI*totalDistance)/180);	//final part of calculation
    return(totalDistance);
}

int main(){
    char choice;
    string inName, findCity, findCity2;
    double inLongitude, inLatitude;
    int position;
    bool programRun=true;
    std::vector<City> cityVector;
	
    City testCity("London",0.1275,51.5072);     //adds two cities at the begining for testing
    cityVector.push_back(testCity);
    City testCity1("New York",74.0059,40.7127);
    cityVector.push_back(testCity1);

    while(programRun){     //while loop for the case statement menu
        cout<<"Choose an option below in upper or lower case"<<endl;
        cout<<"(A)Add \n(D)Display \n(C)Calculate Distance \n(X)Delete \n(M)Modify \n(S)Sort \n(Q)Quit"<<endl;
        cout<<"Enter your choice: ";cin>>choice;
        cin.ignore(99999, '\n');    //clears input buffer otherwise getline reads the \n at the end of the cin above this
        switch(choice){
            case'A':
            case'a':
            {
                cout<<"Enter name of the city: ";
                getline(cin,inName);
                inName=duplicateCheck(cityVector, inName);      //checks name doesn't already exist
                cout<<"Enter the Longitude: ";cin>>inLongitude;
                cout<<"Enter the Latitude: ";cin>>inLatitude;
                City tempCity(inName,inLongitude,inLatitude);   //creates city object
                cityVector.push_back(tempCity);                 //adds object to vector
                break;
            }
            case'D':
            case'd':
                displayVector(cityVector);
                break;
            case'C':
            case'c':
                cout<<"Enter first city name here: ";
                getline(cin,findCity);
                cout<<"Enter second city name here: ";
                getline(cin,findCity2);
                cout<<"Distance between "<<findCity<<" and "<<findCity2<<" is: "
                    <<calculateDistance(cityVector, getCityPos(findCity,cityVector), getCityPos(findCity2,cityVector))<<"KM"<<endl;
                break;
            case'X':
            case'x':
                cout<<"Enter the name of the city you want to delete: ";
                getline(cin,findCity);
                position=(getCityPos(findCity,cityVector)); //checks to see if city exists
                if(position==-1){       //if City doesn't exist
                    cout<<findCity<<" does not exist!"<<endl;
                }
                else{                   //if city does exist
                    cityVector.erase(cityVector.begin()+position);  //deletes city from vector
                    cout<<findCity<<" successfully deleted!"<<endl;
                }
                break;
            case'M':
            case'm':
                cout<<"Enter the name of the city you want to modify: ";
                cin>>findCity;
                position=(getCityPos(findCity,cityVector)); //making sure city exists
                if(position==-1){       //if city doesn't exist
                    cout<<findCity<<" does not exist!"<<endl;
                }
                else{   //if city does exist
                    //Modifying the city
                    cout<<"Enter the new name of the city (currently: "<<cityVector[position].getName()<<"): "; //shows what the current city name is
                    cin>>inName;
                    cityVector[position].setName(inName);   //setname to change the name
                    cout<<"Enter the new longitude of the city (currently: "<<cityVector[position].getLongitude()<<"): ";
                    cin>>inLongitude;
                    cityVector[position].setLongitude(inLongitude);
                    cout<<"Enter the new latitude of the city (currently: "<<cityVector[position].getLatitude()<<"): ";
                    cin>>inLatitude;
                    cityVector[position].setLatitude(inLatitude);
                }
                break;
            case'S':
            case's':
                cout<<"Unsorted"<<endl;
                displayVector(cityVector);  //displays the vector contents before it's been sorted
                std::sort(cityVector.begin(), cityVector.end(), sortFunc);  //sorting function for the vector
                cout<<"Sorted"<<endl;
                displayVector(cityVector);  //displays the vector contents after it's been sorted
                break;
            case'Q':
            case'q':
                cout<<"Goodbye!";
                programRun=false;  //on exit boolean value changed to false
                break;
            default:
                cout<<"Enter something from the above options"<<endl;
        }
    }
    return(0);
}