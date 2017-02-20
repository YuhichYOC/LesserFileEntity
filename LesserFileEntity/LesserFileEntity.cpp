#include "stdafx.h"

#include "LesserFileEntity.h"

void LesserFileEntity::Init(string arg)
{
    fullPath = arg;
}

string LesserFileEntity::GetFullPath()
{
    return fullPath;
}

bool LesserFileEntity::FindFile()
{
    WCharString path;
    path = path.Value(fullPath);
    unique_ptr<wchar_t> filePath = move(path.ToWChar());
    if (PathFileExists((LPCWSTR)filePath.get())) {
        return true;
    }
    else {
        return false;
    }
}

void LesserFileEntity::ReadFile()
{
    if (writePrepared) {
        return;
    }
    ifile = ifstream(fullPath, ios::in | ios::binary);
    ifile.seekg(0, istream::end);
    streamoff endPos = ifile.tellg();
    ifile.seekg(0, istream::beg);
    streamoff startPos = ifile.tellg();
    fileSize = (int)(endPos - startPos);
    readPrepared = true;
    unique_ptr<char> readBuffer(new char[fileSize]);
    ifile.read(readBuffer.get(), fileSize);
    fileContents = move(readBuffer);
    ifile.close();
}

int LesserFileEntity::GetFileSize()
{
    return fileSize;
}

unique_ptr<char> LesserFileEntity::GetFileContents()
{
    unique_ptr<char> ret(new char[fileSize]);
    for (int i = 0; i < fileSize; i++) {
        ret.get()[i] = fileContents.get()[i];
    }
    return ret;
}

void LesserFileEntity::SetFileSize(int arg)
{
    fileSize = arg;
}

void LesserFileEntity::SetFileContents(unique_ptr<char> arg)
{
    fileContents = move(arg);
}

void LesserFileEntity::WriteFile()
{
    if (readPrepared) {
        return;
    }
    ofile = ofstream(fullPath, ios::out | ios::binary);
    writePrepared = true;
    ofile.write(fileContents.get(), fileSize);
    ofile.close();
}

void LesserFileEntity::DeleteExistingFile()
{
    WCharString path;
    path = path.Value(fullPath);
    unique_ptr<wchar_t> filePath = move(path.ToWChar());
    if (FindFile()) {
        int ret = DeleteFile((LPCWSTR)filePath.get());
    }
}

LesserFileEntity::LesserFileEntity()
{
    readPrepared = false;
    writePrepared = false;
}

LesserFileEntity::~LesserFileEntity()
{
}