class WorldGenerator
{

public:

    //
    //
    //

    // Terrain Tiles
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


    //
    //
    //

    bool IsDataValid()
    {
        for (int i = 0; i < generation_steps; i++)
        {
            if (generation_param[i][0] != tTile::AIR) is_data_valid = true;
        }
        return is_data_valid;
    }

    void Copy()
    {
        for (int p = 0; p < world.total_parameters; p++)
        {
            world.clipboard_param[p] = world.generation_param[world.selected_step][p];
        }
    }

    void Paste()
    {
        generation_steps++;
        for (int i = generation_steps-1; i > selected_step; i--)
        {
            for (int p = 0; p < total_parameters; p++)
            {
                generation_param[i-1][p] = generation_param[i-2][p];
            }
        }
        for (int p = 0; p < total_parameters; p++)
        {
            generation_param[selected_step][p] = clipboard_param[p];
        }
        if (selected_step > 0) selected_step--;
    }

    // Matrix
    void ClearMatrix()
    {
        tCell::matrix.clear();
    }

    void InitializeMatrix(int w, int h)
    {
        tCell::width = w;
        tCell::height = h;
        for (int y = 0; y < tCell::height; y++)
        {
            for (int x = 0; x < tCell::width; x++)
            {
                tCell::matrix.push_back(tTile::AIR); tCell::replace.push_back(tTile::AIR);
            }
        }
        std::cout << tCell::matrix.size();
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
        int preset_data[62][12] = {
            { tTile::STONE,      mADD,     8,   1,  0,   100, 20,  75,  0,   0,   0,   0   },
            { tTile::STONE,      mADD,     4,   1,  0,   100, 30,  76,  0,   0,   0,   0   },
            { tTile::STONE,      mADD,     2,   1,  0,   100, 40,  77,  0,   0,   0,   0   },
            { tTile::STONE,      mADD,     1,   1,  0,   100, 50,  78,  0,   0,   0,   0   },
            { tTile::STONE,      mADD,     1,   1,  0,   100, 60,  79,  0,   0,   0,   0   },
            { tTile::MANTLE,     mADD,     8,   1,  0,   100, 95,  100, 0,   0,   0,   0   },
            { tTile::MANTLE,     mADD,     16,  1,  0,   100, 97,  100, 0,   0,   0,   0   },

            { tTile::STONE,      mEXPAND,  0,   1,  0,   100, 15,  85,  25,  50,  100, 100 },
            { tTile::STONE,      mEXPAND,  0,   1,  0,   100, 25,  85,  25,  50,  100, 100 },
            { tTile::STONE,      mEXPAND,  0,   1,  0,   100, 35,  85,  50,  25,  100, 100 },
            { tTile::STONE,      mEXPAND,  0,   2,  0,   100, 45,  85,  25,  5,   100, 100 },
            { tTile::STONE,      mEXPAND,  0,   1,  0,   100, 55,  85,  25,  50,  100, 100 },
            { tTile::STONE,      mEXPAND,  0,   4,  0,   100, 65,  85,  25,  50,  100, 100 },
            { tTile::STONE,      mEXPAND,  0,   2,  0,   100, 75,  85,  50,  25,  100, 100 },
            { tTile::STONE,      mEXPAND,  0,   1,  0,   100, 80,  85,  25,  5,   100, 100 },

            { tTile::SOIL,       mEXPAND,  0,   4,  0,   100, 8,   30,  50,  25,  90,  90  },
            { tTile::MUD,        mEXPAND,  0,   1,  0,   100, 10,  40,  50,  25,  75,  75  },
            { tTile::SOIL,       mEXPAND,  0,   1,  0,   100, 8,   30,  50,  25,  90,  90  },
            { tTile::MUD,        mEXPAND,  0,   2,  0,   100, 10,  40,  50,  25,  75,  75  },
            { tTile::DIRT,       mEXPAND,  0,   1,  0,   100, 10,  40,  50,  25,  90,  90  },
            { tTile::MUD,        mEXPAND,  0,   1,  0,   100, 15,  50,  25,  12,  37,  37  },
            { tTile::DIRT,       mEXPAND,  0,   2,  0,   100, 15,  60,  50,  25,  90,  90  },
            { tTile::MUD,        mEXPAND,  0,   1,  0,   100, 15,  70,  25,  12,  37,  37  },
            { tTile::DIRT,       mEXPAND,  0,   4,  0,   100, 12,  80,  50,  25,  90,  90  },
            { tTile::DIRT,       mEXPAND,  0,   4,  0,   100, 6,   20,  50,  25,  100, 100 },

            { tTile::GRAVEL,     mEXPAND,  0,   4,  0,   100, 30,  80,  50,  0,   0,   0   },
            { tTile::GRAVEL,     mEXPAND,  0,   4,  0,   100, 50,  60,  50,  0,   0,   0   },
            { tTile::GRASS,      mEXPAND,  0,   1,  0,   100, 8,   25,  100, 0,   5,   5   },
            { tTile::MANTLE,     mEXPAND,  0,   16, 0,   100, 85,  100, 10,  10,  100, 100 },
            { tTile::LAVA,       mEXPAND,  0,   16, 0,   100, 90,  100, 100, 100, 100, 100 },

            { tTile::PLATINUM,   mSEED,    2,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { tTile::GOLD,       mSEED,    2,   1,  0,   100, 60,  80,  0,   0,   0,   0   },
            { tTile::SILVER,     mSEED,    3,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { tTile::COPPER,     mSEED,    4,   1,  0,   100, 30,  50,  0,   0,   0,   0   },
            { tTile::LEAD,       mSEED,    3,   1,  0,   100, 70,  80,  0,   0,   0,   0   },
            { tTile::TIN,        mSEED,    3,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { tTile::IRON,       mSEED,    4,   1,  0,   100, 25,  50,  0,   0,   0,   0   },
            { tTile::COBALT,     mSEED,    3,   1,  0,   100, 25,  40,  0,   0,   0,   0   },
            { tTile::NICKEL,     mSEED,    3,   1,  0,   100, 25,  30,  0,   0,   0,   0   },
            { tTile::TITANIUM,   mSEED,    2,   1,  0,   100, 40,  60,  0,   0,   0,   0   },
            { tTile::TUNGSTEN,   mSEED,    2,   1,  0,   100, 70,  80,  0,   0,   0,   0   },

            { tTile::PLATINUM,   mDEPOSIT, 0,   4,  0,   100, 60,  80,  25,  25,  25,  25  },
            { tTile::GOLD,       mDEPOSIT, 0,   4,  0,   100, 60,  80,  25,  25,  25,  25  },
            { tTile::SILVER,     mDEPOSIT, 0,   6,  0,   100, 50,  70,  25,  25,  25,  25  },
            { tTile::COPPER,     mDEPOSIT, 0,   8,  0,   100, 30,  50,  25,  25,  25,  25  },
            { tTile::LEAD,       mDEPOSIT, 0,   8,  0,   100, 70,  80,  25,  25,  25,  25  },
            { tTile::TIN,        mDEPOSIT, 0,   8,  0,   100, 50,  70,  25,  25,  25,  25  },
            { tTile::IRON,       mDEPOSIT, 0,   8,  0,   100, 25,  50,  25,  25,  25,  25  },
            { tTile::COBALT,     mDEPOSIT, 0,   6,  0,   100, 25,  40,  25,  25,  25,  25  },
            { tTile::NICKEL,     mDEPOSIT, 0,   6,  0,   100, 25,  30,  25,  25,  25,  25  },
            { tTile::TITANIUM,   mDEPOSIT, 0,   6,  0,   100, 40,  60,  25,  25,  25,  25  },
            { tTile::TUNGSTEN,   mDEPOSIT, 0,   4,  0,   100, 70,  80,  25,  25,  25,  25  },

            { tTile::JADE,       mSEED,    2,   1,  0,   100, 40,  60,  0,   0,   0,   0   },
            { tTile::RUBY,       mSEED,    2,   1,  0,   100, 40,  60,  0,   0,   0,   0   },
            { tTile::AMBER,      mSEED,    2,   1,  0,   100, 40,  60,  0,   0,   0,   0   },
            { tTile::LAPIS,      mSEED,    2,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { tTile::TOPAZ,      mSEED,    2,   1,  0,   100, 50,  70,  0,   0,   0,   0   },
            { tTile::DIAMOND,    mSEED,    2,   1,  0,   100, 70,  90,  0,   0,   0,   0   },
            { tTile::EMERALD,    mSEED,    2,   1,  0,   100, 70,  90,  0,   0,   0,   0   },
            { tTile::AMETHYST,   mSEED,    2,   1,  0,   100, 60,  80,  0,   0,   0,   0   },
            { tTile::SAPPHIRE,   mSEED,    2,   1,  0,   100, 60,  80,  0,   0,   0,   0   },
        };

        for (int i = 0; i < generation_steps; i++)
        {
            for (int p = 0; p < total_parameters; p++)
            {
                generation_param[i][p] = preset_data[i][p];
            }
        }
    }

    //
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

    //
    std::string GenerateWorld()
    {
        std::string message = "";
        int index = generation_step-1;

        float W = float(float(tCell::width)/100.0);
        float H = float(float(tCell::height)/100.0);

        switch (generation_param[index][pMODE])
        {
            case mADD :
                {
                    message = "Adding " + tTile::NAME[generation_param[index][pTILE]] + " Layer";
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
                    message = "Seeding " + tTile::NAME[generation_param[index][pTILE]] + " Layer";
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
                    message = "Expanding " + tTile::NAME[generation_param[index][pTILE]] + " Layer";
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
                    message = "Depositing " + tTile::NAME[generation_param[index][pTILE]] + " Layer";
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

};