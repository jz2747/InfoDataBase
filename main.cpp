#include<string>
#include<fstream>
#include<cstdlib>
#include<iostream>
using namespace std;

typedef int INDEX;
typedef double MARK;
typedef string NAME;

const int MAX_STUDENT = 500;
const char FILE_PATH[] = "./entry_file";
fstream entryFile;
int entryCount = -1;

class StudentEntry{
	public:
		StudentEntry(NAME name, MARK mark):name(name), mark(mark){}
		
		void operator=(StudentEntry *entry){
			name = entry->name;
			mark = entry->mark;
		}
		
		NAME name;
		MARK mark;
}*entryList[MAX_STUDENT];

int CurrentRecord(){
	return entryCount+1;
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
	}
	delete entryList[entryCount];
}

void Delete(){
	if(entryCount != -1){
		DeleteFromTheList(GetStudentIdx());
		entryCount--;
	}
}

void SetNewMark(INDEX idx, MARK mark){
	entryList[idx]->mark = mark;
}

void AddToList(NAME name, MARK mark){
	entryList[entryCount] = new StudentEntry(name,mark);
}

int comp(const void* a, const void *b){
	if (((StudentEntry*)a)->name < ((StudentEntry*)b)->name)
		return -1;
	else if(((StudentEntry*)a)->name > ((StudentEntry*)b)->name)
		return 1;
	else if(((StudentEntry*)a)->mark < ((StudentEntry*)b)->mark)
		return -1;
	else if(((StudentEntry*)a)->mark > ((StudentEntry*)b)->mark)
		return 1;
	else
		return 0;
}
void SortList(){
	qsort(entryList, entryCount+1, sizeof(StudentEntry*), comp);
}

void LoadDataFromFile(){

	entryFile.open(FILE_PATH, ios_base::in);
	if(entryFile.is_open()){
		cout << "File opened." << endl;
		char temp[100];
		for(entryCount = 0; entryFile >> temp; entryCount++){
			entryList[entryCount] = new StudentEntry(temp, 0);
			entryFile >> entryList[entryCount]->mark;
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
}

void ShowList(){
	for(int i = 0; i < entryCount; i++)
		cout << i << '\t' << entryList[i]->name;
}

void AddEntry(){
	NAME name = GetStudentName();
	MARK mark = GetStudentMark();
	entryCount++;
	AddToList(name, mark);
	SortList();
}

void ChangeMark(){
	SetNewMark(GetStudentIdx(),GetStudentMark());
}

void DeleteEntry(){
	INDEX idx = GetStudentIdx();
	DeleteFromTheList(idx);
	entryCount--;
}

void SearchName(){
	MARK mark = GetStudentMark();
	for(int i = 0; i < entryCount; i++)
		if(entryList[i]->mark == mark)
			cout << i << '\t' << entryList[i]->name;
}


void SearchMark(){

	NAME name = GetStudentName();
	for(int i = 0; i < entryCount; i++)
		if(entryList[i]->name == name)
			cout << i << '\t' << entryList[i]->mark;
}

int GetUserChoice(){
	int choice;
	cout << "Enter the option's number and press enter";
	cin >> choice;
	return choice;
}
int main(){

	int userChoice;
	LoadDataFromFile();
	do{
		cout << "1:ShowList\n2:AddEntry\n3:ChangeMark\n4:DeleteEntry\n5:SearchName\n6:SearchMark\n7:Exit\n";
		cout << "Current number of records: " << CurrentRecord() << endl;
		userChoice = GetUserChoice();
		switch(userChoice){
			case 1: ShowList(); break;
			case 2: AddEntry(); break;
			case 3: ChangeMark(); break;
			case 4: DeleteEntry(); break;
			case 5: SearchName(); break;
			case 6: SearchMark(); break;
			case 7: break;
		}
	}while(userChoice != 7);
	SaveDataToFile();
	return 0;
}


