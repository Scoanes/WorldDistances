#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<fstream>
#include "City.h"

using namespace std;
using std::vector;

int getCityPos(string cityName, string countryName, vector<City> cityVector){
    for(unsigned int i=0;i<cityVector.size();i++){
        if(cityName==cityVector[i].getName()&&countryName==cityVector[i].getCountry()){    //when city is found
            return(i);                              //returns index location
        }
    }
    return(-1);                 //otherwise returns -1
}

void insertionSort(vector<City> &cityVector){
    unsigned int i=0;
    int j;
    while(i<cityVector.size()){
        j=i;
        City x=cityVector[i];		//giving x the object at i
        while(j!=0 && cityVector[j-1].getName()>x.getName()){
            cityVector[j]=cityVector[j-1];	//moving objects that are bigger than the one at position i
            j--;
        }
    cityVector[j]=x; //put x at the position that was j
    i++;	//goes to next insert value
    }
}

bool binarySearch(vector<City> cityVector, string cityName, string countryName){
    vector<City> tempVec = cityVector;  //tempvec in case user doesn't want main vector sorted
    insertionSort(tempVec);             //must be sorted first
    int low=0, high=tempVec.size()-1;   //setting low and high bounds
    if(tempVec.size()==0){   //if vector hasn't been initialised
        return false;
    }
    while(low<=high){
        int middle=(low+high)/2;    //setting middle value
        if((cityName>tempVec[middle].getName())){
            low=middle+1;
        }
        else if(cityName<tempVec[middle].getName()){
            high=middle-1;
        }
        else{   //has been found
            while(cityName==tempVec[middle+1].getName()){ //forces pointer to one end of the city names
                middle++;                       //making sure that it will start at one end rather than the middle of the city names
            }
            while(cityName==tempVec[middle].getName()){ //coming back through the city names 
                if(countryName==tempVec[middle].getCountry()){  //if city name and country name match
                    return true;
                }
                else{
                    middle--;
                }
            }
            return false;   //city name found, but didn't match country name
        }
    }
    return false;    //city name not found
}

int getLatLongPos(vector<City> cityVector, double latVal, double longVal){
	for(unsigned int i=0;i<cityVector.size();i++){
		if((cityVector[i].getLatitude()==(latVal))&&(cityVector[i].getLongitude()==(longVal))){    //if location is already taken
			return(i);                              //returns index location
		}
	}
	return(-1);                 //otherwise returns -1
}

string checkExists(vector<City> cityVector, string cityName, string countryName){
    if(binarySearch(cityVector, cityName, countryName)==0){   //if city doesn't exist
        cout<<"The city you entered does not exist, please enter a city that exists: ";
        getline(cin,cityName);
        cout<<"Enter the country the city is in: ";
        getline(cin, countryName);
        return(checkExists(cityVector, cityName,countryName));      //calls the function again to check new value
    }
    else{
        return(cityName);
    }
}

void displayVector(vector<City> cityVector){
	cout<<"Name                  Country              Longitude    Latitude "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
    for(unsigned int i=0;i<cityVector.size();i++){  //loops through vector
        cout.setf(ios::left);   //aligns to the left
        cout.width(20);         //set width to 20 to fit for all cities
        cout<<cityVector[i].getName()<<" |";         //prints details of all objects in the vector
        cout.width(20);
        cout<<cityVector[i].getCountry()<<" |";
        cout.width(11);
        cout<<cityVector[i].getLongitude()<<" |";
        cout.width(11);
        cout<<cityVector[i].getLatitude()<<" "<<endl;
    }
    cout<<"-------------------------------------------------------------------"<<endl;
}

void loadCities(vector<City>& cityVector){
    string fileName, fileCountry, fileLine;
    double fileLat, fileLong;
    int frontPos, middlePos, backPos;
    fstream infile;
    infile.open("cities.txt",ios::in);
	cityVector.clear();		//clears vector before loading elements so no repeat
    while(! infile.eof()){
        getline(infile,fileLine);       //gets the line from the file
        frontPos=fileLine.find(',');    //finds first comma
        middlePos=fileLine.find(',',frontPos+1);    //finds middle comma
        backPos=fileLine.rfind(',');    //finds last comma
        
        cout<<std::fixed;       //so it assigns the lat and long values to the correct precision rather than rounding them
        fileName=fileLine.substr(0,frontPos);   //splits string at first comma for the name
        fileCountry=fileLine.substr(frontPos+1,(middlePos-frontPos-1));
        fileLat=atof(fileLine.substr(middlePos+1,(backPos-middlePos-1)).c_str()); //between the two comma's for the lat value and converts to double
        fileLong=atof(fileLine.substr(backPos+1).c_str());                      //same as above but for long value
        
        City tempCity(fileName,fileCountry,fileLong,fileLat);       //creates city object
        cityVector.push_back(tempCity);                 //adds object to vector
    }
    infile.close();
}
void saveCities(vector<City>& cityVector){
    fstream outfile;
    unsigned int x=0;
    outfile.open("cities.txt",ios::out);
    cout<<std::fixed;
    for(unsigned int i=0;i<cityVector.size()-1;i++){      //loops through vector
        outfile<<cityVector[i].getName()<<","<<cityVector[i].getCountry()<<","<<cityVector[i].getLatitude()<<","<<cityVector[i].getLongitude()<<"\n";    //adding object attributes to file
        x=i;
	}
    x++;		//so it increments it one more time for last city in vector
    outfile<<cityVector[x].getName()<<","<<cityVector[x].getCountry()<<","<<cityVector[x].getLatitude()<<","<<cityVector[x].getLongitude();  //line outside so doesn't save to disk with extra '\n' at the end
    outfile.close();
}

