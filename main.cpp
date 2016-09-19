/*
  ______________________________________________
 |                                              |
 |                  :: DIVER ::                 |
 |            the HTML/CSS generator            |
 |                                              |
 |                version 0.3dev                |
 |                                              |
 |______________________________________________|

*/

#include <iostream>
#include <fstream>
#include <cstdlib>

    using namespace std;

void fi(string name, bool beg_end = 0){                    // functionInfo

    //////////////////////////
    //                      //
    //  0 = beg, 1 = end    //
    //                      //
    //////////////////////////

    char stCh[2] = {'='};

    cout << "\n";

    for(int i = 0; i < 60; i++) cout << stCh[0];

    cout << "\n";

    if(beg_end == 0) cout << "function.info: " << name << "() is running.\n";
    if(beg_end == 1) cout << "function.info: " << name << "() has ended.\n";

    for(int i = 0; i < 60; i++) cout << stCh[0];

    cout << "\n";
}

bool checkIsExist(string filePath, bool showInfo = false){                                                      // DONE

    if(showInfo) fi("checkIsExitst");

    fstream textFile;
    textFile.open(filePath.c_str());

    bool bufor;

    cout << "Searching for: " << filePath << endl;

    if(textFile.is_open() == true){

        if(showInfo) cout << "file.status: good\n";
        bufor = true;

    }else{

        if(showInfo) cout << "file.status: failed \n" << "The file is missing or has broken \n";
        bufor = false;
    }

    textFile.close();

    if(showInfo) fi("checkIsExitst",1);

    return bufor;
}

void showContent(string filePath, bool showInfo = false){                                                       // DONE

    if(showInfo) fi("showContent");

    if(checkIsExist(filePath, showInfo) == true){

        fstream textFile;
        string content = "";
        bool endLoop = false;

        textFile.open(filePath.c_str());

        cout << "*\n";

            do{

                if(textFile.eof() == false){

                    getline(textFile, content);
                    cout << "* " <<  content << endl;

                }else endLoop = true;

            }while(endLoop == false);

            textFile.close();

    }else cout << "Missing file in showContent() \n";

    if(showInfo) fi("showContent",1);
}

int findInFile(string filePath, string keyWord, bool showInfo = false){                                         // TO OPTIMALIZATION // idk what did I want change :/


    if(showInfo) fi("findInFile");

    if(checkIsExist(filePath.c_str(), showInfo) == true){

    fstream textFile;
    textFile.open(filePath.c_str());

    string downloadedWord;
    int positionInFile;
    int lineInFile = 0;
    bool endLoop = false;

    cout << "Parser is looking for: " << keyWord << endl;

    int smallTest;

    do{

        if(textFile.eof() == false){

            lineInFile++;
            positionInFile = textFile.tellg();

            getline(textFile, downloadedWord);

            if(showInfo) cout << "Parser is comparing: " << downloadedWord << "\n";

            if(downloadedWord == keyWord){

                endLoop = true;

                smallTest = textFile.tellg();

                cout << "DBG.info: pstn in file: " << smallTest << endl;                                            /// BARDZO ISTOTNE MIEJSCE

                if(showInfo){   cout << "In line: " << lineInFile << " has found: " << downloadedWord << endl;
                                cout << "Position in file: " << positionInFile << endl;}

            }else if(showInfo) cout << "In line: " << lineInFile << " hasn't found keyword.\n\n";

        }else endLoop = true;

    }while(endLoop == false);

    textFile.close();

    if(showInfo) fi("findInFile",1);

    return positionInFile;

    }
}

int saveToFile(string filePath, int positionInFile, bool showInfo = false){                                     // TODO - pracowac przede wszystkim tutaj

    if(showInfo) fi("saveToFile");

    string upload;
    fstream textFile;
    textFile.open(filePath.c_str());

    textFile.seekp(positionInFile, ios_base::beg);

    cin >> upload;
    textFile << endl;

    textFile.close();

    if(showInfo) fi("saveToFile",1);

    return textFile.tellp();
}

int sendContent(string filePath, int positionInFile, char mode, bool showInfo = false){                         // TODO

    if(showInfo) fi("sendContent",1);

    fstream textFile;
    fstream temporaryFile;

    if(checkIsExist("temporaryFile.txt") == false) system("gedit temporaryFile.txt");

    textFile.open(filePath.c_str(), ios::out | ios::in );
    temporaryFile.open("temporaryFile.txt", ios::trunc | ios::out | ios::in);

    string contentBufor;

    textFile.seekg(positionInFile, ios_base::beg);

    if( mode == 's') do{

                        cout << "|| Mode: send\n";
                        getline(textFile, contentBufor);
                        temporaryFile << contentBufor << endl;

                    }while(textFile.eof() == false);

    if(mode == 'g') {

                    temporaryFile.seekg(0, ios::beg);
                    bool endLoop = true;

                    do{

                        if(textFile.eof() == false){

                            cout << textFile.tellg() << endl;
                            cout << temporaryFile.tellp() << endl;
                            cout << contentBufor << endl;
                            cout << "|| Mode: get\n";
                            getline(temporaryFile, contentBufor);
                            textFile << contentBufor << endl;

                        }else endLoop = true;

                    }while(endLoop == false);

                    }

    textFile.close();
    temporaryFile.close();

    if(showInfo) fi("sendContent",1);

    return temporaryFile.tellg();

}

int main(){

    bool showInfo = true;

    if(showInfo) fi("main()", 0);


    showContent("test_sets/index.html", showInfo);
    findInFile("test_sets/index.html", "<head>", showInfo); // something issue with reaching eof


    if(showInfo) fi("main()", 1);

}

// function.info: sampleFunction() is running with: <sample> | <sample> | <sample>

















