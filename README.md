# C-program-file-explorer
C Graphics File Explorer
Overview

This is a simple File Explorer application written in C using graphics.h. It allows users to navigate directories, view text files, and perform basic file operations in a graphical interface. It is designed for Windows systems using Turbo C/C++ or WinBGIm library.

Key Features

Scrollable directory listing with up to 10 files visible at a time.

Visual differentiation of folders and file types using simple icons:

Folders: Rectangle icon

Text files (.txt)

Image files (.jpg, .png)

Other files: Default icon

Navigate using arrow keys:

UP/DOWN to select files/folders

ENTER to open folders or view text files

BACKSPACE to go back to the previous folder

File operations:

C key: Copy the selected file (creates a copy with prefix COPY_)

D key: Delete the selected file

Text file viewer opens in a pop-up graphics window.

ESC key exits the program.

Requirements

Turbo C/C++ or any compiler that supports graphics.h.

WinBGIm graphics library if using modern compilers like Code::Blocks.

Include graphics.h and link libbgi.a in your project.

File Structure

file_explorer.c – main program file

README.md – this documentation

Compilation Instructions
Using Turbo C/C++:

Open Turbo C/C++ IDE.

Create a new project and add file_explorer.c.

Make sure graphics.h and conio.h are included in the compiler.

Compile and run the program.

Using Code::Blocks or Modern GCC:

Download WinBGIm graphics library:

WinBGIm download

Place graphics.h and winbgim.h in the compiler's include folder.

Place libbgi.a in the compiler's lib folder.

Compile using:

gcc file_explorer.c -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -o FileExplorer.exe


Run FileExplorer.exe.

How to Use

Launch the program.

Navigate using UP/DOWN arrows.

Press ENTER to:

Open a folder

Open a .txt file in a viewer

Press BACKSPACE to go to the previous folder.

Press C to copy the selected file (creates COPY_<filename>).

Press D to delete the selected file.

Press ESC to exit the program.

Notes

Maximum files per directory displayed: 10 (scrollable).

Supports folders, text files, and image files. Other file types are displayed with a default icon.

Text file viewer only supports .txt files.

File copy/delete operations are basic and do not handle subfolders.

Future Enhancements

Add PDF and other file viewers.

Add folder/file tree view.

Improve file operation handling (move, rename).

Support for drag-and-drop like selection.
