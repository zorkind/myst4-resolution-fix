char strMySystemFile[255];

int WriteToFile(char * strFileSection, char * strKey, char * strValue)
{
	//if ((strlen(strKey) > MAX_PATH) | (strlen(strValue) > MAX_PATH))
	//	return -1;

	return WritePrivateProfileString(strFileSection, strKey, strValue, strMySystemFile);
}

char* ReadFromFile(char* strFileSection, char* strKey)
{
    static char strValue[MAX_PATH];

    DWORD lngRtn = GetPrivateProfileStringA(
        strFileSection,
        strKey,
        "0",
        strValue,
        sizeof(strValue),
        strMySystemFile
    );

    if (lngRtn == 0)
        return NULL;

    return strValue;
}