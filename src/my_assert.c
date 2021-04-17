/** assert.c ~ assert logic used if assumptions are bad
 */
void my_assert(int line_num, char *filename)
{
    if (filename == NULL)
        filename = "NULL";

    char *basename_p = filename;
    char line_str[120]="...not-implemented...\n"; 
    int n;

    /* shorten full path in filename to just base name
    */
    for (n=strlen(filename)-1; n >= 0; n--)
    {
        if ( filename[n] == '/' )
        {
            basename_p = &filename[n];
            break;
        }
    }
    /* read line of assert code that fired
    strcpy(line_str, "");
    FILE *fp = fopen(filename, "r");
    for (n=0; n < line_num; n++)
        getline(sizeof(line_str));
    if ( n < line_num )
        sprintf(line_str, "<error, could only read %d lines>", n);
    */

    printf("\n\nAssert:  line %d, file %s\n", line_num, filename);
    printf("line-text: \"%s\"\n\n", line_str);

    #ifndef TEST_ASSERT
    exit(-1);
    #endif
}
