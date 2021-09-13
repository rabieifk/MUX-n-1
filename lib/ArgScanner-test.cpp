#include "ArgScanner.hpp"


int main(){
    const char * argvTest[] = {"main.exe", "-path", "c:\\hello", "-x", "-n", "5", "-w", "6k", "-m"};
    ArgReader args(argvTest, 7); 

    try{
        auto testVal = args.GetValInt("-x"); 
        printf("* Failed Testing -x: did not throw exception for empty arg.\n");
    } catch(enArgErrros ex){
        printf("%s Testing -x\n", (ex == NoValueFoundForArg) ? "OK" : "* Failed");
    }
    catch(...){
        printf("**Failed Testing -x, Unknown Exeption release. \n");
    }

    try{
        auto testVal = args.GetValInt("-w");
        printf("* Failed Testing -w: did not throw exception for non-numeric arg.\n");
    } catch(enArgErrros ex){
        printf("%s Testing -w\n", (ex == NonNumericCharsFoundInNumber) ? "OK" : "* Failed");
    }
    catch(...){
        printf("**Failed Testing -w, Unknown Exeption release. \n");
    }

    try{
        auto testVal = args.GetValInt("-m");
        printf("* Failed Testing -m: did not throw exception for empty arg.\n");
    } catch(enArgErrros ex){
        printf("%s Testing -m\n", (ex == NoValueFoundForArg) ? "OK" : "* Failed");
    }
    catch(...){
        printf("**Failed Testing -m, Unknown Exeption release. \n");
    }

    try{
        auto testVal = args.GetValInt("-k");
        printf("* Failed Testing -k: did not throw exception for non-found arg.\n");
    } catch(enArgErrros ex){
        printf("%s Testing -k\n", (ex == ArgNotFound) ? "OK" : "* Failed");
    }
    catch(...){
        printf("**Failed Testing -k, Unknown Exeption release. \n");
    }

    auto testInt = args.GetValInt("-n");
    printf("%s Testing Value -n \n", (testInt != 5) ? "* Failed": "OK");

    auto testVal = args.GetVal("-Path");
    printf("%s Testing case-insensitive \n", (strcmp(testVal, "c:\\hello")!=0) ? "* Failed" : "OK");

    return 0;
}