//
// Created by mrybs on 13.08.22.
//

#include "BFinterpreter.h"


char BFinterpreter::getch() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN]  = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return buf;
}
std::string BFinterpreter::simplification(std::string code){
    std::string result = "";
    std::vector<std::string>lines;
    lines.push_back("");
    for(long l = 0; l < result.size(); l++){
        if(result[l] == '\n')
            lines.push_back("");
        else
            lines[lines.size() - 1] += result[l];
    }
    for(long l = 0; l < lines.size(); l++){
        std::string cline = "";
        bool isComment = false;
        for(char c : lines[l])
            if(c == '!') isComment = true;
            else if(!isComment) cline += c;
        lines[l] = cline;
    }
    result = "";
    for(std::string line : lines){
        result += line;
    }
    return result;
}
void BFinterpreter::interpretation(std::string code){
    long currentCell = 0;
    std::vector<char>cells;
    cells.push_back(0);
    int lvl = 0;
    for(long i = 0; i < code.size(); i++){
        if (code[i] == '>') {
            currentCell++;
            if (cells.size() <= currentCell)
                cells.push_back(0);
        }
        if(code[i] == '<') {
            currentCell--;
            if (currentCell < 0) {
                throw std::overflow_error("Out of range, current cell is " + std::to_string(currentCell) + ". Minimum is 0");
            }
        }
        if(code[i] == '+')
            cells[currentCell] ++;
        if(code[i] == '-')
            cells[currentCell] --;
        if(code[i] == '[') {
            lvl = 1;
            if(cells[currentCell] == 0) {
                while(lvl > 0){
                    i ++;
                    if(code[i] == '[') lvl ++;
                    if(code[i] == ']') lvl --;
                }
            }
        }
        if(code[i] == ']') {
            lvl = 1;
            if(cells[currentCell] != 0) {
                while(lvl > 0){
                    i --;
                    if(code[i] == '[') lvl --;
                    if(code[i] == ']') lvl ++;
                }
            }
        }
        if(code[i] == '.')
           std::cout << cells[currentCell];
        if(code[i] == ',')
            cells[currentCell] = getch();
    }
}