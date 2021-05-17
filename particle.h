class Particle
{
public:

    float x = 0;
    float y = 0;

    float vx = 0;
    float vy = 0;

    float speed = 25.0;
    float gravity = 0.3;
    float max_speed = 1.0;

    int r = 255;
    int g = 255;
    int b = 255;
    int a = 255;

    float duration = 1.0;

    bool sticky = false;
    bool bouncy = true;
    bool heavy = false;

    bool destroys = true;
    bool damages = false;
    bool poisons = false;
    bool trips = false;
    bool stuns = false;
    bool burns = false;

    void Position(float X, float Y)
    {
        x = X;
        y = Y;
    }

    void Velocity(float X, float Y)
    {
        vx = X;
        vy = Y;
        CheckSpeed();
    }

    void Move(float X, float Y, float delta, bool collision)
    {
        CheckSpeed();
        if (!collision)
        {
            x += X*speed*delta;
            if (!heavy) y += (Y+gravity)*speed*delta;
            if (heavy) y += (Y+(gravity*2))*speed*delta;
        }
        else
        {
            if (bouncy)
            {
                vx = -X;
                vy = -Y;
            }
            if (sticky)
            {
                vx = 0.0;
                vy = 0.0;
            }
        }
    }

    void CheckSpeed()
    {
        if (vx > max_speed) vx = max_speed;
        else if (vx < -max_speed) vx = -max_speed;
        
        if (vy > max_speed) vy = max_speed;
        else if (vy < -max_speed) vy = -max_speed;
    }

    void Duration(float D)
    {
        duration = D;
    }

    void Color(int R, int G, int B, int A)
    {
        r = R;
        g = G;
        b = B;
        a = A;
    }
};
