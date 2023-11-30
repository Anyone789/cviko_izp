// ujistete se, ze spravne pracujete s pameti -  alokovana pamet je uvolnena
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Initial string content
const char *str_init = "Hello World!";

// Find first substring occurrence in a string and return its starting position.
// Return -1 if the string does not contain substring.
int find_substr(char *str, char *substr) {
    int i=0;
    while (str[i] != '\0')
    {
        if (str[i] == substr[0])
        {
            int j=0;
            while (substr[j] != '\0')
            {
                if (str[i+j] != substr[j])
                {
                    break;
                }
                j++;
            }
            if (substr[j] == '\0')
            {
                return i;
            }
        }
        i++;
    }
    return -1;
}

// Replace same-length substrings in a string.
void replace_same_length(char *str, char *substr, char *new_substr) {
    int pos = find_substr(str, substr);
    if (pos == -1)
    {
        return;
    }
    int i=0;
    while (new_substr[i] != '\0')
    {
        str[pos+i] = new_substr[i];
        i++;
    }

}

// Replace substring in a string with any new substring.
// Returns new string with replaced substring or NULL in case of any error.
char *replace(char *str, char *substr, char *new_substr) {
    // pri nahrazovani retezce je potreba postupovat jinak,
    // pokud je new_substr kratsi nez substr a jinak pokud je
    // new_substr delsi nez substr

    // new_substr < substr
    // 1. priradit obsah new_substr do str na odpovidajici misto
    // 2. posunout znaky v str, aby zaplnily "uvolnene" misto
    // 3. nezapomenout na '\0'
    // 4. realloc


    // new_substr > substr
    // 1. realloc aby se cely zvetseny retezec vlezl do pameti
    // 2. posunout znaky aby byl prostor pro new_substr
    // 3. zapsat obsah new_substr do str na spravne misto
    // 4. nezapomenout na '\0'

    int pos = find_substr(str, substr);
    if (strlen(substr)>strlen(new_substr)) {
        for (int i=0; new_substr[i] != '\0'; i++) {
            str[pos+i] = new_substr[i];
        }
        int d = strlen(substr)-strlen(new_substr);
        for (int j=(pos+strlen(new_substr)); str[j] != '\0'; j++) {
            str[j] = str[j+d];
        }
        str = realloc(str, (strlen(str)-d)*sizeof(char));
        str[strlen(str)] = '\0';
    }

    if (strlen(substr)<strlen(new_substr)) {
        int d = strlen(new_substr)-strlen(substr);
        str = realloc(str, (strlen(str)+d)*sizeof(char));
        for (int i=0; new_substr[i] != '\0'; i++) {
            str[pos+i] = new_substr[i];
        }
        str[strlen(str)] = '\0';
    }

    else {
        replace_same_length(str, substr, new_substr);
    }
    return str;
}

// vlastni funkce pro kopirovani retezcu
// parametry funkce jsou ukazatele na zdrojovy retezec sourceStr
// a cilovy retezec targetStr
// funkce provede "hlubokou kopii" :
// alokuje potrebnu pamet a prekopiruje obsah zdrojoveho retezce do ciloveho
void myStrCopy (char * targetStr, const char * sourceStr)
{
    targetStr = realloc(targetStr, strlen(sourceStr)*sizeof(char));
    for (int i=0; sourceStr[i] != '\0'; i++) {
        targetStr[i] = sourceStr[i];
    }
    targetStr[strlen(targetStr)] = '\0';
}

int main() {
    // Allocate new string.
    char *str = (char *)malloc(strlen(str_init) + 1);
    char *str2 = (char *)malloc(strlen(str_init) + 1);
    myStrCopy(str, str_init);
    if (str == NULL) {
        return 1;
    }
    // Replace substring with a new same-length substring.
    replace_same_length(str, "World!", "worlds");
    printf("%s\n", str);
    myStrCopy(str2, str);
    // Replace substring with a new shorter substring.
    str = replace(str, "worlds", "IZP!");
    if (str == NULL) {
        return 1;
    }
    printf("%s\n", str);
    // Replace substring with a new longer substring.
    str = replace(str, "IZP!", "World!");
    if (str == NULL) {
        return 1;
    }
    printf("%s\n", str);


    // test zameny uprostred retezce
    str2 = replace(str2, "ello", "i");
    if (str2 == NULL) {
        return 1;
    }
    printf("%s\n", str2);

    str2 = replace(str2, "i", "elp the ");
    if (str2 == NULL) {
        return 1;
    }
    printf("%s\n", str2);


    // Cleanup
    free(str);


    printf("Successully replaced all substrings!\n");
    // Allocate and initialize a new string.
    str = (char *)malloc(strlen(str_init) + 1);
    myStrCopy(str, str_init);

    // Try using replace with substring that is not in the string.
    str = replace(str, "worlds", "World!");
    if (str == NULL) {
        free(str);
        return 1;
    }
    printf("%s\n", str);
    free(str2);
    return 0;
}

