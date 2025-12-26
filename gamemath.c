#include "raylib.h"

#include "colors.h"

#define VECTOR3(x, y, z) \
    CLITERAL(Vector3) { x, y, z }

#define VECTOR3_ZERO VECTOR3(0,0,0)
#define VECTOR3_ONE VECTOR3(1,1,1)
#define VECTOR3_RIGHT VECTOR3(1,0,0)
#define VECTOR3_UP VECTOR3(0,1,0)
#define VECTOR3_FORWARD VECTOR3(0,0,1)

#define FONT_PATH "fonts/computer-modern/cmunrm.ttf"
#define FONT_SIZE 32

#define EXTENT 10

static Font font;

typedef struct
{
    Mesh cone;
    Mesh cylinder;
    Mesh knot;
} Meshes;

Meshes gen_meshes()
{
    Meshes meshes = {
        .cone = GenMeshCone(1, 2, 32),
        .cylinder = GenMeshCylinder(1, 2, 16),
        .knot = GenMeshKnot(1, 2, 16, 128),
    };

    return meshes;
}

typedef struct
{
    Model cone;
    Model cylinder;
    Model knot;
} Models;

Models load_models(Meshes meshes)
{
    Models models = {
        .cone = LoadModelFromMesh(meshes.cone),
        .cylinder = LoadModelFromMesh(meshes.cylinder),
        .knot = LoadModelFromMesh(meshes.knot),
    };

    return models;
}

float sign(float value)
{
    return value < 0 ? -1 : 1;
}

void draw_guidelines(Vector3 camera_position)
{
    float sign_x = sign(camera_position.x);
    float sign_y = sign(camera_position.y);
    float sign_z = sign(camera_position.z);

    float to = EXTENT;
    
    Color color_x = RED_950;
    Color color_y = GREEN_950;
    Color color_z = BLUE_950;

    for (int i = 0; i <= EXTENT; ++i)
    {
        float fi = (float)i;

        float to_x = sign_x * to;
        float to_y = sign_y * to;
        float to_z = sign_z * to;

        float xi = sign_x * fi;
        float yi = sign_y * fi;
        float zi = sign_z * fi;

        { // xz plane

            { // x guides
                Vector3 a = {0, 0, zi};
                Vector3 b = {to_x, 0, zi};
                DrawLine3D(a, b, color_x);
            }

            { // z guides
                Vector3 a = {xi, 0, 0};
                Vector3 b = {xi, 0, to_z};
                DrawLine3D(a, b, color_z);
            }
        }

        {     // xy plane
            { // x guides
                Vector3 a = {0, yi, 0};
                Vector3 b = {to_x, yi, 0};
                DrawLine3D(a, b, color_x);
            }

            { // y guides
                Vector3 a = {xi, 0, 0};
                Vector3 b = {xi, to_y, 0};
                DrawLine3D(a, b, color_y);
            }
        }

        { // yz plane

            { // y guides
                Vector3 a = {0, 0, zi};
                Vector3 b = {0, to_y, zi};
                DrawLine3D(a, b, color_y);
            }

            // z guides
            {
                Vector3 a = {0, yi, 0};
                Vector3 b = {0, yi, to_z};
                DrawLine3D(a, b, color_z);
            }
        }
    }
}

void draw_axes(Vector3 camera_position, Models models)
{
    bool neg_x = camera_position.x < 0;
    bool neg_y = camera_position.y < 0;
    bool neg_z = camera_position.z < 0;

    float length = EXTENT / 2;
    float thickness = 0.1f;

    Vector3 scale = {thickness, length, thickness};

    Color xOn = RED_600;
    Color yOn = GREEN_600;
    Color zOn = BLUE_600;

    Color xOff = RED_950;
    Color yOff = GREEN_950;
    Color zOff = BLUE_950;

    Color xPos = neg_x ? xOff : xOn;
    Color yPos = neg_y ? yOff : yOn;
    Color zPos = neg_z ? zOff : zOn;

    Color xNeg = neg_x ? xOn : xOff;
    Color yNeg = neg_y ? yOn : yOff;
    Color zNeg = neg_z ? zOn : zOff;

    // axis
    {
        DrawModelEx(models.cylinder, VECTOR3_ZERO, VECTOR3_FORWARD, -90, scale, xPos);
        DrawModelEx(models.cylinder, VECTOR3_ZERO, VECTOR3_FORWARD, 90, scale, xNeg);
        DrawModelEx(models.cylinder, VECTOR3_ZERO, VECTOR3_UP, 0, scale, yPos);
        DrawModelEx(models.cylinder, VECTOR3_ZERO, VECTOR3_RIGHT, 180, scale, yNeg);
        DrawModelEx(models.cylinder, VECTOR3_ZERO, VECTOR3_RIGHT, 90, scale, zPos);
        DrawModelEx(models.cylinder, VECTOR3_ZERO, VECTOR3_RIGHT, -90, scale, zNeg);
    }

    // tips
    {
        float size = 0.4f;

        Vector3 scale = {size, size, size};

        Vector3 x_end = {EXTENT, 0, 0};
        Vector3 y_end = {0, EXTENT, 0};
        Vector3 z_end = {0, 0, EXTENT};

        DrawModelEx(models.cone, x_end, VECTOR3_FORWARD, -90, scale, neg_x ? RED_900 : RED_500);
        DrawModelEx(models.cone, y_end, VECTOR3_UP, 0, scale, neg_y ? GREEN_900 : GREEN_500);
        DrawModelEx(models.cone, z_end, VECTOR3_RIGHT, 90, scale, neg_z ? BLUE_900 : BLUE_500);
    }
}

