/*
 *
 * Copyright (c) 2000 - 2013 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <SecCryptoSvc.h>

int main(int argc, char** argv)
{
	char* pKey = NULL;
	char* pId = NULL;
	char* pDuid = NULL;
	char info[] = {0xca, 0xfe, 0xbe, 0xbe, 0x78, 0x07, 0x02, 0x03};
	bool result = true;
	int keyLen = 20;
	char *pKeyVersion = NULL;
	const char *version = "1.0#";
/*	if(argc != 2)
	{
		fprintf(stderr, "Invalid Input [%d]\n", argc);
		return 0;
	}
	
	keyLen = atoi(argv[1]);
	if(keyLen <= 0)
	{	
		fprintf(stderr, "Failed to get duild\n");
		return 0;
	}
*/
	pKey = (char*)malloc(keyLen);
	if(pKey == NULL)
	{
		return 0;
	}
	if(SecFrameGeneratePlatformUniqueKey(keyLen, pKey) != true)
	{
		free(pKey);
		//fprintf(stderr, "Failed to get duid\n");
		return 0;
	}

	pDuid = (char*)malloc(keyLen);
	if(pDuid == NULL)
	{
		free(pKey);
		return 0;
	}
    PKCS5_PBKDF2_HMAC_SHA1(info, 8, (unsigned char*)pKey, keyLen, 1, keyLen, (unsigned char*)pDuid);

	pId = Base64Encoding(pDuid, keyLen);
	if(pId == NULL) {
		free(pKey);
		free(pDuid);
		return 0;
	}
//	printf("%s", pId);

	pKeyVersion = (char*)calloc(strlen(pId)+strlen(version)+1, sizeof(char));
	if(pKeyVersion == NULL)
	{
		free(pKey);
		free(pDuid);
		free(pId);
		return 0;
	}
	strncpy(pKeyVersion, version, strlen(version));
	strncat(pKeyVersion, pId, strlen(pId));
	printf("%s", pKeyVersion);

	free(pKeyVersion);
	free(pId);
	free(pKey);
	free(pDuid);
	
	return 1;
}

