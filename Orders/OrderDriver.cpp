#include "OrdersList.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;
int testOrdersList(){
    while(true){
        string orderToIssue;
        cout<<"Insert the order you want to submit. If you are done submitting orders, write Done:";
        cin>>orderToIssue;
        cout<<endl;
        for(int i=0;i<orderToIssue.size();i++){
            orderToIssue[i]=tolower(orderToIssue[i]);
        }
        if(orderToIssue=="done"){
            cout<<"Order issuing phase is done";
            break;
        }
        else if(orderToIssue=="deploy"){
            //Create Deploy Order
            //Put it into the players OrdersList
        }
        else if(orderToIssue=="advance"){
            //Create Advance Order
            //Put it into the players OrderList
        }
        else if(orderToIssue=="bomb"){
            //Create Bomb Order
            //Put it into the players OrderList
        }
        else if(orderToIssue=="blockade"){
            //Create Blockade Order
            //Put it into the players OrderList
        }
        else if(orderToIssue=="airlift"){
            //Create Airlift Order
            //Put it into the players OrderList
        }
        else if(orderToIssue=="negotiate"){
            //Create Negotiate Order
            //Put it into the players OrderList
        }
    }
    return 0;
}

int main(){
    int test = testOrdersList();
    return test;
}