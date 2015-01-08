/*
* 基础服务层
* 为VFS提供基础的创建、读写、关闭文件操作、命令转换操作。
* 但不是为程序提供的文件操作接口。
*/

// 注意： 文件打开后一定要关闭

#include "BasicService.h"
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <iomanip>

/*
* // 块大小 字节
* #define blockSize 256
* // 总块数 10MB
* #define blockNum  10 * 1024 * 1024
* // 启动块 开始块号
* #define bootBlockNo 0
* // 超级块 开始块号
* #define superBlockNo 1
* // 文件信息块 开始块号
* #define infoBlockNo 2
* // 数据块 开始块号
* #define dataBlockNo 128 * 256
*/

using namespace std;

// 初始化静态数据成员
int BasicService::emptyBlockNum = blockNum;
bool BasicService::blockStatus[blockNum];
bool BasicService::infoBlockStatus[dataBlockNo - infoBlockNo];			// 信息块使用情况，TRUE 可用， FALSE 已用
int BasicService::fileInfoBlockNo = 0;						// 指定的文件信息块号码
int BasicService::fileBlockNo[20];
string BasicService::fileName;
string BasicService::fileUser;
bool BasicService::isWrite = false;						// 可写标志位 true不论是否有信息都可写

fstream BasicService::iofile;

void BasicService::init(){
	for (int i = dataBlockNo; i < blockNum; ++i){
		blockStatus[i] = true;
	}
	for (int j = 0; j < dataBlockNo - infoBlockNo; ++j){
		infoBlockStatus[j] = true;
	}

	readUser();
	readDir();
}
void BasicService::test(){
	// init();
	// BasicService::test_1_createFile_shoule_get_true();
	// BasicService::test_2_writeFile();
	// BasicService::test_3_saveFileInfo();
	// BasicService::test_4_writeInfoString();
	
	BasicService::test_5_writeUser();
	BasicService::test_6_readUser();
	BasicService::test_7_writeDir();
	BasicService::test_8_readDir();
	system("pause");
}



/******************************
* 从块设备读取目录信息至数组
*******************************/
void BasicService::test_8_readDir(){
	readDir();
	for (int i = 0; i < 16; ++i){
		cout<<"dir name: " <<setw(11)<<setiosflags(ios::left)<<dir[i][0]
			<<"next: "  <<setw(2)<<dir[i][1]
			<<"child: "  <<setw(2)<<dir[i][2]
			<<endl;
	}
	cout<<"success ^_^"<<endl;
}
void BasicService::readDir(){
	iofile.open("vfs.txt", ios::in);
	iofile.seekg(superBlockNo * blockSize, ios::beg);
	string tName;
	string tNext;
	string tChild;
	for (int i = 0; i < 16; ++i){
		//读取用户名、密码
		iofile>>tName>>tNext>>tChild;
		if (tName == "0")
			break;
		dir[i][0] = tName;
		dir[i][1] = tNext;
		dir[i][2] = tChild;
	}
	iofile.close();
}

/*************************
* 将目录数组写入块设备
**************************/
void BasicService::test_7_writeDir(){
	dir[0][0] = "sky";   dir[0][1] = "1"; dir[0][2] = "0";
	dir[1][0] = "long";  dir[1][1] = "1"; dir[1][2] = "1";
	dir[2][0] = "doc";   dir[2][1] = "0"; dir[2][2] = "0";
	dir[3][0] = "f.txt"; dir[3][1] = "0"; dir[3][2] = "0";

	writeDir();
	cout<<"success ^_^"<<endl;
}
string BasicService::dir[16][3];
void BasicService::writeDir(){
	iofile.open("vfs.txt", ios::in | ios::out);
	iofile.seekp(superBlockNo * blockSize, ios::beg);
	for (int i = 0; i < 16; ++i){
		// 输出，注意长度控制
		iofile<<setw(11)<<setiosflags(ios::left)<<dir[i][0] 
			<<setw(2)<<setiosflags(ios::left)<<dir[i][1]
			<<setw(2)<<setiosflags(ios::left)<<dir[i][2];
	}
	iofile<<0;
	iofile.close();
}


/****************************
* 从块设备读取用户信息至数组
*****************************/
string BasicService::user[11][2];
void BasicService::test_6_readUser(){
	readUser();
	for (int i = 0; i < 11; ++i){
		cout<<"user name: " <<setw(11)<<setiosflags(ios::left)<<user[i][0] 
			<<"password: "  <<setw(11)<<user[i][1]
			<<endl;
	}
	cout<<"success ^_^"<<endl;
}
void BasicService::readUser(){
	iofile.open("vfs.txt", ios::in);
	string tName;
	string tPassword;
	for (int i = 0; i < 11; ++i){
		//读取用户名、密码
		iofile>>tName>>tPassword;
		if (tName == "0"){
			iofile.close();
			return;
		}
			
		user[i][0] = tName;
		user[i][1] = tPassword;
	}
	iofile.close();
}

