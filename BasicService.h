/*
* 基础服务层
* 为VFS提供基础的创建、读写、关闭文件操作、命令转换操作。
* 但不是为程序提供的文件操作接口。
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// 块大小 字节
#define blockSize 256
// 总块数 10MB
#define blockNum  10 * 1024 * 1024
// 启动块 开始块号	存储用户信息
#define bootBlockNo 0
// 超级块 开始块号	存储目录信息
#define superBlockNo 1
// 文件信息块 开始块号	存储文件信息
#define infoBlockNo 2
// 数据块 开始块号		存储文件内容
#define dataBlockNo 128 * 256
using namespace std;



class BasicService
{
private:
	/*data*/
	static int emptyBlockNum;					// 空闲块数量
	static bool blockStatus[blockNum];			// 块使用情况，TRUE 可用， FALSE 已用
	static bool infoBlockStatus[dataBlockNo - infoBlockNo];			// 信息块使用情况，TRUE 可用， FALSE 已用
	
	static int fileInfoBlockNo;						// 指定的文件信息块号码
	
	static bool isWrite;						// 可写标志位 true不论是否有信息都可写
	static string fileName;
	static string fileUser;
	static int fileBlockNo[20];



	static fstream iofile;

public:
	/*test*/
	void static test_1_createFile_shoule_get_true();
	void static test_2_writeFile();
	void static test_3_saveFileInfo();
	void static test_4_writeInfoString();
	void static test_5_writeUser();
	void static test_6_readUser();
	// void static test_9_searchInfoNo();
	void static test();

	string static dir[16][3];
	void static test_8_readDir();
	void static readDir();
	void static test_7_writeDir();
	void static writeDir();
	
	string static user[11][2];
	void static readUser(); 
	void static writeUser();
	void static setFileName(string _fileName);
	void static setFileUser(string _fileUser);
	void static init();
	bool static saveFileInfo();
	void static writeFileInfo();
	void static writeInfoString(string writeString);
	bool static calDataBlock(string fileString);
	int  static infoNo;
	bool static searchInfoNo(string searchName);
	bool static createFile();
	bool static writeFile(string fileString);
};

