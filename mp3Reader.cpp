#include <iostream>
#include <Windows.h>
#include <memory>
#include <string>

using namespace std;

struct MP3Header {
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
};

int main() {
    
    HANDLE hFile = CreateFile(/*MP3 File Name*/, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "Failed to open the MP3 file" << endl;
        return 1;
    }

    SetFilePointer(hFile, -128, NULL, FILE_END);

    unique_ptr<MP3Header> header = make_unique<MP3Header>();
    if (!header) {
        cout << "Failed to allocate memory" << endl;
        CloseHandle(hFile);
        return 1;
    }

    DWORD bytes;
    if (!ReadFile(hFile, header.get(), sizeof(MP3Header), &bytes, NULL) || bytes != sizeof(MP3Header)) {
        cout << "Failed to read file" << endl;
        CloseHandle(hFile);
        return 1;
    }

    if (strncmp(header->tag, "TAG", 3) == 0) {
        cout << "Title: " << header->title << endl;
        cout << "Artist: " << header->artist << endl;
        cout << "Album: " << header->album << endl;
    } else {
        cout << "Tag was not found" << endl;
    }

    cout << endl;


    while(true) {

        cout << "1: Change title" << endl;
        cout << "2: Change artist" << endl;
        cout << "3: Change album" << endl;
        cout << "4: Print header" << endl;
        cout << "5: Exit" << endl;

        int choice;
        cin >>  choice;

        switch (choice)
        {
        case 1: {
            string newTitle;
            cout << "Write new title: " << endl;
            cin >> newTitle;

            strncpy(header->title, newTitle.c_str(), sizeof(header->title));
            SetFilePointer(hFile, -128, NULL, FILE_END);

            DWORD bytes;
            if (!WriteFile(hFile, header.get(), sizeof(MP3Header), &bytes, nullptr) || bytes != sizeof(MP3Header)) {
                cout << "Failed to change title" << endl;
                CloseHandle(hFile);
                return 1;
            }
            break;
        }
        case 2: {
            string newArtist;
            cout << "Write new artist: " << endl;
            cin >> newArtist;

            strncpy(header->artist, newArtist.c_str(), sizeof(header->artist));
            SetFilePointer(hFile, -128, NULL, FILE_END);

            DWORD bytes;
            if (!WriteFile(hFile, header.get(), sizeof(MP3Header), &bytes, nullptr) || bytes != sizeof(MP3Header)) {
                cout << "Failed to change title" << endl;
                CloseHandle(hFile);
                return 1;
            }
            break;
        }

        case 3: {
            string newAlbum;
            cout << "Write new album: " << endl;
            cin >> newAlbum;

            strncpy(header->album, newAlbum.c_str(), sizeof(header->album));
            SetFilePointer(hFile, -128, NULL, FILE_END);

            DWORD bytes;
            if (!WriteFile(hFile, header.get(), sizeof(MP3Header), &bytes, nullptr) || bytes != sizeof(MP3Header)) {
                cout << "Failed to change title" << endl;
                CloseHandle(hFile);
                return 1;
            }
            break;
        }

        case 4: {
            cout << "Title: " << header->title << endl;
            cout << "Artist: " << header->artist << endl;
            cout << "Album: " << header->album << endl;
            break;
        }

        case 5: {
            CloseHandle(hFile);
            return 0;
        }
        
        default:
            CloseHandle(hFile);
            break;
        }
    }

    return 0;
}