typedef struct
{
    Vector2 position;
    bool left_pressed;
    bool left_down;
    Vector2 position_left_pressed;
} Mouse;

typedef struct
{
    float x;
    float y;
    float z;
    float fovy;
    int projection;
} Input;

Vector2 right_of(Rectangle rectangle, float gap)
{
    Vector2 position = {
        .x = rectangle.x + rectangle.width + gap,
        .y = rectangle.y,
    };

    return position;
}

typedef struct
{
    Font font;
    float font_size;
    float spacing;
} FontStyle;

typedef struct
{
    float top;
    float right;
    float bottom;
    float left;
} Padding;

void draw_text(FontStyle font_style, Vector2 position, const char *text, Color color)
{
    DrawTextEx(font_style.font, text, position, font_style.font_size, font_style.spacing, color);
}

void contain_text(Vector2 position, FontStyle font_style, Padding padding, const char *text, Rectangle *container, Vector2 *text_position)
{
    Vector2 text_size = MeasureTextEx(font_style.font, text, font_style.font_size, font_style.spacing);

    *container = (Rectangle){
        .x = position.x,
        .y = position.y,
        .width = padding.left + text_size.x + padding.right,
        .height = padding.top + text_size.y + padding.bottom,
    };

    *text_position = (Vector2){
        .x = position.x + padding.left,
        .y = position.y + padding.top,
    };
}

bool rectangle_contains_point(Rectangle rectangle, Vector2 point)
{
    float x = point.x;
    float y = point.y;

    float x_min = rectangle.x;
    float y_min = rectangle.y;

    if (x < x_min || y < y_min)
    {
        return false;
    }

    float x_max = rectangle.x + rectangle.width;
    float y_max = rectangle.y + rectangle.height;

    if (x > x_max || y > y_max)
    {
        return false;
    }

    return true;
}

float clamp(float min, float max, float value)
{
    return value < min ? min : value > max ? max
                                           : value;
}

bool draw_toggle(Rectangle rectangle, Mouse mouse, bool enabled)
{
    if (enabled)
    {
        DrawRectangleRec(rectangle, FOREGROUND);
    }
    else
    {
        DrawRectangleLinesEx(rectangle, 1, FOREGROUND);
    }

    if (!enabled && mouse.left_pressed && rectangle_contains_point(rectangle, mouse.position_left_pressed))
    {
        return true;
    }

    return false;
}

float draw_slider(Rectangle rectangle, float handle_width, Color handle_color, float min, float max, float value, Mouse mouse)
{
    float pct = (value - min) / (max - min);

    float x_min = rectangle.x;
    float x_max = rectangle.x + rectangle.width - handle_width;

    Rectangle handle = {
        .width = handle_width,
        .height = rectangle.height,
        .x = x_min + pct * (x_max - x_min),
        .y = rectangle.y,
    };

    if (mouse.left_down && rectangle_contains_point(rectangle, mouse.position_left_pressed))
    {
        float x = clamp(x_min, x_max, mouse.position.x);

        pct = (x - x_min) / (x_max - x_min);
        value = min + pct * (max - min);

        handle.x = x;
    }

    DrawRectangleRec(handle, handle_color);
    DrawRectangleLinesEx(rectangle, 1, FOREGROUND);

    return value;
}

