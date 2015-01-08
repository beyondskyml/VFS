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
	int static curpos;
	
	void static test_4_searchNode();
	void static searchNode(string name);
	void static searchNodeCore(Dir * cur, string name);
	void static test_3_writeDir();
	void static writeDir();
	void static writeDirCore(Dir * cur);
	void static outDir();
	void static outDirCore(Dir * cur);
	void static test_2_readDir();
	void static readDir();
	void static readDirCore(Dir * cur);
	
	void static init();
	void static test_1_login();
	void static test();
	bool static login(string name, string key);
};