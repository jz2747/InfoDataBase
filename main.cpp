#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
using namespace std;

const int MAX_STUDENT = 500;
const char FILE_PATH[] = "./entry_file";
typedef int INDEX;
typedef double MARK;
typedef string NAME;
int entryCount = -1;
fstream entryFile;

class StudentEntry{
	public:
		StudentEntry(NAME name, MARK mark):name(name), mark(mark){}
		
		void operator=(StudentEntry *entry){
			name = entry->name;
			mark = entry->mark;
		}
		
		NAME name;
		MARK mark;
} *entryList[MAX_STUDENT];

INDEX GetStudentIdx();
MARK GetStudentMark();
NAME GetStudentName();
void LoadDataFromFile();
void SaveDataToFile();
void DeleteromTheList(INDEX idx);
void Delete();
void ChangeMark();
void SetNewMark(INDEX idx, MARK mark);
void AddEntry();
void AddToList(NAME name, MARK mark);
void SortList();
void SearchMark();
void SearchName():
void ShowList();
int getUserChoice();

int main(){
	LoadDataFromFile();
	int userChoice;
	do{
		cout << "1:ShowList\n2:AddEntry\n3:ChangeMark\n4:DeleteEntry\n5:SearchName\n6:SearchMark\n7:Exit\n";
		cout << "Current number of records: " << entryCount + 1 << endl;
		userChoice = getUserChoice();
		switch(userChoice){
			case 1: ShowList(); break;
			case 2: AddEntry(); break;
			case 3: ChangeMark(); break;
			case 4: DeleteEntry(); break;
			case 5: SearchName(); break;
			case 6: SearchMark(); break;
			case 7: break;
		}
	}while(userChoice != 7){
	SaveDataToFile();
	return 0;
}

INDEX GetStudentIdx(){
	cout << "Enter index: ";
	INDEX idx;
	cin >> idx;
	return idx;
}

MARK GetStudentMark(){
	cout << "Enter mark:";
	MARK mark;
	cin >> mark;
	return mark;
}

NAME GetStudentName(){
	NAME name;
	cout << "Enter name:";
	cin >> name;
	return name;
}


void DeleteFromTheList(INDEX idx){
	if(entryCount != idx){
		for(int i = idx; i < entryCount; i++){
			entryList[i]->name = entryList[i+1]->name;
			entryList[i]->mark = entryList[i+1]->mark;
			}
	delete entryList[entryCount];
}

void Delete(){
	if(entryCount != -1){
		DeleteFromTheList(GetStudentIdx());
		entryCount--;
	}
}

void SetNewMark(INDE idx, MARK mark){
	entryList[idx]->mark = mark;
}

void AddToList(name, mark){
	entryList[entryCount] = new StudentEntry(name,mark);
}

bool comp(const void* a, const void *b){
	return ((*StudentEntry) a)->name < ((*StudentEntry) b) -> name;
}
void SortList(){
	qsort(entryList, entryCount, sizeof(*StudentEntry), comp);
}

void LoadDataFromFile(){

	entryFile.open(FILE_PATH, ios_base::in);
	if(entryFile.is_open()){
		cout << "File opened." << endl;
		char temp[100];
		for(entryCount = 0; entryFile >> temp; entryCount++){
			entryList[entryCount] = new StudentEntry(temp, 0);
			entryFile >> entryList[entryCount->mark];
		}
		entryCount--;
		entryFile.close();
		entryFile.clear();
	}
	else{
		entryFile.clear();
		cout << "File not found in " << FILE_PATH << endl;
	}
}

void SaveDataToFile(){
	entryFile.open(FILE_PATH, ios_base::out);
	if(entryFile.is_open()){
		if(!entryFile.good()){
			cout << "Error writing file." << endl;
		}
		else{
			for(int i = 0; i <= entryCount; i++){
				entryFile << entryList[i]->name << endl;
				entryFile << entryList[i]->mark << endl;
			}
			entryFile.close();
		}
}

void ShowList(){
	for(int i = 0; i < listCount; i++)
		cout << i << '\t' << listItem[i];
}

void AddEntry(){
	name = GetStudentName();
	mark = GetStudentMark();
	listCount++;
	AddToList(name, mark);
	SortList();
}

void ChangeMark(){
	SetNewMark(GetStudentIdx(),GetStudentMark());
}

void DeleteEntry(){
	idx = GetStudentIdx();
	DeleteFromTheList(idx);
	listCount--;
}

void SearchName(){
	MARK mark = GetStudentMark();
	for(int i = 0; i < listCount; i++)
		if(listItem[i].mark == mark)
			cout << i << '\t' << listItem[i].name;
}


void SearchMark(){

	NAME name = GetStudentName();
	for(int i = 0; i < listCount; i++)
		if(listItem[i].name == name)
			cout << i << '\t' << listItem[i].mark;
}

int GetUserChoice(){
	int choice;
	cout << "Enter the option's number and press enter";
	cin >> choice;
	return choice;
}
