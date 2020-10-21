#include<iostream>//Iostream Header File
#include<fstream>// Fstream Header File
#include<iomanip> //Manipulator Header File
#include<cstring> //String Header File
#include<conio.h> //Console Input Output Header File
#include<time.h> // Getting Current Date & Time 
#include<dos.h> //Execution Of System Commands
#include<stdlib.h>//Standard Library For Various Functionalites
#include<stdio.h>//For Remove() & Rename()

using namespace std; //Using standard Namespace  called std
class UMS //Base Class UMS
{
	private: //Private Acess Specifiers
	static int count;
    bool state=0;
	string filename[50];//Filename FOR ATA
	int index=0;//filename index
	string regno;
	string username,password; // Suppose Username = 11804339 Password = 123456
	string newpass,newpass2;
	string x;
	int optionfmenu;//Faculty Menu Option
	fstream out; //Fstream Object
	int num;	//Option Choosen By User Under Main Menus 
	public://Public Acess Specifiers
	void mainPage(); //Main Page Introduction 
	void mainMenu(); //First Menu Which Got Fire As Soon As We Execute Our Program
	void studentLogin(); //Student Menu After Logging In Menu
	void facultyLogin();//Faculty Menu After Logging In Menu
	void userInput(); //User Input (Option) Taking Function
	void createTask();//For Faculty
	void assignTask();//For Faculty
	void updateTask();//For Faculty
	void showTask();//For Student
	void deleteTask();//For Faculty 
	void studentMenu(string);
	string getPassword();//
	void date();//
	void delay(unsigned int);//
	void readFile();
	void facultyMenu();//faculty menu
	int chkauth(string inputUsername,string inputPassword);//check authorization
	string updatePassword(string pass);
	int cfpass();
	int chkpriv(int num);
	string tasks;
	string ctopt; //ChooseTaskOption name
	string chooseTask();
	//Assign Functions
	void ATIO(string opt);//Assign To Individual
	void ATA(string opt);//Assign To All
	void ATI(string name,string opt);//Function Overloading
	void stushowTask(string username);
	void newstu();
};
void UMS::newstu()
{
	string nusername;
	string npassword;
	cout<<"Enter New Student Username "<<endl;
	cin>>nusername;
	cout<<"Enter New Student Password "<<endl;
	cin>>npassword;
	ofstream out;
	out.open("uid_password",ios::out|ios::app);
	out<<nusername+npassword<<endl;
	cout<<"Student Sucessfully Registered "<<endl;
	getch();
	cout<<"Press Enter To Exit To MainMenu";
	
}
void UMS::ATA(string opt)
{ 
    ifstream file("regno.txt");
    if(file.is_open()) 
     {
		for(int i = 0; i < 50; ++i)
    	file >> filename[i];
     }
     for(int i=0;i<50;i++)
     { 
     	ATI(filename[i],opt);
	 }	
	 	facultyMenu();
}
//Function Overloading On ATI
inline void UMS::ATI(string name,string opt)
{
	string ext=".txt";//Extension
	string filename=name.c_str();//Conversion To Character String
	string final=filename+ext;//Concatinate
	for(int i=0;i<50;i++)
	{
	fstream out; //Object For Writing
	out.open(final,ios::out);
	out.close();	
	}
	string newopt=opt+".txt";	
	ifstream file (newopt,ios::in);
	ofstream ofile(final,ios::app);
	while (!file.eof())
	{
   		getline(file,x);
        ofile<<x<<endl;
	}
	file.close();
	ofile.close();
	std::cout<<"Task Assigned Sucessfully To Registration No : "<<name<<endl;
}
inline void UMS::ATIO(string opt)
{	
	cout<<"Enter Registration No Of Student";
	cin>>regno; //Registration No Of Student
	string filename;//Filename
	string ext=".txt";//Extension
	filename=regno.c_str();//Conversion To Character String
	string final=filename+ext; //Concatenate
	fstream out; //Object For Writing
	out.open(final,ios::out);
	out.close();
	string newopt=opt+".txt";	
	ifstream file (newopt,ios::in|ios::app);
	ofstream ofile (final,ios::app);
	while (!file.eof())
	{
   		getline(file,x);
        ofile<<x<<endl;
	}
file.close();
ofile.close();
std::cout<<"Task Assigned Sucessfully"<<endl;
facultyMenu();	
}
string UMS::chooseTask()
{
	cout<<"Enter Task Name You Want To Assign:"<<endl;;
	cin>>ctopt;
	return ctopt;
}
void UMS::createTask()
{
showTask(); 
int coption;
string taskname;
std::cout<<"Enter Task Name : ";
cin>>taskname;
fflush(stdin);
fstream out1;
out1.open("AllTasks.txt",ios::out|ios::app);
out1<<taskname<<endl;//out1<<"\t\t"<<taskname<<endl;
out1.close();
string finaltaskname;
finaltaskname=taskname+".txt";
fstream out;
out.open(finaltaskname.c_str(),ios::out);
char taskdata[200];
cout << "Enter Task To Be Written" << endl;
fflush(stdin);
cin.getline(taskdata, sizeof(taskdata));
out <<taskdata<<endl; 
out.close();
cout<<"Press 1 Add More Tasks"<<endl;
cout<<"Press 2 Exit"<<endl;
cin>>coption;
switch(coption)
{
	case 1:createTask();
			break;
	case 2:facultyMenu();
			break;
	default:cout<<"Invalid Input";
			mainMenu();			
}
}







