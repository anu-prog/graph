//program to generate graph states

#include<iostream> 
#include<math.h>
#include<bitset>
#include<fstream>
#include<string.h>
#include<stdio.h>
using namespace std;

int length, num = 0; 
const int maxsize = 10000; //max. n is 2^n = 10000 => n = 13
int sign[maxsize];
int arr[maxsize][maxsize];
int xarr[maxsize][maxsize];

//This function prints our array as a state.
void printarray(int array[][maxsize])
{
	double norm = sqrt(length);
	//cout<<"1/"<<norm<<" [";
	for(int i = 0; i < length; i++)
	{
		if(i != 0)
			cout<<" + |";
		else
			cout<<"|";
		for(int j = 0; j < num; j++)
		{
			cout<<array[i][j];
		}
		cout<<">";
	}
	//cout<<"]";
	cout<<endl;
}

//This function applies the controlled-Z operation. 
void controlledz(int array[][maxsize], int control, int target)
{
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < num; j++)
		{
			if((j == control) && ((array[i][j] == 1)||(array[i][j] == 2)) && ((array[i][target] == 1)||(array[i][target] == 2)))
			{
				if(array[i][target] == 1)
					array[i][target] = 2;
				else if(array[i][target] == 2)
					array[i][target] = 1; 
			}
		}
	}
}

//This function prints our final state after applying the controlled-Z operation.
void printstate(int array[][maxsize])	
{
	//Change 2 to - sign and 1 
	int flag;
	for(int i = 0; i < length; i++)
	{	
		flag = 0;
		for(int j = 0; j < num; j++)
		{
			if(array[i][j] == 2)
			{
				array[i][j] = 1;
				//sign[i] = 1; 
				flag++;
			}
		}
		if(flag %2 != 0)
			sign[i] = 1;
	}
	
	//Display state
	double norm = sqrt(length);
	//cout<<"1/"<<norm<<" [";
	for(int i = 0; i < length; i++)
	{
		if((i != 0) && (sign[i] == 0))
			cout<<" + |";
		else if((i != 0) && (sign[i] == 1))
			cout<<" - |";
		else
			cout<<"|";
		for(int j = 0; j < num; j++)
		{
			cout<<array[i][j];
		}
		cout<<">";
	}
	//cout<<"]";
	cout<<endl;
}	
		
void xoperation(int array[][maxsize], int xarray[][maxsize])
{
	//We have the array with the terms, and the sign of each term.
	double norm = sqrt(length);
	//cout<<"1/"<<norm<<" [";
	for(int i = 0; i < length; i++)
	{
		if((i != 0) && (sign[i] == 0))
			cout<<" + |";
		else if((i != 0) && (sign[i] == 1))
			cout<<" - |";
		else
			cout<<"|";
		for(int j = 0; j < num; j++)
		{
			if(array[i][j] == 0)
			{
				xarray[i][j] = 1;
				cout<<xarray[i][j];
			}
			else if(array[i][j] == 1)
			{
				xarray[i][j] = 0;
				cout<<xarray[i][j];
			}
		}
		cout<<">";
	}
	//cout<<"]";
	cout<<endl;
}

