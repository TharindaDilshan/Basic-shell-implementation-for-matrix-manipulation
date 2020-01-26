#include<iostream>
#include <string>
#include<sstream>
#include<bits/stdc++.h>

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
		int getMatrix();
		void constructMatrix(string, string);
		void matrixAddition(Matrix);
		void matrixSubtraction(Matrix);
		void matrixMultiplication(Matrix);
		void elementwiseMatrixMultiplication(Matrix);
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

int Matrix::getMatrix(){
	return **matrix;
}

void Matrix::constructMatrix(string variableName, string inputString){
	name = variableName;
	int k = 0;
	int i = 0;	//rows
	int j = 0;  //columns
	int rowChecker = 0;

	while(k < inputString.length()){

		if(inputString[k] == ';'){
			if(i != 0 && rowChecker != j){
				cout<<"Error creating matrix: Dimesion mismatch"<<endl;
				return;
			}
			i++;
			j = 0;
			k++;
		}else if(inputString[k] == ' ' || inputString[k] == ','){
			k++;
		}
		else{
			string x = "";
			while(inputString[k] != ' ' && inputString[k] != ',' && inputString[k] != ';' && inputString[k] != '\0'){
				x += inputString[k];
				k++;
			}
			for(int z=0;z<x.length();z++){
				if(!isdigit(x[z]) && x[z]!='.' ){
					cout<<"Initialization Error: Invalid element type"<<endl;;
					return;
				}
			}
			stringstream num(x);
			num >> matrix[i][j];
			j++;

			if(i == 0){
				rowChecker++;
			}
			if(i != 0 && k == inputString.length()){
				if(j != rowChecker){
					cout<<"Error creating matrix: Dimesion mismatch"<<endl;
					return;
				}	
			}
		}
	}
	rows = i+1;
	columns = j;
	displayMatrix();
}

void Matrix::displayMatrix(){

	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}

void Matrix::matrixAddition(Matrix m2){
	if(rows == m2.rows && columns == m2.columns){
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				cout<<matrix[i][j] + m2.matrix[i][j] <<"\t";
			}
			cout<<endl;
		}
	}else{
		cout<<"Failed to perform addition: Type Mismatch"<<endl;
		return;
	}
}

void Matrix::matrixSubtraction(Matrix m2){
	if(rows == m2.rows && columns == m2.columns){
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				cout<<matrix[i][j] - m2.matrix[i][j] <<"\t";
			}
			cout<<endl;
		}
	}else{
		cout<<"Failed to perform substraction: Type Mismatch"<<endl;
		return;
	}
}

