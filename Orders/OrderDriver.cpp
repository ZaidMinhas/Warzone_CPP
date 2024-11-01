#include <iostream>
#include <string>
using namespace std;
#include "OrderDriver.h"
#include "Orders.h"
//Fixes the order string so only the first letter is uppercased.
static string fixString(string order){
    for(int i=0;i<order.size();i++){
            if(i==0){
                order[i]=toupper(order[i]);
            }
            else{
                order[i]=tolower(order[i]);
            }
        }
    return order;
}
void testOrdersList(){
    OrdersList* test=new OrdersList();
    string order;
    cout<<"Compiling Successful"<<endl;
    /*while(true){
        if(test->getSize()!=0){
            cout<<test;
        }
        cout<<"What are your orders commander: ";
        cin>>order;
        cout<<endl;
        order=fixString(order);
        if(order=="Deploy"){
            test->addOrder(new Deploy(order));
        }
        else if(order=="Advance"){
            test->addOrder(new Advance(order));
        }
        else if(order=="Bomb"){
            test->addOrder(new Bomb(order));
        }
        else if(order=="Blockade"){
            test->addOrder(new Blockade(order));
        }
        else if(order=="Airlift"){
            test->addOrder(new Airlift(order));
        }
        else if(order=="Negotiate"){
            test->addOrder(new Negotiate(order));
        }
        else if(order=="Done"){
            cout<<"Roger that!!"<<endl;
            break;
        }
        else{
            cout<<"Commander!! That order is not possible for this regimend!!"<<endl;
        }
    }
    while(true){
        cout<<test;
        int position1;
        int position2;
        cout<<"Commander!! Are there any orders you would like to Move or Remove before execution:";
        cin>>order;
        cout<<endl;
        order=fixString(order);
        if(order=="Move"){
            cout<<"Understood!! Which order would you like to move and to where: ";
            cin>>position1>>position2;
            cout<<endl;
            test->move(position1,position2);
        }
        else if(order=="Remove"){
            cout<<"Understood!! Which order would you like to remove: ";
            cin>>position1;
            cout<<endl;
            test->remove(position1);
        }
        else if(order=="Done"){
            cout<<"Roger that!! Executing orders now!!"<<endl;
            break;
        }
        else{
            cout<<"Commander!! I cannot authorize that command!!"<<endl;
        }
    }
    test->setCurrentOrder(test->getHead()->getNext());
    for(int i=1;i<=test->getSize();i++){
        test->getCurrentOrder()->execute();
        cout<<endl;
        test->setCurrentOrder(test->getCurrentOrder()->getNext());
    }
    cout<<"All orders you issued have been passed through for execution"<<endl;*/
}