void UMS::assignTask()
{	int atopt;//assigntaskoption
	string opt;
	showTask();
	opt=chooseTask();
	std::cout<<"Press 1 To Assign Task To Individually"<<endl;
	std::cout<<"Press 2 To Assign Task To All"<<endl;
	std::cout<<"Press 3 To Enter Main Menu"<<endl;
	std::cout<<"Press 4 To Create New Task"<<endl;
	cin>>atopt;
	switch(atopt)
	{
		case 1:ATIO(opt);//Assign To Individual Function
				break;
		case 2:ATA(opt); //Assign To All Function
				break;
		case 3:
				{	mainMenu();
					break;
				}
		case 4:createTask();
				break;
	    default:{
				cout<<"You Entered Invalid Input"<<endl;
				delay(30);
				cout<<"Restarting";
				mainPage();
				break;
				}	
	}
}








void UMS::updateTask()
{	int uoption;
	string taskname;
	showTask();
	cout<<"Enter The Task Name You Want To Update :"<<endl;
	cin>>taskname;
	string finaltaskname=taskname+".txt";
	ofstream out;
	out.open(finaltaskname.c_str(),ios::out);
    char taskdata[200];
    cout << "Enter Task To Be Written" << endl;
    fflush(stdin);
    cin.getline(taskdata, sizeof(taskdata));
    out <<taskdata<<endl; 
    out.close();
    cout<<"Task Name "<<taskname<<" Written Sucessfully"<<endl;
    cout<<"Press 1  Update Add More Tasks"<<endl;
    cout<<"Press 2 Exit"<<endl;
    cin>>uoption;
    switch(uoption)
    {
	case 1:updateTask();
			break;
	case 2:facultyMenu();
			break;
	default:cout<<"Invalid Input";
			mainMenu();			

    }
    }	
    
    
    
    
    
    
    
    
    
    
void UMS::showTask()
{ 
	        system("cls");
	        cout<<"All Tasks Are Listed Below"<<endl;
			ifstream out1;
			out1.open("Alltasks.txt");
			char c;
			
				c=out1.get();
			while(!out1.eof())
			{
				cout<<c;
				c=out1.get();
			
			}
			out1.close();
			cout<<endl;
}
void UMS::deleteTask()
{	string taskname;
	int doption;
	showTask();
	cout<<"Enter Task Name To Be Deleted :"<<endl;
	cin>>taskname;
	string finaltaskname=taskname+".txt";
	string deldata="\t\t"+taskname;
	ifstream file ( "Alltasks.txt" );
	ofstream ofile ( "Alltasks1.txt",ios::app);
	while (getline(file,x))
		{
    		if (x == taskname)
    		{
    			ofile<<"";
    		remove(finaltaskname.c_str());
    		}
    		else
			{
        	ofile<<x<<endl;
			}
	}
	
file.close();
ofile.close();
remove("Alltasks.txt");
rename("Alltasks1.txt","Alltasks.txt");
std::cout<<"Sucessfully Deleted"<<endl;
cout<<"Press 1 Delete  More Tasks"<<endl;
cout<<"Press 2 Exit"<<endl;
cin>>doption;
switch(doption)
{
	case 1:deleteTask();
			break;
	case 2:facultyMenu();
			break;
	default:cout<<"Invalid Input";
			mainMenu();			

}

}


