#include <iostream>
#include<fstream>
#include<string.h>
using namespace std;
class adress
{
    public:
             char city[30];
             int distance;
			 int id;

            adress() {
                    distance=0;
                    city[0]='/0';}
            ~adress() {}
            void read();
            void print();
};
class student: public adress
{
    public: char fname[30];
             char lname[30];
             char gender;
             int request;
			 double avg;
			 int nrroom;
    public:
			student(){ fname[0]='/0';
			          lname[0]='/0';
					  gender='/0';
					  request=0;
					  avg=0;
					  nrroom=0;
			}
			~student() {}
            void read();
			//void readfis(int, student*);
			void addstudent();
            void print();
			void room();
			void deletestudent();
};
void student::room ()
{
	cout<<fname<<" "<<lname<<" stays in room number "<< (nrroom-1)<<endl;
}
 
void adress::read()
{
    cout<<"The adress is:"<<endl;
    cout<<"City: ";
    cin.ignore(100,'\n');
    cin.getline(city,30);
    cout<<"Distance between the city and the University is:";
    cin>>distance;
}
void adress::print()
{
    cout<<"City "<<"\t"<<city<<endl;
    cout<<"The distance between the city and the University is"<<"\t"<<distance<<endl;
}
void student::print()
{
    cout<<fname<<"\t"<<lname<<"\t"<<avg<<endl;

}
void student::read()
{
    cout<<"The first name of the student is: ";
	cin.ignore(100,'\n');
    cin.get(fname,30);
    cout<<"The last name of the student is: ";
	cin.ignore(100,'\n');
    cin.get(lname, 30);
    cout<<"The gender of the student: G for girl and B for boy";
	cin.ignore(100,'\n');
    cin.get(gender);
    if(gender!='G'&& gender!='B') cout<<"Error! Gender invalid!";
    cout<<"Write the last semester average or the average entrance";
    cin>> avg;
    cout<<"Write 1 if the student requested to stay in a student dorm or 0 if he didn't";
    cin>>request;
    adress::read();
}
void readfis(int n, student*s)
{
	ifstream infile;
	int nr;
	infile.open("read.txt",ios::app);
	if(!infile.is_open())
	{
		cout<<"Error opening infile!";
	}
	infile>>nr;
		for(int i=0;i<n;i++)
		{
			infile>>s[i].fname;
			  infile>>s[i].lname;
			  infile>>s[i].gender;
			  infile>>s[i].request;
			  infile>>s[i].avg;
			  infile>>s[i].city;
			  infile>>s[i].distance;

		}
		infile.close();
}

void deletestud(student *s, int n)
{
	int nr;
	ifstream infile;
	student aux;
	readfis(n,s);
	cout<<"\nWhich student do you want to delete?\n";
	for(int i=0;i<n;i++)
	{
		cout<<i<<". ";
			s[i].print();
	}
	cin>>nr;
		 for(int j=nr;j<n-1;j++)
            s[j]=s[j+1];
        n--;

}
void student::addstudent()
{
	fstream infile;
	student aux;
	aux.read();
	infile.open("read.txt",ios::app);
	if(!infile.is_open())
	{
		cout<<"Error opening infile!";
	}
	infile<<endl<<aux.fname<<" "<<aux.lname<<" "<<aux.gender<<" "<<aux.request<<" "<<aux.avg<<" "<<aux.city<<" "<<aux.distance;
          
	infile.close();
	
}
void printfis (int n, student*s)
{
	ofstream outfile;
	int i, nr=1;
	student girl[100], boy[100];
	int nr1=0, nr2=0;
	for(i=0;i<n;i++)
		if(s[i].gender=='G')
		{ 
			girl[nr1]=s[i];
			nr1++;
		}
		else
		{boy[nr2]=s[i];
	nr2++;
	}
	for(i=0;i<n;i++)
		if(i<nr1) s[i]=girl[i];
		else
			s[i]=boy[i-nr1];
	 outfile.open ("stud.txt", ios::trunc);
    if(outfile.is_open())
    {
        for(i=0;i<n;i++)
		{
			s[i].nrroom=nr;
			if(i%4==0||i==nr1) {outfile<< "Room "<<nr<<" : ";  nr++; s[i].nrroom=nr; }
            outfile.width(30);
            outfile<<"\t"<<s[i].fname<<"\t";
            outfile.width(30);
            outfile<<s[i].lname<<"\t";
            outfile<<s[i].gender;
            outfile<<endl;
			
        }

        outfile.close();
    }
	else
		cout<<"Error opening outfile!";
}
void printrooms (student* s, int n)
{
	student girl[100], boy[100];
	int nr1=0, nr2=0,i;
	for(i=0;i<n;i++)
		if(s[i].gender =='G')
		{ 
			girl[nr1]=s[i];
			nr1++;
		}
		else
		{boy[nr2]=s[i];
	nr2++;
	}
	for(i=0;i<n;i++)
		if(i<nr1) s[i]=girl[i];
		else
			s[i]=boy[i-nr1];
	int nr=1;
	 for(i=0;i<n;i++)
		{
			s[i].nrroom=nr;
			if(i%4==0|| i==nr1) {cout<< "Room "<<nr<<" : ";  nr++; s[i].nrroom=nr;}
            cout<<"\t"<<s[i].fname<<"\t";
            cout<<s[i].lname<<"\t";
            cout<<s[i].gender;
            cout<<endl;
        }

}

