#define OLC_PGE_APPLICATION
#include "../../lib/olcPixelGameEngine.h"

#include "../included.h"

class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		sAppName = core::game_title;
	}

public:

    enum PAUSE_STATES
    {
        psTILES,
        psWANDS,
    };
    enum ITEM_TYPES
    {
        itNONE,
        itTILE,
        itWAND,
    };

    enum STATES
    {
        TITLE,
        CUSTOM,
        LOADING,
        PLAYING,
        INVENTORY,
        PAUSED,
        EXIT
    };

    bool running = true;
    bool creative_mode = true;
    bool show_grid = false;
    bool loading = false;

    float game_tick = 0.0;
    float tick_delay = 0.033;

    int game_state = 0;
    int pause_state = 0;

    char selected_hotbar = 0;
    char selected_tile = 0;
    char selected_wand = 0;
    int input_value = 0;
    char save_slot = 0;

    int width = core::width;
    int height = core::height;
    int pixel_size = core::resolution;
    int grid_subdivision = 5;

    int world_width = 4096;//8192;
    int world_height = 2048;//4096;

    std::vector<Particle> particles;



    Icon icon = Icon();
    Sky sky = Sky();
    World world = World();
    Player player = Player();

    olc::Pixel hud_color = olc::Pixel(64, 64, 64);
    olc::Pixel hud_select_color = olc::Pixel(255, 255, 255);
    olc::Pixel grid_color = olc::Pixel(0, 0, 0, 64);
    olc::Pixel text_color = olc::Pixel(255, 255, 255);
    olc::Pixel panel_color = olc::Pixel(10, 10, 10);
    olc::Pixel border_color = olc::Pixel(80, 80, 80);
    olc::Pixel button_color = olc::Pixel(32, 32, 32);
    olc::Pixel select_color = olc::Pixel(64, 64, 64);


    void GenerateData()
    {
        std::string _dir = os::GetCWD() + "/data";
        std::string _cmd = "mkdir " + _dir;
        const char* mkdir_cmd = _cmd.c_str();
        system(mkdir_cmd);
    }

    void InstallGame()
    {
        tTile::LoadTileData();
        GenerateData();
    }

    void SaveWorldData()
    {
    }
    
    void LoadWorldData()
    {
    }

    void SaveChunkData(int X, int Y, std::string data_dir = "")
    {
        std::fstream data_file;
        data_dir = std::to_string(X) + "-" + std::to_string(Y);
        std::string _dir = os::GetCWD() + "/data/" + data_dir;
        data_file.open(_dir);

        int x_ = X*world.chunk_size;
        int y_ = Y*world.chunk_size;

        if (data_file.is_open())
        {
            for (int y = 0; y < world.chunk_size; y++)
            {
                for (int x = 0; x < world.chunk_size; x++)
                {
                    int index = (y_+y)*tCell::width+(x_+x);
                    int tile = tCell::matrix[index];
                    data_file << tile << ",\t";
                }
                data_file << std::endl;
            }
            data_file.close();
        }
        else
        {
            std::ofstream new_file (_dir);
            SaveChunkData(X, Y, data_dir);
        }
    }

    void LoadChunkData(int X, int Y, std::string data_dir = "")
    {
        std::string line;
        data_dir = std::to_string(X) + "-" + std::to_string(Y);
        std::fstream data_file;
        std::string _dir = os::GetCWD() + "/data/" + data_dir;
        data_file.open(_dir);

        int x = 0;
        int y = 0;
        int x_ = X*world.chunk_size;
        int y_ = Y*world.chunk_size;

        if (data_file.is_open())
        {
            std::string v = "";
            while (getline(data_file, line))
            {
                for (int i = 0; i < line.length(); i++)
                {
                    std::string c = line.substr(i, 1);
                    if (c == ",") {x++;}
                    if (
                            c == "1" || c == "2" || c == "3" || c == "4" || c == "5" ||
                            c == "6" || c == "7" || c == "8" || c == "9" || c == "0"
                            )
                    {
                        v = v + c;
                    }
                }
                int value = std::stoi(v);
                int index = (y_+y)*tCell::width+(x_+x);
                tCell::matrix[index] = value;
                v = "";
                y++;
                x = 0;
            }
            data_file.close();
        }
    }

    void SavePlayerData(std::string data_dir = "player_data")
    {
        std::fstream data_file;
        std::string _dir = os::GetCWD() + "/data/" + data_dir;
        data_file.open(_dir);

        if (data_file.is_open())
        {
            data_file << "#tiles" << std::endl;
            for (int i = 0; i < player.inventory.data.size(); i++)
            {
                data_file << i << "=" << player.inventory.data[i] << std::endl;
            }
            data_file.close();
        }
        else
        {
            std::ofstream new_file (_dir);
            SavePlayerData(data_dir);
        }
    }

    void LoadPlayerData(std::string data_dir = "player_data")
    {
        std::string line;
        std::fstream data_file;
        std::string _dir = os::GetCWD() + "/data/" + data_dir;
        data_file.open(_dir);

        if (data_file.is_open())
        {
            std::string read_state = "";

            while (getline(data_file, line))
            {
                if (line == "#tiles")
                {
                    read_state = "#tiles";
                }

                if (read_state == "#tiles")
                {
                    bool next = false;
                    std::string itm = "";
                    std::string amnt = "";

                    for (int i = 0; i < line.length(); i++)
                    {
                        std::string c = line.substr(i, 1);
                        if (c == "=")
                        {
                            next = true;
                        }
                        if (
                                c == "1" || c == "2" || c == "3" || c == "4" || c == "5" ||
                                c == "6" || c == "7" || c == "8" || c == "9" || c == "0"
                                )
                        {
                            if (!next) {itm = itm + c;}
                            if (next) {amnt = amnt + c;}
                        }
                    }
                    if (line.substr(0, 1) != "#")
                    {
                        int item = std::stoi(itm);
                        int amount = std::stoi(amnt);
                        player.inventory.AddItem(item, amount);
                    }
                }
            }
        data_file.close();
        }
    }

    void SaveGenerationData(std::string data_dir)
    {
        std::string line;
        std::fstream data_file;
        std::string _dir = os::GetCWD() + "/data/" + data_dir;
        data_file.open(_dir);
        
        if (data_file.is_open())
        {
            for (int i = 0; i < new_world::generation_steps; i++)
            {
                for (int j = 0; j < new_world::total_parameters; j++)
                {
                    data_file << new_world::generation_param[i][j] << std::endl;
                }
            }
            data_file.close();
        }
        else
        {
            std::ofstream new_file (_dir);
            SaveGenerationData(data_dir);
        }
    }

    void LoadGenerationData(std::string data_dir)
    {
        std::string line;
        std::fstream data_file;
        std::string _dir = os::GetCWD() + "/data/" + data_dir;
        data_file.open(_dir);

        if (data_file.is_open())
        {
            int i = 0;
            int j = 0;
            while (getline(data_file, line))
            {
                if (i <= new_world::maximum_generation_steps && line != "")
                {
                    new_world::generation_param[i][j] = std::stoi(line);
                    j++;
                    if (j % new_world::total_parameters == 0)
                    {
                        i++;
                        j = 0;
                    }
                }
            }
            new_world::generation_steps = i;
            data_file.close();
        }
    }



    //
    //
    //

    void SpawnParticle(float X, float Y, Effect e)
    {
        float W = width/2;
        float H = height/2;
        Particle p = Particle();
        p.SetEffect(e);
        p.Position(player.x+(player.direction*(player.height/2)), player.y-player.height/2);
        p.Velocity(float((X-W)*0.1), float((Y-H)*0.1));
        particles.push_back(p);
    }

    void ProgressBar(int x, int y, int minv, int maxv, int W, int R=255, int G=255, int B=255, int r=64, int g=64, int b=64)
    {
        float completed = float(minv)/float(maxv);
        int x2 = W*completed;
        DrawLine(x, y, x+W, y, olc::Pixel(r, g, b));
        DrawLine(x, y, x+x2, y, olc::Pixel(R, G, B));
    }

    void HotbarInput()
    {
        if (GetKey(olc::Key::K1).bPressed) {selected_hotbar = 0;}
        if (GetKey(olc::Key::K2).bPressed) {selected_hotbar = 1;}
        if (GetKey(olc::Key::K3).bPressed) {selected_hotbar = 2;}
        if (GetKey(olc::Key::K4).bPressed) {selected_hotbar = 3;}
        if (GetKey(olc::Key::K5).bPressed) {selected_hotbar = 4;}
        if (GetKey(olc::Key::K6).bPressed) {selected_hotbar = 5;}
        if (GetKey(olc::Key::K7).bPressed) {selected_hotbar = 6;}
        if (GetKey(olc::Key::K8).bPressed) {selected_hotbar = 7;}
        if (GetKey(olc::Key::K9).bPressed) {selected_hotbar = 8;}
    }


    //
    //
    //

    void DrawChunkGrid()
    {
        if (!show_grid) return;
        //grid_subdivision
        int _x = player.x % (world.chunk_size/grid_subdivision);
        int _y = player.y % (world.chunk_size/grid_subdivision);
        for (int y = 0; y < height+world.chunk_size; y += world.chunk_size/grid_subdivision)
        {
            DrawLine({0-_x, y-_y}, {width-_x+world.chunk_size, y-_y}, olc::Pixel(grid_color));
        }
        for (int x = 0; x < width+world.chunk_size; x += world.chunk_size/grid_subdivision)
        {
            DrawLine({x-_x, 0-_y}, {x-_x, height-_y+world.chunk_size}, olc::Pixel(grid_color));
        }
    }

    void DrawIcon(int x, int y, int tile_type, int tile_value)
    {
        int *img;
        switch (tile_type)
        {
            case tTile::GAS      : { img = icon.gas;      } break;
            case tTile::PLASMA   : { img = icon.plasma;   } break;
            case tTile::FUME     : { img = icon.fume;     } break;
            case tTile::FLUID    : { img = icon.fluid;    } break;
            case tTile::GRAIN    : { img = icon.grain;    } break;
            case tTile::GEL      : { img = icon.gel;      } break;
            case tTile::SOLID    : { img = icon.solid;    } break;
            case tTile::LOOSE    : { img = icon.loose;    } break;
            case tTile::BOOM     : { img = icon.boom;     } break;
            case tTile::LOGIC    : { img = icon.logic;    } break;
            case tTile::GIZMO    : { img = icon.gizmo;    } break;
            case tTile::PLATFORM : { img = icon.platform; } break;
            case tTile::PLUMBING : { img = icon.plumbing; } break;
            case tTile::PLANT    : { img = icon.plant;    } break;
            case tTile::CRITTER  : { img = icon.critter;  } break;
        }
        float R = float(tTile::R[tile_value]);
        float G = float(tTile::G[tile_value]);
        float B = float(tTile::B[tile_value]);
        int A = tTile::A[tile_value];
        for (int iy = 0; iy < icon.size; iy++)
        {
            for (int ix = 0; ix < icon.size; ix++)
            {
                int index_value = *(img+iy*icon.size+ix);//[iy*icon.size+ix];
                float v = (0.125*float(index_value));
                if (index_value > 0) Draw(ix+x, iy+y, olc::Pixel(int(R*v), int(G*v), int(B*v), A));
            }
        }
    }

    void DrawWands()
    {
        int cols = 16;
        int rows = 8;
        int x_margin = 48;
        int y_margin = 32;
        int wand_value = 0;

        Button buttons[cols*rows];

        FillRect({x_margin-3, y_margin-3}, {167, 87}, panel_color);
        DrawRect({x_margin-4, y_margin-4}, {168, 88}, border_color);
        SetPixelMode(olc::Pixel::ALPHA);
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < cols; x++)
            {
                if (wand_value < player.wands.size())
                {
                    int wand_color = player.wands[wand_value].material;
                    float R = float(tTile::R[wand_color]);
                    float G = float(tTile::G[wand_color]);
                    float B = float(tTile::B[wand_color]);
                    int A = tTile::A[wand_color];
                    for (int iy = 0; iy < icon.size; iy++)
                    {
                        for (int ix = 0; ix < icon.size; ix++)
                        {
                            Button b = Button();
                            b.Setup((x*10)+x_margin, (y*10)+y_margin, 9, 9, 1.0, std::to_string(wand_value));
                            buttons[y*cols+x] = b;
                            int index_value = icon.wand[iy*icon.size+ix];
                            float v = (0.25*float(index_value));
                            if (index_value > 0) Draw(ix+(x*10)+x_margin, iy+(y*10)+y_margin, olc::Pixel(int(R*v), int(G*v), int(B*v), A));
                        }
                    }
                }
                wand_value++;
            }
        }
        SetPixelMode(olc::Pixel::NORMAL);

        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < cols; x++)
            {
                Button b = buttons[y*cols+x];
                if (b.IsColliding(GetMouseX(), GetMouseY()))
                {
                    DrawRect(b.x, b.y, b.width, b.height, select_color);
                    if (GetMouse(0).bReleased)
                    {
                        player.hotbar[selected_hotbar][0] = itWAND;
                        player.hotbar[selected_hotbar][1] = std::stoi(b.text);
                    }
                }
            }
        }
    }

    void DrawInventory()
    {
        int cols = 16;
        int rows = 8;
        int x_margin = 48;
        int y_margin = 32;
        int tile_value = 0;

        Button buttons[cols*rows];

        FillRect({x_margin-3, y_margin-3}, {167, 87}, panel_color);
        DrawRect({x_margin-4, y_margin-4}, {168, 88}, border_color);
        SetPixelMode(olc::Pixel::ALPHA);
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < cols; x++)
            {
                int tile_type = tTool::GetType(tile_value);
                if (tile_value < tTile::total_tiles)
                {
                    Button b = Button();
                    b.Setup((x*10)+x_margin, (y*10)+y_margin, 9, 9, 1.0, std::to_string(tile_value));
                    buttons[y*cols+x] = b;
                    DrawIcon((x*10)+x_margin+1, (y*10)+y_margin+1, tile_type, tile_value);
                }
                tile_value++;
            }
        }
        SetPixelMode(olc::Pixel::NORMAL);
        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < cols; x++)
            {
                Button b = buttons[y*cols+x];
                if (b.IsColliding(GetMouseX(), GetMouseY()))
                {
                    DrawRect(b.x, b.y, b.width, b.height, select_color);
                    if (GetMouse(0).bReleased)
                    {
                        player.hotbar[selected_hotbar][0] = itTILE;
                        player.hotbar[selected_hotbar][1] = std::stoi(b.text);
                    }
                }
            }
        }
    }

    void DrawSky()
    {
        if (player.status != player.TRIP) Clear(olc::Pixel(sky.R, sky.G, sky.B));
        
        if (sky.starlight >= 0)
        {
            SetPixelMode(olc::Pixel::ALPHA);
            for (int i = 0; i < sky.starcount; i += 4)
            {
                int value = rand()%220+35;
                Draw(sky.stars[i][0], sky.stars[i][1], olc::Pixel(value, value, value, 255-sky.starlight));
                Draw(sky.stars[i+1][0], sky.stars[i][1], olc::Pixel(value, value, value, 255-sky.starlight));
                Draw(sky.stars[i+2][0], sky.stars[i][1], olc::Pixel(value, value, value, 255-sky.starlight));
                Draw(sky.stars[i+3][0], sky.stars[i][1], olc::Pixel(value, value, value, 255-sky.starlight));
            }
        }

        if (sky.time > 0.5)
        {
            FillCircle(sky.sunx, sky.suny, sky.sun, olc::WHITE);
            FillCircle(sky.sunx, sky.suny, sky.sun*1.2, olc::Pixel(255, 255, 255, 24));
            FillCircle(sky.sunx, sky.suny, sky.sun*1.3, olc::Pixel(255, 255, 255, 20));
            FillCircle(sky.sunx, sky.suny, sky.sun*1.4, olc::Pixel(255, 255, 255, 16));
            FillCircle(sky.sunx, sky.suny, sky.sun*1.5, olc::Pixel(255, 255, 255, 12));
        }
        else if (sky.time < 0.5)
        {
            FillCircle(sky.moonx, sky.moony, sky.moon, olc::WHITE);
            FillCircle(sky.moonx, sky.moony, sky.moon*1.2, olc::Pixel(255, 255, 255, 24));
            FillCircle(sky.moonx, sky.moony, sky.moon*1.3, olc::Pixel(255, 255, 255, 20));
            FillCircle(sky.moonx, sky.moony, sky.moon*1.4, olc::Pixel(255, 255, 255, 16));
            FillCircle(sky.moonx, sky.moony, sky.moon*1.5, olc::Pixel(255, 255, 255, 12));

            FillCircle(sky.moonx, sky.moony, sky.moon*0.95, olc::Pixel(220, 220, 220));
            FillCircle(sky.moonx-2, sky.moony+1, sky.moon/2, olc::Pixel(195, 195, 195));
            FillCircle(sky.moonx+3, sky.moony+3, sky.moon/2, olc::Pixel(195, 195, 195));
            FillCircle(sky.moonx+2, sky.moony-1, sky.moon/3, olc::Pixel(170, 170, 170));
            FillCircle(sky.moonx-3, sky.moony-4, sky.moon/3, olc::Pixel(170, 170, 170));
            FillCircle(sky.moonx-2, sky.moony+3, sky.moon/4, olc::Pixel(145, 145, 145));
            FillCircle(sky.moonx+3, sky.moony+4, sky.moon/4, olc::Pixel(145, 145, 145));
            FillCircle(sky.moonx+3, sky.moony-2, sky.moon/5, olc::Pixel(120, 120, 120));
            FillCircle(sky.moonx-4, sky.moony-3, sky.moon/5, olc::Pixel(120, 120, 120));
        }
        for (int i = 0; i < sky.humidity; i++)
        {
            int x = sky.clouds[i][0];
            int y = sky.clouds[i][1];
            FillCircle(x, y, sky.clouds[i][2], olc::Pixel(sky.r, sky.g, sky.b, 4+(8*sky.time)));
        }
        if (sky.humidity > sky.cloudcount/4)
        {
            if (rand()%sky.cloudcount < sky.humidity)
            {
                if (sky.day < sky.year_length*0.75) tCell::matrix[256*tCell::width+((rand()%width)+player.x-(width/2))] = tTile::WATER;
                else if (sky.day >= sky.year_length*0.75) tCell::matrix[256*tCell::width+((rand()%width)+player.x-(width/2))] = tTile::SNOW;
            }
        }
        SetPixelMode(olc::Pixel::NORMAL);
    }

    void DrawTerrain()
    {
        int X = player.x - (width/2);
        int Y = player.y - (height/2);
        SetPixelMode(olc::Pixel::ALPHA);
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x += 4)
            {
                if ( (x+X > 0 && x+X < tCell::width-1) && (y+Y > 1 && y+Y < tCell::height-1) )
                {
                    int v1 = tCell::matrix[(y+Y)*tCell::width+(x+X)];
                    int v2 = tCell::matrix[(y+Y)*tCell::width+(x+X+1)];
                    int v3 = tCell::matrix[(y+Y)*tCell::width+(x+X)+2];
                    int v4 = tCell::matrix[(y+Y)*tCell::width+(x+X)+3];

                    float s1 = 1.0f-std::min(std::max(tTool::Neighbors(x+X, y+Y), 0.0f), 1.0f);
                    float s2 = 1.0f-std::min(std::max(tTool::Neighbors(x+X+1, y+Y), 0.0f), 1.0f);
                    float s3 = 1.0f-std::min(std::max(tTool::Neighbors(x+X+2, y+Y), 0.0f), 1.0f);
                    float s4 = 1.0f-std::min(std::max(tTool::Neighbors(x+X+3, y+Y), 0.0f), 1.0f);

                    Draw(x, y, olc::Pixel(
                                int(tTile::R[v1]*s1),
                                int(tTile::G[v1]*s1),
                                int(tTile::B[v1]*s1),
                                tTile::A[v1])
                            );

                    Draw(x+1, y, olc::Pixel(
                                int(tTile::R[v2]*s2),
                                int(tTile::G[v2]*s2),
                                int(tTile::B[v2]*s2),
                                tTile::A[v2])
                            );
                    Draw(x+2, y, olc::Pixel(
                                int(tTile::R[v3]*s3),
                                int(tTile::G[v3]*s3),
                                int(tTile::B[v3]*s3),
                                tTile::A[v3])
                            );
                    Draw(x+3, y, olc::Pixel(
                                int(tTile::R[v4]*s4),
                                int(tTile::G[v4]*s4),
                                int(tTile::B[v4]*s4),
                                tTile::A[v4])
                            );
                }
            }
        }
        DrawChunkGrid();
        SetPixelMode(olc::Pixel::NORMAL);
    }

    bool PlayerVsWorld()
    {
        bool colliding = false;
        int f = player.animations[player.anim][player.frame];
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                int index = y*8+x;
                if (player.image[f][index] > 0)
                {
                    int _x = x+int(width/2)-4;
                    int _y = y+int(height/2)-7;
                    if ( tTool::IsColliding((player.x+player.vx)+(x-4), (player.y+player.vy)+(y-7)) )
                    {
                        Draw(_x, _y, olc::RED);
                        colliding = true;
                    }
                }
            }
        }
        return colliding;
    }

    void DrawPlayer()
    {
        int r = 0;
        int g = 0;
        int b = 0;
        switch (player.status)
        {
            case player.FINE :     {r=255; g=255; b=255;} break;
            case player.HURT :     {r=255; g=128; b=0  ;} break;
            case player.BURN :     {r=255; g=0  ; b=0  ;} break;
            case player.COLD :     {r=128; g=128; b=255;} break;
            case player.STUN :     {r=255; g=255; b=0  ;} break;
            case player.TRIP :     {r=0;   g=255; b=255;} break;
            case player.POISON :   {r=0;   g=255; b=0  ;} break;
            case player.CONFUSED : {r=128; g=128; b=128;} break;
        }
        int f = player.animations[player.anim][player.frame];
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                int index = y*8+x;
                if (player.image[f][index] > 0)
                {
                    int v = player.image[f][index];
                    int R = std::min((((v*32)+r)/2), 255);
                    int G = std::min((((v*32)+g)/2), 255);
                    int B = std::min((((v*32)+b)/2), 255);
                    int _x = x+int(width/2)-4;
                    int _y = y+int(height/2)-7;
                    Draw(_x, _y, olc::Pixel(R, G, B));
                    if ( tTool::IsColliding((player.x+player.vx)+(x-4), (player.y+player.vy)+(y-7)) ) { Draw(_x+player.vx, _y+player.vy, olc::YELLOW); }
                    if ( tTool::IsColliding(player.x+(x-4), player.y+(y-7)) ) { Draw(_x, _y, olc::RED); }
                }
            }
        }
    }

    void DrawParticles(float delta)
    {
        for (int p = 0; p < (particles.size()); p++)
        {
            float x = particles[p].x;
            float y = particles[p].y;
            float vx = particles[p].vx;
            float vy = particles[p].vy;

            particles[p].Move(vx, vy, delta, tTool::IsColliding(int(x+vx), int(y+vy)));
            if ( particles[p].effect.destroys && tTool::IsColliding(int(x+(vx*1.5)), int(y+(vy*1.5))) )
            {
                tCell::matrix[int(y+(vy*1.5))*tCell::width+int(x+(vx*1.5))] = tTile::AIR;
            }
            if ( particles[p].effect.mines && tTool::IsColliding(int(x+(vx*1.5)), int(y+(vy*1.5))) )
            {
                player.inventory.AddItem(tCell::matrix[int(y+(vy*1.5))*tCell::width+int(x+(vx*1.5))], 1);
                tCell::matrix[int(y+(vy*1.5))*tCell::width+int(x+(vx*1.5))] = tTile::AIR;
            }
            if (particles[p].duration > 0.0)
            {
                particles[p].duration -= delta;
                Draw(x-(player.x-(width/2)), y-(player.y-(height/2)), olc::Pixel(particles[p].r, particles[p].g, particles[p].b, particles[p].a));
            }
            else
            {
                particles.erase(particles.begin()+p);
            }
        }
    }

    void DrawHUD()
    {
        float font = 0.25;

        int lookindex = (player.y-(height/2)+GetMouseY())*tCell::width+(player.x-(width/2)+GetMouseX());

        std::string health = std::to_string(player.hp)+"/"+std::to_string(player.HP);
        std::string lookingat = "Air";
        std::string selectedtile = tTile::NAME[selected_tile];
        std::string selectedcount = "";
        std::string collision_at = std::to_string(tTool::Collision((player.x-(width/2)+GetMouseX()), (player.y-(height/2)+GetMouseY())));

        if ( ( (lookindex < tCell::width*tCell::height) && lookindex > 0) && (tCell::matrix[lookindex] < tTile::total_tiles) )
        {
            lookingat = tTile::NAME[tCell::matrix[lookindex]];
        }
        if (player.inventory.HasItem(selected_tile))
        {
            selectedcount = std::to_string(player.inventory.data[selected_tile]);
        }

        ProgressBar(4, 2, player.hp, player.HP, 32, 255, 0, 0, 64, 0, 0);
        ProgressBar(4, 4, player.jp, player.JP, 32, 0, 255, 0, 0, 64, 0);
        ProgressBar(4, 6, player.bp, player.BP, 32, 0, 0, 255, 0, 0, 64);
        DrawStringDecal({ 4,8  }, "Looking At: " + lookingat, text_color, { font, font });
        //DrawStringDecal({ 4,12 }, "Selected Tile: " + selectedtile + " " + selectedcount, text_color, { font, font });
        DrawStringDecal({ 4,12 }, "Collision: " + collision_at, text_color, { font, font });
        DrawStringDecal({ 4,16 }, "Day: " + std::to_string(sky.day), text_color, { font, font });
        DrawStringDecal({ 4,20 }, "Year: " + std::to_string(sky.year), text_color, { font, font });
        //
        int hb_size = icon.size+1;
        int hb_offset = (width/2) - hb_size*4.5;
        std::string selected_item = "";
        if (player.hotbar[selected_hotbar][0] == itWAND) { selected_item = "Wand"; }
        if (player.hotbar[selected_hotbar][0] == itTILE) { selected_item = tTile::NAME[player.hotbar[selected_hotbar][1]]; }
        float select_x = (width/2)-(selected_item.size());
        DrawStringDecal({ select_x,15 }, selected_item, text_color, { 0.25, 0.25 });
        SetPixelMode(olc::Pixel::ALPHA);
        for (int i = 0; i < 9; i++)
        {
            int x = i*hb_size+hb_offset;
            DrawRect(x, 2, hb_size, hb_size, hud_color);
            
            if (player.hotbar[i][0] == itWAND)
            {
                int tile_value = player.hotbar[i][1];
                float R = float(tTile::R[tile_value]);
                float G = float(tTile::G[tile_value]);
                float B = float(tTile::B[tile_value]);
                for (int iy = 0; iy < icon.size; iy++)
                {
                    for (int ix = 0; ix < icon.size; ix++)
                    {
                        int index_value = icon.wand[iy*icon.size+ix];
                        float v = (0.25*float(index_value));
                        if (index_value > 0) Draw(ix+x+1, iy+3, olc::Pixel(int(R*v), int(G*v), int(B*v)));
                    }
                }
            }
            if (player.hotbar[i][0] == itTILE)
            {
                int tile_value = player.hotbar[i][1];
                int tile_type = tTool::GetType(tile_value);
                DrawIcon(x+1, 3, tile_type, tile_value);
            }
        }
        SetPixelMode(olc::Pixel::NORMAL);
        DrawRect(selected_hotbar*hb_size+hb_offset, 2, hb_size, hb_size, hud_select_color);
    }

    void DrawTitle()
    {
        Clear(olc::BLACK);

        float Tx = (width/2)-((sAppName.size()*16)/2);
        float Ty = (height*0.25);

        float Nx = (width/2)-50;
        float Lx = (width/2)+4;
        float By = (height*0.75);

        DrawStringDecal({ Tx,Ty }, sAppName, text_color, { 2.0, 2.0 });
        
        Button bNew = Button();
        bNew.Setup(Nx, By, 48, 16, 1.0, "New");
        Button bLoad = Button();
        bLoad.Setup(Lx, By, 48, 16, 1.0, "Load");

        DrawStringDecal({ bNew.TextX(),bNew.TextY() }, bNew.text, text_color, { 1.0, 1.0 });
        DrawRect(bNew.x, bNew.y, bNew.width, bNew.height, button_color);
        DrawStringDecal({ bLoad.TextX(),bLoad.TextY() }, bLoad.text, text_color, { 1.0, 1.0 });
        DrawRect(bLoad.x, bLoad.y, bLoad.width, bLoad.height, button_color);

        if (bNew.IsColliding(GetMouseX(), GetMouseY()))
        {
            DrawRect(bNew.x, bNew.y, bNew.width, bNew.height, select_color);
            if (GetMouse(0).bReleased)
            {
                Clear(olc::BLACK);
                game_state = CUSTOM;
                player.Setup();
            }
        }
        if (bLoad.IsColliding(GetMouseX(), GetMouseY()))
        {
            DrawRect(bLoad.x, bLoad.y, bLoad.width, bLoad.height, select_color);
            if (GetMouse(0).bReleased)
            {
                Clear(olc::BLACK);
                LoadPlayerData();
                //LoadWorldData();
                game_state = PLAYING;
            }
        }
    }

    void DrawCustom()
    {
        //Clear(olc::BLACK);
        bool can_draw = false;
        std::string info_text = "Hover Over A Button To See Details";
        std::string dtls_text = "";

        // Buttons
        Button bsave = Button();
        bsave.Setup(105, 37, 32, 8, 0.25, "Save");
        Button bload = Button();
        bload.Setup(105, 45, 32, 8, 0.25, "Load");

        Button bclear = Button();
        bclear.Setup(105, 57, 32, 8, 0.25, "Clear");
        Button bconfig = Button();
        bconfig.Setup(105, 65, 32, 8, 0.25, "Preset");
        Button brandom = Button();
        brandom.Setup(105, 73, 32, 8, 0.25, "Random");
        
        Button bpreview = Button();
        bpreview.Setup(105, 86, 32, 8, 0.25, "Preview");
        Button bgenerate = Button();
        bgenerate.Setup(105, 94, 32, 8, 0.25, "Generate");

        Button bminusgs = Button();
        bminusgs.Setup(183, 2, 70, 4, 0.25, "-");
        Button bplusgs = Button();
        bplusgs.Setup(183, 88, 70, 4, 0.25, "+");

        Button bcopy = Button();
        bcopy.Setup(183, 94, 35, 8, 0.25, "Copy");
        Button bpaste = Button();
        bpaste.Setup(218, 94, 35, 8, 0.25, "Paste");

        Button bsave0 = Button();
        bsave0.Setup(141, 7, 38, 8, 0.25, "Save 0");
        Button bsave1 = Button();
        bsave1.Setup(141, 15, 38, 8, 0.25, "Save 1");
        Button bsave2 = Button();
        bsave2.Setup(141, 23, 38, 8, 0.25, "Save 2");
        Button bsave3 = Button();
        bsave3.Setup(141, 31, 38, 8, 0.25, "Save 3");
        Button bsave4 = Button();
        bsave4.Setup(141, 39, 38, 8, 0.25, "Save 4");
        Button bsave5 = Button();
        bsave5.Setup(141, 47, 38, 8, 0.25, "Save 5");
        Button bsave6 = Button();
        bsave6.Setup(141, 55, 38, 8, 0.25, "Save 6");

        Button btile = Button();
        btile.Setup(141, 70, 18, 8, 0.25, "Tile");
        Button bmode = Button();
        bmode.Setup(141, 78, 18, 8, 0.25, "Mode");
        Button bdense = Button();
        bdense.Setup(141, 86, 18, 8, 0.25, "Density");
        Button biter = Button();
        biter.Setup(141, 94, 18, 8, 0.25, "Repeat");

        Button bminx = Button();
        bminx.Setup(162, 70, 18, 8, 0.25, "Min X");
        Button bmaxx = Button();
        bmaxx.Setup(162, 78, 18, 8, 0.25, "Max X");
        Button bminy = Button();
        bminy.Setup(162, 86, 18, 8, 0.25, "Min Y");
        Button bmaxy = Button();
        bmaxy.Setup(162, 94, 18, 8, 0.25, "Max Y");

        Button bprobn = Button();
        bprobn.Setup(117, 6, 8, 8, 0.25, "N");
        Button bprobs = Button();
        bprobs.Setup(117, 22, 8, 8, 0.25, "S");
        Button bprobe = Button();
        bprobe.Setup(125, 14, 8, 8, 0.25, "E");
        Button bprobw = Button();
        bprobw.Setup(109, 14, 8, 8, 0.25, "W");

        DrawRect(2, 2, 100, 100, border_color);  // Preview Box
        DrawRect(183, 2, 70, 90, border_color);  // Generation Steps Box
        DrawRect(2, 105, 251, 36, border_color);  // Information Box
        DrawRect(105, 2, 32, 32, border_color);  // Neighbors Box

        DrawRect(bsave.x, bsave.y, bsave.width, bsave.height, button_color);
        DrawStringDecal({ bsave.TextX(),bsave.TextY() }, bsave.text, text_color, { bsave.font, bsave.font });
        DrawRect(bload.x, bload.y, bload.width, bload.height, button_color);
        DrawStringDecal({ bload.TextX(),bload.TextY() }, bload.text, text_color, { bload.font, bload.font });
        
        DrawRect(bcopy.x, bcopy.y, bcopy.width, bcopy.height, button_color);
        DrawStringDecal({ bcopy.TextX(),bcopy.TextY() }, bcopy.text, text_color, { bcopy.font, bcopy.font });
        DrawRect(bpaste.x, bpaste.y, bpaste.width, bpaste.height, button_color);
        DrawStringDecal({ bpaste.TextX(),bpaste.TextY() }, bpaste.text, text_color, { bpaste.font, bpaste.font });
        
        DrawRect(bclear.x, bclear.y, bclear.width, bclear.height, button_color);
        DrawStringDecal({ bclear.TextX(),bclear.TextY() }, bclear.text, text_color, { bclear.font, bclear.font });
        DrawRect(bconfig.x, bconfig.y, bconfig.width, bconfig.height, button_color);
        DrawStringDecal({ bconfig.TextX(),bconfig.TextY() }, bconfig.text, text_color, { bconfig.font, bconfig.font });
        DrawRect(brandom.x, brandom.y, brandom.width, brandom.height, button_color);
        DrawStringDecal({ brandom.TextX(),brandom.TextY() }, brandom.text, text_color, { brandom.font, brandom.font });

        DrawRect(bpreview.x, bpreview.y, bpreview.width, bpreview.height, button_color);
        DrawStringDecal({ bpreview.TextX(),bpreview.TextY() }, bpreview.text, text_color, { bpreview.font, bpreview.font });
        DrawRect(bgenerate.x, bgenerate.y, bgenerate.width, bgenerate.height, button_color);
        DrawStringDecal({ bgenerate.TextX(),bgenerate.TextY() }, bgenerate.text, text_color, { bgenerate.font, bgenerate.font });

        DrawRect(bminusgs.x, bminusgs.y, bminusgs.width, bminusgs.height, button_color);
        DrawStringDecal({ bminusgs.TextX(),bminusgs.TextY() }, bminusgs.text, text_color, { btile.font, bminusgs.font });
        DrawRect(bplusgs.x, bplusgs.y, bplusgs.width, bplusgs.height, button_color);
        DrawStringDecal({ bplusgs.TextX(),bplusgs.TextY() }, bplusgs.text, text_color, { bplusgs.font, bplusgs.font });

        DrawRect(bsave0.x, bsave0.y, bsave0.width, bsave0.height, button_color);
        DrawStringDecal({ bsave0.TextX(),bsave0.TextY() }, bsave0.text, text_color, { bsave0.font, bsave0.font });
        DrawRect(bsave1.x, bsave1.y, bsave1.width, bsave1.height, button_color);
        DrawStringDecal({ bsave1.TextX(),bsave1.TextY() }, bsave1.text, text_color, { bsave1.font, bsave1.font });
        DrawRect(bsave2.x, bsave2.y, bsave2.width, bsave2.height, button_color);
        DrawStringDecal({ bsave2.TextX(),bsave2.TextY() }, bsave2.text, text_color, { bsave2.font, bsave2.font });
        DrawRect(bsave3.x, bsave3.y, bsave3.width, bsave3.height, button_color);
        DrawStringDecal({ bsave3.TextX(),bsave3.TextY() }, bsave3.text, text_color, { bsave3.font, bsave3.font });
        DrawRect(bsave4.x, bsave4.y, bsave4.width, bsave4.height, button_color);
        DrawStringDecal({ bsave4.TextX(),bsave4.TextY() }, bsave4.text, text_color, { bsave4.font, bsave4.font });
        DrawRect(bsave5.x, bsave5.y, bsave5.width, bsave5.height, button_color);
        DrawStringDecal({ bsave5.TextX(),bsave5.TextY() }, bsave5.text, text_color, { bsave5.font, bsave5.font });
        DrawRect(bsave6.x, bsave6.y, bsave6.width, bsave6.height, button_color);
        DrawStringDecal({ bsave6.TextX(),bsave6.TextY() }, bsave6.text, text_color, { bsave6.font, bsave6.font });

        DrawRect(btile.x, btile.y, btile.width, btile.height, button_color);
        DrawStringDecal({ btile.TextX(),btile.TextY() }, btile.text, text_color, { btile.font, btile.font });
        DrawRect(bmode.x, bmode.y, bmode.width, bmode.height, button_color);
        DrawStringDecal({ bmode.TextX(),bmode.TextY() }, bmode.text, text_color, { bmode.font, bmode.font });
        DrawRect(bdense.x, bdense.y, bdense.width, bdense.height, button_color);
        DrawStringDecal({ bdense.TextX(),bdense.TextY() }, bdense.text, text_color, { bdense.font, bdense.font });
        DrawRect(biter.x, biter.y, biter.width, biter.height, button_color);
        DrawStringDecal({ biter.TextX(),biter.TextY() }, biter.text, text_color, { biter.font, biter.font });

        DrawRect(bminx.x, bminx.y, bminx.width, bminx.height, button_color);
        DrawStringDecal({ bminx.TextX(),bminx.TextY() }, bminx.text, text_color, { bminx.font, bminx.font });
        DrawRect(bmaxx.x, bmaxx.y, bmaxx.width, bmaxx.height, button_color);
        DrawStringDecal({ bmaxx.TextX(),bmaxx.TextY() }, bmaxx.text, text_color, { bmaxx.font, bmaxx.font });
        DrawRect(bminy.x, bminy.y, bminy.width, bminy.height, button_color);
        DrawStringDecal({ bminy.TextX(),bminy.TextY() }, bminy.text, text_color, { bminy.font, bminy.font });
        DrawRect(bmaxy.x, bmaxy.y, bmaxy.width, bmaxy.height, button_color);
        DrawStringDecal({ bmaxy.TextX(),bmaxy.TextY() }, bmaxy.text, text_color, { bmaxy.font, bmaxy.font });

        DrawRect(bprobn.x, bprobn.y, bprobn.width, bprobn.height, button_color);
        DrawStringDecal({ bprobn.TextX(),bprobn.TextY() }, bprobn.text, text_color, { bprobn.font, bprobn.font });
        DrawRect(bprobs.x, bprobs.y, bprobs.width, bprobs.height, button_color);
        DrawStringDecal({ bprobs.TextX(),bprobs.TextY() }, bprobs.text, text_color, { bprobs.font, bprobs.font });
        DrawRect(bprobe.x, bprobe.y, bprobe.width, bprobe.height, button_color);
        DrawStringDecal({ bprobe.TextX(),bprobe.TextY() }, bprobe.text, text_color, { bprobe.font, bprobe.font });
        DrawRect(bprobw.x, bprobw.y, bprobw.width, bprobw.height, button_color);
        DrawStringDecal({ bprobw.TextX(),bprobw.TextY() }, bprobw.text, text_color, { bprobw.font, bprobw.font });

        // Numeric Input
        if (GetKey(olc::Key::K0).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"0";
            input_value = std::stoi(new_value);
        }
        if (GetKey(olc::Key::K1).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"1";
            input_value = std::stoi(new_value);
        }
        if (GetKey(olc::Key::K2).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"2";
            input_value = std::stoi(new_value);
        }
        if (GetKey(olc::Key::K3).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"3";
            input_value = std::stoi(new_value);
        }
        if (GetKey(olc::Key::K4).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"4";
            input_value = std::stoi(new_value);
        }
        if (GetKey(olc::Key::K5).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"5";
            input_value = std::stoi(new_value);
        }
        if (GetKey(olc::Key::K6).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"6";
            input_value = std::stoi(new_value);
        }
        if (GetKey(olc::Key::K7).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"7";
            input_value = std::stoi(new_value);
        }
        if (GetKey(olc::Key::K8).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"8";
            input_value = std::stoi(new_value);
        }
        if (GetKey(olc::Key::K9).bPressed)
        {
            std::string new_value = std::to_string(input_value)+"9";
            input_value = std::stoi(new_value);
        }

        if (GetKey(olc::Key::ENTER).bPressed)
        {
            switch (new_world::selected_param)
            {
                case new_world::pTILE : if (input_value > tTile::total_tiles-1) input_value = tTile::total_tiles-1; break;
                case new_world::pMODE : if (input_value > 3) input_value = 3; break;
                case new_world::pITER : if (input_value > 64) input_value = 64; break;
                default : if (input_value > 100) input_value = 100; break;
            }
            new_world::generation_param[new_world::selected_step][new_world::selected_param] = input_value;
            input_value = 0;
        }
        // Update Parameters
        if (GetKey(olc::Key::S).bPressed)
        {
            if (new_world::selected_step < new_world::generation_steps-2) new_world::selected_step++;
        }
        if (GetKey(olc::Key::W).bPressed)
        {
            if (new_world::selected_step > 0) new_world::selected_step--;
        }

        if (GetKey(olc::Key::A).bPressed)
        {
            if (new_world::generation_param[new_world::selected_step][new_world::selected_param] > 0)
            {
                new_world::generation_param[new_world::selected_step][new_world::selected_param]--;
            }
        }
        if (GetKey(olc::Key::D).bPressed)
        {
            switch (new_world::selected_param)
            {
                case new_world::pTILE :
                {
                    if (new_world::generation_param[new_world::selected_step][new_world::selected_param] < tTile::total_tiles-1)
                    { new_world::generation_param[new_world::selected_step][new_world::selected_param]++; }
                }
                break;
                case  new_world::pMODE :
                {
                    if (new_world::generation_param[new_world::selected_step][new_world::selected_param] < new_world::total_modes-1)
                    { new_world::generation_param[new_world::selected_step][new_world::selected_param]++;
                    }
                }
                break;
                default :
                {
                    if (new_world::generation_param[new_world::selected_step][new_world::selected_param] < 100)
                    { new_world::generation_param[new_world::selected_step][new_world::selected_param]++; }
                }
                break;
            }
        }
        // Step Value
        if (bminusgs.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Removes The Selected Generation Step From The List";
            //dtls_text = "()";
            DrawRect(bminusgs.x, bminusgs.y, bminusgs.width, bminusgs.height, select_color);
            if (GetMouse(0).bReleased && new_world::generation_steps > 1)
            {
                new_world::generation_steps--;
                for (int i = new_world::selected_step; i < new_world::generation_steps; i++)
                {
                    for (int p = 0; p < new_world::total_parameters; p++)
                    {
                        new_world::generation_param[i][p] = new_world::generation_param[i+1][p];
                    }
                }
                if (new_world::selected_step > 0) new_world::selected_step--;
            }
        }
        if (bplusgs.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Inserts A Generation Step Into The List";
            //dtls_text = "()";
            DrawRect(bplusgs.x, bplusgs.y, bplusgs.width, bplusgs.height, select_color);
            if (GetMouse(0).bReleased && new_world::generation_steps < new_world::maximum_generation_steps)
            {
                new_world::generation_steps++;
                for (int i = new_world::generation_steps-1; i > new_world::selected_step+1; i--)
                {
                    for (int p = 0; p < new_world::total_parameters; p++)
                    {
                        new_world::generation_param[i-1][p] = new_world::generation_param[i-2][p];
                    }
                }
                for (int p = 0; p < new_world::total_parameters; p++)
                {
                    new_world::generation_param[new_world::selected_step][p] = 0;
                }
                if (new_world::selected_step > 0) new_world::selected_step--;
            }
        }
        // Tile Value
        if (btile.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Material To add To World";
            //dtls_text = "()";
            DrawRect(btile.x, btile.y, btile.width, btile.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pTILE;
        }
        // Density Value
        if (bdense.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Probability A Material Will Spawn Per Cell";
            dtls_text = "(Add Layer, Seed Material)";
            DrawRect(bdense.x, bdense.y, bdense.width, bdense.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pDENSE;
        }
        if (biter.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "How Many Times to Repeat Current Step";
            //dtls_text = "()";
            DrawRect(biter.x, biter.y, biter.width, biter.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pITER;
        }
        // X Values
        if (bminx.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Minimum Width Range Of Effect";
            dtls_text = "(0-100 %)";
            DrawRect(bminx.x, bminx.y, bminx.width, bminx.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pMINX;
        }
        if (bmaxx.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Maximum Width Range Of Effect";
            dtls_text = "(0-100 %)";
            DrawRect(bmaxx.x, bmaxx.y, bmaxx.width, bmaxx.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pMAXX;
        }
        // Y values
        if (bminy.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Minimum Height Range Of Effect";
            dtls_text = "(0-100 %)";
            DrawRect(bminy.x, bminy.y, bminy.width, bminy.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pMINY;
        }
        if (bmaxy.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Maximum Height Range Of Effect";
            dtls_text = "(0-100 %)";
            DrawRect(bmaxy.x, bmaxy.y, bmaxy.width, bmaxy.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pMAXY;
        }
        // Neighbor Values
        if (bprobn.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Probability That A Northern Neighbor Will Spawn";
            //dtls_text = "()";
            DrawRect(bprobn.x, bprobn.y, bprobn.width, bprobn.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pPROBN;
        }
        if (bprobs.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Probability That A Southern Neighbor Will Spawn";
            //dtls_text = "()";
            DrawRect(bprobs.x, bprobs.y, bprobs.width, bprobs.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pPROBS;
        }
        if (bprobe.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Probability That An Eastern Neighbor Will Spawn";
            //dtls_text = "()";
            DrawRect(bprobe.x, bprobe.y, bprobe.width, bprobe.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pPROBE;
        }
        if (bprobw.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Probability That A Western Neighbor Will Spawn";
            //dtls_text = "()";
            DrawRect(bprobw.x, bprobw.y, bprobw.width, bprobw.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pPROBW;
        }
        // Mode Value
        if (bmode.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Changes Generation Mode";
            //dtls_text = "()";
            DrawRect(bmode.x, bmode.y, bmode.width, bmode.height, select_color);
            if (GetMouse(0).bReleased) new_world::selected_param = new_world::pMODE;
        }

        // Clear Values
        if (bclear.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Clears All Generation Data";
            DrawRect(bclear.x, bclear.y, bclear.width, bclear.height, select_color);
            if (GetMouse(0).bReleased)
            {
                new_world::ClearData();
            }
        }
        // Auto Configure
        if (bconfig.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Standard World Generation";
            //dtls_text = "()";
            DrawRect(bconfig.x, bconfig.y, bconfig.width, bconfig.height, select_color);
            if (GetMouse(0).bReleased)
            {
                new_world::PresetData();
            }
        }
        // Randomize Seed
        if (brandom.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Randomizes Game Seed";
            DrawRect(brandom.x, brandom.y, brandom.width, brandom.height, select_color);
            if (GetMouse(0).bReleased)
            {
                core::seed = rand() % 9999999999;
                srand(core::seed);
                new_world::ClearMatrix();
                new_world::InitializeMatrix(100, 100);
                for (int i = 0; i < new_world::generation_steps; i++)
                {
                    new_world::GeneratePreview();
                }
                new_world::generation_step = 1;
                can_draw = true;
            }
        }
        // Save
        if (bsave.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Saves Generation Data";
            DrawRect(bsave.x, bsave.y, bsave.width, bsave.height, select_color);
            if (GetMouse(0).bReleased)
            {
                std::string data_dir = std::to_string(save_slot) + ".txt";
                SaveGenerationData(data_dir);
            }
        }
        // Load
        if (bload.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Loads Generation Data";
            DrawRect(bload.x, bload.y, bload.width, bload.height, select_color);
            if (GetMouse(0).bReleased)
            {
                std::string data_dir = std::to_string(save_slot) + ".txt";
                LoadGenerationData(data_dir);
            }
        }
        // Copy
        if (bcopy.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Copies Selected Generation Step";
            DrawRect(bcopy.x, bcopy.y, bcopy.width, bcopy.height, select_color);
            if (GetMouse(0).bReleased)
            {
                for (int p = 0; p < new_world::total_parameters; p++)
                {
                    new_world::clipboard_param[p] = new_world::generation_param[new_world::selected_step][p];
                }
            }
        }
        // Paste
        if (bpaste.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Pastes Selected Generation Step";
            DrawRect(bpaste.x, bpaste.y, bpaste.width, bpaste.height, select_color);
            if (GetMouse(0).bReleased)
            {
                new_world::generation_steps++;
                for (int i = new_world::generation_steps-1; i > new_world::selected_step; i--)
                {
                    for (int p = 0; p < new_world::total_parameters; p++)
                    {
                        new_world::generation_param[i-1][p] = new_world::generation_param[i-2][p];
                    }
                }
                for (int p = 0; p < new_world::total_parameters; p++)
                {
                    new_world::generation_param[new_world::selected_step][p] = new_world::clipboard_param[p];
                }
                if (new_world::selected_step > 0) new_world::selected_step--;
            }
        }
        // Generate World
        if (bgenerate.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Generates World And Starts Game";
            DrawRect(bgenerate.x, bgenerate.y, bgenerate.width, bgenerate.height, select_color);
            if (GetMouse(0).bReleased)
            {
                bool is_data_valid = false;
                for (int i = 0; i < new_world::generation_steps; i++)
                {
                    if (new_world::generation_param[i][0] != tTile::AIR) is_data_valid = true;
                }
                if (!is_data_valid) new_world::PresetData();
                new_world::InitializeMatrix(world_width, world_height);
                srand(core::seed);
                game_state = LOADING;
            }
        }
        // Generate Preview
        if (bpreview.IsColliding(GetMouseX(), GetMouseY()))
        {
            info_text = "Updates The Preview Box";
            DrawRect(bpreview.x, bpreview.y, bpreview.width, bpreview.height, select_color);
            if (GetMouse(0).bReleased)
            {
                srand(core::seed);
                new_world::ClearMatrix();
                new_world::InitializeMatrix(100, 100);
                for (int i = 0; i < new_world::generation_steps; i++)
                {
                    new_world::GeneratePreview();
                }
                new_world::generation_step = 1;
                can_draw = true;
            }
        }
        // Draw Preview
        if (can_draw)
        {
            FillRect(3, 3, 99, 99, olc::Pixel(128, 128, 255));
            SetPixelMode(olc::Pixel::ALPHA);
            for (int y = 0; y < 100; y++)
            {
                for (int x = 0; x < 100; x++)
                {
                    int v = tCell::matrix[y*tCell::width+x];
                    Draw(x+3, y+3, olc::Pixel(
                        tTile::R[v],
                        tTile::G[v],
                        tTile::B[v],
                        tTile::A[v])
                        );
                }
            }
            SetPixelMode(olc::Pixel::NORMAL);
        }
        // Draw Generation Steps
        int list_height = 0;
        int stop_list = std::min(new_world::selected_step+9, new_world::generation_steps);
        int start_list = std::max(stop_list-9, 0);
        for (int i = start_list; i < stop_list; i++)
        {
            std::string vlue_text;
            std::string mode_text;
            std::string tile_text;
            try { if (new_world::generation_param[i][new_world::selected_param] < new_world::total_modes) mode_text = new_world::modes[new_world::generation_param[i][new_world::selected_param]]; }
            catch (std::bad_alloc & ba) { mode_text = "Error"; }
            try { tile_text = tTile::NAME[new_world::generation_param[i][new_world::selected_param]]; }
            catch (std::bad_alloc & ba) { tile_text = "Error"; }
            try { vlue_text = std::to_string(new_world::generation_param[i][new_world::selected_param]); }
            catch (std::bad_alloc & ba) { vlue_text = "Error"; }

            if (i == new_world::selected_step)
            {
                tile_text = ">" + tile_text;
                switch (new_world::selected_param)
                {
                    case new_world::pTILE : DrawStringDecal({ float(186),float((list_height*9)+10) }, tile_text, text_color, { 0.5, 0.5 }); break;
                    case new_world::pMODE : DrawStringDecal({ float(186),float((list_height*9)+10) }, mode_text, text_color, { 0.5, 0.5 }); break;
                    default : DrawStringDecal({ float(186),float((list_height*9)+10) }, vlue_text, text_color, { 0.5, 0.5 }); break;
                }
            }
            else
            {
                switch (new_world::selected_param)
                {
                    case new_world::pTILE : DrawStringDecal({ float(186),float((list_height*9)+10) }, tile_text, button_color, { 0.5, 0.5 }); break;
                    case new_world::pMODE : DrawStringDecal({ float(186),float((list_height*9)+10) }, mode_text, button_color, { 0.5, 0.5 }); break;
                    default : DrawStringDecal({ float(186),float((list_height*9)+10) }, vlue_text, button_color, { 0.5, 0.5 }); break;
                }
            }
            list_height++;
        }
        // Draw Info
        DrawStringDecal({ 5,109 }, info_text, text_color, { 0.5, 0.5 });
        DrawStringDecal({ 5,115 }, dtls_text, text_color, { 0.5, 0.5 });

    }

    void DrawLoading()
    {
        Clear(olc::BLACK);
        
        std::string message = "Generating World, Please Wait.";
        
        if (loading)
        {
            message = new_world::GenerateWorld();
            
            if (new_world::generation_step > new_world::generation_steps)
            {
                sky.GenerateSky(width, height, core::seed);
                player.x = int(tCell::width/2);
                player.y = player.height+2;
                while (!tTool::IsColliding(player.x, player.y+1)) player.Move(0, 1);
                loading = false;
                game_state = PLAYING;
            }
        }
        if (!loading) loading = true;

        int prog_x = (width/2)-(width/4);
        int prog_y = (height/2)+4;

        float msg_x = width/2-((message.size()/2)*4);
        float msg_y = (height/2)-4;

        DrawStringDecal({ msg_x, msg_y }, message, text_color, { 0.5, 0.5 });
        ProgressBar(prog_x, prog_y, new_world::generation_step-1, new_world::generation_steps, width/2);

    }

    void GamePaused()
    {
        if (GetKey(olc::Key::ESCAPE).bPressed) game_state = PLAYING;
        if (GetKey(olc::Key::TAB).bPressed) game_state = INVENTORY;
        
        if (player.state == player.DEAD) return;

        if (GetMouse(0).bHeld)
        {
            if (player.hotbar[selected_hotbar][0] == itNONE)
            {
            }
            if (player.hotbar[selected_hotbar][0] == itWAND)
            {
                if (player.wands[selected_wand].can_fire)
                {
                    player.wands[selected_wand].Cast();
                    Effect e = player.wands[selected_wand].effects[player.wands[selected_wand].current_effect];
                    SpawnParticle(float(GetMouseX()), float(GetMouseY()), e);
                }
            }
            int index = (GetMouseY()+(player.y-(height/2)))*tCell::width+(GetMouseX()+(player.x-(width/2)));
            int tile = tCell::matrix[index];
            int _tile = selected_tile;
            if (player.hotbar[selected_hotbar][0] == itTILE)
            {
                int index = (GetMouseY()+(player.y-(height/2)))*tCell::width+(GetMouseX()+(player.x-(width/2)));
                int tile = tCell::matrix[index];
                int _tile = player.hotbar[selected_hotbar][1];
                if (tile != tTile::MANTLE)
                {
                    if (_tile != tTile::AIR)
                    {
                        if (player.inventory.HasItem(_tile) || creative_mode)
                        {
                            int amnt = 1;
                            if (tile == tTile::AIR) amnt = 0;
                            player.inventory.UseItem(_tile, 1);
                            player.inventory.AddItem(tile, amnt);
                            tCell::matrix[index] = _tile;
                        }
                    }
                    else if (_tile == tTile::AIR)
                    {
                        if (tile != tTile::AIR) player.inventory.AddItem(tile, 1);
                        tCell::matrix[index] = _tile;
                    }
                }
            }
        }

        if (GetKey(olc::Key::SPACE).bPressed)
        {
            world.SettleTiles(player.x-(width), player.y-(height), width*2, height*2);
        }
        DrawSky();
        DrawTerrain();
        DrawPlayer();
        HotbarInput();
        DrawHUD();
    }

    void GameInventory()
    {
        if (GetKey(olc::Key::ESCAPE).bPressed) game_state = PAUSED;
        if (GetKey(olc::Key::TAB).bPressed) game_state = PLAYING;

        if (GetKey(olc::Key::Q).bPressed && selected_tile < tTile::total_tiles-1) selected_tile++;
        if (GetKey(olc::Key::E).bPressed && selected_tile > 0) selected_tile--;

        if (GetKey(olc::Key::I).bPressed) pause_state = psTILES;
        if (GetKey(olc::Key::W).bPressed) pause_state = psWANDS;
        
        if (pause_state == psWANDS) DrawWands();
        if (pause_state == psTILES) DrawInventory();

        HotbarInput();
        DrawHUD();
    }

    void GameLoop(float fElapsedTime)
    {
        if (player.state == player.DEAD)
        {
            if (GetKey(olc::Key::ESCAPE).bPressed) game_state = PAUSED;
            return; 
        }

        if (!tTool::IsColliding(player.x, player.y+1) && !tTool::IsColliding(player.x-1, player.y+1) && player.state != player.JUMP)
        {
            player.vy = 1;
            player.state = player.FALL;
        }
        if (tTool::IsColliding(player.x, player.y+1) || tTool::IsColliding(player.x-1, player.y+1))
        {
            player.state = player.IDLE;
        }

        if (GetKey(olc::Key::ESCAPE).bPressed) game_state = PAUSED;
        if (GetKey(olc::Key::TAB).bPressed) game_state = INVENTORY;
        //
        HotbarInput();
        
        // Stuff
        if (GetMouse(0).bHeld)
        {
            if (player.hotbar[selected_hotbar][0] == itNONE)
            {
            }
            if (player.hotbar[selected_hotbar][0] == itWAND)
            {
                if (player.wands[selected_wand].can_fire)
                {
                    player.wands[selected_wand].Cast();
                    Effect e = player.wands[selected_wand].effects[player.wands[selected_wand].current_effect];
                    SpawnParticle(float(GetMouseX()), float(GetMouseY()), e);
                }
            }
            int index = (GetMouseY()+(player.y-(height/2)))*tCell::width+(GetMouseX()+(player.x-(width/2)));
            int tile = tCell::matrix[index];
            int _tile = selected_tile;
            if (player.hotbar[selected_hotbar][0] == itTILE)
            {
                int index = (GetMouseY()+(player.y-(height/2)))*tCell::width+(GetMouseX()+(player.x-(width/2)));
                int tile = tCell::matrix[index];
                int _tile = player.hotbar[selected_hotbar][1];
                if (tile != tTile::MANTLE)
                {
                    if (_tile != tTile::AIR)
                    {
                        if (player.inventory.HasItem(_tile) || creative_mode)
                        {
                            int amnt = 1;
                            if (tile == tTile::AIR) amnt = 0;
                            player.inventory.UseItem(_tile, 1);
                            player.inventory.AddItem(tile, amnt);
                            tCell::matrix[index] = _tile;
                        }
                    }
                    else if (_tile == tTile::AIR)
                    {
                        if (tile != tTile::AIR) player.inventory.AddItem(tile, 1);
                        tCell::matrix[index] = _tile;
                    }
                }
            }
        }

        // Vertical Movement
        if (GetKey(olc::Key::W).bHeld)
        {
            if ((!tTool::IsColliding(player.x, player.y-player.height)) &&
                (player.jp > 0) &&
                (player.y > 0) )
            {
                player.jp--;
                player.vy = -1;
                player.state = player.JUMP;
            }
            else
            {
                player.vy = 1;
            }
        }

        if (GetKey(olc::Key::W).bReleased) { player.vy = 0; player.state = player.IDLE; }

        if (GetKey(olc::Key::S).bPressed)
        {
            int tile = tCell::matrix[(player.y+(player.height-1))*tCell::width+player.x];
            if (tile == tTile::PLANKS) { player.Move(0, 1); }
        }

        if (!tTool::IsColliding(player.x, player.y+1) && player.state != player.JUMP)
        { player.vy = 1; player.state = player.FALL; }

        // Horizontal Movement
        if (GetKey(olc::Key::A).bHeld && player.x > width/2)
        {
            if (player.state != player.FALL && player.state != player.JUMP) player.vy = 0;
            if (!tTool::IsColliding(player.x-2, player.y) ) { player.vx = -1; }
            else if (tTool::IsColliding(player.x-2, player.y) ||
                    tTool::IsColliding(player.x-2, player.y-1)
                    )
            { player.vx = -1; player.Move(0, -1); }
            if (!GetKey(olc::Key::W).bHeld && player.state != player.FALL) { player.state = player.WALK; }
            player.direction = -1;
        }
        if (GetKey(olc::Key::D).bHeld && player.x < tCell::width-(width/2))
        {
            if (player.state != player.FALL && player.state != player.JUMP) player.vy = 0;
            if (!tTool::IsColliding(player.x+1, player.y) ) { player.vx = 1; }
            else if (tTool::IsColliding(player.x+1, player.y) ||
                    tTool::IsColliding(player.x+1, player.y-1) )
            { player.vx = 1; player.Move(0, -1); }
            if (!GetKey(olc::Key::W).bHeld && player.state != player.FALL) { player.state = player.WALK; }
            player.direction = 1;
        }

        if (GetKey(olc::Key::A).bReleased) { player.vx = 0; }
        if (GetKey(olc::Key::D).bReleased) { player.vx = 0; }

        if (GetKey(olc::Key::Q).bPressed) { if (grid_subdivision > 1) grid_subdivision /= 2; }
        if (GetKey(olc::Key::E).bPressed) { if (grid_subdivision < 8) grid_subdivision *= 2; }
        if (GetKey(olc::Key::G).bPressed) { show_grid = !show_grid; }


        // Update World
        sky.Update(fElapsedTime);
        if (game_tick > tick_delay)
        {
            game_tick -= tick_delay;
            DrawSky();
            world.SettleTiles(player.x-(width), player.y-(height), width*2, height*2);
            DrawTerrain();
            DrawHUD();
        }

        // Update Player
        player.Update(fElapsedTime);
        if (player.hp < 1) player.state = player.DEAD;
        
        /*
        // Tile Effects
        switch (tCell::matrix[(player.y+1)*tCell::width+player.x])
        {
            case tTile::LAVA:
            {
                player.status = player.BURN;
            }
            break;
        }
        switch (tCell::matrix[(player.y-player.height)*tCell::width+player.x])
        {
            case tTile::AIR:
            {
                if (player.status == player.DROWN) player.status = player.FINE;
            }
            break;
            case tTile::LAVA:
            {
                player.status = player.BURN;
            }
            break;
        }
        */
        if (!PlayerVsWorld())
        {
            player.Move(player.vx, player.vy);
        }
        DrawPlayer();
        //player.UpdateWands(fElapsedTime);
        DrawParticles(fElapsedTime);
        //DrawHUD();

        // End Frame
        game_tick += fElapsedTime;
    }



	bool OnUserCreate() override
	{
        InstallGame();
        for (int i = 0; i < new_world::generation_steps; i++)
        {
            new_world::generation_param[i][new_world::pITER] = 1;
        }
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        switch (game_state)
        {
            case PLAYING : GameLoop(fElapsedTime); break;
            case PAUSED : GamePaused(); break;
            case INVENTORY : GameInventory(); break;
            case LOADING : DrawLoading(); break;
            case CUSTOM : DrawCustom(); break;
            case TITLE : DrawTitle(); break;
            case EXIT : {SavePlayerData(); SaveWorldData();running = false;} break;
        }
        return running;
	}
};
