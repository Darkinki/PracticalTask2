#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define max_stat 1000
//1
struct BigInteger {
    int digits[max_stat];
    int length;
    bool sign;
};

void setHex(struct BigInteger *bi, char *hex) {
    int len = strlen(hex);
    int i, j;
    for (i = 0, j = len - 1; i < len; i++, j--) {
        if (hex[j] >= '0' && hex[j] <= '9') {
            bi->digits[i] = hex[j] - '0';
        } else if (hex[j] >= 'a' && hex[j] <= 'f') {
            bi->digits[i] = hex[j] - 'a' + 10;
        } else if (hex[j] >= 'A' && hex[j] <= 'F') {
            bi->digits[i] = hex[j] - 'A' + 10;
        }
    }
    bi->length = len;
}

void getHex(struct BigInteger *bi, char *hex) {
    int i, j;
    for (i = bi->length - 1, j = 0; i >= 0; i--, j++) {
        if (bi->digits[i] < 10) {
            hex[j] = bi->digits[i] + '0';
        } else {
            hex[j] = bi->digits[i] - 10 + 'a';
        }
    }
    hex[bi->length] = '\0';
}
//2
void INV(struct BigInteger *bi) {
    int i;
    for (i = 0; i < bi->length; i++) {
        bi->digits[i] = ~bi->digits[i];
    }
}

void XOR(struct BigInteger *bi1, struct BigInteger *bi2) {
    int i;
    for (i = 0; i < bi1->length; i++) {
        bi1->digits[i] ^= bi2->digits[i];
    }
}

void OR(struct BigInteger *bi1, struct BigInteger *bi2) {
    int i;
    for (i = 0; i < bi1->length; i++) {
        bi1->digits[i] |= bi2->digits[i];
    }
}

void AND(struct BigInteger *bi1, struct BigInteger *bi2) {
    int i;
    for (i = 0; i < bi1->length; i++) {
        bi1->digits[i] &= bi2->digits[i];
    }
}

void shiftR(struct BigInteger *bi, int n) {
    int i;
    for (i = 0; i < bi->length - n; i++) {
        bi->digits[i] = bi->digits[i + n];
    }
    for (; i < bi->length; i++) {
        bi->digits[i] = 0;
    }
}

void shiftL(struct BigInteger *bi, int n) {
    int i;
    for (i = bi->length - 1; i >= n; i--) {
        bi->digits[i] = bi->digits[i - n];
    }
    for (; i >= 0; i--) {
        bi->digits[i] = 0;
    }
}

void ADD(struct BigInteger *bi1, struct BigInteger *bi2, struct BigInteger *bi3){
    int inHead = 0;
    int i;

    for (i = 0; i < bi1->length || i < bi2->length; i++) {
        int sum = bi1->digits[i] + bi2->digits[i] + inHead;
        bi3->digits[i] = sum % 16;
        inHead = sum / 16;
    }

    if (inHead > 0) {
        bi3->digits[i] = inHead;
        i++;
    }

    bi3->length = i;
}

void SUB(struct BigInteger *bi1, struct BigInteger *bi2, struct BigInteger *bi3) {
    int remainder = 0;
    int i;

    for (i = 0; i < bi1->length || i < bi2->length; i++) {
        int dif = bi1->digits[i] - bi2->digits[i] - remainder;
        for (i = 0; i < bi1->length || i < bi2->length; i++) {
            int diff = bi1->digits[i] - bi2->digits[i] - remainder;

            if (diff < 0) {
                diff += 16;
                remainder = 1;
            } else {
                remainder = 0;
            }

            bi3->digits[i] = diff;
        }

        while (i > 0 && bi3->digits[i - 1] == 0) {
            i--;
        }

        bi3->length = i;
    }
}

int main() {
    struct BigInteger bi1, bi2;
    char hex1[max_stat];
    char hex2[max_stat];
    setHex(&bi1, "51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    getHex(&bi1, hex1);
    printf("%s\n", hex1);
    setHex(&bi2, "403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");
    getHex(&bi2, hex2);
    printf("%s\n", hex2);
    printf("now XOR:\n");
    XOR(&bi1, &bi2);
    getHex(&bi1, hex1);
    printf("%s\n", hex1);
}
