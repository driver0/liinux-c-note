#include <string.h>
#include <stdio.h>
#include <iconv.h> 

#define BUFF_LEN 512
char convert_buff[BUFF_LEN];

int code_convert(const char *fromcode,const char *tocode, char *inbuf, size_t *inlen, char *outbuf, size_t *outlen) {
	char *tmpin = NULL, *tmpout = NULL;
	iconv_t cd = NULL;
	
	tmpin = inbuf;
	tmpout = outbuf;

	cd = iconv_open(tocode, fromcode);
	if (cd == (iconv_t)-1) {
		perror("iconv_open");
		return -1;
	}

	if (iconv(cd, &tmpin, inlen, &tmpout, outlen) == (size_t)-1) {
		perror("iconv");
		iconv_close (cd);
		return -1;
	}
					    
	iconv_close (cd);
	return 0;
}

char *gbk_convert_utf8_str(char *in_str) {
	int ret = 0;
	size_t in_len = strlen(in_str);
	size_t out_len = sizeof(convert_buff);
				        
	memset(convert_buff, 0, out_len);
	ret = code_convert("GBK", "UTF-8", in_str, &in_len, (char *)convert_buff, &out_len);
	if (ret) {
		return NULL;
	}

	return convert_buff;
}

int main(void) {
	char in_str[BUFF_LEN] = {0}, *outstr_p = NULL;
	while (1) {
		scanf("%s", in_str);
		outstr_p = gbk_convert_utf8_str(in_str);
		printf("[%s:%d] outstr_p = %s\n\n", __func__, __LINE__, outstr_p);
	}
	return 0;
}
