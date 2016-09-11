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

bool checkIsExist(string filePath, bool showInfo = false){                                                      // DONE

    if(showInfo) cout << "function.info: checkIsExist() is running \n";

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

    if(showInfo) cout << "function.info: checkIsExitst has ended \n";

    return bufor;
}

void showContent(string filePath, bool showInfo = false){                                                       // DONE

    if(showInfo) cout << "function.info: showContent is running \n";

    if(checkIsExist(filePath, showInfo) == true){

        fstream textFile;
        string content = "";
        bool endLoop = false;

        textFile.open(filePath.c_str());

            do{

                if(textFile.eof() == false){

                    getline(textFile, content);
                    cout << "* " <<  content << endl;

                }else endLoop = true;

            }while(endLoop == false);

            textFile.close();

    }else cout << "Missing file in showContent() \n";

    if(showInfo) cout << "function.info: showContent() has ended \n";
}

int findInFile(string filePath, string keyWord, bool showInfo = false){                                         // TO OPTIMALIZATION

    if(showInfo) cout << "function.info: findInFile() is running \n";

    if(checkIsExist(filePath.c_str(), showInfo) == true){

    fstream textFile;
    textFile.open(filePath.c_str());

    string downloadedWord;
    int positionInFile;
    int lineInFile = 0;
    bool endLoop = false;

    cout << "Parser is looking for: " << keyWord << endl;

    do{

        if(textFile.eof() == false){

            lineInFile++;
            positionInFile = textFile.tellg();

            getline(textFile, downloadedWord);

            if(showInfo) cout << "Parser is comparing: " << downloadedWord << "\n";

            if(downloadedWord == keyWord){

                endLoop = true;

                if(showInfo){   cout << "In line: " << lineInFile << " has found: " << downloadedWord << endl;
                                cout << "Position in file: " << positionInFile << endl;}

            }else if(showInfo) cout << "In line: " << lineInFile << " hasn't found keyword.\n\n";

        }else endLoop = true;

    }while(endLoop == false);

    textFile.close();

    if(showInfo) cout << "function.info: findInFile() has ended \n";

    return positionInFile;

    }
}

int saveToFile(string filePath, int positionInFile, bool showInfo = false){                                     // TODO - pracowac przede wszystkim tutaj

    cout << "function.info: saveToFile() is running \n";

    string upload;
    fstream textFile;
    textFile.open(filePath.c_str());

    textFile.seekp(positionInFile, ios_base::beg);

    cin >> upload;
    textFile << endl;

    textFile.close();

    cout << "function.info: saveToFile() has ended \n";

    return textFile.tellp();
}

int sendContent(string filePath, int positionInFile, char mode, bool showInfo = false){                         // TODO

    cout << "||| sendContent is running.. |||\n";

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

    return temporaryFile.tellg();

}

int main(){

    showContent("index.html", 1);
    findInFile("index.html", "<head>", 1); // something issue with reaching eof

}






















