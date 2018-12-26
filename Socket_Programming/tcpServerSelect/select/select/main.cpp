#include <iostream>
#include <regex>
#include <iterator>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <tuple>
#include <pthread.h>
#include <stddef.h>
#include <fstream>
#include <time.h>

#define MIN_PORT 3000
#define MAX_PORT 3999

/**
 CHECKS WHETHER THE PHOTO MESSAGE IS CORRECT
 FORMAT OF THE MESSAGE: <FOTO> <NUM OF SENT BYTES> <BINARY DATA>
 @param photoMessage message with binary data
 @return true if correct
 */
bool checkPhoto(std::string photoMessage){
    std::string numberOfBytes;
    std::string binaryData;
    std::string delimeter = " ";
    std::string::size_type pos = photoMessage.find(delimeter);
    if( pos < 1){
        return false;
    }
    numberOfBytes = photoMessage.substr(0, pos);
    binaryData = photoMessage.substr(pos,photoMessage.length());
    return false;
}

/**
 CHECKS ENTERED PASSWORD BASES ON THE SUM OF ASCII VALUES OF USERNAME
 @return: true on success, false otherwise
 */
bool checkPassword(std::string password, std::string username){
    std::istringstream sst;
    sst.str(username);
    std::cout << sst.str() << std::endl;
    unsigned char byte = '\0';
    int value = 0;
    //dont skip whitespace
    while (sst >> std::noskipws >> byte) {
        value += byte;
    }
    std::cout << "suma: " << value << std::endl;
    // Check the entered password
    if (password == std::to_string(value)) {
        return true;
    }
    
    return false;
}
/**
 CHECKS MESSAGE SYNTAX BASED ON THE STATE WE ARE IN
 CHECKS PASSWORD
 CHECKS CHECK SUM
 @param response <string type (if available), string message to parse>
 @return TRUE on success, FALSE otherwise
 */
bool checkMessage(std::tuple<std::string,std::string> response, int state, std::string& username, std::string& password){
    if (std::get<0>(response) == "NULL") {
        return false;
    }
    auto messageToParse = std::get<1>(response);
    std::string delimeter = "\r\n";
    std::string::size_type pos = messageToParse.find(delimeter);
    auto parsedMessage = messageToParse.substr(0,pos);
    
    
    //USERNAME
    if (state == 0) {
        username = parsedMessage;
        return true;
    }
    
    //PASSWORD CHECK
    if (state == 1 && checkPassword(parsedMessage, username)) {
        password = parsedMessage;
        return true;
    }
    
    if (state == 2) {
        std::string type = std::get<0>(response);
        
        //INFO
        if( type == "NFO"){
            //TODO logging the message
            return true;
        }
        //PHOTO
        if ( type == "OTO") {
            //TODO cehck correctness
            return true;
        }
        return false;
    }
    
    return false;
}
/**
 THIS FUNC WILL CHECK RESPONSE FROM THE ROBOT, AND DECIDE WHAT TO DO BASED ON THE STATE
 @return tuple<bool TRUE if everything is right,std::string MESSAGE to send to the robot>
 */
std::tuple<bool,std::string> checkResponse(std::tuple<std::string, std::string> response, int state, std::string& username, std::string& password){
    
    if (state == 0) {
        if (checkMessage(response, state, username, password)) {
            return std::make_tuple(true, "201 PASSWORD\r\n");
        }
    }
    if (state == 1) {
        if(checkMessage(response, state, username, password)){
            return std::make_tuple(true, "202 OK\r\n");
        }else{
            return std::make_tuple(false, "500 LOGIN FAILED\r\n");
        }
    }
    if (state == 2) {
        
        if (checkMessage(response, state, username, password)) {
            return std::make_tuple(true, "202 OK\r\n");
        }else{
            return std::make_tuple(false, "501 SYNTAX ERROR\r\n");
        }
    }
    return std::make_tuple(false, "unexpected result");
}
/**
 This func will parse the incoming buffer
 @param buffer incoming buffer
 @return tuple <String type of message (U,I,P,F),  String actual message>
 */
std::tuple<std::string, std::string> parseBuffer(std::string buffer, int state){
    if (state == 0) {
        return std::make_tuple("U", buffer);
    }
    if (state == 1) {
        return std::make_tuple("P", buffer);
    }else{
        std::string delimeter = " ";
        std::string::size_type pos = buffer.find(delimeter);
        if (pos < 1) {
            return std::make_tuple("NULL","NULL");
        }
        //TODO check the type
        std::string type = buffer.substr(0, pos );
        std::string message = buffer.erase(0, pos + delimeter.length());
        
        return std::make_tuple(type, message);
    }
}
/**
 read mesage byte after byte, return the whole mesage
 */
