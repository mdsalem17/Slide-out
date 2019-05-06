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
    SDL_FreeSurface(surfaceCorrectPixelFormat);
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
    gameStarted =false;
    PlayerSelectorL = true;
    ResetGame=false;
    currentLevel = 0;
    freqLevel[0] = .0005;
    freqLevel[1] = .0007;
    freqLevel[2] = .001;
    freqLevel[3] = .0012;
    freqLevel[4] = .0014;

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
    im_ladyplayer[0].loadFromFile("data/ladybird0.png", renderer);
    im_ladyplayer[1].loadFromFile("data/ladybird1.png", renderer);
    im_ladyplayer[2].loadFromFile("data/ladybird2.png", renderer);
    im_ladyplayer[3].loadFromFile("data/ladybird3.png", renderer);
    im_ladyplayer[4].loadFromFile("data/ladybird4.png", renderer);
    im_ladyplayer[5].loadFromFile("data/ladybird5.png", renderer);
    im_ladyplayer[6].loadFromFile("data/ladybird6.png", renderer);
    im_timer_bg.loadFromFile("data/timer.png", renderer);
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
    im_background[0].loadFromFile("data/background.png", renderer);
    im_background[1].loadFromFile("data/background2.png", renderer);
    im_background[2].loadFromFile("data/background3.png", renderer);
    im_background[3].loadFromFile("data/background4.png", renderer);
    im_background[4].loadFromFile("data/background5.png", renderer);
    im_arrow.loadFromFile("data/arrow.png", renderer);
    im_arrow2.loadFromFile("data/arrow2.png", renderer);
    im_bonus.loadFromFile("data/bonus.png", renderer);
    im_player_selector.loadFromFile("data/player_selector.png", renderer);
    im_title.loadFromFile("data/title.png", renderer);
    im_gameover.loadFromFile("data/gameover.png", renderer);
    im_avatar.loadFromFile("data/avatar.png", renderer);
    im_astuce.loadFromFile("data/astuce.png", renderer);
    im_espace.loadFromFile("data/espace.png", renderer);

    // FONTS
    font = TTF_OpenFont("data/ttf/DejaVuSansCondensed.ttf",40);
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
     if (withSound)
     {
         StartSound = Mix_LoadWAV("data/audio/intro.wav");
         if (StartSound == NULL) {
             cout << "Failed to load StartSound -> intro.wav! SDL_mixer Error: " << Mix_GetError() << endl; SDL_Quit(); exit(1);
         }
         bonusSound = Mix_LoadWAV("data/audio/bonus.wav");
         if (bonusSound == NULL) {
             cout << "Failed to load bonusSound -> intro.wav! SDL_mixer Error: " << Mix_GetError() << endl; SDL_Quit(); exit(1);
         }
         LvlUpSound = Mix_LoadWAV("data/audio/levelUp-bikibikwa.wav");
         if (LvlUpSound == NULL) {
             cout << "Failed to load LvlUpSound -> intro.wav! SDL_mixer Error: " << Mix_GetError() << endl; SDL_Quit(); exit(1);
         }
     }

}

sdlJeu::~sdlJeu () {
     if (withSound){
        Mix_FreeChunk(StartSound);
        Mix_FreeChunk(bonusSound);
        Mix_FreeChunk(LvlUpSound);
        
        Mix_Quit();
    } 
    TTF_CloseFont(font);

    TTF_Quit();
    
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlJeu::playerSpriteSelector(char RoL){
    // par defaut le joueur a gauche est choisie
    if (RoL == (char)'r'){
        im_player_selector.draw(renderer, SCREEN_WIDTH/2-SPRITE_SIZE/2, SCREEN_HEIGHT/2-100, SPRITE_SIZE*3.5, SPRITE_SIZE*3);
    }else if (RoL == (char)'l'){
        im_player_selector.draw(renderer, SPRITE_SIZE*5-SPRITE_SIZE/2, SCREEN_HEIGHT/2-100, SPRITE_SIZE*3.5, SPRITE_SIZE*3);
    }
}

string sdlJeu::formatNbtoText(int nb){
    string text ;
    if(nb <= 9) text = "    "+std::to_string(nb);
    else if(nb >= 10 && nb <= 99) text = "   "+std::to_string(nb);
    else if(nb >= 100 && nb <= 999) text = "  "+std::to_string(nb);
    else if(nb >= 1000 && nb <= 9999) text = " "+std::to_string(nb);
    else text = std::to_string(nb);
    return text;
}

void sdlJeu::drawText(string text, SDL_Rect rect, SDL_Color color){
    TTF_Font* Sans = TTF_OpenFont("data/ttf/kidsrock-DEMO.ttf", 50);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.data(), color);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

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

void sdlJeu::updatePlayerStatus()
{
    if(seconds <= 0)
    {
        hasLost = true;
        gameStarted =false;
        ResetGame=true;
    }
}

void sdlJeu::updateLevel()
{
    if(jeu.isLevelFinished() && !hasLost)
    {
        hasLost = false;
        Mix_PlayChannel( -1, LvlUpSound, 0 );
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
                sprite_frame = rand() % 5;
                prev_sprite_frame = sprite_frame;
            }
            
            jeu.destroyTerrain();
            
            //Regénération du Terrain
            //la frequence du terrain augmente petit à petit
            jeu.getTerrain()->generateHillPoints(3,freqLevel[currentLevel%5],2);
            jeu.getTerrain()->initTerrain(jeu.world);
            jeu.addBonusPoints();
            currentLevel++;

        }
        
    }
}