void compare (student* s, int n)
{
    student aux;
	for(int i=0;i<n-1;i++)
    for(int j=i+1;j<n;j++)
       if(s[i].avg<s[j].avg)
        {
        aux=s[i];
        s[i]=s[j];
        s[j]=aux;
        }
}
void deletes (student *s, int &n)
{
    int i;
    for(i=0;i<n;i++)
        if(s[i].request==0)
    {
        for(int j=i;j<n-1;j++)
            s[j]=s[j+1];
        n--;
    }
}

void print_menu()
{
	cout<<"Menu"<<endl;
	cout<<"1. Add student"<<endl;
	cout<<"2. Delete student"<<endl;
	cout<<"3. Show the list of the students"<<endl;
	cout<<"4. Show the students grouped by rooms"<<endl;
	cout<<"5. Find out in which room is a specific student"<<endl;
	cout<<"6. Exit"<<endl;
}
void option1 (student* s, int n )
{
	ofstream outfile;
	student aux;
	aux.addstudent();
     n++;
	 readfis(n,s);
	 outfile.open ("read.txt", ios::trunc);
	 outfile<<n<<endl;
	 for(int i=0;i<n;i++)
		 outfile<<s[i].fname<<" "<<s[i].lname<<" "<<s[i].gender<<" "<<s[i].request<<" "<<s[i].avg<<" "<<s[i].city<<" "<<s[i].distance<<endl;
	 outfile.close();
	 cout<<"Display students:"<<endl;
	 for(int i=0;i<n;i++)
		 cout<<i<<". "<<s[i].fname<<" "<<s[i].lname<<endl;
}
void option2 (student *s, int n)
{
	ofstream outfile;
	deletestud (s,n);
	n--;
	outfile.open ("read.txt", ios::trunc);
	outfile<<n<<endl;
	for(int i=0;i<n;i++)
		 outfile<<s[i].fname<<" "<<s[i].lname<<" "<<s[i].gender<<" "<<s[i].request<<" "<<s[i].avg<<" "<<s[i].city<<" "<<s[i].distance<<endl;
	 outfile.close();
	  for(int i=0;i<n;i++)
		 cout<<i<<". "<<s[i].fname<<" "<<s[i].lname<<endl;

}
int main()
{
	char option;
    ofstream outfile;
	ifstream infile;
    int n=0,i,j,rooms, nr=0;
    student *s, aux;
   infile.open("read.txt",ios::app);
	infile>>n;
	infile.close();
	s=new student[n];
	readfis(n,s);
	compare(s,n);
	 printfis(n,s);
	 int nr2;
	do
	{
		print_menu();
		cin>>option;
		switch (option)
		{
		case '1': { option1(s,n); break; }
		case '2': { option2(s,n); break;}
		case '3': { for(i=0;i<n;i++)
					  s[i].print();
			break;
				  }
		case '4': {
			
			printrooms(s,n);
			break;
				  }
		case '5': {
			for(i=0;i<n;i++)
			{
				cout<<i<<". ";
					  s[i].print();
			}
			cout<<"--------------------------"<<endl;
			cout<<"The number of the student: ";
		          cin>>nr2;
                   s[nr2].room();
				   break;
				  }
				 
		case '6': { cout<<"Completed\n";
			        cin.ignore(1);
					cin.get();
					exit(0);
				  }
		default: cout<<"Incorrect option!\n";
		}
		cin.get();
	}while(1);
	delete [] s;
	cin.ignore(100,'\n');
	cin.get();
    return 0;
}
