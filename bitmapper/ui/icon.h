class Icon
{

public:

    int size = 8;

    /*
    int [00] =
    {
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
    };
    */

    // Materials
    int solid[64] =
    {
        0,0,0,4,4,4,4,2,
        0,0,4,4,4,4,2,1,
        0,4,4,4,4,2,1,1,
        3,3,3,3,3,1,1,1,
        3,3,3,3,3,1,1,1,
        3,3,3,3,3,1,1,0,
        3,3,3,3,3,1,0,0,
        3,3,3,3,3,0,0,0,
    };
    int loose[64] =
    {
        0,0,0,4,4,4,4,2,
        0,0,4,0,4,0,2,1,
        0,4,4,4,4,2,0,1,
        3,3,3,3,3,1,1,1,
        3,0,3,0,3,1,0,1,
        3,3,3,3,3,1,1,0,
        3,0,3,0,3,1,0,0,
        3,3,3,3,3,0,0,0,
    };
    int grain[64] =
    {
        0,0,0,4,4,0,0,0,
        0,0,4,4,4,4,0,0,
        0,3,3,4,4,3,3,0,
        0,3,3,3,3,3,3,0,
        3,3,2,3,3,2,3,3,
        2,2,2,2,2,2,2,2,
        1,2,2,2,2,2,2,1,
        0,1,1,1,1,1,1,0,
    };
    int gel[64] =
    {
        0,0,3,3,3,3,0,0,
        0,3,4,4,4,4,3,0,
        2,4,4,4,4,4,4,2,
        2,3,4,4,4,4,3,2,
        2,2,3,3,3,3,2,2,
        2,2,2,2,2,2,2,2,
        0,1,2,2,2,2,1,0,
        0,0,1,1,1,1,0,0,
    };
    int fluid[64] =
    {
        0,0,0,0,4,4,0,0,
        0,0,0,4,4,0,0,0,
        0,0,3,4,4,0,0,0,
        0,0,3,4,4,3,0,0,
        0,2,3,4,4,3,2,0,
        0,2,3,3,3,3,2,0,
        0,1,2,2,2,2,1,0,
        0,0,1,1,1,1,0,0,
    };
    int gas[64] =
    {
        3,4,3,4,3,4,3,4,
        4,3,4,3,4,3,4,3,
        2,3,2,3,2,3,2,3,
        3,2,3,2,3,2,3,2,
        1,2,1,2,1,2,1,2,
        2,1,2,1,2,1,2,1,
        0,1,0,1,0,1,0,1,
        1,0,1,0,1,0,1,0,
    };
    int plasma[64] =
    {
        0,0,7,0,0,7,0,0,
        0,7,8,7,7,8,7,0,
        0,6,0,6,6,0,6,0,
        0,0,0,0,0,0,0,0,
        0,0,8,7,7,8,0,0,
        0,0,7,6,6,7,0,0,
        0,8,7,6,6,7,8,0,
        0,0,7,6,6,7,0,0,
    };
    int fume[64] =
    {
        0,0,8,0,0,8,0,0,
        0,0,0,0,0,0,0,0,
        0,7,0,6,6,0,7,0,
        0,0,0,0,0,0,0,0,
        6,0,5,0,0,5,0,6,
        0,0,0,0,0,0,0,0,
        5,4,0,3,3,0,4,5,
        4,3,0,2,2,0,3,4,
    };

    //
    int plumbing[64] =
    {
        0,0,0,0,0,0,0,4,
        0,0,0,3,3,3,3,4,
        0,0,3,3,3,3,3,4,
        0,3,3,3,3,3,3,4,
        0,3,3,3,2,1,1,3,
        0,3,3,3,1,0,0,2,
        0,3,3,3,1,0,0,0,
        4,4,4,4,3,2,0,0,
    };
    int platform[64] =
    {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        5,5,5,5,5,5,5,5,
        4,4,4,4,4,4,4,4,
        4,4,4,4,4,4,4,4,
        0,3,3,3,3,3,3,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
    };
    int gizmo[64] =
    {
        0,0,0,4,4,0,0,0,
        0,4,3,3,3,3,4,0,
        0,3,2,1,1,2,3,0,
        4,3,1,0,0,1,3,4,
        4,3,1,0,0,1,3,4,
        0,3,2,1,1,2,3,0,
        0,4,3,3,3,3,4,0,
        0,0,0,4,4,0,0,0,
    };
    int logic[64] =
    {
        0,0,8,8,8,8,0,0,
        0,7,5,5,5,5,7,0,
        6,5,5,5,5,5,5,6,
        6,5,5,5,5,5,5,6,
        0,4,5,5,5,5,4,0,
        0,0,3,3,3,3,0,0,
        0,0,0,0,0,1,2,0,
        0,0,0,0,0,0,1,2,
    };
    int plant[64] =
    {
        0,0,0,0,0,6,6,5,
        0,0,0,6,5,5,5,3,
        0,0,6,5,4,4,4,1,
        0,6,5,4,3,4,3,0,
        0,5,4,3,4,3,1,0,
        0,4,3,4,3,1,0,0,
        0,2,1,1,1,0,0,0,
        2,0,0,0,0,0,0,0,
    };
    int critter[64] =
    {
        0,0,7,7,7,7,0,0,
        0,6,5,5,5,5,6,0,
        3,5,1,5,5,1,5,3,
        3,5,5,5,5,5,5,3,
        3,5,5,2,2,5,5,3,
        3,5,5,2,2,5,5,3,
        0,2,5,5,5,5,2,0,
        0,0,1,1,1,1,0,0,
    };



    //
    //
    //

    // Tools
    int wand[64] =
    {
        0,0,0,0,0,0,4,3,
        0,0,0,0,0,4,3,0,
        0,0,0,0,4,3,0,0,
        0,0,0,4,4,0,0,0,
        0,0,4,4,3,0,0,0,
        0,4,4,3,0,0,0,0,
        4,4,3,0,0,0,0,0,
        4,3,0,0,0,0,0,0,
    };
    int pickaxe[64] =
    {
        0,0,0,8,8,7,0,0,
        0,0,0,0,0,5,7,0,
        0,0,0,0,0,4,5,7,
        0,0,0,0,1,0,0,6,
        0,0,3,1,0,0,0,0,
        0,3,2,4,0,0,0,6,
        3,2,4,0,0,0,0,0,
        1,4,0,0,0,0,0,0,
    };
    int axe[64] =
    {
        0,0,0,0,8,8,8,0,
        0,0,0,0,5,5,5,8,
        0,0,0,2,1,5,5,7,
        0,0,2,1,0,0,7,6,
        0,3,2,0,0,0,6,0,
        0,2,1,0,0,0,0,6,
        1,2,0,0,0,0,0,0,
        2,1,0,0,0,0,0,0,
    };
    int wrench[64] =
    {
        0,0,0,0,0,1,1,0,
        0,0,0,0,1,1,0,1,
        0,0,0,0,1,1,1,1,
        0,0,0,1,1,1,1,0,
        0,1,1,1,1,0,0,0,
        1,1,1,1,0,0,0,0,
        1,0,1,1,0,0,0,0,
        0,1,1,0,0,0,0,0,
    };
    int hammer[64] =
    {
        0,0,0,8,8,7,0,0,
        0,0,0,5,4,4,7,0,
        0,0,0,0,4,4,4,7,
        0,0,0,3,4,0,5,6,
        0,0,3,2,1,0,0,6,
        0,3,2,1,0,0,0,0,
        3,2,1,0,0,0,0,0,
        2,1,0,0,0,0,0,0,
    };
    // Containers
    int chest[64] =
    {
        0,0,0,0,0,0,0,0,
        0,8,8,8,8,8,8,0,
        8,7,7,7,7,7,7,8,
        6,4,4,4,4,4,4,6,
        4,6,6,6,6,6,6,4,
        4,6,6,6,6,6,6,4,
        2,1,1,1,1,1,1,2,
        0,0,0,0,0,0,0,0,
    };
};