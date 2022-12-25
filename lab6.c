#include <stdlib.h>
#include <stdio.h>
#include "list.h"


void capitalize(char *data){
	int c_code = *data;
	if (c_code >= 97 && c_code<=122){
	    *data = (char)(c_code - 32);
	}
}


void str_work(List *line){
	Item *ptr = line->head, *ptr_prev = NULL;
	capitalize(&(ptr->data));
    while (ptr) {
    	if (ptr->data == ' ' || ptr->data == '\t'){
    		if(ptr->data == '\t'){
    			ptr->data = ' ';
    		}
    		if(ptr_prev->data == ' '){
    			list_remove(line, ptr);
    			ptr = ptr_prev->next;
    			if (!ptr){
    				break;
    			}
    		}
    	}
    	if (ptr_prev){
	    	if (ptr_prev->data == '.' || ptr_prev->data == '!' || ptr_prev->data == '?'){
	    		while(ptr && (ptr->data == ' ' || ptr->data == '\t')){
	    			list_remove(line, ptr);
	    			ptr = ptr_prev->next;

	    		}
	    		if(!ptr){
	    			break;
	    		}
	    		if (ptr->data !='.'){
	    			capitalize(&(ptr->data));
	    			list_insert(line, ptr_prev, '\n');
	    		}
	    	}
	    }
        ptr_prev = ptr;
        ptr = ptr->next;
    }
}


List *get_line(const char *prompt){
	printf("%s", prompt);
	List *l=list_new();
	char chr;
	while((chr = getchar()) != '\n'){
		if(chr == EOF){
			free(l);
			return NULL;
		}
		else{
			if(l->head || (chr != ' ' && chr !='\t')){
				list_push_back(l, chr);
			}
		}
	}
	return l;
}


int main(){
	List *line = get_line("Enter the line: ");
	while(line){
		str_work(line);
		list_print(line);
		list_delete(line);
		line = get_line("Enter the line: ");
	}
	return 0;
}
