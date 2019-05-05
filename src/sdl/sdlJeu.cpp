#include <sdlJeu.h>
#include <string.h>
#include <time.h>
#include <cassert>
#include <sys/stat.h>
const int SPRITE_SIZE = 50;

// ============= CLASS IMAGE =============== //

Image::Image () {
    surface = NULL;
    texture = NULL;

    has_changed = false;
}


bool Image::file_exists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    assert(file_exists(filename) );
    assert(renderer != NULL);

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
    assert(renderer != NULL);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture from surface " << endl;
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x , int y, int w, int h, float angle) {
    int ok;
    //assert (y>0 );
    assert(renderer != NULL);
    assert( w>0 && h>0);
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
const int SCREEN_WIDTH = 900; 
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

    hasLost = false;
    freqLevel = 9/1000;
    // TEMPS
    //initTimer(5);

    angle = 0;
    player_frame = 0;
    jeu.getPlayer()->setPosition(b2Vec2(200,200),0);

    // Creation de la fenetre
    window = SDL_CreateWindow("SlideOut", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN );
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; SDL_Quit(); exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // IMAGES
    im_player[0].loadFromFile("data/bird0.png", renderer);
    im_player[1].loadFromFile("data/bird1.png", renderer);
    im_player[2].loadFromFile("data/bird2.png", renderer);
    im_player[3].loadFromFile("data/bird3.png", renderer);
    im_player[4].loadFromFile("data/bird4.png", renderer);
    im_player[5].loadFromFile("data/bird5.png", renderer);
    im_player[6].loadFromFile("data/bird6.png", renderer);
    im_timer_bg.loadFromFile("data/timer.png", renderer);
    im_time_up.loadFromFile("data/time_up.png", renderer);
    im_score_bg.loadFromFile("data/bg_score.png", renderer);
    im_sky[0].loadFromFile("data/sky.png", renderer);
    im_sky[1].loadFromFile("data/sky2.png", renderer);
    im_sky[2].loadFromFile("data/sky3.png", renderer);
    im_sky[3].loadFromFile("data/sky4.png", renderer);
    im_sky[4].loadFromFile("data/sky5.png", renderer);
    im_sun.loadFromFile("data/sun.png", renderer);
    im_cloud.loadFromFile("data/cloud.png", renderer);
    im_sprite[0].loadFromFile("data/sprite.png", renderer);
    im_sprite[1].loadFromFile("data/sprite2.png", renderer);
    im_sprite[2].loadFromFile("data/sprite3.png", renderer);
    im_sprite[3].loadFromFile("data/sprite4.png", renderer);
    im_sprite[4].loadFromFile("data/sprite5.png", renderer);
    im_arrow.loadFromFile("data/arrow.png", renderer);
    im_arrow2.loadFromFile("data/arrow2.png", renderer);
    im_bonus.loadFromFile("data/bonus.png", renderer);
    im_player_selector.loadFromFile("data/bonus.png", renderer);

    // FONTS
    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",40);
    if (font == NULL) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; SDL_Quit(); exit(1);
	}
	/*font_color.r = 255;font_color.g = 255;font_color.b = 255;
	font_im.setSurface(TTF_RenderText_Solid(font,"00:00",font_color));
	font_im.loadFromCurrentSurface(renderer);

    score_color.r = 220;score_color.g = 70;score_color.b = 20;
	font_score.setSurface(TTF_RenderText_Solid(font,"0123",score_color));
	font_score.loadFromCurrentSurface(renderer);*/

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
    
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlJeu::playerSpriteSelector(char RoL){
    //bool amLeft = true; // par defaut le joueur a gauche est choisie
    if (RoL == (char)'r'){
        im_player_selector.draw(renderer, 3*SCREEN_WIDTH/4 -200, SCREEN_HEIGHT/2 -150, 300, 300, 0);
    }else if (RoL == (char)'l'){
        im_player_selector.draw(renderer, 50, SCREEN_HEIGHT/2 -150, 300, 300, 0);
    }
    //std::cout<<"eee";
}

void sdlJeu::drawText(string text, SDL_Rect rect, SDL_Color color){
    TTF_Font* Sans = TTF_OpenFont("data/ttf/kidsrock-DEMO.ttf", 50);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.data(), color);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
/*
    SDL_Rect Message_rect;
    Message_rect.x = 0; 
    Message_rect.y = 0;
    Message_rect.w = 100;
    Message_rect.h = 100;
*/
    SDL_RenderCopy(renderer, Message, NULL, &rect); 
    
    SDL_DestroyTexture(Message);
    TTF_CloseFont(Sans);
}

float sdlJeu::computeZoomPlayer(){
    float t = playerPos.y*1.2 - SCREEN_HEIGHT;
    float zoom = 1+(-1*t/2500.0f);
    if(zoom > 2.5) zoom = 2.5f;
    if(zoom < 1) zoom = 1.0f;
    return zoom;
}

