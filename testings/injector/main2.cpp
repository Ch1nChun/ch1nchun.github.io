#include <Windows.h>
#include <iostream>
#include "Information.h"
#include <commdlg.h>
#include <sstream>
#include "ManualMap.cpp"
using namespace std;

string mstrinj = "MasterInjector";
string mstrinj_title = "[MasterInjector]";
string info_title = "[INFO]";
string debug_title = "[DEBUG]";
string error_title = "[ERROR]";
string request_title = "[REQUEST]";


int main() {
    // Chars
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    char userName[UNLEN + 1];

    // Function to get users computer name
    GetComputerName(computerName);
    // Function to get users name
    Get_user_name(userName);
    string newTitle = mstrinj;
    SetConsoleTitle(newTitle.c_str());

    cout << "MasterInjector v2.5" << endl;
    cout << " " << endl; // Empty
    cout << info_title << " Build date: " << BUILD_DATE << endl;
    cout << " " << endl; // Empty
    Sleep(3000);
    cout << mstrinj_title << " Welcome back, " << userName << endl;
    cout << " " << endl;
    Sleep(2000);
    cout << mstrinj_title << " preparing injector " << mstrinj << endl;
    Sleep(2000);
    system("CLS");

    cout << request_title << " Enter your designated process name: " << endl;
    string processName;
    cin >> processName;
    system("CLS");
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Dynamic Link Libraries (*.dll)\0*.dll\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "dll";
    cout << " " << endl; // Empty line
    cout << mstrinj_title << " Select a DLL to inject: " << endl;

    if (GetOpenFileName(&ofn)) {
        cout << mstrinj_title << " Selected DLL: " << szFileName << endl;

        // Perform manual map injection
        ManualMapInjector injector(processName.c_str(), szFileName);
        if (injector.Inject()) {
            cout << mstrinj_title  << " Injection successful!" << endl;
        }
        else {
            cerr << mstrinj_title << " Injection failed." << endl;
        }
    }
    else {
        cerr << mstrinj_title << " File selection canceled." << endl;
    }

    return 0;
}
