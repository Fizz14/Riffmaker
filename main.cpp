#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctype.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

using namespace std;

int WinMain() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	
	window = SDL_CreateWindow("Rifmaker",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetWindowMinimumSize(window, 100, 100);


    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);
	SDL_RenderSetIntegerScale(renderer, SDL_FALSE);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "3"); 

    SDL_GL_SetSwapInterval(1);

    vector<bool> keyrefresh(100);

    const Uint8* SDLkeystates = SDL_GetKeyboardState(NULL);

    SDL_Event event;

    int noteIndex = 0;

    string instrumentName = "ghost";
    string scaleName = "major";
    string keyName = "C";
    int keyindex = 0;

    cout << "Rifmaker:" << endl;
    cout << "input instrumentname: " << endl;
    cin >> instrumentName;
    cout << "input key, e.g. 'C', 'Es' for E-sharp, or 'Ef' for E-flat." << endl;
    cin >> keyName;

    //translate keyName to keyIndex
    keyName[0] = toupper(keyName[0]);
    if(keyName[0] == 'C') {
        keyindex = 0;
    } else if(keyName[0] == 'D') {
        keyindex = 2;
    } else if(keyName[0] == 'E') {
        keyindex = 4;
    } else if(keyName[0] == 'F') {
        keyindex = 5;
    } else if(keyName[0] == 'G') {
        keyindex = 7;
    } else if(keyName[0] == 'A') {
        keyindex = 9;
    } else if(keyName[0] == 'B') {
        keyindex = 11;
    }

    cout << "input scaleName:" << endl;
    cin >> scaleName;

    if(keyName[1] == 's'){
        keyindex++;
    } else if (keyName[1] == 'f') {
        keyindex--;
    }

    vector<Mix_Chunk*> prenotes;
    vector<Mix_Chunk*> notes;

    for(int i = 0; i < 14; i ++) {
        string address = "instruments/" + instrumentName + "/" + to_string(i) + ".wav";
        prenotes.emplace_back(Mix_LoadWAV(address.c_str()));
    }

    //load scale
    string line;
    std::ifstream infile("scale/" + scaleName + ".txt");

    vector<bool> scale;
    bool thisNoteIncludedInScale = 0;
    while(infile >> thisNoteIncludedInScale) {
        scale.push_back(thisNoteIncludedInScale);
    }
    infile.close();

    //shift scale based on scaleindex
    std::rotate(scale.begin(),scale.begin()+keyindex,scale.end());

    //disable notes
    for(int i = 0; i < scale.size(); i++) {
        if(scale[i] && i < prenotes.size()) {
            notes.push_back(prenotes.at(i));
        } 
    }
    
    

    bool quit = 0;
    while(!quit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
        if(SDLkeystates[SDL_SCANCODE_ESCAPE]) { quit = 1;}
        

        if(SDLkeystates[SDL_SCANCODE_LEFT] && keyrefresh[SDL_SCANCODE_LEFT]) {
            if(noteIndex > 0) { noteIndex--;}
            Mix_PlayChannel(0, notes[noteIndex], 0);
            keyrefresh[SDL_SCANCODE_LEFT] = 0;
        }

        if(SDLkeystates[SDL_SCANCODE_RIGHT] && keyrefresh[SDL_SCANCODE_RIGHT]) {
            if(noteIndex < notes.size()) { noteIndex++;}
            Mix_PlayChannel(0, notes[noteIndex], 0);
            keyrefresh[SDL_SCANCODE_RIGHT] = 0;
        }

        if(SDLkeystates[SDL_SCANCODE_DOWN] && keyrefresh[SDL_SCANCODE_DOWN]) {
            Mix_PlayChannel(0, notes[noteIndex], 0);
            keyrefresh[SDL_SCANCODE_DOWN] = 0;
        }

        //map keys to bottom row
        if(SDLkeystates[SDL_SCANCODE_Z] && keyrefresh[SDL_SCANCODE_Z]) {
            int thisindex = 0;
            if(thisindex < notes.size()) {
                Mix_PlayChannel(0, notes[thisindex], 0);
            }
            noteIndex = thisindex;
            keyrefresh[SDL_SCANCODE_Z] = 0;
        }

        if(SDLkeystates[SDL_SCANCODE_X] && keyrefresh[SDL_SCANCODE_X]) {
            int thisindex = 1;
            if(thisindex < notes.size()) {
                Mix_PlayChannel(0, notes[thisindex], 0);
            }
            noteIndex = thisindex;
            keyrefresh[SDL_SCANCODE_X] = 0;
        }

        if(SDLkeystates[SDL_SCANCODE_C] && keyrefresh[SDL_SCANCODE_C]) {
            int thisindex = 2;
            if(thisindex < notes.size()) {
                Mix_PlayChannel(0, notes[thisindex], 0);
            }
            noteIndex = thisindex;
            keyrefresh[SDL_SCANCODE_C] = 0;
        }

        if(SDLkeystates[SDL_SCANCODE_V] && keyrefresh[SDL_SCANCODE_V]) {
            int thisindex = 3;
            if(thisindex < notes.size()) {
                Mix_PlayChannel(0, notes[thisindex], 0);
            }
            noteIndex = thisindex;
            keyrefresh[SDL_SCANCODE_V] = 0;
        }

        if(SDLkeystates[SDL_SCANCODE_B] && keyrefresh[SDL_SCANCODE_B]) {
            int thisindex = 4;
            if(thisindex < notes.size()) {
                Mix_PlayChannel(0, notes[thisindex], 0);
            }
            noteIndex = thisindex;
            keyrefresh[SDL_SCANCODE_B] = 0;
        }

        if(SDLkeystates[SDL_SCANCODE_N] && keyrefresh[SDL_SCANCODE_N]) {
            int thisindex = 5;
            if(thisindex < notes.size()) {
                Mix_PlayChannel(0, notes[thisindex], 0);
            }
            noteIndex = thisindex;
            keyrefresh[SDL_SCANCODE_N] = 0;
        }

        if(SDLkeystates[SDL_SCANCODE_M] && keyrefresh[SDL_SCANCODE_M]) {
            int thisindex = 6;
            if(thisindex < notes.size()) {
                Mix_PlayChannel(0, notes[thisindex], 0);
            }
            noteIndex = thisindex;
            keyrefresh[SDL_SCANCODE_M] = 0;
        }

        if(SDLkeystates[SDL_SCANCODE_COMMA] && keyrefresh[SDL_SCANCODE_COMMA]) {
            int thisindex = 7;
            if(thisindex < notes.size()) {
                Mix_PlayChannel(0, notes[thisindex], 0);
            }
            noteIndex = thisindex;
            
            keyrefresh[SDL_SCANCODE_COMMA] = 0;
        }



        //easy version of 
        // if(!SDLkeystates[SDL_SCANCODE_LEFT]) {
        //     keyrefresh[SDL_SCANCODE_LEFT] = 1;
        // }
        //... for every key
        for(int i = 0; i < 100; i++) {
            if(!SDLkeystates[i]) {
                keyrefresh[i] = 1;
            }
        }
    }
        

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}