int UMS::chkpriv(int num){
	if(num==1)
	{
		return 1;
	}
	else if(num==2)
	{
		return 2;
	}
}



void UMS::facultyMenu()
{				 system("cls");
	 			cout<<"Press 1 - Create Task"<<endl;
	 			cout<<"Press 2 - Assign Task"<<endl;
		        cout<<"Press 3 - Update Task"<<endl;
		        cout<<"Press 4 - Delete Task"<<endl;
		        cout<<"Press 6 - Exit"<<endl;
		        cout<<"Press 5 - To Register New Student"<<endl;
		        cout<<"Enter your choice "<<endl;
		        cin>>optionfmenu;
			switch(optionfmenu) // switch case for choice in mainMenu() Function 
	
			{
				case 1: createTask(); // 
						break; //have to break
				case 2: assignTask();//facultyLogin() Will Be Here; //choice 2
						break; //have to break
				case 3: updateTask();//facultyLogin() Will Be Here; //choice 2
						break; //have to break
				case 4: deleteTask();//facultyLogin() Will Be Here; //choice 2
						break; //have to break
				case 5: newstu();//mainMenu Calling Will Be Here
						break; //have to break	
				case 6: mainMenu();
						break;			
				default: // And Here Comes Default Scenario
					{cout<<"You Entered Invalid Input"; // Statment
					mainMenu();
					} 		
	}
}



int UMS::cfpass()
{
	 	std::cout<<"Enter New Password To Continue"<<endl;
		std::cout<<"Password"<<endl;
		cin.ignore();
		std::cin>>newpass;
		std::cout<<"Confirm Password";
		cin.ignore();
		std::cin>>newpass2;
		if(newpass==newpass2)
		{
		return 1;
		}
		else
		{
			return 0;
		}
}



int UMS::count=0;
string UMS::updatePassword(string pass)
        {
			ifstream file ( "uid_password.txt" );
			ofstream ofile ( "uid_password1.txt",ios::app);
			while (!file.eof())
		{
   	 		getline(file,x);
    		if (x == pass)
    		{
        	ofile << username+newpass << endl;
        	
    		}
    		else
			{
        	ofile<<x<<endl;
			}
	}
file.close();
ofile.close();
remove("uid_password.txt");
rename("uid_password1.txt","uid_password.txt");
std::cout<<"Sucess Login Again"<<endl;
	mainMenu();
	}
	
	
	
	
	
	
	
	
int UMS::chkauth(string inputUsername,string inputPassword)
{
  string  pass = inputUsername+""+inputPassword; // Search pattern
        int offset;
        string line;
        ifstream usersFile;
        usersFile.open ("uid_password.txt");
        if(usersFile.is_open())
        {
        while(!usersFile.eof())
        {
        getline(usersFile,line);
        if ((offset = line.find(pass, 0)) != string::npos) 
		{   // if login data is found
        cout<<endl<<"Login SucessFull "<<endl;
        usersFile.close();
        int option;
        system("cls");
        std::cout<<"Do You Want To Update Your Pasword"<<endl;
        std::cout<<"Press 1 For Yes"<<endl;
        std::cout<<"Press 2 For No"<<endl;
		cin>>option;
        if(option==1)
        {
            int cf=cfpass();
            if(cf)
        	{
        		updatePassword(pass);
			}
			else 
			{
			cfpass();
			}
			
		}
        else if(option==2)
		{
         int ans=chkpriv(num); //student -1 faculty 2
		 if(ans==1)
		 	{
		 	//studentMenu();
		 	system("cls");
		 	cout<<"Welcome To Student Menu"<<endl;
		 	studentMenu(username);
			 }
		 else if(ans==2)
		 	{
		 	system("cls");
		    cout<<"Welcome To Faculty Menu"<<endl;
		 	facultyMenu();
		 
		 	}
		}
}
}
} 
	cout<<endl<<"Invalid Input"<<endl;
	cout<<endl<<"Restarting"<<endl;
	mainPage();
}




