class World
{
public:

    // Class Attributes //

    // World Dimensions

    int width;
    int height;

    // Terrain Tiles

    int total_tiles = 53;
    int total_parameters = 12;
    int total_modes = 4;

    // Procedural Generation
    int selected_step = 0;
    int selected_param = 0;
    int generation_step = 1;
    int generation_steps = 8;

    int generation_param[256][12];

    enum MODES
    {
        mADD,
        mSEED,
        mEXPAND,
        mDEPOSIT,
    };

    std::string modes[4] = {
        "Add Layer",
        "Seed Layer",
        "Expand Material",
        "Deposit Material",
    };

    enum PARAM
    {
        pTILE,
        pDENSE,
        pITER,
        pMINX,
        pMAXX,
        pMINY,
        pMAXY,
        pPROBN,
        pPROBS,
        pPROBE,
        pPROBW,
        pMODE
    };

    enum TYPES
    {
        GAS,
        FLUID,
        GRAIN,
        GEL,
        SOLID,
    };

    enum TILES
    {
        //
        AIR,
        STEAM,
        SMOKE,
        //
        WATER,
        BRINE,
        HONEY,
        BLOOD,
        LAVA,
        //
        SAND,
        SNOW,
        SLEET,
        SILT,
        GRAVEL,
        //
        ICE,
        MUD,
        DIRT,
        SOIL,
        CLAY,
        BONE,
        FOSSIL,
        SLATE,
        ASBESTOS,
        OBSIDIAN,
        STONE,
        GRANITE,
        LIMESTONE,
        SANDSTONE,
        GLASS,
        //
        WOOD,
        LEAVES,
        GRASS,
        MOSS,
        //
        PLATINUM,
        GOLD,
        SILVER,
        COPPER,
        LEAD,
        TIN,
        IRON,
        COBALT,
        NICKEL,
        TITANIUM,
        TUNGSTEN,
        //
        JADE,
        RUBY,
        AMBER,
        LAPIS,
        TOPAZ,
        DIAMOND,
        EMERALD,
        AMETHYST,
        SAPPHIRE,
        //
        MANTLE
    };

    std::string tiles[53] = {
        //
        "Air",
        "Steam",
        "Smoke",
        //
        "Water",
        "Brine",
        "Honey",
        "Blood",
        "Lava",
        //
        "Sand",
        "Snow",
        "Sleet",
        "Silt",
        "Gravel",
        //
        "Ice",
        "Mud",
        "Dirt",
        "Soil",
        "Clay",
        "Bone",
        "Fossil",
        "Slate",
        "Asbestos",
        "Obsidian",
        "Stone",
        "Granite",
        "Limestone",
        "Sandstone",
        "Glass",
        //
        "Wood",
        "Leaves",
        "Grass",
        "Moss",
        //
        "Platinum",
        "Gold",
        "Silver",
        "Copper",
        "Lead",
        "Tin",
        "Iron",
        "Cobalt",
        "Nickel",
        "Titanium",
        "Tungsten",
        //
        "Jade",
        "Ruby",
        "Amber",
        "Lapis",
        "Topaz",
        "Diamond",
        "Emerald",
        "Amethyst",
        "Sapphire",
        //
        "Mantle"
    };

