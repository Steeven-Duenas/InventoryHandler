/*  Steeven Duenas       Student ID: 4000146674
    Problem #BIG PROJECT    Assignment #HONOR CONTRACT
    Date due:
    Description:
        Program Honors Project for C++.
        A program is required to store, retrieve, and process data.
*/
//*** Preprocessors
#include <iostream>     // cout and cin
#include <iomanip>      //setprecision and setw
#include <fstream>      //anything File
#include <string>       //strings
#include <cstring>      //toUPPER
using namespace std;
//**Global Constants
const string CLEAR_SCREEN = "\033[2J \033[1;1H";  // clear screen on any OS and sets cursor at row 1, column 1
//*** Global Variables

//*** Proto-Functions
void displayDescription();
void showMenu();
int menuSelection();
void createFile();
int countFile();
void displayFile();
void processFile();

int main() //*** Program execution begins here
{
    //*** Constants
    const int CREATION_CHOICE = 1, DISPLAY_CHOICE = 2, PROCESS_CHOICE = 3, QUIT_CHOICE = 4;
    int choice;
    //*** Description Program
    cout<<CLEAR_SCREEN;
    displayDescription();
    ///*** Logic Starts here
    //Display the Menu and User Choice.
    do      //recurring loop
    {    
        showMenu();
        cin>>choice;
        //Validate Menue Choice 
        while(choice < CREATION_CHOICE || choice > QUIT_CHOICE)
        {
                cout<<"Please enter a Valid Choice: ";
                cin>> choice;
        }
        if(choice != QUIT_CHOICE)
        {
            switch(choice)
            {
                case CREATION_CHOICE: 
                    createFile();
                break;
                case DISPLAY_CHOICE: 
                    displayFile();
                break;
                case PROCESS_CHOICE: 
                    processFile();
                break;
            }
            cout<<CLEAR_SCREEN;
        }
    }
    while(choice != QUIT_CHOICE); //end do-while

    cout <<"\n\n"; //*** 2 newlines prior to os message 

    //*** Program cleanup
    return 0; //*** Terminate program
}             //*** Program ends
void displayDescription()
{
    cout<<"Program Honors Project for C++" <<endl;
    cout<<"A program is required to store, retrieve, and process data."<<endl; 
}
void showMenu()
{
    cout<<"Menu"<<endl;
    cout<<"==============="<<endl;
    cout<<"1-Create a File"<<endl;
    cout<<"2-Display a File"<<endl;
    cout<<"3-Process a File"<<endl;
    cout<<"4-Quit"<<endl;
    cout<<"====================="<<endl;
    cout<<"Enter your selection: ";
}
void createFile()
{
    ofstream outputFile;
    int markUp,count=0;
    char letter;
    string inventoryList[4],temp;
    outputFile.open("PRODUCT.TXT");
    if(outputFile)
    {
        while(outputFile)
        {
            for(int i = 0;i < 4 ;i++)
            {
                switch(i)
                {
                    case 0:
                        cout<<endl<<"Please input the inventory number: ";
                        cin>>inventoryList[i];
                        outputFile <<inventoryList[i]<<" ";
                        break;
                    case 1:
                        cout<<endl<<"Please input the item description: ";
                        cin>>inventoryList[i];
                        outputFile <<inventoryList[i]<<" ";
                        break;
                    case 2:
                        cout<<endl<<"Please input the unit cost: ";
                        cin>>inventoryList[i];
                        outputFile <<inventoryList[i]<<" ";
                        break;
                    case 3:
                        cout<<endl<<"Please input the Markup % : ";
                        cin>>inventoryList[i];
                        markUp = stoi(inventoryList[i]);
                        while(markUp % 5 != 0 || markUp < 5 || markUp > 50)
                        {
                            cout <<endl<< "Errror: Invalid Markup, Please use multiples of 5 between 5%-50% "<<endl;
			            	cout<< "Please enter the markup of the item: ";
                            cin>>inventoryList[i];
                            markUp = stod(inventoryList[i]);
                        }
                        outputFile <<inventoryList[i]<<" ";
                        break;
                }
            }
            count++;
            outputFile << endl;
            cout<<"Wish to Continue Y=Yes, N=NO: ";
            cin>>letter;
            while (!((letter == 'y') || (letter == 'Y') || (letter == 'n') || (letter == 'N')))
            {

                cout << "ERROR: a Y or an N must be entered: ";
                cin.clear();
                cin >> letter;
            }
            letter = toupper(letter);
            if(letter == 'N')
            {
                break;
            }
        }
        cout<<"Number of Records Input: "<< count<<endl;
        cout << "Press Enter to Continue"<<endl;
        cin.get();
        cin.get();
        outputFile.close();
    }
    else
    {
        cout<<"Error in creating the file"<<endl;
    }
}
int countFile()
{
    int count = 0;
    string temptest;
    ifstream inputFile;
    inputFile.open("PRODUCT.TXT");
    if(inputFile)
    {
        while(getline (inputFile, temptest))
        {
            count++;
        }
        inputFile.close();
    }
    else
    {
        cout<<"Error opening the File";
    }
    return count;
}
void displayFile()
{
    int count= countFile();
    string item;
    ifstream inputFile;
    inputFile.open("PRODUCT.TXT");
    
    if(inputFile)
    {
        cout<<"Inventory"<<setw(20)<<"Item"<<setw(20)<<"Unit"<<setw(20)<<"Markup"<<endl;
        cout<<" Number "<<setw(25)<<"Description"<<setw(16)<<"Cost"<<setw(18)<<"%"<<endl;
        cout<<"========="<<setw(25)<<"============="<<setw(18)<<"========="<<setw(19)<<"========="<<endl;
        while(inputFile)
        {
            for(int i = 0; i < count ;i++)
            {
            
                for(int i=0;i<=3;i++)
                {
                    switch(i)
                    {
                        case 0:
                            inputFile>>item;
                            cout<<item<<setw(19)<<"";
                            break;
                        case 1:
                            inputFile>>item;
                            cout<<left<<setw(7)<<item;
                            break;
                        case 2:
                            inputFile>>item;
                            cout<<right<<""<<setw(24)<<item;
                            break;
                        case 3:
                            inputFile>>item;
                            cout<<right<<""<<setw(19)<<item;
                            break;
                    }
                }
                cout<<endl;
            }
            break;
            
        }
        cout << "Press Enter to Continue"<<endl;
        cin.get();
        cin.get();
        inputFile.close();
    }
    else
    {
        cout<<"Error opening the File";
    }
}
void processFile()
{
    bool showMarkup = false;
    string inventoryNumber,itemDescript,temp;
    int rows = countFile(),count = 0,tempMarkUp;
    double unitCost,tempMarkAmount=0,tempUnitPrice=0.00,markUpArray[10][3],diff;
    string holding[rows][4];
    ifstream inputFile;
    inputFile.open("PRODUCT.TXT");
    if(inputFile)
    {
        while(inputFile)
        {
            for(int i = 0; i <= rows;i++)
            {
                for(int j = 0 ; j < 4;j++)
                {
                        inputFile>>holding[i][j];
                }
            }
        }
        inputFile.close();
    }
    else
    {
        cout<<"Error opening the File";
    }
    for (int i = 0; i < rows; i++ )
    {
        cout<<"Inventory"<<setw(20)<<"Item"<<setw(20)<<"Unit"<<setw(25)<<"Markup"<<setw(18)<<"Markup"<<setw(18)<<"Unit"<<endl;
        cout<<" Number "<<setw(25)<<"Description"<<setw(16)<<"Cost"<<setw(23)<<"%"<<setw(20)<<"Amount"<<setw(18)<<"Price"<<endl;
	cout<<"=========="<<setw(25)<<"============="<<setw(18)<<"========="<<setw(22)<<"========="<<setw(17)<<"========="<<setw(18)<<"=========="<<endl;
        for (int j = 0; j < 4; j++ ) 
        {
            switch(j)
            {
                case 0:
                    inventoryNumber = holding[i][j];
                    break;
                case 1:
                    itemDescript = holding[i][j];
                    break;
                case 2:
                    temp = holding[i][j];
                    unitCost = stod(temp);
                    break;
                case 3:
                    int markUpPercent = stod(holding[i][j]);
                    tempMarkUp = markUpPercent;
                    cout<<inventoryNumber<<setw(21)<<""<<left<<setw(10)<<itemDescript<<right<<""<<setw(18)<<setprecision(2)<<fixed<<unitCost<<right<<""<<setw(18);
                    int tempMark = 0;
                    for(int k=0;k<10;k++)
                    {
                        for(int m = 0; m<3;m++)
                        {
                            switch(m)
                            {
                                case 0:
                                    tempMark = tempMark + 5;
                                    markUpArray[k][m]= tempMark;
                                    if(markUpPercent == tempMark)
                                    {
                                        showMarkup = true;
                                        cout<<"**"<<setprecision(2)<<fixed<<markUpArray[k][m];
                                    }
                                    else
                                    {
                                        cout<<"  "<<setprecision(2)<<fixed<<markUpArray[k][m];
                                    }
                                    break;
                                case 1:
                                    tempMarkAmount = (tempMark * unitCost)/100;
                                    markUpArray[k][m]= tempMarkAmount;
                                    cout<<"%"<<setw(11)<<"$"<<setw(7)<<right<<markUpArray[k][m]<<setprecision(2)<<fixed;
                                    break;
                                case 2:
                                    tempUnitPrice = unitCost + tempMarkAmount;
                                    markUpArray[k][m] =tempUnitPrice;
                                    if(markUpPercent == tempMark)
                                    {
                                        cout<<setw(10)<<"$"<<setw(7)<<right<<setprecision(2)<<fixed<<markUpArray[k][m]<<"**"<<endl;
                                    }
                                    else
                                    {
                                        cout<<setw(10)<<"$"<<setw(7)<<right<<setprecision(2)<<fixed<<markUpArray[k][m]<<endl;
                                    }
                                    if(k!=9)
                                    {
                                        cout<<"   "<<setw(18)<<""<<left<<setw(10)<<"     "<<right<<""<<setw(18)<<"   "<<right<<""<<setw(19);
                                    }
                                    else
                                    {
                                        markUpPercent = false;
                                        int below = (tempMarkUp / 5)-1;
                                        int above = (10-below)-1;
                                        cout<<endl<<"## - Markup percentages are available to increase profits: "<< above<<endl;
                                        cout<<"## - Markup percentages are available for sale purposes before selling at cost: "<<below<<endl;
                                        break;
                                    }
                            break;
                            }
                        }
                    }
                    cout << "Press Enter to Continue"<<endl;
                    cin.get();
                    cin.get();
                    break;
            }
        }
        cout<<endl;
    }
}





