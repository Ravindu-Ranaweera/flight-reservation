#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct Seat{
	int rowNumber;
	char classType;
	string seats;
};
class Flight{				//flight class
	private:
		string flightNumber;
		string dateTime;
		string dAriportCode;
		string aAirportCode;
		int availableSeatB;
		int availableSeatE;
		Seat availableSeats[60];
		int rowCount;

	public:
		Flight(){
		}
		Flight(string &flightNumber,string &dateTime,string &dAriportCode,string &aAirportCode,int availableSeatB,int availableSeatE,Seat *availableSeats , int rowNumberCount);
		
		void displayBasic();
		string getFlightName();
		string getdateTime();
		string getDAriportCode();
		string getAAirportCode();
		int getAvailableSeatB();
		int getAvailableSeatE();
		void seatAvailability();
		void seatBooking();
		void displaySeats();
		void reWriteFile(int lineNO);
};


Flight::Flight(string &flightNumber,string &dateTime,string &dAriportCode,string &aAirportCode,int availableSeatB,int availableSeatE,Seat *availableSeats , int rowCount){
	this->flightNumber = flightNumber;
	this->dateTime = dateTime;
	this->dAriportCode = dAriportCode;
	this->aAirportCode = aAirportCode;
	this->availableSeatB = availableSeatB;
	this->availableSeatE = availableSeatE;
	this->rowCount =rowCount;

	for (int i = 0; i <rowCount; ++i)
	{
		this->availableSeats[i].rowNumber = availableSeats[i].rowNumber;
		this->availableSeats[i].classType = availableSeats[i].classType;
		this->availableSeats[i].seats = availableSeats[i].seats;		
	}
}

string Flight::getFlightName(){
	return flightNumber;
}
string Flight::getdateTime(){
	return dateTime;
}
string Flight::getDAriportCode(){
	return dAriportCode;
}
string Flight::getAAirportCode(){
	return aAirportCode;
}
int Flight::getAvailableSeatB(){
	return availableSeatB;
}
int Flight::getAvailableSeatE(){
	return availableSeatE;
}


void Flight::displayBasic(){				//display flight details
	cout << flightNumber << endl;
	cout << dateTime << endl;
	cout << dAriportCode << endl;
	cout << aAirportCode<<endl;
}

void Flight::displaySeats(){			//display seats details
	for (int i = 0; i < rowCount; ++i)
	{
		cout << availableSeats[i].rowNumber << " " << availableSeats[i].classType << " "<< availableSeats[i].seats<< endl;
		
	}
}

void Flight::seatAvailability(){				//find we can get the seats that flight
	int numOfSeats;
	cout << "Number Of Seats Do You Want : ";
	cin >> numOfSeats;
	
	if(numOfSeats <= (availableSeatB + availableSeatE) ){
		cout << "\nThe Following Seats Can Be Reserved" ;
		displaySeats();
	}else{
		cout << "\nSorry.. We Have " << availableSeatB << " B Class Seats And " <<  availableSeatE <<" E Class Seats Available.. " << endl;
	}
}

void Flight::seatBooking(){ 				//find seeat is possible and book it
	int rowNo;
	char className;
	char seatName;
	cout << "\nEnter the Your Booking Seat Details : "<<endl;
	cout << "Row Number  |  classTypes Type(B or E)  |  Seat Name  : ";
	cin >> rowNo >> className >> seatName;
	int count[4]={0,0,0,0};
	if(rowNo < 60 && (seatName >= 'A' && seatName <= 'Z')){ 						//check given sheat detail is correct
		for (int i = 0; i < rowCount; ++i){
			if(rowNo == availableSeats[i].rowNumber){
				count[0]=1;
				if(className == availableSeats[i].classType){
					count[1]=2;
					for(int j=0; j < availableSeats[i].seats.size(); j++){
						if(seatName == availableSeats[i].seats[j]){
							count[2]=3;
							availableSeats[i].seats.erase(j,1);   					//delete user bookin seeat in object array
							cout << "\nThank You.! Your Seat Is Reserved"<< endl;
							if(className == 'B'){
								availableSeatB--;
							}else{
								availableSeatE--;
							}
						}
					}
				}
			}	
		}
	
	}else{
		count[3]=4;
		cout << "\nSorry ... Seats Are Numbered By Rows 1..60 And A..F In Each rowNumber" << endl;
	}
	
	if(count[0]==0 && count[3]!=4){
		cout << "\nSorry. Row Number Is Does't Match" << endl;
	}else if(count[1]==0 && count[3]!=4){
		cout << "\nSorry. Class Type Is Does't Match" << endl;
	}else if(count[2]==0 && count[3]!=4){
		cout << "\nSorry. Seat Name Is Does't Match" << endl;
	}
	
}

