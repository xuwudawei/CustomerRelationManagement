#include <iostream>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::to_string;

class CustomerRelation{
    private:
        string name;
        string number;
        string complaint;
        string checknum;
        string userId;
        string complaint_ID;
        string action;
        string resolving_remarks;
        static int userCount;
    public:
        CustomerRelation(string,string,string,string);
        CustomerRelation(string);
        void generateID();
        static void changeUserCount();
        void getRecord();
        static void record_exiting_check(string);

};

int CustomerRelation::userCount = 0;

CustomerRelation::CustomerRelation(string name,string number,string complaint,string action){
    cout<<"Resolving Remarks: ";
    getline(cin,resolving_remarks);
    this->name=name;
    this->number=number;
    this->complaint=complaint;
    this->action=action;
    this->resolving_remarks = resolving_remarks;
}
CustomerRelation::CustomerRelation(string num){
    checknum=num;
}

void CustomerRelation::changeUserCount(){
    userCount++;
}

void CustomerRelation::generateID(){
    // Generate id
    changeUserCount();
    userId = name.substr(0,2)+"-"+to_string(userCount);
    complaint_ID = complaint.substr(0,2)+"-"+to_string(userCount);
    cout<<"\nYour User ID: "<<userId<<endl;
    cout<<"Your Complaint ID: "<<complaint_ID<<endl;
    cout<<"Please remember this details"<<endl;

    // Writing information to the User file
    ofstream user;
    user.open("user.txt",ios::app);
    user<<"ID: "+userId+" * "+"Name: "+name+" * "+"Number: "+number<<endl;
    user.close();

    // Writing information to the complaints file
    ofstream complaintFile;
    complaintFile.open("complaint.txt",ios::app);
    complaintFile<<+"Phone number: "+number+" * "+"ID: "+userId+" * "+"CID: "+complaint_ID+" * "+" Complaint: "+complaint+" * "+" Action: "+action+" * "+" Resolving remark: "+resolving_remarks<<endl;
    complaintFile.close();
}
// Extracting previous complaints if phone number already exist
void CustomerRelation::getRecord(){
    ifstream file;
    file.open("complaint.txt",ios::in);
    if(file){
        string line;
        string details;
        string comparer;
        cout<<"\t\tComplaint History"<<endl;
        cout<<"\t\t-----------------"<<endl;
        while(file.good()){
            //Get each line from the file
            getline(file,line);
            //extracting each Id number from the complaint file
            comparer = line.substr(0,line.find("*")-1);
            //comparing it with the id entered
            if(comparer==checknum){
            //setting the extraction position at "*"
            int pos = line.find("*");
            // Copy all substring after pos into another string
            string details = line.substr(pos + 1);
            cout<<details<<endl;
            }
            else {
             
                }
        }
    }
    else{
        cout<<"Failed to open complaint file."<<endl;
    }
}
void CustomerRelation::record_exiting_check(string num_verification)
{
    ifstream file;
    bool f = 0;
    file.open("complaint.txt",ios::in);
    if(file){
        string line;
        string details;
        string comparer;
        int opt1;
        num_verification="Phone number: "+num_verification;
        while(file.good()){
            //Get each line from the file
            getline(file,line);
            //extracting each Id number from the complaint file
            comparer = line.substr(0,line.find("*")-1);
            //comparing it with the id entered
            if(comparer==num_verification){
                f=1;
                cout<<"Number exist."<<endl;
                cout<<"Enter '1' to review complaint registration or '2' to ignore and continue: "<<endl;
                cin>>opt1;
                if(opt1==1)
                {
                //setting the extraction position at "*"
                int pos = line.find("*");
                // Copy all substring after pos into another string
                string details = line.substr(pos + 1);
                cout<<"\t\tComplaint History"<<endl;
                cout<<"\t\t-----------------"<<endl;
                cout<<details<<endl;
                cout<<"Continue below"<<endl;
                break;
                cin.ignore(100,'\n');
                }
                else if(opt1==2)
                {
                    break;
                }
            }
            else {
                    f=0;
                }
        }
        if(f==0) cout<<"This is a new user.\n";
    }
    else
    {
        cout<<"Invalid file operations"<<endl;
        exit(0);
    }
    
}

int main(){
    label:
    string name,action,complaint,number,resolving_remarks;
    int option;
    cout<<"\t\tCustomer Relation"<<endl;
    cout<<"\t\t-----------------"<<endl;
    cout<<"Select an option below: "<<endl;
    cout<<"1. File a new complaint"<<endl;
    cout<<"2. Read complaint history"<<endl;
    cout<<"3.Exit"<<endl;
    cin>>option;
    cin.ignore(1,'\n');
    if(option==1){
        int opt;
        // Filing a complaint
        cout<<"Name: ";
        getline(cin,name);
        cout<<"Number: ";
        getline(cin,number);
        CustomerRelation::record_exiting_check(number);
        cout<<"Complaint: ";
        getline(cin,complaint);
        cin.ignore(100,'\n');
        cout<<"Action: ";
        getline(cin,action);
        // Creating object of the complaints
        CustomerRelation cus(name,number,complaint,action);
        cus.generateID();
        label1:
        cout<<"Do you want to continue ? 1(Yes) / 2(No)"<<endl;
        cin>>opt;
        switch(opt)
        {
            case 1:
            goto label;
            break;
            
            case 2:
            exit(0);
            break;

            default:
            cout<<"Incorrect input! Please enter again"<<endl;
            goto label1;
            break;
        }
    }
    else if(option==2){
        // Getting complaint history
        string checknum;
        cout<<"Please enter your Phone Number: ";
        getline(cin,checknum);
        CustomerRelation cus("Phone number: "+checknum);
        cus.getRecord();
        goto label;
    }
    else if(option==3) exit(0);
    else
    {
        cout<<"Incorrect input,please enter again"<<endl;
        goto label;
    } 
}

