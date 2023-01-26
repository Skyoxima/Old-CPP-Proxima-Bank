//strcat stands for concatenate meaning to add strings.     'catenation'
#include<iostream.h>    //cin cout
#include<stdio.h>       //cprintf remove rename
#include<conio.h>       //getch clrscr textcolor
#include<stdlib.h>      //exit
#include<fstream.h>     // ifstream ofstream
#include<dos.h>	        // delay
#include<string.h>      //strcpy strlen strcat
#include<time.h>        //time_t

char accno[7];            //contains actual acc. no
char accname[40];         //contains actual name
char pass_file[20];      //contains the name of the password file,i.e accno+pas.txt
char acc_name_file[20]; //contains name of files used in ifstream and ofstream
char acc_time[20];
char acclastlog[20];   //  "
char accloglist[20];  //   "
char accamount[20];  //    "
char masterlist[80]; //contains total history for adminaccess
char loan_amt_file[20];  //contains file name which has the loan amount in it
char loan_time_file[20];     //contains the name of the file containing due date for a loan.
char loan_stat_file[20];   //""        ""   "" ""  "" ""       ""      status of a loan.

class account;
class deporwit;
class loan;
class mainpage;

void askagain();
void endgreet();
void rules();
void dots();

class bank
{
private:
double v;
int lt,passcheck;
char password[10],filepassword[10];
long int gettime,transactime;

protected:
double amt;

public:
bank()
 {
   lt=0;
   amt=0;
   inc_count=0;
 }
int inc_count;

void display();
void in_amount();
void out_amount();
void in_curr_time();
void out_curr_time();
void getValue();
void round(double);
void pass_in();
void inc_check_count();
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

void bank::in_curr_time()
{
  time_t systime=time(NULL);

  transactime=systime;

  ifstream intime;
  intime.open(acc_time);
  intime>>gettime;

  if((systime-gettime)>=60)   //interest added in 60 seconds xD
  {
    if(amt>0)    	     //to prevent adding interest on negative amount
    {                       //i could have used && in the first if too...but meh...
       amt=amt+amt*0.01;
       out_curr_time();
    }
  }
}

void bank::out_curr_time()
{
  ofstream outtime;
  outtime.open(acc_time,ios::trunc);
  outtime<<transactime;
  outtime.close();
}

void bank::getValue()
{
  cout<<"Now enter the amount to be transacted : ";
  cin>>v;
  if(v<0)
  {
    textcolor(RED);
    cprintf("Negative number entered...please enter a positive amount!"); cout<<endl<<endl;
    inc_count++;
    inc_check_count();
    getValue();                            //such functions in which the function is calling itself are called recursive functions...I have used many such functions in the program
  }
}

void bank::inc_check_count()
{
    if(inc_count==5)
    {
     cout<<"Too many incorrect selections , transaction being terminated"; dots();
     delay(500);
     exit(0);
    }
    else
    {
      return;
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
    inc_count++;
    inc_check_count();     //incorrect check count
    pass_in();
  }
  else
  {
    textcolor(10);
    cout<<"\n";
    cprintf("Access Granted!"); cout<<endl;
    textcolor(15);
  }
}

void bank::transac(deporwit d)    //since transaction is the friend of deporwit , we need to pass deporwit's object to it.
{                                 //as friend functions are not the member of the class , they cant directly access the data , they can through an object
 if(d.dw==1)                      //i didnt know inheritance here
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

void bank::round(double carrier)
{
  printf("%.2f",carrier);
}

void bank::display()
{
  textcolor(10);
  cprintf("Current available balance : ");
  round(amt); cout<<" INR.\n";

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
   int accnoagain,asknew_acc,pcount;
   char password[10];

  public:
   account()
   {
     ofstream accfile;          //just to create an accounts txt file,,this stopped a bug where if i deleted the txt file externally , the program would not have worked
     accfile.open("Accounts.txt",ios::in);
     accfile.close();

     pcount=0;
   }

   void getaccno();
   void checkaccno();
   void asknewaccount();
   void pass_out();
   void create_newaccount();
   void get_password();
   void out_create_time();
   void copy_cat();
   void generate_run();
   void master_listin();
   void master_listout();
   void adminaccess();
};

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

cout<<"The entered account number is not recorded in our current database...\n";
cout<<"\n1.To try again, press 1\n2.To create a new account, press 2\n3.To exit , press 0 : ";
cin>>accnoagain;

if(accnoagain==1)
 {
   clrscr();
   getaccno();
   checkaccno();
 }
else if(accnoagain==0)
 {
   cout<<"Exiting...";
   delay(3000);
   exit(0);
 }
else if(accnoagain==2)
 {
   clrscr();
   asknewaccount();
 }
else
 {
   cout<<"Incorrect parameter entered , ending this session...";
   delay(1500);
   exit(0);
 }
}

void account::generate_run()
{
 ifstream getname;
 getname.open(acc_name_file);
 getname.getline(accname,40);
 if(strlen(accname)==0)
 {
   strcpy(accname,"NONAME");
 }
 getname.close();

 cout<<"\n\t\t\t\tWelcome!"<<" "<<accname<<"\n\n";

 int histcheck,checkbal;
 bank b;
 deporwit d1;

 b.in_amount();
 b.in_log();
 b.in_curr_time();
 b.out_amount();

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
     cout<<"Incorrect criterion passed...this session will be terminated.";
     delay(2000);
     exit(0);
    }

