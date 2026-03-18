#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/model.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float cameraDistance = 7.0f;

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

glm::vec3 playerPos(0.0f, 0.0f, 0.0f);
glm::vec3 cameraPos(0.0f, 4.0f, 7.0f);
const float playerRadius = 0.45f;
const float playerSpeed = 3.2f;

const float arenaMinX = -8.0f;
const float arenaMaxX = 8.0f;
const float arenaMinZ = -8.0f;
const float arenaMaxZ = 8.0f;

std::vector<AABB> obstacles = {
    {{-1.5f, -1.0f, -2.5f}, {1.5f, 2.0f, -1.0f}},
    {{-4.0f, -1.0f,  1.0f}, {-2.0f, 2.0f,  3.5f}},
    {{ 2.0f, -1.0f,  2.0f}, {4.2f, 2.0f,  4.0f}},
};

std::vector<glm::vec3> coinPositions = {
    {-6.0f, 0.3f, -6.0f},
    {-4.0f, 0.3f,  5.0f},
    {-1.5f, 0.3f,  6.5f},
    { 1.0f, 0.3f, -5.0f},
    { 4.8f, 0.3f,  1.0f},
    { 6.0f, 0.3f, -3.0f},
};
std::vector<bool> coinCollected(coinPositions.size(), false);

bool sphereIntersectsAABB(const glm::vec3& center, float radius, const AABB& box) {
    glm::vec3 closest(
        std::clamp(center.x, box.min.x, box.max.x),
        std::clamp(center.y, box.min.y, box.max.y),
        std::clamp(center.z, box.min.z, box.max.z)
    );

    const glm::vec3 delta = center - closest;
    return glm::dot(delta, delta) <= radius * radius;
}

bool isBlocked(const glm::vec3& p) {
    if (p.x - playerRadius < arenaMinX || p.x + playerRadius > arenaMaxX ||
        p.z - playerRadius < arenaMinZ || p.z + playerRadius > arenaMaxZ) {
        return true;
    }

    for (const AABB& wall : obstacles) {
        if (sphereIntersectsAABB(p, playerRadius, wall)) {
            return true;
        }
    }
    return false;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Simple 3D Coin Game", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    Shader shader(
        FileSystem::getPath("src/3.model_loading/1.model_loading/1.model_loading.vs").c_str(),
        FileSystem::getPath("src/3.model_loading/1.model_loading/1.model_loading.fs").c_str()
    );

    Model sceneModel(FileSystem::getPath("resourse/interior_building_scene/scene.gltf"));
    Model playerModel(FileSystem::getPath("resourse/FarmerPack/Character/Farmer/SKM_Farmer_male.fbx"));
    Model coinModel(FileSystem::getPath("resourse/gold_coin_low_poly/source/GoldCoin/coin.fbx"));

    int collectedCount = 0;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        for (size_t i = 0; i < coinPositions.size(); ++i) {
            if (coinCollected[i]) {
                continue;
            }
            float d = glm::length(playerPos - coinPositions[i]);
            if (d < 0.8f) {
                coinCollected[i] = true;
                collectedCount++;
            }
        }

        const glm::vec3 followOffset(0.0f, 4.2f, cameraDistance);
        glm::vec3 targetCam = playerPos + followOffset;
        float smooth = std::min(1.0f, 5.0f * deltaTime);
        cameraPos = glm::mix(cameraPos, targetCam, smooth);

        std::ostringstream title;
        title << "Simple 3D Coin Game | Coins: " << collectedCount << "/" << coinPositions.size();
        if (collectedCount == static_cast<int>(coinPositions.size())) {
            title << " | You Win!";
        }
        glfwSetWindowTitle(window, title.str().c_str());

        glClearColor(0.08f, 0.08f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 200.0f);
        glm::mat4 view = glm::lookAt(cameraPos, playerPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.2f));
        shader.setMat4("model", model);
        sceneModel.Draw(shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, playerPos);
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.010f));
        shader.setMat4("model", model);
        playerModel.Draw(shader);

        for (size_t i = 0; i < coinPositions.size(); ++i) {
            if (coinCollected[i]) {
                continue;
            }

            model = glm::mat4(1.0f);
            model = glm::translate(model, coinPositions[i] + glm::vec3(0.0f, 0.2f * std::sin(currentFrame * 2.0f + i), 0.0f));
            model = glm::rotate(model, currentFrame * 2.5f, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.012f));
            shader.setMat4("model", model);
            coinModel.Draw(shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    glm::vec3 movement(0.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        movement.z -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        movement.z += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        movement.x -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        movement.x += 1.0f;
    }

    if (glm::length(movement) > 0.0f) {
        movement = glm::normalize(movement) * playerSpeed * deltaTime;

        glm::vec3 nextX = playerPos + glm::vec3(movement.x, 0.0f, 0.0f);
        if (!isBlocked(nextX)) {
            playerPos.x = nextX.x;
        }

        glm::vec3 nextZ = playerPos + glm::vec3(0.0f, 0.0f, movement.z);
        if (!isBlocked(nextZ)) {
            playerPos.z = nextZ.z;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    (void)window;
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    (void)window;
    (void)xoffset;
    cameraDistance -= static_cast<float>(yoffset) * 0.6f;
    cameraDistance = std::clamp(cameraDistance, 4.0f, 12.0f);
}
