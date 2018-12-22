#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sstream>
#include <fstream>

using namespace std;

void menu();
string Search(string, int);
void replace_elem(string);

int written = 0;

//Function to convert Upper to lower case
string tolower(string str){
  for(int i=0;i<str.length();i++){
    str[i]=tolower(str[i]);
  }
  return str;
}

//function to convert string to int
int stoi(string num){
  stringstream geek(num);
  int x = 0;
  geek >> x;
  return x;
}

//function to convert int to string
string itos(int num){
  ostringstream str1;
  str1 << num;
  string geek = str1.str();
  return geek;
}

//Function to clear Screen
void clrscr()
{
   system("cls");
}

//Function to delay
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

//Function to print formated heading
void printh(string heading){
  cout<<"\[-] "<<heading<<"  >>"<<"\n\n";
}

//Function to print formated data
void printd(string data, int index = 0){
  if(!index){
    cout<<" - "<<data<<" : ";
  }
  else{
    cout<<" - "<<data<<" "<<index<<" : ";
  }
}

void printd2(string data, string value){
  cout<<" - "<<data<<" ("<<value<<") : ";
}

void printd2(string data, int value){
  cout<<" - "<<data<<" ("<<value<<") : ";
}

//Function to print formated sub-heading
void printsh(string subHeading){
  cout<<"\n[~] "<<subHeading<<"\n";
}

//Function to print message in box
void printm(string message){
  cout<<"\n";
  int message_length = message.length();
  for(int i=0;i<message_length + 4;i++){
    cout<<"-";
  }
  cout<<"\n| "<<message<<" |\n";
  for(int i=0;i<message_length + 4;i++){
    cout<<"-";
  }
  cout<<"\n\n";
}

//function to print option
void printo(int index, string option){
  cout<<"["<<index<<"] "<<option<<"\t\t";
  if(index && index%3==0){
    cout<<"\n";
  }
}

//function to abort
void abort(){
  printm("Thanks for using our application. The app will abort shortly in 2s");
  delay(2000);
  exit(0);
}

//Structure for individual element
struct element {
  string name;
  float mass;
  int atomic_no;
  int no_of_iso;
  int isotopes[10];
  int no_of_isb;
  int isobars[10];
};

//Class for all elements
class elements {
public :

  element e;
  int total = 0;

  //constructor for elements to initialize the element with default values
  elements (string name="undefined", float mass = 0, int atomic_no = 0, int no_of_isotopes = 0, int no_of_isobars = 0){
    e.name = name;
    e.mass = mass;
    e.atomic_no = atomic_no;
    e.no_of_iso = no_of_isotopes;
    for(int i=0; i<no_of_isotopes; i++){
      e.isotopes[i]=0;
    }
    e.no_of_isb = no_of_isobars;
    for(int i=0; i<no_of_isobars; i++){
      e.isobars[i]=0;
    }
    total++;
    written = 1;
  }

  //Function to ask for input data
  void input(){
    clrscr();
    printh("Enter the Details of the Element");

    printd("Name");
    cin>>e.name;
    cout<<"\n";

    printd("Atomic Mass");
    cin>>e.mass;
    cout<<"\n";

    printd("Atomic Number");
    cin>>e.atomic_no;
    cout<<"\n";

    printd("No. of Isotopes (If Any)");
    cin>>e.no_of_iso;
    cout<<"\n";

    if(e.no_of_iso){  //will ask isotopes only when it has no of isotopes > 0
      printsh("Enter Atomic Mass of Isotopes");
      for(int i=0;i<e.no_of_iso;i++){
        printd("Isotope",i+1);
        cin>>e.isotopes[i];
        cout<<"\n";
      }
    }

    printm("Thanks for Entering Data!");
  }