void sdlJeu::initTimer(unsigned int editTimer)
{
    seconds = editTimer;
    start_timer = editTimer;
}

void sdlJeu::updateTimer(uint32 t)
{
    seconds = start_timer - t/1000;
    //std::cout << "seconds = " << seconds << std::endl;
}

void sdlJeu::updatePlayerStatus()
{
    if(seconds < 0)
    {
        //hasLost = true;
    }
}

void sdlJeu::updateLevel()
{
    if(jeu.isLevelFinished() && !hasLost)
    {
        initTimer(15);
        hasLost = false;
        jeu.getPlayer()->applyForce(b2Vec2(400,-150));

        if(jeu.getPlayer()->getPosition().y < 0){
            jeu.getPlayer()->initPlayer(jeu.world);
            jeu.getPlayer()->setPosition(b2Vec2(100,jeu.dimy),0);
            jeu.getPlayer()->applyForce(b2Vec2(200,0));

            //SPRITE Aléatoire
            srand(time(0));
            sprite_frame = rand() % 5;
            if(prev_sprite_frame == sprite_frame)
            {
                srand(time(0));
                sprite_frame = rand() % 4;
                prev_sprite_frame = sprite_frame;
            }
            
            jeu.destroyTerrain();
            
            //Regénération du Terrain
            //la frequence du terrain augmente petit à petit
            freqLevel = (1/1000.0f - 1/5000.0f);
            std::cout << "FREQ : " << freqLevel << std::endl;
            jeu.getTerrain()->generateHillPoints(3,freqLevel,2);
            jeu.getTerrain()->initTerrain(jeu.world);
            jeu.addBonusPoints();

        }
        
    }
}

void sdlJeu::drawBackground()
{
    SDL_RenderSetScale(renderer, 1, 1);
    
    im_sky[sprite_frame].draw(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    im_sun.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH, SCREEN_HEIGHT/10, 100, 100);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH -600, SCREEN_HEIGHT/15, 200, 200);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH -800, SCREEN_HEIGHT/20, 300, 300);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH -500, SCREEN_HEIGHT/40, 400, 400);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH -200, SCREEN_HEIGHT/10, 300, 300);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH , SCREEN_HEIGHT/120, 300, 300);
    im_timer_bg.draw(renderer, (SCREEN_WIDTH/2)-50*1.4, SCREEN_HEIGHT/30, 100*1.4, 30*1.4, 0);

    SDL_Rect positionTime;
    positionTime.x = (SCREEN_WIDTH/2) -40; positionTime.y = SCREEN_HEIGHT/25*1.2; positionTime.w = 80; positionTime.h = 35;

    SDL_Rect positionScore;
    positionScore.x = SCREEN_WIDTH-100; positionScore.y = SCREEN_HEIGHT/25*1.2; positionScore.w = 70; positionScore.h = 35;

    SDL_Color white = {255, 255, 255};
    SDL_Color orange = {220, 70, 20};

    string text_seconds;
    int min = seconds/60;
    int sec = seconds%60;
    if(sec > 9) text_seconds = "0"+std::to_string(min)+" : "+ std::to_string(sec);
    else if(sec <= 0) text_seconds ="00 : 00";
    else text_seconds = "0"+std::to_string(min)+" : 0"+ std::to_string(sec);
    string text_score = std::to_string(jeu.score);
    string text_bonus_score = std::to_string(jeu.bonus_score);

    drawText(text_seconds,positionTime, white);
    drawText(text_score,positionScore, orange);
}    

void sdlJeu::drawTerrain(){

    SDL_RenderSetScale(renderer, computeZoomPlayer(), computeZoomPlayer());

    im_arrow.draw(renderer, jeu.getTerrain()->tabHillPoints.at(300).x-playerPos.x,jeu.dimy - jeu.getTerrain()->tabHillPoints.at(300).y - SPRITE_SIZE*2 + 5, 100, 100);
    im_arrow2.draw(renderer, jeu.getTerrain()->tabHillPoints.back().x-playerPos.x -15 ,jeu.dimy - jeu.getTerrain()->tabHillPoints.back().y - SPRITE_SIZE*2 + 5, 100, 100);

    //Pour faire defiler le terrain, on applique une force dans le sens contraire de la position du joueur
    //Il faut rajouter à sa position la taille du sprite/2 pour avoir sa position effective
    jeu.getTerrain()->terrainBody->SetLinearVelocity(b2Vec2(-playerPos.x+SPRITE_SIZE/2, 0));

    for(unsigned int i = 1; i < jeu.getTerrain()->tabHillPoints.size(); i++){
        im_sprite[sprite_frame].draw(renderer, jeu.getTerrain()->tabHillPoints.at(i-1).x-playerPos.x+SPRITE_SIZE,
                                    jeu.dimy - jeu.getTerrain()->tabHillPoints.at(i-1).y + 1,
                                    jeu.getTerrain()->terrainResolution,
                                    jeu.getTerrain()->tabHillPoints.at(i-1).y);
    }

    for(unsigned int i = 0; i < jeu.BonusPoints.size(); i++){
        im_bonus.draw(renderer, jeu.BonusPoints.at(i).x-playerPos.x+SPRITE_SIZE,
                                    jeu.dimy - jeu.BonusPoints.at(i).y - SPRITE_SIZE + 10,
                                    35,
                                    35);

        b2Vec2 pos = jeu.getRelativePlayerPos();
        if((int)pos.x == (int)jeu.BonusPoints.at(i).x && playerPos.y - pos.y < 20)
        {
            jeu.BonusPoints.erase(jeu.BonusPoints.begin()+i);
            player_frame = 5;
            jeu.bonus_score++;
        }
    }
}

