/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */
#include "requestLib.h"
#include "dbLib.h"

/// Initialize and Finalize any global data that you use in the program

bool initVGlobalData(void** pGData) {
    // TODO: allocate global data if you think it is necessary.
    /// pGData contains the address of a pointer. You should allocate data for the global data
    /// and then assign its address to *pGData
    return true;
}
void releaseVGlobalData(void* pGData) {
    // TODO: release the data if you finish using it
}

bool processRequest(VRequest& request, L1List<VRecord>& recList, void* pGData) {
    // TODO: Your code comes here

    /// NOTE: The output of the request will be printed on one line
    /// end by the end-line '\n' character.
    string req = request.code;
    if(req == "CNV"){
        L1List<char*> *p = new L1List<char*>();
        char* tmp = recList.at(0).id;
        p->insertHead(tmp);
        for(int i = 0; i < recList.getSize(); i++){
            int j = 0;
            while(j < p->getSize() && strcmp(p->at(j), recList.at(i).id) != 0){
                j++;
            }
            if(j == p->getSize()){
                tmp = recList.at(i).id;
                p->push_back(tmp);
            }
        }
        cout<<p->getSize()<<endl;
    }
    if(req == "VFF"){
        cout<<recList.at(0).id<<endl;
    }
    if(req == "VFL"){
        cout<<recList.at(recList.getSize() - 1).id<<endl;
    }
    if(req.substr(0,3) == "VFY"){
        int i = 0;
        while(i < recList.getSize() && req.substr(3,req.length() - 3) != recList.at(i).id){
            i++;
        }
        if(i != recList.getSize()) cout<<recList.at(i).y<<endl;
        else cout<<req<<": Failed"<<endl;
    }
    if(req.substr(0,3) == "VFX"){
        int i = 0;
        while(i < recList.getSize() && req.substr(3,req.length() - 3) != recList.at(i).id){
            i++;
        }
        if(i != recList.getSize()) cout<<recList.at(i).x<<endl;
        else cout<<req<<": Failed"<<endl;
    }
    if(req.substr(0,3) == "VLY"){
        int i = recList.getSize() - 1;
        while(i >= 0 && req.substr(3,req.length() - 3) != recList.at(i).id){
            i--;
        }
        if(i != -1) cout<<recList.at(i).y<<endl;
        else cout<<req<<": Failed"<<endl;
    }
    if(req.substr(0,3) == "VLX"){
        int i = recList.getSize() - 1;
        while(i >= 0 && req.substr(3,req.length() - 3) != recList.at(i).id){
            i--;
        }
        if(i != -1) cout<<recList.at(i).x<<endl;
        else cout<<req<<": Failed"<<endl;
    }
    if(req.substr(0,3) == "VFT"){
        int i = 0;
        while(i < recList.getSize() && req.substr(3,req.length() - 3) != recList.at(i).id){
            i++;
        }
        if(i != recList.getSize()){
            char* des = new char();
            strPrintTime(des, recList.at(i).timestamp);
            cout<<des<<endl;
        }
        else cout<<req<<": Failed"<<endl;
    }
    if(req.substr(0,3) == "VLT"){
        int i = recList.getSize() - 1;
        while(i >= 0 && req.substr(3,req.length() - 3) != recList.at(i).id){
            i--;
        }
        if(i != -1){
            char* des = new char();
            strPrintTime(des, recList.at(i).timestamp);
            cout<<des<<endl;
        }
        else cout<<req<<": Failed"<<endl;
    }
    if(req.substr(0,3) == "VCR"){
        int k = 0;
        for(int i = 0; i < recList.getSize(); i++){
            if(req.substr(3,req.length() - 3) == recList.at(i).id) k++;
        }
        if(k != 0) cout<<k<<endl;
        else cout<<req<<": Failed"<<endl;
    }
    if(req.substr(0,3) == "VCL"){
        int i = 0;
        double x, y, k = 0;
        while(i < recList.getSize() && req.substr(3,req.length() - 3) != recList.at(i).id){
            i++;
        }
        if(i != recList.getSize()){
            x = recList.at(i).x;
            y = recList.at(i).y;
        }
        for(i++; i < recList.getSize(); i++){
            if(req.substr(3,req.length() - 3) == recList.at(i).id){
                k += distanceVR(y, x, recList.at(i).y, recList.at(i).x);
                x = recList.at(i).x;
                y = recList.at(i).y;
            }
        }
        cout<<k<<endl;
    }
    if(req.substr(0,3) == "VMT"){
        int t = 0, i = 0;
        time_t tmp;
        double x, y;
        while(i < recList.getSize() && req.substr(3,req.length() - 3) != recList.at(i).id){
            i++;
        }
        if(i != recList.getSize()){
            x = recList.at(i).x;
            y = recList.at(i).y;
            tmp = recList.at(i).timestamp;
        }
        for(i++; i < recList.getSize(); i++){
            if(req.substr(3,req.length() - 3) == recList.at(i).id){
                if(x != recList.at(i).x || y != recList.at(i).y) t += recList.at(i).timestamp - tmp;
                x = recList.at(i).x;
                y = recList.at(i).y;
                tmp = recList.at(i).timestamp;
            }
        }
        cout<<t<<endl;
    }
    if(req.substr(0,3) == "VFS"){
        int t = 0, i = 0;
        double x, y;
        while(i < recList.getSize() && req.substr(3,req.length() - 3) != recList.at(i).id){
            i++;
        }
        if(i != recList.getSize()){
            x = recList.at(i).x;
            y = recList.at(i).y;
        }
        for(i++; i < recList.getSize(); i++){
            if(req.substr(3,req.length() - 3) == recList.at(i).id){
                x = recList.at(i).x;
                y = recList.at(i).y;
            }
        }
        cout<<t<<endl;
    }
    if(req == "CNR"){
        cout<<recList.getSize()<<endl;
    }
    return true;
}