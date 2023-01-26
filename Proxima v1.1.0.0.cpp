//strcat stands for concatenate meaning to add strings.
#include<iostream.h>    //cin cout
#include<stdio.h>       //cprintf
#include<conio.h>       //getch clrscr textcolor
#include<stdlib.h>      //exit
#include<fstream.h>     // ifstream ofstream
#include<dos.h>	        // delay
#include<string.h>      //strcpy strlen strcat
#include<time.h>        //time_t

char accno[7];            //contains actual acc. no
char accname[40];         //contains actual name
char pass_file[20];      //"
char acc_name_file[20]; //contains name of files used in ifstream and ofstream
char acclastlog[20];   //  "
char accloglist[20];  //   "
char accamount[20];  //    "
char masterlist[80]; //contains total history for adminaccess

class account;
class deporwit;

void askagain();
void endgreet();
void rules();

class bank
{
private:
double amt,v;
int lt,passcheck;
char password[10],filepassword[10];

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
void pass_in();
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
    cprintf("Negative number entered...please enter a positive amount!"); cout<<endl<<endl;
    getValue();
  }
}

void bank::pass_in()
{
  textcolor(12);
  cprintf("Enter your 4 digit PIN : ");
  cin>>password;

  ifstream getpass;
  getpass.open(pass_file);
  getpass>>filepassword;

  passcheck=strcmp(filepassword,password);
  if(passcheck!=0)
  {
    cout<<"Entered password was invalid...please try again...\n";
    pass_in();
  }
  else
  {
    cout<<"\nAccess granted!\n";
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
   if(v>amt)
   {
     textcolor(13);
     cprintf("Insufficient funds...transaction abrupted.");
     delay(5000);
     exit(0);
   }
   else
    {
     amt=amt-v;
     lt=2;
    }
  }
}

void bank::display()
{
  textcolor(10);
  cprintf("Current available balance : ");
  cout<<amt<<" INR.\n";

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
  inamount.open(accamount);
  inamount>>amt;
  inamount.close();
}

void bank::out_amount()
{
  ofstream outamount;
  outamount.open(accamount,ios::trunc);
  outamount<<amt;
  outamount.close();
}

void bank::in_log()
{
  ifstream lastlog;
  lastlog.open(acclastlog);
  lastlog>>lt;
  lastlog.close();
}

void bank::out_log()
{
  ofstream lastlog;
  lastlog.open(acclastlog);
  lastlog<<lt;
  lastlog.close();
}

void bank::in_loglist()
{
  char timelog[80];

  ifstream inloglist;
  inloglist.open(accloglist);

  inloglist.getline(timelog,80);
  if(strlen(timelog)==0)
  {
    cout<<"No transaction history found...";
  }
  else
 {
   while(!inloglist.eof())
    {
      cout<<timelog<<endl;                   //getline works with files too!
      inloglist.getline(timelog,80);         //this will work because fstream has 2 pointers one for the beginning of the file and one for the current location.
    }
 }
 inloglist.close();
}