/*****************************
* 将用户信息数组写入块设备
******************************/
void BasicService::test_5_writeUser(){
	user[0][0] = "001"; user[0][1] = "100";
	user[1][0] = "002"; user[1][1] = "200";
		writeUser();
	cout<<"success ^_^"<<endl;
}
void BasicService::writeUser(){
	iofile.open("vfs.txt", ios::in | ios::out);
	iofile.seekp(0, ios::beg);
	for (int i = 0; i < 11; ++i){
		// 输出，注意长度控制
		iofile<<setw(11)<<setiosflags(ios::left)<<user[i][0] 
			<<setw(11)<<setiosflags(ios::left)<<user[i][1];
	}
	iofile<<0;
	iofile.close();
}

// ***********************************
void BasicService::setFileName(string _fileName){
	fileName = _fileName;
}
void BasicService::setFileUser(string _fileUser){
	fileUser = _fileUser;
}


void BasicService::test_1_createFile_shoule_get_true(){
	if (createFile())
		cout<<"success ^_^" <<endl;
	else
		cout<<"fails XD" <<endl;
}
void BasicService::test_2_writeFile(){
	string testString;
	// testString = "This is a test string , to check writefile().";
	testString = "I need to make it clear, right from the start, that I do not have 'Bieber Fever'. But could I (and you) develop a case after seeing the pop mega-superstar's new movie? Well, as the title says, 'Never Say Never'.The film chronicles Bieber's life, from the time he was a 'Baby, Baby, Baby' - singing for his family and banging on drums - to performing in front of sold-out crowds across the globe. We get a lot of home movies, enough songs to make even the most diehard fans happy and backstage, behind-the-scenes video. The movie is part biography - part concert film.I didn't know much about Bieber's background before I saw the film, and his story is interesting. One of the strengths of the movie are all the interviews with fans, who simply LOVE this guy. The film does a great job showing the joy that Bieber and his music bring to millions of (mostly) young girls around the world.And that includes the 200 or so screaming fans I was surrounded by in the theater where I saw the movie. I do wish I had brought some earplugs - not because of what was happening on the screen, but what was happening in the audience. But I do have to give credit to the girl who was sitting next to me: She knew every word of every song. Chances are you may have one or two of those fans around you when you watch the DVD (or you may be one). Bieber is joined on stage by Miley Cyrus, Jaden Smith and Usher, who is part of  and appears throughout the film.";
	// cout<<testString.length()<<endl;
	// cout<< emptyBlockNum << endl << blockStatus[2] << endl;
	if (writeFile(testString))
		cout<<"success ^_^" <<endl;
	else
		cout<<"fails XD" <<endl;
}

void BasicService::test_3_saveFileInfo(){
	isWrite = false;
	setFileName("haha");
	setFileUser("001");
	fileBlockNo[0] = dataBlockNo;
	fileBlockNo[1] = dataBlockNo + 1;
	fileBlockNo[2] = dataBlockNo + 2;
	fileBlockNo[3] = dataBlockNo + 3;
	fileBlockNo[4] = dataBlockNo + 4;
	fileBlockNo[5] = dataBlockNo + 5;
	fileBlockNo[6] = dataBlockNo + 6;
	fileBlockNo[7] = dataBlockNo + 7;
	fileBlockNo[8] = dataBlockNo + 8;
	if(saveFileInfo())
		cout<<"success ^_^" <<endl;
	else
		cout<<"fails XD" <<endl;
}
void BasicService::test_4_writeInfoString(){

	writeInfoString("user1");
	iofile.close();
}
// ~BasicService();
	// 应该先使用calBlockNo函数将块号保存在fileBlockNo中，再使用该函数保存
