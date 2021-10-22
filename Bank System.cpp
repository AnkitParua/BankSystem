/*
Bank Management System
author : Ankit Kumar parua
last edit : 22/10/21
*/

#include<iostream>
#include<string.h>
#include<vector>
#include<fstream>
using namespace std;

#define MAX 60
#define interest 5

static long randnum = 1000000;
int lastentry = -1;

class bank{
	string name_;
	char add_[MAX];
	long acc_no_, acc_type_;
	double bal_,interest_gained_;
	int visible=0,num_of_transact;
	
	public :
		bank()
		{
			name_="";
			acc_type_=bal_=0;
			visible=1;
			num_of_transact=0;
			interest_gained_=0;
		}
		
		void add_details()
		{
			cout<<"\nEnter Yourfirst Name : ";
			cin>>name_;
			cout<<"\nEnter Your Account Type \n(1 for Current Account\t2 for Savings Account\t3 for FD Account)\nEnter your choice : ";
			cin>>acc_type_;
			cout<<"\nEnter Your Address : ";
			cin.ignore();
			cin.getline(add_,MAX);
			acc_no_ = (randnum+=5);
		}
		
		void add_details_dynamic(string n, int ac, char* ad, double sal,int acno)
		{
		    name_=n;
		    acc_type_=ac;
		    strcpy(add_,ad);
		    acc_no_ = acno;
		    bal_ = sal;
		}
		
		void show_details()
		{
		    cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
			cout<<"\n\tHello "<<name_<<"\n\tYour Account Number is : "<<acc_no_<<"\n\tYour current balance is : "<<bal_<<endl;
			cout<<"\tYour Account Type is : ";
			switch(acc_type_)
			{
			    case 1 : {
			        cout<<"Current Account";
			        break;
			    }
			    case 2 : {
			        cout<<"Savings Account";
			        break;
			    }
			    case 3 : {
			        cout<<"FD Account";
			        break;
			    }
			    default :
			    cout<<"Not listed !!";
			}
			cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
			
		}
		
	    void displayall()
	    {
	        cout<<acc_no_<<"\t"<<name_<<"\t"<<bal_<<"\t"<<acc_type_;
	    }
	    
	    void deleteuser()
	    {
	        visible = 0;
	    }
	    
	    long accountnum()
	    {
	        return acc_no_;
	    }
	    
	    string getname()
	    {
	        return name_;
	    }
	    
	    double getbal()
	    {
	        return bal_;
	    }
	    
	    char* getaddress()
	    {
	        return add_;
	    }
	    
	    void transact()
	    {
	        cout<<"Do you want to credit(0) or debit(1) : ";
	        int n;
	        cin>>n;
	        if(n==0)
	        {
	            cout<<"How much do you want to add? : ";
	            int money;
	            cin>>money;
	            bal_ += money;
	            num_of_transact++;
	        }
	        else
	        if(n==1)
	        {
	            cout<<"How much do you want to debit? : ";
	            int money;
	            cin>>money;
	            if(money > bal_)
	            {
	                cout<<"Entered input exceeds current balance.";
	                return;
	            }
	            else
	            bal_ -= money;
	            num_of_transact++;
	        }
	        else
	        {
	            cout<<"Wrong input !";
	            return;
	        }
	    }
	    
	    void calinterest()
	    {
	        if(num_of_transact==0)
	        interest_gained_ += bal_*0.05;
	    }
	    
	    int getvisibility()
	    {
	        return visible;
	    }
	    
	    long getacc()
	    {
	        return acc_no_;
	    }
	    
	    int acct()
	    {
	        return acc_type_;
	    }
	    
};

void viewall(vector<bank> arr)
{
    cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"Acc no.\tName\tBalance\taccount type"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    for(auto &a: arr)
    {
        if(!a.getvisibility())
        continue;
        a.displayall();
        cout<<endl;
    }
}


