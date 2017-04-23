#ifndef MYARDUINOPROJECT_STRINGUTILS_H
#define MYARDUINOPROJECT_STRINGUTILS_H


int len(char* data) {
    int i = 0;
    while (data[i++]);
    return i - 1;
}

int indexOf(char* data, char c, int startPosition) {

    if (len(data) < startPosition) return -1;

    int position = startPosition;
    while (position < len(data)) {
        if (data[position++] == c) {
            return position - 1;
        }
    }

    return -1;
}


// void strcpy(const char* src, ) {

// }

int strCmp(const char* s1, const char* s2) {
    while(*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

#endif