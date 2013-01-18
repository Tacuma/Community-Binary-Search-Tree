//Tacuma Solomon
//Programming Assignment 3
/*This assignment involves modeling a community of people
to be able to answer certain questions about the community and its members. 
Each member x of the community is a person that has a unique SSN (any unsigned int), 
a name (first and last name), a mother, a father, and a list of people (from within the community) 
that x considers to be his/her friends.*/

#include"Person.h"
#include"TreeType.h"
#include<iostream>
#include<fstream>
using namespace std;

void readfile(TreeType&,TreeTypeint&,ifstream&);
void readqueries(TreeType&, ifstream&); // Function prototype
void motherOfSSN(TreeType&,int);
void fatherOfSSN(TreeType&,int); 
void nameOfSSN(TreeType&,int);
void halfSiblingsOfSSN(TreeType&, int);
void fullSiblingsOfSSN(TreeType&, int);
void childrenOfSSN(TreeType&, int);
void inverseFriendsOfSSN(TreeType&, int);
void mutualFriendsOfSSN(TreeType&, int);
void mostMutualFriends(TreeType&);
void Footer();

bool found = false;

int main()
{
	TreeType Community;
	TreeTypeint friendsSSN;
	ifstream inData;
	ifstream inData2;
	inData.open("Communityfile.txt");
	inData2.open("queriesfile.txt");
	if ( !inData.is_open() || !inData2.is_open()) {
			cout<<"Could not open file\n";
			Footer();
			system("pause");
			return 0;
	}
	readfile(Community,friendsSSN,inData);
	readqueries(Community,inData2);
	cout << endl;
	Footer();
	system("pause");
	return 0;
}

//Reads the Community info from file and builds an Binary Search Tree of People
void readfile(TreeType& Community, TreeTypeint& friendsSSN, ifstream& inData)
{
	int SSN, fatherSSN, motherSSN,value;
	string figure,temp;
	string firstName, lastName;
	
	while (!(inData.eof())) {

		inData.ignore(20,':');
		inData >> firstName;
		inData.ignore(20,':');
		inData >> lastName;
		inData.ignore(20,':');
		inData >> SSN; 
		inData.ignore(20,':');
		inData >> fatherSSN; 
		inData.ignore(20,':');
		inData >> motherSSN; 
		inData.ignore(20,':');
	    getline(inData,figure);

		//Parses the friends SSN into string tokens
	    while (figure.find(",", 0) != std::string::npos)
		{ //does the string a comma in it?
			size_t  pos = figure.find(",", 0); //store the position of the delimiter
			temp = figure.substr(0, pos);      //get the token
			figure.erase(0, pos + 1);          //erase it from the source 
			value = atoi(temp.c_str());  //convert the temp string to an int
			friendsSSN.PutItem(value);         //and put it into the array
		}
		value = atoi(figure.c_str());  ////the last token is all alone 
		friendsSSN.PutItem(value);         //and put it into the array

		Person person(SSN,firstName,lastName,fatherSSN,motherSSN,friendsSSN); // New person 
																			  //object is created
		Community.PutItem(person); // person object is placed in community(binary search tree)
		friendsSSN.MakeEmpty();

	}

}

//Reads and executes the queries file
void readqueries(TreeType& Community, ifstream& inData)
{
	string query;
	int SSN;
	while (!(inData.eof()))
	{
		inData >> query;
		if (query == "NAME-OF"){
			inData >> SSN;
			nameOfSSN(Community,SSN);
		}
		else if (query == "MOTHER-OF"){
			inData >> SSN;
			motherOfSSN(Community,SSN);
		}
		else if (query == "FATHER-OF"){
			inData >> SSN;
			fatherOfSSN(Community,SSN);
		}
		else if (query == "HALF-SIBLINGS-OF"){
			inData >> SSN;
			halfSiblingsOfSSN(Community,SSN);
		}
		else if (query == "FULL-SIBLINGS-OF"){
			inData >> SSN;
			fullSiblingsOfSSN(Community,SSN);
		}
		else if (query == "CHILDREN-OF"){
			inData >> SSN;
			childrenOfSSN(Community,SSN);
		}
		else if (query == "MUTUAL-FRIENDS-OF"){
			inData >> SSN;
			mutualFriendsOfSSN(Community,SSN);
		}
		else if (query == "INVERSE-FRIENDS-OF"){
			inData >> SSN;
			inverseFriendsOfSSN(Community,SSN);
		}
		else if (query == "WHO-HAS-MOST-MUTUAL-FRIENDS"){
			mostMutualFriends(Community);
		}
	}
}

