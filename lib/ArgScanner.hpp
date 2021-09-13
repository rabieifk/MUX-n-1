#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

enum enArgErrros
{
    NoError,
    NoValueFoundForArg,
    ArgNotFound,
    NonNumericCharsFoundInNumber,
};

class ArgReader{
    public:
	int arg_count;
	const char ** args;
	ArgReader(const char * args_list[], int count){
        args = args_list;
		arg_count = count;
	}
	bool isAllNumeric(const char *a){
		for ( ; *a != 0 ; a++) {
			if(!isdigit(*a))
			  return false;
		}
		return true;
	}
    bool IsSet(const char *arg_name){
        if (GetVal(arg_name, false) != NULL)
            return true;
        return false;
    }
	const char* GetVal(const char *arg_name, bool val_must_be_non_empty = false) 
	{
		for(int i = 0 ; i < arg_count ; i++) {
			if (stricmp(arg_name, args[i]) == 0) {
				if (i+1 < arg_count){
					if (args[i+1][0] != '-') {
                        if (val_must_be_non_empty && args[i+1][0]==0)
                            throw NoValueFoundForArg;
                        return args[i+1];
                    }
					else { //args[i+1][0] == '-' ==> empty value
                        if (val_must_be_non_empty)
                            throw NoValueFoundForArg;
                        return "";
                    }
				} else if (i+1 == arg_count){ // last Arg, empty
                    if (val_must_be_non_empty)
                        throw NoValueFoundForArg;
                    return "";
                }
			}
		}
        if (val_must_be_non_empty)
            throw ArgNotFound;
        return NULL; // arg_name Not found
	}

    void printAll() {
        for (int i = 0; i < arg_count; i++)
            printf("args[%d] = %s \n", i, args[i]);
    }

	int GetValInt(const char * arg_name) {
		auto arg_val = GetVal(arg_name, true);
        if (!isAllNumeric(arg_val))
            throw NonNumericCharsFoundInNumber;
		return atoi(arg_val);
         
	}
};
