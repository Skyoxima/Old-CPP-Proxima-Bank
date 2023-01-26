#include<iostream.h>    //cin cout
#include<stdio.h>       //cprintf
#include<conio.h>       //getch clrscr textcolor
#include<stdlib.h>      //exit
#include<fstream.h>     // ifstream ofstream
#include<dos.h>	        // delay
#include<string.h>      //strcpy

void askagain();
void endgreet();
void rules();
class deporwit;

class bank
{
private:
double amt,v;
int lt;

public:
bank()
 {
   lt=0;
   amt=0;
 }
void display();
void in_amount();
void out_amount();
void getValue();
void transac(deporwit);
void in_log();
void out_log();
void in_loglist();
void out_loglist();
};

class deporwit
{
private:
int dw,cdw,check;

public:
void askdw();
void confdw();
void checkagain();
friend void bank::transac(deporwit);
};

void deporwit::askdw()
{
cout<<"Select whether to perform DEPOSITION or WITHDRAWAL : ";
cin>>dw;

switch(dw)
 {
  case 1:
  cout<<"You have selected DEPOSITION...\n";
  confdw();
  break;

  case 2:
  cout<<"You have selected WITHDRAWAL...\n";
  confdw();
  break;

  default:
  cout<<"The entered key was inapproriate...Would you like to choose again? : ";
  cin>>check;
  checkagain();
 }
}

void deporwit::confdw()
{
cout<<"Please Enter Confirmation : ";
cin>>cdw;

switch(cdw)
 {
  case 0:
  cout<<"Transaction Denied;\n Would you like to select a type again? : ";
  cin>>check;
  checkagain();
  break;

  case 1:
  cout<<"Transaction Confirmed!\n";
  break;

  default:
  cout<<"Confirmation entered was undefined...\n"<<"Would you like to select a type again? : ";
  cin>>check;
  checkagain();
 }
}

void deporwit::checkagain()
{
switch(check)
{
  case 0:
  cout<<"\n\n\t\t\t\tExiting...";
  delay(3000);
  exit(0);
  break;

  case 1:
  cout<<"Proceduring...\n";
  delay(1000);
  askdw();
  break;

  default:
  cout<<"Too many incorrect selections...aborting the program...";
  delay(2000);
  exit(0);
 }
}

void bank::getValue()
{
  cout<<"Now enter the amount to be transacted : ";
  cin>>v;
  if(v<0)
  {
    textcolor(RED);
    cprintf("Negative number entered...please enter a positive amount!"); cout<<endl;
    getValue();
  }
}

void bank::transac(deporwit d)    //since transaction is the friend of deporwit , we need to pass deporwit's object to it.
{                                 //as friend functions are not the member of the class , they cant directly access the data , they can through an object
 if(d.dw==1)
  {
   cout<<"The amount entered will be DEPOSITED.\n\n";
   amt=amt+v;
   lt=1;
  }
 else
  {
   cout<<"The amount entered will be WITHDRAWN.\n\n";
   amt=amt-v;
   lt=2;
  }
}

void bank::display()
{
  textcolor(10);
  cprintf("Current available balance : ");
  cout<<amt<<"\n";

  if(lt==1)
	   cout<<"The last session of transaction was a DEPOSITION.\n";
  else if(lt==2)
	   cout<<"The last session of transaction was a WITHDRAWAL.\n";
  else
	   cout<<"Last session of transaction unavailable.\n";
}

void bank::in_amount()
{
ifstream inamount;
inamount.open("Amount.txt");
inamount>>amt;
inamount.close();
}

void bank::out_amount()
{
ofstream outamount;
outamount.open("Amount.txt",ios::trunc);
outamount<<amt;
outamount.close();
}

void bank::in_log()
{
  ifstream lastlog;
  lastlog.open("Lastlog.txt");
  lastlog>>lt;
  lastlog.close();
}

void bank::out_log()
{
  ofstream lastlog;
  lastlog.open("Lastlog.txt");
  lastlog<<lt;
  lastlog.close();
}

void bank::in_loglist()
{
  char log[15];
  ifstream inloglist;
  inloglist.open("Loglist.txt");
  while(!inloglist.eof())
   {
     inloglist>>log;
     cout<<log<<endl;
   }
  inloglist.close();
}

void bank::out_loglist()
{
 char log[15];
 switch(lt)
  {
    case 1:
    strcpy(log,"DEPOSITION");
    break;

    case 2:
    strcpy(log,"WITHDRAWAL");
    break;

    default:
    strcpy(log,"START");
  }
 ofstream outloglist;
 outloglist.open("Loglist.txt",ios::app);
 outloglist<<log<<endl;
 outloglist.close();
}

void endgreet()
{
   textcolor(11);
   cout<<"\n\t\t";
   cprintf("Thank you for banking with us!");
   textcolor(14);
   cout<<"\n\t\t\t";
   cprintf("Visit Again!");
}

void main()
{
 int logcheck;
 clrscr();
 bank b;
 deporwit d1;

  rules();
  b.in_amount();
  b.in_log();
  cout<<"Would you like your transaction history? : ";
  cin>>logcheck;
   switch(logcheck)
    {
     case 1:
     clrscr();
     b.in_loglist();
     getch();
     clrscr();
     break;

     case 0:
     cout<<"Log Denied...proceeding with current session...\n";
     clrscr();
     break;

     default:
     cout<<"Incorrect criteria passed...this session will be terminated.";
     delay(2000);
     exit(0);
    }
  b.display();
  d1.askdw();
  b.getValue();
  b.transac(d1);
  b.out_amount();
  b.out_log();
  b.out_loglist();
  b.display();
  askagain();

 getch();
}

void rules()
{
  clrscr();
 textcolor(12);
  cout<<"\t\t\t\t";
  cprintf("WELCOME TO PROXIMA."); cout<<endl<<endl;
 textcolor(11);
  cprintf("To make you transaction smoother, please follow the instructions listed below :");cout<<endl;
 textcolor(15);
  cprintf("1. When prompted, please press 1 for DEPOSITION or 2 for WITHDRAWAL."); cout<<endl;
  cprintf("2. When prompted, please press 0 for NO or 1 for YES. "); cout<<endl;
  cprintf("3. Incorrect selections for the above will terminate the transaction."); cout<<endl;
  cprintf("Press any key to continue...");
  getch();
  clrscr();
}

void askagain()
{
 int anotherone;
 cout<<"Would you like to carry out another transaction? : ";
 cin>>anotherone;

 switch(anotherone)
  {
   case 0:
   endgreet();
   delay(2000);
   exit(0);
   break;

   case 1:
   cout<<"Proceeding...\n";
   delay(1000);
   main();
   break;             //doesnt let me rule check.

   default:
   cout<<"Incorrect selection...aborting...";
   delay(2000);
   exit(0);
  }
}
