Community Binary Search Tree
============================

Courtesy of 
George Washington University's
Fall 2005 class on Data Structures in C++
http://www.seas.gwu.edu/~ayoussef/cs103/fall05/Assignment3.html


Data Structures/Concepts Used:
==============================
Binary Search Trees, Reading items with a "," delimiter, copy constructors
Structs, Object Oriented Programming (OOP), File I/O, Header and cpp files


Output:
=======
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


Input:
======
#####queriesfile.txt
	NAME-OF 1
	FATHER-OF 10
	MOTHER-OF 10
	MOTHER-OF 11
	HALF-SIBLINGS-OF 11
	FULL-SIBLINGS-OF 1
	CHILDREN-OF 5
	CHILDREN-OF 1
	MUTUAL-FRIENDS-OF 5
	INVERSE-FRIENDS-OF 9 
	WHO-HAS-MOST-MUTUAL-FRIENDS

#####communityfile.txt
	FIRST NAME: John
	LAST NAME: Smith
	SSN: 1
	FATHER: 4
	MOTHER: 5
	FRIENDS: 2,3
	
	FIRST NAME: Barbara
	LAST NAME: Benning
	SSN: 2
	FATHER: 8
	MOTHER: 9
	FRIENDS: 1,3,11,10
	
	FIRST NAME: David
	LAST NAME: Dean
	SSN: 3
	FATHER: 6
	MOTHER: 7
	FRIENDS: 2
	
	FIRST NAME: Dave
	LAST NAME: Smith
	SSN: 4
	FATHER: 20
	MOTHER: 21
	FRIENDS: 9,8
	
	FIRST NAME:  Mary
	LAST NAME:  Green
	SSN: 5
	FATHER: 31
	MOTHER: 12
	FRIENDS: 8,9,6,7
	
	FIRST NAME: Robert
	LAST NAME: Dean
	SSN: 6
	FATHER: 22
	MOTHER: 23
	FRIENDS: 9,8
	
	FIRST NAME: Kate
	LAST NAME: Dean
	SSN: 7
	FATHER: 20
	MOTHER: 19
	FRIENDS: 9
	
	FIRST NAME: Dan
	LAST NAME: Benning
	SSN: 8
	FATHER: 13
	MOTHER: 14
	FRIENDS: 4,5
	
	FIRST NAME: Jennifer
	LAST NAME: Benning
	SSN: 9
	FATHER: 15
	MOTHER: 16
	FRIENDS: 4,5,6,7
	
	FIRST NAME: Howard
	LAST NAME: Smith
	SSN: 10
	FATHER: 4
	MOTHER: 5
	FRIENDS: 2,3
	
	FIRST NAME: Ken
	LAST NAME: Dean
	SSN: 11
	FATHER: 6
	MOTHER: 5
	FRIENDS: 2
		
		
Statement of Problem:
=====================

#####This assignment involves modeling a community of people to be able to answer certain questions about the community and its members.

Each member x of the community is a person that has a unique SSN (any unsigned int), a name (first and last name), a mother, a father, and a list of people (from within the community) that x considers to be his/her friends. Note that if x considers y a friend, it does not necessarily follow that y considers x a friend. The kinds of queries that your program should be able to answer are:

For a given person x, find all the children of x; 
For a given person x, find all the half-siblings of x; 
For a given person x, find all the full-siblings of x; 
For a given person x, find the friends of x that consider x as their friend as well; 
For a given person x, find all the Persons that consider x as their friend; 
Who has the most mutual friends; 
The precise types of questions your program should answer are detailed below.

The Input:  

Your program will take two input files from the command prompt, the first file containing the information about the community, and the second file containing the queries that your program should answer. 

The first input file, which has the information about the community, will be such that each person has one "paragraph", with at least one blank between successive paragraphs. The format of the paragraph of a person is: 

<<<<<<< HEAD
FIRST NAME: word       // just one word representing the first name
LAST NAME: word        // just one word representing the last name
SSN: number                     // social security number (any unsigned integer)
FATHER: number            // representing the SSN of the father
MOTHER: number          // representing the SSN of the mother
FRIENDS: a coma-separated list of SSNs of this person?s friends
Note: The list after FRIENDS is the list of the SSNs of the people that the person in question considers to be his/her friends. Those SSNs are not necessarily sorted.
=======
FIRST NAME: word       // just one word representing the first name  
LAST NAME: word        // just one word representing the last name   
SSN: number                     // social security number (any unsigned integer)   
FATHER: number            // representing the SSN of the father   
MOTHER: number          // representing the SSN of the mother    
FRIENDS: a coma-separated list of SSNs of this person's friends    
Note: The list after FRIENDS is the list of the SSNs of the people that the person in question considers to be his/her friends. Those SSNs are not necessarily sorted.   
>>>>>>> Updated

The second input file will have a sequence of queries, one query per line, where each query is any of the following:

NAME-OF SSN    
MOTHER-OF SSN   
FATHER-OF SSN   
HALF-SIBLINGS-OF SSN  
FULL-SIBLINGS-OF SSN   
CHILDREN-OF SSN   
MUTUAL-FRIENDS-OF SSN   
INVERSE-FRIENDS-OF SSN     
WHO-HAS-MOST-MUTUAL-FRIENDS    

Note that SSN in the above queries stands for an unsigned int.  

The output:

Your program must take as input the two input files above, in that order. That is, we should be able to compile your program into an executable file (called Project3, say), then call it from the command-line like this: 

>> Project3 communityFileName queriesFileName

<<<<<<< HEAD
(Note this unlike in the previous two projects, in this project the file names are not guaranteed to be literally ?communityFileName? and ?queriesFileName?.)

(Note this unlike in the previous two projects, in this project the file names are not guaranteed to be literally "communityFileName" and "queriesFileName".)
>>>>>>> Updated

Your program must then output as many lines as there are query lines: the kth output line should be the answer to the kth query line in file queriesFileName. Your output line answer to a query should begin by repeating the exact same query, followed by a colon (:), followed by the query-answer. The query-answer for the first three types of query should be the two words representing the first and last name of the answer-person. The query-answer for the next five types of query should be a list of first name and last name pairs, separated by commas, and ordered so that their SSNs are in increasing order. For example, a possible output for "CHILDREN-OF 3155" can be: 

        CHILDREN-OF 3155: John Smith, Adam Smith, Susan Smith 

And for the query "MUTUAL-FRIENDS-OF 3155", a possible answer can be: 

        MUTUAL-FRIENDS-OF 3155: John Redman, Janet Fisher, Joe Fisher 

The answer to INVERSE-FRIENDS-OF SSN query should consist of the people that consider the person with the specified SSN to be their friend.

The answer to a WHO-HAS-MOST-MUTUAL-FRIENDS query should be the full name of the person who has the most mutual friends; in case of a tie, choose the one with the smallest SSN.
