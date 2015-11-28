#include "Function.h"

#include <string>
#include <vector>
using namespace std;

Function::Function(string name){
	m_name = name;
}
Function::Function(){}
Function::~Function(){}

void Function::addArgument(string arg){
	m_args.push_back(arg);
}
string Function::getArgument(int index){
	return m_args[index];
}
string* Function::getAllArguments(){
	return &m_args[0];
}
int Function::countArguments(){
	return m_args.size();
}

void Function::setName(string name){
	m_name = name;
}
string Function::getName(){
	return m_name;
}
void Function::addPath(string path){
	m_paths.push_back(path);
}
string* Function::getAllPaths(){
	return &m_paths[0];
}
string Function::getPath(int index){
	return m_paths[index];
}
int Function::countPaths(){
	return m_paths.size();
}

Function& Function::operator=(const Function& copy){
	m_name = copy.m_name;
	m_args = copy.m_args;
	m_paths = copy.m_paths;
}