void bank::out_loglist()
{
  char log[20];
  char timelog[80];
  char timet[60];

  time_t currtime=time(NULL);
  strcpy(timet,ctime(&currtime));

 switch(lt)
  {
    case 1:
    strcpy(log,"DEPOSITION:- ");
    break;

    case 2:
    strcpy(log,"WITHDRAWAL:- ");
    break;

    default:
    strcpy(log,"START:- ");
  }

strcpy(timelog,log);
strcat(timelog,timet);

 ofstream outloglist;
 outloglist.open(accloglist,ios::app);
 outloglist<<timelog<<endl;
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

class account
{
  private:
   int linorsin,accnoagain,asknew_acc;
   char password[10];

  public:
   account()
   {
     ofstream accfile;          //just to create an accounts txt file
     accfile.open("Accounts.txt",ios::in);
     accfile.close();
   }

   void create_or_login();
   void getaccno();
   void checkaccno();
   void asknewaccount();
   void pass_out();
   void create_newaccount();
   void copy_cat();
   void generate_run();
   void master_listin();
   void master_listout();
   void adminaccess();
};

void account::create_or_login()
{
  textcolor(13);
		cout<<"\t";
		cprintf("Would you like to log in to an existing account?");
		cout<<"\n\t\t\tOR\n";
  textcolor(11);
		cout<<"\t\t";
		cprintf("Create a new account?:");    cout<<"\t";
		cin>>linorsin;

 textcolor(15);              //the last color which goes to main decides the color for the cout statements..thats why i added it here

 switch(linorsin)
 {
   case 1:
   cout<<"\t\tProceeding...\n";
   delay(2000);
   clrscr();
   getaccno();
   checkaccno();
   break;

   case 2:
   cout<<"\t\tProceeding...\n";
   delay(2000);
   clrscr();
   asknewaccount();
   break;

   default:
   cout<<"Incorrect selection, terminating the transaction.";
   delay(1000);
   exit(0);
 }
}

void account::getaccno()
{
  cout<<"Enter your 5 digit account number : ";
  cin>>accno;
}

void account::checkaccno()
{
  if(strcmp(accno,"0x09C")==0)
   {
     cout<<"Admin access granted! \n\n";
     adminaccess();
     return;   //if cannot have break, therefore i used return instead
   }          //return will go back to the function who called this one i.e create_or_login which is in main
	      //therefore the next line, getch() in main is executed after return
  else
   {
     char checker[20];
     int c;

     ifstream accnos;
     accnos.open("Accounts.txt");
     while(!accnos.eof())
     {
       accnos>>checker;
       c=strcmp(checker,accno);
       if(c==0)
       {
	 copy_cat();
	 generate_run();
	 return;
       }
     }
     accnos.close();
   }

cout<<"The entered account number is not recorded in present our database...\n";
cout<<"Would you like to try again? or Create a new account? ";
cin>>accnoagain;
if(accnoagain==1)
 {
   clrscr();
   getaccno();
   checkaccno();
 }
else if(accnoagain==2)
 {
   clrscr();
   asknewaccount();
 }
else
 {
   cout<<"Ending this session...";
   delay(1500);
   exit(0);
 }
}

void account::generate_run()
{
 strcpy(acc_name_file,accno);
 strcat(acc_name_file,"nm.txt");

 ifstream getname;
 getname.open(acc_name_file);
 getname.getline(accname,40);
 if(strlen(accname)==0)
 {
   strcpy(accname,"NONAME");
 }
 getname.close();

 cout<<"\n\t\t\t\tWelcome!"<<" "<<accname<<"\n\n";
 int histcheck;
 bank b;
 deporwit d1;

 b.in_amount();
 b.in_log();
 cout<<"Would you like to have your transaction history? : ";
 cin>>histcheck;

   switch(histcheck)
    {
     case 1:
     clrscr();
     b.in_loglist();
     getch();
     clrscr();
     break;

     case 0:
     cout<<"History denied...proceeding with current session...\n";
     delay(2000);
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
  b.pass_in();
  b.transac(d1);
  b.out_amount();
  b.out_log();
  b.out_loglist();
  b.display();
  askagain();
}

			       void main()
			       {
				 clrscr();
				 rules();
				 account a;
				 a.create_or_login();
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
  cprintf("1. When prompted, press 1 to login into an account, 2 to create an account."); cout<<endl;
  cprintf("2. When prompted, please press 1 for DEPOSITION or 2 for WITHDRAWAL."); cout<<endl;
  cprintf("3. When prompted for confirmation, please press 0 for NO or 1 for YES."); cout<<endl;
  cprintf("4. When prompted for a new transaction, press 1 for YES, 0 for NO."); cout<<endl;
  cprintf("5. When prompted for transaction history, press 1 for YES, 0 for NO."); cout<<endl;
  cprintf("6. When prompted for amount, do not put negative values!"); cout<<endl;
  cprintf("7. Incorrect selections for the above will terminate the transaction."); cout<<endl<<endl;
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
   break;             //doesnt let me rule check.But greatly reduces the work.

   default:
   cout<<"Incorrect selection...aborting...";
   delay(2000);
   exit(0);
  }
}

void account::copy_cat()
{
 strcpy(acclastlog,accno);
  strcat(acclastlog,"log.txt");
 strcpy(accloglist,accno);
  strcat(accloglist,"ll.txt");
 strcpy(accamount,accno);
  strcat(accamount,"amt.txt");
 strcpy(pass_file,accno);
  strcat(pass_file,"pas.txt");
}

void account::asknewaccount()
{
 cout<<"Would you like to create a new account? : ";
 cin>>asknew_acc;

 switch(asknew_acc)
  {
    case 0:
    cout<<"To make use of our services, you need to create an account first.";
    delay(5000);
    exit(0);
    break;

    case 1:
    cout<<"Proceeding...\n";    //call here
    create_newaccount();       //this \n is probably why am i forced to use cin.ignore in create function.
    break;

    default:
    cout<<"Transaction is not possible without an account...aborting...";
    delay(2000);
    exit(0);
  }
}

void account::pass_out()
{
  strcpy(pass_file,accno);
  strcat(pass_file,"pas.txt");

  ofstream givepass;
  givepass.open(pass_file);
  givepass<<password;
  givepass.close();
}

void account::create_newaccount()
{
  int x=0;
  textcolor(YELLOW);
  cout<<"Enter your name : ";
  cin.ignore();
  cin.getline(accname,40);

  cprintf("Generating your account number...");
  delay(4000);
  srand(time(NULL));

  x=20000+(rand()%9999);
  itoa(x,accno,10);

  cout<<"\nEnter your desired 4 digit PIN : ";
  cin>>password;

  cout<<"\nYour account number is : "; cprintf("%s",accno);
  cout<<"\nYour account name is : "; cprintf("%s",accname);
  cout<<"\nThe password entered will be your permanent password.";
  cout<<"\nYou can use this account to carry out your\ntransaction next time you log in!";

  ofstream acc_no,acc_name;
  acc_no.open("Accounts.txt",ios::app);
  acc_no<<accno<<endl;
  acc_no.close();

strcpy(acc_name_file,accno);
strcat(acc_name_file,"nm.txt");

  acc_name.open(acc_name_file);
  acc_name<<accname<<endl;
  acc_name.close();

pass_out();            //for password save
master_listout();      //for admin access
}

void account::master_listin()
{
  ifstream mastin;
  mastin.open("ADMIN.txt");
  mastin.getline(masterlist,80);
  if (strlen(masterlist)==0)
  {
    cout<<"No accounts registered yet...";
  }
  else
  {
    while(!mastin.eof())
     {
       cout<<masterlist<<endl;
       mastin.getline(masterlist,80);
     }
  }
  mastin.close();
}

void account::master_listout()
{
  strcpy(masterlist,accno);
  strcat(masterlist,"\t\t");
  strcat(masterlist,accname);

  ofstream  mastout;
  mastout.open("ADMIN.txt",ios::app);
  mastout<<masterlist<<endl;
  mastout.close();
}

void account::adminaccess()
{
  int mastercomm,mas_no_flag;
  char masaccno[10],checker2[10],namefile[20],namegetter[80],masaccloglist[25],dismasaccll[80];

  cout<<"What would you like to do Sir/Madam?\n";
  cout<<"Press 1 for account names and numbers\n"
      <<"Press 2 for Individual account history : ";
  cin>>mastercomm;

  switch(mastercomm)
   {
     case 1:
     cout<<"Acc.nos\t\tNames\n\n";
     master_listin();
     break;

     case 2:
     cout<<"Enter the account number you want to access : ";
     cin>>masaccno;  cout<<endl;

     ifstream checkmasaccno;
     checkmasaccno.open("Accounts.txt");
     checkmasaccno>>checker2;
     while(!checkmasaccno.eof())
      {
	mas_no_flag=strcmp(checker2,masaccno);

	 if(mas_no_flag==0)
	  {
	    strcpy(masaccloglist,masaccno);
	    strcat(masaccloglist,"ll.txt");

	    strcpy(namefile,masaccno);
	    strcat(namefile,"nm.txt");

	    ifstream mas_acc_ll,get_mas_name;
	    get_mas_name.open(namefile);
	    get_mas_name.getline(namegetter,80);
	    cout<<"Account name : "<<namegetter<<endl<<endl;
	    get_mas_name.close();

	    mas_acc_ll.open(masaccloglist);
	    mas_acc_ll.getline(dismasaccll,80);
	    if(strlen(dismasaccll)==0)
	    cout<<"No transaction history is found...";
	    while(!mas_acc_ll.eof())
	     {
	       cout<<dismasaccll<<endl;
	       mas_acc_ll.getline(dismasaccll,80);
	     }
	    mas_acc_ll.close();
	    return;
	  }
     checkmasaccno>>checker2;
     }

     cout<<"Entered account number was not found...reinitialsing...\n\n";
     adminaccess();
     break;

     default:
     cout<<"Entered parameter was incorrect , terminating this session...";
     delay(2000);
     exit(0);
   }
}