char readByte(int c_sockfd){
    
    int mlen;
    char buf[1];
    if ((mlen = recv(c_sockfd, buf, 1, 0)) < 1){
        perror("Reading a byte was not successful");
        close(c_sockfd);
        return NULL;
    }else{
        return buf[0];
    }
    return NULL;
}
std::string readWord(int c_sockfd){
    std::stringstream message;
    while (1) {
        char currentByte = readByte(c_sockfd);
        
        if(currentByte == ' '){
            return message.str().c_str();
            break;
        }
        
        message << currentByte;
    }
}

std::string readMessage(int c_sockfd){
    char lastByte='\0';
    char currentByte;
    std::stringstream message;
    while (1) {
        currentByte = readByte(c_sockfd);
        message << currentByte;
        
        if(lastByte == '\r' && currentByte == '\n'){
            message << currentByte;
            return message.str().c_str();
            break;
        }
        lastByte = currentByte;
    }
}

/*
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {
    int    sockfd, c_sockfd;
    sockaddr_in my_addr, rem_addr;
    socklen_t    rem_addr_length;
    const int PORT_NUM = atoi(argv[1]);
    /*
     * check command line arguments
     */
    if( (PORT_NUM > MAX_PORT) || (PORT_NUM < MIN_PORT)){
        perror("Port number is not acceptable");
        exit(-1);
    }
    
    if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        perror("Socket creation was not successful");
        exit(-1);
    }
    
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
               (const void *)&optval , sizeof(int));
    
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT_NUM);
    std::cout << PORT_NUM << " PORT NUM" << std::endl;
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
        perror("Error in bind");
        close(sockfd); exit(1);
    }
    
    if (listen(sockfd, SOMAXCONN) == -1)
    {
        perror("Listen action not successful");
        close(sockfd); exit(1);
    }
    //////////////////////////////////////
   
    int connectcnt; /* number of connection requests */
    int notdone;
    fd_set readfds;
    /* initialize some things for the main loop */
  
    connectcnt = 0;
    printf("server> ");
    fflush(stdout);
    
    /*
     * main loop: wait for connection request or stdin command.
     *
     * If connection request, then echo input line
     * and close connection.
     * If command, then process command.
     */
    while (notdone) {
        
        /*
         * select: Has the user typed something to stdin or
         * has a connection request arrived?
         */
        FD_ZERO(&readfds);          /* initialize the fd set */
        FD_SET(sockfd, &readfds); /* add socket fd */
        FD_SET(0, &readfds);        /* add stdin fd (0) */
        if (select(sockfd + 1, &readfds, 0, 0, 0) < 0) {
            error("ERROR in select");
        }
        
        /* if the user has entered a command, process it */
//        if (FD_ISSET(0, &readfds)) {
//            fgets(buf, BUFSIZE, stdin);
//            switch (buf[0]) {
//                case 'c': /* print the connection cnt */
//                    printf("Received %d connection requests so far.\n", connectcnt);
//                    printf("server> ");
//                    fflush(stdout);
//                    break;
//                case 'q': /* terminate the server */
//                    notdone = 0;
//                    break;
//                default: /* bad input */
//                    printf("ERROR: unknown command\n");
//                    printf("server> ");
//                    fflush(stdout);
//            }
//        }
//
        /* if a connection request has arrived, process it */
        if (FD_ISSET(sockfd, &readfds)) {
            /*
             * accept: wait for a connection request
             */
//            childfd = accept(parentfd,
//                             (struct sockaddr *) &clientaddr, &clientlen);
//            if (childfd < 0)
//                error("ERROR on accept");
//            connectcnt++;
            
            /*
             * read: read input string from the client
             */
//            bzero(buf, BUFSIZE);
//            n = read(childfd, buf, BUFSIZE);
//            if (n < 0)
//                error("ERROR reading from socket");
            
            int c_sockfd = accept(sockfd, (struct sockaddr*) &rem_addr, &rem_addr_length);
            
            if ( c_sockfd == -1)
            {
                perror("Client socket not created");
                close(sockfd); exit(1);
            }
            ///tady nekde zacne jet novej thread
            /**
             0 - LOGIN SUCCESSFUL, USERNAME IS IN THE BUFFER
             1 - PASSWORD CHECK
             2 - PASSWORD OK, COMMUNICATING
             */
            int state = 0;
            std::string username, password;
    
            ///FIRST MESSAGE
            std::string ok = "200 LOGIN\r\n";
            send(c_sockfd, ok.c_str(), ok.length(), 0);
            ///MAIN PART
            time_t timeB = time(NULL);
            
            //std::stringstream message;
            
            //char firstByte = readByte(c_sockfd);
            ///LOGIN
            while (1) {
                std::string response = readMessage(c_sockfd);
                std::cout << "response " << response << std::endl;
                auto messageToSend = checkResponse(parseBuffer(response, state),state,username,password);
                std::cout << "message to send " << std::get<1>(messageToSend) << std::endl;
                send(c_sockfd, std::get<1>(messageToSend).c_str(), std::get<1>(messageToSend).length(), 0);
                state++;
                if (time(NULL) - timeB > 45) {
                    close(c_sockfd);
                }
                if (std::get<0>(messageToSend) == false) {
                    close(c_sockfd);
                }
                ///PASSWORD
                response = readMessage(c_sockfd);
                messageToSend = checkResponse(parseBuffer(response, state),state,username,password);
                state++;
                std::cout << "response " << response << std::endl;
                std::cout << "message to send " << std::get<1>(messageToSend) << std::endl;
                send(c_sockfd, std::get<1>(messageToSend).c_str(), std::get<1>(messageToSend).length(), 0);
                if (time(NULL) - timeB > 45 ) {
                    close(c_sockfd);
                    return NULL;
                }
                if (std::get<0>(messageToSend) == false) {
                    close(c_sockfd);
                    return NULL;
                }
                
                while (1) {
                    if (time(NULL) - timeB > 45 ) {
                        close(c_sockfd);
                    
                    }
                    char firstByte = readByte(c_sockfd);
                    if(firstByte == 'I'){
                        response = readMessage(c_sockfd);
                        messageToSend = checkResponse(parseBuffer(response, state),state,username,password);
                        send(c_sockfd, std::get<1>(messageToSend).c_str(), std::get<1>(messageToSend).length(), 0);
                        if (std::get<0>(messageToSend) == false) {
                            close(c_sockfd);
                    
                        }
                    }
                    if(firstByte == 'F'){
                        char byte;
                        int computedCrc = 0, readBytes = 0;
                        
                        std::stringstream stream, tempHex, readCrc;
                        
                        std::string type = readWord(c_sockfd);
                        
                        if (type.compare("OTO") != 0 ) {
                            std::string badCheksum = "501 SYNTAX ERROR\r\n";
                            send(c_sockfd, badCheksum.c_str(), badCheksum.length(), 0);
                            
                        }
                        
                        int countOfBytes = std::atoi(readWord(c_sockfd).c_str()) + 4;
                        std::string crcR;
                        while(readBytes <= countOfBytes){
                            byte = readByte(c_sockfd);
                            
                            ///CRC
                            if (countOfBytes - readBytes > 4 ) {
                                computedCrc += byte;
                                stream << byte;
                            }else{
                                readCrc << byte;
                                crcR = readCrc.str();
                            }
                            readBytes++;
                        }
                        
                        tempHex << std::hex << computedCrc;
                        std::string hex = tempHex.str().c_str();
                        
                        std::cout << "hex: "<< hex << std::endl;
                        std::cout << "stream: "<< stream.str() << std::endl;
                        std::cout << computedCrc << " crc" << std::endl;
                        std::cout << crcR << " crc" << std::endl;
                        //std::cout << "rovna se?" << (std::stoi(crcR) == std::stoi(hex)) << std::endl;
                        int one = std::stoi(crcR);
                        int two = std::stoi(hex);
                        if ( one == two ) {
//                            std::cout << "rovna se" << readBytes   << std::endl;
//                            std::stringstream filename;
//                            filename << "foto" << (rand() % 1000) << ".png";
                            
//                            std::ofstream file (filename.str().c_str(), std::ios::out | std::ios::binary);
//                            file.write(stream.str().c_str(),readBytes);
//                            file.close();
                            std::string okCheck = "202 OK\r\n";
                            send(c_sockfd, okCheck.c_str(), okCheck.length(), 0);
                        }else{
                            std::string badCheksum = "300 BAD CHEKSUM\r\n";
                            send(c_sockfd, badCheksum.c_str(), badCheksum.length(), 0);
                        }
                        
                    }
                }
                
            }
        }
    }
    
    /* clean up */
    printf("Terminating server.\n");
    close(sockfd);
    exit(0);
}