void controlshifter(vector<bank> &arr)
{
    cout<<"Enter the Account Number to search : ";
    long num_;
    int ch_;
    cin>>num_;
    for(auto &a: arr)
    {
        if(a.accountnum() == num_)
        {
            if(!a.getvisibility())
            {
                cout<<"Not Found!!!";
                return;
            }
            cout<<"Found!";
            cout<<"\n\tPress 1 to view current customer\n\tPress 2 for view Address\n\tPress 3 for view Name\n\tPress 4 for view balance\n\tPress 5 for deposit/credit money\n\tPress 6 to delete the current customer\n\tPress 7 to exit";
            cout<<"\n\t\tEnter Your Choice : ";
            cin>>ch_;
            switch(ch_)
            {
                case 1 :{
                    a.show_details();
                    break;
                }
                case 2 :{
                    cout<<"\n\t*******************************";
	                cout<<"\n\t\tAddress : "<<a.getaddress();
	                cout<<"\n\t*******************************\n";
                    
                    break;
                }
                case 3 :{
                    cout<<"\n\t*******************************";
                    cout<<"\n\t\tName : "<<a.getname();       
                    cout<<"\n\t*******************************\n";
                    
                    break;
                }
                case 4 :{
                    cout<<"\n\t*******************************";
	                cout<<"\n\t\tBalance : "<<a.getbal();
	                cout<<"\n\t*******************************\n";
                    
                    break;
                }
                case 5 :{
                    a.transact();
                    break;
                }
                case 6 :{
                    a.deleteuser();
                    break;
                }
                case 7 :{
                    break;
                }
                default:
                {
                    cout<<"Wrong input!!";
                }
            }
            return;
        }
    }
    cout<<"Not Found!!";
}

//vector<bank>
void read()
{
    vector<bank> arr;
    //double bal;
    //long nums;
    string names,bal,nums,type, adds;
    //char adds[MAX];
    //int type;
    
    ifstream fin;
    fin.open("DB.txt");

    while(fin)
    {
        bank b;
        getline(fin,names);
        getline(fin,bal);
        getline(fin,nums);
        getline(fin,adds);
        getline(fin,type);
        
        cout<<names<<" "<<bal<<" "<<nums<<" "<<adds<<" "<<type<<"\n";
    }
    fin.close();
    //return arr;
}

void write(vector<bank>arr)
{
    ofstream fout;
    int i=0,size=arr.size()-1;
    
    fout.open("DB.txt");
    
    for(auto &a:arr)
    {
        if(!a.getvisibility())
        continue;
        fout<<a.getname()<<endl;
        fout<<a.getbal()<<endl;
        fout<<a.getacc()<<endl;
        fout<<a.getaddress()<<endl;
        if(i==size)
        {
            fout<<a.acct();
        }
        else
        fout<<a.acct()<<endl;
        i++;
    }
    
    fout.close();
}

void controller()
{
    cout<<"\t~~~~~~~~~~Welcome~~~~~~~~~~"<<endl;
    cout<<"\n\t\tMaster Control"<<endl;
    vector<bank> arr;// = read();
    read();
    int options_;
    int enter_ = 1;
    bank a;
    a.add_details();
    arr.push_back(a);
    while(1)
    {
        
        bank b;

        
        cout<<"\nPress 0 to add a Customer\nPress 1 to view all costumer\nPress 2 to view current customer\nPress 3 for view Address\nPress 4 for view Name\nPress 5 for view balance\nPress 6 for deposit/credit money\nPress 7 to check a given number is present in the list and operate on that account\nPress 8 to delete the current customer\nPress 9 to EXIT";
        cout<<"\n\tEnter your option : ";
        cin>>options_;
        
        switch(options_)
        {
            case 0 :{
                b.add_details();
                arr.push_back(b);
                break;
            }
            case 1 :{
                viewall(arr);
                break;
            }
            
            case 2 :{
                arr[arr.size()-1].show_details();
                break;
            }
            case 3 :{
                cout<<"\n\t*******************************";
	            cout<<"\n\t\tAddress : "<<arr[arr.size()-1].getaddress();
	            cout<<"\n\t*******************************\n";
                
                break;
            }
            case 4 :{
                    cout<<"\n\t*******************************";
                    cout<<"\n\t\tName : "<<arr[arr.size()-1].getname();
                    cout<<"\n\t*******************************\n";
                    
                break;
            }
            case 5 :{
                    cout<<"\n\t*******************************";
	                cout<<"\n\t\tBalance : "<<arr[arr.size()-1].getbal();;
	                cout<<"\n\t*******************************\n";
                
                break;
            }
            case  6:{
                arr[arr.size()-1].transact();
                break;
            }
            case 7 :{
                controlshifter(arr);
                break;
            }
            case 8 :{
                cout<<"\n\t\t\tCustomer Account Deleted.";
                arr[arr.size()-1].deleteuser();
                break;
            }
            case 9 : {
                cout<<endl;
                break;
            }
            default:
            cout<<"Not Listed Option !!";
        }
        
        if(options_ > 8)
        break;
    }
    
    write(arr);
    
}


int main()
{
	controller();
	return 0;
}
