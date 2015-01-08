/*
* 管理系统层
* 实现对文件的管理
* 面向应用提供服务
*/

#include "BasicService.h"
// #include <iostream>
// #include <string>
// #include <iomanip>
using namespace std;

struct Dir{
	string name;
	struct Dir * next;
	struct Dir * child;
};

class ManageSys
{
public:
	static Dir * dirHead;
	static Dir * needNode;
	static int curpos;

	static Dir* searchCurDir(Dir* curDir, string name);
	static bool openFile(string curDir, string name);
	static void test_4_searchNode();
	static void searchNode(string name);
	static void searchNodeCore(Dir * cur, string name);
	static void test_3_writeDir();
	static void writeDir();
	static void writeDirCore(Dir * cur);
	static void outDir();
	static void outDirCore(Dir * cur);
	static void test_2_readDir();
	static void readDir();
	static void readDirCore(Dir * cur);
	
	static void init();
	static void test_1_login();
	static void test();
	static bool login(string name, string key);
};