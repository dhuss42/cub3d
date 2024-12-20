#include "../cub.h"

#include <stdio.h>

// Define a 2D vector
typedef struct {
    float x;
    float y;
} Vector2D;

// Function to compute a perpendicular vector
Vector2D perpendicularVector(Vector2D v, float scale) {
    return (Vector2D){-v.y * scale, v.x * scale};
}

// Function to compute a ray direction
Vector2D computeRayDir(Vector2D playerDir, Vector2D cameraPlane, float x, int screenWidth) {
    float cameraX = 2 * x / (float)screenWidth - 1; // Map x to [-1, 1]
    return (Vector2D){
        playerDir.x + cameraPlane.x * cameraX,
        playerDir.y + cameraPlane.y * cameraX
    };
}

// Example usage
int main() {
    // Player position and direction
    Vector2D playerPos = {4.0, 4.0};
    Vector2D playerDir = {1.0, 0.0}; // Facing right

    // Camera plane (perpendicular to direction, scaled for FOV)
    Vector2D cameraPlane = perpendicularVector(playerDir, 0.66);

    // Screen resolution
    int screenWidth = 640;

    // Compute a ray for each screen pixel
    for (int x = 0; x < screenWidth; x++) {
        Vector2D rayDir = computeRayDir(playerDir, cameraPlane, x, screenWidth);
        printf("Ray for pixel %d: (%.2f, %.2f)\n", x, rayDir.x, rayDir.y);
    }

    return 0;
}
