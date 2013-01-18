// Tacuma Solomon
// Person.h


#include<string>
#include"TreeType(int).h"
using namespace std;

class Person
{
public:
	Person();
	Person(int,string,string,int,int,TreeTypeint);
	int getSSN();
	string getFullName();
	int getFatherSSN();
	int getMotherSSN();
	bool isYourFriend(int);
	
private:
	int SSN;			//Person's Social Security Number
	string firstName;	//Person's First Name
	string lastName;	//Person's Last Name
	int FatherSSN;		//Person's Father's Social Security Number
	int MotherSSN;		//Person's Mother's Social Security Number
	TreeTypeint friendSSNs;	//Person's Friend's Social Security Numbers
};	

//Constructor
Person::Person(){
}

// Constructor
Person::Person(int SSN, string firstName, string lastName, int fatherSSN, int motherSSN, TreeTypeint friendsSSN ){
	this->SSN = SSN;
	this->firstName = firstName;
	this->lastName = lastName;
	FatherSSN = fatherSSN;
	MotherSSN = motherSSN;
	this->friendSSNs = friendsSSN;
}

//Returns Person's SSN
int Person::getSSN(){
	return SSN;
}

//Returns Person's full name
string Person::getFullName(){
	string fullName = firstName + " " + lastName;
	return fullName;
}

//Returns Person's Father's SSN
int Person::getFatherSSN(){
	return FatherSSN;
}

//Returns Person's Mother's SSN
int Person::getMotherSSN(){
	return MotherSSN;
}

//Returns true if SSN is Person's friend
bool Person::isYourFriend(int SSN){
	bool found=false;
	return friendSSNs.GetItem(SSN,found);
}