void UMS::stushowTask(string username)
{
 			int stusopt;
			system("cls");
	        cout<<"All Tasks Are Listed Below"<<endl;
			ifstream out1;
			string finalusername=username+".txt";
			out1.open(finalusername.c_str(),ios::in);
			char c;
			
				c=out1.get();
			while(!out1.eof())
			{
				cout<<c;
				c=out1.get();
			
			}
			out1.close();
			cout<<endl;
			fflush(stdin);
			std::cout<<endl<<"Press 1 To Exit To Main Menu"<<endl;
			cin>>stusopt;
			if(stusopt==1)
			{
				mainMenu();
			}
			else
			{
				cout<<"Restarting....";
				mainPage();
			}
}
void UMS::delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void UMS::date()
{
  time_t T= time(NULL);
  struct  tm tm = *localtime(&T);
  printf("\n\n\n");
  printf("\t\t\t\t\t   Date:%02d/%02d/%04d\n",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UMS::mainPage() 
{
  int process=0;
  date();
  cout<<"\n";
  cout<<"\t\t\t\t    ---------------------------\n";
  cout<<"\t\t\t\t    |UMS MANAGEMENT SYSTEM|\n";
  cout<<"\t\t\t\t    ---------------------------\n";
  cout<<"\n\n\n";
  cout<<"\t\t\t\t";
  cout<<"Prepared By    ";
  cout<<":";
  cout<<"  Vansh Devgan";
  cout<<"\n\n";
  cout<<"\t\t\t\t";
  cout<<"CSE 101 Project  ";
  cout<<":";
  cout<<"   UMS Management System";
  cout<<"\n\n";
  cout<<"\t\t\t\t";
  cout<<"Guided By      ";
  cout<<":";
  cout<<"   Gautam Majumdar";
  cout<<"\n\n";
  cout<<"\t\t\t\t    Press Enter to continue......";
  cout<<"\n\n";
  getchar();
  cout<<"\t\t\t\tLoading";
  for(process=0;process<35;process++)
  {
    delay(60);
    cout<<".";
  }
mainMenu();
}
////////////////////////////////////////////////////////////////////////////////////////////
inline void UMS::mainMenu()//Defination of mainMenu Function Declared In Class UMS Public Section
 {	system("cls");
	std::cout<<" \t \t \t \t \t \t Choose Given Option Below -"<<endl<<endl; //Statement
	std::cout<<std::setfill('*')<<std::setw(50)<<" "<<endl<<endl;//Design ***
	std::cout<<"1- Student Login"<<endl<<endl;//Statement
	std::cout<<"2- Faculty Login"<<endl<<endl;//Statement
	userInput();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
void UMS::studentMenu(string username)
{ int soption;
cout<<"Press 1  Show Task"<<endl;
cout<<"Press 2  Logout"<<endl;
cin>>soption;
switch(soption)
{
	case 1:stushowTask(username);
			break;
	case 2:mainMenu();
			break;
	default:cout<<"Invalid Input";
			mainMenu();			

}
}

void UMS::studentLogin()//Defination of studentLogin() Function Declared In Class UMS Public Section
{
std::cout<<"Reg No : "<<endl; //statement
cin>>username;//Username input
	if(username.size()>9)
{
	cout<<"Reg NO Can't Be Greater Than 8";
	exit(1);
}
std::cout<<"Password : "<<endl;//statement	
cin>>password;	
chkauth(username,password);
//vansh=getPassword();//Password input
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void UMS::facultyLogin()
{
	std::cout<<"UID: "<<endl; //statement
	cin>>username;//Username input
	if(username.size()>6)
{
	cout<<"UID Can't Be Greater Than 6";
	exit(1);
}
	std::cout<<"Password : "<<endl;//statement	
	cin>>password;
	chkauth(username,password);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void UMS::userInput()// Defination of userInput() Function Declared In Class UMS Public Section.
{
cin>>num;// choice input
num=(int)num; // typecasting if user enterd float

switch(num) // switch case for choice in mainMenu() Function 
	
	{
	case 1: studentLogin(); //choice 1 
			break; //have to break
	case 2: facultyLogin();//facultyLogin() Will Be Here; //choice 2
			break; //have to break
	case 3: newstu();
	default: // And Here Comes Default Scenario
			cout<<"You Entered Invalid Input"; // Statment 		
	}
	
}
	
int main() // THIS IS MAIN FUNCTION
{
 UMS A;  // A Is Object Of Class UMS In Other Words - A Is Of Type UMS 
  A.mainPage();
  return 0;
}
