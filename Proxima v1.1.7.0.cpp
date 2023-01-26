//strcat stands for concatenate meaning to add strings.     'catenation'
#include<iostream.h>    //cin cout
#include<stdio.h>       //cprintf remove rename
#include<conio.h>       //getch clrscr textcolor
#include<stdlib.h>      //exit   itoa
#include<fstream.h>     // ifstream ofstream
#include<dos.h>	        // delay
#include<string.h>      //strcpy strlen strcat
#include<time.h>        //time_t

char accno[7];            //contains actual acc. no  ; used string cause this is used for names of the files.
char accname[80];         //contains actual name
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
char loan_log_file[20];

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
double amt;         //cause the derived class directly wanna use it
int inc_count;      //	""

public:
bank()
 {
   lt=0;
   amt=0;
   inc_count=0;
 }

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
     cout<<"Too many incorrect selections , session being terminated"; dots();
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
  timet[24]='\0';          //important

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
 outloglist<<timelog<<" -- "<<v<<" INR."<<endl<<endl;
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
   int accnoagain,asknew_acc,pcount,i,j,l;
   char password[10],disaccno[7],delaccno[7],dis_nn[80],del_nn[80]; //nn stands for number-name
   char nn_full[80],n_only[6];
  public:
   account()
   {
     ofstream accfile;         	 //just to create an accounts txt file,this stopped a bug where if i deleted the txt file externally , the program would not have worked
     accfile.open("Accounts.txt",ios::in);       //for some reason ios::out erases the file...ios in doesnt thats whyi have to use it in the constructor
     accfile.close();

     pcount=0;
   }

   void getaccno();
   void checkaccno();
   void asknewaccount();
   void pass_out();

   void create_newaccount();
   void get_name_list();
   void seperation();
   void rearrangement(char[],int,int,int);
   void compare();
   void error_message();

   void get_password();
   void out_create_time();
   void copy_cat();
   void generate_run();

   void master_listin();
   void master_listout();            //could have made 2 or 3 classes xP.
   void adminaccess();

   void check_if_disabled();
   void admin_delete_procedure();
   void admin_del_num();
   void admin_del_nn();
   void intro();
   void outro();
   void del_conf_message();
   void del_txt_files();
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
	 check_if_disabled();
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

 strcpy(loan_log_file,accno);
  strcat(loan_log_file,"lol.txt");      //lol stands for loan log.
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

  textcolor(14);
  cout<<"Enter your name : ";
  cin.ignore();        		//used to remove the "not asking for name , directly going to the next command" error
  cin.getline(accname,80);

  cout<<"\nThe system is checking for existance of previous accounts"; dots(); dots();
  get_name_list();

  cprintf("Generating your account number");
  dots(); dots();
  srand(time(NULL));

  x=20000+(rand()%9999);
  itoa(x,accno,10);       //super convenient.

  cout<<"\nEnter your desired ";
  cprintf("4 DIGIT"); cout<<" PIN : ";
  get_password();           //significantly reduced the size of this function

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

 acc_ll.open(accloglist);
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

void account::get_name_list()
{
   ifstream namelist;
   namelist.open("Admin.txt");
   namelist.getline(nn_full,80);
   if(strlen(nn_full)==0)
   {
      cout<<"No existing registered accounts receieved"; dots();
   }
   else
   {
      while(!namelist.eof())
      {
	 seperation();
	 compare();
	 namelist.getline(nn_full,80);
      }
   }
   namelist.close();
}

void account::seperation()
{
   l=strlen(nn_full);
   for(i=0;i<=l;i++)
   {
      if(nn_full[i]!=9)
      {
	n_only[i]=nn_full[i];
      }
      else
      {
	n_only[i]='\0';
	rearrangement(nn_full,i,i,l);
	break;
      }
   }
}

void account::rearrangement(char arr[],int iterator,int iterator1,int strlen)
{
  for(j=0;j<=(strlen-iterator);j++,iterator1++)
  {
     arr[j]=arr[iterator1+1];
  }
}

void account::compare()
{
   if(strcmp(accname,nn_full)==0)
   {
     error_message();
   }
}

void account::error_message()
{
  cout<<"Account with the name provided already exists!\n\nYou cannot have an another account for the same name!";
  cout<<"\n\nThat account is of number : ";
  textcolor(11);
  cprintf("%s",n_only);
  textcolor(15);
  cout<<"\nIf you wish to discontinue with the above account number ,"
  <<"\nyou can request for its deletion by going to the miscellaneous options\nfrom the menu page.";
  cout<<"\n\nWe will have to end this session"; dots(); dots();
  delay(2000);
  exit(0);
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
  strcat(masterlist,"\t");
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

     case 3:
     admin_delete_procedure();
     break;

     default:
     cout<<"Entered parameter was incorrect , terminating this session...";
     delay(2000);
     exit(0);
   }
}