void draw_controls(Mouse mouse, Input *input)
{
    float x = 32;
    float y = 32;

    // x
    {

        float value = input->x;
        Rectangle slider = {
            .x = x,
            .y = y,
            .width = 320,
            .height = FONT_SIZE,
        };
        value = draw_slider(slider, FONT_SIZE, RED_600, -100, 100, value, mouse);

        Vector2 position = right_of(slider, 8);
        const char *text = TextFormat("x: %.2f", value);
        DrawTextEx(font, text, position, FONT_SIZE, 1, FOREGROUND);

        input->x = value;
        y += slider.height;
    }

    y += 16;

    // y
    {

        float value = input->y;
        Rectangle slider = {
            .x = x,
            .y = y,
            .width = 320,
            .height = FONT_SIZE,
        };
        value = draw_slider(slider, FONT_SIZE, GREEN_600, -100, 100, value, mouse);

        Vector2 position = right_of(slider, 8);
        const char *text = TextFormat("y: %.2f", value);
        DrawTextEx(font, text, position, FONT_SIZE, 1, FOREGROUND);

        input->y = value;
        y += slider.height;
    }

    y += 16;

    // z
    {

        float value = input->z;
        Rectangle slider = {
            .x = x,
            .y = y,
            .width = 320,
            .height = FONT_SIZE,
        };
        value = draw_slider(slider, FONT_SIZE, BLUE_600, -100, 100, value, mouse);

        Vector2 position = right_of(slider, 8);
        const char *text = TextFormat("z: %.2f", value);
        DrawTextEx(font, text, position, FONT_SIZE, 1, FOREGROUND);

        input->z = value;
        y += slider.height;
    }

    y += 16;

    // fov-y
    {

        float value = input->fovy;
        Rectangle slider = {
            .x = x,
            .y = y,
            .width = 320,
            .height = FONT_SIZE,
        };
        value = draw_slider(slider, FONT_SIZE, YELLOW, 0, 360, value, mouse);

        Vector2 position = right_of(slider, 8);
        const char *text = TextFormat("fov: %.2f", value);
        DrawTextEx(font, text, position, FONT_SIZE, 1, FOREGROUND);

        input->fovy = value;
        y += slider.height;
    }

    y += 16;

    {
        Vector2 toggle_position = {
            .x = x,
            .y = y,
        };

        FontStyle font_style = {
            .font = font,
            .font_size = FONT_SIZE,
            .spacing = 1,
        };

        Padding padding = {8, 16, 8, 16};

        {
            const char *text = "Perspective";

            Rectangle toggle;
            Vector2 text_position;
            contain_text(toggle_position, font_style, padding, text, &toggle, &text_position);

            bool enabled = input->projection == CAMERA_PERSPECTIVE;
            bool clicked = draw_toggle(toggle, mouse, enabled);
            if (clicked)
            {
                input->projection = CAMERA_PERSPECTIVE;
            }

            draw_text(font_style, text_position, text, enabled ? BACKGROUND : FOREGROUND);

            toggle_position.x += toggle.width;
        }

        {
            const char *text = "Orthographic";

            Rectangle toggle;
            Vector2 text_position;
            contain_text(toggle_position, font_style, padding, text, &toggle, &text_position);

            bool enabled = input->projection == CAMERA_ORTHOGRAPHIC;
            bool clicked = draw_toggle(toggle, mouse, enabled);
            if (clicked)
            {
                input->projection = CAMERA_ORTHOGRAPHIC;
            }

            draw_text(font_style, text_position, text, enabled ? BACKGROUND : FOREGROUND);
        }
    }
}

int main(void)
{
    const int screenWidth = 16 * 100;
    const int screenHeight = 9 * 100;

    InitWindow(screenWidth, screenHeight, "Game Math");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    Meshes meshes = gen_meshes();
    Models models = load_models(meshes);

    RenderTexture2D background = LoadRenderTexture(screenWidth, screenHeight);

    Camera3D camera = {
        .position = (Vector3){2 * EXTENT, 2 * EXTENT, 2 * EXTENT},
        .target = (Vector3){0.0f, 0.0f, 0.0f},
        .up = (Vector3){0.0f, 1.0f, 0.0f},
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE,
    };

    font = LoadFont(FONT_PATH);

    SetTargetFPS(60);

    Mouse mouse = {0};

    Input input = {
        .x = camera.position.x,
        .y = camera.position.y,
        .z = camera.position.z,
        .fovy = camera.fovy,
    };

    while (!WindowShouldClose())
    {
        // Update

        camera.position.x = input.x;
        camera.position.y = input.y;
        camera.position.z = input.z;
        camera.fovy = input.fovy;
        camera.projection = input.projection;

        mouse.position = GetMousePosition();
        mouse.left_pressed = IsMouseButtonPressed(0);
        mouse.left_down = IsMouseButtonDown(0);
        if (mouse.left_pressed)
        {
            mouse.position_left_pressed = mouse.position;
        }

        // Draw
        {

            {
                BeginTextureMode(background);
                ClearBackground(BACKGROUND);

                BeginMode3D(camera);

                draw_guidelines(camera.position);

                EndMode3D();

                EndTextureMode();
            }

            BeginDrawing();

            ClearBackground(BACKGROUND);

            {
                Texture2D texture = background.texture;
                Rectangle source = {
                    0.0f,
                    0.0f,
                    (float)background.texture.width,
                    (float)-background.texture.height};
                Rectangle dest = {
                    (GetScreenWidth() - ((float)screenWidth)) * 0.5f,
                    (GetScreenHeight() - ((float)screenHeight)) * 0.5f,
                    (float)screenWidth,
                    (float)screenHeight};
                Vector2 origin = {0, 0};
                float rotation = 0.0f;
                Color tint = WHITE;
                DrawTexturePro(texture, source, dest, origin, rotation, tint);
            }

            {
                BeginMode3D(camera);

                draw_axes(camera.position, models);

                // DrawModel(models.knot, VECTOR3_ZERO, 3, WHITE);

                EndMode3D();
            }

            draw_controls(mouse, &input);

            EndDrawing();
        }
    }

    CloseWindow();

    return 0;
}