    int tileset[53][2][4] = {
        // |Base Color        |     |Variation       |
        // Gases
        {  {200, 200, 230, 5  },    {1,   1,   25,  0}  },// Air
        {  {220, 220, 230, 32 },    {5,   5,   25,  0}  },// Steam
        {  {128, 128, 128, 64 },    {5,   5,   5,   0}  },// Smoke
        // Fluids
        {  {0,   0,   128, 128},    {1,   1,   25,  0}  },// Water
        {  {16,  16,  128, 128},    {1,   1,   25,  0}  },// Brine
        {  {230, 200, 0,   212},    {25,  10,  1,   0}  },// Honey
        {  {128, 0,   0,   255},    {25,  1,   1,   0}  },// Blood
        {  {254, 20,  0,   255},    {1,  180,  1,   0}  },// Lava
        // Granular Materials
        {  {230, 230, 128, 255},    {15,  15,  5,   0}  },// Sand
        {  {230, 230, 230, 255},    {1,   1,   25,  0}  },// Snow
        {  {200, 200, 200, 212},    {1,   1,   55,  0}  },// Sleet
        {  {130, 120, 140, 255},    {10,  10,  10,  0}  },// Silt
        {  {110, 105, 100, 255},    {10,  10,  10,  0}  },// Gravel
        // Solid Materials
        {  {180, 180, 200, 128},    {1,   1,   55,  0}  },// Ice
        {  {58,  32,  16,  255},    {8,   4,   2,   0}  },// Mud
        {  {80,  64,  32,  255},    {8,   4,   2,   0}  },// Dirt
        {  {24,  20,  16,  255},    {8,   4,   2,   0}  },// Soil
        {  {160, 80,  20,  255},    {8,   4,   1,   0}  },// Clay
        {  {240, 240, 200, 255},    {15,  15,  1,   0}  },// Bone
        {  {20,  15,  10,  255},    {10,  5,   1,   0}  },// Fossil
        {  {120, 100, 80,  255},    {25,  20,  10,  0}  },// Slate
        {  {64,  132, 148, 255},    {1,   15,  25,  0}  },// Asbestos
        {  {32,  16,  8,   255},    {15,  1,   1,   0}  },// Obsidian
        {  {64,  64,  64,  255},    {5,   5,   10,  0}  },// Stone
        {  {80,  80,  80,  255},    {5,   15,  25,  0}  },// Granite
        {  {128, 128, 128, 255},    {5,   5,   10,  0}  },// Limestone
        {  {200, 200, 100, 255},    {5,   5,   10,  0}  },// Sandstone
        {  {220, 220, 245,  64},    {5,   15,  10,  0}  },// Glass
        // Plant Materials
        {  {80,  64,  32,  255},    {25,  20,  10,  0}  },// Wood
        {  {40,   80, 0,   225},    {5,   20,  1,   0}  },// Leaves
        {  {0,   128, 0,   255},    {5,   20,  1,   0}  },// Grass
        {  {20,   80, 0,   255},    {5,   20,  1,   0}  },// Moss
        // Metals
        {  {190, 190, 230, 255},    {10,  10,  25,  0}  },// Platinum
        {  {245, 230, 0,   255},    {10,  5,   1,   0}  },// Gold
        {  {180, 180, 220, 255},    {10,  10,  15,  0}  },// Silver
        {  {128, 60,  0,   255},    {10,  5,   1,   0}  },// Copper
        {  {16,  32,  48,  255},    {2,   4,   8,   0}  },// Lead
        {  {180, 200, 100, 255},    {15,  15,  10,  0}  },// Tin
        {  {140, 100, 100, 255},    {15,  10,  10,  0}  },// Iron
        {  {80,  100, 140, 255},    {4,   8,   10,  0}  },// Cobalt
        {  {100, 100, 100, 255},    {4,   8,   10,  0}  },// Nickel
        {  {100, 110, 120, 255},    {6,   8,   12,  0}  },// Titanium
        {  {50,  55,  60,  255},    {6,   8,   12,  0}  },// Tungsten
        // Gemstones
        {  {0,   210, 20,  212},    {1,   25,  1,   0}  },// Jade
        {  {180, 0,   0,   160},    {25,  1,   1,   0}  },// Ruby
        {  {180, 140, 0,   192},    {25,  10,  1,   0}  },// Amber
        {  {0,   0,   200, 212},    {1,   25,  1,   0}  },// Lapis
        {  {230, 180, 0,   160},    {25,  10,  1,   0}  },// Topaz
        {  {250, 250, 250, 160},    {5,   5,   5,   0}  },// Diamond
        {  {0,   180, 90,  160},    {1,   25,  1,   0}  },// Emerald
        {  {150, 100, 200, 160},    {25,  1,   25,  0}  },// Amethyst
        {  {15,  80,  185, 160},    {1,   1,   25,  0}  },// Sapphire
        // Unbreakable
        {  {25,  20,  20,  255},    {25,  1,   1,   0}  },// Mantle
    };

    std::vector<short> matrix;
    std::vector<short> replace;



    // Matrix
    void ClearMatrix()
    {
        matrix.clear();
    }

