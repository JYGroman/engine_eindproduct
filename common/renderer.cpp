#include <common/renderer.h>

Renderer::Renderer()
{
    window_width = 1280;
    window_height = 720;

    fragment_shader	= "shaders/sprite.frag";
    vertex_shader	= "shaders/sprite.vert";
}

Renderer::~Renderer()
{

}

//#######################################
//#######################################
//########## SDL WINDOW TEST ############

// Create window and renderer.
//Return -1 if it fails.
int Renderer::SDLinit(){
    sdlwindow = NULL;

    screensurface = NULL;

    int window_width = 1280;
    int window_height = 720;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    } else {
        //Create window
        sdlwindow = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN );

        if( sdlwindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            return -1;
        } else {
            //Get window surface
            screensurface = SDL_GetWindowSurface( sdlwindow );

            //Create renderer for window
            gRenderer = SDL_CreateRenderer( sdlwindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                return -1;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    return -1;
                }
            }
        }
    }

    return 0;

}

//Create and SDL surface from an image.
SDL_Surface* Renderer::loadSurface( std::string path ) {

	//Final optimized image
	SDL_Surface* optimizedsurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    myprint(path.c_str());

    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
		optimizedsurface = SDL_ConvertSurface( loadedSurface, screensurface->format, 0 );

		if( optimizedsurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

	}

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );

    return optimizedsurface;
}

//Change current surface depending on inputs.
bool Renderer::loadmedia(){
	bool success = true;

	//Load default surface
    /*surfaces[ KEY_PRESS_DEFAULT ] = loadSurface( "assets/hoi.bmp" );
    if( surfaces[ KEY_PRESS_DEFAULT ] == NULL ) {
        printf( "Failed to load default image!\n" );
        success = false;
    }

	surfaces[ KEY_PRESS_UP ] = loadSurface( "assets/island.bmp" );
    if( surfaces[ KEY_PRESS_UP ] == NULL ) {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    surfaces[ KEY_PRESS_DOWN ] = loadSurface( "assets/test.bmp" );
    if( surfaces[ KEY_PRESS_DOWN ] == NULL ) {
        printf( "Failed to load default image!\n" );
        success = false;
    }*/

    gTexture = loadTexture("assets/pngtest2.png");
    if(gTexture == NULL){
		printf( "Failed to load texture image!\n" );
        success = false;
	}

    //Set default current surface
    //currentsurface = surfaces[ KEY_PRESS_DEFAULT ];

	return success;
}

//Draw SDL Window.
void Renderer::drawSDLwindow(){
	//Apply the image
	SDL_BlitSurface( currentsurface, NULL, screensurface, NULL );

	//Update the surface
	SDL_UpdateWindowSurface( sdlwindow );
}

//Free surfaces and close window before exiting program.
void Renderer::close(){
	//Deallocate surface
	SDL_FreeSurface( currentsurface );
    if(currentsurface != NULL){
		currentsurface = NULL;
	}

	//Deallocate surface
	SDL_FreeSurface( screensurface );
    if(screensurface != NULL){
		screensurface = NULL;
	}

	/*for(int i = 0; i < KEY_PRESS_DOWN; i++){
		if(surfaces[i] != NULL){
			SDL_FreeSurface( surfaces[i] );
			surfaces[i] = NULL;
		}
	}*/

    //Destroy window
    SDL_DestroyWindow( sdlwindow );
    if(sdlwindow != NULL){
		sdlwindow = NULL;
	}


    //Quit SDL subsystems
    SDL_Quit();
}

// Change current surface.
void Renderer::changeimage(KeyPressSurfaces key){
	currentsurface = surfaces[key];
	//currentsurface = StretchSurface(currentsurface);
}

//Stretch given surface.
SDL_Surface* Renderer::StretchSurface(SDL_Surface surface){

	//Apply the image stretched
	SDL_Surface* stretchedsurface = NULL;
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = window_width;
	stretchRect.h = window_height;
	SDL_BlitScaled( stretchedsurface, NULL, screensurface, &stretchRect );

	return stretchedsurface;
}

// Convert syrface to texture.
SDL_Texture* Renderer::loadTexture( std::string path )
{

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}


//######## SDL WINDOW TEST END ##########
//#######################################
//#######################################

/*int Renderer::init()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Open a window and create its OpenGL context
    _window = glfwCreateWindow( window_width, window_height, "Demo", NULL, NULL);
    if( _window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(_window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    //glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    //glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // Create and compile our GLSL program from the shaders
    // see: shader.h/cpp
    programID = loadShaders(vertex_shader.c_str(), fragment_shader.c_str());

    // Get a handle for our buffers
    vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    vertexUVID = glGetAttribLocation(programID, "vertexUV");

    // Get a handle for our "MVP" uniform
    matrixID = glGetUniformLocation(programID, "MVP");
    // Get a handle for our "myTextureSampler" uniform
    textureID  = glGetUniformLocation(programID, "myTextureSampler");

    ProjectionMatrix = glm::ortho(0.0f, (float)window_width, (float)window_height, 0.0f, 0.1f, 100.0f);

    return 0;
}

void Renderer::renderSprite(Sprite* sprite)
{
	// Compute the ViewMatrix from keyboard and mouse input (see: camera.h/cpp)
	computeMatricesFromInputs(_window);

	glm::vec3 cursor = getCursor();
	//printf("(%f,%f)\n",cursor.x, cursor.y);

	glm::mat4 ViewMatrix = getViewMatrix(); // get from Camera (Camera position and direction)
	glm::mat4 ModelMatrix = glm::mat4(1.0f);

	// Use our shader
	glUseProgram(programID);

	// Build the Model matrix
	glm::mat4 translationMatrix	= glm::translate(glm::mat4(1.0f), glm::vec3(500.0f, 300.0f, 0.0f));
	glm::mat4 rotationMatrix	= glm::eulerAngleYXZ(sprite->rotX(), sprite->rotY(), sprite->rotZ());
	glm::mat4 scalingMatrix		= glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	ModelMatrix = translationMatrix * rotationMatrix * scalingMatrix;

	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite->texture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(textureID, 0);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(vertexPosition_modelspaceID);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->vertexbuffer());
	glVertexAttribPointer(
		vertexPosition_modelspaceID,  // The attribute we want to configure
		3,							// size : x+y+z => 3
		GL_FLOAT,					 // type
		GL_FALSE,					 // normalized?
		0,							// stride
		(void*)0					  // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(vertexUVID);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->uvbuffer());
	glVertexAttribPointer(
		vertexUVID,				   // The attribute we want to configure
		2,							// size : U+V => 2
		GL_FLOAT,					 // type
		GL_FALSE,					 // normalized?
		0,							// stride
		(void*)0					  // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 2*3); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(vertexPosition_modelspaceID);
	glDisableVertexAttribArray(vertexUVID);
}*/