void sdlJeu::ResetLevel(){
    if( ResetGame && hasLost)
    {
        jeu.destroyTerrain();

        currentLevel = 0;
        jeu.score = 0; 
        jeu.bonus_score = 0;
        
        jeu.getPlayer()->applyForce(b2Vec2(400,-150));

        if( (jeu.getPlayer()->getPosition().y < 0) || ResetGame) {
            jeu.getPlayer()->initPlayer(jeu.world);
            jeu.getPlayer()->setPosition(b2Vec2(100,jeu.dimy),0);
            jeu.getPlayer()->applyForce(b2Vec2(200,0));

            //SPRITE Aléatoire
            srand(time(0));
            sprite_frame = rand() % 5;
            if(prev_sprite_frame == sprite_frame)
            {
                srand(time(0));
                sprite_frame = rand() % 5;
                prev_sprite_frame = sprite_frame;
            }
            
            jeu.destroyTerrain();
            
            //Regénération du Terrain
            //la frequence du terrain augmente petit à petit
            jeu.getTerrain()->generateHillPoints(3,freqLevel[currentLevel%5],2);
            jeu.getTerrain()->initTerrain(jeu.world);
            jeu.addBonusPoints();

        }
        ResetGame = false;
        hasLost =false;
        
    }
}


void sdlJeu::drawBackground()
{
    SDL_RenderSetScale(renderer, 1, 1);
    
    im_sky[sprite_frame].draw(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    im_sun.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH, SCREEN_HEIGHT/10, 100, 100);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH -600, SCREEN_HEIGHT/15, 200, 200);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH -800, SCREEN_HEIGHT/20, 300, 300);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH -500, SCREEN_HEIGHT/40, 350, 350);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH -200, SCREEN_HEIGHT/10, 300, 300);
    im_cloud.draw(renderer, -playerPos.x/60 + SCREEN_WIDTH , SCREEN_HEIGHT/120, 300, 300);
    im_timer_bg.draw(renderer, (SCREEN_WIDTH/2)-50*1.4, SCREEN_HEIGHT/30, 100*1.4, 30*1.4, 0);

    im_score_bg.draw(renderer, SCREEN_WIDTH -120 , SCREEN_HEIGHT/25*1.2-4, 100*1.4, 35, 0);
    im_score_bg.draw(renderer, SCREEN_WIDTH -120, (SCREEN_HEIGHT/25*1.2)+40-4, 100*1.4, 35, 0);
    im_bonus.draw(renderer, SCREEN_WIDTH -110, (SCREEN_HEIGHT/25*1.2)+40, 25, 25);

    im_background[sprite_frame].draw(renderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

    SDL_Rect positionTime;
    positionTime.x = (SCREEN_WIDTH/2) -40; positionTime.y = SCREEN_HEIGHT/25*1.2; positionTime.w = 80; positionTime.h = 35;

    SDL_Rect positionScore;
    positionScore.x = SCREEN_WIDTH-90; positionScore.y = SCREEN_HEIGHT/25*1.2; positionScore.w = 70; positionScore.h = 30;

    SDL_Rect positionBonusScore;
    positionBonusScore.x = SCREEN_WIDTH-90; positionBonusScore.y = (SCREEN_HEIGHT/25*1.2)+40; positionBonusScore.w = 70; positionBonusScore.h = 30;

    SDL_Color white = {255, 255, 255};

    string text_seconds;
    int min = seconds/60;
    int sec = seconds%60;
    if(sec > 9) text_seconds = "0"+std::to_string(min)+" : "+ std::to_string(sec);
    else if(sec <= 0) text_seconds ="00 : 00";
    else text_seconds = "0"+std::to_string(min)+" : 0"+ std::to_string(sec);

    string text_score = formatNbtoText(jeu.score);
    string text_bonus_score = formatNbtoText(jeu.bonus_score);

    drawText(text_seconds,positionTime, white);
    drawText(text_score,positionScore, white);
    drawText(text_bonus_score,positionBonusScore, white);

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

        b2Vec2 pos = jeu.getRelativeTerrainPos();
        if((int)pos.x == (int)jeu.BonusPoints.at(i).x && playerPos.y - pos.y < 20)
        {
            jeu.BonusPoints.erase(jeu.BonusPoints.begin()+i);
            player_frame = 5;
            jeu.bonus_score++;
            Mix_PlayChannel( -1, bonusSound, 0 );

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
    if (PlayerSelectorL) im_player[player_frame].draw(renderer, playerPos.x-(playerPos.x-SPRITE_SIZE/2),(jeu.dimy - playerPos.y-SPRITE_SIZE),SPRITE_SIZE,SPRITE_SIZE, angle*-50.0f);
    else  im_ladyplayer[player_frame].draw(renderer, playerPos.x-(playerPos.x-SPRITE_SIZE/2),(jeu.dimy - playerPos.y-SPRITE_SIZE),SPRITE_SIZE,SPRITE_SIZE, angle*-50.0f);
}

void sdlJeu::sdlAff () {
	//Remplir l'ecran de blanc
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawBackground();
    drawTerrain();
    drawPlayer();
}

void sdlJeu::drawMenu(){
    if( ! gameStarted )
    {
        im_sky[sprite_frame].draw(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        im_ladyplayer[0].draw(renderer, (SCREEN_WIDTH/2), SCREEN_HEIGHT/2-100, SPRITE_SIZE*2.5, SPRITE_SIZE*2.5);
        im_player[0].draw(renderer, SPRITE_SIZE*5, SCREEN_HEIGHT/2-100, SPRITE_SIZE*2.5, SPRITE_SIZE*2.5);
        im_avatar.draw(renderer, (SCREEN_WIDTH/2)-560/2, SCREEN_HEIGHT/4-60/2, 1000/2, 125/2);
        im_espace.draw(renderer, (SCREEN_WIDTH/2)-540/2, SCREEN_HEIGHT-100, 1000/2, 90/2);
        im_cloud.draw(renderer, 50, 20, 200, 200);
        im_cloud.draw(renderer, 0, 180, 400, 400);
        im_cloud.draw(renderer, SCREEN_WIDTH-280, 40, 300, 300);
        if( hasLost ){
            im_gameover.draw(renderer, (SCREEN_WIDTH/2)-250, SCREEN_HEIGHT/8-75, 400, 150);
            im_score_bg.draw(renderer, (SCREEN_WIDTH/2), SCREEN_HEIGHT/2+75, SPRITE_SIZE*3, SPRITE_SIZE);
            im_score_bg.draw(renderer, SPRITE_SIZE*5, SCREEN_HEIGHT/2+75, SPRITE_SIZE*3, SPRITE_SIZE);
            im_bonus.draw(renderer,(SCREEN_WIDTH/2)+10, SCREEN_HEIGHT/2+85, 25, 25);

            SDL_Rect positionScore;
            positionScore.x = SPRITE_SIZE*5+30; positionScore.y = SCREEN_HEIGHT/2+75+10; positionScore.w = 70; positionScore.h = 30;

            SDL_Rect positionBonusScore;
            positionBonusScore.x = SCREEN_WIDTH/2+30; positionBonusScore.y = SCREEN_HEIGHT/2+75+10; positionBonusScore.w = 70; positionBonusScore.h = 30;

            SDL_Color white = {255, 255, 255};
            string text_score = formatNbtoText(jeu.score);
            string text_bonus_score = formatNbtoText(jeu.bonus_score);

            drawText(text_score,positionScore, white);
            drawText(text_bonus_score,positionBonusScore, white);
        }
        else{//ici le joeur n'a pas encore commence de jouer;
            im_title.draw(renderer, (SCREEN_WIDTH/2)-250, SCREEN_HEIGHT/8-75, 400, 150);
            im_astuce.draw(renderer, (SCREEN_WIDTH/2)-570/2, SCREEN_HEIGHT-200, 1050/2, 170/2);
        }
    }
}


void sdlJeu::sdlBoucle () {
    SDL_Event events;
    bool quit = false;
    
    // RANDOMS
    srand(time(0));
    sprite_frame = rand() % 5;
    prev_sprite_frame = sprite_frame;
 
    Uint32 t = SDL_GetTicks(), nt;
    Uint32 space_time = (Uint32) 0;
 
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
        seconds = 120 - t/1000 + space_time/1000;
        updatePlayerStatus();
        updateLevel();
       
        playerPos = jeu.getPlayer()->getPosition();
        playerSpriteSelector('r');
       
        if (gameStarted && !hasLost) {
            jeu.getPlayer()->wake();  
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
                    if (!gameStarted){
                    space_time= t;
                    gameStarted =true;
                    ResetLevel();
                    Mix_PlayChannel( -1, StartSound, 0 );}
                    break;
                case SDL_SCANCODE_RIGHT:
                    if(!gameStarted ){
                            PlayerSelectorL = false;
                            
                        }
                    break;
                case SDL_SCANCODE_LEFT:
                    if( !gameStarted ) {
                            PlayerSelectorL = true;
                            
                        }
                    break;
                case SDL_SCANCODE_DOWN:
                    if(gameStarted ) {jeu.getPlayer()->dive();}
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
        drawMenu();
         if (PlayerSelectorL   && !gameStarted) {
            playerSpriteSelector('l');
        }
        if (!PlayerSelectorL && !gameStarted ) {
            playerSpriteSelector('r');
        } 
        // on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
}
