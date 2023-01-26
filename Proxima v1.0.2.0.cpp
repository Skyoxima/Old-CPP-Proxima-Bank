#include<iostream.h>    //cin cout
#include<stdio.h>       //cprintf
#include<conio.h>       //getch clrscr textcolor
#include<stdlib.h>      //exit
#include<fstream.h>     // ifstream ofstream
#include<dos.h>         // delay
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
}

void bank::transac(deporwit d)
{
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
	   cout<<"The last transaction was a DEPOSITION.\n";
  else if(lt==2)
	   cout<<"The last transaction was a WITHDRAWAL.\n";
  else
	   cout<<"Last transaction unavailable.\n";
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
 clrscr();
 bank b;
 deporwit d1;

  rules();
  b.in_amount();
  b.display();
  d1.askdw();
  b.getValue();
  b.transac(d1);
  b.out_amount();
  b.display();
  askagain();

 getch();
}

void rules()
{
  clrscr();
 textcolor(12);
  cout<<"\t\t\t\t";
  cprintf("Welcome to Proxima."); cout<<endl;
 textcolor(11);
  cprintf("To make you transaction smoother, please follow the instructions listed below :");cout<<endl;
 textcolor(15);
  cprintf("1. When prompted, please press 1 for DEPOSITION or 2 for WITHDRAWAL."); cout<<endl;
  cprintf("2. When prompted, please press 0 for NO or 1 for YES. "); cout<<endl;
  cprintf("3. Incorrect selections for the above will terminate the transaction."); cout<<endl;
  cprintf("Press ant key to continue...");
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
   main();             //doesnt let me rule check.

   default:
   cout<<"Incorrect selection...aborting...";
   delay(2000);
   exit(0);
  }
}
