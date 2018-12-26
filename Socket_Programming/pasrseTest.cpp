#include <iostream>
#include <regex>
#include <iterator>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <tuple>

std::tuple<std::string, std::string> parseBuffer(std::string buffer){
    std::string delimeter = " ";
    std::string::size_type pos = buffer.find(delimeter);
    std::string type = buffer.substr(0, pos );
    std::string message = buffer.erase(0, pos + delimeter.length());
    
    return std::make_tuple(type, message);
    
}

int main(){
	std::string str = "aok \r\n\r\njnasdjajsdij\r\n\r\nnsnuajdijad\r\n";
	std::string::size_type pos = str.find("\r\n");
	std::cout << pos << std::endl;
}