    void InitializeMatrix(int w, int h)
    {
        width = w;
        height = h;
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                matrix.push_back(AIR);
                replace.push_back(AIR);
            }
        }
    }

    // Generation
    std::string GenerateWorld(int seed)
    {
        srand(seed);

        std::string message = "";
        int index = generation_step-1;

        int W = float(float(width)/100.0);
        int H = float(float(height)/100.0);

        switch (generation_param[index][pMODE])
        {
            case mADD :
                {
                    message = "Adding " + tiles[generation_param[index][pTILE]] + " Layer";
                    for (int i = 0; i < generation_param[index][pITER]; i++) AddLayer(
                            generation_param[index][pTILE],
                            generation_param[index][pDENSE],
                            int(generation_param[index][pMINX]*W),
                            int(generation_param[index][pMAXX]*W),
                            int(generation_param[index][pMINY]*H),
                            int(generation_param[index][pMAXY]*H)
                            );
                }
                break;
            case mSEED :
                {
                    message = "Seeding " + tiles[generation_param[index][pTILE]] + " Layer";
                    for (int i = 0; i < generation_param[index][pITER]; i++) SeedLayer(
                            generation_param[index][pTILE],
                            generation_param[index][pDENSE],
                            int(generation_param[index][pMINX]*W),
                            int(generation_param[index][pMAXX]*W),
                            int(generation_param[index][pMINY]*H),
                            int(generation_param[index][pMAXY]*H)
                            );
                }
                break;
            case mEXPAND :
                {
                    message = "Expanding " + tiles[generation_param[index][pTILE]] + " Layer";
                    for (int i = 0; i < generation_param[index][pITER]; i++) Expand(
                            generation_param[index][pTILE],
                            int(generation_param[index][pMINX]*W),
                            int(generation_param[index][pMAXX]*W),
                            int(generation_param[index][pMINY]*H),
                            int(generation_param[index][pMAXY]*H),
                            generation_param[index][pPROBN],
                            generation_param[index][pPROBS],
                            generation_param[index][pPROBE],
                            generation_param[index][pPROBW]
                            );
                }
                break;
            case mDEPOSIT :
                {
                    message = "Depositing " + tiles[generation_param[index][pTILE]] + " Layer";
                    for (int i = 0; i < generation_param[index][pITER]; i++) Deposit(
                            generation_param[index][pTILE],
                            int(generation_param[index][pMINX]*W),
                            int(generation_param[index][pMAXX]*W),
                            int(generation_param[index][pMINY]*H),
                            int(generation_param[index][pMAXY]*H),
                            generation_param[index][pPROBN],
                            generation_param[index][pPROBS],
                            generation_param[index][pPROBE],
                            generation_param[index][pPROBW]
                            );
        
                }
                break;
        }
        generation_step++;

        return message;
    }

    // Seed Methods
    void AddLayer(int t, int density, int xmin, int xmax, int ymin, int ymax)
    {
        for (int y = ymin; y < ymax; y++)
        {
            for (int x = xmin; x < xmax; x++)
            {
                if (rand()%1000 < density) matrix[y*width+x] = t;
            }
        }
    }

    void SeedLayer(int t, int density, int xmin, int xmax, int ymin, int ymax)
    {
        for (int y = ymin; y < ymax; y++)
        {
            for (int x = xmin; x < xmax; x++)
            {
                int index = y*width+x;
                if (matrix[index] != AIR && rand()%10000 < density) matrix[index] = t;
            }
        }
    }

    // Deposition Methods
    void Expand(int t, int xmin, int xmax, int miny, int maxy, int dn=5, int ds=5, int de=25, int dw=25)
    {
        replace = matrix;

        for (int y = miny; y < maxy; y++)
        {
            for (int x = xmin; x < xmax; x++)
            {
                if (matrix[y*width+x] != AIR &&
                        ( (x > 0) && (x < width-1) ) &&
                        ( (y > 0) && (y < height-1) ))
                {
                    int n = (y-1)*width+x;
                    int s = (y+1)*width+x;
                    int e = y*width+(x+1);
                    int w = y*width+(x-1);

                    if (matrix[n] == AIR && rand()%100 < dn) replace[n] = t;
                    if (matrix[s] == AIR && rand()%100 < ds) replace[s] = t;
                    if (matrix[e] == AIR && rand()%100 < de) replace[e] = t;
                    if (matrix[w] == AIR && rand()%100 < dw) replace[w] = t;
                }
            }
        }
        matrix = replace;
    }

    void Deposit(int t, int xmin, int xmax, int miny, int maxy, int dn=5, int ds=5, int de=25, int dw=25)
    {
        replace = matrix;

        for (int y = miny; y < maxy; y++)
        {
            for (int x = xmin; x < xmax; x++)
            {
                if (matrix[y*width+x] == t &&
                        ( (x > 0) && (x < width-1) ) &&
                        ( (y > 0) && (y < height-1) )
                        )
                {
                    int n = (y-1)*width+x;
                    int s = (y+1)*width+x;
                    int e = y*width+(x+1);
                    int w = y*width+(x-1);

                    if (rand()%100 < dn) replace[n] = t;
                    if (rand()%100 < ds) replace[s] = t;
                    if (rand()%100 < de) replace[e] = t;
                    if (rand()%100 < dw) replace[w] = t;
                }
            }
        }
        matrix = replace;
    }

    // Update Method
    void SettleTiles(int X, int Y, int W, int H)
    {
        replace = matrix;

        for (int y = H; y > 0; y--)
        {
            for (int x = 0; x < W; x++)
            {
                if ( (y+Y > 2 && y+Y < height-2) && Collision(x+X, y+Y) )
                {
                    int index = (y+Y)*width+(x+X);
                    int current_cell = matrix[index];

                    // Tile Interactions
                    switch (current_cell)
                    {
                        case WATER :
                        {
                            int dN  = int( (y+Y-1) * width + (x+X  ) );
                            int dE  = int( (y+Y  ) * width + (x+X+1) );
                            int dS  = int( (y+Y+1) * width + (x+X  ) );
                            int dW  = int( (y+Y  ) * width + (x+X-1) );
                            switch (matrix[dS])
                            {
                                case GRASS :
                                {
                                    replace[index] = AIR;
                                    replace[dS] = GRASS;
                                }
                                break;
                                case DIRT :
                                {
                                    replace[index] = AIR;
                                    replace[dS] = MUD;
                                }
                                break;
                                case SNOW :
                                {
                                    replace[index] = AIR;
                                    replace[dS] = ICE;
                                }
                                break;
                                case MANTLE :
                                {
                                    replace[index] = STEAM;
                                }
                                break;
                                case LAVA :
                                {
                                    replace[index] = STEAM;
                                    matrix[index] = STEAM;
                                    replace[dS] = OBSIDIAN;
                                    matrix[dS] = OBSIDIAN;
                                }
                                break;
                            }
                            switch (matrix[dW])
                            {
                                case DIRT :
                                {
                                    replace[index] = AIR;
                                    replace[dW] = MUD;
                                }
                                break;
                                case LAVA :
                                {
                                    replace[index] = STEAM;
                                    matrix[index] = STEAM;
                                    replace[dW] = OBSIDIAN;
                                    matrix[dW] = OBSIDIAN;
                                }
                                break;
                            }
                            switch (matrix[dE])
                            {
                                case DIRT :
                                {
                                    replace[index] = AIR;
                                    replace[dE] = MUD;
                                }
                                break;
                                case LAVA :
                                {
                                    replace[index] = STEAM;
                                    matrix[index] = STEAM;
                                    replace[dE] = OBSIDIAN;
                                    matrix[dE] = OBSIDIAN;
                                }
                                break;
                            }
                            switch (matrix[dN])
                            {
                                case DIRT :
                                {
                                    replace[index] = AIR;
                                    replace[dN] = MUD;
                                }
                                break;
                                case LAVA :
                                {
                                    replace[index] = STEAM;
                                    matrix[index] = STEAM;
                                    replace[dN] = OBSIDIAN;
                                    matrix[dN] = OBSIDIAN;
                                }
                                break;
                            }
                        }
                        break;
                        case SNOW :
                        {
                            int dS  = int( (y+Y+1) * width + (x+X  ) );
                            switch (matrix[dS])
                            {
                                case GRASS :
                                {
                                    if (rand()%100 < 25) replace[index] = AIR;
                                }
                                break;
                                case LAVA :
                                {
                                    replace[index] = WATER;
                                }
                                break;
                            }
                        }
                        break;
                        case ICE :
                        {
                            int dN  = int( (y+Y-1) * width + (x+X  ) );
                            int dE  = int( (y+Y  ) * width + (x+X+1) );
                            int dS  = int( (y+Y+1) * width + (x+X  ) );
                            int dW  = int( (y+Y  ) * width + (x+X-1) );
                            if ((matrix[dN] == LAVA) ||
                                (matrix[dS] == LAVA) ||
                                (matrix[dE] == LAVA) ||
                                (matrix[dW] == LAVA)) replace[index] = WATER;
                            if (matrix[dS] == GRASS)
                            {
                                replace[index] = WATER;
                            }
                        }
                        break;
                        case GRASS :
                        {
                            int dNW = int( (y+Y-1) * width + (x+X-1) );
                            int dNE = int( (y+Y-1) * width + (x+X+1) );
                            int dE  = int( (y+Y  ) * width + (x+X+1) );
                            int dSE = int( (y+Y+1) * width + (x+X+1) );
                            int dSW = int( (y+Y+1) * width + (x+X-1) );
                            int dW  = int( (y+Y  ) * width + (x+X-1) );
                            if (rand()%100 < 5)
                            {
                                if ((matrix[dE] == DIRT || matrix[dE] == SOIL) && !Collision(x+X+1, y+Y-1)) replace[dE] = GRASS;
                                else if ((matrix[dW] == DIRT || matrix[dW] == SOIL) && !Collision(x+X-1, y+Y-1)) replace[dW] = GRASS;
                                else if ((matrix[dNE] == DIRT || matrix[dNE] == SOIL) && !Collision(x+X+1, y+Y-2)) replace[dNE] = GRASS;
                                else if ((matrix[dNW] == DIRT || matrix[dNE] == SOIL) && !Collision(x+X-1, y+Y-2)) replace[dNW] = GRASS;
                                else if ((matrix[dSE] == DIRT || matrix[dSE] == SOIL) && !Collision(x+X+1, y+Y)) replace[dSE] = GRASS;
                                else if ((matrix[dSW] == DIRT || matrix[dSE] == SOIL) && !Collision(x+X-1, y+Y)) replace[dSW] = GRASS;
                            }
                        }
                        break;
                        case MOSS :
                        {
                            int dNW = int( (y+Y-1) * width + (x+X-1) );
                            int dNE = int( (y+Y-1) * width + (x+X+1) );
                            int dE  = int( (y+Y  ) * width + (x+X+1) );
                            int dSE = int( (y+Y+1) * width + (x+X+1) );
                            int dSW = int( (y+Y+1) * width + (x+X-1) );
                            int dW  = int( (y+Y  ) * width + (x+X-1) );
                            if (rand()%1000 < 5)
                            {
                                if ((matrix[dE] == STONE) && !Collision(x+X+1, y+Y-1)) replace[dE] = MOSS;
                                else if ((matrix[dW] == STONE) && !Collision(x+X-1, y+Y-1)) replace[dW] = MOSS;
                                else if ((matrix[dNE] == STONE) && !Collision(x+X+1, y+Y-2)) replace[dNE] = MOSS;
                                else if ((matrix[dNW] == STONE) && !Collision(x+X-1, y+Y-2)) replace[dNW] = MOSS;
                                else if ((matrix[dSE] == STONE) && !Collision(x+X+1, y+Y)) replace[dSE] = MOSS;
                                else if ((matrix[dSW] == STONE) && !Collision(x+X-1, y+Y)) replace[dSW] = MOSS;
                            }
                        }
                        break;
                    }
                    // Update Moving Tiles
                    int cell_type = SOLID;
                    switch (current_cell)
                        {
                        case WATER : cell_type = FLUID; break;
                        case BRINE : cell_type = FLUID; break;
                        case BLOOD : cell_type = FLUID; break;
                        
                        case HONEY : cell_type = GEL; break;
                        case LAVA : cell_type = GEL; break;

                        case SAND : cell_type = GRAIN; break;
                        case SNOW : cell_type = GRAIN; break;
                        case SLEET : cell_type = GRAIN; break;
                        case SILT : cell_type = GRAIN; break;
                        case GRAVEL : cell_type = GRAIN; break;
                        
                        case STEAM : cell_type = GAS; break;
                        case SMOKE : cell_type = GAS; break;
                    }

                    switch (cell_type)
                    {
                        case FLUID :
                        {
                            if (!FluidCollision(x+X, y+Y+2) && !FluidCollision(x+X, y+Y+1))
                            {
                                int rplc = (y+Y+2)*width+(x+X);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░░░░░
                                                                  // ░░██░░
                            }
                            else if (!FluidCollision(x+X, y+Y+1))
                            {
                                int rplc = (y+Y+1)*width+(x+X);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░██░░
                            }
                            else if (!FluidCollision(x+X-1, y+Y+1))
                            {
                                int rplc = (y+Y+1)*width+(x+X-1); // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ██░░░░
                            }
                            else if (!FluidCollision(x+X+1, y+Y+1))
                            {
                                int rplc = (y+Y+1)*width+(x+X+1); // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░░░██
                            }
                            else if (!FluidCollision(x+X-2, y+Y) && !FluidCollision(x+X-1, y+Y))
                            {
                                int rplc = (y+Y)*width+(x+X-2);   // ░░░░░░░░
                                replace[rplc] = matrix[index];    // ██░░▓▓░░
                                replace[index] = AIR;             // ░░░░░░░░
                            }
                            else if (!FluidCollision(x+X+2, y+Y) && !FluidCollision(x+X+1, y+Y))
                            {
                                int rplc = (y+Y)*width+(x+X+2);   // ░░░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░██
                                replace[index] = AIR;             // ░░░░░░░░
                            }
                            else if (!FluidCollision(x+X-1, y+Y) && FluidCollision(x+X+1, y+Y))
                            {
                                int rplc = (y+Y)*width+(x+X-1);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ██▓▓░░
                                replace[index] = AIR;             // ░░░░░░
                            }
                            else if (!FluidCollision(x+X+1, y+Y) && FluidCollision(x+X-1, y+Y))
                            {
                                int rplc = (y+Y)*width+(x+X+1);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓██
                                replace[index] = AIR;             // ░░░░░░
                            }
                        };
                        break;
                        case GEL :
                        {
                            if (!FluidCollision(x+X, y+Y+1))
                            {
                                int rplc = (y+Y+1)*width+(x+X);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░██░░
                            }
                            else if (!FluidCollision(x+X-1, y+Y+1))
                            {
                                int rplc = (y+Y+1)*width+(x+X-1); // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ██░░░░
                            }
                            else if (!FluidCollision(x+X+1, y+Y+1))
                            {
                                int rplc = (y+Y+1)*width+(x+X+1); // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░░░██
                            }
                            else if (!FluidCollision(x+X-1, y+Y) && FluidCollision(x+X+1, y+Y))
                            {
                                int rplc = (y+Y)*width+(x+X-1);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ██▓▓░░
                                replace[index] = AIR;             // ░░░░░░
                            }
                            else if (!FluidCollision(x+X+1, y+Y) && FluidCollision(x+X-1, y+Y))
                            {
                                int rplc = (y+Y)*width+(x+X+1);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓██
                                replace[index] = AIR;             // ░░░░░░
                            }
                        };
                        break;
                        case GRAIN :
                        {
                            if (!DualCollision(x+X, y+Y+1))
                            {
                                int rplc = (y+Y+1)*width+(x+X);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░██░░
                            }
                            else if (!DualCollision(x+X-1, y+Y+1))
                            {
                                int rplc = (y+Y+1)*width+(x+X-1); // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ██░░░░
                            }
                            else if (!DualCollision(x+X+1, y+Y+1))
                            {
                                int rplc = (y+Y+1)*width+(x+X+1); // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░░░██
                            }
                        };
                        break;
                        case GAS :
                        {
                            if (!DualCollision(x+X, y+Y-1))
                            {
                                int rplc = (y+Y-1)*width+(x+X);   // ░░██░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░░░░░
                            }
                            else if (!DualCollision(x+X-1, y+Y-1))
                            {
                                int rplc = (y+Y-1)*width+(x+X-1); // ██░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░░░░░
                            }
                            else if (!DualCollision(x+X+1, y+Y-1))
                            {
                                int rplc = (y+Y-1)*width+(x+X+1); // ░░░░██
                                replace[rplc] = matrix[index];    // ░░▓▓░░
                                replace[index] = AIR;             // ░░░░░░
                            }
                            else if (!DualCollision(x+X-1, y+Y) && DualCollision(x+X+1, y+Y))
                            {
                                int rplc = (y+Y)*width+(x+X-1);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ██▓▓░░
                                replace[index] = AIR;             // ░░░░░░
                            }
                            else if (!DualCollision(x+X+1, y+Y) && DualCollision(x+X-1, y+Y))
                            {
                                int rplc = (y+Y)*width+(x+X+1);   // ░░░░░░
                                replace[rplc] = matrix[index];    // ░░▓▓██
                                replace[index] = AIR;             // ░░░░░░
                            }
                        };
                        break;
                    }
                }
            }
        }
        matrix = replace;
    }

    // Return Methods
    int Neighbors(int x, int y)
    {
        int value = 0;
        value += bool(matrix[(y-2)*width+(x)]);
        value += bool(matrix[(y-1)*width+(x)]);
        value += bool(matrix[(y)*width+(x-1)]);
        value += bool(matrix[(y)*width+(x+1)]);

        return value;
    }

    bool FluidCollision(int x, int y)
    {
        return (replace[y*width+x] > SMOKE);
    }

    bool DualCollision(int x, int y)
    {
        return (matrix[y*width+x]) || bool(replace[y*width+x]);
    }

    bool Collision(int x, int y)
    {
        return bool(matrix[y*width+x]);
    }

    bool IsColliding(int x, int y)
    {
        return (matrix[y*width+x] > LAVA);
    }

};
