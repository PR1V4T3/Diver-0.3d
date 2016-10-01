/*
  ______________________________________________
 |                                              |
 |                  :: DIVER ::                 |
 |            the HTML/CSS generator            |
 |                                              |
 |              version 0.4.1 Alpha             |
 |                                              |
 |______________________________________________|

*/

#include <iostream>
#include <fstream>
#include <cstdlib>

    using namespace std;

struct data{

    string date = "DATE";
    string topic = "TOPIC";
    string content = "CONTENT";
    string diverSymbol = "<!-- DIVER_INIT -->";
};

void functionInfo(bool showInfo, string name, char startOrEnd = 's'){                                           // DONE

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

void numberVievAdjusting(int number){                                                                           // DONE

    //functionInfo(true, "numerViewAdjusting");

    // : 10000 |

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


    //functionInfo(true, "numerViewAdjusting", 'e');
}

bool checkIsExist(string filePath, bool showInfo = false){                                                      // DONE

    functionInfo(showInfo, "checkIsExitst");

    fstream textFile;
    textFile.open(filePath.c_str());

    bool bufor;

    cout << endl;
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

        cout << endl;

        for(int i = 0; i < 60; i++) cout << "#";

        cout << endl;

            do{

                if(textFile.eof() == false){

                    line++;
                    getline(textFile, content);
                    numberVievAdjusting(line);
                    cout <<  content << endl;

                }else endLoop = true;

            }while(endLoop == false);

            textFile.close();

        for(int i = 0; i < 60; i++) cout << "#";

        cout << "\n";

    }else cout << "Missing file in showContent() \n";

    functionInfo(showInfo, "showContent",'e');
}

int findInFile(string filePath, string keyWord, bool mode, bool showInfo = false){                              // DONE

    functionInfo(showInfo, "findInFile");

    if(checkIsExist(filePath.c_str(), showInfo) == true){

    fstream textFile;
    textFile.open(filePath.c_str());

    string downloadedWord;
    int positionInFileAK;
    int positionInFileBK;
    int lineInFile = 0;
    bool endLoop = false;
    bool isFound = false;

    cout << "Parser is looking for: " << keyWord << endl;

    do{

        if(textFile.eof() == false){

            lineInFile++;
            positionInFileBK = textFile.tellg(); // AK means "After Keyword"

            getline(textFile, downloadedWord);

            if(showInfo) cout << "Parser is comparing: " << downloadedWord << "\n";

            if(downloadedWord == keyWord){

                endLoop = true;
                isFound = true;

                positionInFileAK = textFile.tellg(); // BK means "BeforeKeyword

            }else if(showInfo) cout << "In line: " << lineInFile << " hasn't found keyword.\n\n";

        }else endLoop = true;

    }while(endLoop == false);

    textFile.close();

    if(isFound == true){

        cout << "The keyword has found\n";

        if(showInfo){

            cout << endl;
            cout << "############################################################\n";
            cout << "DBG.info: position before keyword: " << positionInFileBK << endl;
            cout << "DBG.info: position after keyword: " << positionInFileAK << endl;                                          /// VERY IMPORTANT PLACE
            cout << "In line: " << lineInFile << " has found: " << downloadedWord << endl;
            cout << "############################################################\n";

        }

        functionInfo(showInfo, "findInFile", 'e');

            switch(mode){

                case 0:
                return positionInFileBK;
                break;

                case 1:
                return positionInFileAK;
                break;

                default:
                break;

            }

        }else{

            cout << "The keyword hasn't found.\n";
            return -1;

        }
    }
}

void backupContent(string filePath, string backupFilePath, int positionInFile, bool showInfo = false){          // DONE

    functionInfo(showInfo, "backupContent");

    if(checkIsExist(filePath, showInfo) == true){

        string bufor;
        bool endLoop = false;

        fstream textFile;
        textFile.open(filePath.c_str());

        fstream backupFile;
        backupFile.open(backupFilePath.c_str(), ios::trunc | ios::out | ios::in);

        textFile.seekg(positionInFile, ios_base::beg);
        backupFile.seekp(0, ios_base::beg);

            do{

                if(textFile.eof() == false){

                    getline(textFile, bufor);
                    backupFile << bufor << endl;

                }else endLoop = true;

            }while(endLoop == false);

            textFile.close();
            backupFile.close();

    }else cout << "Missing file in backupContent() \n";

    functionInfo(showInfo, "backupContent",'e');
}

