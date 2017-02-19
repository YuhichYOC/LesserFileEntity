#include "stdafx.h"

#include "LesserFileEntity.h"

void TestMethod01()
{
    LesserFileEntity in;
    in.Init("D:\\TestDatas\\LesserFileEntity\\TestMethod01in.bin");
    in.ReadFile();
    LesserFileEntity out;
    out.Init("D:\\TestDatas\\LesserFileEntity\\TestMethod01out.bin");
    out.SetFileSize(in.GetFileSize());
    out.SetFileContents(in.GetFileContents());
    out.WriteFile();
}

int main(int argc, char * argv[])
{
    TestMethod01();
}