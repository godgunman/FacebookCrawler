#include <string>
#include <iostream>
#include <stdio.h>
#include <set>
const int L = 10000;

std::set<long long> t;

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
	if(fgets(buffer, 128, pipe) != NULL)
	    result += buffer;
    }
    pclose(pipe);
    return result;
}

int main(int argc, char* argv[]) {

    if(argc !=3 ) {
	puts("error argument!! ");
	puts("./search dir_path search_content");
	return 0;
    }

    char command[L];
    sprintf(command,"find %s | grep -R %s %s* | cut -f 1 -d ':' | sort | uniq",argv[1],argv[2],argv[1]);
    printf("command::\n %s \n",command);

    std::string result = exec( command ) ;

    char result_char[L];
    long long uid, pid;
    strcpy(result_char, result.c_str());

    char* token;
    token = strtok(result_char,"\n");
    while(token!=NULL) {

	char parse[L];
	sprintf(parse,"%s%%lld_%%lld/%%*c",argv[1]);
	sscanf(token,parse,&uid,&pid);

//	printf("%s\n %s\n",parse, token);
//	printf("%lld %lld\n",uid,pid);

	token = strtok(NULL,"\n");
//	sscanf(result_char,"../facebook/data/posts/%lld_%lld/content.json",&uid ,&pid);
  
	if(t.find(uid*pid)!=t.end()) continue;
	t.insert(uid*pid);

	char open_chrome[L];
	sprintf(open_chrome,"open -a /Applications/Google\\ Chrome.app/ ""https://www.facebook.com/%lld/posts/%lld""",uid,pid);
//	puts(open_chrome);
	system(open_chrome);
    }
}