void generateBlock(string filePath, data filler, int positionInFile = 0, bool showInfo = false){                // DONE

    if(checkIsExist(filePath.c_str(), showInfo) == true){

        functionInfo(showInfo, "generator");

        cout << "Path: " << filePath << " Position: " << positionInFile << endl;

        fstream textFile;
        textFile.open(filePath.c_str());

        textFile.seekp(positionInFile, ios_base::beg);

        string date = "<div id=\"data\"> " + filler.date + " </div>";
        string topic = "<div id=\"topic\"> " + filler.topic + " </div>";
        string content = "<div id=\"content\"> " + filler.content + " </div>";

        textFile << date << endl;
        textFile << topic << endl;
        textFile << content << endl;

        textFile << endl << filler.diverSymbol << endl << endl;

        textFile.close();

        functionInfo(showInfo, "generator", 'e');

    }
}

void putBackup(string filePath, string backupFilePath, int positionInFile, bool showInfo = false){              // DONE

    functionInfo(showInfo, "backupContent");

    if(checkIsExist(filePath, showInfo) == true){

        string content = "";
        string bufor;
        bool endLoop = false;

        fstream textFile;
        textFile.open(filePath.c_str());

        fstream backupFile;
        backupFile.open(backupFilePath.c_str());

        textFile.seekg(positionInFile, ios_base::beg);
        backupFile.seekp(0, ios_base::beg);

            do{

                if(backupFile.eof() == false){

                    getline(backupFile, bufor);
                    textFile << bufor << endl;

                }else endLoop = true;

            }while(endLoop == false);

            textFile.close();
            backupFile.close();

    }else cout << "Missing file in backupContent() \n";

    functionInfo(showInfo, "backupContent",'e');
}

string write(string name, string endKeyword = "-e", bool showInfo = false){                                     // TODO: new method for save return values, all is in one line without new line charachters

    functionInfo(showInfo, "write");

    string bufor = "";
    string content = "";
    bool endLoop = false;

    for(int i = 0; i < 60; i++) cout << "#";

    cout << "\n\n";
    cout << "# You're writting in: " << name << "\n\n";

    if(name == "Date" || name == "date") cout << "Date Format: \n\n\tdd.mm.yy " << endKeyword << "\n" << "or" << "\n" << "\tdd mm yy " << endKeyword << "\n" << "or" << "\n" << "\tdd/mm/yy " << endKeyword << "\n\n";


    cout << "# If you want go to next step, you should write \" " << endKeyword << " \"; at end of your text and separate it by pressing spacebar.\n\n";
    cout << ": ";
    do{

        cin >> bufor;

        if(bufor != endKeyword) content = content + bufor;
        else endLoop = true;

    }while(endLoop == false);

    for(int i = 0; i < 60; i++) cout << "#";

    cout << "\n";

    functionInfo(showInfo, "write", 'e');

    return content;
}

int main(){

    bool showInfo = true;

    string endKeyword = "-e";

    string filePath       = "test_sets/index.html";
    string backupFilePath = "test_sets/backup.txt";

    data sample;

    sample.date = write("Date", endKeyword, showInfo);
    sample.topic = write("Topic", endKeyword, showInfo);
    sample.content = write("Content", endKeyword, showInfo);
    sample.diverSymbol = "<!-- DIVER_INIT -->";

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    functionInfo(showInfo, "main");

    showContent(filePath, showInfo);

    // 0 = before keyword, 1 = after keyword

    ///
    backupContent(filePath, backupFilePath, findInFile(filePath, sample.diverSymbol, 1, false), showInfo);
    ///
    generateBlock(filePath, sample, findInFile(filePath, sample.diverSymbol, 0, false), showInfo);
    ///
    putBackup(filePath, backupFilePath, findInFile(filePath, sample.diverSymbol, 1, false), showInfo);
    ///


    functionInfo(showInfo, "main", 'e');

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return 0;

}

















