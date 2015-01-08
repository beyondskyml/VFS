/*
* ���������
* ΪVFS�ṩ�����Ĵ�������д���ر��ļ�����������ת��������
* ������Ϊ�����ṩ���ļ������ӿڡ�
*/

// ע�⣺ �ļ��򿪺�һ��Ҫ�ر�

#include "BasicService.h"
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <iomanip>

/*
* // ���С �ֽ�
* #define blockSize 256
* // �ܿ��� 10MB
* #define blockNum  10 * 1024 * 1024
* // ������ ��ʼ���
* #define bootBlockNo 0
* // ������ ��ʼ���
* #define superBlockNo 1
* // �ļ���Ϣ�� ��ʼ���
* #define infoBlockNo 2
* // ���ݿ� ��ʼ���
* #define dataBlockNo 128 * 256
*/

using namespace std;

// ��ʼ����̬���ݳ�Ա
int BasicService::emptyBlockNum = blockNum;
bool BasicService::blockStatus[blockNum];
bool BasicService::infoBlockStatus[dataBlockNo - infoBlockNo];			// ��Ϣ��ʹ�������TRUE ���ã� FALSE ����
int BasicService::fileInfoBlockNo = 0;						// ָ�����ļ���Ϣ�����
int BasicService::fileBlockNo[20];
string BasicService::fileName;
string BasicService::fileUser;
bool BasicService::isWrite = false;						// ��д��־λ true�����Ƿ�����Ϣ����д

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
* �ӿ��豸��ȡĿ¼��Ϣ������
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
		//��ȡ�û���������
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
* ��Ŀ¼����д����豸
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
		// �����ע�ⳤ�ȿ���
		iofile<<setw(11)<<setiosflags(ios::left)<<dir[i][0] 
			<<setw(2)<<setiosflags(ios::left)<<dir[i][1]
			<<setw(2)<<setiosflags(ios::left)<<dir[i][2];
	}
	iofile<<0;
	iofile.close();
}


/****************************
* �ӿ��豸��ȡ�û���Ϣ������
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
		//��ȡ�û���������
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
* ���û���Ϣ����д����豸
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
		// �����ע�ⳤ�ȿ���
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
	// Ӧ����ʹ��calBlockNo��������ű�����fileBlockNo�У���ʹ�øú�������
bool BasicService::saveFileInfo(){
	iofile.open("vfs.txt", ios::in | ios::out);
		if (!isWrite){	// ������½��ļ�
		iofile.seekp(infoBlockNo * blockSize);
		for (int i = 0; i < dataBlockNo - infoBlockNo; ++i){
			if(infoBlockStatus[i]){		// ���ҿտ鲢����
				// ���ļ���Ϣд��ÿ�
				writeFileInfo();
				// �ÿ���ռ��
				infoBlockStatus[i] = false;
				iofile.close();
				return true;
			}
		}
		iofile.close();
		return false;
	}
	else{		// ��������½��ļ�
		iofile.seekp(fileInfoBlockNo * blockSize);
		// ���ļ���Ϣд��ÿ�
		writeFileInfo();	// ��ʱ�ļ��Ŀ��Ӧ���Ѿ�������fileBlockNo[]��
		iofile.close();
		return true;
	}
}
void BasicService::writeFileInfo(){
	writeInfoString(fileName);
	writeInfoString(fileUser);
	cout<<"2\n";
	// ������Ŀ��д���ļ�
	for (int i = 0; i < 20; ++i){		
		//ÿ���鱣��20����ţ�����12λ�����ڼ��Ѱַ
		//ÿ��������10Ϊ�����һλ�ո����ڶ�ȡʱ����
		iofile<<setw(11)<<setiosflags(ios::left)<<fileBlockNo[i];
	}
}
void BasicService::writeInfoString(string writeString){
	iofile<<setw(11)<<setiosflags(ios::left)<<writeString;
}

// �����ļ��洢�Ŀ��
bool BasicService::calDataBlock(string fileString){
	// �����ļ������Ƿ񳬳�
	int needBlockNum = fileString.length() % blockSize;
	if(needBlockNum > 10)
		return false;	//�ļ�����������ʧ��
	if(!isWrite){ // ������½��ļ�
		int curPos = 0;
		for (int i = 0; i < dataBlockNo - infoBlockNo; ++i){
			if(infoBlockStatus[i]){
				infoBlockStatus[i] = false;
				fileBlockNo[curPos] = i + dataBlockNo;
				curPos++;
			}
			if (curPos + 1 == 10){	// ��ÿ���ļ�����������10
				return true;
			}
		}
		return false;//ʣ����п鲻����
	}
	else{
		ifstream iFile;
		iFile.open("vfs.txt", ios::in);
		
		// ����Ǹ���д���ļ�
		searchInfoNo(fileName);	// ע��fileName�Ƿ��Ѿ�����
		iFile.seekg(fileInfoBlockNo * blockSize + 24);
		for (int i = 0; i < 10; ++i){
			iFile>>fileBlockNo[i];
		}
		return true;//��ȡ������
	}	
}


/*void BasicService::test_9_searchInfoNo(){

}*/
// �ļ����� ����true ���򷵻�false
// ���ļ���Ϣ�飬�����ҵ��ļ����ݱ���Ŀ顣
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

// �������ļ�ϵͳ�����������򴴽��������������
bool BasicService::createFile(/* char * url*/){
	// ���Դ��ļ�
	//fstream ioFile(url, ios::out | ios::noreplace);
	ofstream ioFile;
	ioFile.open("vfs.txt", ios::out); //�����ʽ���ļ����������򴴽�
	// �ж��Ƿ�ɹ�
	if (! ioFile){
		// ʧ�ܷ���false
		ioFile.close();
		return false;
	}
	// ��ʼ��
	init();
		// �ɹ�����TRUE
		ioFile.close();
	return true;  
}

// ���ַ���д����п�
// ע�⣺���ô˺���ǰ�������createFile����,��ȷ����ʼ���ļ�ϵͳ
// �ַ����еĻ���Ҫ��\t��ʾ(\r\t?)
bool BasicService::writeFile(string fileString){
	ofstream oFile;
	oFile.open("vfs.txt", ios::app); //�����ʽ���ļ����������򴴽�
	// �ж��Ƿ�ɹ�
	if (! oFile){
		// ʧ�ܷ���false
		oFile.close();
		return false;
	}
	// д���ļ�
	int needBlockNum = fileString.length() % blockSize + 1;

	// Ӧ���ȷ����(���ļ�)�����߻��(�����ļ�)��������
	// Ȼ��writeFile()���ݿ�������ֱ��д���ļ�
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
			
	// �ɹ�����TRUE
	oFile.close();
	return true;
}

// //��������������ʱʹ��
// int main(){
// 	BasicService::test();
// 	return 0;
// }