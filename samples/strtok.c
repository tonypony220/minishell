#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	 char test[80], blah[80];
     char *sep = "\\/:;=-.";
     char *word, *phrase, *brkt, *brkb;

     strcpy(test, "This;is.a:test:of=the/string\\tokenizer-function.");

     word = strtok(test, sep);
	 while (word)
     {
		 printf("%s\n", word);
		 printf(">> %s\n", brkt);
         word = strtok(NULL, "/");
        // strcpy(blah, "blah:blat:blab:blag");

        // for (phrase = strtok_r(blah, sep, &brkb);
        //      phrase;
        //      phrase = strtok_r(NULL, sep, &brkb))
        // {
        //     printf("So far we're at %s:%s\n", word, phrase);
        // }
     }
	 system("leaks a.out");
}
