#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include <sys/types.h>
#include <dirent.h>
#include<iostream>

#include<string>
#include<vector>
#include<algorithm>
#include"json.h"

using namespace std;

class Json{

    public:
	Json(json_t* ptr) {
	    _ptr = ptr;
	}
	Json() {
	}
	Json object_find(string filed) {

	    json_t* now;
	    now = _ptr->child;

	    while( strcmp(filed.c_str(),now->text)!=0 ) {
		now = now->next;
	    }        
	    return Json(now->child);
	}
	/*
	   string get(){
	   return string(_ptr->text);
	   }
	   */
	string value_get() {

	    if(_ptr->text == NULL) return "";
	    return string(_ptr->text);
	}

	vector<Json> array_get() {

	    vector<Json> result;

	    json_t* now;
	    now = _ptr->child;

	    if(now == NULL) return result;

	    result.push_back(Json(now));

	    while(now->next!=NULL) {
		now = now->next;
		result.push_back(Json(now));
	    } 

	    return result;
	}

    private:
	json_t* _ptr;

};

struct People{
    string id;
    int likeTimes;

    bool operator < (const People e) const{
	if(likeTimes != e.likeTimes) return likeTimes > e.likeTimes;
	if(id != e.id) return id < e.id;
    }
};

vector<People> people;
vector<string> userPosts;
json_t *document;
Json root;
string userID;

json_t* parsing(const char *jsonFilePath);
void likes_mapping();
void likes_most();
void user_posts_saving();

int main(){
    DIR *dir;
    struct dirent *ptr;
    const char *path = "./data/posts/";
    dir = opendir(path);

    int count = 0;
    people.clear();
    userPosts.clear();

    document = NULL;
    userID = "100000154563058";

    while((ptr = readdir(dir)) != NULL){
	count++;
	if(count <= 2);
	else{
	    string tmp = path;
//	    printf("%s\n", ptr->d_name);
	    tmp += ptr->d_name;
	    document = parsing((tmp + "/likes.json").c_str());
	    if(document != NULL){
		root = Json(document);
		likes_mapping();
		json_free_value(&document);
	    }
	    document = parsing((tmp + "/comments.json").c_str());
	    if(document != NULL){
		user_posts_saving();
		json_free_value(&document);
	    }        
	}
    }
    likes_most();
    closedir(dir);
    return 0;
}


json_t* parsing(const char *jsonFilePath){
    FILE *fp;
    json_t *tmp = NULL;
    //printf("%s\n", jsonFilePath);
    fp = fopen(jsonFilePath,"r");
    if(fp == NULL){
	printf("couldn't open the file!!\n");
	return NULL;
    }
    else{
	//printf("file open!!\n");	
	if((json_stream_parse(fp, &tmp)) == JSON_OK){
	    //printf("parse OK!!\n");
	}else{
	    printf("QQ!!\n");
	}
    }
    fclose(fp);
    return tmp;
}

void likes_mapping(){
    Json data = root.object_find("data");
    vector<Json> tmp = data.array_get();
    if(tmp.size() != 0){
	for(int i = 0; i < tmp.size(); i++){
	    Json id = tmp[i].object_find("id");
	    string idString = id.value_get();
	    //cout << idString << endl;
	    //if(idString == userID) printf("自讚！！\n");
	    bool flag = false;
	    for(int j = 0; j < people.size(); j++){
		if(people[j].id == idString){
		    people[j].likeTimes++;
		    flag = true;
		}
	    }
	    if(!flag){
		People tmp = (People) {idString, 1};
		people.push_back(tmp);
	    }
	}
    }
}

void likes_most(){
    sort(people.begin(), people.end());
    printf("Most Like:\n");
    int cnt = 0;
    for(int i = 0; i < people.size() && cnt < 10; i++){
	if(people[i].id != userID){
	    cnt++;
	    printf("%s :%d likes!!\n", people[i].id.c_str(), people[i].likeTimes);
	}
    }
}

void user_posts_saving(){
    Json data = root.object_find("data");
    vector<Json> tmp = data.array_get();
    if(tmp.size() != 0){
	for(int i = 0; i < tmp.size(); i++){
	    Json from = tmp[i].object_find("from");
	    //cout << from.get() << endl;
	    //cout << from.value_get() << endl;
	    Json id = from.object_find("id");
	    string idString = id.value_get();
	    //cout << id.value_get() << endl;
	    if(idString == userID){
		Json message = tmp[i].object_find("message");
		//cout << message.value_get() << endl;
		userPosts.push_back(message.value_get());
	    }
	}
    }
}
