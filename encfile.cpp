#include <memory.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <iostream>  
#include "openssl/aes.h"  
 
#pragma comment(lib,"libeay32.lib")  
  
void testAes(char inString[], int inLen, char passwd[], int pwdLen, bool encode)  
{  
    FILE * fw = fopen("codes", "wb");
    int i,j, len, nLoop, nRes;  
    char enString[1024];  
    char deString[1024];  
  
    unsigned char buf[16];  
    unsigned char buf2[16];  
    unsigned char aes_keybuf[32];  
    AES_KEY aeskey;  
  
    // 准备32字节(256位)的AES密码字节  
    memset(aes_keybuf,0x90,32);  
    if(pwdLen<32){ len=pwdLen; } else { len=32;}  
    for(i=0;i<len;i++) aes_keybuf[i]=passwd[i];  
    // 输入字节串分组成16字节的块     
    nLoop=inLen/16; nRes = inLen%16;  
    if(encode == true){
    	// 加密输入的字节串  
    	AES_set_encrypt_key(aes_keybuf,256,&aeskey);  
    	for(i=0;i<nLoop;i++){  
        	memset(buf,0,16);  
        	for(j=0;j<16;j++) buf[j]=inString[i*16+j];  
        	AES_encrypt(buf,buf2,&aeskey);  
        	for(j=0;j<16;j++) enString[i*16+j]=buf2[j];  
    	}  
    	if(nRes>0){  
        	memset(buf,0,16);  
        	for(j=0;j<nRes;j++) buf[j]=inString[i*16+j];  
        	AES_encrypt(buf,buf2,&aeskey);  
        	for(j=0;j<16;j++) enString[i*16+j]=buf2[j];  
        	//puts("encrypt");  
    	}  
    	enString[i*16+j]=0; 
	printf("The original string is:\n  %s ", inString);
       	printf("The encrypted string is:\n  %s ", enString);  
 	fputs(enString, fw);	
    }
    else if(encode == false){  
	    // 密文串的解密     
	    AES_set_decrypt_key(aes_keybuf,256,&aeskey);  
	    for(i=0;i<nLoop;i++){  
		memset(buf,0,16);  
		for(j=0;j<16;j++) buf[j]=inString[i*16+j];  
		AES_decrypt(buf,buf2,&aeskey);  
		for(j=0;j<16;j++) deString[i*16+j]=buf2[j];  
	    }  
	    if(nRes>0){  
		memset(buf,0,16);  
		for(j=0;j<16;j++) buf[j]=inString[i*16+j];  
		AES_decrypt(buf,buf2,&aeskey);  
		for(j=0;j<16;j++) deString[i*16+j]=buf2[j];  
		//puts("decrypt");  
	    }  
	    deString[i*16+nRes]=0;  
	    //比较解密后的串是否与输入的原始串相同  
    	    //if(memcmp(inString,deString,strlen(inString))==0)  
            //{ printf("test success\r\n");} else { printf("test fail\r\n");}  
            printf("The encrypted string is:\n  %s ", inString);  
            printf("The decrypted string is:\n  %s ", deString); 
    }
    fclose(fw);
}  
  
int main(int argc, char* argv[])  
{   
    if(argc != 4){
	    printf("wrong input");
	    return 1;
    } 
   //char inString[] = "This is a sample. I am a programer.\n";  
    //char passwd[] = "0123456789ABCDEFGHIJK";
    
    char ar[100];
    char* str1 = (char*)"enc";
    char* str2 = (char*)"dec";
    FILE * fp = fopen(argv[2], "rb");
    fgets(ar, 100, fp);
   
    if(strcmp(argv[1], str1) == 0)//加密
    {
	 testAes(ar, strlen(ar), argv[3], strlen(argv[3]), true);	 
    }
    else if(strcmp(argv[1], str2) == 0){//解密
        testAes(ar, strlen(ar), argv[3], strlen(argv[3]), false); 
    }
    fclose(fp);
    
    return 0;  
}  