  //Function to edit data
  void edit(int code = 0){
    clrscr();

    string rep=""; // string used in replace_elem(strig) for updating data
    string old_name=e.name; //saving old value of name of element
    string name,mass,a_no, nso, nsb;

    printh("Edit Details of the Element");
    printsh("Enter data for fields that you want to edit else just press '-' ");

    printd2("Name",e.name);
    cin>>name;
    if(name != "-"){ //checking if user entered '-' or actual data
      e.name = name;  // in case user entered data, we will update old data
    }
    rep+=e.name; //growing replacement string by adding updated values in string form
    rep+=" "; // adding space for separating consecutive values
    cout<<"\n"; // same process is employed for rest of data too...

    printd2("Atomic Mass",e.mass);
    cin>>mass;
    if(mass != "-"){
      e.mass = stoi(mass);
    }
    rep+=itos(e.mass);
    rep+=" ";
    cout<<"\n";

    printd2("Atomic Number",e.atomic_no);
    cin>>a_no;
    if(a_no != "-"){
      e.atomic_no = stoi(a_no);
    }
    rep+=itos(e.atomic_no);
    rep+=" ";
    cout<<"\n";

    printd2("No. of Isotopes (If Any)",e.no_of_iso);
    cin>>nso;
    if(nso != "-"){
      e.no_of_iso = stoi(nso);
    }
    rep+=itos(e.no_of_iso);
    rep+=" ";
    cout<<"\n";

    if(e.no_of_iso && nso!="-"){
      printsh("Enter Atomic Mass of Isotopes");
      for(int i=0;i<e.no_of_iso;i++){
        printd("Isotope",i+1);
        cin>>e.isotopes[i];
        rep+=itos(e.isotopes[i]);
        rep+=" ";
        cout<<"\n";
      }
    }
    //cout<<rep<<endl;
    //delay(5000);
    if(code){ //if edit function was called by search and edit route
      replace_elem(rep,old_name); //this function replaces the old data string with new data string i.e. rep
    }
    printm("Your Data has been Edited. You would be redirected in 2s");
    delay(2000);
    if(code){
      menu(); //then menu would be invoked for further options
    }
    else{ //in case it was invoked normally after creating a element
      display(); //display() is called for more options and to display edited content
    }
  }

  //Function to display output data
  void display(int code=0){
    clrscr();
    printh("Details of the Element");

    printd("Name");
    cout<<e.name<<"\n";

    printd("Atomic Mass");
    cout<<e.mass<<"\n";

    printd("Atomic Number");
    cout<<e.atomic_no<<"\n";

    printd("Total Number of Isotopes are ");
    cout<<e.no_of_iso<<"\n";

    if(e.no_of_iso){
      printsh("Atomic Mass of Isotopes");
      for(int i=0;i<e.no_of_iso;i++){
        printd("Isotope",i+1);
        cout<<e.isotopes[i]<<"\n";
      }
    }

    printm("What next?");

    if(code){
       printo(1,"Edit");
       printo(2,"Delete");
       printo(3,"Go back");
       printo(0,"Any other Key to abort");

       int go_back = 2;
       cout<<"\n\n";
       printd("Enter your choice");
       cin>>go_back;

       switch(go_back){
         case 1 :edit(1);break;
         case 2 :delete_elem();break;
         case 3 :menu();break;
         default :abort();break;
       }
    }
    else{
      printo(1,"Edit");
      printo(2,"Save");
      printo(3,"Go back without saving");
      printo(0,"Any other Key to abort");

      int go_back = 2;
      cout<<"\n\n";
      printd("Enter your choice");
      cin>>go_back;

      switch(go_back){
        case 1 :edit();break;
        case 2 :save();break;
        case 3 :menu();break;
        default :abort();break;
      }
    }

  }

  void replace_elem(string rep, string name){
    fstream file;
    file.open("Element.txt",ios::in); //Element.txt is opened for reading
    string ch;
    string ss = Search(name,0); // old data is retrieved from text file
    int diff = rep.length() - ss.length();
    while(getline(file,ch)){  // data is read as whole line only
      int pos = ch.find(ss);  // position of old data is found
      ch.erase(pos,ss.length()); // old data is erased
      ch.insert(pos,rep); // new data is inserted at that position
    }
    file.close();
    file.open("Element.txt",ios::out); //Element.txt is opened for writing
    file<<ch; //New data is written in it
    file.close();
  }

  //Function to delete element
  void delete_elem(){
    fstream file;
    file.open("Element.txt",ios::in);
    string ch;
    string ss = Search(e.name,0); //data is searched
    //cout<<ss<<" ";
    while(getline(file,ch)){
      ch.replace(ch.find(ss),ss.length(),""); //data is found and replaced with a empty string i.e. ""
      //cout<<ch;
    }
    file.close();
    file.open("Element.txt",ios::out);
    file<<ch;
    file.close();
    printm("Element is removed!");
    delay(2000);
    menu();
  }

  //Function to save element data
  void save(){
    fstream fout;
    fout.open("Element.txt",ios::app);
    fout<<e.name;
    fout<<" ";
    fout<<e.mass;
    fout<<" ";
    fout<<e.atomic_no;
    fout<<" ";
    if(e.no_of_iso){
      fout<<e.no_of_iso;
      fout<<" ";
      for(int i=0;i<e.no_of_iso;i++){
        fout<<e.isotopes[i];
        fout<<" ";
      }
    }
    fout.close();
    printm("Element Data saved successfully. You'll be redirected in 2s");
    delay(2000);
    menu();
  }
};

