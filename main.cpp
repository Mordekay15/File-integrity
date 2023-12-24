#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "md5.h"
#include "sha-256.h"
#include "keccak.h"


void get_par(std::map<std::string, std::string> &map_par , std::string &par)
{
    par.erase(0, par.find(" ")+1);

    int ret = par.find("-i ");
    if(ret != -1) {
        par.erase(0, par.find("-i ") + 3);
        map_par["input_file"] = par.substr(0, par.find(" "));
        par.erase(0, par.find(" ") + 1);
    }
    else {
        printf("No reference file\n");
        exit(-1);
    }

     map_par["check_file"] = par.substr(0, par.find(" "));
     if (map_par["check_file"] == "") {
         printf("No file to check\n");
         exit(-1);
     }
     par.erase(0, par.find(" ") + 1);


}


void open_file(std::map<std::string, std::string> &map_par) {

    std::ifstream input_file(map_par["input_file"]);
    std::stringstream buffer;
    buffer << input_file.rdbuf();
    map_par["input_buf"] = buffer.str();
    if(map_par["input_buf"].empty()) {
        printf("The reference file is empty\n");
        exit(-1);
    }

    std::ifstream check_file(map_par["check_file"]);
    std::stringstream buffer_;
    buffer_ << check_file.rdbuf();
    map_par["check_buf"] = buffer_.str();
    if(map_par["check_buf"].empty()) {
        printf("The checked file is empty\n");
        exit(-1);
    }
}


void md5 (std::map<std::string, std::string> &map_par) {
    open_file(map_par);

    MD5 md5;

    printf("Reference hash       : %s\n", md5(map_par["input_buf"]).c_str());
    printf("Hash of file to check: %s\n", md5(map_par["check_buf"]).c_str());

    if(md5(map_par["input_buf"]) == md5(map_par["check_buf"])) {
        printf("Integrity is correct\n");

    }
    else {
        printf("Integrity is BROCKEN !\n");
    }
}


void sha_256(std::map<std::string, std::string> &map_par){
    open_file(map_par);

    SHA256 sha256;

    printf("Reference hash       : %s\n", sha256(map_par["input_buf"]).c_str());
    printf("Hash of file to check: %s\n", sha256(map_par["check_buf"]).c_str());

    if(sha256(map_par["input_buf"]) == sha256(map_par["check_buf"])) {
        printf("Integrity is correct\n");

    }
    else {
        printf("Integrity is BROCKEN !\n");
    }
}


void keccak(std::map<std::string, std::string> &map_par, Keccak::Bits bits){
    open_file(map_par);

    Keccak keccak(bits);
    printf("Reference hash       : %s\n", keccak(map_par["input_buf"]).c_str());
    printf("Hash of file to check: %s\n", keccak(map_par["check_buf"]).c_str());

    if(keccak(map_par["input_buf"]) == keccak(map_par["check_buf"])) {
        printf("Integrity is correct\n");

    }
    else {
        printf("Integrity is BROCKEN !\n");
    }
}



int main(int argc, char** argv)
{
    std::string par_1 = "./file_integrity -i test.txt a.txt -keccak_512";

    std::string par;
    for(int i = 0; i < argc; i++) {
        std::string str(argv[i]);
	par += str;
	par += " ";
    }
    
    std::map<std::string, std::string> map_par;

    get_par(map_par, par);

    int ret = par.find("-md5");
    if(ret != -1) {
        md5(map_par);
        return 0;
    }

    ret = par.find("-sha_256");
    if(ret != -1) {
        sha_256(map_par);
        return 0;
    }

    ret = par.find("-keccak_224");
    if(ret != -1) {
        keccak(map_par, Keccak::Keccak224);
        return 0;
    }

    ret = par.find("-keccak_256");
    if(ret != -1) {
        keccak(map_par, Keccak::Keccak256);
        return 0;
    }

    ret = par.find("-keccak_384");
    if(ret != -1) {
        keccak(map_par, Keccak::Keccak384);
        return 0;
    }

    ret = par.find("-keccak_512");
    if(ret != -1) {
        keccak(map_par, Keccak::Keccak512);
        return 0;
    }

    printf("Hash function %s is not supported", par.c_str());

    return 0;
}
