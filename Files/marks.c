#include <stdio.h>

int main(int argc, char *argv[]) {
	char string[64];
	int  num;
	FILE *fp;
    int count = 0;
    int pass = 0;
    float pct = 0;
    

	fp = fopen(argv[1], "r");
	if (fp != NULL) {
		//file was opened
		while (!feof(fp)) {
			//there is still something left to read
			if (fscanf(fp, "%d",  &num) != 1)
				break; //the file format is not as i expected
			count++;
            if (num >= 50)
            {
                /* code */
                pass++;
            }
		}
        pct = ((float)pass/count) * 100;
        printf("Pass rate is %d of %d (%.2f)", pass, count, pct);
		fclose(fp);
	} else {
        printf("failed to open %s", argv[1]);
    }
	
	return 0;
}