//Outputs Full name of person with select social security number
void nameOfSSN(TreeType& Community,int SSN) 
{
	Person person,mother;
	person = Community.getPerson(SSN,found);
	cout << "NAME-OF "<< SSN <<":" << person.getFullName() << endl;
}

//Returns full name of SSN's mother
void motherOfSSN(TreeType& Community,int SSN) 
{
	Person person,mother;
	person = Community.getPerson(SSN,found);
	mother = Community.getPerson(person.getMotherSSN(),found);
	cout << "MOTHER-OF " << SSN << ":" << mother.getFullName() << endl;
}

//Returns full name of SSN's father
void fatherOfSSN(TreeType& Community,int SSN) 
{
	Person person,father;
	person = Community.getPerson(SSN,found);
	father = Community.getPerson(person.getFatherSSN(),found);
	cout << "FATHER-OF " << SSN << ":" << father.getFullName() << endl;
}

//Returns the full names of the SSN's half siblings
void halfSiblingsOfSSN(TreeType& Community, int SSN) 
{
	Person person = Community.getPerson(SSN,found);
	cout << "HALF-SIBLINGS-OF " << SSN << ":";
	Community.gethalfSiblings(person);
	cout << endl;
}

//Returns the full names of the SSN's full siblings
void fullSiblingsOfSSN(TreeType& Community, int SSN) 
{
	Person person = Community.getPerson(SSN,found);
	cout << "FULL-SIBLINGS-OF " << SSN << ":";
	Community.getfullSiblings(person);
	cout << endl;
}

//Returns the full names of the SSN's children
void childrenOfSSN(TreeType& Community, int SSN) 
{
	Person person = Community.getPerson(SSN,found);
	cout << "CHILDREN-OF " << SSN << ":";
	Community.getChildren(person);
	cout << endl;
}

//Returns the full names of the SSN's Inverse friends
void inverseFriendsOfSSN(TreeType& Community, int SSN)
{
	Person person = Community.getPerson(SSN,found);
	cout << "INVERSE-FRIENDS-OF " << SSN << ":";
	Community.getInverseFriend(person);
	cout << endl;
}

//Returns the full names of SSN's Mutual friends
void mutualFriendsOfSSN(TreeType& Community, int SSN)
{
	Person person = Community.getPerson(SSN,found);
	cout << "MUTUAL-FRIENDS-OF " << SSN << ":";
	Community.getMutualFriend(person);
	cout << endl;
}

//Prints the name of the person with most mutual friends
void mostMutualFriends(TreeType& Community)
{
	cout << "WHO-HAS-MOST-MUTUAL-FRIENDS:";
	Community.mostMutualFriends();
}

void Footer()
{
	cout << endl << endl;
	cout << "() Code by Tacuma Solomon " << endl;
	cout << "() Not for Redistribution or Reuse." << endl << endl;
}

/*
NAME-OF 1:John Smith
FATHER-OF 10:Dave Smith
MOTHER-OF 10:Mary Green
MOTHER-OF 11:Mary Green
HALF-SIBLINGS-OF 11:John Smith, David Dean, Howard Smith
FULL-SIBLINGS-OF 1:Howard Smith
CHILDREN-OF 5:John Smith, Howard Smith, Ken Dean
CHILDREN-OF 1:UNAVAILABLE
MUTUAL-FRIENDS-OF 5:Dan Benning, Jennifer Benning
INVERSE-FRIENDS-OF 9:Dave Smith, Mary Green, Robert Dean, Kate Dean
WHO-HAS-MOST-MUTUAL-FRIENDS:Barbara Benning



() Code by Tacuma Solomon
() Not for Redistribution or Reuse.

Press any key to continue . . .
*/