bool BasicService::saveFileInfo(){
	iofile.open("vfs.txt", ios::in | ios::out);
		if (!isWrite){	// 如果是新建文件
		iofile.seekp(infoBlockNo * blockSize);
		for (int i = 0; i < dataBlockNo - infoBlockNo; ++i){
			if(infoBlockStatus[i]){		// 查找空块并分配
				// 将文件信息写入该块
				writeFileInfo();
				// 该块已占用
				infoBlockStatus[i] = false;
				iofile.close();
				return true;
			}
		}
		iofile.close();
		return false;
	}
	else{		// 如果不是新建文件
		iofile.seekp(fileInfoBlockNo * blockSize);
		// 将文件信息写入该块
		writeFileInfo();	// 此时文件的块号应该已经保存在fileBlockNo[]中
		iofile.close();
		return true;
	}
}
void BasicService::writeFileInfo(){
	writeInfoString(fileName);
	writeInfoString(fileUser);
	cout<<"2\n";
	// 将分配的块号写入文件
	for (int i = 0; i < 20; ++i){		
		//每个块保存20个块号，留下12位可用于间接寻址
		//每个块号最大10为，多出一位空格，用于读取时区分
		iofile<<setw(11)<<setiosflags(ios::left)<<fileBlockNo[i];
	}
}
void BasicService::writeInfoString(string writeString){
	iofile<<setw(11)<<setiosflags(ios::left)<<writeString;
}

// 查找文件存储的块号
bool BasicService::calDataBlock(string fileString){
	// 计算文件长度是否超长
	int needBlockNum = fileString.length() % blockSize;
	if(needBlockNum > 10)
		return false;	//文件超长，返回失败
	if(!isWrite){ // 如果是新建文件
		int curPos = 0;
		for (int i = 0; i < dataBlockNo - infoBlockNo; ++i){
			if(infoBlockStatus[i]){
				infoBlockStatus[i] = false;
				fileBlockNo[curPos] = i + dataBlockNo;
				curPos++;
			}
			if (curPos + 1 == 10){	// 给每个文件分配最大块数10
				return true;
			}
		}
		return false;//剩余空闲块不够用
	}
	else{
		ifstream iFile;
		iFile.open("vfs.txt", ios::in);
		
		// 如果是覆盖写入文件
		searchInfoNo(fileName);	// 注意fileName是否已经更新
		iFile.seekg(fileInfoBlockNo * blockSize + 24);
		for (int i = 0; i < 10; ++i){
			iFile>>fileBlockNo[i];
		}
		return true;//读取块号完毕
	}	
}


/*void BasicService::test_9_searchInfoNo(){

}*/
// 文件存在 返回true 否则返回false
// 找文件信息块，从中找到文件数据保存的块。
int BasicService::infoNo;
bool BasicService::searchInfoNo(string searchName){
	string name;
	iofile.open("vfs.txt", ios::in);
	for (int i = 0; i < dataBlockNo - infoBlockNo && infoBlockStatus[i] == false; ++i){
		iofile.seekg((infoBlockNo + i) * blockSize);
		iofile>>name;
		if (searchName == name){
			infoNo = i + infoBlockNo;
			iofile.close();
			return true;
		}
	}
	iofile.close();
	infoNo = -1;
	return false;
}

// 打开虚拟文件系统，若不存在则创建，若存在则清空
bool BasicService::createFile(/* char * url*/){
	// 尝试打开文件
	//fstream ioFile(url, ios::out | ios::noreplace);
	ofstream ioFile;
	ioFile.open("vfs.txt", ios::out); //输出方式打开文件，不存在则创建
	// 判断是否成功
	if (! ioFile){
		// 失败返回false
		ioFile.close();
		return false;
	}
	// 初始化
	init();
		// 成功返回TRUE
		ioFile.close();
	return true;  
}

// 将字符串写入空闲块
// 注意：调用此函数前必须调用createFile函数,以确保初始化文件系统
// 字符串中的换行要用\t表示(\r\t?)
bool BasicService::writeFile(string fileString){
	ofstream oFile;
	oFile.open("vfs.txt", ios::app); //输出方式打开文件，不存在则创建
	// 判断是否成功
	if (! oFile){
		// 失败返回false
		oFile.close();
		return false;
	}
	// 写入文件
	int needBlockNum = fileString.length() % blockSize + 1;

	// 应该先分配块(新文件)，或者获得(已有文件)块分配情况
	// 然后writeFile()根据块分配情况直接写入文件
	int writePos = 0;
	for (int curPos = 0; curPos < blockNum; ++curPos){
		if (blockStatus[curPos]){
			oFile.seekp(blockSize * curPos, ios::cur);
			while(writePos < fileString.length()){
				if ((writePos + 1) % blockSize == 0 ){
					break;
				}
				else if(fileString[writePos] == ' ')
					oFile<<"\\";
				else
					oFile<<fileString[writePos];
				writePos++;
			}
			if (writePos >= fileString.length()){
					break;
			}
		}
	}
			
	// 成功返回TRUE
	oFile.close();
	return true;
}

// //测试主函数，临时使用
// int main(){
// 	BasicService::test();
// 	return 0;
// }