void Matrix::matrixMultiplication(Matrix m2){
	int sum;
	if(rows == 1 && columns == 1 && m2.rows == 1 && m2.columns == 1){
		cout<<matrix[0][0] * m2.matrix[0][0]<<endl;
	}
	else if(columns == m2.rows){
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < m2.columns; j++){
				sum = 0;
				for(int k = 0; k < columns; k++){
					sum += matrix[i][k] * m2.matrix[k][j];
				}
				cout<<sum<<"\t";
			}
			cout<<endl;
		}       
	}
	else if((rows == 1 && columns == 1) || (m2.rows == 1 && m2.columns == 1)){
		if(rows == 1 && columns == 1){
			for(int i=0;i<m2.rows;i++){
				for(int j=0;j<m2.columns;j++){
					cout<< matrix[0][0] * m2.matrix[i][j]<<"\t"; 
				}
				cout<<endl;
			}
		}
		else if(m2.rows == 1 && m2.columns == 1){
			for(int i=0;i<rows;i++){
				for(int j=0;j<columns;j++){
					cout<< m2.matrix[0][0] * matrix[i][j]<<"\t"; 
				}
				cout<<endl;
			}
		}
	}
	else{
		cout<<"Failed to perform multiplication: Dimension Mismatch"<<endl;
		return;
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
	int n, validName, updated, operandCount,viewValue,v;
	int arraySize = 10;
	string variableName, variableValue, left, right;
	Matrix leftOperand, rightOperand;
	
	Matrix matrixArray[arraySize];
	int arrayRef = 0;
	string inputStr;
	cout<<"Welcome to Universal Complex Scripting Calculator by UCSC, Sri Lanka. Version: 1.0 "<<endl;
	while(true){
		cout<<">>";
		string check = inputStr;
		transform(check.begin(), check.end(), check.begin(), ::toupper);
		if( check == "EXIT"){
			break;
		}
		if(check == ""){
			continue;
		}
		viewValue = 1;
		int brk = 0;
		for(int i=0;i<inputStr.length();i++){
			if(inputStr[i]=='=' || inputStr[i]=='+' || inputStr[i]=='-' || inputStr[i]=='*' || inputStr[i]=='/' || inputStr[i]=='.'){
				viewValue = 0;
				switch(inputStr[i]){
					case '=':
						if(inputStr.find('+') != string::npos || inputStr.find('*') != string::npos){
							cout<<"Complex assignments not supported"<<endl;
							brk = 1;
							break;
						}
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
											// matrixArray[j].displayMatrix();
											updated = 1;
											break;
										}
									}
									if(!updated){
										for(int j=0;j<arraySize;j++){
											if(matrixArray[j].getName() == ""){
												// matrixArray[j].displayMatrix();
												break;
											}
										}
									}

								}else if(variableValue[0] == '[' || variableValue[variableValue.length() - 1] == ']'){
									cout<<"Invalid Matrix syntax"<<endl;
									break;
								}else{
									// Number
									updated = 0;
									for(int j=0;j<arraySize;j++){
										if(matrixArray[j].getName() == variableName){
											matrixArray[j].constructMatrix(variableName, variableValue);
											// matrixArray[j].displayMatrix();
											updated = 1;
											break;
										}
									}
									if(!updated){
										for(int j=0;j<arraySize;j++){
											if(matrixArray[j].getName() == ""){
												matrixArray[j].constructMatrix(variableName, variableValue);
												// matrixArray[j].displayMatrix();
												break;
											}
										}
									}
								}
							}else{
								cout<<"Invalid Assignment"<<endl;
							}
						}else{
							cout<<"Invalid Variable Name"<<endl;
						}
						break;

					case '+':
						n = inputStr.find('+');
						left = trim(inputStr.substr(0,n));
						right = trim(inputStr.substr(n+1));
						
						if(numeric(left) && numeric(right)){
							int leftInt,rightInt;
							stringstream q(left);
							stringstream r(right);
							
							q>>leftInt;
							r>>rightInt;
							cout<<leftInt+rightInt<<endl;
							break;
						}
						v = 0;
						for(int j=0;j<arraySize;j++){
							if(matrixArray[j].getName() == left){
								leftOperand = matrixArray[j];
								v++;
							}
							if(matrixArray[j].getName() == right){
								rightOperand = matrixArray[j];
								v++;
							}
						}	
						if(leftOperand.getName() != "" && rightOperand.getName() != "" && v == 2){
							leftOperand.matrixAddition(rightOperand);
						}
						else{
							cout<<"Invalid Variable"<<endl;
							brk = 1;
						}	
						break;	

					case '-':
						if(inputStr.find('=') != string::npos){
							break;
						}else{
							n = inputStr.find('-');
							left = trim(inputStr.substr(0,n));
							right = trim(inputStr.substr(n+1));
							
							if(numeric(left) && numeric(right)){
								int leftInt,rightInt;
								stringstream q(left);
								stringstream r(right);
								
								q>>leftInt;
								r>>rightInt;
								cout<<leftInt-rightInt<<endl;
								break;
							}
							v = 0;
							for(int j=0;j<arraySize;j++){
								if(matrixArray[j].getName() == left){
									leftOperand = matrixArray[j];
									v++;
								}
								if(matrixArray[j].getName() == right){
									rightOperand = matrixArray[j];
									v++;
								}
							}	
							if(leftOperand.getName() != "" && rightOperand.getName() != ""){
								leftOperand.matrixSubtraction(rightOperand);
							}else{
								cout<<"Invalid Variable"<<endl;
								brk = 1;
							}
						}	
						break;

					case '*':
						if(inputStr.find('.') != string::npos){
							break;
						}
					 	n = inputStr.find('*');
						left = trim(inputStr.substr(0,n));
						right = trim(inputStr.substr(n+1));
						
						if(numeric(left) && numeric(right)){
							int leftInt,rightInt;
							stringstream q(left);
							stringstream r(right);
							
							q>>leftInt;
							r>>rightInt;
							cout<<leftInt*rightInt<<endl;
							break;
						}
						v = 0;
						for(int j=0;j<arraySize;j++){
							if(matrixArray[j].getName() == left){
								leftOperand = matrixArray[j];
								v++;
							}
							if(matrixArray[j].getName() == right){
								rightOperand = matrixArray[j];
								v++;
							}
						}	
						if(leftOperand.getName() != "" && rightOperand.getName() != "" && v == 2){
							leftOperand.matrixMultiplication(rightOperand);
						}else{
							cout<<"Invalid Variable"<<endl;
							brk = 1;
						}
						break;

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