string duplicateCheck(vector<City> cityVector, string cityCheck, string countryCheck){
    for(unsigned int i=0;i<cityVector.size();i++){  //looping through the vector
        if(cityCheck==cityVector[i].getName()&&countryCheck==cityVector[i].getCountry()){     //comparing with each city in the vector
            cout<<"The city you have entered already exists in that country! please enter a differnt city name"<<endl;
            cout<<"Enter the new name here: ";getline(cin,cityCheck);
            return(duplicateCheck(cityVector, cityCheck,countryCheck));  //calls function again if name is already in the vector
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
    string inName, inCountry, findCity, findCity2, findCountry, findCountry2;
    double inLongitude, inLatitude;
    int position;
    bool programRun=true;
    std::vector<City> cityVector;
    loadCities(cityVector);

    while(programRun){     //while loop for the case statement menu
        cout<<"Choose an option below in upper or lower case"<<endl;
        cout<<"(A)Add \n(D)Display \n(C)Calculate Distance \n(X)Delete \n(M)Modify \n(S)Sort \n(Y)Save Cities \n(L)Load Cities \n(Q)Quit"<<endl;
        cout<<""<<endl;
        cout<<"Enter your choice: ";cin>>choice;
        cin.ignore(99999, '\n');    //clears input buffer otherwise getline reads the \n at the end of the cin above this
        switch(choice){
            case'A':
            case'a':
            {
                cout<<"Enter name of the city: ";
                getline(cin,inName);	//cin>>inName
                cout<<"Enter the Country: ";
                getline(cin,inCountry);
                inName=duplicateCheck(cityVector, inName, inCountry);      //checks name doesn't already exist
                cout<<"Enter the Longitude: ";cin>>inLongitude;
                cout<<"Enter the Latitude: ";cin>>inLatitude;
                while(getLatLongPos(cityVector, inLatitude, inLongitude)!=-1){
                    cout<<"location entered is already taken! please enter an acceptable value!"<<endl;
                    cout<<"Latitude: ";cin>>inLatitude;
                    cout<<"Longitude: ";cin>>inLongitude;
                }
                cin.ignore(99999, '\n');
                City tempCity(inName,inCountry,inLongitude,inLatitude);   //creates city object
                cityVector.push_back(tempCity);                 //adds object to vector
                break;
            }
            case'D':
            case'd':
                displayVector(cityVector);
                break;
            case'C':
            case'c':
                cout<<"Enter first City: ";
                getline(cin,findCity);
                cout<<"Enter the first Country: ";
                getline(cin,findCountry);
                findCity=checkExists(cityVector,findCity,findCountry); //checks to make sure city entered exists
                cout<<"Enter second city name here: ";
                getline(cin,findCity2);
                cout<<"Enter the second Country: ";
                getline(cin,findCountry2);
                findCity2=checkExists(cityVector,findCity2,findCountry2);
                cout<<"Distance between "<<findCity<<" and "<<findCity2<<" is: "
                    <<calculateDistance(cityVector, getCityPos(findCity,findCountry,cityVector), getCityPos(findCity2,findCountry2,cityVector))<<" KM"<<endl;
                cout<<"Which is "<<(calculateDistance(cityVector, getCityPos(findCity,findCountry,cityVector), getCityPos(findCity2,findCountry2,cityVector))*0.621371)<<" Miles"<<endl;
                break;
            case'X':
            case'x':
                cout<<"Enter the name of the city you want to delete: ";
                getline(cin,findCity);
                cout<<"Enter the Country the city is in: ";
                getline(cin,findCountry);
                position=(getCityPos(findCity,findCountry,cityVector)); //checks to see if city exists
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
                getline(cin,findCity);
                cout<<"Enter the name of the country the city is in: ";
                getline(cin,findCountry);
                position=(getCityPos(findCity,findCountry,cityVector)); //making sure city exists
                if(position==-1){       //if city doesn't exist
                    cout<<findCity<<" does not exist!"<<endl;
                }
                else{   //if city does exist
                    //Modifying the city
                    cout<<"Enter the new name of the city (currently: "<<cityVector[position].getName()<<"): "; //shows what the current city name is
                    getline(cin,inName);
                    cityVector[position].setName(inName);   //setname to change the name
                    cout<<"Enter the new name of the country (currently: "<<cityVector[position].getCountry()<<"): ";
                    getline(cin,inCountry);
                    cityVector[position].setCountry(inCountry);
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
		insertionSort(cityVector);
                cout<<"Sorted"<<endl;
                displayVector(cityVector);  //displays the vector contents after it's been sorted
                break;
            case'Y':
            case'y':
                saveCities(cityVector);
                cout<<"Cities successfully saved to disk"<<endl;;
                break;
            case'L':
            case'l':
                loadCities(cityVector);
                cout<<"Cities successfully loaded from disk"<<endl;
                break;
            case'Q':
            case'q':
                cout<<"Goodbye!"<<endl;
		saveCities(cityVector); //saves cities before exit
                programRun=false;  //on exit boolean value changed to false
                break;
            default:
                cout<<"Enter something from the above options"<<endl;
        }
    }
    return(0);
}