  cout<<"Would you like to check your current balance and last transaction? : ";
  cin>>checkbal;  cout<<endl<<endl;

  switch(checkbal)
  {
    case 0:
    cout<<"Proceeding with the current session...";
    delay(1000);
    clrscr();
    break;

    case 1:
    b.display();
    break;

    default:
    cout<<"The entered parameter was incorrect, please try again...\n\n";
    generate_run();
  }

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


void rules()
{
  clrscr();
 textcolor(12);
  cout<<"\t\t\t\t";
  cprintf("WELCOME TO PROXIMA."); cout<<endl<<endl;
 textcolor(11);
  cprintf("To make you transaction smoother, please follow the instructions listed below :");cout<<endl;
 textcolor(15);
  cprintf("1. When prompted, press 1 to log-in into an account, 2 to create an account."); cout<<endl<<endl;
  cprintf("2. When prompted, please press 1 for DEPOSITION or 2 for WITHDRAWAL."); cout<<endl<<endl;
  cprintf("3. When prompted for confirmation, please press 0 for NO or 1 for YES."); cout<<endl<<endl;
  cprintf("4. When prompted for a new transaction, press 1 for YES, 0 for NO."); cout<<endl<<endl;
  cprintf("5. When prompted for transaction history, press 1 for YES, 0 for NO."); cout<<endl<<endl;
  cprintf("6. When prompted for amount, do not put negative values!"); cout<<endl<<endl;
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

   case 1:           //since its re-initialising an object , all the class related variables will be restted but not the global strings which contain the name and number...so it will still show the same name which is what is needed!
   cout<<"Proceeding...\n";
   delay(1000);
   textcolor(15);
   clrscr();
   account a1;
   a1.generate_run();
   break;             //rule check solved!

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

 strcpy(acc_name_file,accno);
  strcat(acc_name_file,"nm.txt");

 strcpy(pass_file,accno);
  strcat(pass_file,"pas.txt");

 strcpy(acc_time,accno);
  strcat(acc_time,"tim.txt");

 strcpy(loan_amt_file,accno);
  strcat(loan_amt_file,"la.txt");        //la stands for loan amount.

 strcpy(loan_time_file,accno);
  strcat(loan_time_file,"lt.txt");      //lt stands for loan time.

 strcpy(loan_stat_file,accno);
 strcat(loan_stat_file,"ls.txt");       //ls stands for loan status.
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

void account::out_create_time()
{
 strcpy(acc_time,accno);
 strcat(acc_time,"tim.txt");

 time_t createtime=time(NULL);

 ofstream outtime;
 outtime.open(acc_time);
 outtime<<createtime;
 outtime.close();
}

void account::get_password()
{
  cin>>password;
    if(strlen(password)!=4)
     {
       pcount++;

       if(pcount==5)
	{
	  cout<<"Too many incorrect attempts...aborting the procedure...";
	  delay(5000);
	  exit(0);
	}
       else
	{
	  cout<<"Password length is inadequate...try again... \n"
	      <<"Enter your desired 4 digit PIN ";
	  get_password();
	}
     }
   else
    {
      return;
    }
}

void account::create_newaccount()
{
  int x=0;

  textcolor(9);
  cout<<"Enter your name : ";
  cin.ignore();        //used to remove the "not asking for name , directly going to the next command" error
  cin.getline(accname,40);

  cprintf("Generating your account number...");
  delay(4000);
  srand(time(NULL));

  x=20000+(rand()%9999);
  itoa(x,accno,10);       //super convenient.

  cout<<"\nEnter your desired ";
  cprintf("4 DIGIT"); cout<<" PIN : ";
  cin>>password;

    if(strlen(password)!=4)
     {
       pcount++;

       if(pcount==5)
	{
	  cout<<"Too many incorrect attempts...aborting the procedure...";
	  delay(5000);
	  exit(0);
	}
       else
	{
	  cout<<"Password length is inadequate...try again... \n"
	      <<"Enter your desired 4 digit PIN ";
	  get_password();
	}
     }

  ofstream acc_no,acc_name,acc_ll;
  acc_no.open("Accounts.txt",ios::app);
  acc_no<<accno<<endl;
  acc_no.close();

strcpy(acc_name_file,accno);
strcat(acc_name_file,"nm.txt");

  acc_name.open(acc_name_file);
  acc_name<<accname<<endl;
  acc_name.close();

strcpy(accloglist,accno);
strcat(accloglist,"ll.txt");

 acc_ll.open(accloglist,ios::in);
 acc_ll.close();

pass_out();            //for password save
master_listout();      //for admin access
out_create_time();     //saves creation time, used for interest

    cout<<"\nYour account number is : "; cprintf("%s",accno);
    cout<<"\nYour account name is : "; cprintf("%s",accname);
    cout<<"\nPress any key to continue for a transaction...";
    getch();
    textcolor(15);
    clrscr();
    getaccno();
    checkaccno();
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
  char masaccno[10],checker2[10],namefile[20],namegetter[80],masaccloglist[25],dismasaccll[80],adminID[6];

  cout<<"What would you like to do Sir/Madam?\n";
  cout<<"Press 1 for account names and numbers\n"
      <<"Press 2 for Individual account history\n"
      <<"Press 3 for Account removal : ";       //account removal still in beta
  cin>>mastercomm;

  switch(mastercomm)
   {
     case 1:
     cout<<"\n\nAcc.nos\t\tNames\n\n";
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
	    mas_acc_ll.getline(dismasaccll,80);     //important to check whether the file is empty or modified.
	    if(strlen(dismasaccll)==0)
	    {
	      cout<<"No transaction history is found...";
	    }
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

     cout<<"Entered account number was not found...reinitialising...\n\n";
     adminaccess();
     break;

     default:
     cout<<"Entered parameter was incorrect , terminating this session...";
     delay(2000);
     exit(0);
   }
}

class loan : public account , protected bank
{
  private:
  int loancheck,loanagain,statflag,statuscheck;
  double loanamt,limitamt,amtcarrier;
  char loantimee[40];
  long int loantimeee;
  public:

  loan()
  {
     loanamt=0;
  }

  void loantype();
  void loanproced();
  void loanfetch();
  void loanmech();
  void loan_amt_out();
  void loan_time_out();
  void loan_stat_out();
  void due_time_check();
  void loanstatcheck();
  void allow_or_deny();
  void repayment();
  void loan_amt_in();
  void no_sec_loan();
};

void loan::loantype()
{
gotoxy(30,1);

 textcolor(13);
 cprintf("Welcome to our Loan Page!");
 textcolor(15);
 cout<<"\nWhich loan service would you like to avail?\n\n"
     <<"Press 1 for Home Loan.\n"
     <<"Press 2 for Vehicle Loan.\n"
     <<"Press 3 for Personal Loan.\n"
     <<"Press 4 for Education Loan.\n"
     <<"Press 5 for Gold Loan.\n";
 cin>>loancheck;

 switch(loancheck)
  {
    case 1:
    clrscr();
    cout<<"You have selected for Home loan...\n";
    limitamt=1000000;
    loanproced();
    break;

    case 2:
    clrscr();
    cout<<"You have selected for Vehicle loan...\n";
    limitamt=1000000;
    loanproced();
    break;

    case 3:
    clrscr();
    cout<<"You have selected for Personal loan...\n";
    limitamt=100000;
    loanproced();
    break;

    case 4:
    clrscr();
    cout<<"You have selected for Education loan...\n";
    limitamt=700000;
    loanproced();
    break;

    case 5:
    clrscr();
    cout<<"You have selected for Business loan...\n";
    limitamt=500000;
    loanproced();
    break;
  }
}

void loan::loanproced()       //loanproced stands for loan procedure
{
  cout<<"Please specify the amount (Max limit "<<limitamt<<") : ";
  cin>>loanamt;
  if(loanamt<0)
  {
     textcolor(4);
     cprintf("Negative value not accepted...");
     textcolor(15);
     cout<<"try again...";
     inc_count++;
     inc_check_count();
     loanproced();
  }

  if(loanamt>limitamt)
   {
     loanamt=limitamt;
   }

  cout<<"The amount requested is : "<<loanamt<<" INR."<<endl<<endl;
  loanfetch();
}             //cant loan_amt_out here

void loan::loanfetch()
{
  char checker[6];

  textcolor(10);
  cprintf("Please follow the instructions for a smooth procedure.");    cout<<endl;

  textcolor(15);
  cout<<"Please enter your valid/registered account number : ";

  cin>>accno;

  cout<<"\nThe system will fetch your details , please wait"; dots();
  copy_cat();        //very important

  ifstream loanstuff;                   //add checking if the account exists ---done
  loanstuff.open("Accounts.txt");

  while(!loanstuff.eof())
  {
    loanstuff>>checker;

    if(strcmp(checker,accno)==0)
    {
      textcolor(10);
      cprintf("The entered account number is registered!"); cout<<endl;
      no_sec_loan();			    //here i may add to check if the no. is "valid" or not (in debt or not)--added to the function no_sec_loan itself..loanstatcheck does this work
      loanmech();
      return;
    }
  }
  loanstuff.close();

  cout<<"The entered account number is not registered.\n"
      <<"Would you like to try again? : ";
  cin>>loanagain; cout<<"\n";

  inc_count++;             	//you gotta make another switch/if else here--no need , used class bank's function and inc_count
  inc_check_count();

  switch(loanagain)
  {
     case 0:
     cout<<"Okay...aborting the procedure"; dots();
     exit(0);
     break;

     case 1:
     cout<<"Proceeding"; dots();
     clrscr();
     loanfetch();
     break;
  }
}

void loan::no_sec_loan()
{
  double flag1;

  ifstream loan_pen_check;
  loan_pen_check.open(loan_amt_file,ios::nocreate);     //check if opening amount file works
  loan_pen_check>>flag1;
  loan_pen_check.close();

  if(flag1==0)
  {
     cout<<"\nNo loan currently pending.\n";
  }
  else
  {
     textcolor(12);
     cout<<endl;
     cprintf("You have a loan pending...you cannot ask for another loan , ");
     cout<<endl;
     cprintf("till the first one is cleared."); cout<<"\n";
     textcolor(15);
     loanstatcheck();       //loanstatcheck and due time check are not getting used yet...you have to use them in transaction.
  }
}


void loan::loanstatcheck()
{
   due_time_check();                  			//super crucial

   int repay;

   ifstream loanstat_in;
   loanstat_in.open(loan_stat_file);
   loanstat_in>>statuscheck;
   loanstat_in.close();

   if(statuscheck==1)
   {
      allow_or_deny();
   }
   else
   {
      cout<<"Loan due date not yet expired."; dots();
      cout<<"Would you like to repay the loan? : ";
      cin>>repay;

      if(repay==1)
      {
	 repayment();
      }
      else
      {
	ifstream duetime;
	duetime.open(loan_time_file,ios::nocreate);
	if(duetime.fail())
	{
	   cout<<"The loan has already been repaid.\n";
	   cout<<"Press any key to exit...";
	   getch();
	   exit(0);
	}
	else
	{
	   duetime>>loantimeee;
	   cout<<"\nYour loan can be repaid by the date : "<<ctime(&loantimeee)<<"\n";
	   cout<<"Press any key to exit this session...";
	   getch();
	   exit(0);
	}
       duetime.close();
      }
   }
}

void loan::allow_or_deny()
{
   int paymcheck;
   cout<<"\nYour loan repayment is due.\n";
   cout<<"Without the repayment all transactions will be halted permanently.\n";
   cout<<"Would you like to repay your loan now? : ";
   cin>>paymcheck;    //paymcheck stands for payment check

   switch(paymcheck)
   {
     case 0:
     cout<<"\nAs mentioned , you will be exempted from making any transactions \ntill the loan is repaid...";
     cout<<"\n\nTo repay the loan , you can also access the repayment page from the main menu.";
     cout<<"\n\n Press any key to exit...";
     getch();
     exit(0);
     break;

     case 1:
     repayment();
     break;

     default:
     cout<<"Incorrect selection , terminating the transaction";dots();
     exit(0);
     break;
   }
}

void loan::due_time_check()
{
  ifstream debtortime;
  debtortime.open(loan_time_file,ios::nocreate);
  if(debtortime.fail())
  {
     statflag=0;
     loan_stat_out();
  }
 else
 {
     time_t systemtime=time(NULL);
     debtortime>>loantimeee;
     if(loantimeee<systemtime)
     {
	statflag=1;
	loan_stat_out();
     }
     else
     {
	statflag=0;
	loan_stat_out();
     }
 }
 debtortime.close();
}

void loan::loanmech()
{
   textcolor(15);
   char name[80];

   ifstream debtor;
   debtor.open(acc_name_file);
   debtor.getline(name,80);
   cout<<"\nName : "<<name<<".\n\n";
   debtor.close();

   debtor.open(accamount);
   debtor>>amt;
   debtor.close();

   in_curr_time();     //for interest
   out_amount();
   cout<<"Fetching current balance amount"; dots();
   pass_in();    	   				       //adds asking password for much better security.(function pass_in() of class bank is reusable due to multilevel inheritence)
   cout<<"Current available balance : "; round(amt); cout<<" INR.\n\n";
   cout<<"The requested amount will be added to your account";  dots();

   amt=amt+loanamt;

   cout<<"Amount added successfully!\n";
   textcolor(10);
   cprintf("Current available balance : ");
   round(amt);
   cout<<" INR.\n";
   textcolor(15);

   out_amount();
   loan_amt_out();         //crucial

   time_t systemtime=time(NULL);
   loantimeee=(systemtime + 86400);
   strcpy(loantimee,ctime(&loantimeee));

   cout<<"The repayment of the loan is due : ";							//problem! if only loan is asked , the interested amount is not recorded hence not shown too, solve this before heading further. --resolved
   textcolor(4);
   cprintf("%s",loantimee);
   textcolor(15);
   statflag=0;
   loan_time_out();    //crucial
   loan_stat_out();    //crucial
}

void loan::loan_time_out()
{
  ofstream debtortime;
  debtortime.open(loan_time_file,ios::trunc);
  debtortime<<loantimeee; 		      //its sending the due date only
  debtortime.close();
}

void loan::loan_stat_out()
{
  ofstream debtorstat;
  debtorstat.open(loan_stat_file);
  debtorstat<<statflag;
  debtorstat.close();
}

void loan::loan_amt_out()
{
  ofstream amountout;
  amountout.open(loan_amt_file);
  amountout<<loanamt;
  amountout.close();
}

void loan::repayment()
{
  clrscr();
  gotoxy(30,1);
  textcolor(12);
  cprintf("Loan Repayment Page");
  textcolor(15);

  in_amount();
  textcolor(10);
  cout<<"\n\n\n";
  cprintf("Current available balance : ");
  textcolor(15);  round(amt); cout<<" INR.\n";

  loan_amt_in();
  cout<<"Your current pending loan amount : "<<amtcarrier<<" INR.\n";
  cout<<"This amount will be deducted from your account.\n";
  cout<<"\nPress any key to continue...\n";
  getch();

  amt=amt-amtcarrier;
  out_amount();

  statflag=0;
  loan_stat_out();
  remove(loan_time_file);            //couldnt have set this to 0 , that would initiate due_time_check()[although i could write an if statement there to prevent this but i find this method more assuring cause then the program checks all the 3 necessary loan related files]
  loanamt=0;
  loan_amt_out();				//crucial...prevents multiple loan repayment

  textcolor(10);
  cout<<"\n";
  cprintf("Current available balance : "); round(amt); cout<<" INR.";
  textcolor(15);

  if(amt<0)
  {
     cout<<"\n\nYour current balance is negative...\n\nThis means that your next deposition will be automatically used to \nclear the debt.\n";
  }

  cout<<"\n\nPress any key to exit... ";
  getch();
  delay(200);
  exit(0);
}

void loan::loan_amt_in()
{    	                            				 // very big problem...the lockdown after due date works
  ifstream amountin;              				 // but i can take another loan and bypass the previous amount which completely wrecks the purpose
  amountin.open(loan_amt_file);   			         // moreover the amount get replaced instead of adding up!   --solved...you can only have one pending loan at a given time.
  amountin>>amtcarrier;
  amountin.close();
}


void dots()
{
  delay(750); cout<<"."; delay(750); cout<<"."; delay(750); cout<<".\n";
}

class mainpage : public loan        //might turn it protected loan
{
  private:
  int criteria;

  public:
  void mainlist();
};


void mainpage::mainlist()
{
 textcolor(13);
 cprintf("Greetings!"); cout<<endl;

 textcolor(11);
 cprintf("What would you like to carry out today?"); cout<<endl<<endl;

 textcolor(15);

 cout<<"Press 1 for a Transaction.\n"
     <<"Press 2 for creating a new account.\n"
     <<"Press 3 to view our Loan schemes.\n"
     <<"Press 4 to repay your pending loan.\n\n";
 cin>>criteria;

 textcolor(15);              //the last color which goes to main decides the color for the cout statements..thats why i added it here

 switch(criteria)
 {
   case 1:
   cout<<"\t\tProceeding";
   dots();
   clrscr();
   getaccno();
   checkaccno();
   break;

   case 2:
   cout<<"\t\tProceeding";
   dots();
   clrscr();
   asknewaccount();
   break;

   case 3:
   cout<<"\t\tProceeding";
   dots();
   clrscr();
   loantype();            //it inherited class loan  , so no need to create loan's object
   break;

   case 4:
   cout<<"\t\tProceeding"; dots();
   clrscr();
   getaccno();
   copy_cat();
   no_sec_loan();
   break;

   default:
   cout<<"Incorrect selection, terminating the transaction";
   dots();
   exit(0);
 }
}

			       void main()
			       {
				  clrscr();
				  rules();
				  mainpage m;
				  m.mainlist();
				  getch();
			       }

//why the hell is it saying that mainlist not a member of mainpage??? --resolved
//i maybe should have/could have used inheritance, make a seperate class loan which is derived from account and maybe even bank  --resolved
//things to be added : rounding amount ,   --done
//loan log ,
//miscellaneous account options ,
//remove particular account (for admin) ,
//no two accounts for a same name ,
//give one more loan due date for the needy xP ,
//exempt all the procedures till loan is not repaid.