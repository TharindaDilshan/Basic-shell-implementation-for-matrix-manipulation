#include<iostream>
#include <string>
#include<sstream>

using namespace std;

const int MAXROWS = 100;
const int MAXCOLUMNS = 100;

class Matrix{
	private:
		string name;
		int matrix[MAXROWS][MAXCOLUMNS];
		int rows;
		int columns;
	public:
		Matrix();
		string getName();
		void constructMatrix(string, string);
		void updateMatrix(string);
		void displayMatrix();
};

Matrix::Matrix(){
	name= "",
	rows = 0;
	columns = 0;
}

string Matrix::getName(){
	return name;
}

void Matrix::constructMatrix(string variableName, string inputString){
	name = variableName;
	int k = 0;
	int i = 0;
	int j = 0;
	// int l = 0;
	while(k < inputString.length()){

		if(inputString[k] == ';'){
			i++;
			j = 0;
			k++;
		}else if(inputString[k] == ' ' || inputString[k] == ','){
			k++;
		}
		else{
			string x = "";
			while(inputString[k] != ' ' && inputString[k] != ',' && inputString[k] != ';'){
				x += inputString[k];
				// l++;
				k++;
			}
			stringstream num(x);
			num >> matrix[i][j];
			j++;
		}
	}
	rows = i+1;
	columns = j;
}

void Matrix::updateMatrix(string matrixString){
	
//	for(int i=0;i<rows;i++){
//		for(int j=0;j<columns;j++){
//			matrix[i][j] = 0;
//		}
//	}
}

void Matrix::displayMatrix(){

	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

int main(){
	int n, validName, updated;
	int arraySize = 10;
	string variableName, variableValue;
	Matrix matrixArray[arraySize];
	int arrayRef = 0;
	string inputStr;
	cout<<"Welcome to Universal Complex Scripting Calculator by UCSC, Sri Lanka. Version: 1.0 "<<endl;
	while(true){
		cout<<">>";
		getline(cin, inputStr);

		for(int i=0;i<inputStr.length();i++){
			if(inputStr[i]=='=' || inputStr[i]=='+' || inputStr[i]=='-' || inputStr[i]=='*' || inputStr[i]=='/'){
				switch(inputStr[i]){
					case '=':
						n = inputStr.find('=');
						variableName = inputStr.substr(0,n);
						variableName = trim(variableName);
						validName = 0;
						if((int(variableName[0]) >= 65 && int(variableName[0]) <= 90) || (int(variableName[0]) >= 97 && int(variableName[0]) <= 122)){
							for(int j=0;j<variableName.length();j++){
								if(variableName[j] == ' '){   
									validName = 0;
									break;
								}else{
									validName = 1;
								}
							}
						}
						
						if(validName){
							variableValue = trim(inputStr.substr(n+1));

							if(variableValue.length() > 0){
								if(variableValue[0] == '[' && variableValue[variableValue.length() - 1] == ']'){
									// Matrix
									updated = 0;
									
									for(int j=0;j<arraySize;j++){
										if(matrixArray[j].getName() == variableName){
											matrixArray[j].constructMatrix(variableName, variableValue.substr(1,variableValue.length()-2));
											matrixArray[j].displayMatrix();
											updated = 1;
											break;
										}
									}
									if(!updated){
										for(int j=0;j<arraySize;j++){
											if(matrixArray[j].getName() == ""){
												matrixArray[j].constructMatrix(variableName, variableValue.substr(1,variableValue.length()-2));
												matrixArray[j].displayMatrix();
												break;
											}
										}
									}

								}else if(variableValue[0] == '[' || variableValue[variableValue.length() - 1] == ']'){
									cout<<"Invalid Matrix syntax"<<endl;
								}else{
									// Number
								}
							}else{
								cout<<"Invalid Assignment"<<endl;
							}
						}else{
							cout<<"Invalid Variable Name"<<endl;
						}

					// case '+':

					// case '-':

					// case '*':

					// case '/':

					// default:

				}
			}
		}
	for(int j=0;j<arraySize;j++){
		if(matrixArray[j].getName() != ""){
			cout<<matrixArray[j].getName();
		}
	}		
				
	}
	
}
