#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main_test() {
	double last_num = 0;
    char line[256];
    char *last_line = NULL;
    FILE *fp = fopen("银行总金额变化文件.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    while (fgets(line, sizeof(line), fp)) {
        last_line = strdup(line);
    }

    if (last_line != NULL) {
        char *last_num_str = strrchr(last_line, ' ');
        if (last_num_str != NULL) {
            last_num = atoi(last_num_str);
        }
        free(last_line);
    }

    printf("The last number in the file is: %lf\n", last_num);
    fclose(fp);
    return 0;
}
