// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//#include "imgui.h"
//#include "imgui_impl_glfw_gl3.h"

GLFWwindow* InitWindow()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(960, 540, "Tutorial 02 - Red triangle", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return nullptr;

    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

int main(void)
{
    GLFWwindow* window = InitWindow();
    if (!window)
        return -1;

    float positions[] = {
       50.0f,  50.0f, 0.0f, 0.0f, // 0
       100.0f, 50.0f, 1.0f, 0.0f, // 1
       100.0f,  100.0f, 1.0f, 1.0f, // 2
      50.0f,  100.0f, 0.0f, 1.0f  // 3
    };

  
    float positions1[] = {
  100.0f, 100.0f, 0.0f, 0.0f, // 0
  150.0f, 100.0f, 1.0f, 0.0f, // 1
  150.0f, 150.0f, 1.0f, 1.0f, // 2
  100.0f, 150.0f, 0.0f, 1.0f  // 3
    };

    // A rectangle with the bottom left corner at (200, 200)
    float positions2[] = {
      200.0f, 200.0f, 0.0f, 0.0f, // 0
      250.0f, 200.0f, 1.0f, 0.0f, // 1
      250.0f, 300.0f, 1.0f, 1.0f, // 2
      200.0f, 300.0f, 0.0f, 1.0f //3
    };
    
    
    //float positions1[] = {
    //  -50.0f, -50.0f, 0.0f, 0.0f, // 0
    //   50.0f, -50.0f, 1.0f, 0.0f, // 1
    //   50.0f,  50.0f, 1.0f, 1.0f, // 2
    //  -50.0f,  50.0f, 0.0f, 1.0f  // 3
    //};


    //float positions2[] = {
    //  -50.0f, -50.0f, 0.0f, 0.0f, // 0
    //   50.0f, -50.0f, 1.0f, 0.0f, // 1
    //   50.0f,  50.0f, 1.0f, 1.0f, // 2
    //  -50.0f,  50.0f, 0.0f, 1.0f  // 3
    //};


    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };



    // Use the second four vertices in positions1
    unsigned int indices1[] = {
      3, 2, 1,
      2, 1, 0
    };

    // Use the last three vertices in positions2
    unsigned int indices2[] = {
     
      0, 3, 2, 
      1, 2, 1




    };


    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    {
        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        IndexBuffer ib(indices, 6);

        // projection matrix
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

        glm::mat4 projX = glm::ortho(0.0f, 200.0f, 0.0f, 200.0f, -1.0f, 1.0f);

        glm::mat4 projXX =glm::ortho(0.0f, 100.0f, 0.0f, 100.0f, -1.0f, 1.0f);

        // view matrix
        glm::mat4 ident = glm::mat4(1.0f);
        glm::vec3 trvec = glm::vec3(0, 0, 0);
        glm::mat4 view = glm::translate(ident, trvec);

        VertexBufferLayout layout;
        layout.AddFloat(2);
        layout.AddFloat(2);

        va.AddBuffer(vb, layout);

       
        VertexBufferLayout layout1;
        layout1.AddFloat(2);
        layout1.AddFloat(2);

        VertexBufferLayout layout2;
        layout2.AddFloat(2);
        layout2.AddFloat(2);



        // Create three different vertex arrays and index buffers for three different objects
        VertexArray va1;
        VertexBuffer vb1(positions1, 4 * 4 * sizeof(float));
        IndexBuffer ib1(indices1, 6);

        VertexArray va2;
        VertexBuffer vb2(positions2, 4 * 4 * sizeof(float));
        IndexBuffer ib2(indices2, 6);

       /* VertexArray va3;
        VertexBuffer vb3(positions3, 4 * 4 * sizeof(float));
        IndexBuffer ib3(indices3, 6);*/

        // Add the same layout to each vertex array
        va1.AddBuffer(vb1, layout1);
        va2.AddBuffer(vb2, layout2);
       // va3.AddBuffer(vb3, layout);




        Shader shader("Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);

       ///* */Texture texture("phone.png");

        //Texture texture("X.png");
        //Texture texture("golddollar.png");


               // Load the textures and bind them to different texture units
        Texture texture1("phone.png");
        glActiveTexture(GL_TEXTURE0);
        texture1.Bind();

        Texture texture2("X.png");
        glActiveTexture(GL_TEXTURE1);
        texture2.Bind();

        Texture texture3("golddollar.png");
        glActiveTexture(GL_TEXTURE2);
        texture3.Bind();

      /*  texture.Bind();
         
                    
        shader.SetUniform1i("u_Texture", 0);

     
        
       Shader shader2("Basic.shader");
      shader2.Bind();
      shader2.SetUniform4f("u_Color", 0.0f, 0.3f, 0.8f, 1.0f);

        Texture texture4("golddollar.png");
        texture4.Bind();
       shader2.SetUniform1i("u_Texture", 1);*/



        


        
        float red = 0.0f;
        float step = 0.05f;

        Renderer renderer;

     
        glm::vec3 translationA(200, 200, 0);
        glm::vec3 translationB(400, 200, 0);
        glm::vec3 translationC(300, 300, 0);


                do {
                    renderer.Clear();
        
             
                    {
                        //glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                        glm::mat4 model = glm::mat4(1.0f);
                        glm::mat4 mvp = projX * view * model;
                      //  texture1.Bind();                        
                       // shader.Bind();
                        shader.SetUniformMat4f("u_MVP", mvp);
                        shader.SetUniform1i("u_Texture", 0);
                        renderer.Draw(va, ib, shader);
                    }
        
                    {
                        //glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                        glm::mat4 model = glm::mat4(1.0f);
                        glm::mat4 mvp = projX * view * model;
                        //texture1.Bind();
                       // shader.Bind();
                        shader.SetUniformMat4f("u_MVP", mvp);
                        shader.SetUniform1i("u_Texture", 1);
                        renderer.Draw(va1, ib1, shader);
                    }
        
                    {
                        glm::mat4 model = glm::translate(glm::mat4(1.0f), translationC);
                        //glm::mat4 model = glm::mat4(1.0f);
                        glm::mat4 mvp = proj * view * model;
                        //texture1.Unbind();
                        //texture3.Bind();
                        //shader.Bind();
                        shader.SetUniformMat4f("u_MVP", mvp);
                        shader.SetUniform1i("u_Texture", 2);
                        renderer.Draw(va2, ib2, shader);

                    }
        
        
                    // Swap buffers
                    glfwSwapBuffers(window);
                    glfwPollEvents();
        
                    // increment red
                    if (red < 0.0f || red > 1.0f)
                        step *= -1.0;
                    red += step;
        
                } // Check if the ESC key was pressed or the window was closed
                while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
                    glfwWindowShouldClose(window) == 0);
            }
        
            glfwTerminate();

        return 0;
    }