void rhs(int array[][maxsize], int xarray[][maxsize])
{
	for(int i = 0; i < length; i++)
	{
		if((i != 0) && (sign[i] == 0))
			cout<<" + |0";
		else if((i != 0) && (sign[i] == 1))
			cout<<" - |0";
		else
			cout<<"|0";
		for(int j = 0; j < num; j++)
		{
			cout<<array[i][j];
		}
		cout<<">";
	}
	for(int i = 0; i < length; i++)
	{
		if(sign[i] == 0)
		{
			if(num %2 == 0)
				cout<<" - |1";
			else if(num %2 == 1)
				cout<<" + |1";
		}
		else if(sign[i] == 1)
		{
			if(num %2 == 0)
				cout<<" + |1";
			else if(num %2 == 1)
				cout<<" - |1";
		}
		for(int j = 0; j < num; j++)
		{
			cout<<xarray[i][j];
		}
		cout<<">";
	}
	cout<<endl;
}

		
int main()
{
	//First, calculate how many terms we will need.
	cout<<endl<<"How many qubits in your graph state? ";
	cin>>num;
	length = pow(2,num);
	//cout<<"There will be "<<length<<" terms in your graph state."<<endl;
  	
  	//Then, initialise an array of size n X length such that each row is one term. 
  	int ctrl, trgt;
  	
  	for(int i = 0; i < maxsize; i++)
  	{
  		for(int j = 0; j < maxsize; j++)
  		{
  			arr[i][j] = 0;
  			xarr[i][j] = 0;
  		}
  	}
  	
  	//Fill this array with the initial state of |+>|+>...|+>. This is just the binary numbers.
	//x is the binary representation of number i (which should range from 0 to n).
  	for(int i = 0; i < length; i++)
  	{	
  		//char a = i;    
		std::bitset<1000> x(i); //Put bitset<n> here
		//std::cout << x;
		for(int j = 0; j < num; j++)
  		{
			arr[i][j] = x[j]; //Extracts from the right-hand-side of x
			//cout<<arr[i][j];
		}
		//cout<<endl;
	} 

	//At this stage, our array arr should contain all the terms in |+>...|+>.
	//Doesn't need to be in a particular order as long as we get all the elements.
	//cout<<"The initial state is: ";
	//printarray(arr);
	
	char ans;
	int choice;
	cout<<endl<<"Here is what you can do with your "<<num<<" qubits."<<endl;
	cout<<"------------------------------------------"<<endl;
	cout<<"| 1. Make a cyclic graph state            |"<<endl;
	cout<<"|          o---o                          |"<<endl;
	cout<<"|          |   |                          |"<<endl;
	cout<<"|          o---o                          |"<<endl;  
	cout<<"| 2. Make a path graph state              |"<<endl;
	cout<<"|         o---o---o                       |"<<endl;
	cout<<"| 3. Make any other kind of graph state.  |"<<endl;
	cout<<"------------------------------------------"<<endl;
	cout<<"Enter your choice (1-3)."<<endl;
	cin>>choice;
	
	switch(choice)
	{
		case 1 :
		{
			int v;
			for(v = 1; v <= num; v++)
			{
				controlledz(arr,v-1,v);
			}
			if(num != 2)
				controlledz(arr,0,v-2); //Do CZ between 1st and last qubit (v = num+1 at end of loop)
			//Print the state
			cout<<endl<<"Your state is...";
			cout<<endl<<"----------------"<<endl;
			//cout<<"LHS: ";
			printstate(arr);
			cout<<"----------------";
			cout<<endl<<endl;
			break;
		}
		
		case 2 :
		{
			int v;
			for(v = 1; v <= num; v++)
			{
				controlledz(arr,v-1,v);
			}
			//Print the state
			cout<<endl<<"Your state is...";
			cout<<endl<<"----------------"<<endl;
			//cout<<"LHS: ";
			printstate(arr);
			cout<<"----------------";
			cout<<endl<<endl;
			break;
		}
	
		case 3 :
		{
			ans = 'n';
			do
			{
				//Now, we apply the CZ operation between any two qubits.
				cout<<"Which qubits do you want to do CZ between? Enter the control, then the target. ";
				cin>>ctrl>>trgt;
				controlledz(arr, ctrl-1, trgt-1);
	
				cout<<"Do you want to apply more CZ operations? (y/n) ";
				cin>>ans;
			}while(ans == 'y');
 
			//Finally, print our state in the correct form.
			cout<<endl<<"Your state is...";
			cout<<endl<<"----------------"<<endl;
			//cout<<"LHS: ";
			printstate(arr);
			cout<<"----------------";
			cout<<endl<<endl;
			break;
		}
		
  		default :
  		{
  			cout<<"That's not an option!"<<endl;
  			break;
  		}
  	}
	
  	return 0;
}


