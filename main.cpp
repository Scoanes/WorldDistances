#include<iostream>
#include<string>
#include<vector>
#include "City.h"

using namespace std;
using std::vector;

int getCityPos(string cityName, vector<City>& cityVector){
    for(int i=0;i<cityVector.size();i++){
        if(cityVector[i].getName()==(cityName)){
            return(i);
        }
    }
    return(-1);
}

double calculateDistance(vector<City>& cityVector, string cityName1, string cityName2){
    
}
int main(){
	char choice;
	string inName, findCity;
	double inLongitude, inLatitude;
        int position;
        bool programRun=true;
	std::vector<City> cityVector;
	
        while(programRun){     //while loop for the case statement menu
            cout<<"Choose an option below in upper or lower case"<<endl;
            cout<<"(A)Add \n(D)Display \n(X)Delete \n(M)Modify \n(Q)Quit"<<endl;
            cout<<"Enter your choice: ";cin>>choice;
            cin.ignore(99999, '\n');    //clears input buffer otherwise getline reads the \n at the end of the cin above this
            switch(choice){
                    case'A':
                    case'a':
                    {
                        cout<<"Enter name of the city: ";
                        getline(cin,inName);    //has to be here twice, otherwise just ignores it?
                        cout<<"Enter the Longitude: ";cin>>inLongitude;
                        cout<<"Enter the Latitude: ";cin>>inLatitude;
                        City tempCity(inName,inLongitude,inLatitude);
                        cityVector.push_back(tempCity);
                        break;
                    }
                    case'D':
                    case'd':
                        for(int i=0;i<cityVector.size();i++){
                            cout<<cityVector[i].getName()<<" ";
                            cout<<cityVector[i].getLongitude()<<" ";
                            cout<<cityVector[i].getLatitude()<<" "<<endl;
                        }
                        break;
                    case'X':
                    case'x':
                        cout<<"Enter the name of the city you want to delete: ";
                        getline(cin,findCity);
                        position=(getCityPos(findCity,cityVector));
                        if(position==-1){
                            cout<<findCity<<" does not exist!"<<endl;
                        }
                        else{
                            cityVector.erase(cityVector.begin()+position);
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