int pos = 0;

string Search(string ss, int index){
  fstream file;
  pos=0;
  file.open("Element.txt",ios::in);
  string ch;
  string data = "";
  int found = 0;
  int i=0;
  while(file>>ch){
    if(isalpha(ch[0])){
        //cout<<data;
        if(found) break;
        else{
          pos++;
          data="";
          i=0;
        }
    }
    data+=ch;
    //cout<<data<<"   ";
    data+=" ";
    if(tolower(ss) == tolower(ch) && index == i){
      found = 1;
    }
    i++;
  }
  if(!found){
    return "\n   Not Found!\n";
  }
  file.close();
  return data;
}

//function to search and edit
void searchAndEdit(){
  clrscr();
  printm("Choose search option");
  printo(1,"Name");
  printo(2,"Atomic Mass");
  printo(3,"Atomic Number");
  printf("\n");
  printd("Enter your choice");
  int choice;
  cin>>choice;
  cout<<"\n";
  int option = 0;
  string ss;
  switch(choice){
    case 1 : option = 1;printd("Name");cin>>ss;break;
    case 2 : option = 2;printd("Atomic Mass");cin>>ss;break;
    case 3 : option = 3;printd("Atomic Number");cin>>ss;break;
    case 0 : menu();break;
    default: printm("You can press '0' to go back!");delay(3000);searchAndEdit();break;
  }

  if(option){
    string data = Search(ss,option-1);
    //cout<<data<<" at "<<pos;
    //delay(5000);
    string name,mass,atomic_no,nos,isotopes;
    int index=0;
    for(int i=0;i<data.length();i++){
      if(isspace(data[i])){
        index++;
        if(index<=4)
          i++;
      }
      switch(index){
        case 0: name+=data[i];break;
        case 1: mass+=data[i];break;
        case 2: atomic_no+=data[i];break;
        case 3: nos+=data[i];break;
      }
      if(index>=4){
        isotopes+=data[i];
      }
    }
    elements el;
    int mass_t = stoi(mass);
    int atomic_t = stoi(atomic_no);
    int iso = stoi(nos);
    if(iso){
      int isotopes_t[iso];
      int k=0;
      string num;
      cout<<isotopes;
      for(int i=0;i<isotopes.length();i++){
        if(isspace(isotopes[i])){
          i++;
          isotopes_t[k++]=stoi(num);
          num="";
        }
        num+=isotopes[i];
      }
      el.e.no_of_iso = iso;
      for(int i=0;i<=k;i++){
        el.e.isotopes[i]=isotopes_t[i];
      }
    }
    el.e.name = name;
    el.e.mass = mass_t;
    el.e.atomic_no = atomic_t;
    el.display(1);
  }
}


//function to list element data
void listElements(){
  clrscr();
  fstream fin;
  string attr[4]={"Name", "Atomic Mass", "Atomic Number", "Number of Isotopes"};
  fin.open("Element.txt",ios::in);
  char ch[50];
  printm("Elements found!");
  int i=0;
  while(fin>>ch){
    if(isalpha(ch[0])){
      cout<<" - - - - - - - - - - - - - - - - - - - - - -\n";
      i=0;
    }
    if(i<3 && i>=0){
      printd(attr[i]);
      cout<<ch<<"\n";
    }
    else if(i==3){
      int no = stoi(ch);
      printd("Number of Isotopes are");
      cout<<no<<"\n";
    }
    else if(i>=4){
      printd("Atomic Mass for Isotope",i-3);
      cout<<ch<<"\n";
    }
    i++;
  }
  fin.close();
  printm("What next?");

  printo(1,"Go back to menu");
  printo(0,"Any other Key to abort");

  int go_back = 2;
  cout<<"\n\n";
  printd("Enter your choice");
  cin>>go_back;

  switch(go_back){
    case 1 :menu();break;
    default :abort();break;
  }

}

void menu(){
  clrscr();
  elements el;

  printm("C H E M - A S S I S T A N T");
  printh("Menu");

  printo(1,"Enter New Element");
  printo(2,"Show Elements List");
  printo(3,"Search, Edit and Delete");
  printo(4,"Exit Code");

  cout<<"\n\n";
  int option = 0;
  printd("Enter your choice");
  cin>>option;
  switch(option){
    case 1 : el.input();el.display();break;
    case 2 : listElements();break;
    case 3 : searchAndEdit();break;
    case 4 : abort();break;
    default : printm("Please Enter in range!");delay(2000);menu();
  }
}

int main(){
  menu();
  return 0;
}
