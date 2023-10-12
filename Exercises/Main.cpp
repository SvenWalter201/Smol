#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <unordered_map>
#include <conio.h>

#include "FileManagement/FileManager.h"
#include "Level/Level.h"
#include "Player/Player.h"
#include "Utility/Log.h"
#include "source/Graphics/Draw.h"

//put this somewhere else
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "source/Graphics/IndexBuffer.h"
#include "source/Graphics/VertexBuffer.h"
#include "source/Graphics/VertexArray.h"
#include "source/Graphics/Shader.h"
#include "source/Graphics/Renderer.h"
#include "source/Graphics/Texture.h"
#include "source/input/Input.h"
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "source/game/GameObject.h"
#include "source/game/QuadRenderer.h"
#include "source/game/Game.h"

//Exercise
/*
- Scrolling grid
- Load Grid from csv or other file format
- Add Player input and Player win/lose conditions
- Add Player powerups, timers etc.
- ()Add Graphics using OpenCL or IMGUI
- ()Add procedural, infinite level with high score


- Move player function

Exercise															Concepts

- Basic functions (that will be used later)							Learning syntax and basic operations, such as iostream
	- Log
	- Math Helper
- Player class														Handling Inputs, Making classes
- Filemanager class													File IO
- Game class														Handling complex program states
- Level and Cell classes											Handling arrays and indizes
- Cell Content class -> overridable onPlayerTouch function			Inheritance and Interfaces
	- Rock: Game over
	- Jewel: Increase Player score
- Inputhandling
- Procedural Levels													Memory management and more complex logic
- Graphics															Using external libraries
- Different builds													CMake and other configuration tools

- Templates?
*/

/*
char lastInput;
bool abrt = false;

void InputHandler()
{
	while (!abrt)
		lastInput = _getch();
}
*/

void Run()
{
	Level level;
	Player* player = new Player();

	if (!ReadLevel("../../../../Exercises/Level.txt", level))
	{
		std::cout << "File could not be read" << std::endl;
		std::cin.get();
		return;
	}

	int currentLevelPosition = 0;
	int screenHeight = 12;
	int input = 0;
	level.playerRef = player;
	level.ChangePlayerPosition(0, 4);

	//start up input handler thread
	std::thread t(InputHandler);

	while (true)
	{
		system("cls");
		int playerMove = 0;
		switch ((char)input)
		{
		case 'a':
			playerMove = -1;
			break;
		case 'd':
			playerMove = 1;
			break;
		default:
			break;
		}
		
		level.ChangePlayerPosition(currentLevelPosition, player->locationX + playerMove);

		level.DisplayCurrentSegment(currentLevelPosition + screenHeight, currentLevelPosition);
		if (!level.CheckPlayerInteraction())
		{
			Log("You lose");
			std::cout << "Final Score: " << std::to_string(player->score) << std::endl;
			//abrt = true;
			//t.join();
			return;
		}
		currentLevelPosition++;
		if (currentLevelPosition >= level.GetCurrentLevelLength())
		{
			Log("You win");
			std::cout << "Final Score: " << std::to_string(player->score) << std::endl;
			//abrt = true;
			//t.join();
			return;
		}
		std::cout << "Score: " << std::to_string(player->score) << std::endl;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		//input = lastInput;
		//lastInput = 'w';
	}
}

int OpenGLWindow()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	/* Create a windowed mode window and its OpenGL context */
	int screenWidth = 1920;
	int screenHeight = 1080;
	window = glfwCreateWindow(screenWidth, screenHeight, "Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Not ok!" << std::endl;

	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	float unitWidth = 12.0f;
	float aspectRatio = (float)screenWidth / (float)screenHeight;
	float unitHeight = unitWidth / aspectRatio;

	Game game;
	game.Setup();

	glm::mat4 proj = glm::ortho(-unitWidth, unitWidth, -unitHeight, unitHeight, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(3, 0, 0));

	/*
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	
	ImGui::StyleColorsDark();
	*/
	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	//const char* glsl_version = "#version 100";
	//ImGui_ImplOpenGL3_Init(glsl_version);


	Renderer renderer;
	renderer.AddTypeForDynamicallyBatchedRendering(0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		game.Update();
		/* Render here */
		renderer.Clear();

		



		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();

		auto gameObjects = game.GetGameObjects();
		renderer.DynamicBatchRender(proj, view, gameObjects);
		/*
		static float f = 0.0f;
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		*/

		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

int main()
{
	//Run();
	return OpenGLWindow();
	//return 0;
}