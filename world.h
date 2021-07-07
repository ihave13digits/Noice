class World
{
public:

    // Class Attributes //

    // World Dimensions

    int width;
    int height;
    int chunk_size = 16;

    // Terrain Tiles

    int total_tiles = 92;
    int total_parameters = 12;
    int total_modes = 4;

    // Procedural Generation
    int selected_step = 0;
    int selected_param = 0;
    int generation_step = 1;
    int generation_steps = 1;
    int maximum_generation_steps = 128;

    int clipboard_param[12];
    int generation_param[128][12];

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
        pMODE,
        pDENSE,
        pITER,
        pMINX,
        pMAXX,
        pMINY,
        pMAXY,
        pPROBN,
        pPROBS,
        pPROBE,
        pPROBW
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
        THIN_SMOKE,
        SMOKE,
        THICK_SMOKE,
        FLARE,
        FLAME,
        FIRE,
        //
        FOG,
        WATER,
        BRINE,
        HONEY,
        BLOOD,
        LAVA,
        MUCK,
        MUD,
        //
        ASH,
        EMBER,
        SAND,
        SNOW,
        SLEET,
        SALT,
        SILT,
        GRAVEL,
        CHARCOAL,
        //
        CHARRED_WOOD,
        ICE,
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
        //
        WOOD,
        TRUNK,
        BRANCH,
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
        GLASS,
        PLANKS,
        VALVE_CLOSED,
        VALVE_OPEN,
        PUMP,
        PIPE,
        PIPE_WATER,
        PIPE_BRINE,
        PIPE_HONEY,
        PIPE_BLOOD,
        PIPE_LAVA,
        PIPE_MUCK,
        PIPE_MUD,
        DRAIN,
        GUTTER,
        GUTTER_WATER,
        GUTTER_BRINE,
        GUTTER_HONEY,
        GUTTER_BLOOD,
        GUTTER_LAVA,
        GUTTER_MUCK,
        GUTTER_MUD,
        //
        AXLE_LEFT,
        AXLE_RIGHT,
        CONVEYOR_LEFT,
        CONVEYOR_RIGHT,
        //
        MANTLE
    };

    std::string tiles[92] = {
        //
        "Air",
        "Steam",
        "Thin Smoke",
        "Smoke",
        "Thick Smoke",
        "Flare",
        "Flame",
        "Fire",
        //
        "Fog",
        "Water",
        "Brine",
        "Honey",
        "Blood",
        "Lava",
        "Muck",
        "Mud",
        //
        "Ash",
        "Ember",
        "Sand",
        "Snow",
        "Sleet",
        "Salt",
        "Silt",
        "Gravel",
        "Charcoal",
        //
        "Charred Wood",
        "Ice",
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
        //
        "Wood",
        "Trunk",
        "Branch",
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
        "Glass",
        "Planks",
        "Valve (Closed)",
        "Valve (Open)",
        "Pump",
        "Pipe",
        "Pipe (Water)",
        "Pipe (Brine)",
        "Pipe (Honey)",
        "Pipe (Blood)",
        "Pipe (Lava)",
        "Pipe (Muck)",
        "Pipe (Mud)",
        "Drain",
        "Gutter",
        "Gutter (Water)",
        "Gutter (Brine)",
        "Gutter (Honey)",
        "Gutter (Blood)",
        "Gutter (Lava)",
        "Gutter (Muck)",
        "Gutter (Mud)",
        //
        "Axle (Left)",
        "Axle (Right)",
        "Conveyor (Left)",
        "Conveyor (Right)",
        //
        "Mantle"
    };

    int tileset[92][2][4] = {
        // |Base Color        |     |Variation       |
        // Gases
        {  {200, 200, 230, 5  },    {1,   1,   25,  0}  },// Air
        {  {220, 220, 230, 32 },    {5,   5,   25,  0}  },// Steam
        {  {128, 128, 128, 32 },    {5,   5,   5,   0}  },// Thin Smoke
        {  {128, 128, 128, 64 },    {5,   5,   5,   0}  },// Smoke
        {  {128, 128, 128, 128},    {5,   5,   5,   0}  },// Thick Smoke
        {  {255, 255, 0,   200},    {1,  180,  1,   0}  },// Flare
        {  {255, 200, 0,   200},    {1,  180,  1,   0}  },// Flame
        {  {255, 180, 0,   200},    {1,  180,  1,   0}  },// Fire
        // Fluids
        {  {230, 230, 230, 64 },    {5,   5,   25,  0}  },// Fog
        {  {0,   0,   128, 128},    {1,   1,   25,  0}  },// Water
        {  {0,   64,  128, 128},    {1,   1,   25,  0}  },// Brine
        {  {230, 200, 0,   212},    {25,  10,  1,   0}  },// Honey
        {  {128, 0,   0,   255},    {25,  1,   1,   0}  },// Blood
        {  {254, 80,  0,   255},    {1,  180,  1,   0}  },// Lava
        {  {20,  16,  12,  255},    {8,   4,   2,   0}  },// Muck
        {  {58,  32,  16,  255},    {8,   4,   2,   0}  },// Mud
        // Granular Materials
        {  {225, 225, 225, 255},    {1,   1,   1,   0}  },// Ash
        {  {255, 100, 0,   255},    {1,  180,  1,   0}  },// Ember
        {  {230, 230, 128, 255},    {15,  15,  5,   0}  },// Sand
        {  {255, 255, 255, 255},    {1,   1,   25,  0}  },// Snow
        {  {200, 200, 200, 212},    {1,   1,   55,  0}  },// Sleet
        {  {240, 240, 240, 255},    {10,  10,  10,  0}  },// Salt
        {  {130, 120, 140, 255},    {10,  10,  10,  0}  },// Silt
        {  {110, 105, 100, 255},    {10,  10,  10,  0}  },// Gravel
        {  {16,  10,  8,   255},    {10,  5,   1,   0}  },// Charcoal
        // Solid Materials
        {  {24,  16,  12,   255},    {10,  5,   1,   0}  },// Charred Wood
        {  {180, 180, 200, 128},    {1,   1,   55,  0}  },// Ice
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
        // Plant Materials
        {  {120, 80,  64,  255},    {25,  20,  10,  0}  },// Wood
        {  {64,  48,  32,  255},    {25,  20,  10,  0}  },// Trunk
        {  {66,  50,  34,  255},    {25,  20,  10,  0}  },// Branch
        {  {40,   80, 0,   225},    {5,   20,  1,   0}  },// Leaves
        {  {0,   128, 0,   255},    {5,   20,  1,   0}  },// Grass
        {  {20,   80, 0,   255},    {5,   20,  1,   0}  },// Moss
        // Metals
        {  {200, 200, 230, 255},    {10,  10,  25,  0}  },// Platinum
        {  {245, 230, 0,   255},    {10,  5,   1,   0}  },// Gold
        {  {160, 160, 200, 255},    {10,  10,  15,  0}  },// Silver
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
        // Crafted Materials
        {  {220, 220, 245,  64},    {5,   15,  10,  0}  },// Glass
        {  {120, 80,  48,  255},    {25,  20,  10,  0}  },// Planks
        {  {80,  80,  80,  255},    {15,  10,  10,  0}  },// Valve (Closed)
        {  {80,  80,  80,  255},    {15,  10,  10,  0}  },// Valve (Open)
        {  {80,  80,  80,  255},    {15,  10,  10,  0}  },// Pump
        {  {100, 100, 100, 255},    {15,  10,  10,  0}  },// Pipe
        {  {100, 100, 110, 255},    {15,  10,  10,  0}  },// Pipe (Water)
        {  {100, 100, 110, 255},    {15,  10,  10,  0}  },// Pipe (Brine)
        {  {110, 110, 100, 255},    {15,  10,  10,  0}  },// Pipe (Honey)
        {  {110, 100, 100, 255},    {15,  10,  10,  0}  },// Pipe (Blood)
        {  {130, 120, 100, 255},    {15,  10,  10,  0}  },// Pipe (Lava)
        {  {120, 110, 100, 255},    {15,  10,  10,  0}  },// Pipe (Muck)
        {  {130, 120, 110, 255},    {15,  10,  10,  0}  },// Pipe (Mud)
        {  {60,  60,  60,  255},    {15,  10,  10,  0}  },// Drain
        {  {100, 100, 100, 255},    {15,  10,  10,  0}  },// Gutter
        {  {100, 100, 110, 255},    {15,  10,  10,  0}  },// Gutter (Water)
        {  {100, 100, 110, 255},    {15,  10,  10,  0}  },// Gutter (Brine)
        {  {110, 110, 100, 255},    {15,  10,  10,  0}  },// Gutter (Honey)
        {  {110, 100, 100, 255},    {15,  10,  10,  0}  },// Gutter (Blood)
        {  {130, 120, 100, 255},    {15,  10,  10,  0}  },// Gutter (Lava)
        {  {120, 110, 100, 255},    {15,  10,  10,  0}  },// Gutter (Muck)
        {  {130, 120, 110, 255},    {15,  10,  10,  0}  },// Gutter (Mud)
        {  {40,  40,  50,  255},    {15,  10,  10,  0}  },// Axle (Left)
        {  {40,  40,  50,  255},    {15,  10,  10,  0}  },// Axle (Right)
        {  {50,  50,  50,  255},    {15,  10,  10,  0}  },// Conveyor (Left)
        {  {50,  50,  50,  255},    {15,  10,  10,  0}  },// Conveyor (Right)
        // Unbreakable
        {  {25,  20,  20,  255},    {25,  1,   1,   0}  },// Mantle
    };

    std::vector<char> matrix;
    std::vector<char> replace;



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

    void ClearData()
    {
        for (int i = 0; i < maximum_generation_steps; i++)
        {
            for (int p = 0; p < total_parameters; p++)
            {
                generation_param[i][p] = 0;
            }
        }
    }

    void PresetData()
    {
        generation_steps = 62;
        int preset_data[generation_steps][total_parameters] = {
            // T          M         D    I   x    X    y    Y    N    S    E    W
            { STONE,      mADD,     8,   1,  0,   100, 20,  75,  0,   0,   0,   0   },
            { STONE,      mADD,     4,   1,  0,   100, 30,  76,  0,   0,   0,   0   },
            { STONE,      mADD,     2,   1,  0,   100, 40,  77,  0,   0,   0,   0   },
            { STONE,      mADD,     1,   1,  0,   100, 50,  78,  0,   0,   0,   0   },
            { STONE,      mADD,     1,   1,  0,   100, 60,  79,  0,   0,   0,   0   },
            { MANTLE,     mADD,     8,   1,  0,   100, 95,  100, 0,   0,   0,   0   },
            { MANTLE,     mADD,     16,  1,  0,   100, 97,  100, 0,   0,   0,   0   },

            { STONE,      mEXPAND,  0,   1,  0,   100, 15,  85,  25,  50,  100, 100 },
            { STONE,      mEXPAND,  0,   1,  0,   100, 25,  85,  25,  50,  100, 100 },
            { STONE,      mEXPAND,  0,   1,  0,   100, 35,  85,  50,  25,  100, 100 },
            { STONE,      mEXPAND,  0,   2,  0,   100, 45,  85,  25,  5,   100, 100 },
            { STONE,      mEXPAND,  0,   1,  0,   100, 55,  85,  25,  50,  100, 100 },
            { STONE,      mEXPAND,  0,   4,  0,   100, 65,  85,  25,  50,  100, 100 },
            { STONE,      mEXPAND,  0,   2,  0,   100, 75,  85,  50,  25,  100, 100 },
            { STONE,      mEXPAND,  0,   1,  0,   100, 80,  85,  25,  5,   100, 100 },
            
            { SOIL,       mEXPAND,  0,   4,  0,   100, 8,   30,  50,  25,  90,  90  },
            { MUD,        mEXPAND,  0,   1,  0,   100, 10,  40,  50,  25,  75,  75  },
            { SOIL,       mEXPAND,  0,   1,  0,   100, 8,   30,  50,  25,  90,  90  },
            { MUD,        mEXPAND,  0,   2,  0,   100, 10,  40,  50,  25,  75,  75  },
            { DIRT,       mEXPAND,  0,   1,  0,   100, 10,  40,  50,  25,  90,  90  },
            { MUD,        mEXPAND,  0,   1,  0,   100, 15,  50,  25,  12,  37,  37  },
            { DIRT,       mEXPAND,  0,   2,  0,   100, 15,  60,  50,  25,  90,  90  },
            { MUD,        mEXPAND,  0,   1,  0,   100, 15,  70,  25,  12,  37,  37  },
            { DIRT,       mEXPAND,  0,   4,  0,   100, 12,  80,  50,  25,  90,  90  },
            { DIRT,       mEXPAND,  0,   4,  0,   100, 6,   20,  50,  25,  100, 100 },

            { GRAVEL,     mEXPAND,  0,   4,  0,   100, 30,  80,  50,  0,   0,   0   },
            { GRAVEL,     mEXPAND,  0,   4,  0,   100, 50,  60,  50,  0,   0,   0   },
            { GRASS,      mEXPAND,  0,   1,  0,   100, 8,   25,  100, 0,   5,   5   },
            { MANTLE,     mEXPAND,  0,   16, 0,   100, 85,  100, 10,  10,  100, 100 },
            { LAVA,       mEXPAND,  0,   16, 0,   100, 90,  100, 100, 100, 100, 100 },

            { PLATINUM,   mSEED,    2,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { GOLD,       mSEED,    2,   1,  0,   100, 60,  80,  0,   0,   0,   0   },
            { SILVER,     mSEED,    3,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { COPPER,     mSEED,    4,   1,  0,   100, 30,  50,  0,   0,   0,   0   },
            { LEAD,       mSEED,    3,   1,  0,   100, 70,  80,  0,   0,   0,   0   },
            { TIN,        mSEED,    3,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { IRON,       mSEED,    4,   1,  0,   100, 25,  50,  0,   0,   0,   0   },
            { COBALT,     mSEED,    3,   1,  0,   100, 25,  40,  0,   0,   0,   0   },
            { NICKEL,     mSEED,    3,   1,  0,   100, 25,  30,  0,   0,   0,   0   },
            { TITANIUM,   mSEED,    2,   1,  0,   100, 40,  60,  0,   0,   0,   0   },
            { TUNGSTEN,   mSEED,    2,   1,  0,   100, 70,  80,  0,   0,   0,   0   },

            { PLATINUM,   mDEPOSIT, 0,   4,  0,   100, 60,  80,  25,  25,  25,  25  },
            { GOLD,       mDEPOSIT, 0,   4,  0,   100, 60,  80,  25,  25,  25,  25  },
            { SILVER,     mDEPOSIT, 0,   6,  0,   100, 50,  70,  25,  25,  25,  25  },
            { COPPER,     mDEPOSIT, 0,   8,  0,   100, 30,  50,  25,  25,  25,  25  },
            { LEAD,       mDEPOSIT, 0,   8,  0,   100, 70,  80,  25,  25,  25,  25  },
            { TIN,        mDEPOSIT, 0,   8,  0,   100, 50,  70,  25,  25,  25,  25  },
            { IRON,       mDEPOSIT, 0,   8,  0,   100, 25,  50,  25,  25,  25,  25  },
            { COBALT,     mDEPOSIT, 0,   6,  0,   100, 25,  40,  25,  25,  25,  25  },
            { NICKEL,     mDEPOSIT, 0,   6,  0,   100, 25,  30,  25,  25,  25,  25  },
            { TITANIUM,   mDEPOSIT, 0,   6,  0,   100, 40,  60,  25,  25,  25,  25  },
            { TUNGSTEN,   mDEPOSIT, 0,   4,  0,   100, 70,  80,  25,  25,  25,  25  },

            { JADE,       mSEED,    2,   1,  0,   100, 40,  60,  0,   0,   0,   0   },
            { RUBY,       mSEED,    2,   1,  0,   100, 40,  60,  0,   0,   0,   0   },
            { AMBER,      mSEED,    2,   1,  0,   100, 40,  60,  0,   0,   0,   0   },
            { LAPIS,      mSEED,    2,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { TOPAZ,      mSEED,    2,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { DIAMOND,    mSEED,    2,   1,  0,   100, 70,  90,  0,   0,   0,   0   },
            { EMERALD,    mSEED,    2,   1,  0,   100, 70,  90,  0,   0,   0,   0   },
            { AMETHYST,   mSEED,    2,   1,  0,   100, 60,  80,  0,   0,   0,   0   },
            { SAPPHIRE,   mSEED,    2,   1,  0,   100, 60,  80,  0,   0,   0,   0   },
        };

        for (int i = 0; i < generation_steps; i++)
        {
            for (int p = 0; p < total_parameters; p++)
            {
                generation_param[i][p] = preset_data[i][p];
            }
        }
    }

    void GeneratePreview()
    {
        int index = generation_step-1;

        switch (generation_param[index][pMODE])
        {
            case mADD :
                {
                    for (int i = 0; i < generation_param[index][pITER]; i++) AddLayer(
                            generation_param[index][pTILE],
                            generation_param[index][pDENSE],
                            generation_param[index][pMINX],
                            generation_param[index][pMAXX],
                            generation_param[index][pMINY],
                            generation_param[index][pMAXY]
                            );
                }
                break;
            case mSEED :
                {
                    for (int i = 0; i < generation_param[index][pITER]; i++) SeedLayer(
                            generation_param[index][pTILE],
                            generation_param[index][pDENSE],
                            generation_param[index][pMINX],
                            generation_param[index][pMAXX],
                            generation_param[index][pMINY],
                            generation_param[index][pMAXY]
                            );
                }
                break;
            case mEXPAND :
                {
                    for (int i = 0; i < generation_param[index][pITER]; i++) Expand(
                            generation_param[index][pTILE],
                            generation_param[index][pMINX],
                            generation_param[index][pMAXX],
                            generation_param[index][pMINY],
                            generation_param[index][pMAXY],
                            generation_param[index][pPROBN],
                            generation_param[index][pPROBS],
                            generation_param[index][pPROBE],
                            generation_param[index][pPROBW]
                            );
                }
                break;
            case mDEPOSIT :
                {
                    for (int i = 0; i < generation_param[index][pITER]; i++) Deposit(
                            generation_param[index][pTILE],
                            generation_param[index][pMINX],
                            generation_param[index][pMAXX],
                            generation_param[index][pMINY],
                            generation_param[index][pMAXY],
                            generation_param[index][pPROBN],
                            generation_param[index][pPROBS],
                            generation_param[index][pPROBE],
                            generation_param[index][pPROBW]
                            );
                }
                break;
        }
        generation_step++;
    }

    // Generation
    std::string GenerateWorld()
    {
        std::string message = "";
        int index = generation_step-1;

        float W = float(float(width)/100.0);
        float H = float(float(height)/100.0);

        switch (generation_param[index][pMODE])
        {
            case mADD :
                {
                    message = "Adding " + tiles[generation_param[index][pTILE]] + " Layer";
                    for (int i = 0; i < generation_param[index][pITER]; i++) AddLayer(
                            generation_param[index][pTILE],
                            generation_param[index][pDENSE],
                            std::round(float(generation_param[index][pMINX])*W),
                            std::round(float(generation_param[index][pMAXX])*W),
                            std::round(float(generation_param[index][pMINY])*H),
                            std::round(float(generation_param[index][pMAXY])*H)
                            );
                }
                break;
            case mSEED :
                {
                    message = "Seeding " + tiles[generation_param[index][pTILE]] + " Layer";
                    for (int i = 0; i < generation_param[index][pITER]; i++) SeedLayer(
                            generation_param[index][pTILE],
                            generation_param[index][pDENSE],
                            std::round(float(generation_param[index][pMINX])*W),
                            std::round(float(generation_param[index][pMAXX])*W),
                            std::round(float(generation_param[index][pMINY])*H),
                            std::round(float(generation_param[index][pMAXY])*H)
                            );
                }
                break;
            case mEXPAND :
                {
                    message = "Expanding " + tiles[generation_param[index][pTILE]] + " Layer";
                    for (int i = 0; i < generation_param[index][pITER]; i++) Expand(
                            generation_param[index][pTILE],
                            std::round(float(generation_param[index][pMINX])*W),
                            std::round(float(generation_param[index][pMAXX])*W),
                            std::round(float(generation_param[index][pMINY])*H),
                            std::round(float(generation_param[index][pMAXY])*H),
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
                            std::round(float(generation_param[index][pMINX])*W),
                            std::round(float(generation_param[index][pMAXX])*W),
                            std::round(float(generation_param[index][pMINY])*H),
                            std::round(float(generation_param[index][pMAXY])*H),
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
    void Expand(int t, int minx, int maxx, int miny, int maxy, int dn=5, int ds=5, int de=25, int dw=25)
    {
        replace = matrix;

        minx = std::max(minx, 1);
        maxx = std::min(maxx, width-2);
        miny = std::max(miny, 1);
        maxy = std::min(maxy, height-2);

        for (int y = miny; y < maxy; y++)
        {
            for (int x = minx; x < maxx; x++)
            {
                if (matrix[y*width+x] != AIR)
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

    void Deposit(int t, int minx, int maxx, int miny, int maxy, int dn=5, int ds=5, int de=25, int dw=25)
    {
        replace = matrix;

        minx = std::max(minx, 1);
        maxx = std::min(maxx, width-2);
        miny = std::max(miny, 1);
        maxy = std::min(maxy, height-2);
        
        for (int y = miny; y < maxy; y++)
        {
            for (int x = minx; x < maxx; x++)
            {
                if (matrix[y*width+x] == t)
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

        if (Y < 2)
        {
            Y = 1;
        }
        if (Y > height-H-2)
        {
            H = height-Y;
        }

        for (int y = H; y > 0; y--)
        {
            for (int x = 0; x < W; x++)
            {
                int _x = x+X;
                int _y = y+Y;
                if ( Collision(_x, _y) )
                {
                    int index = (_y)*width+(_x);
                    int current_cell = matrix[index];
                    int cell_type = CellType(_x, _y);
                    int direction = rand() % 100;

                    switch (cell_type)
                    {
                        case FLUID :
                        {
                            if (direction < 50)
                            {
                                if (!FluidCollision(_x, _y+2) && !FluidCollision(_x, _y+1))
                                {
                                    int rplc = (_y+2)*width+(_x);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                                                      // ░░██░░
                                }
                                else if (!FluidCollision(_x, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░██░░
                                }
                                else if (!FluidCollision(_x-1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x-1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ██░░░░
                                }
                                else if (!FluidCollision(_x+1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x+1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░██
                                }
                                else if (!FluidCollision(_x-2, _y) && !FluidCollision(_x-1, _y))
                                {
                                    int rplc = (_y)*width+(_x-2);     // ░░░░░░░░
                                    replace[rplc] = matrix[index];    // ██░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░░░
                                }
                                else if (!FluidCollision(_x+2, _y) && !FluidCollision(_x+1, _y))
                                {
                                    int rplc = (_y)*width+(_x+2);     // ░░░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░██
                                    replace[index] = AIR;             // ░░░░░░░░
                                }
                                else if (!FluidCollision(_x-1, _y) && FluidCollision(_x+1, _y))
                                {
                                    int rplc = (_y)*width+(_x-1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ██▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!FluidCollision(_x+1, _y) && FluidCollision(_x-1, _y))
                                {
                                    int rplc = (_y)*width+(_x+1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓██
                                    replace[index] = AIR;             // ░░░░░░
                                }
                            }
                            else
                            {
                                if (!FluidCollision(_x, _y+2) && !FluidCollision(_x, _y+1))
                                {
                                    int rplc = (_y+2)*width+(_x);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                                                      // ░░██░░
                                }
                                else if (!FluidCollision(_x, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░██░░
                                }
                                else if (!FluidCollision(_x+1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x+1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░██
                                }
                                else if (!FluidCollision(_x-1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x-1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ██░░░░
                                }
                                else if (!FluidCollision(_x+2, _y) && !FluidCollision(_x+1, _y))
                                {
                                    int rplc = (_y)*width+(_x+2);     // ░░░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░██
                                    replace[index] = AIR;             // ░░░░░░░░
                                }
                                else if (!FluidCollision(_x-2, _y) && !FluidCollision(_x-1, _y))
                                {
                                    int rplc = (_y)*width+(_x-2);     // ░░░░░░░░
                                    replace[rplc] = matrix[index];    // ██░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░░░
                                }
                                else if (!FluidCollision(_x+1, _y) && FluidCollision(_x-1, _y))
                                {
                                    int rplc = (_y)*width+(_x+1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓██
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!FluidCollision(_x-1, _y) && FluidCollision(_x+1, _y))
                                {
                                    int rplc = (_y)*width+(_x-1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ██▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                            }
                        };
                        break;
                        case GEL :
                        {
                            if (direction < 50)
                            {
                                if (!FluidCollision(_x, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░██░░
                                }
                                else if (!FluidCollision(_x-1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x-1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ██░░░░
                                }
                                else if (!FluidCollision(_x+1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x+1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░██
                                }
                                else if (!FluidCollision(_x-1, _y) && FluidCollision(_x+1, _y))
                                {
                                    int rplc = (_y)*width+(_x-1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ██▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!FluidCollision(_x+1, _y) && FluidCollision(_x-1, _y))
                                {
                                    int rplc = (_y)*width+(_x+1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓██
                                    replace[index] = AIR;             // ░░░░░░
                                }
                            }
                            else
                            {
                                if (!FluidCollision(_x, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░██░░
                                }
                                else if (!FluidCollision(_x+1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x+1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░██
                                }
                                else if (!FluidCollision(_x-1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x-1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ██░░░░
                                }
                                else if (!FluidCollision(_x+1, _y) && FluidCollision(_x-1, _y))
                                {
                                    int rplc = (_y)*width+(_x+1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓██
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!FluidCollision(_x-1, _y) && FluidCollision(_x+1, _y))
                                {
                                    int rplc = (_y)*width+(_x-1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ██▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                            }
                        };
                        break;
                        case GRAIN :
                        {
                            if (direction < 50)
                            {
                                if (!DualCollision(_x, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░██░░
                                }
                                else if (!DualCollision(_x-1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x-1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ██░░░░
                                }
                                else if (!DualCollision(_x+1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x+1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░██
                                }
                            }
                            else
                            {
                                if (!DualCollision(_x, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░██░░
                                }
                                else if (!DualCollision(_x+1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x+1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░██
                                }
                                else if (!DualCollision(_x-1, _y+1))
                                {
                                    int rplc = (_y+1)*width+(_x-1);   // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ██░░░░
                                }
                            }
                        };
                        break;
                        case GAS :
                        {
                            if (direction < 50)
                            {
                                if (!DualCollision(_x, _y-1))
                                {
                                    int rplc = (_y-1)*width+(_x);     // ░░██░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!DualCollision(_x-1, _y-1))
                                {
                                    int rplc = (_y-1)*width+(_x-1);   // ██░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!DualCollision(_x+1, _y-1))
                                {
                                    int rplc = (_y-1)*width+(_x+1);   // ░░░░██
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!DualCollision(_x-1, _y) && DualCollision(_x+1, _y))
                                {
                                    int rplc = (_y)*width+(_x-1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ██▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!DualCollision(_x+1, _y) && DualCollision(_x-1, _y))
                                {
                                    int rplc = (_y)*width+(_x+1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓██
                                    replace[index] = AIR;             // ░░░░░░
                                }
                            }
                            else
                            {
                                if (!DualCollision(_x, _y-1))
                                {
                                    int rplc = (_y-1)*width+(_x);     // ░░██░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!DualCollision(_x+1, _y-1))
                                {
                                    int rplc = (_y-1)*width+(_x+1);   // ░░░░██
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!DualCollision(_x-1, _y-1))
                                {
                                    int rplc = (_y-1)*width+(_x-1);   // ██░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!DualCollision(_x+1, _y) && DualCollision(_x-1, _y))
                                {
                                    int rplc = (_y)*width+(_x+1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ░░▓▓██
                                    replace[index] = AIR;             // ░░░░░░
                                }
                                else if (!DualCollision(_x-1, _y) && DualCollision(_x+1, _y))
                                {
                                    int rplc = (_y)*width+(_x-1);     // ░░░░░░
                                    replace[rplc] = matrix[index];    // ██▓▓░░
                                    replace[index] = AIR;             // ░░░░░░
                                }
                            }
                        };
                        break;
                    }

                    // Tile Interactions
                    switch (current_cell)
                    {
                        case WATER :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            switch (matrix[dS])
                            {
                                case GRASS : {replace[index] = AIR; replace[dS] = GRASS;} break;
                                case DIRT : {replace[index] = AIR; replace[dS] = MUD;} break;
                                case SOIL : {replace[index] = AIR; replace[dS] = MUCK;} break;
                                case SNOW : {replace[index] = AIR; replace[dS] = ICE;} break;
                                case SALT : { replace[index] = AIR; replace[dS] = BRINE; } break;
                                case MANTLE : {replace[index] = STEAM;} break;
                                case LAVA : {replace[index] = STEAM; replace[dS] = OBSIDIAN;} break;
                            }
                            switch (matrix[dW])
                            {
                                case DIRT : {replace[index] = AIR; replace[dW] = MUD;} break;
                                case SOIL : {replace[index] = AIR; replace[dW] = MUCK;} break;
                                case SALT : { replace[index] = AIR; replace[dS] = BRINE; } break;
                                case LAVA : {replace[index] = STEAM; replace[dW] = OBSIDIAN;} break;
                            }
                            switch (matrix[dE])
                            {
                                case DIRT : {replace[index] = AIR; replace[dE] = MUD;} break;
                                case SOIL : {replace[index] = AIR; replace[dE] = MUCK;} break;
                                case SALT : { replace[index] = AIR; replace[dS] = BRINE; } break;
                                case LAVA : {replace[index] = STEAM; replace[dE] = OBSIDIAN;} break;
                            }
                            switch (matrix[dN])
                            {
                                case DIRT : {replace[index] = AIR; replace[dN] = MUD;} break;
                                case SOIL : {replace[index] = AIR; replace[dN] = MUCK;} break;
                                case SALT : { replace[index] = AIR; replace[dS] = BRINE; } break;
                                case LAVA : {replace[index] = STEAM; replace[dN] = OBSIDIAN;} break;
                            }
                        }
                        break;
                        case LAVA :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            int chance = rand()%10000;
                            switch (matrix[dS])
                            {
                                case GRAVEL : { if (chance < 100) replace[dS] = LAVA;} break;
                                case SAND : { if (chance < 500) replace[dS] = LAVA;} break;
                                case ASH : { if (chance < 1000) replace[dS] = SMOKE;} break;
                                case ICE : {replace[dS] = WATER;} break;
                                case SNOW : {replace[dS] = WATER;} break;
                                case WATER : {replace[index] = OBSIDIAN; replace[dS] = STEAM;} break;
                                case CHARCOAL : { if (chance < 1000) replace[dS] = EMBER; } break;
                                case CHARRED_WOOD : { if (chance < 1000) replace[dN] = CHARCOAL; } break;
                                case WOOD: { if (chance < 500) replace[dS] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dW])
                            {
                                case GRAVEL : { if (chance < 100) replace[dW] = LAVA;} break;
                                case SAND : { if (chance < 500) replace[dW] = LAVA;} break;
                                case ASH : { if (chance < 1000) replace[dW] = SMOKE;} break;
                                case WATER : {replace[index] = OBSIDIAN; replace[dW] = STEAM;} break;
                                case CHARCOAL : { if (chance < 1000) replace[dW] = EMBER; } break;
                                case CHARRED_WOOD : { if (chance < 1000) replace[dN] = CHARCOAL; } break;
                                case WOOD: { if (chance < 500) replace[dW] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dE])
                            {
                                case GRAVEL : { if (chance < 100) replace[dE] = LAVA;} break;
                                case SAND : { if (chance < 500) replace[dE] = LAVA;} break;
                                case ASH : { if (chance < 1000) replace[dE] = SMOKE;} break;
                                case WATER : {replace[index] = OBSIDIAN; replace[dE] = STEAM;} break;
                                case CHARCOAL : { if (chance < 1000) replace[dE] = EMBER; } break;
                                case CHARRED_WOOD : { if (chance < 1000) replace[dN] = CHARCOAL; } break;
                                case WOOD: { if (chance < 500) replace[dE] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dN])
                            {
                                case GRAVEL : { if (chance < 100) replace[dN] = LAVA;} break;
                                case SAND : { if (chance < 500) replace[dN] = LAVA;} break;
                                case ASH : { if (chance < 1000) replace[dN] = SMOKE;} break;
                                case WATER : {replace[index] = OBSIDIAN; replace[dN] = STEAM;} break;
                                case CHARCOAL : { if (chance < 1000) replace[dN] = EMBER; } break;
                                case CHARRED_WOOD : { if (chance < 1000) replace[dN] = CHARCOAL; } break;
                                case WOOD: { if (chance < 500) replace[dN] = CHARRED_WOOD; } break;
                            }
                        }
                        break;
                        case MUD :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            if (matrix[dN] == AIR) { if (rand()%10000 < 5) replace[index] = DIRT; }
                        }
                        break;
                        case MUCK :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            if (matrix[dN] == AIR) { if (rand()%10000 < 5) replace[index] = SOIL; }
                        }
                        break;
                        case SNOW :
                        {
                            int dS  = int( (_y+1) * width + (_x  ) );
                            switch (matrix[dS])
                            {
                                case GRASS : { if (rand()%100 < 25) replace[index] = AIR; } break;
                                case LAVA : { replace[index] = WATER; } break;
                            }
                        }
                        break;
                        case BRINE :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            if (matrix[dN] == AIR) if (rand()%10000 < 5) { replace[index] = WATER; replace[dN] = SALT; }
                        }
                        break;
                        case EMBER :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            int chance = rand()%10000;
                            switch (matrix[dN])
                            {
                                case WATER : { replace[index] = CHARCOAL; } break;
                                case AIR: { replace[dN] = FIRE; } break;
                                case ASH : { replace[index] = CHARCOAL; } break;
                                case SMOKE : { replace[index] = CHARCOAL; } break;
                                case CHARCOAL : { if (chance < 1000) replace[dN] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 1000) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 500) replace[dN] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 500) replace[dN] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 500) replace[dN] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dS])
                            {
                                case SMOKE : { replace[dS] = EMBER; } break;
                                case WATER : { replace[index] = AIR; } break;
                                case CHARCOAL : { if (chance < 500) replace[dS] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 500) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 250) replace[dS] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 250) replace[dS] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 250) replace[dS] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dE])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR: { replace[dE] = FIRE; } break;
                                case CHARCOAL : { if (chance < 500) replace[dE] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 500) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 250) replace[dE] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 250) replace[dE] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 250) replace[dE] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dW])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR: { replace[dW] = FIRE; } break;
                                case CHARCOAL : { if (chance < 500) replace[dW] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 500) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 250) replace[dW] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 250) replace[dW] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 250) replace[dW] = CHARRED_WOOD; } break;
                            }

                            if (chance < 50) replace[index] = FIRE;
                        }
                        break;
                        case FIRE :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            int chance = rand()%1000;
                            switch (matrix[dN])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR: { replace[dN] = FLAME; } break;
                                case ASH : { replace[index] = AIR; } break;
                                case SMOKE : { replace[index] = AIR; } break;
                                case FIRE : { replace[index] = AIR; } break;
                                case CHARCOAL : { if (chance < 250) replace[dN] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 250) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 100) replace[dN] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 100) replace[dN] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 250) replace[dN] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dS])
                            {
                                case CHARCOAL : { if (chance < 50) replace[dS] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 50) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 25) replace[dS] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 25) replace[dS] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 50) replace[dS] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dE])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR: { replace[index] = FLAME; } break;
                                case ASH : { replace[index] = AIR; } break;
                                case SMOKE : { replace[index] = AIR; } break;
                                case CHARCOAL : { if (chance < 50) replace[dE] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 50) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 25) replace[dE] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 25) replace[dE] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 50) replace[dE] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dW])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR: { replace[index] = FLAME; } break;
                                case ASH : { replace[index] = AIR; } break;
                                case SMOKE : { replace[index] = AIR; } break;
                                case CHARCOAL : { if (chance < 50) replace[dW] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 50) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 25) replace[dW] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 25) replace[dW] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 50) replace[dW] = CHARRED_WOOD; } break;
                            }
                        }
                        break;
                        case FLAME :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            int chance = rand()%1000;
                            switch (matrix[dN])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR:
                                    {
                                        if (chance < 100) replace[dN] = FLARE;
                                        if (chance < 2) replace[index] = THICK_SMOKE;
                                        if (chance > 500) replace[index] = AIR;
                                    } break;
                                case ASH : { replace[index] = AIR; } break;
                                case SMOKE : { replace[index] = AIR; } break;
                                case CHARCOAL: { if (chance < 250) replace[dN] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 250) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 100) replace[dN] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 100) replace[dN] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 250) replace[dN] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dE])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR:
                                    {
                                        if (chance < 100) replace[dE] = FLARE;
                                        if (chance < 5) replace[index] = SMOKE;
                                        if (chance < 3) replace[index] = ASH;
                                        if (chance > 500) replace[index] = AIR;
                                    } break;
                                case ASH : { replace[index] = AIR; } break;
                                case SMOKE : { replace[index] = AIR; } break;
                                case CHARCOAL: { if (chance < 50) replace[dE] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 50) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 25) replace[dE] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 25) replace[dE] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 50) replace[dE] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dW])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR:
                                    {
                                        if (chance < 100) replace[dW] = FLARE;
                                        if (chance < 5) replace[index] = SMOKE;
                                        if (chance < 3) replace[index] = ASH;
                                        if (chance > 500) replace[index] = AIR;
                                    } break;
                                case ASH : { replace[index] = AIR; } break;
                                case SMOKE : { replace[index] = AIR; } break;
                                case CHARCOAL: { if (chance < 50) replace[dW] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 50) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 25) replace[dW] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 25) replace[dW] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 50) replace[dW] = CHARRED_WOOD; } break;
                            }
                        }
                        break;
                        case FLARE :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            int chance = rand()%1000;
                            switch (matrix[dN])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR: { replace[dN] = FIRE; } break;
                                case ASH : { replace[index] = AIR; } break;
                                case SMOKE : { replace[index] = AIR; } break;
                                case CHARCOAL : { if (chance < 500) replace[dN] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 250) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 250) replace[dN] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 250) replace[dN] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 500) replace[dN] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dE])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR: { replace[index] = FIRE; } break;
                                case ASH : { replace[index] = AIR; } break;
                                case SMOKE : { replace[index] = AIR; } break;
                                case CHARCOAL : { if (chance < 250) replace[dE] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 250) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 100) replace[dE] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 100) replace[dE] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 250) replace[dE] = CHARRED_WOOD; } break;
                            }
                            switch (matrix[dW])
                            {
                                case WATER : { replace[index] = AIR; } break;
                                case AIR: { replace[index] = FIRE; } break;
                                case ASH : { replace[index] = AIR; } break;
                                case SMOKE : { replace[index] = AIR; } break;
                                case CHARCOAL : { if (chance < 250) replace[dW] = EMBER; } break;
                                case CHARRED_WOOD: { if (chance < 250) replace[dW] = CHARCOAL; } break;
                                case WOOD: { if (chance < 100) replace[dW] = CHARRED_WOOD; } break;
                                case TRUNK: { if (chance < 100) replace[dW] = CHARRED_WOOD; } break;
                                case BRANCH: { if (chance < 250) replace[dW] = CHARRED_WOOD; } break;
                            }
                        }
                        break;
                        case THIN_SMOKE :
                        {
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            int dS  = int( (_y+1) * width + (_x  ) );

                            int chance = rand()%100;
                            switch (matrix[dS])
                            {
                                case AIR : { matrix[index] = AIR; replace[index] = AIR;} break;
                                case SMOKE : { if (rand()%10 < 6) {replace[dS] = THIN_SMOKE; replace[index] = AIR;}} break;
                                case THICK_SMOKE : { if (rand()%100 < 4) {replace[dS] = THIN_SMOKE; replace[index] = THIN_SMOKE;}} break;
                            }
                            if (chance < 40)
                            {
                                switch (matrix[dE])
                                {
                                    case AIR : { replace[dE] = THIN_SMOKE; replace[index] = AIR; } break;
                                    case SMOKE : { replace[dE] = THIN_SMOKE; replace[index] = SMOKE; } break;
                                    case THICK_SMOKE : { replace[dE] = THIN_SMOKE; replace[index] = THICK_SMOKE; } break;
                                }
                            }
                            if (chance > 60)
                            {
                                switch (matrix[dW])
                                {
                                    case AIR : { replace[dW] = THIN_SMOKE; replace[index] = AIR; } break;
                                    case SMOKE : { replace[dW] = THIN_SMOKE; replace[index] = SMOKE; } break;
                                    case THICK_SMOKE : { replace[dW] = THIN_SMOKE; replace[index] = THICK_SMOKE; } break;
                                }
                            }
                        }
                        break;
                        case SMOKE :
                        {
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            int dS  = int( (_y+1) * width + (_x  ) );

                            int chance = rand()%100;
                            switch (matrix[dS])
                            {
                                case AIR : { matrix[index] = THIN_SMOKE; replace[index] = THIN_SMOKE;} break;
                                case THIN_SMOKE : { if (rand()%10 < 6) {replace[dS] = SMOKE; replace[index] = THIN_SMOKE;}} break;
                                case THICK_SMOKE : { if (rand()%100 < 4) {replace[dS] = SMOKE; replace[index] = SMOKE;}} break;
                            }
                            if (chance < 40)
                            {
                            switch (matrix[dE])
                            {
                                case AIR : { replace[dE] = SMOKE; replace[index] = AIR; } break;
                                case THIN_SMOKE : { replace[dE] = SMOKE; replace[index] = THIN_SMOKE; } break;
                                case THICK_SMOKE : { replace[dE] = SMOKE; replace[index] = THICK_SMOKE; } break;
                            }
                            }
                            if (chance > 60)
                            {
                            switch (matrix[dW])
                            {
                                case AIR : { replace[dW] = SMOKE; replace[index] = AIR; } break;
                                case THIN_SMOKE : { replace[dW] = SMOKE; replace[index] = THIN_SMOKE; } break;
                                case THICK_SMOKE : { replace[dW] = SMOKE; replace[index] = THICK_SMOKE; } break;
                            }
                            }
                        }
                        break;
                        case THICK_SMOKE :
                        {
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            
                            int chance = rand()%100;
                            switch (matrix[dS])
                            {
                                case AIR : { matrix[index] = THIN_SMOKE; replace[index] = THIN_SMOKE;} break;
                                case THIN_SMOKE : { if (rand()%10 < 6) {replace[dS] = THICK_SMOKE; replace[index] = THIN_SMOKE;}} break;
                                case SMOKE : { if (rand()%100 < 4) {replace[dS] = THICK_SMOKE; replace[index] = SMOKE;}} break;
                            }
                            if (chance < 40)
                            {
                                switch (matrix[dE])
                                {
                                    case AIR : { replace[dE] = THICK_SMOKE; replace[index] = AIR; } break;
                                    case THIN_SMOKE : { replace[dE] = THICK_SMOKE; replace[index] = THIN_SMOKE; } break;
                                    case SMOKE : { replace[dE] = THICK_SMOKE; replace[index] = SMOKE; } break;
                                }
                            }
                            if (chance > 60)
                            {
                                switch (matrix[dW])
                                {
                                    case AIR : { replace[dW] = THICK_SMOKE; replace[index] = AIR; } break;
                                    case THIN_SMOKE : { replace[dW] = THICK_SMOKE; replace[index] = THIN_SMOKE; } break;
                                    case SMOKE : { replace[dW] = THICK_SMOKE; replace[index] = SMOKE; } break;
                                }
                            }
                        }
                        break;
                        case ICE :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            if ((matrix[dN] == LAVA) ||
                                (matrix[dS] == LAVA) ||
                                (matrix[dE] == LAVA) ||
                                (matrix[dW] == LAVA) ||
                                (matrix[dN] == EMBER) ||
                                (matrix[dS] == EMBER) ||
                                (matrix[dE] == EMBER) ||
                                (matrix[dW] == EMBER) ||
                                (matrix[dN] == FIRE) ||
                                (matrix[dS] == FIRE) ||
                                (matrix[dE] == FIRE) ||
                                (matrix[dW] == FIRE) ||
                                (matrix[dN] == FLAME) ||
                                (matrix[dS] == FLAME) ||
                                (matrix[dE] == FLAME) ||
                                (matrix[dW] == FLAME)) { replace[index] = WATER; }
                            if (matrix[dS] == GRASS) { replace[index] = WATER; }
                        }
                        break;
                        case TRUNK :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            if (rand()%1000 < 5)
                            {
                                if (matrix[dN] == AIR && rand()%1000 < 10) { replace[dN] = TRUNK; }
                                if (matrix[dE] == AIR && matrix[dN] == AIR && matrix[dS] == AIR && rand()%1000 < 5) { replace[dE] = TRUNK; }
                                if (matrix[dW] == AIR && matrix[dN] == AIR && matrix[dS] == AIR && rand()%1000 < 5) { replace[dW] = TRUNK; }
                                if (matrix[dN] == AIR && matrix[dS] == AIR && matrix[dE] == AIR && matrix[dW] == TRUNK && rand()%1000 < 10) { replace[dE] = BRANCH; }
                                if (matrix[dN] == AIR && matrix[dS] == AIR && matrix[dE] == TRUNK && matrix[dW] == AIR && rand()%1000 < 10) { replace[dW] = BRANCH; }
                            }
                        }
                        case BRANCH :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            if (rand()%100 < 5)
                            {
                                if (matrix[dN] == AIR && matrix[dE] == AIR && matrix[dW] == AIR && rand()%1000 < 5) { replace[dN] = BRANCH; }
                                if (matrix[dE] == AIR && matrix[dS] == AIR && matrix[dN] == AIR && rand()%1000 < 10) { replace[dE] = BRANCH; }
                                if (matrix[dW] == AIR && matrix[dS] == AIR && matrix[dN] == AIR && rand()%1000 < 10) { replace[dW] = BRANCH; }
                                if (matrix[dN] == AIR && matrix[dS] == AIR && matrix[dE] == AIR && matrix[dW] == AIR && rand()%1000 < 5) { replace[dN] = LEAVES; }
                            }
                        }
                        case LEAVES :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            if (rand()%10000 < 5)
                            {
                                if (matrix[dN] == AIR && matrix[dE] == BRANCH || matrix[dW] == BRANCH && rand()%1000 < 5) { replace[dN] = LEAVES; }
                                if (matrix[dE] == AIR && matrix[dS] == BRANCH || matrix[dN] == BRANCH && rand()%1000 < 10) { replace[dE] = LEAVES; }
                                if (matrix[dW] == AIR && matrix[dS] == BRANCH || matrix[dN] == BRANCH && rand()%1000 < 10) { replace[dW] = LEAVES; }
                            }
                        }
                        case GRASS :
                        {
                            int dNW = int( (_y-1) * width + (_x-1) );
                            int dNE = int( (_y-1) * width + (_x+1) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dSE = int( (_y+1) * width + (_x+1) );
                            int dSW = int( (_y+1) * width + (_x-1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            if (rand()%1000 < 5)
                            {
                                if ((matrix[dE] == DIRT || matrix[dE] == SOIL) && !Collision(_x+1, _y-1)) replace[dE] = GRASS;
                                else if ((matrix[dW] == DIRT || matrix[dW] == SOIL) && !Collision(_x-1, _y-1)) replace[dW] = GRASS;
                                else if ((matrix[dNE] == DIRT || matrix[dNE] == SOIL) && !Collision(_x+1, _y-2)) replace[dNE] = GRASS;
                                else if ((matrix[dNW] == DIRT || matrix[dNE] == SOIL) && !Collision(_x-1, _y-2)) replace[dNW] = GRASS;
                                else if ((matrix[dSE] == DIRT || matrix[dSE] == SOIL) && !Collision(_x+1, _y)) replace[dSE] = GRASS;
                                else if ((matrix[dSW] == DIRT || matrix[dSE] == SOIL) && !Collision(_x-1, _y)) replace[dSW] = GRASS;
                            }
                        }
                        break;
                        case MOSS :
                        {
                            int dNW = int( (_y-1) * width + (_x-1) );
                            int dNE = int( (_y-1) * width + (_x+1) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dSE = int( (_y+1) * width + (_x+1) );
                            int dSW = int( (_y+1) * width + (_x-1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            if (rand()%1000 < 5)
                            {
                                if ((matrix[dE] == STONE) && !Collision(_x+1, _y-1)) replace[dE] = MOSS;
                                else if ((matrix[dW] == STONE) && !Collision(_x-1, _y-1)) replace[dW] = MOSS;
                                else if ((matrix[dNE] == STONE) && !Collision(_x+1, _y-2)) replace[dNE] = MOSS;
                                else if ((matrix[dNW] == STONE) && !Collision(_x-1, _y-2)) replace[dNW] = MOSS;
                                else if ((matrix[dSE] == STONE) && !Collision(_x+1, _y)) replace[dSE] = MOSS;
                                else if ((matrix[dSW] == STONE) && !Collision(_x-1, _y)) replace[dSW] = MOSS;
                            }
                        }
                        break;
                        case PIPE :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );

                            switch (matrix[dE])
                            {
                                case PIPE_WATER : {replace[dE] = PIPE; replace[index] = PIPE_WATER;} break;
                                case PIPE_BRINE : {replace[dE] = PIPE; replace[index] = PIPE_BRINE;} break;
                                case PIPE_HONEY : {replace[dE] = PIPE; replace[index] = PIPE_HONEY;} break;
                                case PIPE_BLOOD : {replace[dE] = PIPE; replace[index] = PIPE_BLOOD;} break;
                                case PIPE_LAVA : {replace[dE] = PIPE; replace[index] = PIPE_LAVA;} break;
                                case PIPE_MUCK : {replace[dE] = PIPE; replace[index] = PIPE_MUCK;} break;
                                case PIPE_MUD : {replace[dE] = PIPE; replace[index] = PIPE_MUD;} break;
                            }
                            switch (matrix[dW])
                            {
                                case PIPE_WATER : {replace[dW] = PIPE; replace[index] = PIPE_WATER;} break;
                                case PIPE_BRINE : {replace[dW] = PIPE; replace[index] = PIPE_BRINE;} break;
                                case PIPE_HONEY : {replace[dW] = PIPE; replace[index] = PIPE_HONEY;} break;
                                case PIPE_BLOOD : {replace[dW] = PIPE; replace[index] = PIPE_BLOOD;} break;
                                case PIPE_LAVA : {replace[dW] = PIPE; replace[index] = PIPE_LAVA;} break;
                                case PIPE_MUCK : {replace[dW] = PIPE; replace[index] = PIPE_MUCK;} break;
                                case PIPE_MUD : {replace[dW] = PIPE; replace[index] = PIPE_MUD;} break;
                            }
                            switch (matrix[dS])
                            {
                                case PIPE_WATER : {replace[dS] = PIPE; replace[index] = PIPE_WATER;} break;
                                case PIPE_BRINE : {replace[dS] = PIPE; replace[index] = PIPE_BRINE;} break;
                                case PIPE_HONEY : {replace[dS] = PIPE; replace[index] = PIPE_HONEY;} break;
                                case PIPE_BLOOD : {replace[dS] = PIPE; replace[index] = PIPE_BLOOD;} break;
                                case PIPE_LAVA : {replace[dS] = PIPE; replace[index] = PIPE_LAVA;} break;
                                case PIPE_MUCK : {replace[dS] = PIPE; replace[index] = PIPE_MUCK;} break;
                                case PIPE_MUD : {replace[dS] = PIPE; replace[index] = PIPE_MUD;} break;
                                case WATER : {replace[dS] = AIR; replace[index] = PIPE_WATER;} break;
                                case BRINE : {replace[dS] = AIR; replace[index] = PIPE_BRINE;} break;
                                case HONEY : {replace[dS] = AIR; replace[index] = PIPE_HONEY;} break;
                                case BLOOD : {replace[dS] = AIR; replace[index] = PIPE_BLOOD;} break;
                                case LAVA : {replace[dS] = AIR; replace[index] = PIPE_LAVA;} break;
                                case MUCK : {replace[dS] = AIR; replace[index] = PIPE_MUCK;} break;
                                case MUD : {replace[dS] = AIR; replace[index] = PIPE_MUD;} break;
                            }

                        }
                        break;
                        case PUMP :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            if (matrix[dN] == AIR)
                            {
                                switch (matrix[dS])
                                {
                                    case PIPE_WATER : {replace[dS] = PIPE; replace[dN] = WATER;} break;
                                    case PIPE_BRINE : {replace[dS] = PIPE; replace[dN] = BRINE;} break;
                                    case PIPE_HONEY : {replace[dS] = PIPE; replace[dN] = HONEY;} break;
                                    case PIPE_BLOOD : {replace[dS] = PIPE; replace[dN] = BLOOD;} break;
                                    case PIPE_LAVA : {replace[dS] = PIPE; replace[dN] = LAVA;} break;
                                    case PIPE_MUCK : {replace[dS] = PIPE; replace[dN] = MUCK;} break;
                                    case PIPE_MUD : {replace[dS] = PIPE; replace[dN] = MUD;} break;
                                }
                            }
                        }
                        break;
                        case GUTTER :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );

                            switch (matrix[dE])
                            {
                                case GUTTER_WATER : {replace[dE] = GUTTER; replace[index] = GUTTER_WATER;} break;
                                case GUTTER_BRINE : {replace[dE] = GUTTER; replace[index] = GUTTER_BRINE;} break;
                                case GUTTER_HONEY : {replace[dE] = GUTTER; replace[index] = GUTTER_HONEY;} break;
                                case GUTTER_BLOOD : {replace[dE] = GUTTER; replace[index] = GUTTER_BLOOD;} break;
                                case GUTTER_LAVA : {replace[dE] = GUTTER; replace[index] = GUTTER_LAVA;} break;
                                case GUTTER_MUCK : {replace[dE] = GUTTER; replace[index] = GUTTER_MUCK;} break;
                                case GUTTER_MUD : {replace[dE] = GUTTER; replace[index] = GUTTER_MUD;} break;
                            }
                            switch (matrix[dW])
                            {
                                case GUTTER_WATER : {replace[dW] = GUTTER; replace[index] = GUTTER_WATER;} break;
                                case GUTTER_BRINE : {replace[dW] = GUTTER; replace[index] = GUTTER_BRINE;} break;
                                case GUTTER_HONEY : {replace[dW] = GUTTER; replace[index] = GUTTER_HONEY;} break;
                                case GUTTER_BLOOD : {replace[dW] = GUTTER; replace[index] = GUTTER_BLOOD;} break;
                                case GUTTER_LAVA : {replace[dW] = GUTTER; replace[index] = GUTTER_LAVA;} break;
                                case GUTTER_MUCK : {replace[dW] = GUTTER; replace[index] = GUTTER_MUCK;} break;
                                case GUTTER_MUD : {replace[dW] = GUTTER; replace[index] = GUTTER_MUD;} break;
                            }
                            switch (matrix[dN])
                            {
                                case GUTTER_WATER : {replace[dN] = GUTTER; replace[index] = GUTTER_WATER;} break;
                                case GUTTER_BRINE : {replace[dN] = GUTTER; replace[index] = GUTTER_BRINE;} break;
                                case GUTTER_HONEY : {replace[dN] = GUTTER; replace[index] = GUTTER_HONEY;} break;
                                case GUTTER_BLOOD : {replace[dN] = GUTTER; replace[index] = GUTTER_BLOOD;} break;
                                case GUTTER_LAVA : {replace[dN] = GUTTER; replace[index] = GUTTER_LAVA;} break;
                                case GUTTER_MUCK : {replace[dN] = GUTTER; replace[index] = GUTTER_MUCK;} break;
                                case GUTTER_MUD : {replace[dN] = GUTTER; replace[index] = GUTTER_MUD;} break;
                                case WATER : {replace[dN] = AIR; replace[index] = GUTTER_WATER;} break;
                                case BRINE : {replace[dN] = AIR; replace[index] = GUTTER_BRINE;} break;
                                case HONEY : {replace[dN] = AIR; replace[index] = GUTTER_HONEY;} break;
                                case BLOOD : {replace[dN] = AIR; replace[index] = GUTTER_BLOOD;} break;
                                case LAVA : {replace[dN] = AIR; matrix[dN] = AIR; replace[index] = GUTTER_LAVA;} break;
                                case MUCK : {replace[dN] = AIR; matrix[dN] = AIR; replace[index] = GUTTER_MUCK;} break;
                                case MUD : {replace[dN] = AIR; matrix[dN] = AIR; replace[index] = GUTTER_MUD;} break;
                            }
                        }
                        break;
                        case DRAIN :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            if (matrix[dS] == AIR)
                            {
                                switch (matrix[dN])
                                {
                                    case GUTTER_WATER : {replace[dN] = GUTTER; replace[dS] = WATER;} break;
                                    case GUTTER_BRINE : {replace[dN] = GUTTER; replace[dS] = BRINE;} break;
                                    case GUTTER_HONEY : {replace[dN] = GUTTER; replace[dS] = HONEY;} break;
                                    case GUTTER_BLOOD : {replace[dN] = GUTTER; replace[dS] = BLOOD;} break;
                                    case GUTTER_LAVA : {replace[dN] = GUTTER; replace[dS] = LAVA;} break;
                                    case GUTTER_MUCK : {replace[dN] = GUTTER; replace[dS] = MUCK;} break;
                                    case GUTTER_MUD : {replace[dN] = GUTTER; replace[dS] = MUD;} break;
                                }
                            }
                        }
                        break;
                        case VALVE_OPEN :
                        {
                            int dN  = int( (_y-1) * width + (_x  ) );
                            int dS  = int( (_y+1) * width + (_x  ) );
                            int dE  = int( (_y  ) * width + (_x+1) );
                            int dW  = int( (_y  ) * width + (_x-1) );
                            switch (matrix[dN])
                            {
                                case GUTTER_WATER : {if (matrix[dS] == GUTTER) replace[dN] = GUTTER; replace[dS] = GUTTER_WATER;} break;
                                case GUTTER_BRINE : {if (matrix[dS] == GUTTER) replace[dN] = GUTTER; replace[dS] = GUTTER_BRINE;} break;
                                case GUTTER_HONEY : {if (matrix[dS] == GUTTER) replace[dN] = GUTTER; replace[dS] = GUTTER_HONEY;} break;
                                case GUTTER_BLOOD : {if (matrix[dS] == GUTTER) replace[dN] = GUTTER; replace[dS] = GUTTER_BLOOD;} break;
                                case GUTTER_LAVA : {if (matrix[dS] == GUTTER) replace[dN] = GUTTER; replace[dS] = GUTTER_LAVA;} break;
                                case GUTTER_MUCK : {if (matrix[dS] == GUTTER) replace[dN] = GUTTER; replace[dS] = GUTTER_MUCK;} break;
                                case GUTTER_MUD : {if (matrix[dS] == GUTTER) replace[dN] = GUTTER; replace[dS] = GUTTER_MUD;} break;
                            }
                            switch (matrix[dS])
                            {
                                case PIPE_WATER : {if (matrix[dN] == PIPE) replace[dS] = PIPE; replace[dN] = PIPE_WATER;} break;
                                case PIPE_BRINE : {if (matrix[dN] == PIPE) replace[dS] = PIPE; replace[dN] = PIPE_BRINE;} break;
                                case PIPE_HONEY : {if (matrix[dN] == PIPE) replace[dS] = PIPE; replace[dN] = PIPE_HONEY;} break;
                                case PIPE_BLOOD : {if (matrix[dN] == PIPE) replace[dS] = PIPE; replace[dN] = PIPE_BLOOD;} break;
                                case PIPE_LAVA : {if (matrix[dN] == PIPE) replace[dS] = PIPE; replace[dN] = PIPE_LAVA;} break;
                                case PIPE_MUCK : {if (matrix[dN] == PIPE) replace[dS] = PIPE; replace[dN] = PIPE_MUCK;} break;
                                case PIPE_MUD : {if (matrix[dN] == PIPE) replace[dS] = PIPE; replace[dN] = PIPE_MUD;} break;
                            }
                            switch (matrix[dE])
                            {
                                case PIPE_WATER : {if (matrix[dW] == PIPE) replace[dE] = PIPE; replace[dW] = PIPE_WATER;} break;
                                case PIPE_BRINE : {if (matrix[dW] == PIPE) replace[dE] = PIPE; replace[dW] = PIPE_BRINE;} break;
                                case PIPE_HONEY : {if (matrix[dW] == PIPE) replace[dE] = PIPE; replace[dW] = PIPE_HONEY;} break;
                                case PIPE_BLOOD : {if (matrix[dW] == PIPE) replace[dE] = PIPE; replace[dW] = PIPE_BLOOD;} break;
                                case PIPE_LAVA : {if (matrix[dW] == PIPE) replace[dE] = PIPE; replace[dW] = PIPE_LAVA;} break;
                                case PIPE_MUCK : {if (matrix[dW] == PIPE) replace[dE] = PIPE; replace[dW] = PIPE_MUCK;} break;
                                case PIPE_MUD : {if (matrix[dW] == PIPE) replace[dE] = PIPE; replace[dW] = PIPE_MUD;} break;
                                case GUTTER_WATER : {if (matrix[dW] == GUTTER) replace[dE] = GUTTER; replace[dW] = GUTTER_WATER;} break;
                                case GUTTER_BRINE : {if (matrix[dW] == GUTTER) replace[dE] = GUTTER; replace[dW] = GUTTER_BRINE;} break;
                                case GUTTER_HONEY : {if (matrix[dW] == GUTTER) replace[dE] = GUTTER; replace[dW] = GUTTER_HONEY;} break;
                                case GUTTER_BLOOD : {if (matrix[dW] == GUTTER) replace[dE] = GUTTER; replace[dW] = GUTTER_BLOOD;} break;
                                case GUTTER_LAVA : {if (matrix[dW] == GUTTER) replace[dE] = GUTTER; replace[dW] = GUTTER_LAVA;} break;
                                case GUTTER_MUCK : {if (matrix[dW] == GUTTER) replace[dE] = GUTTER; replace[dW] = GUTTER_MUCK;} break;
                                case GUTTER_MUD : {if (matrix[dW] == GUTTER) replace[dE] = GUTTER; replace[dW] = GUTTER_MUD;} break;
                            }
                            switch (matrix[dW])
                            {
                                case PIPE_WATER : {if (matrix[dE] == PIPE) replace[dW] = PIPE; replace[dE] = PIPE_WATER;} break;
                                case PIPE_BRINE : {if (matrix[dE] == PIPE) replace[dW] = PIPE; replace[dE] = PIPE_BRINE;} break;
                                case PIPE_HONEY : {if (matrix[dE] == PIPE) replace[dW] = PIPE; replace[dE] = PIPE_HONEY;} break;
                                case PIPE_BLOOD : {if (matrix[dE] == PIPE) replace[dW] = PIPE; replace[dE] = PIPE_BLOOD;} break;
                                case PIPE_LAVA : {if (matrix[dE] == PIPE) replace[dW] = PIPE; replace[dE] = PIPE_LAVA;} break;
                                case PIPE_MUCK : {if (matrix[dE] == PIPE) replace[dW] = PIPE; replace[dE] = PIPE_MUCK;} break;
                                case PIPE_MUD : {if (matrix[dE] == PIPE) replace[dW] = PIPE; replace[dE] = PIPE_MUD;} break;
                                case GUTTER_WATER : {if (matrix[dE] == GUTTER) replace[dW] = GUTTER; replace[dE] = GUTTER_WATER;} break;
                                case GUTTER_BRINE : {if (matrix[dE] == GUTTER) replace[dW] = GUTTER; replace[dE] = GUTTER_BRINE;} break;
                                case GUTTER_HONEY : {if (matrix[dE] == GUTTER) replace[dW] = GUTTER; replace[dE] = GUTTER_HONEY;} break;
                                case GUTTER_BLOOD : {if (matrix[dE] == GUTTER) replace[dW] = GUTTER; replace[dE] = GUTTER_BLOOD;} break;
                                case GUTTER_LAVA : {if (matrix[dE] == GUTTER) replace[dW] = GUTTER; replace[dE] = GUTTER_LAVA;} break;
                                case GUTTER_MUCK : {if (matrix[dE] == GUTTER) replace[dW] = GUTTER; replace[dE] = GUTTER_MUCK;} break;
                                case GUTTER_MUD : {if (matrix[dE] == GUTTER) replace[dW] = GUTTER; replace[dE] = GUTTER_MUD;} break;
                            }
                        }
                        break;
                        case AXLE_LEFT :
                        {
                            int dNW = int( (_y-1) * width + (_x-1) );
                            int dN = int( (_y-1) * width + (_x) );
                            int dNE = int( (_y-1) * width + (_x+1) );
                            int dW = int( (_y) * width + (_x-1) );
                            int dE = int( (_y) * width + (_x+1) );
                            int dSW = int( (_y+1) * width + (_x-1) );
                            int dSE = int( (_y+1) * width + (_x+1) );
                            int dS = int( (_y+1) * width + (_x) );
                            
                            if (
                                    (GetType(matrix[dNW]) == SOLID) &&
                                    (GetType(matrix[dN]) == SOLID) &&
                                    (GetType(matrix[dNE]) == SOLID) &&
                                    (GetType(matrix[dE]) == SOLID) &&
                                    (GetType(matrix[dSE]) == SOLID) &&
                                    (GetType(matrix[dS]) == SOLID) &&
                                    (GetType(matrix[dSW]) == SOLID) &&
                                    (GetType(matrix[dW]) == SOLID) )
                            {
                                int v1 = matrix[dNW];
                                int v2 = matrix[dN];
                                int v3 = matrix[dNE];
                                int v4 = matrix[dE];
                                int v5 = matrix[dSE];
                                int v6 = matrix[dS];
                                int v7 = matrix[dSW];
                                int v8 = matrix[dW];

                                replace[dNW] = v2;
                                replace[dN] =  v3;
                                replace[dNE] = v4;
                                replace[dE] =  v5;
                                replace[dSE] = v6;
                                replace[dS] =  v7;
                                replace[dSW] = v8;
                                replace[dW] =  v1;

                                matrix[dNW] = v2;
                                matrix[dN] =  v3;
                                matrix[dNE] = v4;
                                matrix[dE] =  v5;
                                matrix[dSE] = v6;
                                matrix[dS] =  v7;
                                matrix[dSW] = v8;
                                matrix[dW] =  v1;
                            }
                        }
                        break;
                        case AXLE_RIGHT:
                        {
                            int dNW = int( (_y-1) * width + (_x-1) );
                            int dN = int( (_y-1) * width + (_x) );
                            int dNE = int( (_y-1) * width + (_x+1) );
                            int dW = int( (_y) * width + (_x-1) );
                            int dE = int( (_y) * width + (_x+1) );
                            int dSW = int( (_y+1) * width + (_x-1) );
                            int dSE = int( (_y+1) * width + (_x+1) );
                            int dS = int( (_y+1) * width + (_x) );

                            if (
                                    (GetType(matrix[dNW]) == SOLID) &&
                                    (GetType(matrix[dN]) == SOLID) &&
                                    (GetType(matrix[dNE]) == SOLID) &&
                                    (GetType(matrix[dE]) == SOLID) &&
                                    (GetType(matrix[dSE]) == SOLID) &&
                                    (GetType(matrix[dS]) == SOLID) &&
                                    (GetType(matrix[dSW]) == SOLID) &&
                                    (GetType(matrix[dW]) == SOLID) )
                            {
                                int v1 = matrix[dNW];
                                int v2 = matrix[dN];
                                int v3 = matrix[dNE];
                                int v4 = matrix[dE];
                                int v5 = matrix[dSE];
                                int v6 = matrix[dS];
                                int v7 = matrix[dSW];
                                int v8 = matrix[dW];

                                replace[dNW] = v8;
                                replace[dN] =  v1;
                                replace[dNE] = v2;
                                replace[dE] =  v3;
                                replace[dSE] = v4;
                                replace[dS] =  v5;
                                replace[dSW] = v6;
                                replace[dW] =  v7;

                                matrix[dNW] = v8;
                                matrix[dN] =  v1;
                                matrix[dNE] = v2;
                                matrix[dE] =  v3;
                                matrix[dSE] = v4;
                                matrix[dS] =  v5;
                                matrix[dSW] = v6;
                                matrix[dW] =  v7;
                            }

                        }
                        break;
                        case CONVEYOR_LEFT :
                        {
                            int dNW = int( (_y-1) * width + (_x-1) );
                            int dNE = int( (_y-1) * width + (_x+1) );
                            int dN = int( (_y-1) * width + (_x) );

                            if ( matrix[dN] < VALVE_CLOSED && matrix[dNE] < VALVE_CLOSED && matrix[dNW] < VALVE_CLOSED )
                            {
                                if (matrix[dN] > MUD && matrix[dNW] == AIR)
                                {
                                    replace[dNW] = matrix[dN];
                                    replace[dN] = matrix[dNE];
                                    replace[dNE] = AIR;

                                    matrix[dNW] = matrix[dN];
                                    matrix[dN] = matrix[dNE];
                                    matrix[dNE] = AIR;
                                }
                            }
                        }
                        break;
                        case CONVEYOR_RIGHT :
                        {
                            int dNW = int( (_y-1) * width + (_x-1) );
                            int dNE = int( (_y-1) * width + (_x+1) );
                            int dN = int( (_y-1) * width + (_x) );
                            if ( matrix[dN] < VALVE_CLOSED && matrix[dNE] < VALVE_CLOSED && matrix[dNW] < VALVE_CLOSED )
                            {
                                if (matrix[dN] > MUD && matrix[dNE] == AIR)
                                {
                                    replace[dNE] = matrix[dN];
                                    replace[dN] = matrix[dNW];
                                    replace[dNW] = AIR;

                                    matrix[dNW] = matrix[dN];
                                    matrix[dN] = matrix[dNE];
                                    matrix[dNE] = AIR;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        matrix = replace;
    }

    // Return Methods

    int CellType(int x, int y)
    {
        int index = (y)*width+(x);
        int current_cell = matrix[index];

        // Update Moving Tiles
        int cell_type = SOLID;
        switch (current_cell)
        {
            // Fluid
            case WATER : cell_type = FLUID; break;
            case BRINE : cell_type = FLUID; break;
            case BLOOD : cell_type = FLUID; break;
            case FOG : cell_type = FLUID; break;
            // Gel
            case HONEY : cell_type = GEL; break;
            case LAVA : cell_type = GEL; break;
            case MUCK : cell_type = GEL; break;
            case MUD : cell_type = GEL; break;
            // Grain
            case ASH : cell_type = GRAIN; break;
            case CHARCOAL : cell_type = GRAIN; break;
            case EMBER : cell_type = GRAIN; break;
            case SAND : cell_type = GRAIN; break;
            case SNOW : cell_type = GRAIN; break;
            case SLEET : cell_type = GRAIN; break;
            case SALT : cell_type = GRAIN; break;
            case SILT : cell_type = GRAIN; break;
            case GRAVEL : cell_type = GRAIN; break;
            // Gas
            case STEAM : cell_type = GAS; break;
            case THIN_SMOKE : cell_type = GAS; break;
            case SMOKE : cell_type = GAS; break;
            case THICK_SMOKE : cell_type = GAS; break;
        }
        return cell_type;
    }

    int GetType(int current_cell)
    {
        int cell_type = SOLID;
        switch (current_cell)
        {
            // Fluid
            case WATER : cell_type = FLUID; break;
            case BRINE : cell_type = FLUID; break;
            case BLOOD : cell_type = FLUID; break;
            case FOG : cell_type = FLUID; break;
            // Gel
            case HONEY : cell_type = GEL; break;
            case LAVA : cell_type = GEL; break;
            case MUCK : cell_type = GEL; break;
            case MUD : cell_type = GEL; break;
            // Grain
            case ASH : cell_type = GRAIN; break;
            case CHARCOAL : cell_type = GRAIN; break;
            case EMBER : cell_type = GRAIN; break;
            case SAND : cell_type = GRAIN; break;
            case SNOW : cell_type = GRAIN; break;
            case SLEET : cell_type = GRAIN; break;
            case SALT : cell_type = GRAIN; break;
            case SILT : cell_type = GRAIN; break;
            case GRAVEL : cell_type = GRAIN; break;
            // Gas
            case STEAM : cell_type = GAS; break;
            case THIN_SMOKE : cell_type = GAS; break;
            case SMOKE : cell_type = GAS; break;
            case THICK_SMOKE : cell_type = GAS; break;
            // 
            // Mechanism
        }
        return cell_type;
    }

    int Neighbors(int x, int y)
    {
        int value = 0;

        //value += bool(matrix[(y-2)*width+(x)]);
        //value += bool(matrix[(y-1)*width+(x)]);
        //value += bool(matrix[(y)*width+(x-1)]);
        //value += bool(matrix[(y)*width+(x+1)]);

        value += GetLightValue(x, y-2);
        value += GetLightValue(x, y-1);
        value += GetLightValue(x-1, y);
        value += GetLightValue(x+1, y);

        /*
        value += GetLightValue(x, y-5);
        value += GetLightValue(x, y-4);
        value += GetLightValue(x, y-3);
        value += GetLightValue(x, y-2);
        value += GetLightValue(x, y-1);
        value += GetLightValue(x, y+1);
        value += GetLightValue(x, y+2);
        value += GetLightValue(x-1, y);
        value += GetLightValue(x+1, y);
        value += GetLightValue(x-2, y);
        value += GetLightValue(x+2, y);

        value += GetLightValue(x-1, y-1);
        value += GetLightValue(x+1, y-1);
        value += GetLightValue(x-1, y+1);
        value += GetLightValue(x+1, y+1);
        */

        return value;
    }

    float GetLightValue(int x, int y)
    {
        float value = 1.0;
        switch (matrix[y*width+x])
        {
            case AIR : { value = -1.0; } break;
            case LAVA : { value = -3.0; } break;
            case EMBER : { value = -2.0; } break;
            case FIRE : { value = -2.0; } break;
            case FLAME : { value = -2.0; } break;
            case FLARE : { value = -3.0; } break;
        }

        return value;
    }

    bool FluidCollision(int x, int y)
    {
        return (replace[y*width+x] > FOG);
    }

    bool DualCollision(int x, int y)
    {
        return bool(matrix[y*width+x]) || bool(replace[y*width+x]);
    }

    bool Collision(int x, int y)
    {
        return bool(matrix[y*width+x]);
    }

    bool IsColliding(int x, int y)
    {
        return matrix[y*width+x] > MUD;
    }

};
