#pragma once

#include "stdafx.h"

#include "WCharString.h"

class LesserFileEntity
{
private:

    string fullPath;

    ifstream ifile;

    ofstream ofile;

    int fileSize;

    unique_ptr<char> fileContents;

    bool readPrepared;

    bool writePrepared;

public:

    void Init(string arg);

    string GetFullPath();

    bool FindFile();

    void ReadFile();

    int GetFileSize();

    unique_ptr<char> GetFileContents();

    void SetFileSize(int arg);

    void SetFileContents(unique_ptr<char> arg);

    void WriteFile();

    void DeleteExistingFile();

    LesserFileEntity();

    ~LesserFileEntity();
};
