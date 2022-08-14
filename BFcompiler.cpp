//
// Created by mrybs on 13.08.22.
//

#include "BFcompiler.h"

std::string BFcompiler::simplification(std::string code){
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

std::string BFcompiler::compile(std::string code){
    std::string result = "#include<iostream>\n"
                         "#include<vector>\n"
                         "#include<unistd.h>\n"
                         "#include<termios.h>\n"
                         "#include<string>\n"
                         "using namespace std;"
                         "char g(){"
                         "char b=0;"
                         "struct termios c={0};"
                         "fflush(stdout);"
                         "if(tcgetattr(0,&c)<0)perror(\"tcsetattr()\");"
                         "c.c_lflag&=~ICANON;"
                         "c.c_lflag&=~ECHO;"
                         "c.c_cc[VMIN]=1;"
                         "c.c_cc[VTIME]=0;"
                         "if(tcsetattr(0,TCSANOW,&c)<0)perror(\"\");"
                         "if(read(0,&b,1)<0)perror(\"read()\");"
                         "c.c_lflag|=ICANON;"
                         "c.c_lflag|=ECHO;"
                         "if(tcsetattr(0,TCSADRAIN,&c)< 0)perror(\"\");"
                         "return b;"
                         "}"
                         "string d(string a){"
                         "return a;"
                         "}"
                         "void e(string a){"
                         "long b=0;"
                         "vector<char>c;"
                         "c.push_back(0);"
                         "int d=0;"
                         "for(long i=0;i<a.size();i++){"
                         "if(a[i]=='>'){"
                         "b++;"
                         "if(c.size()<=b)"
                         "c.push_back(0);"
                         "}"
                         "if(a[i]=='<'){"
                         "b--;"
                         "if(b<0){"
                         "throw overflow_error(\"Out of range, current cell is \"+to_string(b)+\". Minimum is 0\");"
                         "}"
                         "}"
                         "if(a[i]=='+')"
                         "c[b]++;"
                         "if(a[i]=='-')"
                         "c[b]--;"
                         "if(a[i]=='['){"
                         "d=1;"
                         "if(c[b]==0){"
                         "while(d>0){"
                         "i++;"
                         "if(a[i]=='[')d++;"
                         "if(a[i]==']')d--;"
                         "}"
                         "}"
                         "}"
                         "if(a[i]==']'){"
                         "d=1;"
                         "if(c[b]!=0){"
                         "while(d>0){"
                         "i--;"
                         "if(a[i]=='[')d--;"
                         "if(a[i]==']')d++;"
                         "}"
                         "}"
                         "}"
                         "if(a[i]=='.')"
                         "cout<<c[b];"
                         "if(a[i]==',')"
                         "c[b]=g();"
                         "}"
                         "}"
                         "int main(){"
                         "string a=\""+code+"\";"
                         "a=d(a);"
                         "try{"
                         "e(a);"
                         "}catch(overflow_error j){cout<<j.what();}"
                         "return 0;"
                         "}";
    return result;
}
