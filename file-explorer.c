#include <graphics.h>
#include <conio.h>
#include <dir.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100
#define DISPLAY_LIMIT 10

char currentPath[300] = "*.*";
char prevPaths[20][300];
int prevCount = 0;

// File type detection for icons/colors
int isFolder(char *name) {
    struct ffblk ff;
    if (findfirst(name, &ff, FA_DIREC) == 0)
        return 1; // it's a folder
    return 0;
}

int isTextFile(char *name) {
    char *ext = strrchr(name, '.');
    return (ext && strcmp(ext, ".txt") == 0);
}

int isImageFile(char *name) {
    char *ext = strrchr(name, '.');
    return (ext && (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".png") == 0));
}

void listFiles(char *path, char files[MAX_FILES][100], int *count) {
    struct ffblk ff;
    *count = 0;
    if (findfirst(path, &ff, FA_DIREC) == 0) {
        do {
            if (strcmp(ff.ff_name, ".") != 0 && strcmp(ff.ff_name, "..") != 0)
                strcpy(files[(*count)++], ff.ff_name);
        } while (findnext(&ff) == 0 && *count < MAX_FILES);
    }
}

void drawIcons(char files[MAX_FILES][100], int count, int highlight, int startIndex) {
    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(50, 20, "Graphical C File Explorer");
    outtextxy(50, 40, "ESC: Exit | ENTER: Open | BACKSPACE: Back | C: Copy | D: Delete");

    int endIndex = startIndex + DISPLAY_LIMIT;
    if (endIndex > count) endIndex = count;

    for (int i = startIndex; i < endIndex; i++) {
        int y = 80 + (i - startIndex) * 40;

        if (i == highlight) setcolor(RED);
        else setcolor(WHITE);

        // draw folder/file icon
        if (isFolder(files[i])) rectangle(30, y, 50, y + 20);       // folder icon
        else if (isTextFile(files[i])) rectangle(30, y, 50, y + 20); // text file icon
        else if (isImageFile(files[i])) rectangle(30, y, 50, y + 20); // image file icon
        else rectangle(30, y, 50, y + 20); // default file icon

        outtextxy(60, y, files[i]);
    }
}

void openTextFile(char *filepath) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) return;

    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    char line[200];
    int y = 20;
    while (fgets(line, sizeof(line), fp) != NULL && y < getmaxy() - 20) {
        outtextxy(10, y, line);
        y += 15;
    }
    fclose(fp);
    getch(); // wait for key press
}

void copyFile(char *source) {
    char dest[300];
    sprintf(dest, "COPY_%s", source);
    FILE *src = fopen(source, "rb");
    FILE *dst = fopen(dest, "wb");
    if (!src || !dst) return;
    char buffer[1024]; size_t n;
    while ((n = fread(buffer,1,sizeof(buffer),src))>0) fwrite(buffer,1,n,dst);
    fclose(src); fclose(dst);
}

void deleteFile(char *filename) {
    remove(filename);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    char files[MAX_FILES][100];
    int count = 0, highlight = 0, startIndex = 0;

    listFiles(currentPath, files, &count);
    drawIcons(files, count, highlight, startIndex);

    char ch;
    while ((ch = getch()) != 27) {
        if (ch == 0) { ch = getch();
            if (ch == 72) highlight--; // UP
            if (ch == 80) highlight++; // DOWN
        } else if (ch == 13) { // ENTER
            char newPath[300];
            sprintf(newPath, "%s\\%s", prevCount==0?".":prevPaths[prevCount-1], files[highlight]);
            struct ffblk ff;
            if (findfirst(newPath, &ff, FA_DIREC)==0) { // folder
                strcat(newPath,"\\*.*");
                prevCount++; strcpy(prevPaths[prevCount-1], newPath);
                strcpy(currentPath, newPath); listFiles(currentPath, files, &count);
                highlight = 0; startIndex = 0;
            } else if (isTextFile(files[highlight])) openTextFile(newPath);
        } else if (ch == 8) { // BACKSPACE
            if (prevCount>1) {
                prevCount--; strcpy(currentPath, prevPaths[prevCount-1]);
                listFiles(currentPath, files, &count);
                highlight = 0; startIndex = 0;
            }
        } else if (ch=='c'||ch=='C') copyFile(files[highlight]);
        else if (ch=='d'||ch=='D') { deleteFile(files[highlight]); listFiles(currentPath, files, &count); if(highlight>=count) highlight=count-1; }

        if(highlight<0) highlight=0;
        if(highlight>=count) highlight=count-1;
        if(highlight>=startIndex+DISPLAY_LIMIT) startIndex=highlight-DISPLAY_LIMIT+1;
        if(highlight<startIndex) startIndex=highlight;

        drawIcons(files,count,highlight,startIndex);
    }

    closegraph();
    return 0;
}
