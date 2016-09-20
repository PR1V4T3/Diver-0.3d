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

void functionInfo(bool showInfo, string name, char startOrEnd = 's'){                    // functionInfo

     if(showInfo){

        char stCh[2] = {'='};

        cout << "\n";

        for(int i = 0; i < 60; i++) cout << stCh[0];

        cout << "\n";

        if(startOrEnd == 's') cout << "function.info: " << name << "() is running. ++\n";
        if(startOrEnd == 'e') cout << "function.info: " << name << "() has ended. --\n";

        for(int i = 0; i < 60; i++) cout << stCh[0];

        cout << "\n";
    }
}

void numberVievAdjusting(int number){

    // : 10000 |

    int i = 0;

    unsigned int howManySpaces;

    if(number < 10){

        howManySpaces = 3;

    }else if(number < 100){

        howManySpaces = 2;

    }else if(number < 1000){

        howManySpaces = 1;

    }else if(number < 10000){

        howManySpaces = 0;
    }

    cout << ": " << number;

    for(int i = 0; i < howManySpaces; i++) cout << " ";

    cout << " | ";
}

bool checkIsExist(string filePath, bool showInfo = false){                                                      // DONE

    functionInfo(showInfo, "checkIsExitst");

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

    functionInfo(showInfo, "checkIsExitst", 'e');

    return bufor;
}

void showContent(string filePath, bool showInfo = false){                                                       // DONE

    functionInfo(showInfo, "showContent");

    if(checkIsExist(filePath, showInfo) == true){

        fstream textFile;
        string content = "";
        bool endLoop = false;
        int line = 0;

        textFile.open(filePath.c_str());


        for(int i = 0; i < 50; i++) cout << "=";

        cout << "\n";

            do{

                if(textFile.eof() == false){

                    line++;
                    getline(textFile, content);
                    numberVievAdjusting(line);
                    cout <<  content << endl;

                }else endLoop = true;

            }while(endLoop == false);

            textFile.close();

        for(int i = 0; i < 50; i++) cout << "=";

        cout << "\n";

    }else cout << "Missing file in showContent() \n";

    functionInfo(showInfo, "showContent",'e');
}

int findInFile(string filePath, string keyWord, bool showInfo = false){                                         // TO OPTIMALIZATION // idk what did I want change :/

    functionInfo(showInfo, "findInFile");

    if(checkIsExist(filePath.c_str(), showInfo) == true){

    fstream textFile;
    textFile.open(filePath.c_str());

    string downloadedWord;
    int positionInFile;
    int lineInFile = 0;
    bool endLoop = false;
    bool isFound = false;

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
                isFound = true;

                smallTest = textFile.tellg();

                if(showInfo){

                    cout << "DBG.info: actual position in file: " << smallTest << endl;                                            /// VERY IMPORTANT PLACE
                    cout << "In line: " << lineInFile << " has found: " << downloadedWord << endl;
                    cout << "Keyword's line position in file: " << positionInFile << endl;
                }

            }else if(showInfo) cout << "In line: " << lineInFile << " hasn't found keyword.\n\n";

        }else endLoop = true;

    }while(endLoop == false);

    textFile.close();

    if(isFound == false) cout << "The keyword hasn't found.\n";
    else cout << "The keyword has found\n";

    functionInfo(showInfo, "findInFile", 'e');

    return positionInFile;

    }
}

int saveToFile(string filePath, int positionInFile, bool showInfo = false){                                     // TODO - pracowac przede wszystkim tutaj

    functionInfo(showInfo, "saveToFile");

    string upload;
    fstream textFile;
    textFile.open(filePath.c_str());

    textFile.seekp(positionInFile, ios_base::beg);

    cin >> upload;
    textFile << endl;

    textFile.close();

    functionInfo(showInfo, "saveToFile", 'e');

    return textFile.tellp();
}

int sendContent(string filePath, int positionInFile, char mode, bool showInfo = false){                         // TODO

    functionInfo(showInfo, "sendContent",1);

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

    functionInfo(showInfo, "sendContent",1);

    return temporaryFile.tellg();

}

int main(){

    bool showInfo = 0;
    string keyword = "<div id=name>";

    functionInfo(showInfo, "main()");

    showContent("test_sets/index.html", showInfo);

    cout << "The Keyword is: ";
    //cin >> keyword;

    findInFile("test_sets/index.html", keyword, showInfo); // sometimes makes issue with reaching eof, ikd what to do


    functionInfo(showInfo, "main()", 'e');

}

