void account::check_if_disabled()
{
   ifstream del_list;
   del_list.open("Adminno.txt");
   while(!del_list.eof())
   {
     del_list>>disaccno;                    //disaccno stands for disabled accno
     if(strcmp(accno,disaccno)==0)
     {
	cout<<"This account is disabled , no transactions can be carried out on it!\n";
	cout<<"\n\nExiting this session"; dots(); delay(5000);
	exit(0);
     }
   }
}

void account::admin_delete_procedure()
{
   intro();                          //ifstream for 2 files , ofstream for 2 files ,remove for 1 and rename for 2.

     ifstream admin1;
     admin1.open("Adminno.txt");
     while(!admin1.eof())
     {
       admin1>>delaccno;
       if(strlen(delaccno)!=0)
       {
	 admin_del_num();
       }
     }
     admin1.close();

     admin1.open("Admindel.txt");
     while(!admin1.eof())
     {
       admin1.getline(del_nn,80);
       if(strlen(del_nn)!=0)
       {
	 admin_del_nn();
       }
     }

   outro();
}

void account::admin_del_num()
{
   ifstream admin2;
   ofstream admin3;
   admin2.open("Accounts.txt");
   admin3.open("temp.txt");
   while(!admin2.eof())
   {
      admin2>>disaccno;
      if(strcmp(delaccno,disaccno)!=0)
      {
	 if(strlen(disaccno)!=0)              //this if statement prevents horrible consequences xP
	{
	  admin3<<disaccno<<endl;
	}
      }
   }
  admin2.close();
  admin3.close();

  remove("Accounts.txt");        //maybe put this in the loop--nah lol
  rename("temp.txt","Accounts.txt");

  del_txt_files();
  del_conf_message();
}

void account::del_txt_files()
{
   strcpy(accno,delaccno);
   copy_cat();

   remove(accamount);
   remove(acc_name_file);
   remove(pass_file);
   remove(acc_time);
   remove(acclastlog);
   remove(accloglist);
   remove(loan_log_file);
   remove(loan_amt_file);
   remove(loan_stat_file);
}

void account::del_conf_message()
{
     textcolor(14);
     cout<<"\nThe account of number "; cprintf("%s",delaccno);
     cout<<" has been successfully deleted.";
     textcolor(15);
}

void account::admin_del_nn()
{
  ifstream admin2;
  ofstream admin3;
  admin2.open("Admin.txt");
  admin3.open("temp1.txt");
  while(!admin2.eof())
  {
     admin2.getline(dis_nn,80);
     if(strcmp(del_nn,dis_nn)!=0)
     {
       if(strlen(dis_nn)!=0)
       {
	 admin3<<dis_nn<<endl;
       }
     }
  }
  admin2.close();
  admin3.close();

  remove("Admin.txt");
  rename("temp1.txt","Admin.txt");
}

void account::intro()
{
  cout<<"Initialising"; dots(); dots();
  cout<<"Fetching account numbers"; dots(); dots();
}

void account::outro()
{
  ofstream adm_file;
  adm_file.open("Admindel.txt",ios::trunc);
  adm_file.close();

  adm_file.open("Adminno.txt",ios::trunc);
  adm_file.close();
}

class loan : public account , public bank
{
  private:
  int loancheck,loanagain,statflag,statuscheck;
  double loanamt,limitamt,amtcarrier;
  char loantimee[30],loanlog[100],loan_type[20];
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
  void loan_history_out();
  void loan_history_in();
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
     <<"Press 5 for Business Loan.\n";
 cout<<"Option No : ";
 cin>>loancheck;

