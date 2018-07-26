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
    cout<<req<<": ";

    // Tính số lượng thiết bị trong database
    if(req == "CNV"){
        int size = recList.getSize();
        char* arr[size];

        for(int i = 0; i < size; i++){
            arr[i] = recList.at(i).id;
        }
        for(int i = 0; i < size - 1; i++){
            for(int j = i + 1; j < size; j++){
                if(strcmp(arr[i],arr[j]) == 0){
                    for(int k = j; k < size; k++){
                        arr[k] = arr[k+1];
                    }
                    size--;
                    j--;
                }
            }
        }
        cout<<size<<endl;
    }
    // Tìm thiết bị được lưu trữ đầu tiên
    if(req == "VFF"){
        cout<<recList.at(0).id<<endl;
    }
    // Tìm thiết bị được lưu trữ cuối cùng
    if(req == "VFL"){
        int size = recList.getSize();
        char* arr[size];

        for(int i = 0; i < size; i++){
            arr[i] = recList.at(i).id;
        }
        for(int i = 0; i < size - 1; i++){
            for(int j = i + 1; j < size; j++){
                if(strcmp(arr[i],arr[j]) == 0){
                    for(int k = j; k < size; k++){
                        arr[k] = arr[k+1];
                    }
                    size--;
                    j--;
                }
            }
        }
        cout<<arr[size - 1]<<endl;
    }
    // Tìm tọa độ y được lưu trữ đầu tiên của thiết bị <ID>
    if(req.substr(0,3) == "VFY"){
        int i = 0;
        int size = recList.getSize();
        string tmp = req.substr(3,req.length() - 3);
        while(i < size && tmp != recList.at(i).id){
            i++;
        }
        if(i != size) cout<<recList.at(i).y<<endl;
        else cout<<"not found!"<<endl;
    }
    // Tìm tọa độ x được lưu trữ đầu tiên của thiết bị <ID>
    if(req.substr(0,3) == "VFX"){
        int i = 0;
        int size = recList.getSize();
        string tmp = req.substr(3,req.length() - 3);
        while(i < size && tmp != recList.at(i).id){
            i++;
        }
        if(i != size) cout<<recList.at(i).x<<endl;
        else cout<<"not found!"<<endl;
    }
    // Tìm tọa độ y được lưu trữ cuối cùng của thiết bị <ID>
    if(req.substr(0,3) == "VLY"){
        int i = recList.getSize() - 1;
        string tmp = req.substr(3,req.length() - 3);
        while(i >= 0 && tmp != recList.at(i).id){
            i--;
        }
        if(i != -1) cout<<recList.at(i).y<<endl;
        else cout<<"not found!"<<endl;
    }
    // Tìm tọa độ x được lưu trữ cuối cùng của thiết bị <ID>
    if(req.substr(0,3) == "VLX"){
        int i = recList.getSize() - 1;
        string tmp = req.substr(3,req.length() - 3);
        while(i >= 0 && tmp != recList.at(i).id){
            i--;
        }
        if(i != -1) cout<<recList.at(i).x<<endl;
        else cout<<"not found!"<<endl;
    }
    // Tìm thời điểm bắt đầu lưu trữ của thiết bị <ID>
    if(req.substr(0,3) == "VFT"){
        int i = 0;
        int size = recList.getSize();
        string tmp = req.substr(3,req.length() - 3);
        while(i < size && tmp != recList.at(i).id){
            i++;
        }
        if(i != size){
            char* des = new char();
            strPrintTime(des, recList.at(i).timestamp);
            cout<<des<<endl;
        }
        else cout<<"not found!"<<endl;
    }
    // Tìm thời điểm kết thúc lưu trữ của thiết bị <ID>
    if(req.substr(0,3) == "VLT"){
        int i = recList.getSize() - 1;
        string tmp = req.substr(3,req.length() - 3);
        while(i >= 0 && tmp != recList.at(i).id){
            i--;
        }
        if(i != -1){
            char* des = new char();
            strPrintTime(des, recList.at(i).timestamp);
            cout<<des<<endl;
        }
        else cout<<"not found!"<<endl;
    }
    // Tính số lượng record của thiết bị <ID>
    if(req.substr(0,3) == "VCR"){
        int k = 0;
        int size = recList.getSize();
        string tmp = req.substr(3,req.length() - 3);
        for(int i = 0; i < size; i++){
            if(tmp == recList.at(i).id) k++;
        }
        if(k != 0) cout<<k<<endl;
        else cout<<"not found!"<<endl;
    }
    // Tính độ dài hành trình của thiết bị <ID>
    if(req.substr(0,3) == "VCL"){
        int i = 0;
        int size = recList.getSize();
        double x, y, k = 0;
        string tmp = req.substr(3,req.length() - 3);
        while(i < size && tmp != recList.at(i).id){
            i++;
        }
        if(i != size){
            x = recList.at(i).x;
            y = recList.at(i).y;
        }
        for(i++; i < size; i++){
            if(tmp == recList.at(i).id){
                k += distanceVR(y, x, recList.at(i).y, recList.at(i).x);
                x = recList.at(i).x;
                y = recList.at(i).y;
            }
        }
        cout<<k<<endl;
    }
    // Tính thời gian di chuyển của thiết bị <ID>
    if(req.substr(0,3) == "VMT"){
        int t = 0, i = 0;
        int size = recList.getSize();
        time_t times;
        double x, y;
        string tmp = req.substr(3,req.length() - 3);
        while(i < size && tmp != recList.at(i).id){
            i++;
        }
        if(i != size){
            x = recList.at(i).x;
            y = recList.at(i).y;
            times = recList.at(i).timestamp;
        }
        for(i++; i < size; i++){
            if(tmp == recList.at(i).id){
                if(distanceVR(y, x, recList.at(i).y, recList.at(i).x) > 0.005){
                    t += recList.at(i).timestamp - times;
                }
                x = recList.at(i).x;
                y = recList.at(i).y;
                times = recList.at(i).timestamp;
            }
        }
        cout<<t<<endl;
    }
    // Tìm điểm dừng đầu tiên của thiết bị <ID>, xuất (x y)
    if(req.substr(0,3) == "VFS"){
        int t = 0, i = 0;
        int size = recList.getSize();
        double x, y;
        string tmp = req.substr(3,req.length() - 3);
        while(i < size && tmp != recList.at(i).id){
            i++;
        }
        if(i != size){
            x = recList.at(i).x;
            y = recList.at(i).y;
        }
        for(i++; i < size; i++){
            if(tmp == recList.at(i).id){
                if(distanceVR(y, x, recList.at(i).y, recList.at(i).x) < 0.005){
                    t = 1;
                    break;
                }
                x = recList.at(i).x;
                y = recList.at(i).y;
            }
        }
        if(t == 1) cout<<"("<<x<<", "<<y<<")"<<endl;
        else cout<<"non stop!"<<endl;
    }
    // Tìm điểm dừng cuối cùng của thiết bị <ID>
    if(req.substr(0,3) == "VLS"){
        int t = 0;
        int i = recList.getSize() - 1;
        double x, y;
        string tmp = req.substr(3,req.length() - 3);
        while(i >= 0 && tmp != recList.at(i).id){
            i--;
        }
        if(i != -1){
            x = recList.at(i).x;
            y = recList.at(i).y;
        }
        for(i--; i >= 0; i--){
            if(tmp == recList.at(i).id && distanceVR(y, x, recList.at(i).y, recList.at(i).x) < 0.005){
                t = 1;
                break;
            }
        }
        if(t == 1) cout<<"("<<recList.at(i).x<<", "<<recList.at(i).y<<")"<<endl;
        else cout<<"non stop!"<<endl;
    }
    // Tìm thời gian dừng lâu nhất của thiết bị <ID>
    if(req.substr(0,3) == "VMS"){
        int t = 0, i = 0, max = 0;
        int size = recList.getSize();
        time_t times;
        double x, y;
        string tmp = req.substr(3,req.length() - 3);
        while(i < size && tmp != recList.at(i).id){
            i++;
        }
        if(i != size){
            x = recList.at(i).x;
            y = recList.at(i).y;
            times = recList.at(i).timestamp;
        }
        for(i++; i < size; i++){
            if(tmp == recList.at(i).id){
                if(distanceVR(y, x, recList.at(i).y, recList.at(i).x) < 0.005){
                    t = recList.at(i).timestamp - times;
                    if(t > max) max = t;
                }
                x = recList.at(i).x;
                y = recList.at(i).y;
                times = recList.at(i).timestamp;
            }
        }
        if(max != 0) cout<<max<<endl;
        else cout<<"non stop!"<<endl;
    }
    // Tìm khoảng cách trung bình giữa 2 lần thu thập dữ liệu của thiết bị <ID>
    if(req.substr(0,3) == "VAS"){
        int i = 0, j = 0;
        int size = recList.getSize();
        double x, y, k = 0;
        string tmp = req.substr(3,req.length() - 3);
        while(i < size && tmp != recList.at(i).id){
            i++;
        }
        if(i != size){
            x = recList.at(i).x;
            y = recList.at(i).y;
        }
        for(i++; i < size; i++){
            if(tmp == recList.at(i).id){
                k += distanceVR(y, x, recList.at(i).y, recList.at(i).x);
                x = recList.at(i).x;
                y = recList.at(i).y;
                j++;
            }
        }
        if(j != 0) cout<<(k/j)*1000<<" meter"<<endl;
        else cout<<0<<endl;
    }
    // TODO: Tìm thời lượng dừng lâu nhất của tất cả các thiết bị
    if(req == "MST"){
    }
    // Tính số lượng record trong database
    if(req == "CNR"){
        cout<<recList.getSize()<<endl;
    }
    // Tìm thiết bị có số lượng record nhiều nhất
    if(req == "MRV"){
        int size = recList.getSize();
        char* arr[size];

        for(int i = 0; i < size; i++){
            arr[i] = recList.at(i).id;
        }
        
        char* id = arr[0];
        int max = 0;
        for(int i = 0; i < size - 1; i++){
            int idx = 0;
            for(int j = i + 1; j < size; j++){
                if(strcmp(arr[i],arr[j]) == 0){
                    idx++;
                    for(int k = j; k < size; k++){
                        arr[k] = arr[k+1];
                    }
                    size--;
                    j--;
                }
            }
            if(idx > max){
                max = idx;
                id = arr[i];
            }
        }
        cout<<id<<endl;
    }
    // Tìm thiết bị có số lượng record ít nhất
    if(req == "LRV"){
        int k = 0, idx = 0;
        int size = recList.getSize();
        while(k != 1 && idx < size){
            string tmp = recList.at(idx).id;
            k = 0;
            for(int i = idx; i < size; i++){
                if(tmp == recList.at(i).id) k++;
            }
            idx++;
        }
        cout<<recList.at(idx - 1).id<<endl;
    }
    // TODO: Tìm thiết bị có tổng thời gian di chuyển lâu nhất
    if(req == "MTV"){
    }
    // TODO: Tìm thiết bị có vận tốc di chuyển trung bình nhanh nhất
    if(req == "MVV"){
    }
    // TODO: Tính số lượng thiết bị luôn di chuyển và không dừng
    if(req == "CNS"){
    }
    // TODO: Tính khoảng cách trung bình khi thu thập dữ liệu của tất cả các thiết bị
    if(req == "CAS"){
    }
    // TODO: Tìm thiết bị có hành trình dài nhất
    if(req == "LPV"){
    }
    // TODO: Tìm thiết bị có hành trình ngắn nhất
    if(req == "SPV"){
    }
    // Xóa các record của thiết bị <ID>
    if(req.substr(0,3) == "RVR"){
        int i = 0;
        int size = recList.getSize();
        string tmp = req.substr(3,req.length() - 3);
        while(i < size && tmp != recList.at(i).id){
            i++;
        }
        if(i != size){
            recList.remove(i);
            size = recList.getSize();
            for(i; i < size; i++){
                if(tmp == recList.at(i).id){
                    recList.remove(i);
                    size = recList.getSize();
                }
            }
            cout<<"success!"<<endl;
        } else cout<<"not found!"<<endl;
    }
    return true;
}