void sdlJeu::calculAngle(){
    //calcul de l'angle pour l'orientation de l'image
    b2Vec2 vel = jeu.getPlayer()->playerBody->GetLinearVelocity();
    angle = atan2f(vel.y, vel.x);

    float minAngle = -10.0f, maxAngle = 10.0f;
    if(angle < minAngle) angle = minAngle;
    if(angle > maxAngle) angle = maxAngle;
}

void sdlJeu::drawPlayer(){
    SDL_RenderSetScale(renderer, computeZoomPlayer(), computeZoomPlayer());
    calculAngle();
    im_player[player_frame].draw(renderer, playerPos.x-(playerPos.x-SPRITE_SIZE/2),(jeu.dimy - playerPos.y-SPRITE_SIZE),SPRITE_SIZE,SPRITE_SIZE, angle*-50.0f);
}

void sdlJeu::sdlAff () {
	//Remplir l'ecran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawBackground();
    drawTerrain();
    drawPlayer();

    // Ecrire un titre par dessus
    SDL_Rect positionTime;
    positionTime.x = (SCREEN_WIDTH/2) -35; positionTime.y = SCREEN_HEIGHT/25*1.2; positionTime.w = 70; positionTime.h = 30;

    SDL_Rect positionScore;
    positionScore.x = SCREEN_WIDTH-100; positionScore.y = SCREEN_HEIGHT/25*1.2; positionScore.w = 60; positionScore.h = 30;

    SDL_RenderCopy(renderer,font_im.getTexture(),NULL,&positionTime);
    SDL_RenderCopy(renderer,font_score.getTexture(),NULL,&positionScore);
}

void sdlJeu::sdlBoucle () {
    SDL_Event events;
    bool quit = false;
    bool is_space_pressed = false;
    bool SelectorR = false;
    bool SelectorL = true;
 
    // RANDOMS
    srand(time(0));
    sprite_frame = rand() % 4;
    prev_sprite_frame = sprite_frame;
 
    Uint32 t = SDL_GetTicks(), nt;
 
    // tant que ce n'est pas la fin ...
   
 
    while (!quit) {
 
        nt = SDL_GetTicks();
        if (nt-t>500) {
            t = nt;
        }
        //vitesse des ailes
        if(nt-t > 300)
        {
            player_frame++;
            if(player_frame > 4) player_frame = 0;
        }
        //calcul et affichage temps en seconds
        //TODO: if(seconds > 0 && playerLost()) must stop game and inform user
        seconds = 20 - t/1000;
        updatePlayerStatus();
        updateLevel();
        //updateTimer(t);
       
        playerPos = jeu.getPlayer()->getPosition();
        playerSpriteSelector('r');
       
        if (is_space_pressed) {
            jeu.getPlayer()->wake();  
            //SDL_Delay(10);
            jeu.collision();
            jeu.updateBox2dWorld();
           
        }
       
        events.key.repeat = 1;
        // tant qu'il y a des evenements  traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
            else if (events.type == SDL_KEYDOWN && events.key.repeat == 0) {              // Si une touche est enfoncee
                switch (events.key.keysym.scancode) {
                case SDL_SCANCODE_SPACE :
                    is_space_pressed =true;
                    break;
                case SDL_SCANCODE_RIGHT:
                    if(!is_space_pressed ){
                            SelectorL = false;
                            SelectorR = true;
                        }
                    break;
                case SDL_SCANCODE_LEFT:
                    if( ! is_space_pressed ) {
                            SelectorL = true;
                            SelectorR = false;
 
                        }
                    break;
                case SDL_SCANCODE_DOWN:
                    if(is_space_pressed ) {jeu.getPlayer()->dive();}
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
         if (SelectorL && !SelectorR  && !is_space_pressed) {
            playerSpriteSelector('l');
        }
        if (!SelectorL && SelectorR && !is_space_pressed ) {
            playerSpriteSelector('r');
        }
        //im_playerSelector.draw(renderer,(SCREEN_WIDTH/2)-100*1.4, SCREEN_HEIGHT/30, 100*1.4, 30*1.4, 0);
 
        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
}