 switch(loancheck)
  {
    case 1:
    clrscr();
    cout<<"You have selected for Home loan...\n";
    limitamt=1000000;
    strcpy(loan_type," :-Home Loan");
    loanproced();
    break;

    case 2:
    clrscr();
    cout<<"You have selected for Vehicle loan...\n";
    limitamt=1000000;
    strcpy(loan_type," :-Vehicle Loan");
    loanproced();
    break;

    case 3:
    clrscr();
    cout<<"You have selected for Personal loan...\n";
    limitamt=100000;
    strcpy(loan_type," :-Personal Loan");
    loanproced();
    break;

    case 4:
    clrscr();
    cout<<"You have selected for Education loan...\n";
    limitamt=700000;
    strcpy(loan_type," :-Education Loan");
    loanproced();
    break;

    case 5:
    clrscr();
    cout<<"You have selected for Business loan...\n";
    limitamt=500000;
    strcpy(loan_type," :-Business Loan");
    loanproced();
    break;

    default:
    cout<<"The entered criteria was incorrect...\n"
	<<"Would you like to select again?\n"
	<<"(Press 1 for YES , 0 for NO) : ";
    cin>>loancheck;
    if(loancheck==1)
    {
      cout<<"\n\nProceeding"; dots();
      clrscr();
      loantype();
    }
    else if(loancheck==0)
    {
      cout<<"\n\nProceeding"; dots();
      exit(0);
    }
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
  int position;

  ifstream loan_pen_check;
  loan_pen_check.open(loan_amt_file,ios::out);     //check if opening amount file works--yes it does
  loan_pen_check>>flag1;
  position=(loan_pen_check.tellg());
  loan_pen_check.close();

  if(flag1==0||position==0)
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
   textcolor(11);
   cprintf("%s",loantimee);
   textcolor(15);
   statflag=0;
   loan_time_out();    //crucial
   loan_stat_out();    //crucial
   loan_history_out();
}

void loan::loan_history_out()
{
   time_t systemtime=time(NULL);
   strcpy(loantimee,ctime(&systemtime));
   loantimee[24]='\0';

    strcpy(loanlog,loantimee); 			//i couldnt use loanlog directly above since i had to remove the \n from it first.
     strcat(loanlog,loan_type);                 //strcat is smart enough to check for first null to replace...still we can change 25th char to something else if we wish.

   ofstream loanout;
   loanout.open(loan_log_file,ios::app);
   loanout<<loanlog<<"--"<<loanamt<<" INR."<<endl<<endl;
   loanout.close();                       //i may have to add loan hist check in misc options feature...cause here itself in loan its not fitting anywhere...
}

void loan::loan_history_in()
{
  ifstream loanloglist;
  loanloglist.open(loan_log_file);
  loanloglist.getline(loanlog,100);
  if(strlen(loanlog)==0)
  {
    cout<<"No loan history found\nFor loan history to appear here , you have to have a loan first!";
  }
  else
  {
    while(!loanloglist.eof())
    {
      cout<<loanlog<<endl;         //only one endl still causes a gap since the external file has 2nd line empty so this loop prints that here after the first endl. if you remove the endl here then that empty space is ignored and the 2nd log line is printed right after the first without new line.
      loanloglist.getline(loanlog,100);
    }
  }
  loanloglist.close();
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
  remove(loan_time_file);            //couldnt have set this to 0 , that would initiate due_time_check() [although i could write an if statement there to prevent this but i find this method more assuring cause then the program checks all the 3 necessary loan related files]
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

class mainpage : public loan        //might turn it protected loan--no need, dont
{
  private:
  int criteria,vericheck;
  char accholder[10];
  double lamthold;
  long int timecarrier,amthold;

  public:
  mainpage()
  {
    ofstream fout;
    fout.open("Admindel.txt",ios::in);
    fout.close();

    fout.open("Adminno.txt",ios::in);
    fout.close();
  }

  void mainlist();
  void misc_options();
  void return_back();
  int  verify_accno();
  void is_verified();
  int  get_loan_time();
  void show_loan_time();
  void request_deletion();
  int is_amount_zero();
  int is_loan_repaid();
};

void mainpage::mainlist()
{
 textcolor(13);
 cprintf("Greetings!"); cout<<endl;

 textcolor(11);
 cprintf("What would you like to carry out?"); cout<<endl<<endl;

 textcolor(15);

 cout<<"Press 1 for a Transaction.\n"
     <<"Press 2 for creating a new account.\n"
     <<"Press 3 to view our Loan schemes.\n"
     <<"Press 4 to repay your pending loan.\n"
     <<"Press 5 to access account miscellaneous functions.\n"
     <<"Press 0 to exit.\n\n"
     <<"Option No : ";
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

   case 5:
   cout<<"Proceeding"; dots();
   clrscr();
   getaccno();
   vericheck=verify_accno();
   is_verified();
   copy_cat();
   pass_in();
   misc_options();
   break;

   case 0:
   cout<<"\n\nOkay...exiting"; dots();
   delay(2000);
   exit(0);
   break;

   default:
   cout<<"Incorrect selection, terminating this session";
   dots();
   exit(0);
 }
}

int mainpage::verify_accno()
{
   ifstream accin;
   accin.open("Accounts.txt");
   while(!accin.eof())
   {
     accin>>accholder;
     if(strcmp(accno,accholder)==0)
     {
       return 1;
     }
   }
   accin.close();
   return 0;
}

void mainpage::is_verified()
{
   if(vericheck==1)  // you can also remove verify_accno from the switch above and directly put it in here...
   {                 //the program executes it here and according to the return value executes if statement
     textcolor(10);  //i may have an example shown down in is_amount zero()
     cprintf("Entered account is registered!"); cout<<endl<<endl;
     textcolor(15);
   }
   else
   {
     textcolor(12);
     cprintf("Entered account is not registered...");
     inc_count++;
     inc_check_count();
     cout<<"\nWould you like to try again? : ";
     cin>>criteria;
     if(criteria==1)
     {
       getaccno();
       vericheck=verify_accno();
       is_verified();
     }
     else if(criteria==0)
     {
       cout<<"\n\nReturning to mainpage"; dots();
       clrscr();
       mainlist();
     }
     else
     {
       cout<<"\n\nIncorrect parameter forwarded...terminating this session"; dots();
       delay(2000);
       exit(0);
     }
   }
}

void mainpage::misc_options()
{
  clrscr();

  gotoxy(30,1);
  textcolor(10);
  cprintf("MISCELLANEOUS OPTIONS"); cout<<"\n\n";

  textcolor(11);
  cprintf("Press the corresponding key to carry out the desired function."); cout<<endl;
  textcolor(15);
  cout<<"1.View current available balance.\n"
      <<"2.Check if any loan is pending.\n"
      <<"3.View transaction history.\n"
      <<"4.Clear transaction history.\n"
      <<"5.View loan history.\n"
      <<"6.Clear loan history.\n"
      <<"7.To request deletion of your account.\n"
      <<"0. Return to main page.";
  cout<<"\n\nOption No.: ";
  cin>>criteria;

  switch(criteria)
  {
     case 1:
     in_amount();
     in_curr_time();
     textcolor(10);
     cprintf("Current Available Balance : ");
     textcolor(15);
     round(amt); cout<<" INR.\n\n";
     out_amount();
     return_back();
     break;

     case 2:
     cout<<"\nProceeding"; dots();
     int p=get_loan_time();
     if(p==1)
     {
       show_loan_time();
     }
     return_back();
     break;

     case 3:
     clrscr();
     in_loglist();
     cout<<"\nPress any key to continue...";
     getch();
     return_back();
     break;

     case 4:
     cout<<"Proceeding"; dots();
     ofstream outll;
     outll.open(accloglist,ios::trunc);
     outll.close();
     cout<<"History successfully deleted!\n\n";
     return_back();
     break;

     case 5:
     cout<<"Proceeding"; dots();
     clrscr();
     loan_history_in();
     cout<<"\nPress any key to continue...";
     getch();
     return_back();
     break;

     case 6:
     cout<<"Proceeding"; dots();
     ofstream outlol;
     outlol.open(loan_log_file,ios::trunc);
     outlol.close();
     cout<<"History successfully deleted!\nPress any key to continue...";
     getch();
     clrscr();
     cout<<"\n";
     return_back();
     break;

     case 7:
     clrscr();
     cout<<"You are about to request deletion of your account...\nIt is advised to first check and empty your account \nto prevent rejection of your account's deletion.\n\n";
     request_deletion();
     return_back();
     break;

     case 0:
     cout<<"You have chosen to return to the main page";
     cout<<"\nProceeding"; dots();
     clrscr();
     mainlist();
     break;

     default:
     cout<<"The entered parameter was incorrect...exiting"; dots();
     delay(2000);
     exit(0);
     break;
  }
}

void mainpage::return_back()
{
   cout<<"\nWould you like to carry out another function?\n(Press 1 for YES or 0 for NO) : ";
   cin>>criteria;
   if(criteria==1)
   {
      cout<<"Proceeding"; dots();
      misc_options();
   }
   else if(criteria==0)
   {
      cout<<"OK...would you like to return to the main page? : ";
      cin>>criteria;
      if(criteria==1)
      {
	cout<<"Proceeding"; dots();
	clrscr();
	mainlist();
      }
      else if(criteria==0)
      {
	cout<<"OK...ending this session"; dots();    cout<<endl;
	clrscr();
	textcolor(11);
	gotoxy(20,11);
	cprintf("Thank you for visiting Proxima Bank!"); cout<<endl;
	gotoxy(25,12);
	textcolor(14);
	cprintf("We wish to see you soon! :-D"); cout<<endl;
	textcolor(15);
	delay(2750);
	exit(0);
      }
   }
   else
   {
      cout<<"Incorrect selection...terminating this session"; dots();
      exit(0);
   }
}

int mainpage::get_loan_time()
{
  ifstream time_in;
  time_in.open(loan_time_file,ios::nocreate);
  if(time_in.fail())
  {
    cout<<"No loan currently pending...";
    time_in.close();
    return 0;
  }
  else
  {
    time_in>>timecarrier;
    time_in.close();
    return 1;
  }
}

void mainpage::show_loan_time()
{
  cout<<"Your loan due date is : ";
  textcolor(11);
  cprintf("%s",ctime(&timecarrier));   cout<<endl;
  textcolor(15);

  time_t systemtime=time(NULL);
  if(systemtime>=timecarrier)
  {
     textcolor(12);
     cprintf("Loan due time expired!");   cout<<endl;
     textcolor(15);
  }
  else
  {
    textcolor(10);
    cprintf("Loan due time not yet expired."); cout<<endl;
    textcolor(15);
  }
}

void mainpage::request_deletion()
{
     ifstream getname;
     getname.open(acc_name_file);
     getname.getline(accname,80);
     getname.close();

     cout<<"The account of number "<<accno<<" will be deleted permanently , \nplease confirm request submission : ";
     cin>>criteria;

     if(criteria==1&&is_amount_zero()==1&&is_loan_repaid()==1)
     {
       cout<<"\nConfirmation submitted"; dots();
       cout<<"Effective immediately this account is disabled ;\nno further transactions will be entertained for this account.\n";
       cout<<"Proceeding"; dots();
       ofstream delfile;
       delfile.open("Admindel.txt",ios::app);
       delfile<<accno<<"\t"<<accname<<endl;
       delfile.close();

       delfile.open("Adminno.txt",ios::app);
       delfile<<accno<<endl;
       delfile.close();

       cout<<"Request sent successfully! This account will be deleted by our admin.\n\n";
     }
     else if(is_amount_zero()==0&&is_loan_repaid()==0)          //does it again execute this function? [Most probably it does...so...maybe i should have used an int here =O]
     {
       cout<<"Your account's current balance is non-zero...\nYou also have a loan repayment pending...\nWe cannot send the request for it to be deleted"; dots();
       return_back();
     }
     else if(is_amount_zero()==1&&is_loan_repaid()==0)
     {
       cout<<"You have a loan repayment pending...\nWe cannot submit your confirmation till it's repaid.\n";
       return_back();
     }
     else if(is_amount_zero()==0&&is_loan_repaid()==1)
     {
       cout<<"Your account's current balance is non-zero...\nWe cannot submit your request till you account balance is 0.00 INR.\n";
       return_back();
     }
     else if(criteria==0)
     {
       cout<<"Action not confirmed , suspending this process"; dots();
       delay(2500);
       exit(0);
     }

     else
     {
       cout<<"\nIncorrect criterion submitted"; dots();
       return_back();
     }
}

int mainpage::is_amount_zero()
{
    ifstream amount_in;
    amount_in.open(accamount);					//  FILE*ptr=fopen(accamount,"f");	//  fscanf(ptr,"%.2f",&amthold);       //if something like this would work then that would be great
    amount_in>>amthold;            //otherwise i have to make amthold a long int or make a special clear amount function in class bank.
    amount_in.close();

  if(amthold!=0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int mainpage::is_loan_repaid()
{
  int popointer;

  ifstream loanin;
  loanin.open(loan_amt_file,ios::out);
  loanin>>lamthold;
  popointer=(loanin.tellg());
  loanin.close();

  if(lamthold==0||popointer==0)     //popointer is position_pointer...
  {				   //it is used to tell the prog that the account has not taken a loan ever and this condtion should pass as no loan pending  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void rules()
{
  clrscr();
 textcolor(12);
  cout<<"\t\t\t\t";
  cprintf("WELCOME TO PROXIMA."); cout<<endl<<endl;
 textcolor(11);
  cprintf("To make your transaction smoother, please follow the instructions listed below :");cout<<endl;
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

			       void main()
			       {
				  clrscr();
				  rules();
				  mainpage m;
				  m.mainlist();
				  getch();
			       }

//why is it saying that mainlist not a member of mainpage??? --resolved
//i maybe should have/could have used inheritance, make a seperate class loan which is derived from account and maybe even bank  --resolved
//things to be added : rounding amount ,   --done
//loan log ,   -- done
//logs should also show amount   --done
//miscellaneous account options ,    --done , 7 of them rn! + additonal safety features
//remove particular account(s) (for admin) ,     --done!     [was challenging]
//no two accounts for a same name ,    --done!
//give one more loan due date for the needy xP ,
//exempt all the procedures till loan is not repaid.