void Flight::reWriteFile(int lineNo){			//create new .dat file and write final report user changed
	ofstream newFile;
	if(lineNo==0){
		newFile.open("flights.dat", ofstream::trunc);
	}
	newFile.open("flights.dat", ofstream::app);
	
	newFile << flightNumber << endl;
	newFile << dateTime << endl;
	newFile << dAriportCode << endl;
	newFile << aAirportCode<<endl;

	for (int i = 0; i < rowCount; ++i)
	{
		newFile << availableSeats[i].rowNumber << " " << availableSeats[i].classType << " "<< availableSeats[i].seats<< endl;
		
	}	
	newFile.close();
	
}
int main(){

	vector<Flight *> objArray;				//create vector array for the flights
	ifstream file("Flights.txt");

	string line;
	int lineCount=0,rowCount=0,flightCount=0;

	string flightNumber;
	string dateTime;
	string dAriportCode;
	string aAirportCode;
	int availableSeatB=0;
	int availableSeatE=0;
	Seat availableSeats[60];

	int rowNumber;
	char classType;
	string seats;

	while(!file.eof()){					//open Flights.txt and read data
		getline(file,line);
		cout << line<< endl;
		lineCount++;
		if(line.empty()){
			flightCount++;
			Flight *tmp = new Flight(flightNumber,dateTime,dAriportCode,aAirportCode,availableSeatB,availableSeatE,availableSeats,rowCount);
			objArray.push_back(tmp);
			rowCount=0;
			lineCount=0;
			availableSeatB=0;
			availableSeatE=0;
			
		}else{										//store flights data in object array
			if(lineCount == 1){
				flightNumber = line;
			}else if(lineCount == 2){
				dateTime = line;
			}else if(lineCount == 3){
				dAriportCode = line;
			}else if(lineCount == 4){
				aAirportCode = line;
			}else{
				stringstream s(line);
				
				s >> rowNumber >> classType >> seats;
				availableSeats[rowCount].rowNumber = rowNumber;
				availableSeats[rowCount].classType = classType;
				availableSeats[rowCount].seats = seats;
				
				for (int i=0; i<seats.size(); i++){
					if(classType == 'B')
						availableSeatB++;
					else
						availableSeatE++;
				}
				rowCount++;	
			}
		}
	}
	cout << "\t---------------------------------------------------" << endl;
	cout << "\t___Welcome To The Virgin Airline Booking Service___" << endl;
	cout << "\t---------------------------------------------------" << endl;
	int option;
	while(option!=5){
		cout << "\n\t1. Display Availble Flights\n\t2. View Flight\n\t3. View Available Seats\n\t4. Book A Seat\n\t5. Exit" << endl;
		cout << "\nSelect Your Option : ";
		cin >> option;

		switch(option){					//selections of users

			case 1:{
				cout << endl;
				for (int i = 0; i < flightCount; ++i)
				{
					if(objArray[i]->getAvailableSeatB()+objArray[i]->getAvailableSeatE() > 0){
						objArray[i]->displayBasic();
						cout << "There Are " << objArray[i]->getAvailableSeatB() << " Seats In B Class" << endl;
						cout << "There Are " << objArray[i]->getAvailableSeatE() << " Seats In E Class" << endl<< endl;
					}
				}
				break;
			}
			case 2:{
				
				string flightNum;
				cout << "Enter the Flight Number : ";
				cin >> flightNum;
				int flag=0;
				for (int i = 0; i < flightCount; ++i)
				{
					if(objArray[i]->getFlightName() == flightNum ){
						objArray[i]->displayBasic();
						objArray[i]->displaySeats();
						flag++;
					}							
				}
				if(flag==0){
						cout << "Sorry. We Can't Found This Flight Number" << endl;
					}
				break;
			}
			
			case 3:{
				
				string flightNum;
				cout << "Enter the Flight Number : ";
				cin >> flightNum;
				int flag = 0;
				for (int i = 0; i < flightCount; ++i)
				{
					if(objArray[i]->getFlightName() == flightNum ){
						flag++;
						objArray[i]->seatAvailability();
					}							
				}
				if(flag==0){
						cout << "Sorry. We Can't Found This Flight Number" << endl;
					}
				break;
			}
			
			case 4:{
				
				string flightNum;
				cout << "Enter the Flight Number : ";
				cin >> flightNum;
				int flag = 0;
				for (int i = 0; i < flightCount; ++i)
				{
					if(objArray[i]->getFlightName() == flightNum ){
						objArray[i]->seatBooking();
						flag++;
					}							
				}
				if(flag==0){
						cout << "Sorry. We Can't Found This Flight Number" << endl;
					}
				break;
			}
			
			case 5:{
				int flag = 0;
				for (int i = 0; i < flightCount; ++i)
				{
						objArray[i]->reWriteFile(i);
				}
				
				break;
			}
			
			default: cout << "Enter A Valid Process.\n" << endl;
			system("pause");
			
		}
		
	}

	return 0;
}
