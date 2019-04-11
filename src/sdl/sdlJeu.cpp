#include <sdlJeu.h>
const int SPRITE_SIZE = 50;

// ============= CLASS IMAGE =============== //

Image::Image () {
    surface = NULL;
    texture = NULL;

    has_changed = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    surface = IMG_Load(filename);
    if (surface == NULL) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< filename <<endl;
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture from surface " << endl;
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h, float angle) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if (has_changed) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }

    //ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    ok = SDL_RenderCopyEx(renderer, texture, NULL, &r, angle,NULL,SDL_FLIP_NONE);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const {return texture;}

void Image::setSurface(SDL_Surface * surf) {surface = surf;}


// ============= CLASS SDLJEU =============== //

//The dimensions of the level
const int LEVEL_WIDTH = 1280; 
const int LEVEL_HEIGHT = 960;

//Screen dimension constants
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 480;
sdlJeu::sdlJeu () : jeu() {
    // Initialisation de la SDL
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;SDL_Quit();exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        //SDL_Quit();exit(1);
        withSound = false;
    }
    else withSound = true;

    ///PLAYER
	int dimx, dimy;
    dimx = jeu.dimx;
    dimy = jeu.dimy;

    angle =0;
    camera = {0,0,dimx, dimy};
    jeu.getPlayer()->setPosition(b2Vec2(200,200),0);

    // Creation de la fenetre
    window = SDL_CreateWindow("SlideOut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN );
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_player.loadFromFile("data/bird1.png",renderer);
    timer_bg.loadFromFile("data/timer.png",renderer);

    // FONTS
    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (font == NULL) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
	}
	font_color.r = 50;font_color.g = 50;font_color.b = 255;
	font_im.setSurface(TTF_RenderText_Solid(font,"Slideout",font_color));
	font_im.loadFromCurrentSurface(renderer);

    // SONS
    // if (withSound)
    // {
    //     sound = Mix_LoadWAV("data/son.wav");
    //     if (sound == NULL) {
    //             cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl; SDL_Quit(); exit(1);
    //     }
    // }

}

sdlJeu::~sdlJeu () {
    if (withSound) Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlJeu::drawTerrain(){
    //Pour faire defiler le terrain, on applique une force dans le sens contraire de la position du joueur
    //Il faut rajouter à sa position la taille du sprite/2 pour avoir sa position effective
   jeu.getTerrain()->terrainBody->SetLinearVelocity(b2Vec2(-playerPos.x+SPRITE_SIZE/2, 0));

    //Pour l'affichage on retire à chaque coordonnées x du point affiché, la position du joueur
    //afin que ce qui est affiché corresponde à la force appliquée au terrain
    for(unsigned int i = 1 ; i < jeu.getTerrain()->tabHillPoints.size() ; i++){
        SDL_RenderDrawLine(renderer, jeu.getTerrain()->tabHillPoints.at(i-1).x-playerPos.x+SPRITE_SIZE, jeu.dimy - jeu.getTerrain()->tabHillPoints.at(i-1).y,
                                       jeu.getTerrain()->tabHillPoints.at(i).x-playerPos.x+SPRITE_SIZE, jeu.dimy - jeu.getTerrain()->tabHillPoints.at(i).y);
    }
        timer_bg.draw(renderer, (SCREEN_WIDTH/2) -50 ,SCREEN_HEIGHT/25,100,30, 1);
}

void sdlJeu::getAngle(){
    //calcul de l'angle pour l'orientation de l'image
    
    b2Vec2 vel = jeu.getPlayer()->playerBody->GetLinearVelocity();
    angle = atan2f(vel.y, vel.x);

    //std::cout << angle << std::endl;
    float minAngle = -10.0f, maxAngle = 10.0f;
    if(angle < minAngle) angle = minAngle;
    if(angle > maxAngle) angle = maxAngle;

    
}

void sdlJeu::drawPlayer(){
    //SDL_RenderDrawPoint(renderer, jeu.getPlayer()->getPosition().x, jeu.getPlayer()->getPosition().y);
    getAngle();
    
    im_player.draw(renderer, playerPos.x-(playerPos.x-SPRITE_SIZE/2),(jeu.dimy - playerPos.y-SPRITE_SIZE),SPRITE_SIZE,SPRITE_SIZE, angle*-50.0f);

}

void sdlJeu::sdlAff () {
	//Remplir l'cran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawTerrain();
    drawPlayer(); 

    // Ecrire un titre par dessus
    SDL_Rect positionTitre;
    positionTitre.x = 0; positionTitre.y = 0; positionTitre.w = 100; positionTitre.h = 30;

    SDL_RenderCopy(renderer,font_im.getTexture(),NULL,&positionTitre);

}


void sdlJeu::sdlBoucle () {
    SDL_Event events;
	bool quit = false;

    Uint32 t = SDL_GetTicks(), nt;

	// tant que ce n'est pas la fin ...
	while (!quit) {

        nt = SDL_GetTicks();
        if (nt-t>500) {
            t = nt;
        }
        playerPos = jeu.getPlayer()->getPosition();
        jeu.getPlayer()->wake();
        jeu.updateBox2dWorld();
        events.key.repeat = 1;
		// tant qu'il y a des evenements  traiter (cette boucle n'est pas bloquante)
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
				switch (events.key.keysym.scancode) {
				case SDL_SCANCODE_DOWN:
                   	jeu.getPlayer()->dive();	
					break;
                case SDL_SCANCODE_ESCAPE:
                    quit=true;
                    break;
				default: break;
				}
			}
		}
		// on affiche le jeu sur le buffer cach
		sdlAff();

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
	}
}

